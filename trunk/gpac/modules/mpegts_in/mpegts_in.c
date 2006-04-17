/*
 *			GPAC - Multimedia Framework C SDK
 *
 *			Authors: Jean le Feuvre
 *				Copyright (c) 2005-200X ENST
 *					All rights reserved
 *
 *  This file is part of GPAC / M2TS reader module
 *
 *  GPAC is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser General Public License as published by
 *  the Free Software Foundation; either version 2, or (at your option)
 *  any later version.
 *   
 *  GPAC is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser General Public License for more details.
 *   
 *  You should have received a copy of the GNU Lesser General Public
 *  License along with this library; see the file COPYING.  If not, write to
 *  the Free Software Foundation, 675 Mass Ave, Cambridge, MA 02139, USA. 
 *		
 */

#include <gpac/modules/service.h>
#include <gpac/modules/codec.h>
#include <gpac/mpegts.h>
#include <gpac/thread.h>
#include <gpac/network.h>
#include <gpac/constants.h>

typedef struct
{
	GF_ClientService *service;
	u32 pmt_state;
	GF_M2TS_Demuxer *ts;

	/*demuxer thread*/
	GF_Thread *th;
	u32 run_state;

	/*net playing*/
	GF_Socket *sock;
	
	/*local file playing*/
	FILE *file;
	u32 start_range, end_range;
	u32 file_size;
	Double duration;
	u32 nb_playing;
} M2TSIn;

static Bool M2TS_CanHandleURL(GF_InputService *plug, const char *url)
{
	char *sExt;
	
	if (!strnicmp(url, "udp://", 6) 
		|| !strnicmp(url, "mpegts-udp://", 13) 
		|| !strnicmp(url, "mpegts-tcp://", 13) ) {
		return 1;
	}
	
	sExt = strrchr(url, '.');
	if (!sExt) return 0;
	if (gf_term_check_extension(plug, "video/mpeg-2", "ts m2t", "MPEG-2 TS", sExt)) return 1;
	return 0;
}

#define REGULATE_TIME_SLOT	400

static void M2TS_Regulate(M2TSIn *read)
{
	GF_NetworkCommand com;

	com.command_type = GF_NET_BUFFER_QUERY;
	/*sleep untill the buffer occupancy is too low - note that this work because all streams in this
	demuxer are synchronized*/
	while (read->run_state) {
		/*wait for a connected channel !!*/
		if (!read->nb_playing && (read->pmt_state==2)) {
			gf_sleep(50);
		} else {
			gf_term_on_command(read->service, &com, GF_OK);
			if (com.buffer.occupancy < REGULATE_TIME_SLOT) return;
			//fprintf(stdout, "MPEG-2 TS regulate: %d ms in buffers\n", com.buffer.occupancy );
			gf_sleep(com.buffer.occupancy  - REGULATE_TIME_SLOT);
		}
	}
}

static void MP2TS_DeclareStream(M2TSIn *read, GF_M2TS_PES *stream)
{
	GF_ObjectDescriptor *od;
	GF_ESD *esd;

	/*create a stream description for this channel*/
	esd = gf_odf_desc_esd_new(0);
	esd->ESID = stream->pid;
	/*ASSIGN PCR here*/
	esd->OCRESID = stream->program->pcr_pid;
	switch (stream->stream_type) {
	case GF_M2TS_VIDEO_MPEG1:
		esd->decoderConfig->streamType = GF_STREAM_VISUAL;
		esd->decoderConfig->objectTypeIndication = 0x6A;
		break;
	case GF_M2TS_VIDEO_MPEG2:
		esd->decoderConfig->streamType = GF_STREAM_VISUAL;
		esd->decoderConfig->objectTypeIndication = 0x65;
		break;
	case GF_M2TS_VIDEO_MPEG4:
		esd->decoderConfig->streamType = GF_STREAM_VISUAL;
		esd->decoderConfig->objectTypeIndication = 0x20;
		break;
	case GF_M2TS_VIDEO_H264:
		esd->decoderConfig->streamType = GF_STREAM_VISUAL;
		esd->decoderConfig->objectTypeIndication = 0x21;
		break;
	case GF_M2TS_AUDIO_MPEG1:
		esd->decoderConfig->streamType = GF_STREAM_AUDIO;
		esd->decoderConfig->objectTypeIndication = 0x6B;
		break;
	case GF_M2TS_AUDIO_MPEG2:
		esd->decoderConfig->streamType = GF_STREAM_AUDIO;
		esd->decoderConfig->objectTypeIndication = 0x69;
		break;
	case GF_M2TS_AUDIO_AAC:
		esd->decoderConfig->streamType = GF_STREAM_AUDIO;
		esd->decoderConfig->objectTypeIndication = 0x40;
		break;
	default:
		gf_odf_desc_del((GF_Descriptor *)esd);
		return;
	}
	esd->decoderConfig->bufferSizeDB = 0;

	/*we only use AUstart indicator*/
	esd->slConfig->useAccessUnitStartFlag = 1;
	esd->slConfig->useAccessUnitEndFlag = 0;
	esd->slConfig->useRandomAccessPointFlag = 1;
	esd->slConfig->AUSeqNumLength = 0;
	esd->slConfig->timestampResolution = 90000;
	
	/*decoder config*/
	if (0) {
		esd->decoderConfig->decoderSpecificInfo->dataLength = 0;
	}

	/*declare object to terminal*/
	od = (GF_ObjectDescriptor*)gf_odf_desc_new(GF_ODF_OD_TAG);
	gf_list_add(od->ESDescriptors, esd);
	od->objectDescriptorID = stream->pid;	
	/*declare but don't regenerate scene*/
	gf_term_add_media(read->service, (GF_Descriptor*)od, 1);
	/*wait for connection*/
	while (!stream->user) gf_sleep(0);
}

static void MP2TS_SetupProgram(M2TSIn *read, GF_M2TS_Program *prog)
{
	u32 i, count;
	count = gf_list_count(prog->streams);
	for (i=0; i<count; i++) {
		GF_M2TS_PES *pes = gf_list_get(prog->streams, i);
		if (pes->pid==prog->pmt_pid) continue;
		gf_m2ts_set_pes_framing(pes, GF_M2TS_PES_FRAMING_SKIP);
		MP2TS_DeclareStream(read, pes);
	}
	/*force scene regeneration*/
	gf_term_add_media(read->service, NULL, 0);
}

static void MP2TS_SendPacket(M2TSIn *read, GF_M2TS_PES_PCK *pck)
{
	GF_SLHeader slh;
	assert(pck->stream->user);

	if (!pck->stream->program->first_dts && pck->PTS) {
		pck->stream->program->first_dts = (pck->DTS ? pck->DTS : pck->PTS) - read->start_range * 90;
	}

	memset(&slh, 0, sizeof(GF_SLHeader));
	slh.accessUnitStartFlag = (pck->flags & GF_M2TS_PES_PCK_AU_START) ? 1 : 0;
	if (slh.accessUnitStartFlag) {
		if (pck->PTS < pck->stream->program->first_dts) return;
		slh.compositionTimeStampFlag = 1;
		slh.compositionTimeStamp = pck->PTS - pck->stream->program->first_dts;
		if (pck->DTS) {
			slh.decodingTimeStampFlag = 1;
			slh.decodingTimeStamp = pck->DTS - pck->stream->program->first_dts;
		}
		slh.randomAccessPointFlag = (pck->flags & GF_M2TS_PES_PCK_RAP) ? 1 : 0;
	}
	gf_term_on_sl_packet(read->service, pck->stream->user, pck->data, pck->data_len, &slh, GF_OK);
}

static void M2TS_OnEvent(GF_M2TS_Demuxer *ts, u32 evt_type, void *param)
{
	M2TSIn *read = (M2TSIn *) ts->user;
	switch (evt_type) {
	case GF_M2TS_EVT_PAT_FOUND:
		if (!read->pmt_state) {
			read->pmt_state = 1;
			gf_term_on_connect(read->service, NULL, GF_OK);
		}
		break;
	case GF_M2TS_EVT_PMT_FOUND:
		MP2TS_SetupProgram(read, param);
		break;
	case GF_M2TS_EVT_PAT_UPDATE:
	case GF_M2TS_EVT_PMT_UPDATE:
		if (read->pmt_state) read->pmt_state = 2;
		break;
	case GF_M2TS_EVT_PES_PCK:
		MP2TS_SendPacket(read, param);
		break;
	}
}


u32 M2TS_Run(void *_p)
{
	char data[3760];
	u32 size, i;
	M2TSIn *read = _p;

	read->run_state = 1;
	read->ts->on_event = M2TS_OnEvent;
	gf_m2ts_reset_parsers(read->ts);

	if (read->sock) {
		while (read->run_state) {
			/*read chunks by chunks*/
			GF_Err e = gf_sk_receive(read->sock, data, 3760, 0, &size);
			if (!size || e) {
				gf_sleep(3);
				continue;
			}
			/*process chunk*/
			gf_m2ts_process_data(read->ts, data, size);
		}

	} else {
		u32 pos = 0;
		if (read->start_range && read->duration) {
			Double perc = read->start_range / (1000 * read->duration);
			pos = (u32) (s64) (perc * read->file_size);
			/*align to TS packet size*/
			while (pos%188) pos++;
			if (pos>=read->file_size) {
				read->start_range = 0;
				pos = 0;
			}
		}
		fseek(read->file, pos, SEEK_SET);
		while (read->run_state && !feof(read->file) ) {
			/*read chunks by chunks*/
			size = fread(data, 1, 188, read->file);
			if (!size) break;
			/*process chunk*/
			gf_m2ts_process_data(read->ts, data, size);
		
			/*regulate file reading*/
			M2TS_Regulate(read);
		}

		if (read->nb_playing) {
			for (i=0; i<GF_M2TS_MAX_STREAMS; i++) {
				GF_M2TS_PES *pes = (GF_M2TS_PES *)read->ts->ess[i];
				if (!pes || (pes->pid==pes->program->pmt_pid)) continue;
				if (!pes->user || !pes->reframe) continue;
				gf_term_on_sl_packet(read->service, pes->user, NULL, 0, NULL, GF_EOS);
				gf_m2ts_set_pes_framing(pes, GF_M2TS_PES_FRAMING_SKIP);
			}
		}

	}
	read->run_state = 2;
	return 0;
}

void M2TS_SetupLive(M2TSIn *read, char *url)
{
	GF_Err e = GF_OK;
	char *str;
	u16 port;
	u32 sock_type = 0;
	if (!strnicmp(url, "udp://", 6) || !strnicmp(url, "mpegts-udp://", 13)) {
		sock_type = GF_SOCK_TYPE_UDP;
	} 
	else if (!strnicmp(url, "mpegts-tcp://", 13) ) {
		sock_type = GF_SOCK_TYPE_TCP;
	}
	if (!sock_type) e = GF_NOT_SUPPORTED;

	if (e) goto exit;

	url = strchr(url, ':');
	url += 3;

	read->sock = gf_sk_new(sock_type);
	if (!read->sock) { e = GF_IO_ERR; goto exit; }
	gf_sk_set_buffer_size(read->sock, 0, 20*188);

	/*setup port and src*/
	port = 1234;
	str = strrchr(url, ':');
	/*take care of IPv6 address*/
	if (str && strchr(str, ']')) str = strchr(url, ':');
	if (str) port = atoi(str+1);
	gf_sk_bind(read->sock, port, 1);
	if (str) str[0] = 0;

	/*do we have a source ?*/
	if (strlen(url) && strcmp(url, "localhost") ) {
		if (gf_sk_is_multicast_address(url)) {
			gf_sk_setup_multicast(read->sock, url, port, 0, 1, NULL);
		} else {
			gf_sk_set_remote_address(read->sock, url);
			gf_sk_set_remote_port(read->sock, port);
		}
	}
	if (str) str[0] = ':';
	read->pmt_state = 0;
	read->th = gf_th_new();
	/*start playing for tune-in*/
	gf_th_run(read->th, M2TS_Run, read);

exit:
	if (e) {
		gf_term_on_connect(read->service, NULL, e);
	}
}

static void M2TS_OnEventPCR(GF_M2TS_Demuxer *ts, u32 evt_type, void *param)
{
	if (evt_type==GF_M2TS_EVT_PES_PCR) {
		M2TSIn *read = ts->user;
		GF_M2TS_PES_PCK *pck = param;
		if (!read->nb_playing) {
			read->nb_playing = pck->stream->pid;
			read->end_range = (u32) (pck->PTS / 90);
		} else if (read->nb_playing == pck->stream->pid) {
			read->start_range = (u32) (pck->PTS / 90);
		}
	}
}

static GF_Err M2TS_ConnectService(GF_InputService *plug, GF_ClientService *serv, const char *url)
{
	char data[188];
	u32 size;
	s32 nb_rwd;
	char szURL[2048];
	char *ext;
	M2TSIn *read = plug->priv;
	read->service = serv;

	strcpy(szURL, url);
	ext = strrchr(szURL, '#');
	if (ext) ext[0] = 0;

	read->pmt_state = 0;
	read->duration = 0;

	/*remote fetch*/
	if (strstr(url, "udp://") || strstr(url, "tcp://") ) {
		M2TS_SetupLive(read, (char *) szURL);
		return GF_OK;
	}

	read->file = fopen(szURL, "rb");
	if (!read->file) {
		gf_term_on_connect(serv, NULL, GF_URL_ERROR);
		return GF_OK;
	}

	fseek(read->file, 0, SEEK_END);
	read->file_size = ftell(read->file);
	/*estimate duration*/
	read->nb_playing = 0;
	read->ts->on_event = M2TS_OnEventPCR;
	read->end_range = 0;
	nb_rwd = 1;
	while (1) {
		fseek(read->file, read->file_size - 188 * nb_rwd, SEEK_SET);
		/*read chunks by chunks*/
		size = fread(data, 1, 188, read->file);
		if (!size) break;
		/*process chunk*/
		gf_m2ts_process_data(read->ts, data, size);
		if (read->nb_playing) break;
		nb_rwd ++;
	}

	fseek(read->file, 0, SEEK_SET);
	gf_m2ts_reset_parsers(read->ts);
	read->start_range = 0;
	while (1) {
		/*read chunks by chunks*/
		size = fread(data, 1, 188, read->file);
		if (!size) break;
		/*process chunk*/
		gf_m2ts_process_data(read->ts, data, size);
		if (read->start_range) break;
	}
	read->duration = (read->end_range - read->start_range) / 300000.0;
	gf_m2ts_demux_del(read->ts);
	read->ts = gf_m2ts_demux_new();
	read->ts->user = read;
	read->end_range = read->start_range = 0;
	read->nb_playing = 0;

	read->th = gf_th_new();
	/*start playing for tune-in*/
	gf_th_run(read->th, M2TS_Run, read);
	return GF_OK;
}

static GF_Err M2TS_CloseService(GF_InputService *plug)
{
	M2TSIn *read = plug->priv;

	if (read->th) {
		if (read->run_state == 1) {
			read->run_state=0;
			while (read->run_state!=2) gf_sleep(0);
		}
		gf_th_del(read->th);
		read->th = NULL;
	}

	if (read->file) fclose(read->file);
	read->file = NULL;
	gf_term_on_disconnect(read->service, NULL, GF_OK);
	return GF_OK;
}

static GF_Descriptor *M2TS_GetServiceDesc(GF_InputService *plug, u32 expect_type, const char *sub_url)
{
	u32 i=0;
	M2TSIn *read = plug->priv;
	GF_ObjectDescriptor *od = (GF_ObjectDescriptor *) gf_odf_desc_new(GF_ODF_IOD_TAG);
	od->objectDescriptorID = 1;
	/*returning an empty IOD means "no scene description", let the terminal handle all media objects*/
	return (GF_Descriptor *) od;
}

static GF_Err M2TS_ConnectChannel(GF_InputService *plug, LPNETCHANNEL channel, const char *url, Bool upstream)
{
	u32 ES_ID;
	GF_Err e;
	M2TSIn *read = plug->priv;

	e = GF_STREAM_NOT_FOUND;
	if (strstr(url, "ES_ID")) {
		sscanf(url, "ES_ID=%d", &ES_ID);

		if ((ES_ID<GF_M2TS_MAX_STREAMS) && read->ts->ess[ES_ID]) {
			GF_M2TS_PES *pes = (GF_M2TS_PES *)read->ts->ess[ES_ID];
			if (pes->user) e = GF_SERVICE_ERROR;
			else {
				pes->user = channel;
				e = GF_OK;
			}
		}
	}
	gf_term_on_connect(read->service, channel, e);
	return e;
}

static GF_M2TS_PES *M2TS_GetChannel(M2TSIn *read, LPNETCHANNEL channel)
{
	u32 i;
	for (i=0; i<GF_M2TS_MAX_STREAMS; i++) {
		GF_M2TS_PES *pes = (GF_M2TS_PES *)read->ts->ess[i];
		if (!pes || (pes->pid==pes->program->pmt_pid)) continue;
		if (pes->user == channel) return pes;
	}
	return NULL;
}
static GF_Err M2TS_DisconnectChannel(GF_InputService *plug, LPNETCHANNEL channel)
{
	M2TSIn *read = plug->priv;
	GF_Err e = GF_STREAM_NOT_FOUND;
	GF_M2TS_PES *pes = M2TS_GetChannel(read, channel);
	if (pes) {
		pes->user = NULL;
		e = GF_OK;
	}
	gf_term_on_disconnect(read->service, channel, e);
	return GF_OK;
}

static GF_Err M2TS_ServiceCommand(GF_InputService *plug, GF_NetworkCommand *com)
{
	GF_M2TS_PES *pes;
	M2TSIn *read = plug->priv;

	if (!com->base.on_channel) return GF_NOT_SUPPORTED;
	switch (com->command_type) {
	/*we cannot pull complete AUs from the stream*/
	case GF_NET_CHAN_SET_PULL:
		return GF_NOT_SUPPORTED;
	/*we cannot seek stream by stream*/
	case GF_NET_CHAN_INTERACTIVE:
		return GF_NOT_SUPPORTED;
	case GF_NET_CHAN_BUFFER:
		com->buffer.max = REGULATE_TIME_SLOT;
		com->buffer.min = 0;
		return GF_OK;
	case GF_NET_CHAN_DURATION:
		com->duration.duration = read->duration;
		return GF_OK;
	case GF_NET_CHAN_PLAY:
		pes = M2TS_GetChannel(read, com->base.on_channel);
		if (!pes) return GF_STREAM_NOT_FOUND;
		gf_m2ts_set_pes_framing(pes, GF_M2TS_PES_FRAMING_DEFAULT);
		/*this is a multplex, only trigger the play command for the first stream activated*/
		if (!read->nb_playing) {
			read->start_range = (u32) (com->play.start_range*1000);
			read->end_range = (com->play.end_range>0) ? (u32) (com->play.end_range*1000) : 0;
			/*start demuxer*/
			if (read->run_state!=1) {
				gf_th_run(read->th, M2TS_Run, read);
			}
		}
		read->nb_playing++;
		return GF_OK;
	case GF_NET_CHAN_STOP:
		pes = M2TS_GetChannel(read, com->base.on_channel);
		if (!pes) return GF_STREAM_NOT_FOUND;
		gf_m2ts_set_pes_framing(pes, GF_M2TS_PES_FRAMING_SKIP);

		assert(read->nb_playing);
		read->nb_playing--;
		/*stop demuxer*/
		if (!read->nb_playing && (read->run_state==1)) {
			read->run_state=0;
			while (read->run_state!=2) gf_sleep(2);
		}
		return GF_OK;
	default:
		return GF_OK;
	}
}


GF_InputService *NewM2TSReader()
{
	M2TSIn *reader;
	GF_InputService *plug = malloc(sizeof(GF_InputService));
	memset(plug, 0, sizeof(GF_InputService));
	GF_REGISTER_MODULE_INTERFACE(plug, GF_NET_CLIENT_INTERFACE, "GPAC MPEG-2 TS Reader", "gpac distribution")

	plug->CanHandleURL = M2TS_CanHandleURL;
	plug->ConnectService = M2TS_ConnectService;
	plug->CloseService = M2TS_CloseService;
	plug->GetServiceDescriptor = M2TS_GetServiceDesc;
	plug->ConnectChannel = M2TS_ConnectChannel;
	plug->DisconnectChannel = M2TS_DisconnectChannel;
	plug->ServiceCommand = M2TS_ServiceCommand;

	reader = malloc(sizeof(M2TSIn));
	memset(reader, 0, sizeof(M2TSIn));
	plug->priv = reader;
	reader->ts = gf_m2ts_demux_new();
	reader->ts->on_event = M2TS_OnEvent;
	reader->ts->user = reader;
	return plug;
}

void DeleteM2TSReader(void *ifce)
{
	GF_InputService *plug = (GF_InputService *) ifce;
	M2TSIn *read = plug->priv;
	gf_m2ts_demux_del(read->ts);
	free(read);
	free(plug);
}


Bool QueryInterface(u32 InterfaceType)
{
	switch (InterfaceType) {
	case GF_NET_CLIENT_INTERFACE: return 1;
	default: return 0;
	}
}

GF_BaseInterface *LoadInterface(u32 InterfaceType)
{
	switch (InterfaceType) {
	case GF_NET_CLIENT_INTERFACE: return (GF_BaseInterface *) NewM2TSReader();
	default: return NULL;
	}
}

void ShutdownInterface(GF_BaseInterface *ifce)
{
	switch (ifce->InterfaceType) {
	case GF_NET_CLIENT_INTERFACE:  DeleteM2TSReader(ifce); break;
	}
}

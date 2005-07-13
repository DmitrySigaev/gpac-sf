/*
 *			GPAC - Multimedia Framework C SDK
 *
 *			Copyright (c) Jean Le Feuvre 2000-2005 
 *					All rights reserved
 *
 *  This file is part of GPAC / AMR&EVRC&SMV reader module
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
#include <gpac/constants.h>
#include <gpac/isomedia.h>

typedef struct
{
	GF_ClientService *service;

	Bool is_remote;
	u32 start_offset;
	u32 mtype, sample_rate, block_size;

	FILE *stream;
	u32 duration;

	Bool needs_connection;
	u32 pad_bytes;
	Bool es_done, od_done;
	u32 es_status, od_status;
	LPNETCHANNEL es_ch, od_ch;

	unsigned char *es_data;
	u32 es_data_size;

	char *od_data;
	u32 od_data_size;

	SLHeader sl_hdr;

	Double start_range, end_range;
	u32 current_time;
	/*file downloader*/
	GF_DownloadSession * dnload;

	//Bool is_live;
} AMR_Reader;

static Bool AMR_CanHandleURL(GF_InputService *plug, const char *url)
{
	char *sExt;
	sExt = strrchr(url, '.');
	if (!sExt) return 0;
	if (gf_term_check_extension(plug, "audio/amr", "amr awb", "AMR Speech Data", sExt)) return 1;
	if (gf_term_check_extension(plug, "audio/evrc", "evc", "EVRC Speech Data", sExt)) return 1;
	if (gf_term_check_extension(plug, "audio/smv", "smv", "SMV Speech Data", sExt)) return 1;
	return 0;
}

static Bool file_is_local(const char *url)
{
	if (!strnicmp(url, "file://", 7)) return 1;
	if (strstr(url, "://")) return 0;
	return 1;
}


static Bool AMR_ConfigureFromFile(AMR_Reader *read)
{
	u32 i;
	char magic[20];

	if (!read->stream) return 0;
	read->mtype = 0;
	read->start_offset = 6;
	read->sample_rate = 8000;
	read->block_size = 160;
	fread(magic, 1, 20, read->stream);

	if (!strnicmp(magic, "#!AMR\n", 6)) {
		fseek(read->stream, 6, SEEK_SET);
		read->mtype = GF_ISOM_SUBTYPE_3GP_AMR;
	}
	else if (!strnicmp(magic, "#!EVRC\n", 7)) {
		fseek(read->stream, 7, SEEK_SET);
		read->start_offset = 7;
		read->mtype = GF_ISOM_SUBTYPE_3GP_EVRC;
	}
	else if (!strnicmp(magic, "#!SMV\n", 6)) {
		fseek(read->stream, 6, SEEK_SET);
		read->mtype = GF_ISOM_SUBTYPE_3GP_SMV;
	}
	else if (!strnicmp(magic, "#!AMR-WB\n", 9)) {
		read->mtype = GF_ISOM_SUBTYPE_3GP_AMR_WB;
		read->start_offset = 9;
		read->sample_rate = 16000;
		read->block_size = 320;
		fseek(read->stream, 9, SEEK_SET);
	}
	else if (!strnicmp(magic, "#!AMR_MC1.0\n", 12)) return 0;
	else if (!strnicmp(magic, "#!AMR-WB_MC1.0\n", 15)) return 0;
	else return 0;


	read->duration = 0;
	
	if (!read->is_remote) {
		u32 size;
		while (!feof(read->stream)) {
			u8 ft = fgetc(read->stream);
			switch (read->mtype) {
			case GF_ISOM_SUBTYPE_3GP_AMR:
			case GF_ISOM_SUBTYPE_3GP_AMR_WB:
				ft = (ft >> 3) & 0x0F;
				size = (read->mtype==GF_ISOM_SUBTYPE_3GP_AMR_WB) ? GF_AMR_WB_FRAME_SIZE[ft] : GF_AMR_FRAME_SIZE[ft];
				break;
			default:
				for (i=0; i<GF_SMV_EVRC_RATE_TO_SIZE_NB; i++) {
					if (GF_SMV_EVRC_RATE_TO_SIZE[2*i]==ft) {
						/*remove rate_type byte*/
						size = GF_SMV_EVRC_RATE_TO_SIZE[2*i+1] - 1;
						break;
					}
				}
				break;
			}

			if (size) fseek(read->stream, size, SEEK_CUR);
			read->duration += read->block_size;
		}
	}
	fseek(read->stream, read->start_offset, SEEK_SET);
	return 1;
}

static void AMR_OnData(void *cbk, char *data, u32 size, u32 status, GF_Err e)
{
	const char *szCache;
	u32 bytes_done;
	AMR_Reader *read = (AMR_Reader *) cbk;

	/*done*/
	if ((e == GF_EOS) && read->stream) {
		read->is_remote = 0;
		return;
	}
	/*handle service message*/
	gf_term_download_update_stats(read->dnload);
	if (!size) return;

	/*data fetching*/
	if (e >= GF_OK) {
		if (read->stream) return;

		/*open service*/
		szCache = gf_dm_get_cache_name(read->dnload);
		if (!szCache) e = GF_IO_ERR;
		else {
			read->stream = fopen((char *) szCache, "rb");
			if (!read->stream) e = GF_SERVICE_ERROR;
			else {
				/*if full file at once (in cache) parse duration*/
				if (e==GF_EOS) read->is_remote = 0;
				e = GF_OK;
				/*not enough data*/
				if (!AMR_ConfigureFromFile(read)) {
					/*bad data...*/
					gf_dm_get_stats(read->dnload, NULL, NULL, NULL, &bytes_done, NULL, NULL);
					if (bytes_done>10*1024) {
						e = GF_CORRUPTED_DATA;
					} else {
						fclose(read->stream);
						read->stream = NULL;
						return;
					}
				}
			}
		}
	}
	/*OK confirm*/
	if (read->needs_connection) {
		read->needs_connection = 0;
		gf_term_on_connect(read->service, NULL, e);
	}
}

static void AMR_DownloadFile(GF_InputService *plug, char *url)
{
	AMR_Reader *read = (AMR_Reader*) plug->priv;

	read->needs_connection = 1;

	read->dnload = gf_term_download_new(read->service, url, 0, AMR_OnData, read);
	if (!read->dnload) {
		read->needs_connection = 0;
		gf_term_on_connect(read->service, NULL, GF_NOT_SUPPORTED);
	}
	/*service confirm is done once fetched*/
}


static GF_Err AMR_ConnectService(GF_InputService *plug, GF_ClientService *serv, const char *url)
{
	char szURL[2048];
	char *ext;
	GF_Err reply;
	AMR_Reader *read = plug->priv;
	read->service = serv;

	if (read->dnload) gf_term_download_del(read->dnload);
	read->dnload = NULL;

	strcpy(szURL, url);
	ext = strrchr(szURL, '#');
	if (ext) ext[0] = 0;

	/*remote fetch*/
	read->is_remote = !file_is_local(szURL);
	if (read->is_remote) {
		AMR_DownloadFile(plug, (char *) szURL);
		return GF_OK;
	}

	reply = GF_OK;
	read->stream = fopen(szURL, "rb");
	if (!read->stream) {
		reply = GF_URL_ERROR;
	} else if (!AMR_ConfigureFromFile(read)) {
		fclose(read->stream);
		read->stream = NULL;
		reply = GF_NOT_SUPPORTED;
	}
	gf_term_on_connect(serv, NULL, reply);
	return GF_OK;
}

static GF_Err AMR_CloseService(GF_InputService *plug)
{
	AMR_Reader *read = plug->priv;
	if (read->stream) fclose(read->stream);
	read->stream = NULL;
	if (read->dnload) gf_term_download_del(read->dnload);
	read->dnload = NULL;

	if (read->es_data) free(read->es_data);
	read->es_data = NULL;
	gf_term_on_disconnect(read->service, NULL, GF_OK);
	return GF_OK;
}

static GF_ESD *AMR_GetESD(AMR_Reader *read)
{
	GF_BitStream *dsi;
	GF_ESD *esd;
	esd = gf_odf_desc_esd_new(0);
	esd->decoderConfig->streamType = GF_STREAM_AUDIO;
	esd->ESID = 2;
	esd->OCRESID = 1;
	esd->slConfig->timestampResolution = read->sample_rate;
	/*all packets are complete AUs*/
	esd->slConfig->useAccessUnitEndFlag = esd->slConfig->useAccessUnitStartFlag = 0;
	esd->slConfig->hasRandomAccessUnitsOnlyFlag = 1;

	if ((read->mtype==GF_ISOM_SUBTYPE_3GP_AMR) || (read->mtype==GF_ISOM_SUBTYPE_3GP_AMR_WB)) {
		esd->decoderConfig->objectTypeIndication = GPAC_QT_CODECS_OTI;
		dsi = gf_bs_new(NULL, 0, GF_BITSTREAM_WRITE);
		gf_bs_write_u32(dsi, read->mtype);
		gf_bs_get_content(dsi, (unsigned char **) & esd->decoderConfig->decoderSpecificInfo->data, & esd->decoderConfig->decoderSpecificInfo->dataLength);
		gf_bs_del(dsi);
	} 
	else if (read->mtype==GF_ISOM_SUBTYPE_3GP_EVRC) esd->decoderConfig->objectTypeIndication = 0xA0;
	else if (read->mtype==GF_ISOM_SUBTYPE_3GP_SMV) esd->decoderConfig->objectTypeIndication = 0xA1;
	return esd;
}

static GF_Descriptor *AMR_GetServiceDesc(GF_InputService *plug, u32 expect_type, const char *sub_url)
{
	GF_ESD *esd;
	AMR_Reader *read = plug->priv;
	GF_ObjectDescriptor *od = (GF_ObjectDescriptor *) gf_odf_desc_new(GF_ODF_OD_TAG);
	/*since we don't handle multitrack in aac, we don't need to check sub_url, only use expected type*/

	od->objectDescriptorID = 1;
	/*audio object*/
	if (expect_type==GF_MEDIA_OBJECT_AUDIO) {
		esd = AMR_GetESD(read);
		esd->OCRESID = 0;
		gf_list_add(od->ESDescriptors, esd);
		return (GF_Descriptor *) od;
	}
	/*inline scene*/
	/*OD ESD*/
	esd = gf_odf_desc_esd_new(0);
	esd->slConfig->timestampResolution = 1000;
	esd->decoderConfig->streamType = GF_STREAM_OD;
	esd->decoderConfig->objectTypeIndication = GPAC_STATIC_OD_OTI;
	esd->ESID = 1;
	gf_list_add(od->ESDescriptors, esd);
	return (GF_Descriptor *) od;
}

static GF_Err AMR_ConnectChannel(GF_InputService *plug, LPNETCHANNEL channel, const char *url, Bool upstream)
{
	u32 ES_ID;
	GF_Err e;
	AMR_Reader *read = plug->priv;

	e = GF_SERVICE_ERROR;
	if ((read->es_ch==channel) || (read->od_ch==channel)) goto exit;

	e = GF_STREAM_NOT_FOUND;
	if (strstr(url, "ES_ID")) {
		sscanf(url, "ES_ID=%d", &ES_ID);
	}
	/*URL setup*/
	else if (!read->es_ch && AMR_CanHandleURL(plug, url)) ES_ID = 2;

	switch (ES_ID) {
	case 1:
		read->od_ch = channel;
		e = GF_OK;
		break;
	case 2:
		read->es_ch = channel;
		e = GF_OK;
		break;
	}

exit:
	gf_term_on_connect(read->service, channel, e);
	return e;
}

static GF_Err AMR_DisconnectChannel(GF_InputService *plug, LPNETCHANNEL channel)
{
	AMR_Reader *read = plug->priv;

	GF_Err e = GF_STREAM_NOT_FOUND;
	if (read->es_ch == channel) {
		read->es_ch = NULL;
		if (read->es_data) free(read->es_data);
		read->es_data = NULL;
		e = GF_OK;
	} else if (read->od_ch == channel) {
		read->od_ch = NULL;
		e = GF_OK;
	}
	gf_term_on_disconnect(read->service, channel, e);
	return GF_OK;
}

static GF_Err AMR_ServiceCommand(GF_InputService *plug, GF_NetworkCommand *com)
{
	AMR_Reader *read = plug->priv;

	if (!com->base.on_channel) return GF_NOT_SUPPORTED;
	switch (com->command_type) {
	case GF_NET_CHAN_SET_PULL:
		return GF_OK;
	case GF_NET_CHAN_INTERACTIVE:
		return GF_OK;
	case GF_NET_CHAN_BUFFER:
		return GF_OK;
	case GF_NET_CHAN_SET_PADDING:
		read->pad_bytes = com->pad.padding_bytes;
		return GF_OK;
	case GF_NET_CHAN_DURATION:
		com->duration.duration = read->duration;
		com->duration.duration /= read->sample_rate;
		return GF_OK;
	case GF_NET_CHAN_PLAY:
		read->start_range = com->play.start_range;
		read->end_range = com->play.end_range;
		read->current_time = 0;
		if (read->stream) fseek(read->stream, read->start_offset, SEEK_SET);

		if (read->es_ch == com->base.on_channel) { 
			read->es_done = 0; 
			/*PLAY after complete download, estimate duration*/
			if (!read->is_remote && !read->duration) {
				AMR_ConfigureFromFile(read);
				if (read->duration) {
					GF_NetworkCommand rcfg;
					rcfg.base.on_channel = read->es_ch;
					rcfg.base.command_type = GF_NET_CHAN_DURATION;
					rcfg.duration.duration = read->duration;
					rcfg.duration.duration /= read->sample_rate;
					gf_term_on_command(read->service, &rcfg, GF_OK);
				}
			}
		}
		else if (read->od_ch == com->base.on_channel) { read->od_done = 0; }
		return GF_OK;
	case GF_NET_CHAN_STOP:
		return GF_OK;
	default:
		return GF_OK;
	}
}


static GF_Err AMR_ChannelGetSLP(GF_InputService *plug, LPNETCHANNEL channel, char **out_data_ptr, u32 *out_data_size, SLHeader *out_sl_hdr, Bool *sl_compressed, GF_Err *out_reception_status, Bool *is_new_data)
{
	u32 pos, start_from, i;
	u8 toc, ft;
	AMR_Reader *read = plug->priv;

	*out_reception_status = GF_OK;
	*sl_compressed = 0;
	*is_new_data = 0;

	memset(&read->sl_hdr, 0, sizeof(SLHeader));
	read->sl_hdr.randomAccessPointFlag = 1;
	read->sl_hdr.compositionTimeStampFlag = 1;

	if (read->od_ch == channel) {
		GF_ODCodec *codec;
		GF_ObjectDescriptor *od;
		GF_ODUpdate *odU;
		GF_ESD *esd;
		if (read->od_done) {
			*out_reception_status = GF_EOS;
			return GF_OK;
		}
		read->sl_hdr.compositionTimeStamp = (u64) (read->start_range * 1000);
		*out_sl_hdr = read->sl_hdr;
		if (!read->od_data) {
			*is_new_data = 1;
			odU = (GF_ODUpdate *) gf_odf_com_new(GF_ODF_OD_UPDATE_TAG);
			od = (GF_ObjectDescriptor *) gf_odf_desc_new(GF_ODF_OD_TAG);
			od->objectDescriptorID = 2;

			esd = AMR_GetESD(read);
			/*we signal start/end of units in live mode*/
			gf_list_add(od->ESDescriptors, esd);
			gf_list_add(odU->objectDescriptors, od);
			codec = gf_odf_codec_new();
			gf_odf_codec_add_com(codec, (GF_ODCom *)odU);
			gf_odf_codec_encode(codec);
			gf_odf_codec_get_au(codec, &read->od_data, &read->od_data_size);
			gf_odf_codec_del(codec);
		}
		*out_data_ptr = read->od_data;
		*out_data_size = read->od_data_size;
		return GF_OK;
	}

	if (read->es_ch != channel) return GF_STREAM_NOT_FOUND;

	/*fetching es data*/
	if (read->es_done) {
		*out_reception_status = GF_EOS;
		return GF_OK;
	}

	if (!read->es_data) {
		if (!read->stream) {
			*out_data_ptr = NULL;
			*out_data_size = 0;
			return GF_OK;
		}
		*is_new_data = 1;

fetch_next:
		pos = ftell(read->stream);

		toc = fgetc(read->stream);
		switch (read->mtype) {
		case GF_ISOM_SUBTYPE_3GP_AMR:
		case GF_ISOM_SUBTYPE_3GP_AMR_WB:
			ft = (ft >> 3) & 0x0F;
			read->es_data_size = (read->mtype==GF_ISOM_SUBTYPE_3GP_AMR_WB) ? GF_AMR_WB_FRAME_SIZE[ft] : GF_AMR_FRAME_SIZE[ft];
			break;
		default:
			for (i=0; i<GF_SMV_EVRC_RATE_TO_SIZE_NB; i++) {
				if (GF_SMV_EVRC_RATE_TO_SIZE[2*i]==ft) {
					/*remove rate_type byte*/
					read->es_data_size = GF_SMV_EVRC_RATE_TO_SIZE[2*i+1] - 1;
					break;
				}
			}
			break;
		}
		/*we're seeking*/
		if (read->start_range && read->duration) {
			start_from = (u32) (read->start_range * read->sample_rate);
			if (read->current_time + read->block_size < start_from) {
				read->current_time += read->block_size;
				fseek(read->stream, read->es_data_size, SEEK_CUR);
				goto fetch_next;
			} else {
				read->start_range = 0;
			}
		}
		
		read->es_data_size++;
		read->sl_hdr.compositionTimeStamp = read->current_time;
		read->es_data = malloc(sizeof(char) * (read->es_data_size+read->pad_bytes));
		read->es_data[0] = toc;
		if (read->es_data_size>1) fread(read->es_data + 1, read->es_data_size-1, 1, read->stream);
		if (read->pad_bytes) memset(read->es_data + read->es_data_size, 0, sizeof(char) * read->pad_bytes);
	}
	*out_sl_hdr = read->sl_hdr;
	*out_data_ptr = read->es_data;
	*out_data_size = read->es_data_size;
	return GF_OK;
}

static GF_Err AMR_ChannelReleaseSLP(GF_InputService *plug, LPNETCHANNEL channel)
{
	AMR_Reader *read = plug->priv;

	if (read->es_ch == channel) {
		if (!read->es_data) return GF_BAD_PARAM;
		free(read->es_data);
		read->es_data = NULL;
		read->current_time += read->block_size;
		return GF_OK;
	}
	if (read->od_ch == channel) {
		if (!read->od_data) return GF_BAD_PARAM;
		free(read->od_data);
		read->od_data = NULL;
		read->od_done = 1;
		return GF_OK;
	}
	return GF_OK;
}

GF_InputService *NewAESReader()
{
	AMR_Reader *reader;
	GF_InputService *plug = malloc(sizeof(GF_InputService));
	memset(plug, 0, sizeof(GF_InputService));
	GF_REGISTER_MODULE(plug, GF_NET_CLIENT_INTERFACE, "GPAC AMR/EVRC/SMV Reader", "gpac distribution", 0)

	plug->CanHandleURL = AMR_CanHandleURL;
	plug->ConnectService = AMR_ConnectService;
	plug->CloseService = AMR_CloseService;
	plug->GetServiceDescriptor = AMR_GetServiceDesc;
	plug->ConnectChannel = AMR_ConnectChannel;
	plug->DisconnectChannel = AMR_DisconnectChannel;
	plug->ServiceCommand = AMR_ServiceCommand;
	/*we do support pull mode*/
	plug->ChannelGetSLP = AMR_ChannelGetSLP;
	plug->ChannelReleaseSLP = AMR_ChannelReleaseSLP;

	reader = malloc(sizeof(AMR_Reader));
	memset(reader, 0, sizeof(AMR_Reader));
	plug->priv = reader;
	return plug;
}

void DeleteAESReader(void *ifce)
{
	GF_InputService *plug = (GF_InputService *) ifce;
	AMR_Reader *read = plug->priv;
	free(read);
	free(plug);
}

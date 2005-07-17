/*
 *			GPAC - Multimedia Framework C SDK
 *
 *			Copyright (c) Jean Le Feuvre 2000-2005
 *					All rights reserved
 *
 *  This file is part of GPAC / 3GPP/MPEG4 timed text module
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

#ifndef GPAC_READ_ONLY

#include <gpac/media_tools.h>

typedef struct
{
	GF_ClientService *service;
	Bool od_done;
	Bool needs_connection;
	u32 es_status, od_status;
	LPNETCHANNEL es_ch, od_ch;

	char *od_data;
	u32 od_data_size;

	SLHeader sl_hdr;

	GF_ISOFile *mp4;
	char *szFile;
	u32 tt_track;
	GF_ISOSample *samp;
	u32 samp_num;

	u32 start_range;
	/*file downloader*/
	GF_DownloadSession * dnload;
} TTIn;


static Bool TTIn_CanHandleURL(GF_InputService *plug, const char *url)
{
	char *sExt;
	sExt = strrchr(url, '.');
	if (!sExt) return 0;
	if (gf_term_check_extension(plug, "x-subtitle/srt", "srt", "SRT SubTitles", sExt)) return 1;
	if (gf_term_check_extension(plug, "x-subtitle/sub", "sub", "SUB SubTitles", sExt)) return 1;
	if (gf_term_check_extension(plug, "x-subtitle/ttxt", "ttxt", "3GPP TimedText", sExt)) return 1;
	return 0;
}

static Bool TTIn_is_local(const char *url)
{
	if (!strnicmp(url, "file://", 7)) return 1;
	if (strstr(url, "://")) return 0;
	return 1;
}

void tti_progress(GF_MediaImporter *ti, u32 cur_sample, u32 sample_count) {}
void tti_message(GF_MediaImporter *ti, GF_Err e, const char *message) {}


GF_Err TTIn_LoadFile(GF_InputService *plug, const char *url, Bool is_cache)
{
	GF_Err e;
	GF_MediaImporter import;

	char szFILE[GF_MAX_PATH];
	TTIn *tti = (TTIn *)plug->priv;
	const char *cache_dir = gf_modules_get_option((GF_BaseInterface *)plug, "General", "CacheDirectory");
	
	if (cache_dir && strlen(cache_dir)) {
		if (cache_dir[strlen(cache_dir)-1] != GF_PATH_SEPARATOR) {
			sprintf(szFILE, "%s%csrt_%d_mp4", cache_dir, GF_PATH_SEPARATOR, (u32) tti);
		} else {
			sprintf(szFILE, "%ssrt_%d_mp4", cache_dir, (u32) tti);
		}
	} else {
		sprintf(szFILE, "%d_temp_mp4", (u32) tti);
	}
	tti->mp4 = gf_isom_open(szFILE, GF_ISOM_OPEN_WRITE);
	if (!tti->mp4) return gf_isom_last_error(NULL);

	tti->szFile = strdup(szFILE);

	memset(&import, 0, sizeof(GF_MediaImporter));
	import.import_progress = tti_progress;
	import.import_message = tti_message;
	import.dest = tti->mp4;
	import.user_data = tti;
	/*override layout from sub file*/
	import.flags = GF_IMPORT_SKIT_TXT_BOX;
	import.in_name = (char *) url;
	
	e = gf_media_import(&import);
	if (!e) {
		tti->tt_track = 1;
		gf_isom_text_set_streaming_mode(tti->mp4, 1);
	}
	return e;
}

void TTIn_OnData(void *cbk, char *data, u32 size, u32 status, GF_Err e)
{
	const char *szCache;
	GF_InputService *plug = (GF_InputService *)cbk;
	TTIn *tti = (TTIn *) plug->priv;

	gf_term_download_update_stats(tti->dnload);

	/*wait to get the whole file*/
	if (e == GF_OK) return;
	else if (e==GF_EOS) {
		szCache = gf_dm_sess_get_cache_name(tti->dnload);
		if (!szCache) e = GF_IO_ERR;
		else {
			e = TTIn_LoadFile(plug, szCache, 1);
		}
	} 
	/*OK confirm*/
	if (tti->needs_connection) {
		tti->needs_connection = 0;
		gf_term_on_connect(tti->service, NULL, e);
	}
}

void TTIn_download_file(GF_InputService *plug, char *url)
{
	TTIn *tti = (TTIn *) plug->priv;

	tti->needs_connection = 1;
	tti->dnload = gf_term_download_new(tti->service, url, 0, TTIn_OnData, plug);
	if (!tti->dnload) {
		tti->needs_connection = 0;
		gf_term_on_connect(tti->service, NULL, GF_NOT_SUPPORTED);
	}
	/*service confirm is done once fetched*/
}

static GF_Err TTIn_ConnectService(GF_InputService *plug, GF_ClientService *serv, const char *url)
{
	GF_Err e;
	TTIn *tti = plug->priv;

	tti->service = serv;

	if (tti->dnload) gf_term_download_del(tti->dnload);
	tti->dnload = NULL;

	/*remote fetch*/
	if (!TTIn_is_local(url)) {
		TTIn_download_file(plug, (char *) url);
		return GF_OK;
	}
	e = TTIn_LoadFile(plug, url, 0);
	gf_term_on_connect(serv, NULL, e);
	return GF_OK;
}

static GF_Err TTIn_CloseService(GF_InputService *plug)
{
	TTIn *tti = plug->priv;
	if (tti->samp) gf_isom_sample_del(&tti->samp);
	if (tti->mp4) gf_isom_delete(tti->mp4);
	tti->mp4 = NULL;
	if (tti->szFile) {
		gf_delete_file(tti->szFile);
		free(tti->szFile);
		tti->szFile = NULL;
	}
	if (tti->dnload) gf_term_download_del(tti->dnload);
	tti->dnload = NULL;

	gf_term_on_disconnect(tti->service, NULL, GF_OK);
	return GF_OK;
}

static GF_Descriptor *TTIn_GetServiceDesc(GF_InputService *plug, u32 expect_type, const char *sub_url)
{
	GF_ESD *esd;
	TTIn *tti = plug->priv;
	GF_ObjectDescriptor *od = (GF_ObjectDescriptor *) gf_odf_desc_new(GF_ODF_OD_TAG);

	od->objectDescriptorID = 1;
	/*visual object*/
	if (expect_type==GF_MEDIA_OBJECT_TEXT) {
		esd = gp_media_map_esd(tti->mp4, tti->tt_track);
		gf_list_add(od->ESDescriptors, esd);
		esd->ESID = 2;
		return (GF_Descriptor *) od;
	}

	/*OD ESD*/
	esd = gf_odf_desc_esd_new(0);
	esd->slConfig->timestampResolution = 1000;
	esd->decoderConfig->streamType = GF_STREAM_OD;
	esd->decoderConfig->objectTypeIndication = GPAC_STATIC_OD_OTI;
	esd->ESID = 1;
	gf_list_add(od->ESDescriptors, esd);
	return (GF_Descriptor *) od;
}

static GF_Err TTIn_ConnectChannel(GF_InputService *plug, LPNETCHANNEL channel, const char *url, Bool upstream)
{
	u32 ES_ID;
	GF_Err e;
	TTIn *tti = plug->priv;

	e = GF_SERVICE_ERROR;
	if ((tti->es_ch==channel) || (tti->od_ch==channel)) goto exit;

	e = GF_OK;
	ES_ID = 0;
	if (strstr(url, "ES_ID")) sscanf(url, "ES_ID=%d", &ES_ID);

	switch (ES_ID) {
	case 1:
		tti->od_ch = channel;
		break;
	case 2:
		tti->es_ch = channel;
		break;
	default:
		e = GF_STREAM_NOT_FOUND;
		break;
	}

exit:
	gf_term_on_connect(tti->service, channel, e);
	return e;
}

static GF_Err TTIn_DisconnectChannel(GF_InputService *plug, LPNETCHANNEL channel)
{
	TTIn *tti = plug->priv;
	GF_Err e = GF_STREAM_NOT_FOUND;

	if (tti->es_ch == channel) {
		tti->es_ch = NULL;
		e = GF_OK;
	} else if (tti->od_ch == channel) {
		tti->od_ch = NULL;
		e = GF_OK;
	}
	gf_term_on_disconnect(tti->service, channel, e);
	return GF_OK;
}

static GF_Err TTIn_ServiceCommand(GF_InputService *plug, GF_NetworkCommand *com)
{
	TTIn *tti = plug->priv;

	if (!com->base.on_channel) return GF_NOT_SUPPORTED;
	switch (com->command_type) {
	case GF_NET_CHAN_SET_PADDING:
		gf_isom_set_sample_padding(tti->mp4, tti->tt_track, com->pad.padding_bytes);
		return GF_OK;
	case GF_NET_CHAN_DURATION:
		com->duration.duration = (Double) (s64) gf_isom_get_media_duration(tti->mp4, tti->tt_track);
		com->duration.duration /= gf_isom_get_media_timescale(tti->mp4, tti->tt_track);
		return GF_OK;
	case GF_NET_CHAN_PLAY:
		tti->start_range = (com->play.start_range>0) ? (u32) (com->play.start_range * 1000) : 0;
		if (tti->od_ch == com->base.on_channel) { tti->od_done = 0; }
		else if (tti->es_ch == com->base.on_channel) {
			tti->samp_num = 0;
			if (tti->samp) gf_isom_sample_del(&tti->samp);
		}
		return GF_OK;
	case GF_NET_CHAN_STOP:
		return GF_OK;
	default:
		return GF_OK;
	}
}


static GF_Err TTIn_ChannelGetSLP(GF_InputService *plug, LPNETCHANNEL channel, char **out_data_ptr, u32 *out_data_size, SLHeader *out_sl_hdr, Bool *sl_compressed, GF_Err *out_reception_status, Bool *is_new_data)
{
	TTIn *tti = plug->priv;

	*out_reception_status = GF_OK;
	*sl_compressed = 0;
	*is_new_data = 0;

	memset(&tti->sl_hdr, 0, sizeof(SLHeader));
	tti->sl_hdr.randomAccessPointFlag = 1;
	tti->sl_hdr.compositionTimeStampFlag = 1;
	tti->sl_hdr.accessUnitStartFlag = tti->sl_hdr.accessUnitEndFlag = 1;

	/*fetching es data*/
	if (tti->es_ch == channel) {
		if (tti->samp_num>=gf_isom_get_sample_count(tti->mp4, tti->tt_track)) {
			*out_reception_status = GF_EOS;
			return GF_OK;
		}

		if (!tti->samp) {
			u32 di;
			if (tti->start_range) {
				u32 di;
				*out_reception_status = gf_isom_get_sample_for_movie_time(tti->mp4, tti->tt_track, tti->start_range, &di, GF_ISOM_SEARCH_SYNC_BACKWARD, &tti->samp, &tti->samp_num);
				tti->start_range = 0;
			} else {
				tti->samp = gf_isom_get_sample(tti->mp4, tti->tt_track, tti->samp_num+1, &di);
			}
			if (!tti->samp) {
				*out_reception_status = GF_CORRUPTED_DATA;
				return GF_OK;
			}
			*is_new_data = 1;
		}
		tti->sl_hdr.compositionTimeStamp = tti->sl_hdr.decodingTimeStamp = tti->samp->DTS;
		*out_data_ptr = tti->samp->data;
		*out_data_size = tti->samp->dataLength;
		*out_sl_hdr = tti->sl_hdr;
		return GF_OK;
	}
	if (tti->od_ch == channel) {
		GF_ODCodec *codec;
		GF_ObjectDescriptor *od;
		GF_ODUpdate *odU;
		GF_ESD *esd;
		if (tti->od_done) {
			*out_reception_status = GF_EOS;
			return GF_OK;
		}
		if (!tti->od_data) {
			*is_new_data = 1;
			odU = (GF_ODUpdate *) gf_odf_com_new(GF_ODF_OD_UPDATE_TAG);
			od = (GF_ObjectDescriptor *) gf_odf_desc_new(GF_ODF_OD_TAG);
			od->objectDescriptorID = 2;
			esd = gp_media_map_esd(tti->mp4, tti->tt_track);
			esd->ESID = 2;
			esd->OCRESID = 1;
			gf_list_add(od->ESDescriptors, esd);
			gf_list_add(odU->objectDescriptors, od);
			codec = gf_odf_codec_new();
			gf_odf_codec_add_com(codec, (GF_ODCom *)odU);
			gf_odf_codec_encode(codec);
			gf_odf_codec_get_au(codec, &tti->od_data, &tti->od_data_size);
			gf_odf_codec_del(codec);
		}
		*out_data_ptr = tti->od_data;
		*out_data_size = tti->od_data_size;
		tti->sl_hdr.compositionTimeStamp = tti->sl_hdr.decodingTimeStamp = tti->start_range;
		*out_sl_hdr = tti->sl_hdr;
		return GF_OK;
	}
	return GF_STREAM_NOT_FOUND;
}

static GF_Err TTIn_ChannelReleaseSLP(GF_InputService *plug, LPNETCHANNEL channel)
{
	TTIn *tti = plug->priv;

	if (tti->es_ch == channel) {
		if (!tti->samp) return GF_BAD_PARAM;
		gf_isom_sample_del(&tti->samp);
		tti->samp = NULL;
		tti->samp_num++;
		return GF_OK;
	}
	if (tti->od_ch == channel) {
		if (!tti->od_data) return GF_BAD_PARAM;
		free(tti->od_data);
		tti->od_data = NULL;
		tti->od_done = 1;
		return GF_OK;
	}
	return GF_OK;
}


void *NewTTReader()
{
	TTIn *priv;
	GF_InputService *plug = malloc(sizeof(GF_InputService));
	memset(plug, 0, sizeof(GF_InputService));
	GF_REGISTER_MODULE_INTERFACE(plug, GF_NET_CLIENT_INTERFACE, "GPAC SubTitle Reader", "gpac distribution")

	plug->CanHandleURL = TTIn_CanHandleURL;
	plug->CanHandleURLInService = NULL;
	plug->ConnectService = TTIn_ConnectService;
	plug->CloseService = TTIn_CloseService;
	plug->GetServiceDescriptor = TTIn_GetServiceDesc;
	plug->ConnectChannel = TTIn_ConnectChannel;
	plug->DisconnectChannel = TTIn_DisconnectChannel;
	plug->ChannelGetSLP = TTIn_ChannelGetSLP;
	plug->ChannelReleaseSLP = TTIn_ChannelReleaseSLP;
	plug->ServiceCommand = TTIn_ServiceCommand;

	priv = malloc(sizeof(TTIn));
	memset(priv, 0, sizeof(TTIn));
	plug->priv = priv;
	return plug;
}

void DeleteTTReader(void *ifce)
{
	GF_InputService *plug = (GF_InputService *) ifce;
	TTIn *tti = plug->priv;
	free(tti);
	free(plug);
}

#endif

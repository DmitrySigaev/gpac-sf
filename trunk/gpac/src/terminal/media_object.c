/*
 *			GPAC - Multimedia Framework C SDK
 *
 *			Copyright (c) Jean Le Feuvre 2000-2005
 *					All rights reserved
 *
 *  This file is part of GPAC / Media terminal sub-project
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


#include <gpac/internal/terminal_dev.h>
#include <gpac/internal/compositor_dev.h>
#include <gpac/internal/scenegraph_dev.h>
#include <gpac/modules/codec.h>
#include <gpac/nodes_x3d.h>
#include "media_memory.h"
#include "media_control.h"
#include <gpac/nodes_svg.h>


static GF_MediaObject *get_sync_reference(GF_Scene *scene, XMLRI *iri, u32 o_type, GF_Node *orig_ref, Bool *post_pone)
{
	MFURL mfurl;
	SFURL sfurl;
	GF_MediaObject *res;
	GF_Node *ref = NULL;

	u32 stream_id = 0;
	if (iri->type==XMLRI_STREAMID) {
		stream_id = iri->lsr_stream_id;
	} else if (!iri->string) {
		return NULL;
	} else {
		if (iri->target) ref = iri->target;
		else if (iri->string[0]=='#') ref = gf_sg_find_node_by_name(scene->graph, iri->string+1);
		else ref = gf_sg_find_node_by_name(scene->graph, iri->string);

		if (ref) {
#ifndef GPAC_DISABLE_SVG
			GF_FieldInfo info;
#endif
			/*safety check, break cyclic references*/
			if (ref==orig_ref) return NULL;

			switch (ref->sgprivate->tag) {
#ifndef GPAC_DISABLE_SVG
			case TAG_SVG_audio:
				o_type = GF_MEDIA_OBJECT_AUDIO; 
				if (gf_node_get_attribute_by_tag(ref, TAG_XLINK_ATT_href, 0, 0, &info)==GF_OK) {
					return get_sync_reference(scene, info.far_ptr, o_type, orig_ref ? orig_ref : ref, post_pone);
				}
				return NULL;
			case TAG_SVG_video:
				o_type = GF_MEDIA_OBJECT_VIDEO; 
				if (gf_node_get_attribute_by_tag(ref, TAG_XLINK_ATT_href, 0, 0, &info)==GF_OK) {
					return get_sync_reference(scene, info.far_ptr, o_type, orig_ref ? orig_ref : ref, post_pone);
				}
				return NULL;
#endif
			default:
				return NULL;
			}
		}
	}
	*post_pone = 0;
	mfurl.count = 1;
	mfurl.vals = &sfurl;
	mfurl.vals[0].OD_ID = stream_id;
	mfurl.vals[0].url = iri->string;

	res = gf_scene_get_media_object(scene, &mfurl, o_type, 0);
	if (!res) *post_pone = 1;
	return res;
}

GF_EXPORT
GF_MediaObject *gf_mo_register(GF_Node *node, MFURL *url, Bool lock_timelines, Bool force_new_res)
{
	u32 obj_type;
#ifndef GPAC_DISABLE_SVG
	Bool post_pone;
	GF_FieldInfo info;
#endif
	GF_Scene *scene;
	GF_MediaObject *res, *syncRef;
	GF_SceneGraph *sg = gf_node_get_graph(node);
	if (!sg) return NULL;
	scene = (GF_Scene*)gf_sg_get_private(sg);
	if (!scene) return NULL;

	syncRef = NULL;

	/*keep track of the kind of object expected if URL is not using OD scheme*/
	switch (gf_node_get_tag(node)) {
#ifndef GPAC_DISABLE_VRML
	/*MPEG-4 / VRML / X3D only*/
	case TAG_MPEG4_AudioClip: 
	case TAG_MPEG4_AudioSource: 
#ifndef GPAC_DISABLE_X3D
	case TAG_X3D_AudioClip: 
#endif
		obj_type = GF_MEDIA_OBJECT_AUDIO; 
		break;
	case TAG_MPEG4_SBVCAnimation: 
	case TAG_MPEG4_AnimationStream: 
		obj_type = GF_MEDIA_OBJECT_UPDATES; 
		break;
	case TAG_MPEG4_BitWrapper:
		obj_type = GF_MEDIA_OBJECT_SCENE;
		break;
	case TAG_MPEG4_InputSensor: 
		obj_type = GF_MEDIA_OBJECT_INTERACT; 
		break;
	case TAG_MPEG4_Background2D: 
	case TAG_MPEG4_Background: 
	case TAG_MPEG4_ImageTexture:
	case TAG_MPEG4_CacheTexture:
	case TAG_MPEG4_MovieTexture: 
#ifndef GPAC_DISABLE_X3D
	case TAG_X3D_Background: 
	case TAG_X3D_ImageTexture:
	case TAG_X3D_MovieTexture:
#endif
		obj_type = GF_MEDIA_OBJECT_VIDEO; 
		break;
	case TAG_MPEG4_Inline: 
#ifndef GPAC_DISABLE_X3D
	case TAG_X3D_Inline: 
#endif
		obj_type = GF_MEDIA_OBJECT_SCENE; 
		break;
#endif /*GPAC_DISABLE_VRML*/

	/*SVG*/
#ifndef GPAC_DISABLE_SVG
	case TAG_SVG_audio: 
		obj_type = GF_MEDIA_OBJECT_AUDIO; 
		if (gf_node_get_attribute_by_tag(node, TAG_SVG_ATT_syncReference, 0, 0, &info)==GF_OK) {
			syncRef = get_sync_reference(scene, info.far_ptr, GF_MEDIA_OBJECT_UNDEF, node, &post_pone);
			/*syncRef is specified but doesn't exist yet, post-pone*/
			if (post_pone) return NULL;
		}
		break;
	case TAG_SVG_video: 
		obj_type = GF_MEDIA_OBJECT_VIDEO; 
		if (gf_node_get_attribute_by_tag(node, TAG_SVG_ATT_syncReference, 0, 0, &info)==GF_OK) {
			syncRef = get_sync_reference(scene, info.far_ptr, GF_MEDIA_OBJECT_UNDEF, node, &post_pone);
			/*syncRef is specified but doesn't exist yet, post-pone*/
			if (post_pone) return NULL;
		}
		break;
	case TAG_SVG_image: 
		obj_type = GF_MEDIA_OBJECT_VIDEO; 
		break;
	case TAG_SVG_foreignObject: 
	case TAG_SVG_animation: 
		obj_type = GF_MEDIA_OBJECT_SCENE; 
		break;
	case TAG_LSR_updates: 
		obj_type = GF_MEDIA_OBJECT_UPDATES; 
		break;
#endif

	default: obj_type = GF_MEDIA_OBJECT_UNDEF; break;
	}

	/*move to primary resource handler*/
	while (scene->secondary_resource && scene->root_od->parentscene)
		scene = scene->root_od->parentscene;

	res = gf_scene_get_media_object_ex(scene, url, obj_type, lock_timelines, syncRef, force_new_res, node);
	return res;
}


void gf_mo_unregister(GF_Node *node, GF_MediaObject *mo)
{
	if (mo && node) {
		gf_list_del_item(mo->nodes, node);
	}
}

GF_MediaObject *gf_mo_new()
{
	GF_MediaObject *mo;
	mo = (GF_MediaObject *) gf_malloc(sizeof(GF_MediaObject));
	memset(mo, 0, sizeof(GF_MediaObject));
	mo->speed = FIX_ONE;
	mo->URLs.count = 0;
	mo->URLs.vals = NULL;
	mo->nodes = gf_list_new();
	return mo;
}


GF_EXPORT
Bool gf_mo_get_visual_info(GF_MediaObject *mo, u32 *width, u32 *height, u32 *stride, u32 *pixel_ar, u32 *pixelFormat)
{
	GF_CodecCapability cap;
	if ((mo->type != GF_MEDIA_OBJECT_VIDEO) && (mo->type!=GF_MEDIA_OBJECT_TEXT)) return 0;

	if (width) {
		cap.CapCode = GF_CODEC_WIDTH;
		gf_codec_get_capability(mo->odm->codec, &cap);
		*width = cap.cap.valueInt;
	}
	if (height) {
		cap.CapCode = GF_CODEC_HEIGHT;
		gf_codec_get_capability(mo->odm->codec, &cap);
		*height = cap.cap.valueInt;
	}
	if (mo->type==GF_MEDIA_OBJECT_TEXT) return 1;

	if (stride) {
		cap.CapCode = GF_CODEC_STRIDE;
		gf_codec_get_capability(mo->odm->codec, &cap);
		*stride = cap.cap.valueInt;
	}
	if (pixelFormat) {
		cap.CapCode = GF_CODEC_PIXEL_FORMAT;
		gf_codec_get_capability(mo->odm->codec, &cap);
		*pixelFormat = cap.cap.valueInt;

		if (mo->odm && mo->odm->parentscene->is_dynamic_scene) {
			const char *name = gf_node_get_name(gf_list_get(mo->nodes, 0));
			if (name && !strcmp(name, "DYN_VIDEO")) {
				const char *opt;
				u32 r, g, b, a;
				M_Background2D *back = (M_Background2D *) gf_sg_find_node_by_name(mo->odm->parentscene->graph, "DYN_BACK");
				if (back) {
					switch (cap.cap.valueInt) {
					case GF_PIXEL_ARGB:
					case GF_PIXEL_RGBA:
					case GF_PIXEL_YUVA:
						opt = gf_cfg_get_key(mo->odm->term->user->config, "Compositor", "BackColor");
						if (!opt) {
							gf_cfg_set_key(mo->odm->term->user->config, "Compositor", "BackColor", "FF999999");
							opt = "FF999999";
						}
						sscanf(opt, "%02X%02X%02X%02X", &a, &r, &g, &b);
						back->backColor.red = INT2FIX(r)/255;
						back->backColor.green = INT2FIX(g)/255;
						back->backColor.blue = INT2FIX(b)/255;
						break;
					default:
						back->backColor.red = back->backColor.green = back->backColor.blue = FIX_ONE;
						break;
					}
					gf_node_dirty_set((GF_Node *)back, 0, 1);
				}
			}
		}
	}
	/*get PAR settings*/
	if (pixel_ar) {
		cap.CapCode = GF_CODEC_PAR;
		gf_codec_get_capability(mo->odm->codec, &cap);
		*pixel_ar = cap.cap.valueInt;
		if (! (*pixel_ar & 0x0000FFFF)) *pixel_ar = 0;
		if (! (*pixel_ar & 0xFFFF0000)) *pixel_ar = 0;

		/**/
		if (! *pixel_ar) {
			GF_Channel *ch;
			GF_NetworkCommand com;
			com.base.command_type = GF_NET_CHAN_GET_PIXEL_AR;
			ch = gf_list_get(mo->odm->channels, 0);
			if (!ch) return 0;

			com.base.on_channel = ch;
			com.par.hSpacing = com.par.vSpacing = 0;
			if (gf_term_service_command(ch->service, &com) == GF_OK) {
				if ((com.par.hSpacing>65535) || (com.par.vSpacing>65535)) {
					com.par.hSpacing>>=16;
					com.par.vSpacing>>=16;
				}
				if (com.par.hSpacing|| com.par.vSpacing)
					*pixel_ar = (com.par.hSpacing<<16) | com.par.vSpacing;
			}
		}
	}
	return 1;
}

GF_EXPORT
Bool gf_mo_get_audio_info(GF_MediaObject *mo, u32 *sample_rate, u32 *bits_per_sample, u32 *num_channels, u32 *channel_config)
{
	GF_CodecCapability cap;
	if (!mo->odm || !mo->odm->codec || (mo->type != GF_MEDIA_OBJECT_AUDIO)) return 0;

	if (sample_rate) {
		cap.CapCode = GF_CODEC_SAMPLERATE;
		gf_codec_get_capability(mo->odm->codec, &cap);
		*sample_rate = cap.cap.valueInt;
	}
	if (num_channels) {
		cap.CapCode = GF_CODEC_NB_CHAN;
		gf_codec_get_capability(mo->odm->codec, &cap);
		*num_channels = cap.cap.valueInt;
	}
	if (bits_per_sample) {
		cap.CapCode = GF_CODEC_BITS_PER_SAMPLE;
		gf_codec_get_capability(mo->odm->codec, &cap);
		*bits_per_sample = cap.cap.valueInt;
	}
	if (channel_config) {
		cap.CapCode = GF_CODEC_CHANNEL_CONFIG;
		gf_codec_get_capability(mo->odm->codec, &cap);
		*channel_config = cap.cap.valueInt;
	}
	return 1;
}

void gf_mo_update_caps(GF_MediaObject *mo)
{
	GF_CodecCapability cap;

	mo->flags &= ~GF_MO_IS_INIT;

	if (mo->type == GF_MEDIA_OBJECT_VIDEO) {
		cap.CapCode = GF_CODEC_FPS;
		gf_codec_get_capability(mo->odm->codec, &cap);
		mo->odm->codec->fps = cap.cap.valueFloat;
	}
	else if (mo->type == GF_MEDIA_OBJECT_AUDIO) {
		u32 sr, nb_ch, bps;
		sr = nb_ch = bps = 0;
		gf_mo_get_audio_info(mo, &sr, &bps, &nb_ch, NULL);
		mo->odm->codec->bytes_per_sec = sr * nb_ch * bps / 8;
	}
}

GF_EXPORT
char *gf_mo_fetch_data(GF_MediaObject *mo, Bool resync, Bool *eos, u32 *timestamp, u32 *size)
{
	Bool force_decode = 0;
	u32 obj_time;
	GF_CMUnit *CU;
	*eos = 0;

	if (!gf_odm_lock_mo(mo)) return NULL;

	if (!mo->odm->codec || !mo->odm->codec->CB) {
		gf_odm_lock(mo->odm, 0);
		return NULL;
	}

	/*if frame locked return it*/
	if (mo->nb_fetch) {
		*eos = 0;
		*timestamp = mo->timestamp;
		*size = mo->framesize;
		mo->nb_fetch ++;
		gf_odm_lock(mo->odm, 0);
		return mo->frame;
	}

	/*end of stream */
	*eos = gf_cm_is_eos(mo->odm->codec->CB);

	/*not running and no resync (ie audio)*/
	if (!resync && !gf_cm_is_running(mo->odm->codec->CB)) {
		gf_odm_lock(mo->odm, 0);
		return NULL;
	}
	if (! *eos && (mo->odm->codec->ck->speed > FIX_ONE))
		force_decode = 1;

	if (force_decode) {
		gf_odm_lock(mo->odm, 0);
		if (gf_term_lock_codec(mo->odm->codec, 1)) {
			gf_codec_process(mo->odm->codec, 1);
			gf_term_lock_codec(mo->odm->codec, 0);
		}
		if (!gf_odm_lock_mo(mo)) return NULL;
	}

	/*new frame to fetch, lock*/
	CU = gf_cm_get_output(mo->odm->codec->CB);
	/*no output*/
	if (!CU || (CU->RenderedLength == CU->dataLength)) {
		gf_odm_lock(mo->odm, 0);
		return NULL;
	}

	/*note this assert is NOT true when recomputing DTS from CTS on the fly (MPEG1/2 RTP and H264/AVC RTP)*/
	//assert(CU->TS >= mo->odm->codec->CB->LastRenderedTS);

	if (mo->odm->codec->CB->UnitCount==1) resync = 0;

	/*resync*/
	if (resync) {
		u32 nb_droped = 0;
		obj_time = gf_clock_time(mo->odm->codec->ck);
		while (CU->TS < obj_time) {
			if (!CU->next->dataLength) {
				if (force_decode) {
					obj_time = gf_clock_time(mo->odm->codec->ck);
					gf_odm_lock(mo->odm, 0);
					if (gf_term_lock_codec(mo->odm->codec, 1)) {
						gf_codec_process(mo->odm->codec, 1);
						gf_term_lock_codec(mo->odm->codec, 0);
					}
					gf_odm_lock(mo->odm, 1);
					if (!CU->next->dataLength) 
						break;
				} else {
					break;
				}
			}
			/*figure out closest time*/
			if (CU->next->TS > obj_time) {
				*eos = 0;
				break;
			}
			nb_droped ++;
			if (nb_droped>1) {
				GF_LOG(GF_LOG_INFO, GF_LOG_MEDIA, ("[ODM%d] At OTB %d dropped frame TS %d\n", mo->odm->OD->objectDescriptorID, obj_time, CU->TS));
				mo->odm->codec->nb_droped++;
			}
			/*discard*/
			CU->RenderedLength = CU->dataLength = 0;
			gf_cm_drop_output(mo->odm->codec->CB);

			/*get next*/
			CU = gf_cm_get_output(mo->odm->codec->CB);
			*eos = gf_cm_is_eos(mo->odm->codec->CB);
		}
	}	

	mo->framesize = CU->dataLength - CU->RenderedLength;
	mo->frame = CU->data + CU->RenderedLength;
	if (mo->timestamp != CU->TS) {
#ifndef GPAC_DISABLE_VRML
		mediasensor_update_timing(mo->odm, mo->odm->codec->CB->HasSeenEOS);
#endif
	
		if (mo->odm->parentscene->is_dynamic_scene)
			mo->odm->parentscene->root_od->current_time = mo->odm->current_time;

		mo->timestamp = CU->TS;
		GF_LOG(GF_LOG_DEBUG, GF_LOG_MEDIA, ("[ODM%d] At OTB %d fetch frame TS %d size %d - %d unit in CB\n", mo->odm->OD->objectDescriptorID, gf_clock_time(mo->odm->codec->ck), mo->timestamp, mo->framesize, mo->odm->codec->CB->UnitCount));
		/*signal EOS after rendering last frame, not while rendering it*/
		*eos = 0;
	}

	/*also adjust CU time based on consummed bytes in input, since some codecs output very large audio chunks*/
	if (mo->odm->codec->bytes_per_sec) mo->timestamp += CU->RenderedLength * 1000 / mo->odm->codec->bytes_per_sec;

	mo->nb_fetch ++;
	*timestamp = mo->timestamp;
	*size = mo->framesize;

	gf_odm_lock(mo->odm, 0);
	return mo->frame;
}

GF_EXPORT
void gf_mo_release_data(GF_MediaObject *mo, u32 nb_bytes, s32 forceDrop)
{
#if 0
	u32 obj_time;
#endif
	if (!gf_odm_lock_mo(mo)) return;

	if (!mo->nb_fetch || !mo->odm->codec) {
		gf_odm_lock(mo->odm, 0);
		return;
	}
	mo->nb_fetch--;
	if (mo->nb_fetch) {
		gf_odm_lock(mo->odm, 0);
		return;
	}
	if (mo->odm->codec->CB->no_allocation)
		forceDrop = 1;

	/*perform a sanity check on TS since the CB may have changed status - this may happen in 
	temporal scalability only*/
	if (mo->odm->codec->CB->output->dataLength ) {
		if (nb_bytes==0xFFFFFFFF) {
			mo->odm->codec->CB->output->RenderedLength = mo->odm->codec->CB->output->dataLength;
		} else {
			assert(mo->odm->codec->CB->output->RenderedLength + nb_bytes <= mo->odm->codec->CB->output->dataLength);
			mo->odm->codec->CB->output->RenderedLength += nb_bytes;
		}

		if (forceDrop<0) {
			/*only allow for explicit last frame keeping if only one node is using the resource
			otherwise this would block the composition memory*/
			if (mo->num_open>1) forceDrop=0;
			else {
				gf_odm_lock(mo->odm, 0);
				return;
			}
		}

		/*discard frame*/
		if (mo->odm->codec->CB->output->RenderedLength == mo->odm->codec->CB->output->dataLength) {
			if (forceDrop) {
				gf_cm_drop_output(mo->odm->codec->CB);
				forceDrop--;
//				if (forceDrop) mo->odm->codec->nb_droped++;
			} else {
				/*we cannot drop since we don't know the speed of the playback (which can even be frame by frame)*/
#if 0
				obj_time = gf_clock_time(mo->odm->codec->ck);
				if (mo->odm->codec->CB->output->next->dataLength) { 
					if (2*obj_time < mo->timestamp + mo->odm->codec->CB->output->next->TS ) {
						mo->odm->codec->CB->output->RenderedLength = 0;
					} else {
						gf_cm_drop_output(mo->odm->codec->CB);
					}
				} else {
					gf_cm_drop_output(mo->odm->codec->CB);
				}
#else
				mo->odm->codec->CB->output->RenderedLength = 0;
#endif
			}
		}
	}
	gf_odm_lock(mo->odm, 0);
}

GF_EXPORT
void gf_mo_get_object_time(GF_MediaObject *mo, u32 *obj_time)
{
	if (!gf_odm_lock_mo(mo)) return;

	/*regular media codec...*/
	if (mo->odm->codec) {
		/*get absolute clock (without drift) for audio*/
		if (mo->odm->codec->type==GF_STREAM_AUDIO)  
			*obj_time = gf_clock_real_time(mo->odm->codec->ck);
		else
			*obj_time = gf_clock_time(mo->odm->codec->ck);
	}
	/*BIFS object */
	else if (mo->odm->subscene && mo->odm->subscene->scene_codec) {
		*obj_time = gf_clock_time(mo->odm->subscene->scene_codec->ck);
	} 
	/*unknown / unsupported object*/
	else {
		*obj_time = 0;
	}
	gf_odm_lock(mo->odm, 0);
}


GF_EXPORT
void gf_mo_play(GF_MediaObject *mo, Double clipBegin, Double clipEnd, Bool can_loop)
{
	if (!mo) return;

	if (!mo->num_open && mo->odm) {
		s32 res;
		Bool is_restart = 0;

		/*remove object from media queue*/
		gf_term_lock_media_queue(mo->odm->term, 1);
		res = gf_list_del_item(mo->odm->term->media_queue, mo->odm);
		gf_term_lock_media_queue(mo->odm->term, 0);

		if (mo->odm->action_type!=GF_ODM_ACTION_PLAY) {
			mo->odm->action_type = GF_ODM_ACTION_PLAY;
			is_restart = 0;
			res = -1;
		}

		if (mo->odm->flags & GF_ODM_NO_TIME_CTRL) {
			mo->odm->media_start_time = 0;
		} else {
			mo->odm->media_start_time = (u64) (clipBegin*1000);
			if (mo->odm->duration && (mo->odm->media_start_time > mo->odm->duration)) {
				if (can_loop) {
					mo->odm->media_start_time %= mo->odm->duration;
				} else {
					mo->odm->media_start_time = mo->odm->duration;
				}
			}
			if (clipEnd>=clipBegin) {
				mo->odm->media_stop_time = (u64) (clipEnd*1000);
				if (mo->odm->duration && (mo->odm->media_stop_time > mo->odm->duration)) {
					mo->odm->media_stop_time = 0;
				}
			} else {
				mo->odm->media_stop_time = 0;
			}
		}
		/*done prefetching*/
		mo->odm->flags &= ~GF_ODM_PREFETCH;

		if (is_restart) {
			mediacontrol_restart(mo->odm);
		} else {
			/*FIXME - this breaks inital loading on JPEG and PNG files ...*/
//			if (mo->odm->subscene && mo->odm->subscene->is_dynamic_scene) mo->odm->flags |= GF_ODM_REGENERATE_SCENE;

			gf_odm_start(mo->odm, (res>=0) ? 1 : 0);
		}
	} else if (mo->odm) {
		if (mo->num_to_restart) mo->num_restart--;
		if (!mo->num_restart && (mo->num_to_restart==mo->num_open+1) ) {
			mediacontrol_restart(mo->odm);
			mo->num_to_restart = mo->num_restart = 0;
		}
	}
	mo->num_open++;
}

GF_EXPORT
Bool gf_mo_stop(GF_MediaObject *mo)
{
	Bool ret = 0;
	if (!mo || !mo->num_open) return 0;

	mo->num_open--;
	if (!mo->num_open && mo->odm) {
		if (mo->odm->flags & GF_ODM_DESTROYED) return 1;

		/*do not stop directly, this can delete channel data currently being decoded (BIFS anim & co)*/
		gf_term_lock_media_queue(mo->odm->term, 1);
		/*if object not in media queue, add it*/
		if (gf_list_find(mo->odm->term->media_queue, mo->odm)<0) {
			gf_list_add(mo->odm->term->media_queue, mo->odm);
		}
		
		/*signal STOP request*/
		if ((mo->OD_ID==GF_MEDIA_EXTERNAL_ID) || (mo->odm && mo->odm->OD && (mo->odm->OD->objectDescriptorID==GF_MEDIA_EXTERNAL_ID))) {
			mo->odm->action_type = GF_ODM_ACTION_DELETE;
			ret = 1;
		}
		else 
			mo->odm->action_type = GF_ODM_ACTION_STOP;

		gf_term_lock_media_queue(mo->odm->term, 0);
	} else {
		if (!mo->num_to_restart) {
			mo->num_restart = mo->num_to_restart = mo->num_open + 1;
		}
	}
	return ret;
}

GF_EXPORT
void gf_mo_restart(GF_MediaObject *mo)
{
	void *mediactrl_stack = NULL;
	if (!gf_odm_lock_mo(mo)) return;

#ifndef GPAC_DISABLE_VRML
	mediactrl_stack = gf_odm_get_mediacontrol(mo->odm);
#endif
	/*if no control and not root of a scene, check timelines are unlocked*/
	if (!mediactrl_stack && !mo->odm->subscene) {
		/*don't restart if sharing parent scene clock*/
		if (gf_odm_shares_clock(mo->odm, gf_odm_get_media_clock(mo->odm->parentscene->root_od))) {
			gf_odm_lock(mo->odm, 0);
			return;
		}
	}
	/*all other cases, call restart to take into account clock references*/
	mediacontrol_restart(mo->odm);
	gf_odm_lock(mo->odm, 0);
}

u32 gf_mo_get_od_id(MFURL *url)
{
	u32 i, j, tmpid;
	char *str, *s_url;
	u32 id = 0;

	if (!url) return 0;
	
	for (i=0; i<url->count; i++) {
		if (url->vals[i].OD_ID) {
			/*works because OD ID 0 is forbidden in MPEG4*/
			if (!id) {
				id = url->vals[i].OD_ID;
			}
			/*bad url, only one object can be described in MPEG4 urls*/
			else if (id != url->vals[i].OD_ID) return 0;
		} else if (url->vals[i].url && strlen(url->vals[i].url)) {
			/*format: od:ID or od:ID#segment - also check for "ID" in case...*/
			str = url->vals[i].url;
			if (!strnicmp(str, "od:", 3)) str += 3;
			/*remove segment info*/
			s_url = gf_strdup(str);
			j = 0;
			while (j<strlen(s_url)) {
				if (s_url[j]=='#') {
					s_url[j] = 0;
					break;
				}
				j++;
			}
			j = sscanf(s_url, "%u", &tmpid);
			/*be carefull, an url like "11-regression-test.mp4" will return 1 on sscanf :)*/
			if (j==1) {
				char szURL[20];
				sprintf(szURL, "%u", tmpid);
				if (stricmp(szURL, s_url)) j = 0;
			}
			gf_free(s_url);

			if (j!= 1) {
				/*dynamic OD if only one URL specified*/
				if (!i) return GF_MEDIA_EXTERNAL_ID;
				/*otherwise ignore*/
				continue;
			}
			if (!id) {
				id = tmpid;
				continue;
			}
			/*bad url, only one object can be described in MPEG4 urls*/
			else if (id != tmpid) return 0;
		}
	}
	return id;
}


Bool gf_mo_is_same_url(GF_MediaObject *obj, MFURL *an_url, Bool *keep_fragment, u32 obj_hint_type)
{
	Bool include_sub_url = 0;
	u32 i;
	char szURL1[GF_MAX_PATH], szURL2[GF_MAX_PATH], *ext;

	if (!obj->URLs.count) {
		if (!obj->odm) return 0;
		strcpy(szURL1, obj->odm->net_service->url);
	} else {
		strcpy(szURL1, obj->URLs.vals[0].url);
	}

	/*don't analyse audio/video to locate segments or viewports*/
	if ((obj->type==GF_MEDIA_OBJECT_AUDIO) || (obj->type==GF_MEDIA_OBJECT_VIDEO)) {
		if (keep_fragment) *keep_fragment = 0;
		include_sub_url = 1;
	} else if ((obj->type==GF_MEDIA_OBJECT_SCENE) && keep_fragment && obj->odm) {
		GF_ClientService *ns;
		u32 j;
		/*for remoteODs/dynamic ODs, check if one of the running service cannot be used*/
		for (i=0; i<an_url->count; i++) {
			char *frag = strrchr(an_url->vals[i].url, '#');
			j=0;
			/*this is the same object (may need some refinement)*/
			if (!stricmp(szURL1, an_url->vals[i].url)) return 1;

			/*fragment is a media segment, same URL*/
			if (frag ) {
				Bool same_res = 0;
				frag[0] = 0;
				same_res = !strncmp(an_url->vals[i].url, szURL1, strlen(an_url->vals[i].url)) ? 1 : 0;
				frag[0] = '#';

				/*if we're talking about the same resource, check if the fragment can be matched*/
				if (same_res) {
					/*if the fragment is a node which can be found, this is the same resource*/
					if (obj->odm->subscene && (gf_sg_find_node_by_name(obj->odm->subscene->graph, frag+1)!=NULL) )
						return 1;
				
					/*if the expected type is an existing segment (undefined media type), this is the same resource*/
					if (!obj_hint_type && gf_odm_find_segment(obj->odm, frag+1))
						return 1;
				}
			}

			while ( (ns = (GF_ClientService*)gf_list_enum(obj->odm->term->net_services, &j)) ) {
				/*sub-service of an existing service - don't touch any fragment*/
				if (gf_term_service_can_handle_url(ns, an_url->vals[i].url)) {
					*keep_fragment = 1;
					return 0;
				}
			}
		}
	}

	/*check on full URL without removing fragment IDs*/
	if (include_sub_url) {
		for (i=0; i<an_url->count; i++) {
			if (an_url->vals[i].url && !stricmp(szURL1, an_url->vals[i].url)) return 1;
		}
		/*not same resource, we will have to check fragment as URL might point to a sub-service or single stream of a mux*/
		if (keep_fragment) *keep_fragment = 1;
		return 0;
	}
	ext = strrchr(szURL1, '#');
	if (ext) ext[0] = 0;
	for (i=0; i<an_url->count; i++) {
		if (!an_url->vals[i].url) return 0;
		strcpy(szURL2, an_url->vals[i].url);
		ext = strrchr(szURL2, '#');
		if (ext) ext[0] = 0;
		if (!stricmp(szURL1, szURL2)) return 1;
	}
	return 0;
}

GF_EXPORT
Bool gf_mo_url_changed(GF_MediaObject *mo, MFURL *url)
{
	u32 od_id;
	Bool ret = 0;
	if (!mo) return (url ? 1 : 0);
	od_id = gf_mo_get_od_id(url);
	if ( (mo->OD_ID == GF_MEDIA_EXTERNAL_ID) && (od_id == GF_MEDIA_EXTERNAL_ID)) {
		ret = !gf_mo_is_same_url(mo, url, NULL, 0);
	} else {
		ret = (mo->OD_ID == od_id) ? 0 : 1;
	}
	/*special case for 3GPP text: if not playing and user node changed, force removing it*/
	if (ret && mo->odm && !mo->num_open && (mo->type == GF_MEDIA_OBJECT_TEXT)) {
		mo->flags |= GF_MO_DISPLAY_REMOVE;
		gf_term_stop_codec(mo->odm->codec);
	}
	return ret;
}

GF_EXPORT
void gf_mo_pause(GF_MediaObject *mo)
{
#ifndef GPAC_DISABLE_VRML
	if (!mo || !mo->num_open || !mo->odm) return;
	mediacontrol_pause(mo->odm);
#endif
}

GF_EXPORT
void gf_mo_resume(GF_MediaObject *mo)
{
#ifndef GPAC_DISABLE_VRML
	if (!mo || !mo->num_open || !mo->odm) return;
	mediacontrol_resume(mo->odm);
#endif
}

GF_EXPORT
void gf_mo_set_speed(GF_MediaObject *mo, Fixed speed)
{
#ifndef GPAC_DISABLE_VRML
	MediaControlStack *ctrl;
#endif

	if (!mo) return;
	if (!mo->odm) {
		mo->speed = speed;
		return;
	}
#ifndef GPAC_DISABLE_VRML
	/*if media control forbidd that*/
	ctrl = gf_odm_get_mediacontrol(mo->odm);
	if (ctrl) return;
#endif
	gf_odm_set_speed(mo->odm, speed);
}

GF_EXPORT
Fixed gf_mo_get_current_speed(GF_MediaObject *mo)
{
	return (mo && mo->odm && mo->odm->codec && mo->odm->codec->ck) ? mo->odm->codec->ck->speed : FIX_ONE;
}


GF_EXPORT
Fixed gf_mo_get_speed(GF_MediaObject *mo, Fixed in_speed)
{
	Fixed res = in_speed;

#ifndef GPAC_DISABLE_VRML
	MediaControlStack *ctrl;

	if (!gf_odm_lock_mo(mo)) return in_speed;

	/*get control*/
	ctrl = gf_odm_get_mediacontrol(mo->odm);
	if (ctrl) res = ctrl->control->mediaSpeed;

	gf_odm_lock(mo->odm, 0);
#endif

	return res;
}

GF_EXPORT
Bool gf_mo_get_loop(GF_MediaObject *mo, Bool in_loop)
{
	GF_Clock *ck;
#ifndef GPAC_DISABLE_VRML
	MediaControlStack *ctrl;
#endif
	if (!gf_odm_lock_mo(mo)) return in_loop;
	
	/*get control*/
#ifndef GPAC_DISABLE_VRML
	ctrl = gf_odm_get_mediacontrol(mo->odm);
	if (ctrl) in_loop = ctrl->control->loop;
#endif

	/*otherwise looping is only accepted if not sharing parent scene clock*/
	ck = gf_odm_get_media_clock(mo->odm->parentscene->root_od);
	if (gf_odm_shares_clock(mo->odm, ck)) {
		in_loop = 0;
#ifndef GPAC_DISABLE_VRML
/*
	if (ctrl && ctrl->stream->odm && ctrl->stream->odm->subscene)
			gf_term_invalidate_compositor(mo->odm->term);
*/
#endif
	}
	gf_odm_lock(mo->odm, 0);
	return in_loop;
}

GF_EXPORT
Double gf_mo_get_duration(GF_MediaObject *mo)
{
	Double dur;
	if (!gf_odm_lock_mo(mo)) return -1.0;
	dur = ((Double) (s64)mo->odm->duration)/1000.0;
	gf_odm_lock(mo->odm, 0);
	return dur;
}

GF_EXPORT
Bool gf_mo_should_deactivate(GF_MediaObject *mo)
{
	Bool res = 0;
#ifndef GPAC_DISABLE_VRML
	MediaControlStack *ctrl;
#endif

	if (!gf_odm_lock_mo(mo)) return 0;
	
	if (!mo->odm->state) {
		gf_odm_lock(mo->odm, 0);
		return 0;
	}

#ifndef GPAC_DISABLE_VRML
	/*get media control and see if object owning control is running*/
	ctrl = gf_odm_get_mediacontrol(mo->odm);
	if (!ctrl) res = 1;
	/*if ctrl and ctrl not ruling this mediaObject, deny deactivation*/
	else if (ctrl->stream->odm != mo->odm) res = 0;
	/*this is currently under discussion in MPEG. for now we deny deactivation as soon as a mediaControl is here*/
	else if (ctrl->stream->odm->state) res = 0;
	/*otherwise allow*/	
	else 
#endif
		res = 1;

	gf_odm_lock(mo->odm, 0);
	return res;
}

GF_EXPORT
Bool gf_mo_is_muted(GF_MediaObject *mo)
{
	Bool res = 0;
#ifndef GPAC_DISABLE_VRML
	if (!gf_odm_lock_mo(mo)) return 0;
	res = mo->odm->media_ctrl ? mo->odm->media_ctrl->control->mute : 0;
	gf_odm_lock(mo->odm, 0);
#endif
	return res;
}

GF_EXPORT
Bool gf_mo_is_done(GF_MediaObject *mo)
{
	Bool res = 0;
	GF_Codec *codec;
	u64 dur;
	if (!gf_odm_lock_mo(mo)) return 0;

	if (mo->odm->codec && mo->odm->codec->CB) {
		/*for natural media use composition buffer*/
		res = (mo->odm->codec->CB->Status==CB_STOP) ? 1 : 0;
	} else {
		/*otherwise check EOS and time*/
		codec = mo->odm->codec;
		dur = mo->odm->duration;
		if (!mo->odm->codec) {
			if (!mo->odm->subscene) res = 0;
			else {
				codec = mo->odm->subscene->scene_codec;
				dur = mo->odm->subscene->duration;
			}
		}
		if (codec && (codec->Status==GF_ESM_CODEC_STOP)) {
			/*codec is done, check by duration*/
			GF_Clock *ck = gf_odm_get_media_clock(mo->odm);
			if (gf_clock_time(ck) > dur) res = 1;
		}
	}
	gf_odm_lock(mo->odm, 0);
	return res;
}

/*resyncs clock - only audio objects are allowed to use this*/
GF_EXPORT
void gf_mo_adjust_clock(GF_MediaObject *mo, s32 ms_drift)
{
	if (!mo || !mo->odm) return;
	if (!mo->odm->codec || (mo->odm->codec->type != GF_STREAM_AUDIO) ) return;
	gf_clock_adjust_drift(mo->odm->codec->ck, ms_drift);
}

GF_EXPORT
u32 gf_mo_get_flags(GF_MediaObject *mo)
{
	return mo ? mo->flags : 0;
}

GF_EXPORT
void gf_mo_set_flag(GF_MediaObject *mo, u32 flag, Bool set_on)
{
	if (mo) {
		if (set_on) 
			mo->flags |= flag;
		else
			mo->flags &= ~flag;
	}
}

GF_EXPORT
u32 gf_mo_get_last_frame_time(GF_MediaObject *mo)
{
	return mo ? mo->timestamp : 0;
}

GF_EXPORT
Bool gf_mo_is_private_media(GF_MediaObject *mo)
{
	if (mo->odm && mo->odm->codec && mo->odm->codec->decio && (mo->odm->codec->decio->InterfaceType==GF_PRIVATE_MEDIA_DECODER_INTERFACE)) return 1;
	return 0;
}

GF_EXPORT
Bool gf_mo_set_position(GF_MediaObject *mo, GF_Window *src, GF_Window *dst)
{
	GF_Err e;
	GF_PrivateMediaDecoder *dec;
	if (!mo->odm || !mo->odm->codec || !mo->odm->codec->decio || (mo->odm->codec->decio->InterfaceType!=GF_PRIVATE_MEDIA_DECODER_INTERFACE)) return 0;

	dec = (GF_PrivateMediaDecoder*)mo->odm->codec->decio;
	e = dec->Control(dec, 0, src, dst);
	if (e==GF_BUFFER_TOO_SMALL) return 1;
	return 0;
}

GF_EXPORT
u32 gf_mo_has_audio(GF_MediaObject *mo)
{
	char *sub_url, *ext;
	u32 i;
	GF_NetworkCommand com;
	GF_ClientService *ns;
	GF_Scene *scene;
	if (!mo || !mo->odm) return 0;
	if (mo->type != GF_MEDIA_OBJECT_VIDEO) return 0;
	if (!mo->odm->net_service) return 2;

	ns = mo->odm->net_service;
	scene = mo->odm->parentscene;
	sub_url = strchr(ns->url, '#');
	for (i=0; i<gf_list_count(scene->resources); i++) {
		GF_ObjectManager *odm = gf_list_get(scene->resources, i);
		if (odm->net_service != ns) continue;
		if (!odm->mo) continue;

		if (sub_url) {
			ext = odm->mo->URLs.count ? odm->mo->URLs.vals[0].url : NULL;
			if (ext) ext = strchr(ext, '#');
			if (!ext || strcmp(sub_url, ext)) continue;
		} 
		/*there is already an audio object in this service, do not recreate one*/
		if (odm->mo->type == GF_MEDIA_OBJECT_AUDIO) return 0;
	}
	memset(&com, 0, sizeof(GF_NetworkCommand) );
	com.command_type = GF_NET_SERVICE_HAS_AUDIO;
	com.audio.base_url = mo->URLs.count ? mo->URLs.vals[0].url : NULL;
	if (!com.audio.base_url) com.audio.base_url = ns->url;
	if (gf_term_service_command(ns, &com) == GF_OK) return 1;
	return 0;
}

GF_EXPORT
GF_SceneGraph *gf_mo_get_scenegraph(GF_MediaObject *mo)
{
	if (!mo || !mo->odm || !mo->odm->subscene) return NULL;
	return mo->odm->subscene->graph;
}


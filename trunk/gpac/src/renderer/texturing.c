/*
 *			GPAC - Multimedia Framework C SDK
 *
 *			Copyright (c) Jean Le Feuvre 2000-2005
 *					All rights reserved
 *
 *  This file is part of GPAC / Scene Rendering sub-project
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

#include <gpac/internal/renderer_dev.h>

#include <gpac/nodes_svg.h>

#ifdef DANAE
#pragma message("compiling DANAE Texture handling")
int getDanaeTextureProperties(void *dmo, unsigned int stime, 
			int *dmo_last_frame_time,
			unsigned int *dmo_width, unsigned int *dmo_height,
			unsigned int *dmo_hasTransparentComponent,
			unsigned int *dmo_pixelFormat, unsigned int *dmo_stride, unsigned int *dmo_current_size,
			char **dmo_current_frame);

#endif



void gf_sr_texture_setup(GF_TextureHandler *txh, GF_Renderer *sr, GF_Node *owner)
{
	memset(txh, 0, sizeof(GF_TextureHandler));
	txh->owner = owner;
	txh->compositor = sr;
	if (gf_list_find(sr->textures, txh)<0) gf_list_add(sr->textures, txh);
}


void gf_sr_texture_destroy(GF_TextureHandler *txh)
{
	if (txh->hwtx) {
		txh->compositor->visual_renderer->ReleaseTexture(txh);
		txh->hwtx = NULL;
	}
	if (txh->is_open) gf_sr_texture_stop(txh);
	gf_list_del_item(txh->compositor->textures, txh);
}

Bool gf_sr_texture_check_url_change(GF_TextureHandler *txh, MFURL *url)
{
#ifdef DANAE
	return 0;
#else
	if (!txh->stream) return url->count;
	return gf_mo_url_changed(txh->stream, url);
#endif
}

GF_Err gf_sr_texture_play(GF_TextureHandler *txh, MFURL *url)
{
	if (txh->is_open) return GF_BAD_PARAM;

	/*if existing texture in cache destroy it - we don't destroy it on stop to handle MovieTexture*/
	if (txh->hwtx) {
		txh->compositor->visual_renderer->ReleaseTexture(txh);
		txh->hwtx = NULL;
	}

	/*store url*/
	gf_sg_vrml_field_copy(&txh->current_url, url, GF_SG_VRML_MFURL);

#ifdef DANAE
txh->dmo = getDanaeMediaOjbectFromUrl(txh->compositor->danae_session, url->vals[0].url, (gf_node_get_tag(txh->owner)==TAG_SVG_video) ? 1 : 0);
#else 
	/*get media object*/
	txh->stream = gf_mo_find(txh->owner, url);
	/*bad/Empty URL*/
	if (!txh->stream) return GF_NOT_SUPPORTED;
	/*request play*/
	gf_mo_play(txh->stream);
#endif

	txh->last_frame_time = (u32) (-1);
	gf_sr_invalidate(txh->compositor, NULL);
	txh->is_open = 1;
	return GF_OK;
}

void gf_sr_texture_stop(GF_TextureHandler *txh)
{
	if (!txh->is_open) return;
#ifdef DANAE
	releaseDanaeMediaObject(txh->dmo);
#else 
	gf_sr_texture_release_stream(txh);
	gf_sr_invalidate(txh->compositor, NULL);
	gf_mo_stop(txh->stream);
#endif
	gf_sg_vrml_mf_reset(&txh->current_url, GF_SG_VRML_MFURL);
	txh->is_open = 0;

	/*and deassociate object*/
	txh->stream = NULL;
}

void gf_sr_texture_restart(GF_TextureHandler *txh)
{
#ifdef DANAE
	return;
#else
	if (!txh->is_open) return;
	gf_sr_texture_release_stream(txh);
	txh->stream_finished = 0;
	gf_mo_restart(txh->stream);
#endif
}

void gf_sr_texture_update_frame(GF_TextureHandler *txh, Bool disable_resync)
{
	/*already refreshed*/
	if (txh->needs_refresh) return;

#ifdef DANAE
	{
		u32 dmo_last_frame_time;
		u32 dmo_width, dmo_height;
		u32 dmo_hasTransparentComponent;
		u32 dmo_pixelFormat, dmo_stride, dmo_current_size;
		char *dmo_current_frame;

		s32 ret = getDanaeTextureProperties(txh->dmo, (u32) (gf_node_get_scene_time(txh->owner)*1000),
			&dmo_last_frame_time,
			&dmo_width, &dmo_height,
			&dmo_hasTransparentComponent,
			&dmo_pixelFormat, &dmo_stride, &dmo_current_size,
			&dmo_current_frame);
		if (ret == -1) return;

		if (!txh->hwtx) {
			txh->compositor->visual_renderer->AllocTexture(txh);
			if (!txh->hwtx) return;

			txh->transparent = dmo_hasTransparentComponent;

		}

		txh->width = dmo_width;
		txh->height = dmo_height;
		txh->pixelformat = (dmo_pixelFormat == 0) ? GF_PIXEL_RGB_32 : 0;
		txh->stride = dmo_stride;
		//txh->frame_size = dmo_current_size;
		txh->data = dmo_current_frame;
	}
#else
	if (!txh->stream) {
		txh->data = NULL;
		return;
	}

	/*this is in case the texture was not release at previous cycle if the node hasn't been drawn
	we need a better way to do this since it locks video memory*/
	if (txh->needs_release) {
		gf_mo_release_data(txh->stream, txh->stream->current_size, 0);
	}
	txh->needs_release = gf_mo_fetch_data(txh->stream, !disable_resync, &txh->stream_finished);

	/*check init flag*/
	if (!(txh->stream->mo_flags & GF_MO_IS_INIT)) {
		/*if we had a texture this means the object has changed - delete texture and force next frame 
		rendering (this will take care of OD reuse)*/
		if (txh->hwtx) {
			txh->compositor->visual_renderer->ReleaseTexture(txh);
			txh->hwtx = NULL;
			txh->data = NULL;
			txh->needs_refresh = 1;
			gf_sr_invalidate(txh->compositor, NULL);
			return;
		}
	}

	/*if no frame or muted don't draw*/
	if (!txh->stream->current_frame || !txh->stream->current_size) return;

	/*if setup and same frame return*/
	if (txh->hwtx && (txh->stream_finished || (txh->last_frame_time==txh->stream->current_ts)) ) {
		if (txh->needs_release) {
			gf_mo_release_data(txh->stream, txh->stream->current_size, 0);
			txh->needs_release = 0;
		}
		return;
	}
	txh->last_frame_time = txh->stream->current_ts;
	if (gf_mo_is_muted(txh->stream)) return;

	if (!txh->hwtx) {
		txh->compositor->visual_renderer->AllocTexture(txh);
		if (!txh->hwtx) return;

		txh->transparent = 0;
		switch (txh->stream->pixelFormat) {
		case GF_PIXEL_ALPHAGREY:
		case GF_PIXEL_ARGB:
		case GF_PIXEL_RGBA:
		case GF_PIXEL_YUVA:
			txh->transparent = 1;
			break;
		}

		txh->stream->mo_flags |= GF_MO_IS_INIT;
	}

	txh->width = txh->stream->width;
	txh->height = txh->stream->height;
	txh->pixelformat = txh->stream->pixelFormat;
	txh->stride = txh->stream->stride;
	txh->data = txh->stream->current_frame;
	txh->pixel_ar = txh->stream->pixel_ar;

#endif
	/*try to push texture on graphics but don't complain if failure*/
	txh->compositor->visual_renderer->SetTextureData(txh);

	txh->needs_refresh = 1;
	gf_sr_invalidate(txh->compositor, NULL);
}

void gf_sr_texture_release_stream(GF_TextureHandler *txh)
{
	if (txh->needs_release) {
		assert(txh->stream);
		gf_mo_release_data(txh->stream, txh->stream->current_size, 0);
		txh->needs_release = 0;
	}
	txh->needs_refresh = 0;
}

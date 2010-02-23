/*
 *			GPAC - Multimedia Framework C SDK
 *
 *			Copyright (c) Jean Le Feuvre 2000-2005 
 *					All rights reserved
 *
 *  This file is part of GPAC / Scene Management sub-project
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

#include <gpac/scene_manager.h>
#include <gpac/constants.h>
#include <gpac/media_tools.h>
#include <gpac/bifs.h>
#include <gpac/xml.h>
#include <gpac/internal/scenegraph_dev.h>


GF_EXPORT
GF_SceneManager *gf_sm_new(GF_SceneGraph *graph)
{
	GF_SceneManager *tmp;
	
	if (!graph) return NULL;
	GF_SAFEALLOC(tmp, GF_SceneManager);
	tmp->streams = gf_list_new();
	tmp->scene_graph = graph;
	return tmp;
}

GF_EXPORT
GF_StreamContext *gf_sm_stream_new(GF_SceneManager *ctx, u16 ES_ID, u8 streamType, u8 objectType)
{
	u32 i;
	GF_StreamContext *tmp;

	i=0;
	while ((tmp = (GF_StreamContext*)gf_list_enum(ctx->streams, &i))) {
		/*we MUST use the same ST*/
		if (tmp->streamType!=streamType) continue;
		/*if no ESID/OTI specified this is a base layer (default stream created by parsers)
		if ESID/OTI specified this is a stream already setup
		*/
		if ( tmp->ESID==ES_ID ){
			//tmp->objectType = objectType;
			return tmp;
		}
	}
	
	GF_SAFEALLOC(tmp, GF_StreamContext);
	tmp->AUs = gf_list_new();
	tmp->ESID = ES_ID;
	tmp->streamType = streamType;
	tmp->objectType = objectType;
	tmp->timeScale = 1000;
	gf_list_add(ctx->streams, tmp);
	return tmp;
}

GF_StreamContext *gf_sm_stream_find(GF_SceneManager *ctx, u16 ES_ID)
{
	u32 i, count;
	if (!ES_ID) return NULL;
	count = gf_list_count(ctx->streams);
	for (i=0; i<count; i++) {
		GF_StreamContext *tmp = (GF_StreamContext *)gf_list_get(ctx->streams, i);
		if (tmp->ESID==ES_ID) return tmp;
	}
	return NULL;
}

static void gf_sm_reset_stream(GF_StreamContext *sc)
{
	while (gf_list_count(sc->AUs)) {
		GF_AUContext *au = (GF_AUContext *)gf_list_last(sc->AUs);
		gf_list_rem_last(sc->AUs);

		while (gf_list_count(au->commands)) {
			void *comptr = gf_list_last(au->commands);
			gf_list_rem_last(au->commands);
			switch (sc->streamType) {
			case GF_STREAM_OD:
				gf_odf_com_del((GF_ODCom**) & comptr);
				break;
			case GF_STREAM_SCENE:
				gf_sg_command_del((GF_Command *)comptr);
				break;
			}
		}
		gf_list_del(au->commands);
		gf_free(au);
	}
}

static void gf_sm_delete_stream(GF_StreamContext *sc)
{
	gf_sm_reset_stream(sc);
	gf_list_del(sc->AUs);
	if (sc->name) gf_free(sc->name);
	if (sc->dec_cfg) gf_free(sc->dec_cfg);
	gf_free(sc);
}

GF_EXPORT
void gf_sm_stream_del(GF_SceneManager *ctx, GF_StreamContext *sc)
{
	if (gf_list_del_item(ctx->streams, sc)>=0) {
		gf_sm_delete_stream(sc);
	}
}

GF_EXPORT
void gf_sm_del(GF_SceneManager *ctx)
{
	u32 count;
	while ( (count = gf_list_count(ctx->streams)) ) {
		GF_StreamContext *sc = (GF_StreamContext *)gf_list_get(ctx->streams, count-1);
		gf_list_rem(ctx->streams, count-1);
		gf_sm_delete_stream(sc);
	}
	gf_list_del(ctx->streams);
	if (ctx->root_od) gf_odf_desc_del((GF_Descriptor *) ctx->root_od);
	gf_free(ctx);
}

GF_EXPORT
void gf_sm_reset(GF_SceneManager *ctx)
{
	GF_StreamContext *sc;
	u32 i=0;
	while ( (sc = gf_list_enum(ctx->streams, &i)) ) {
		gf_sm_reset_stream(sc);
	}
	if (ctx->root_od) gf_odf_desc_del((GF_Descriptor *) ctx->root_od);
	ctx->root_od = NULL;
}

GF_EXPORT
GF_AUContext *gf_sm_stream_au_new(GF_StreamContext *stream, u64 timing, Double time_sec, Bool isRap)
{
	u32 i;
	GF_AUContext *tmp;

	/*look for existing AU*/
	i=0;
	while ((tmp = (GF_AUContext *)gf_list_enum(stream->AUs, &i))) {
		if (timing && (tmp->timing==timing)) return tmp;
		else if (time_sec && (tmp->timing_sec == time_sec)) return tmp;
		else if (!time_sec && !timing && !tmp->timing && !tmp->timing_sec) return tmp;
		/*insert AU*/
		else if ((time_sec && time_sec<tmp->timing_sec) || (timing && timing<tmp->timing)) {
			tmp = (GF_AUContext *)gf_malloc(sizeof(GF_AUContext));
			tmp->commands = gf_list_new();
			tmp->is_rap = isRap;
			tmp->timing = timing;
			tmp->timing_sec = time_sec;
			tmp->owner = stream;
			gf_list_insert(stream->AUs, tmp, i-1);
			return tmp;
		}
	}
	tmp = (GF_AUContext *)gf_malloc(sizeof(GF_AUContext));
	tmp->commands = gf_list_new();
	tmp->is_rap = isRap;
	tmp->timing = timing;
	tmp->timing_sec = time_sec;
	tmp->owner = stream;
	gf_list_add(stream->AUs, tmp);
	return tmp;
}

static Bool au_triggers_changes(GF_AUContext *au, Bool mark_for_aggregation)
{
	u32 i= 0;
	GF_Command *com;
	while ((com = gf_list_enum(au->commands, &i))) {
		if ((i==1) && mark_for_aggregation) com->never_apply = 1;
		if (!com->never_apply) return 1;
	}
	return 0;
}

GF_EXPORT
GF_Err gf_sm_make_random_access(GF_SceneManager *ctx)
{
	GF_Err e;
	u32 i, stream_count;
#ifndef GPAC_DISABLE_VRML
	u32 j, au_count, com_count;
	GF_AUContext *au, *first_au;
	GF_Command *com;
#endif
	Bool has_changes = 0;

	e = GF_OK;
	stream_count = gf_list_count(ctx->streams);
	for (i=0; i<stream_count; i++) {
		GF_StreamContext *sc = (GF_StreamContext *)gf_list_get(ctx->streams, i);

		/*FIXME - do this as well for ODs*/
#ifndef GPAC_DISABLE_VRML
		if (sc->streamType == GF_STREAM_SCENE) {
			/*we check for each stream if a RAP is carried (several streams may carry RAPs if inline nodes are used)*/
			Bool stream_rap_found = 0;

			/*in DIMS we use an empty initial AU with no commands to signal the RAP*/
            if (sc->objectType == GPAC_OTI_SCENE_DIMS) stream_rap_found = 1;

			/*apply all commands - this will also apply the SceneReplace*/
			j=0;
			while ((au = (GF_AUContext *)gf_list_enum(sc->AUs, &j))) {
				if (!stream_rap_found) {
					u32 k=0;
					while ((com = gf_list_enum(au->commands, &k))) {
						switch (sc->objectType) {
						case GPAC_OTI_SCENE_BIFS:
						case GPAC_OTI_SCENE_BIFS_V2:
							if (com->tag==GF_SG_SCENE_REPLACE)
								stream_rap_found = 1;
							break;
						case GPAC_OTI_SCENE_LASER:
							if (com->tag==GF_SG_LSR_NEW_SCENE)
								stream_rap_found = 1;
							break;
						}
						if (stream_rap_found) break;
					}
				}

				/*FIXME - this doesn't work for route insert/replace/append, they are applied to the graph, not to a subtree
				and will therefore end up in the base layer RAP (eg, SCENE REPLACE)*/

				/*skip first command of first AU if aggregation is enabled (this first command is the pseudo-rap of this stream)*/
				if (au_triggers_changes(au, (sc->aggregation_enabled && (j==1)) ? 1 : 0)) {
					e = gf_sg_command_apply_list(ctx->scene_graph, au->commands, 0);
					has_changes = 1;
				}
				if (e) return e;
			}

			/* Delete all the commands in the stream, except those marked as 'never_apply'*/
			au_count = gf_list_count(sc->AUs);

			while (au_count) {
				au = (GF_AUContext *)gf_list_get(sc->AUs, au_count-1);

				/*if aggregating */
				first_au = NULL;
				if (sc->aggregation_enabled && (au_count>1)) first_au = gf_list_get(sc->AUs, 0);

				com_count = gf_list_count(au->commands);
				while (com_count) {
					com = (GF_Command*)gf_list_get(au->commands, com_count - 1);
					if (!com->never_apply) {
						gf_list_rem(au->commands, com_count - 1);
						gf_sg_command_del(com);
					}
					else {
						/*reset never_apply flag*/
						if (sc->aggregation_enabled) com->never_apply=0;
						assert(!stream_rap_found);
					}
					com_count--;
				}
				if (!gf_list_count(au->commands)) {
					gf_list_rem(sc->AUs, au_count-1);
					gf_list_del(au->commands);
					gf_free(au);
				}
				au_count--;
			}
			/*and recreate scene replace*/
			if (stream_rap_found) {
				au = gf_sm_stream_au_new(sc, 0, 0, 1);

				switch (sc->objectType) {
				case GPAC_OTI_SCENE_BIFS:
				case GPAC_OTI_SCENE_BIFS_V2:
					com = gf_sg_command_new(ctx->scene_graph, GF_SG_SCENE_REPLACE);
					break;
				case GPAC_OTI_SCENE_LASER:
					com = gf_sg_command_new(ctx->scene_graph, GF_SG_LSR_NEW_SCENE);
					break;
                case GPAC_OTI_SCENE_DIMS:
                    /* We do not create a new command, empty AU is enough in DIMS*/
				default:
					com = NULL;
					break;
				}

				if (com) {
					com->node = ctx->scene_graph->RootNode;
					ctx->scene_graph->RootNode = NULL;
					gf_list_del(com->new_proto_list);
					com->new_proto_list = ctx->scene_graph->protos;
					ctx->scene_graph->protos = NULL;
					/*indicate the command is the aggregated scene graph, so that PROTOs and ROUTEs 
					are taken from the scenegraph when encoding*/
					com->aggregated = 1;
					gf_list_add(au->commands, com);
				}
			}
		}
#endif
	}
	return e;
}

#ifndef GPAC_DISABLE_LOADER_BT
GF_Err gf_sm_load_init_bt(GF_SceneLoader *load);
void gf_sm_load_done_bt(GF_SceneLoader *load);
GF_Err gf_sm_load_run_bt(GF_SceneLoader *load);
GF_Err gf_sm_load_init_bt_string(GF_SceneLoader *load, char *str);
GF_Err gf_sm_load_done_bt_string(GF_SceneLoader *load);
#endif 

#ifndef GPAC_DISABLE_LOADER_XMT
GF_Err gf_sm_load_init_xmt(GF_SceneLoader *load);
void gf_sm_load_done_xmt(GF_SceneLoader *load);
void gf_sm_load_suspend_xmt(GF_SceneLoader *load, Bool suspend);
GF_Err gf_sm_load_run_xmt(GF_SceneLoader *load);
GF_Err gf_sm_load_init_xmt_string(GF_SceneLoader *load, char *str);
#endif


GF_Err gf_sm_load_init_isom(GF_SceneLoader *load);
void gf_sm_load_done_isom(GF_SceneLoader *load);
GF_Err gf_sm_load_run_isom(GF_SceneLoader *load);

#ifndef GPAC_DISABLE_SVG

GF_Err gf_sm_load_init_svg(GF_SceneLoader *load);
GF_Err gf_sm_load_done_svg(GF_SceneLoader *load);
GF_Err gf_sm_load_run_svg(GF_SceneLoader *load);
GF_Err gf_sm_load_init_svg_string(GF_SceneLoader *load, char *str);
GF_Err gf_sm_load_suspend_svg(GF_SceneLoader *load, Bool suspend);

GF_Err gf_sm_load_init_xbl(GF_SceneLoader *load);
GF_Err gf_sm_load_done_xbl(GF_SceneLoader *load);
GF_Err gf_sm_load_run_xbl(GF_SceneLoader *load);
#endif

#ifndef GPAC_DISABLE_SWF_IMPORT

GF_Err gf_sm_load_init_swf(GF_SceneLoader *load);
void gf_sm_load_done_swf(GF_SceneLoader *load);
GF_Err gf_sm_load_run_swf(GF_SceneLoader *load);

#endif


#ifndef GPAC_DISABLE_QTVR

GF_Err gf_sm_load_init_qt(GF_SceneLoader *load);
void gf_sm_load_done_qt(GF_SceneLoader *load);
GF_Err gf_sm_load_run_qt(GF_SceneLoader *load);
#endif


static GF_Err gf_sm_load_init_from_string(GF_SceneLoader *load, char *str)
{

	/*we need at least a scene graph*/
	if (!load || (!load->ctx && !load->scene_graph)) return GF_BAD_PARAM;

	if (!load->type) return GF_NOT_SUPPORTED;

	if (!load->scene_graph) load->scene_graph = load->ctx->scene_graph;

	switch (load->type) {
#ifndef GPAC_DISABLE_LOADER_BT
	case GF_SM_LOAD_BT: 
	case GF_SM_LOAD_VRML:
	case GF_SM_LOAD_X3DV:
		return gf_sm_load_init_bt_string(load, str);
#endif

#ifndef GPAC_DISABLE_LOADER_XMT
	case GF_SM_LOAD_XMTA:
	case GF_SM_LOAD_X3D:
		return gf_sm_load_init_xmt_string(load, str);
#endif

#ifndef GPAC_DISABLE_SVG
	case GF_SM_LOAD_SVG_DA: 
	case GF_SM_LOAD_XSR: 
	case GF_SM_LOAD_DIMS: 
		return gf_sm_load_init_svg_string(load, str);
#endif

	case GF_SM_LOAD_SWF: 
		return GF_NOT_SUPPORTED;

#ifndef GPAC_DISABLE_LOADER_ISOM
	case GF_SM_LOAD_MP4:
		return GF_NOT_SUPPORTED;
#endif
	}
	return GF_NOT_SUPPORTED;
}

static void gf_sm_load_done_string(GF_SceneLoader *load, Bool do_clean)
{
	switch (load->type) {
#ifndef GPAC_DISABLE_LOADER_BT
	case GF_SM_LOAD_BT:
	case GF_SM_LOAD_VRML:
	case GF_SM_LOAD_X3DV:
		gf_sm_load_done_bt_string(load); 
		break;
#endif

#ifndef GPAC_DISABLE_LOADER_XMT
	case GF_SM_LOAD_XMTA:
	case GF_SM_LOAD_X3D:
		/*we do not reset it here to enable SAX parsing*/
		if (do_clean) gf_sm_load_done_xmt(load); 
		break;

#endif

#ifndef GPAC_DISABLE_SVG
	/*we do not reset it here to enable SAX parsing*/
	case GF_SM_LOAD_SVG_DA:
	case GF_SM_LOAD_XSR:
	case GF_SM_LOAD_DIMS:
		break;
#endif
	default: 
		break;
	}
}

GF_EXPORT
GF_Err gf_sm_load_string(GF_SceneLoader *load, char *str, Bool do_clean)
{
	GF_Err e = gf_sm_load_init_from_string(load, str);
	if (e) return e;
	e = gf_sm_load_run(load);
	gf_sm_load_done_string(load, do_clean);
	return (e<0) ? e : GF_OK;
}


/*initializes the context loader*/
GF_EXPORT
GF_Err gf_sm_load_init(GF_SceneLoader *load)
{
	GF_Err e = GF_NOT_SUPPORTED;
	char *ext, szExt[50];
	/*we need at least a scene graph*/
	if (!load || (!load->ctx && !load->scene_graph) 
#ifndef GPAC_DISABLE_ISOM
		|| (!load->fileName && !load->isom)
#endif
		) return GF_BAD_PARAM;

	if (!load->type) {
#ifndef GPAC_DISABLE_ISOM
		if (load->isom) {
			load->type = GF_SM_LOAD_MP4;
		} else 
#endif
		{
			ext = strrchr(load->fileName, '.');
			if (!ext) return GF_NOT_SUPPORTED;
			if (!stricmp(ext, ".gz")) {
				char *anext;
				ext[0] = 0;
				anext = strrchr(load->fileName, '.');
				ext[0] = '.';
				ext = anext;
			}
			strcpy(szExt, &ext[1]);
			strlwr(szExt);
			if (strstr(szExt, "bt")) load->type = GF_SM_LOAD_BT;
			else if (strstr(szExt, "wrl")) load->type = GF_SM_LOAD_VRML;
			else if (strstr(szExt, "x3dv")) load->type = GF_SM_LOAD_X3DV;
#ifndef GPAC_DISABLE_LOADER_XMT
			else if (strstr(szExt, "xmt") || strstr(szExt, "xmta")) load->type = GF_SM_LOAD_XMTA;
			else if (strstr(szExt, "x3d")) load->type = GF_SM_LOAD_X3D;
#endif
			else if (strstr(szExt, "swf")) load->type = GF_SM_LOAD_SWF;
			else if (strstr(szExt, "mov")) load->type = GF_SM_LOAD_QT;
			else if (strstr(szExt, "svg")) load->type = GF_SM_LOAD_SVG_DA;
			else if (strstr(szExt, "xsr")) load->type = GF_SM_LOAD_XSR;
			else if (strstr(szExt, "xbl")) load->type = GF_SM_LOAD_XBL;
			else if (strstr(szExt, "xml")) {
				char *rtype = gf_xml_get_root_type(load->fileName, &e);
				if (rtype) {
					if (!strcmp(rtype, "SAFSession")) load->type = GF_SM_LOAD_XSR;
					else if (!strcmp(rtype, "XMT-A")) load->type = GF_SM_LOAD_XMTA;
					else if (!strcmp(rtype, "X3D")) load->type = GF_SM_LOAD_X3D;
					else if (!strcmp(rtype, "bindings")) load->type = GF_SM_LOAD_XBL;

					gf_free(rtype);
				}
			}
		}
	}
	if (!load->type) return e;

	if (!load->scene_graph) load->scene_graph = load->ctx->scene_graph;

	switch (load->type) {
#ifndef GPAC_DISABLE_LOADER_BT
	case GF_SM_LOAD_BT: 
	case GF_SM_LOAD_VRML:
	case GF_SM_LOAD_X3DV:
		return gf_sm_load_init_bt(load);
#endif
#ifndef GPAC_DISABLE_LOADER_XMT
	case GF_SM_LOAD_XMTA:
	case GF_SM_LOAD_X3D:
		return gf_sm_load_init_xmt(load);
#endif

#ifndef GPAC_DISABLE_SVG
	case GF_SM_LOAD_SVG_DA:
	case GF_SM_LOAD_XSR:
	case GF_SM_LOAD_DIMS:
		return gf_sm_load_init_svg(load);

	case GF_SM_LOAD_XBL: 
		return gf_sm_load_init_xbl(load);
#endif

#ifndef GPAC_DISABLE_SWF_IMPORT
	case GF_SM_LOAD_SWF: 
		return gf_sm_load_init_swf(load);
#endif

#ifndef GPAC_DISABLE_LOADER_ISOM
	case GF_SM_LOAD_MP4:
		return gf_sm_load_init_isom(load);
#endif

#ifndef GPAC_DISABLE_QTVR
	case GF_SM_LOAD_QT: 
		return gf_sm_load_init_qt(load);
#endif

	}
	return GF_NOT_SUPPORTED;
}

GF_EXPORT
void gf_sm_load_done(GF_SceneLoader *load)
{
	switch (load->type) {
#ifndef GPAC_DISABLE_LOADER_BT
	case GF_SM_LOAD_BT:
	case GF_SM_LOAD_VRML:
	case GF_SM_LOAD_X3DV:
		gf_sm_load_done_bt(load); 
		break;
#endif

#ifndef GPAC_DISABLE_LOADER_XMT
	case GF_SM_LOAD_XMTA:
	case GF_SM_LOAD_X3D:
		gf_sm_load_done_xmt(load); 
		break;
#endif

#ifndef GPAC_DISABLE_SVG
	case GF_SM_LOAD_SVG_DA:
	case GF_SM_LOAD_XSR:
	case GF_SM_LOAD_DIMS:
		gf_sm_load_done_svg(load);
		break;

	case GF_SM_LOAD_XBL:
		gf_sm_load_done_xbl(load);
		break;
#endif

#ifndef GPAC_DISABLE_SWF_IMPORT
	case GF_SM_LOAD_SWF: 
		gf_sm_load_done_swf(load); 
		break;
#endif

#ifndef GPAC_DISABLE_LOADER_ISOM
	case GF_SM_LOAD_MP4: 
		gf_sm_load_done_isom(load); 
		break;
#endif

#ifndef GPAC_DISABLE_QTVR
	case GF_SM_LOAD_QT: 
		gf_sm_load_done_qt(load); 
		break;
#endif

	}
}

GF_EXPORT
GF_Err gf_sm_load_run(GF_SceneLoader *load)
{
	switch (load->type) {
#ifndef GPAC_DISABLE_LOADER_BT
	case GF_SM_LOAD_BT:
	case GF_SM_LOAD_VRML:
	case GF_SM_LOAD_X3DV:
		return gf_sm_load_run_bt(load);
#endif
#ifndef GPAC_DISABLE_LOADER_XMT
	case GF_SM_LOAD_XMTA:
	case GF_SM_LOAD_X3D:
		return gf_sm_load_run_xmt(load);
#endif

#ifndef GPAC_DISABLE_SVG
	case GF_SM_LOAD_SVG_DA:
	case GF_SM_LOAD_XSR:
	case GF_SM_LOAD_DIMS:
		return gf_sm_load_run_svg(load);
#endif

#ifndef GPAC_DISABLE_SVG
	case GF_SM_LOAD_XBL:
		return gf_sm_load_run_xbl(load);
#endif

#ifndef GPAC_DISABLE_SWF_IMPORT
	case GF_SM_LOAD_SWF:
		return gf_sm_load_run_swf(load);
#endif

#ifndef GPAC_DISABLE_LOADER_ISOM
	case GF_SM_LOAD_MP4: 
		return gf_sm_load_run_isom(load);
#endif

#ifndef GPAC_DISABLE_QTVR
	case GF_SM_LOAD_QT: 
		return gf_sm_load_run_qt(load);
#endif

	default:
		return GF_BAD_PARAM;
	}
}


GF_EXPORT
void gf_sm_load_suspend(GF_SceneLoader *load, Bool suspend)
{
	switch (load->type) {
#ifndef GPAC_DISABLE_LOADER_BT
	case GF_SM_LOAD_BT:
	case GF_SM_LOAD_VRML:
	case GF_SM_LOAD_X3DV:
		//gf_sm_load_suspend_bt(load, suspend); 
		break;
#endif

#ifndef GPAC_DISABLE_LOADER_XMT
	case GF_SM_LOAD_XMTA:
	case GF_SM_LOAD_X3D:
		gf_sm_load_suspend_xmt(load, suspend); 
		break;
#endif

#ifndef GPAC_DISABLE_SVG
	case GF_SM_LOAD_SVG_DA:
	case GF_SM_LOAD_XSR:
	case GF_SM_LOAD_DIMS:
		gf_sm_load_suspend_svg(load, suspend);
		break;

	case GF_SM_LOAD_XBL:
		break;
#endif

#ifndef GPAC_DISABLE_SWF_IMPORT
	case GF_SM_LOAD_SWF: 
		//gf_sm_load_suspend_swf(load, suspend); 
		break;
#endif

#ifndef GPAC_DISABLE_LOADER_ISOM
	case GF_SM_LOAD_MP4: 
		//gf_sm_load_suspend_isom(load, suspend); 
		break;
#endif

#ifndef GPAC_DISABLE_QTVR
	case GF_SM_LOAD_QT: 
		gf_sm_load_done_qt(load); 
		break;
#endif

	}
}

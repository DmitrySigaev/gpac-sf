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
	tmp->objectType = objectType ? objectType : 1;
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

static void gf_sm_au_del(GF_StreamContext *sc, GF_AUContext *au)
{
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

static void gf_sm_reset_stream(GF_StreamContext *sc)
{
	while (gf_list_count(sc->AUs)) {
		GF_AUContext *au = (GF_AUContext *)gf_list_last(sc->AUs);
		gf_list_rem_last(sc->AUs);
		gf_sm_au_del(sc, au);

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
			GF_SAFEALLOC(tmp, GF_AUContext);
			tmp->commands = gf_list_new();
			if (isRap) tmp->flags = GF_SM_AU_RAP;
			tmp->timing = timing;
			tmp->timing_sec = time_sec;
			tmp->owner = stream;
			gf_list_insert(stream->AUs, tmp, i-1);
			return tmp;
		}
	}
	GF_SAFEALLOC(tmp, GF_AUContext);
	tmp->commands = gf_list_new();
	if (isRap) tmp->flags = GF_SM_AU_RAP;
	tmp->timing = timing;
	tmp->timing_sec = time_sec;
	tmp->owner = stream;
	if (stream->disable_aggregation) tmp->flags |= GF_SM_AU_NOT_AGGREGATED;
	gf_list_add(stream->AUs, tmp);
	return tmp;
}

static u32 store_or_aggregate(GF_StreamContext *sc, GF_Command *com, GF_List *commands, Bool *has_modif)
{
	u32 i, count, j, nb_fields;
	GF_CommandField *field, *check_field;

	count = gf_list_count(commands);
	for (i=0; i<count; i++) {
		GF_Command *check = gf_list_get(commands, i);

		if (sc->streamType == GF_STREAM_SCENE) {
			switch (com->tag) {
			case GF_SG_FIELD_REPLACE:
			case GF_SG_MULTIPLE_REPLACE:
			case GF_SG_INDEXED_REPLACE:
			case GF_SG_MULTIPLE_INDEXED_REPLACE:
				if (check->tag != com->tag) goto check_next;
				if (check->node != com->node) goto check_next;
				nb_fields = gf_list_count(com->command_fields);
				if (gf_list_count(check->command_fields) != nb_fields) goto check_next;
				for (j=0; j<nb_fields; j++) {
					field = gf_list_get(com->command_fields, j);
					check_field = gf_list_get(check->command_fields, j);
					if (field->pos != check_field->pos) goto check_next;
					if (field->fieldIndex != check_field->fieldIndex) goto check_next;
				}
				/*same target node+fields, destroy first command and store new one*/
				gf_sg_command_del((GF_Command *)check);
				gf_list_rem(commands, i);
				if (has_modif) *has_modif = 1;
				return 1;

			case GF_SG_NODE_REPLACE:
				if (check->tag != GF_SG_NODE_REPLACE) goto check_next;
				/*TODO - THIS IS NOT SUPPORTED IN GPAC SINCE WE NEVER ALLOW FOR DUPLICATE NODE IDs IN THE SCENE !!!*/
				if (gf_node_get_id(check->node) != gf_node_get_id(com->node) ) goto check_next;
				/*same node ID, destroy first command and store new one*/
				gf_sg_command_del((GF_Command *)check);
				gf_list_rem(commands, i);
				if (has_modif) *has_modif = 1;
				return 1;

			case GF_SG_INDEXED_DELETE:
				/*look for an indexed insert before the indexed delete with same target pos and node. If found, discard both commands!*/
				if (check->tag != GF_SG_INDEXED_INSERT) goto check_next;
				if (com->node != check->node) goto check_next;
				field = gf_list_get(com->command_fields, 0);
				check_field = gf_list_get(check->command_fields, 0);
				if (!field || !check_field) goto check_next;
				if (field->pos != check_field->pos) goto check_next;
				if (field->fieldIndex != check_field->fieldIndex) goto check_next;

				gf_sg_command_del((GF_Command *)check);
				gf_list_rem(commands, i);
				if (has_modif) *has_modif = 1;
				return 2;

			default:
				GF_LOG(GF_LOG_ERROR, GF_LOG_SCENE, ("[Scene Manager] Stream Aggregation not implemented for command - aggregating on main scene\n"));
				break;
			}
check_next:
			;
		}
	}
	return 0;
}


GF_EXPORT
GF_Err gf_sm_aggregate(GF_SceneManager *ctx, u16 ESID)
{
	GF_Err e;
	u32 i, stream_count;
	GF_List *commands;
#ifndef GPAC_DISABLE_VRML
	u32 j;
	GF_AUContext *au;
	GF_Command *com;
#endif

	e = GF_OK;

#if DEBUG_RAP
    com_count = 0;
	stream_count = gf_list_count(ctx->streams);
    for (i=0; i<stream_count; i++) {
		GF_StreamContext *sc = (GF_StreamContext *)gf_list_get(ctx->streams, i);
		if (sc->streamType == GF_STREAM_SCENE) {
	        au_count = gf_list_count(sc->AUs);
            for (j=0; j<au_count; j++) {
				au = (GF_AUContext *)gf_list_get(sc->AUs, j);
                com_count += gf_list_count(au->commands);
            }
        }
    }
    GF_LOG(GF_LOG_INFO, GF_LOG_SCENE, ("[SceneManager] Making RAP with %d commands\n", com_count));
#endif

	stream_count = gf_list_count(ctx->streams);
	for (i=0; i<stream_count; i++) {
		GF_StreamContext *sc = (GF_StreamContext *)gf_list_get(ctx->streams, i);
		if (ESID && (sc->ESID!=ESID)) continue;

		/*TODO - do this as well for ODs*/
#ifndef GPAC_DISABLE_VRML
		if (sc->streamType == GF_STREAM_SCENE) {
			Bool has_modif = 0;
			Bool first_au=1;
			/*we check for each stream if it is a base stream (SceneReplace ...) - several streams may carry RAPs if inline nodes are used*/
			Bool base_stream_found = 0;
			u32 first_au_com_count = 0;

			/*in DIMS we use an empty initial AU with no commands to signal the RAP*/
            if (sc->objectType == GPAC_OTI_SCENE_DIMS) base_stream_found = 1;

			commands = gf_list_new();

			/*apply all commands - this will also apply the SceneReplace*/
			while (gf_list_count(sc->AUs)) {
				Bool first_com=1;
				u32 count;
				au = (GF_AUContext *) gf_list_get(sc->AUs, 0);
				gf_list_rem(sc->AUs, 0);

				/*AU not aggregated*/
				if (au->flags & GF_SM_AU_NOT_AGGREGATED) {
					gf_sm_au_del(sc, au);
					first_au=0;
					continue;
				}

				count = gf_list_count(au->commands);
				if (first_au && (au->flags & GF_SM_AU_CAROUSEL) ) first_au_com_count = count;

				for (j=0; j<count; j++) {
					u32 store=0;
					com = gf_list_get(au->commands, j);
					if (!base_stream_found) {
						switch (com->tag) {
						case GF_SG_SCENE_REPLACE:
						case GF_SG_LSR_NEW_SCENE:
						case GF_SG_LSR_REFRESH_SCENE:
							base_stream_found = 1;
							break;
						}
					}

					/*aggregate the command*/

					/*if stream doesn't carry a carousel or carries the base carousel (scene replace), always apply the command*/
					if (base_stream_found || !sc->aggregation_enabled) {
						store = 0;
					} 
					/*otherwise, check wether the command should be kept in this stream as is, or can be aggregated on this stream*/
					else {
						switch (com->tag) {
						/*the following commands do not impact a sub-tree (eg do not deal with nodes), we cannot
						aggregate them... */
						case GF_SG_ROUTE_REPLACE:
						case GF_SG_ROUTE_DELETE:
						case GF_SG_ROUTE_INSERT:
						case GF_SG_PROTO_INSERT:
						case GF_SG_PROTO_DELETE:
						case GF_SG_PROTO_DELETE_ALL:
						case GF_SG_GLOBAL_QUANTIZER:
						case GF_SG_LSR_RESTORE:
						case GF_SG_LSR_SAVE:
						case GF_SG_LSR_SEND_EVENT:
						case GF_SG_LSR_CLEAN:
						/*todo check in which category to put these commands*/
//						case GF_SG_LSR_ACTIVATE:
//						case GF_SG_LSR_DEACTIVATE:
							store = 1;
							break;
						/*other commands: 
							!!! we need to know if the target node of the command has been inserted in this stream !!!
						
						This is a tedious task, for now we will consider the following cases:
							- locate a similar command in the stored list: remove the similar one and aggregate on stream
							- by default all AUs are stored if the stream is in aggregate mode - we should fix that by checking insertion points:
							 if a command apllies on a node that has been inserted in this stream, we can aggregate, otherwise store
						*/
						default:
							store = store_or_aggregate(sc, com, commands, &has_modif);
							if (!store && sc->aggregation_enabled) store = 1;
							break;
						}
					}

					switch (store) {
					case 2:
						gf_list_rem(au->commands, j);
						j--;
						count--;
						gf_sg_command_del((GF_Command *)com);
						break;
					case 1:
						gf_list_insert(commands, com, 0);
						gf_list_rem(au->commands, j);
						j--;
						count--;
						break;
					default:
						/*apply command*/
						e = gf_sg_command_apply(ctx->scene_graph, com, 0);
						break;
					}
					first_com=0;
				}
				gf_sm_au_del(sc, au);
				first_au=0;
			}

			/*and recreate scene replace*/
			if (base_stream_found) {
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

				assert(gf_list_count(commands)==0);
				gf_list_del(commands);
			}
			/*create an empty AU with stored commands*/ 
			else {
				au = gf_sm_stream_au_new(sc, 0, 0, 1);
				gf_list_del(au->commands);
				au->commands = commands;
				au->flags |= GF_SM_AU_RAP | GF_SM_AU_CAROUSEL;
				if (has_modif || (gf_list_count(au->commands) != first_au_com_count)) {
					au->flags |= GF_SM_AU_MODIFIED;
				}

			}
		}
#endif
	}
	return e;
}

#ifndef GPAC_DISABLE_LOADER_BT
GF_Err gf_sm_load_init_bt(GF_SceneLoader *load);
#endif 

#ifndef GPAC_DISABLE_LOADER_XMT
GF_Err gf_sm_load_init_xmt(GF_SceneLoader *load);
#endif

#ifndef GPAC_DISABLE_LOADER_ISOM
GF_Err gf_sm_load_init_isom(GF_SceneLoader *load);
#endif

#ifndef GPAC_DISABLE_SVG

GF_Err gf_sm_load_init_svg(GF_SceneLoader *load);

GF_Err gf_sm_load_init_xbl(GF_SceneLoader *load);
GF_Err gf_sm_load_run_xbl(GF_SceneLoader *load);
void gf_sm_load_done_xbl(GF_SceneLoader *load);
#endif

#ifndef GPAC_DISABLE_SWF_IMPORT
GF_Err gf_sm_load_init_swf(GF_SceneLoader *load);
#endif


#ifndef GPAC_DISABLE_QTVR

GF_Err gf_sm_load_init_qt(GF_SceneLoader *load);
#endif



GF_EXPORT
GF_Err gf_sm_load_string(GF_SceneLoader *load, char *str, Bool do_clean)
{
	GF_Err e;
	if (!load->type) e = GF_BAD_PARAM;
	else if (load->parse_string) e = load->parse_string(load, str);
	else e = GF_NOT_SUPPORTED;

	return e;
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
		|| (!load->fileName && !load->isom && !(load->flags & GF_SM_LOAD_FOR_PLAYBACK) )
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
			else if (strstr(szExt, "svg")) load->type = GF_SM_LOAD_SVG;
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
	case GF_SM_LOAD_SVG:
	case GF_SM_LOAD_XSR:
	case GF_SM_LOAD_DIMS:
		return gf_sm_load_init_svg(load);

	case GF_SM_LOAD_XBL: 
		e = gf_sm_load_init_xbl(load);

		load->process = gf_sm_load_run_xbl;;
		load->done = gf_sm_load_done_xbl;
		return e;
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
	if (load->done) load->done(load);
}

GF_EXPORT
GF_Err gf_sm_load_run(GF_SceneLoader *load)
{
	if (load->process) return load->process(load);
	return GF_OK;
}

GF_EXPORT
GF_Err gf_sm_load_suspend(GF_SceneLoader *load, Bool suspend)
{
	if (load->suspend) return load->suspend(load, suspend);
	return GF_OK;
}

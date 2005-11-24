/*
 *			GPAC - Multimedia Framework C SDK
 *
 *			Copyright (c) Jean Le Feuvre 2000-2005
 *					All rights reserved
 *
 *  This file is part of GPAC / Scene Graph sub-project
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


#include <gpac/internal/scenegraph_dev.h>
/*MPEG4 tags (for internal nodes)*/
#include <gpac/nodes_mpeg4.h>


GF_Command *gf_sg_command_new(GF_SceneGraph *graph, u32 tag)
{
	GF_Command *ptr;
	GF_SAFEALLOC(ptr, sizeof(GF_Command));
	if (!ptr) return NULL;
	ptr->tag = tag;
	ptr->in_scene = graph;
	ptr->command_fields = gf_list_new();
	if (tag < GF_SG_LAST_BIFS_COMMAND) ptr->new_proto_list = gf_list_new();
	return ptr;
}
static void SG_CheckNodeUnregister(GF_Command *com)
{
	if (com->tag==GF_SG_SCENE_REPLACE) {
		gf_node_unregister(com->node, NULL);
	} else {
		u32 i;
		for (i=0; i<com->in_scene->node_reg_size; i++) {
			if (com->in_scene->node_registry[i] == com->node) {
				gf_node_unregister(com->node, NULL);
				return;
			}
		}
	}
}

void gf_sg_command_del(GF_Command *com)
{
	u32 i;
	if (!com) return;

	if (com->tag < GF_SG_LAST_BIFS_COMMAND) {
		while (gf_list_count(com->command_fields)) {
			GF_CommandField *inf = gf_list_get(com->command_fields, 0);
			gf_list_rem(com->command_fields, 0);

			switch (inf->fieldType) {
			case GF_SG_VRML_SFNODE:
				if (inf->field_ptr && *(GF_Node **) inf->field_ptr) gf_node_unregister(*(GF_Node **) inf->field_ptr, com->node);
				break;
			case GF_SG_VRML_MFNODE:
				if (inf->field_ptr) {
					gf_node_unregister_children(com->node, *(GF_List**) inf->field_ptr);
					gf_list_del(*(GF_List**) inf->field_ptr);
				}
				break;
			default:
				gf_sg_vrml_field_pointer_del(inf->field_ptr, inf->fieldType);
				break;
			}
			free(inf);
		}
	} else {
	}
	gf_list_del(com->command_fields);

	for (i=0; i<gf_list_count(com->new_proto_list); i++) {
		GF_Proto *proto = gf_list_get(com->new_proto_list, i);
		gf_sg_proto_del(proto);
	}
	gf_list_del(com->new_proto_list);

	if (com->node) {
		if (!com->in_scene) gf_node_unregister(com->node, NULL);
		else SG_CheckNodeUnregister(com);
	}

	if (com->del_proto_list) free(com->del_proto_list);
	if (com->def_name) free(com->def_name);
	if (com->scripts_to_load) gf_list_del(com->scripts_to_load);
	free(com);
}

static void SG_CheckFieldChange(GF_Node *node, GF_FieldInfo *field)
{
	/*and propagate eventIn if any*/
	if (field->on_event_in) {
		field->on_event_in(node);
	} else if ((field->eventType==GF_SG_EVENT_IN) && (gf_node_get_tag(node) == TAG_MPEG4_Script)) {
		gf_sg_script_event_in(node, field);
	} else {
		/*Notify eventOut in all cases to handle protos*/
		gf_node_event_out(node, field->fieldIndex);
	}
	/*signal node modif*/
	gf_node_changed(node, field);
}

GF_Err gf_sg_command_apply(GF_SceneGraph *graph, GF_Command *com, Double time_offset)
{
	GF_Err e;
	GF_CommandField *inf;
	GF_FieldInfo field;
	GF_Node *def, *node;
	void *slot_ptr;

	if (!com || !graph) return GF_BAD_PARAM;

	e = GF_OK;
	switch (com->tag) {
	case GF_SG_SCENE_REPLACE:
		/*unregister root*/
		gf_node_unregister(graph->RootNode, NULL);
		/*remove all protos and routes*/
		while (gf_list_count(graph->routes_to_activate)) 
			gf_list_rem(graph->routes_to_activate, 0);
		
		/*destroy all routes*/
		while (gf_list_count(graph->Routes)) {
			GF_Route *r = gf_list_get(graph->Routes, 0);
			/*this will unregister the route from the graph, so don't delete the chain entry*/
			gf_sg_route_del(r);
		}
		/*destroy all proto*/
		while (gf_list_count(graph->protos)) {
			GF_Proto *p = gf_list_get(graph->protos, 0);
			/*this will unregister the proto from the graph, so don't delete the chain entry*/
			gf_sg_proto_del(p);
		}
		/*DO NOT TOUCH node registry*/
		/*DO NOT TOUCH UNREGISTERED PROTOS*/

		/*move all protos in graph*/
		while (gf_list_count(com->new_proto_list)) {
			GF_Proto *p = gf_list_get(com->new_proto_list, 0);
			gf_list_rem(com->new_proto_list, 0);
			gf_list_del_item(graph->unregistered_protos, p);
			gf_list_add(graph->protos, p);
		}
		/*assign new root (no need to register/unregister)*/
		graph->RootNode = com->node;
		com->node = NULL;
		break;

	case GF_SG_NODE_REPLACE:
		if (!gf_list_count(com->command_fields)) return GF_OK;
		inf = gf_list_get(com->command_fields, 0);
		e = gf_node_replace(com->node, inf->new_node, 0);
		if (inf->new_node) gf_node_register(inf->new_node, NULL);
		break;

	case GF_SG_MULTIPLE_REPLACE:
	case GF_SG_FIELD_REPLACE:
	{
		u32 i, j;
		GF_List *container, *list;
		for (j=0; j<gf_list_count(com->command_fields); j++) {
			inf = gf_list_get(com->command_fields, j);

			e = gf_node_get_field(com->node, inf->fieldIndex, &field);
			if (e) return e;

			switch (field.fieldType) {
			case GF_SG_VRML_SFNODE:
			{
				node = *((GF_Node **) field.far_ptr);
				e = gf_node_unregister(node, com->node);
				*((GF_Node **) field.far_ptr) = inf->new_node;
				if (!e) gf_node_register(inf->new_node, com->node);
				break;
			}
			case GF_SG_VRML_MFNODE:
				container = * ((GF_List **) field.far_ptr);
				list = * ((GF_List **) inf->field_ptr);
				gf_node_unregister_children(com->node, container);

				for (i=0; i<gf_list_count(list); i++) {
					node = gf_list_get(list, i);
					gf_list_add(container, node);
					if (!e) gf_node_register(node, com->node);
				}
				break;
			default:
				/*this is a regular field, reset it and clone - we cannot switch pointers since the
				original fields are NOT pointers*/
				if (!gf_sg_vrml_is_sf_field(field.fieldType)) {
					e = gf_sg_vrml_mf_reset(field.far_ptr, field.fieldType);
				}
				if (e) return e;
				gf_sg_vrml_field_copy(field.far_ptr, inf->field_ptr, field.fieldType);
				if (field.fieldType==GF_SG_VRML_SFTIME) *(SFTime *)field.far_ptr = *(SFTime *)field.far_ptr + time_offset;
				break;
			}
			SG_CheckFieldChange(com->node, &field);
		}
		break;
	}

	case GF_SG_MULTIPLE_INDEXED_REPLACE:
	case GF_SG_INDEXED_REPLACE:
	{
		u32 sftype, i;
		for (i=0; i<gf_list_count(com->command_fields); i++) {
			inf = gf_list_get(com->command_fields, i);

			e = gf_node_get_field(com->node, inf->fieldIndex, &field);
			if (e) return e;

			/*if MFNode remove the child and set new node*/
			if (field.fieldType == GF_SG_VRML_MFNODE) {
				/*we must remove the node before in case the new node uses the same ID (not forbidden) and this
				command removes the last instance of the node with the same ID*/
				gf_node_replace_child(com->node, *((GF_List**) field.far_ptr), inf->pos, inf->new_node);
				if (inf->new_node) gf_node_register(inf->new_node, com->node);
			}
			/*erase the field item*/
			else {
				if ((inf->pos < 0) || ((u32) inf->pos >= ((GenMFField *) field.far_ptr)->count) ) {
					inf->pos = ((GenMFField *)field.far_ptr)->count - 1;
					/*may happen with text and default value*/
					if (inf->pos < 0) {
						inf->pos = 0;
						gf_sg_vrml_mf_alloc(field.far_ptr, field.fieldType, 1);
					}
				}
				e = gf_sg_vrml_mf_get_item(field.far_ptr, field.fieldType, & slot_ptr, inf->pos);
				if (e) return e;
				sftype = gf_sg_vrml_get_sf_type(field.fieldType);
				gf_sg_vrml_field_copy(slot_ptr, inf->field_ptr, sftype);
				/*note we don't add time offset, since there's no MFTime*/
			}
			SG_CheckFieldChange(com->node, &field);
		}
		break;
	}
	case GF_SG_ROUTE_REPLACE:
	{
		GF_Route *r;
		char *name;
		r = gf_sg_route_find(graph, com->RouteID);
		def = gf_sg_find_node(graph, com->fromNodeID);
		node = gf_sg_find_node(graph, com->toNodeID);
		if (!node || !def) return GF_SG_UNKNOWN_NODE;
		name = NULL;
		if (r) {
			name = r->name;
			r->name = NULL;
			gf_sg_route_del(r);
		}
		r = gf_sg_route_new(graph, def, com->fromFieldIndex, node, com->toFieldIndex);
		gf_sg_route_set_id(r, com->RouteID);
		if (name) {
			gf_sg_route_set_name(r, name);
			free(name);
		}
		break;
	}
	case GF_SG_NODE_DELETE_EX:
	case GF_SG_NODE_DELETE:
	{
		if (com->node) gf_node_replace(com->node, NULL, (com->tag==GF_SG_NODE_DELETE_EX) ? 1 : 0);
		break;
	}
	case GF_SG_ROUTE_DELETE:
	{
		return gf_sg_route_del_by_id(graph, com->RouteID);
	}
	case GF_SG_INDEXED_DELETE:
	{
		if (!gf_list_count(com->command_fields)) return GF_OK;
		inf = gf_list_get(com->command_fields, 0);

		e = gf_node_get_field(com->node, inf->fieldIndex, &field);
		if (e) return e;
		if (gf_sg_vrml_is_sf_field(field.fieldType)) return GF_NON_COMPLIANT_BITSTREAM;

		/*then we need special handling in case of a node*/
		if (gf_sg_vrml_get_sf_type(field.fieldType) == GF_SG_VRML_SFNODE) {
			e = gf_node_replace_child(com->node, * ((GF_List **) field.far_ptr), inf->pos, NULL);
		} else {
			if ((inf->pos < 0) || ((u32) inf->pos >= ((GenMFField *) field.far_ptr)->count) ) {
				inf->pos = ((GenMFField *)field.far_ptr)->count - 1;
			}
			/*this is a regular MFField, just remove the item (realloc)*/
			e = gf_sg_vrml_mf_remove(field.far_ptr, field.fieldType, inf->pos);
		}
		/*deletion -> node has changed*/
		if (!e) SG_CheckFieldChange(com->node, &field);
		break;
	}
	case GF_SG_NODE_INSERT:
	{
		if (!gf_list_count(com->command_fields)) return GF_OK;
		inf = gf_list_get(com->command_fields, 0);

		e = gf_node_insert_child(com->node, inf->new_node, inf->pos);
		if (!e) gf_node_register(inf->new_node, com->node);
		/*notify (children is the 3rd field, so 2 0-based)*/
		if (!e) gf_node_event_out(com->node, 2);
		break;
	}
	case GF_SG_ROUTE_INSERT:
	{
		GF_Route *r;
		def = gf_sg_find_node(graph, com->fromNodeID);
		node = gf_sg_find_node(graph, com->toNodeID);
		if (!node || !def) return GF_SG_UNKNOWN_NODE;
		r = gf_sg_route_new(graph, def, com->fromFieldIndex, node, com->toFieldIndex);
		if (com->RouteID) gf_sg_route_set_id(r, com->RouteID);
		if (com->def_name) {
			gf_sg_route_set_name(r, com->def_name);
			free(com->def_name);
			com->def_name = NULL;
		}
		break;
	}
	case GF_SG_INDEXED_INSERT:
	{
		u32 sftype;
		if (!gf_list_count(com->command_fields)) return GF_OK;
		inf = gf_list_get(com->command_fields, 0);
		e = gf_node_get_field(com->node, inf->fieldIndex, &field);
		if (e) return e;

		/*rescale the MFField and parse the SFField*/
		if (field.fieldType != GF_SG_VRML_MFNODE) {
			if (inf->pos == -1) {
				e = gf_sg_vrml_mf_append(field.far_ptr, field.fieldType, & slot_ptr);
			} else {
				e = gf_sg_vrml_mf_insert(field.far_ptr, field.fieldType, & slot_ptr, inf->pos);
			}
			if (e) return e;
			sftype = gf_sg_vrml_get_sf_type(field.fieldType);
			gf_sg_vrml_field_copy(slot_ptr, inf->field_ptr, sftype);
		} else {
			if (inf->new_node) {
				GF_List *list = *(GF_List **) field.far_ptr;
				if (inf->pos == -1) {
					e = gf_list_add(list, inf->new_node);
				} else {
					e = gf_list_insert(list, inf->new_node, inf->pos);
				}
				if (e) return e;
				gf_node_register(inf->new_node, com->node);
			}
		}
		if (!e) SG_CheckFieldChange(com->node, &field);
		break;
	}
	case GF_SG_PROTO_INSERT:
		/*destroy all proto*/
		while (gf_list_count(com->new_proto_list)) {
			GF_Proto *p = gf_list_get(com->new_proto_list, 0);
			gf_list_rem(com->new_proto_list, 0);
			gf_list_del_item(graph->unregistered_protos, p);
			gf_list_add(graph->protos, p);
		}
		return GF_OK;
	case GF_SG_PROTO_DELETE:
		{
			u32 i;
			for (i=0; i<com->del_proto_list_size; i++) {
				/*note this will check for unregistered protos, but since IDs are unique we are sure we will 
				not destroy an unregistered one*/
				GF_Proto *proto = gf_sg_find_proto(graph, com->del_proto_list[i], NULL);
				if (proto) gf_sg_proto_del(proto);
			}
		}
		return GF_OK;
	case GF_SG_PROTO_DELETE_ALL:
		/*destroy all proto*/
		while (gf_list_count(graph->protos)) {
			GF_Proto *p = gf_list_get(graph->protos, 0);
			gf_list_rem(graph->protos, 0);
			/*this will unregister the proto from the graph, so don't delete the chain entry*/
			gf_sg_proto_del(p);
		}
		/*DO NOT TOUCH UNREGISTERED PROTOS*/
		return GF_OK;
	/*only used by BIFS*/
	case GF_SG_GLOBAL_QUANTIZER:
		return GF_OK;
	default:
		return GF_NOT_SUPPORTED;
	}
	if (e) return e;

	if (com->scripts_to_load) {
		while (gf_list_count(com->scripts_to_load)) {
			GF_Node *script = gf_list_get(com->scripts_to_load, 0);
			gf_list_rem(com->scripts_to_load, 0);
			gf_sg_script_load(script);
		}
		gf_list_del(com->scripts_to_load);
		com->scripts_to_load = NULL;
	}
	return GF_OK;
}

GF_CommandField *gf_sg_command_field_new(GF_Command *com)
{
	GF_CommandField *ptr;
	GF_SAFEALLOC(ptr, sizeof(GF_CommandField));
	gf_list_add(com->command_fields, ptr);
	return ptr;
}


GF_Err gf_sg_command_apply_list(GF_SceneGraph *graph, GF_List *comList, Double time_offset)
{
	GF_Err e;
	u32 i;
	for (i=0; i<gf_list_count(comList); i++) {
		GF_Command *com = gf_list_get(comList, i);
		e = gf_sg_command_apply(graph, com, time_offset);
		if (e) return e;
	}
	return GF_OK;
}

GF_Command *gf_sg_command_clone(GF_Command *com, GF_SceneGraph *inGraph)
{
	u32 i;
	GF_Command *dest;
	
	if (com->tag==GF_SG_SCENE_REPLACE) return NULL;
	/*FIXME - to do*/
	if (gf_list_count(com->new_proto_list)) return NULL;
	dest = gf_sg_command_new(inGraph, com->tag);

	/*node the command applies to - may be NULL*/
	dest->node = gf_node_clone(inGraph, com->node, NULL);
	/*route insert, replace and delete*/
	dest->RouteID = com->RouteID;
	if (com->def_name) dest->def_name = strdup(com->def_name);
	dest->fromNodeID = com->fromNodeID;
	dest->fromFieldIndex = com->fromFieldIndex;
	dest->toNodeID = com->toNodeID;
	dest->toFieldIndex = com->toFieldIndex;
	dest->del_proto_list_size = com->del_proto_list_size;
	if (com->del_proto_list_size) {
		dest->del_proto_list = malloc(sizeof(u32) * com->del_proto_list_size);
		memcpy(dest->del_proto_list, com->del_proto_list, sizeof(u32) * com->del_proto_list_size);
	}

	for (i=0; i<gf_list_count(com->command_fields); i++) {
		GF_CommandField *fo = gf_list_get(com->command_fields, i);
		GF_CommandField *fd = gf_sg_command_field_new(dest);

		fd->fieldIndex = fo->fieldIndex;
		fd->fieldType = fo->fieldType;
		fd->pos = fo->pos;
		if (fo->field_ptr) {
			fd->field_ptr = gf_sg_vrml_field_pointer_new(fd->fieldType);
			gf_sg_vrml_field_copy(fd->field_ptr, fo->field_ptr, fo->fieldType);
		}

		if (fo->new_node) {
			fd->new_node = gf_node_clone(inGraph, fo->new_node, dest->node);
			fd->field_ptr = &fd->new_node;
		}
		if (fo->node_list) {
			u32 j;
			fd->node_list = gf_list_new();
			for (j=0; j<gf_list_count(fo->node_list); j++) {
				GF_Node *co = gf_list_get(fo->node_list, j);
				GF_Node *cd = gf_node_clone(inGraph, co, dest->node);
				gf_list_add(fd->node_list, cd);
			}
			fd->field_ptr = &fd->node_list;
		}
	}
	return dest;
}


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


/*
	DO NOT MOFIFY - File generated on GMT Thu Jun 25 11:28:59 2009

	BY MPEG4Gen for GPAC Version 0.4.6-DEV
*/

#include <gpac/nodes_mpeg4.h>


#include <gpac/internal/scenegraph_dev.h>

/*
	Anchor Node deletion
*/

static void Anchor_Del(GF_Node *node)
{
	M_Anchor *p = (M_Anchor *) node;
	gf_sg_sfstring_del(p->description);
	gf_sg_mfstring_del(p->parameter);
	gf_sg_mfurl_del(p->url);
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 Anchor_Def2All[] = { 2, 3, 4, 5};
static const u16 Anchor_In2All[] = { 0, 1, 2, 3, 4, 5, 6};
static const u16 Anchor_Out2All[] = { 2, 3, 4, 5};

static u32 Anchor_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 7;
	case GF_SG_FIELD_CODING_DEF: return 4;
	case GF_SG_FIELD_CODING_OUT: return 4;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 7;
	}
}

static GF_Err Anchor_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Anchor_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Anchor_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Anchor_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Anchor_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Anchor *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_Anchor *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Anchor *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_Anchor *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_Anchor *)node)->children;
		return GF_OK;
	case 3:
		info->name = "description";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_Anchor *) node)->description;
		return GF_OK;
	case 4:
		info->name = "parameter";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFSTRING;
		info->far_ptr = & ((M_Anchor *) node)->parameter;
		return GF_OK;
	case 5:
		info->name = "url";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_Anchor *) node)->url;
		return GF_OK;
	case 6:
		info->name = "activate";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Anchor *)node)->on_activate;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Anchor *) node)->activate;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Anchor_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	if (!strcmp("description", name)) return 3;
	if (!strcmp("parameter", name)) return 4;
	if (!strcmp("url", name)) return 5;
	if (!strcmp("activate", name)) return 6;
	return -1;
	}
static Bool Anchor_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *Anchor_Create()
{
	M_Anchor *p;
	GF_SAFEALLOC(p, M_Anchor);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Anchor);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	AnimationStream Node deletion
*/

static void AnimationStream_Del(GF_Node *node)
{
	M_AnimationStream *p = (M_AnimationStream *) node;
	gf_sg_mfurl_del(p->url);
	gf_node_free((GF_Node *) p);
}

static const u16 AnimationStream_Def2All[] = { 0, 1, 2, 3, 4};
static const u16 AnimationStream_In2All[] = { 0, 1, 2, 3, 4};
static const u16 AnimationStream_Out2All[] = { 0, 1, 2, 3, 4, 5, 6};
static const u16 AnimationStream_Dyn2All[] = { 1};

static u32 AnimationStream_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 5;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 7;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 7;
	}
}

static GF_Err AnimationStream_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = AnimationStream_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = AnimationStream_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = AnimationStream_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = AnimationStream_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err AnimationStream_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "loop";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_AnimationStream *) node)->loop;
		return GF_OK;
	case 1:
		info->name = "speed";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_AnimationStream *) node)->speed;
		return GF_OK;
	case 2:
		info->name = "startTime";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_AnimationStream *) node)->startTime;
		return GF_OK;
	case 3:
		info->name = "stopTime";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_AnimationStream *) node)->stopTime;
		return GF_OK;
	case 4:
		info->name = "url";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_AnimationStream *) node)->url;
		return GF_OK;
	case 5:
		info->name = "duration_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_AnimationStream *) node)->duration_changed;
		return GF_OK;
	case 6:
		info->name = "isActive";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_AnimationStream *) node)->isActive;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 AnimationStream_get_field_index_by_name(char *name)
{
	if (!strcmp("loop", name)) return 0;
	if (!strcmp("speed", name)) return 1;
	if (!strcmp("startTime", name)) return 2;
	if (!strcmp("stopTime", name)) return 3;
	if (!strcmp("url", name)) return 4;
	if (!strcmp("duration_changed", name)) return 5;
	if (!strcmp("isActive", name)) return 6;
	return -1;
	}
static Bool AnimationStream_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 7;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *AnimationStream_Create()
{
	M_AnimationStream *p;
	GF_SAFEALLOC(p, M_AnimationStream);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_AnimationStream);

	/*default field values*/
	p->speed = FLT2FIX(1.0);
	p->startTime = 0;
	p->stopTime = 0;
	return (GF_Node *)p;
}


/*
	Appearance Node deletion
*/

static void Appearance_Del(GF_Node *node)
{
	M_Appearance *p = (M_Appearance *) node;
	gf_node_unregister((GF_Node *) p->material, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->texture, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->textureTransform, (GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 Appearance_Def2All[] = { 0, 1, 2};
static const u16 Appearance_In2All[] = { 0, 1, 2};
static const u16 Appearance_Out2All[] = { 0, 1, 2};

static u32 Appearance_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 3;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 3;
	}
}

static GF_Err Appearance_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Appearance_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Appearance_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Appearance_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Appearance_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "material";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFMaterialNode;
		info->far_ptr = & ((M_Appearance *)node)->material;
		return GF_OK;
	case 1:
		info->name = "texture";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFTextureNode;
		info->far_ptr = & ((M_Appearance *)node)->texture;
		return GF_OK;
	case 2:
		info->name = "textureTransform";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFTextureTransformNode;
		info->far_ptr = & ((M_Appearance *)node)->textureTransform;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Appearance_get_field_index_by_name(char *name)
{
	if (!strcmp("material", name)) return 0;
	if (!strcmp("texture", name)) return 1;
	if (!strcmp("textureTransform", name)) return 2;
	return -1;
	}
static Bool Appearance_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *Appearance_Create()
{
	M_Appearance *p;
	GF_SAFEALLOC(p, M_Appearance);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Appearance);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	AudioBuffer Node deletion
*/

static void AudioBuffer_Del(GF_Node *node)
{
	M_AudioBuffer *p = (M_AudioBuffer *) node;
	gf_node_unregister_children((GF_Node *) p, p->children);	
	gf_sg_mfint32_del(p->phaseGroup);
	gf_node_free((GF_Node *) p);
}

static const u16 AudioBuffer_Def2All[] = { 0, 1, 2, 3, 4, 5, 6, 7};
static const u16 AudioBuffer_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7};
static const u16 AudioBuffer_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
static const u16 AudioBuffer_Dyn2All[] = { 1};

static u32 AudioBuffer_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 8;
	case GF_SG_FIELD_CODING_DEF: return 8;
	case GF_SG_FIELD_CODING_OUT: return 10;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 10;
	}
}

static GF_Err AudioBuffer_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = AudioBuffer_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = AudioBuffer_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = AudioBuffer_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = AudioBuffer_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err AudioBuffer_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "loop";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_AudioBuffer *) node)->loop;
		return GF_OK;
	case 1:
		info->name = "pitch";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_AudioBuffer *) node)->pitch;
		return GF_OK;
	case 2:
		info->name = "startTime";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_AudioBuffer *) node)->startTime;
		return GF_OK;
	case 3:
		info->name = "stopTime";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_AudioBuffer *) node)->stopTime;
		return GF_OK;
	case 4:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFAudioNode;
		info->far_ptr = & ((M_AudioBuffer *)node)->children;
		return GF_OK;
	case 5:
		info->name = "numChan";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_AudioBuffer *) node)->numChan;
		return GF_OK;
	case 6:
		info->name = "phaseGroup";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_AudioBuffer *) node)->phaseGroup;
		return GF_OK;
	case 7:
		info->name = "length";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_AudioBuffer *) node)->length;
		return GF_OK;
	case 8:
		info->name = "duration_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_AudioBuffer *) node)->duration_changed;
		return GF_OK;
	case 9:
		info->name = "isActive";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_AudioBuffer *) node)->isActive;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 AudioBuffer_get_field_index_by_name(char *name)
{
	if (!strcmp("loop", name)) return 0;
	if (!strcmp("pitch", name)) return 1;
	if (!strcmp("startTime", name)) return 2;
	if (!strcmp("stopTime", name)) return 3;
	if (!strcmp("children", name)) return 4;
	if (!strcmp("numChan", name)) return 5;
	if (!strcmp("phaseGroup", name)) return 6;
	if (!strcmp("length", name)) return 7;
	if (!strcmp("duration_changed", name)) return 8;
	if (!strcmp("isActive", name)) return 9;
	return -1;
	}
static Bool AudioBuffer_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 7;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 2:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 3:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 5:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(255);
		return 1;
	case 7:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *AudioBuffer_Create()
{
	M_AudioBuffer *p;
	GF_SAFEALLOC(p, M_AudioBuffer);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_AudioBuffer);

	/*default field values*/
	p->pitch = FLT2FIX(1);
	p->startTime = 0;
	p->stopTime = 0;
	p->numChan = 1;
	p->phaseGroup.vals = (SFInt32*)malloc(sizeof(SFInt32)*1);
	p->phaseGroup.count = 1;
	p->phaseGroup.vals[0] = 1;
	p->length = FLT2FIX(0.0);
	return (GF_Node *)p;
}


/*
	AudioClip Node deletion
*/

static void AudioClip_Del(GF_Node *node)
{
	M_AudioClip *p = (M_AudioClip *) node;
	gf_sg_sfstring_del(p->description);
	gf_sg_mfurl_del(p->url);
	gf_node_free((GF_Node *) p);
}

static const u16 AudioClip_Def2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 AudioClip_In2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 AudioClip_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7};
static const u16 AudioClip_Dyn2All[] = { 2};

static u32 AudioClip_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 6;
	case GF_SG_FIELD_CODING_DEF: return 6;
	case GF_SG_FIELD_CODING_OUT: return 8;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 8;
	}
}

static GF_Err AudioClip_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = AudioClip_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = AudioClip_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = AudioClip_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = AudioClip_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err AudioClip_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "description";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_AudioClip *) node)->description;
		return GF_OK;
	case 1:
		info->name = "loop";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_AudioClip *) node)->loop;
		return GF_OK;
	case 2:
		info->name = "pitch";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_AudioClip *) node)->pitch;
		return GF_OK;
	case 3:
		info->name = "startTime";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_AudioClip *) node)->startTime;
		return GF_OK;
	case 4:
		info->name = "stopTime";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_AudioClip *) node)->stopTime;
		return GF_OK;
	case 5:
		info->name = "url";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_AudioClip *) node)->url;
		return GF_OK;
	case 6:
		info->name = "duration_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_AudioClip *) node)->duration_changed;
		return GF_OK;
	case 7:
		info->name = "isActive";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_AudioClip *) node)->isActive;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 AudioClip_get_field_index_by_name(char *name)
{
	if (!strcmp("description", name)) return 0;
	if (!strcmp("loop", name)) return 1;
	if (!strcmp("pitch", name)) return 2;
	if (!strcmp("startTime", name)) return 3;
	if (!strcmp("stopTime", name)) return 4;
	if (!strcmp("url", name)) return 5;
	if (!strcmp("duration_changed", name)) return 6;
	if (!strcmp("isActive", name)) return 7;
	return -1;
	}
static Bool AudioClip_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 2:
		*AType = 7;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *AudioClip_Create()
{
	M_AudioClip *p;
	GF_SAFEALLOC(p, M_AudioClip);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_AudioClip);

	/*default field values*/
	p->pitch = FLT2FIX(1.0);
	p->startTime = 0;
	p->stopTime = 0;
	return (GF_Node *)p;
}


/*
	AudioDelay Node deletion
*/

static void AudioDelay_Del(GF_Node *node)
{
	M_AudioDelay *p = (M_AudioDelay *) node;
	gf_sg_mfint32_del(p->phaseGroup);
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 AudioDelay_Def2All[] = { 2, 3, 4, 5};
static const u16 AudioDelay_In2All[] = { 0, 1, 2, 3};
static const u16 AudioDelay_Out2All[] = { 2, 3};

static u32 AudioDelay_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 4;
	case GF_SG_FIELD_CODING_OUT: return 2;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 6;
	}
}

static GF_Err AudioDelay_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = AudioDelay_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = AudioDelay_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = AudioDelay_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err AudioDelay_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_AudioDelay *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFAudioNode;
		info->far_ptr = & ((M_AudioDelay *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_AudioDelay *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFAudioNode;
		info->far_ptr = & ((M_AudioDelay *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFAudioNode;
		info->far_ptr = & ((M_AudioDelay *)node)->children;
		return GF_OK;
	case 3:
		info->name = "delay";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_AudioDelay *) node)->delay;
		return GF_OK;
	case 4:
		info->name = "numChan";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_AudioDelay *) node)->numChan;
		return GF_OK;
	case 5:
		info->name = "phaseGroup";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_AudioDelay *) node)->phaseGroup;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 AudioDelay_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	if (!strcmp("delay", name)) return 3;
	if (!strcmp("numChan", name)) return 4;
	if (!strcmp("phaseGroup", name)) return 5;
	return -1;
	}
static Bool AudioDelay_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 4:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(255);
		return 1;
	case 5:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(255);
		return 1;
	default:
		return 0;
	}
}



GF_Node *AudioDelay_Create()
{
	M_AudioDelay *p;
	GF_SAFEALLOC(p, M_AudioDelay);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_AudioDelay);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->delay = 0;
	p->numChan = 1;
	return (GF_Node *)p;
}


/*
	AudioFX Node deletion
*/

static void AudioFX_Del(GF_Node *node)
{
	M_AudioFX *p = (M_AudioFX *) node;
	gf_sg_sfstring_del(p->orch);
	gf_sg_sfstring_del(p->score);
	gf_sg_mffloat_del(p->params);
	gf_sg_mfint32_del(p->phaseGroup);
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 AudioFX_Def2All[] = { 2, 3, 4, 5, 6, 7};
static const u16 AudioFX_In2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 AudioFX_Out2All[] = { 2, 3, 4, 5};
static const u16 AudioFX_Dyn2All[] = { 5};

static u32 AudioFX_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 6;
	case GF_SG_FIELD_CODING_DEF: return 6;
	case GF_SG_FIELD_CODING_OUT: return 4;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 8;
	}
}

static GF_Err AudioFX_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = AudioFX_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = AudioFX_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = AudioFX_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = AudioFX_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err AudioFX_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_AudioFX *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFAudioNode;
		info->far_ptr = & ((M_AudioFX *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_AudioFX *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFAudioNode;
		info->far_ptr = & ((M_AudioFX *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFAudioNode;
		info->far_ptr = & ((M_AudioFX *)node)->children;
		return GF_OK;
	case 3:
		info->name = "orch";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_AudioFX *) node)->orch;
		return GF_OK;
	case 4:
		info->name = "score";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_AudioFX *) node)->score;
		return GF_OK;
	case 5:
		info->name = "params";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_AudioFX *) node)->params;
		return GF_OK;
	case 6:
		info->name = "numChan";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_AudioFX *) node)->numChan;
		return GF_OK;
	case 7:
		info->name = "phaseGroup";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_AudioFX *) node)->phaseGroup;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 AudioFX_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	if (!strcmp("orch", name)) return 3;
	if (!strcmp("score", name)) return 4;
	if (!strcmp("params", name)) return 5;
	if (!strcmp("numChan", name)) return 6;
	if (!strcmp("phaseGroup", name)) return 7;
	return -1;
	}
static Bool AudioFX_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 5:
		*AType = 7;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 6:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(255);
		return 1;
	case 7:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(255);
		return 1;
	default:
		return 0;
	}
}



GF_Node *AudioFX_Create()
{
	M_AudioFX *p;
	GF_SAFEALLOC(p, M_AudioFX);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_AudioFX);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->numChan = 1;
	return (GF_Node *)p;
}


/*
	AudioMix Node deletion
*/

static void AudioMix_Del(GF_Node *node)
{
	M_AudioMix *p = (M_AudioMix *) node;
	gf_sg_mffloat_del(p->matrix);
	gf_sg_mfint32_del(p->phaseGroup);
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 AudioMix_Def2All[] = { 2, 3, 4, 5, 6};
static const u16 AudioMix_In2All[] = { 0, 1, 2, 3, 4};
static const u16 AudioMix_Out2All[] = { 2, 3, 4};
static const u16 AudioMix_Dyn2All[] = { 4};

static u32 AudioMix_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 5;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 7;
	}
}

static GF_Err AudioMix_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = AudioMix_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = AudioMix_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = AudioMix_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = AudioMix_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err AudioMix_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_AudioMix *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFAudioNode;
		info->far_ptr = & ((M_AudioMix *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_AudioMix *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFAudioNode;
		info->far_ptr = & ((M_AudioMix *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFAudioNode;
		info->far_ptr = & ((M_AudioMix *)node)->children;
		return GF_OK;
	case 3:
		info->name = "numInputs";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_AudioMix *) node)->numInputs;
		return GF_OK;
	case 4:
		info->name = "matrix";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_AudioMix *) node)->matrix;
		return GF_OK;
	case 5:
		info->name = "numChan";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_AudioMix *) node)->numChan;
		return GF_OK;
	case 6:
		info->name = "phaseGroup";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_AudioMix *) node)->phaseGroup;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 AudioMix_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	if (!strcmp("numInputs", name)) return 3;
	if (!strcmp("matrix", name)) return 4;
	if (!strcmp("numChan", name)) return 5;
	if (!strcmp("phaseGroup", name)) return 6;
	return -1;
	}
static Bool AudioMix_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 3:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 8;
		*b_min = FLT2FIX(1);
		*b_max = FLT2FIX(255);
		return 1;
	case 4:
		*AType = 7;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 5:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(255);
		return 1;
	case 6:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(255);
		return 1;
	default:
		return 0;
	}
}



GF_Node *AudioMix_Create()
{
	M_AudioMix *p;
	GF_SAFEALLOC(p, M_AudioMix);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_AudioMix);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->numInputs = 1;
	p->numChan = 1;
	return (GF_Node *)p;
}


/*
	AudioSource Node deletion
*/

static void AudioSource_Del(GF_Node *node)
{
	M_AudioSource *p = (M_AudioSource *) node;
	gf_sg_mfurl_del(p->url);
	gf_sg_mfint32_del(p->phaseGroup);
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 AudioSource_Def2All[] = { 2, 3, 4, 5, 6, 7, 8, 9};
static const u16 AudioSource_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7};
static const u16 AudioSource_Out2All[] = { 2, 3, 4, 5, 6, 7};
static const u16 AudioSource_Dyn2All[] = { 4, 5};

static u32 AudioSource_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 8;
	case GF_SG_FIELD_CODING_DEF: return 8;
	case GF_SG_FIELD_CODING_OUT: return 6;
	case GF_SG_FIELD_CODING_DYN: return 2;
	default:
		return 10;
	}
}

static GF_Err AudioSource_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = AudioSource_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = AudioSource_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = AudioSource_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = AudioSource_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err AudioSource_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_AudioSource *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFAudioNode;
		info->far_ptr = & ((M_AudioSource *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_AudioSource *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFAudioNode;
		info->far_ptr = & ((M_AudioSource *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFAudioNode;
		info->far_ptr = & ((M_AudioSource *)node)->children;
		return GF_OK;
	case 3:
		info->name = "url";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_AudioSource *) node)->url;
		return GF_OK;
	case 4:
		info->name = "pitch";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_AudioSource *) node)->pitch;
		return GF_OK;
	case 5:
		info->name = "speed";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_AudioSource *) node)->speed;
		return GF_OK;
	case 6:
		info->name = "startTime";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_AudioSource *) node)->startTime;
		return GF_OK;
	case 7:
		info->name = "stopTime";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_AudioSource *) node)->stopTime;
		return GF_OK;
	case 8:
		info->name = "numChan";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_AudioSource *) node)->numChan;
		return GF_OK;
	case 9:
		info->name = "phaseGroup";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_AudioSource *) node)->phaseGroup;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 AudioSource_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	if (!strcmp("url", name)) return 3;
	if (!strcmp("pitch", name)) return 4;
	if (!strcmp("speed", name)) return 5;
	if (!strcmp("startTime", name)) return 6;
	if (!strcmp("stopTime", name)) return 7;
	if (!strcmp("numChan", name)) return 8;
	if (!strcmp("phaseGroup", name)) return 9;
	return -1;
	}
static Bool AudioSource_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 4:
		*AType = 7;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 5:
		*AType = 7;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 8:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(255);
		return 1;
	case 9:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(255);
		return 1;
	default:
		return 0;
	}
}



GF_Node *AudioSource_Create()
{
	M_AudioSource *p;
	GF_SAFEALLOC(p, M_AudioSource);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_AudioSource);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->pitch = FLT2FIX(1);
	p->speed = FLT2FIX(1);
	p->startTime = 0;
	p->stopTime = 0;
	p->numChan = 1;
	return (GF_Node *)p;
}


/*
	AudioSwitch Node deletion
*/

static void AudioSwitch_Del(GF_Node *node)
{
	M_AudioSwitch *p = (M_AudioSwitch *) node;
	gf_sg_mfint32_del(p->whichChoice);
	gf_sg_mfint32_del(p->phaseGroup);
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 AudioSwitch_Def2All[] = { 2, 3, 4, 5};
static const u16 AudioSwitch_In2All[] = { 0, 1, 2, 3};
static const u16 AudioSwitch_Out2All[] = { 2, 3};

static u32 AudioSwitch_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 4;
	case GF_SG_FIELD_CODING_OUT: return 2;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 6;
	}
}

static GF_Err AudioSwitch_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = AudioSwitch_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = AudioSwitch_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = AudioSwitch_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err AudioSwitch_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_AudioSwitch *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFAudioNode;
		info->far_ptr = & ((M_AudioSwitch *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_AudioSwitch *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFAudioNode;
		info->far_ptr = & ((M_AudioSwitch *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFAudioNode;
		info->far_ptr = & ((M_AudioSwitch *)node)->children;
		return GF_OK;
	case 3:
		info->name = "whichChoice";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_AudioSwitch *) node)->whichChoice;
		return GF_OK;
	case 4:
		info->name = "numChan";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_AudioSwitch *) node)->numChan;
		return GF_OK;
	case 5:
		info->name = "phaseGroup";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_AudioSwitch *) node)->phaseGroup;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 AudioSwitch_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	if (!strcmp("whichChoice", name)) return 3;
	if (!strcmp("numChan", name)) return 4;
	if (!strcmp("phaseGroup", name)) return 5;
	return -1;
	}
static Bool AudioSwitch_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 3:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 1;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 4:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(255);
		return 1;
	case 5:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(255);
		return 1;
	default:
		return 0;
	}
}



GF_Node *AudioSwitch_Create()
{
	M_AudioSwitch *p;
	GF_SAFEALLOC(p, M_AudioSwitch);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_AudioSwitch);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->numChan = 1;
	return (GF_Node *)p;
}


/*
	Background Node deletion
*/

static void Background_Del(GF_Node *node)
{
	M_Background *p = (M_Background *) node;
	gf_sg_mffloat_del(p->groundAngle);
	gf_sg_mfcolor_del(p->groundColor);
	gf_sg_mfurl_del(p->backUrl);
	gf_sg_mfurl_del(p->bottomUrl);
	gf_sg_mfurl_del(p->frontUrl);
	gf_sg_mfurl_del(p->leftUrl);
	gf_sg_mfurl_del(p->rightUrl);
	gf_sg_mfurl_del(p->topUrl);
	gf_sg_mffloat_del(p->skyAngle);
	gf_sg_mfcolor_del(p->skyColor);
	gf_node_free((GF_Node *) p);
}

static const u16 Background_Def2All[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
static const u16 Background_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
static const u16 Background_Out2All[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
static const u16 Background_Dyn2All[] = { 1, 2, 9, 10};

static u32 Background_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 11;
	case GF_SG_FIELD_CODING_DEF: return 10;
	case GF_SG_FIELD_CODING_OUT: return 11;
	case GF_SG_FIELD_CODING_DYN: return 4;
	default:
		return 12;
	}
}

static GF_Err Background_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Background_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Background_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Background_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Background_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Background_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_bind";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Background *)node)->on_set_bind;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Background *) node)->set_bind;
		return GF_OK;
	case 1:
		info->name = "groundAngle";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_Background *) node)->groundAngle;
		return GF_OK;
	case 2:
		info->name = "groundColor";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFCOLOR;
		info->far_ptr = & ((M_Background *) node)->groundColor;
		return GF_OK;
	case 3:
		info->name = "backUrl";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_Background *) node)->backUrl;
		return GF_OK;
	case 4:
		info->name = "bottomUrl";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_Background *) node)->bottomUrl;
		return GF_OK;
	case 5:
		info->name = "frontUrl";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_Background *) node)->frontUrl;
		return GF_OK;
	case 6:
		info->name = "leftUrl";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_Background *) node)->leftUrl;
		return GF_OK;
	case 7:
		info->name = "rightUrl";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_Background *) node)->rightUrl;
		return GF_OK;
	case 8:
		info->name = "topUrl";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_Background *) node)->topUrl;
		return GF_OK;
	case 9:
		info->name = "skyAngle";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_Background *) node)->skyAngle;
		return GF_OK;
	case 10:
		info->name = "skyColor";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFCOLOR;
		info->far_ptr = & ((M_Background *) node)->skyColor;
		return GF_OK;
	case 11:
		info->name = "isBound";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Background *) node)->isBound;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Background_get_field_index_by_name(char *name)
{
	if (!strcmp("set_bind", name)) return 0;
	if (!strcmp("groundAngle", name)) return 1;
	if (!strcmp("groundColor", name)) return 2;
	if (!strcmp("backUrl", name)) return 3;
	if (!strcmp("bottomUrl", name)) return 4;
	if (!strcmp("frontUrl", name)) return 5;
	if (!strcmp("leftUrl", name)) return 6;
	if (!strcmp("rightUrl", name)) return 7;
	if (!strcmp("topUrl", name)) return 8;
	if (!strcmp("skyAngle", name)) return 9;
	if (!strcmp("skyColor", name)) return 10;
	if (!strcmp("isBound", name)) return 11;
	return -1;
	}
static Bool Background_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 8;
		*QType = 6;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1.5707963);
		return 1;
	case 2:
		*AType = 4;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 9:
		*AType = 8;
		*QType = 6;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(3.14159265);
		return 1;
	case 10:
		*AType = 4;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	default:
		return 0;
	}
}



GF_Node *Background_Create()
{
	M_Background *p;
	GF_SAFEALLOC(p, M_Background);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Background);

	/*default field values*/
	p->skyColor.vals = (SFColor*)malloc(sizeof(SFColor)*1);
	p->skyColor.count = 1;
	p->skyColor.vals[0].red = FLT2FIX(0);
	p->skyColor.vals[0].green = FLT2FIX(0);
	p->skyColor.vals[0].blue = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	Background2D Node deletion
*/

static void Background2D_Del(GF_Node *node)
{
	M_Background2D *p = (M_Background2D *) node;
	gf_sg_mfurl_del(p->url);
	gf_node_free((GF_Node *) p);
}

static const u16 Background2D_Def2All[] = { 1, 2};
static const u16 Background2D_In2All[] = { 0, 1, 2};
static const u16 Background2D_Out2All[] = { 1, 2, 3};
static const u16 Background2D_Dyn2All[] = { 1};

static u32 Background2D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 4;
	}
}

static GF_Err Background2D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Background2D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Background2D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Background2D_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Background2D_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Background2D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_bind";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Background2D *)node)->on_set_bind;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Background2D *) node)->set_bind;
		return GF_OK;
	case 1:
		info->name = "backColor";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFCOLOR;
		info->far_ptr = & ((M_Background2D *) node)->backColor;
		return GF_OK;
	case 2:
		info->name = "url";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_Background2D *) node)->url;
		return GF_OK;
	case 3:
		info->name = "isBound";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Background2D *) node)->isBound;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Background2D_get_field_index_by_name(char *name)
{
	if (!strcmp("set_bind", name)) return 0;
	if (!strcmp("backColor", name)) return 1;
	if (!strcmp("url", name)) return 2;
	if (!strcmp("isBound", name)) return 3;
	return -1;
	}
static Bool Background2D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 4;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	default:
		return 0;
	}
}



GF_Node *Background2D_Create()
{
	M_Background2D *p;
	GF_SAFEALLOC(p, M_Background2D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Background2D);

	/*default field values*/
	p->backColor.red = FLT2FIX(0);
	p->backColor.green = FLT2FIX(0);
	p->backColor.blue = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	Billboard Node deletion
*/

static void Billboard_Del(GF_Node *node)
{
	M_Billboard *p = (M_Billboard *) node;
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 Billboard_Def2All[] = { 2, 3};
static const u16 Billboard_In2All[] = { 0, 1, 2, 3};
static const u16 Billboard_Out2All[] = { 2, 3};
static const u16 Billboard_Dyn2All[] = { 3};

static u32 Billboard_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 2;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 4;
	}
}

static GF_Err Billboard_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Billboard_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Billboard_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Billboard_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Billboard_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Billboard_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Billboard *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_Billboard *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Billboard *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_Billboard *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_Billboard *)node)->children;
		return GF_OK;
	case 3:
		info->name = "axisOfRotation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_Billboard *) node)->axisOfRotation;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Billboard_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	if (!strcmp("axisOfRotation", name)) return 3;
	return -1;
	}
static Bool Billboard_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 3:
		*AType = 9;
		*QType = 9;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Billboard_Create()
{
	M_Billboard *p;
	GF_SAFEALLOC(p, M_Billboard);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Billboard);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->axisOfRotation.x = FLT2FIX(0);
	p->axisOfRotation.y = FLT2FIX(1);
	p->axisOfRotation.z = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	Bitmap Node deletion
*/

static void Bitmap_Del(GF_Node *node)
{
	M_Bitmap *p = (M_Bitmap *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 Bitmap_Def2All[] = { 0};
static const u16 Bitmap_In2All[] = { 0};
static const u16 Bitmap_Out2All[] = { 0};
static const u16 Bitmap_Dyn2All[] = { 0};

static u32 Bitmap_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 1;
	case GF_SG_FIELD_CODING_DEF: return 1;
	case GF_SG_FIELD_CODING_OUT: return 1;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 1;
	}
}

static GF_Err Bitmap_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Bitmap_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Bitmap_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Bitmap_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Bitmap_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Bitmap_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "scale";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_Bitmap *) node)->scale;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Bitmap_get_field_index_by_name(char *name)
{
	if (!strcmp("scale", name)) return 0;
	return -1;
	}
static Bool Bitmap_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 12;
		*QType = 12;
		*b_min = FLT2FIX(-1);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Bitmap_Create()
{
	M_Bitmap *p;
	GF_SAFEALLOC(p, M_Bitmap);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Bitmap);

	/*default field values*/
	p->scale.x = FLT2FIX(-1);
	p->scale.y = FLT2FIX(-1);
	return (GF_Node *)p;
}


/*
	Box Node deletion
*/

static void Box_Del(GF_Node *node)
{
	M_Box *p = (M_Box *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 Box_Def2All[] = { 0};

static u32 Box_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 0;
	case GF_SG_FIELD_CODING_DEF: return 1;
	case GF_SG_FIELD_CODING_OUT: return 0;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 1;
	}
}

static GF_Err Box_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_DEF:
		*allField = Box_Def2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Box_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "size";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_Box *) node)->size;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Box_get_field_index_by_name(char *name)
{
	if (!strcmp("size", name)) return 0;
	return -1;
	}
static Bool Box_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 0;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Box_Create()
{
	M_Box *p;
	GF_SAFEALLOC(p, M_Box);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Box);

	/*default field values*/
	p->size.x = FLT2FIX(2);
	p->size.y = FLT2FIX(2);
	p->size.z = FLT2FIX(2);
	return (GF_Node *)p;
}


/*
	Circle Node deletion
*/

static void Circle_Del(GF_Node *node)
{
	M_Circle *p = (M_Circle *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 Circle_Def2All[] = { 0};
static const u16 Circle_In2All[] = { 0};
static const u16 Circle_Out2All[] = { 0};
static const u16 Circle_Dyn2All[] = { 0};

static u32 Circle_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 1;
	case GF_SG_FIELD_CODING_DEF: return 1;
	case GF_SG_FIELD_CODING_OUT: return 1;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 1;
	}
}

static GF_Err Circle_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Circle_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Circle_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Circle_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Circle_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Circle_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "radius";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Circle *) node)->radius;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Circle_get_field_index_by_name(char *name)
{
	if (!strcmp("radius", name)) return 0;
	return -1;
	}
static Bool Circle_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 7;
		*QType = 12;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Circle_Create()
{
	M_Circle *p;
	GF_SAFEALLOC(p, M_Circle);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Circle);

	/*default field values*/
	p->radius = FLT2FIX(1);
	return (GF_Node *)p;
}


/*
	Collision Node deletion
*/

static void Collision_Del(GF_Node *node)
{
	M_Collision *p = (M_Collision *) node;
	gf_node_unregister((GF_Node *) p->proxy, (GF_Node *) p);	
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 Collision_Def2All[] = { 2, 3, 4};
static const u16 Collision_In2All[] = { 0, 1, 2, 3};
static const u16 Collision_Out2All[] = { 2, 3, 5};

static u32 Collision_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 3;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 6;
	}
}

static GF_Err Collision_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Collision_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Collision_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Collision_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Collision_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Collision *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_Collision *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Collision *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_Collision *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_Collision *)node)->children;
		return GF_OK;
	case 3:
		info->name = "collide";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Collision *) node)->collide;
		return GF_OK;
	case 4:
		info->name = "proxy";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_Collision *)node)->proxy;
		return GF_OK;
	case 5:
		info->name = "collideTime";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_Collision *) node)->collideTime;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Collision_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	if (!strcmp("collide", name)) return 3;
	if (!strcmp("proxy", name)) return 4;
	if (!strcmp("collideTime", name)) return 5;
	return -1;
	}
static Bool Collision_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *Collision_Create()
{
	M_Collision *p;
	GF_SAFEALLOC(p, M_Collision);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Collision);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->collide = 1;
	return (GF_Node *)p;
}


/*
	Color Node deletion
*/

static void Color_Del(GF_Node *node)
{
	M_Color *p = (M_Color *) node;
	gf_sg_mfcolor_del(p->color);
	gf_node_free((GF_Node *) p);
}

static const u16 Color_Def2All[] = { 0};
static const u16 Color_In2All[] = { 0};
static const u16 Color_Out2All[] = { 0};
static const u16 Color_Dyn2All[] = { 0};

static u32 Color_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 1;
	case GF_SG_FIELD_CODING_DEF: return 1;
	case GF_SG_FIELD_CODING_OUT: return 1;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 1;
	}
}

static GF_Err Color_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Color_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Color_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Color_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Color_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Color_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "color";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFCOLOR;
		info->far_ptr = & ((M_Color *) node)->color;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Color_get_field_index_by_name(char *name)
{
	if (!strcmp("color", name)) return 0;
	return -1;
	}
static Bool Color_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 4;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	default:
		return 0;
	}
}



GF_Node *Color_Create()
{
	M_Color *p;
	GF_SAFEALLOC(p, M_Color);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Color);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	ColorInterpolator Node deletion
*/

static void ColorInterpolator_Del(GF_Node *node)
{
	M_ColorInterpolator *p = (M_ColorInterpolator *) node;
	gf_sg_mffloat_del(p->key);
	gf_sg_mfcolor_del(p->keyValue);
	gf_node_free((GF_Node *) p);
}

static const u16 ColorInterpolator_Def2All[] = { 1, 2};
static const u16 ColorInterpolator_In2All[] = { 0, 1, 2};
static const u16 ColorInterpolator_Out2All[] = { 1, 2, 3};

static u32 ColorInterpolator_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err ColorInterpolator_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = ColorInterpolator_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = ColorInterpolator_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = ColorInterpolator_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err ColorInterpolator_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_fraction";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_ColorInterpolator *)node)->on_set_fraction;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ColorInterpolator *) node)->set_fraction;
		return GF_OK;
	case 1:
		info->name = "key";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_ColorInterpolator *) node)->key;
		return GF_OK;
	case 2:
		info->name = "keyValue";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFCOLOR;
		info->far_ptr = & ((M_ColorInterpolator *) node)->keyValue;
		return GF_OK;
	case 3:
		info->name = "value_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFCOLOR;
		info->far_ptr = & ((M_ColorInterpolator *) node)->value_changed;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 ColorInterpolator_get_field_index_by_name(char *name)
{
	if (!strcmp("set_fraction", name)) return 0;
	if (!strcmp("key", name)) return 1;
	if (!strcmp("keyValue", name)) return 2;
	if (!strcmp("value_changed", name)) return 3;
	return -1;
	}
static Bool ColorInterpolator_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 2:
		*AType = 0;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	default:
		return 0;
	}
}



GF_Node *ColorInterpolator_Create()
{
	M_ColorInterpolator *p;
	GF_SAFEALLOC(p, M_ColorInterpolator);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_ColorInterpolator);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	CompositeTexture2D Node deletion
*/

static void CompositeTexture2D_Del(GF_Node *node)
{
	M_CompositeTexture2D *p = (M_CompositeTexture2D *) node;
	gf_node_unregister((GF_Node *) p->background, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->viewport, (GF_Node *) p);	
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 CompositeTexture2D_Def2All[] = { 2, 3, 4, 5, 6, 7};
static const u16 CompositeTexture2D_In2All[] = { 0, 1, 2, 3, 4, 5, 6};
static const u16 CompositeTexture2D_Out2All[] = { 2, 3, 4, 5, 6};

static u32 CompositeTexture2D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 7;
	case GF_SG_FIELD_CODING_DEF: return 6;
	case GF_SG_FIELD_CODING_OUT: return 5;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 8;
	}
}

static GF_Err CompositeTexture2D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = CompositeTexture2D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = CompositeTexture2D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = CompositeTexture2D_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err CompositeTexture2D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_CompositeTexture2D *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_CompositeTexture2D *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_CompositeTexture2D *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_CompositeTexture2D *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_CompositeTexture2D *)node)->children;
		return GF_OK;
	case 3:
		info->name = "pixelWidth";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_CompositeTexture2D *) node)->pixelWidth;
		return GF_OK;
	case 4:
		info->name = "pixelHeight";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_CompositeTexture2D *) node)->pixelHeight;
		return GF_OK;
	case 5:
		info->name = "background";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFBackground2DNode;
		info->far_ptr = & ((M_CompositeTexture2D *)node)->background;
		return GF_OK;
	case 6:
		info->name = "viewport";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFViewportNode;
		info->far_ptr = & ((M_CompositeTexture2D *)node)->viewport;
		return GF_OK;
	case 7:
		info->name = "repeatSandT";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_CompositeTexture2D *) node)->repeatSandT;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 CompositeTexture2D_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	if (!strcmp("pixelWidth", name)) return 3;
	if (!strcmp("pixelHeight", name)) return 4;
	if (!strcmp("background", name)) return 5;
	if (!strcmp("viewport", name)) return 6;
	if (!strcmp("repeatSandT", name)) return 7;
	return -1;
	}
static Bool CompositeTexture2D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 3:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 16;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX /*WARNING: modified to allow 16.16 fixed point version!!*/;
		return 1;
	case 4:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 16;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX /*WARNING: modified to allow 16.16 fixed point version!!*/;
		return 1;
	case 7:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 2;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(3);
		return 1;
	default:
		return 0;
	}
}



GF_Node *CompositeTexture2D_Create()
{
	M_CompositeTexture2D *p;
	GF_SAFEALLOC(p, M_CompositeTexture2D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_CompositeTexture2D);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->pixelWidth = -1;
	p->pixelHeight = -1;
	p->repeatSandT = 3;
	return (GF_Node *)p;
}


/*
	CompositeTexture3D Node deletion
*/

static void CompositeTexture3D_Del(GF_Node *node)
{
	M_CompositeTexture3D *p = (M_CompositeTexture3D *) node;
	gf_node_unregister((GF_Node *) p->background, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->fog, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->navigationInfo, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->viewpoint, (GF_Node *) p);	
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 CompositeTexture3D_Def2All[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10};
static const u16 CompositeTexture3D_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};
static const u16 CompositeTexture3D_Out2All[] = { 2, 3, 4, 5, 6, 7, 8};

static u32 CompositeTexture3D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 9;
	case GF_SG_FIELD_CODING_DEF: return 9;
	case GF_SG_FIELD_CODING_OUT: return 7;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 11;
	}
}

static GF_Err CompositeTexture3D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = CompositeTexture3D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = CompositeTexture3D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = CompositeTexture3D_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err CompositeTexture3D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_CompositeTexture3D *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_CompositeTexture3D *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_CompositeTexture3D *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_CompositeTexture3D *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_CompositeTexture3D *)node)->children;
		return GF_OK;
	case 3:
		info->name = "pixelWidth";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_CompositeTexture3D *) node)->pixelWidth;
		return GF_OK;
	case 4:
		info->name = "pixelHeight";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_CompositeTexture3D *) node)->pixelHeight;
		return GF_OK;
	case 5:
		info->name = "background";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFBackground3DNode;
		info->far_ptr = & ((M_CompositeTexture3D *)node)->background;
		return GF_OK;
	case 6:
		info->name = "fog";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFFogNode;
		info->far_ptr = & ((M_CompositeTexture3D *)node)->fog;
		return GF_OK;
	case 7:
		info->name = "navigationInfo";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFNavigationInfoNode;
		info->far_ptr = & ((M_CompositeTexture3D *)node)->navigationInfo;
		return GF_OK;
	case 8:
		info->name = "viewpoint";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFViewpointNode;
		info->far_ptr = & ((M_CompositeTexture3D *)node)->viewpoint;
		return GF_OK;
	case 9:
		info->name = "repeatS";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_CompositeTexture3D *) node)->repeatS;
		return GF_OK;
	case 10:
		info->name = "repeatT";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_CompositeTexture3D *) node)->repeatT;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 CompositeTexture3D_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	if (!strcmp("pixelWidth", name)) return 3;
	if (!strcmp("pixelHeight", name)) return 4;
	if (!strcmp("background", name)) return 5;
	if (!strcmp("fog", name)) return 6;
	if (!strcmp("navigationInfo", name)) return 7;
	if (!strcmp("viewpoint", name)) return 8;
	if (!strcmp("repeatS", name)) return 9;
	if (!strcmp("repeatT", name)) return 10;
	return -1;
	}
static Bool CompositeTexture3D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 3:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 16;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX /*WARNING: modified to allow 16.16 fixed point version!!*/;
		return 1;
	case 4:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 16;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX /*WARNING: modified to allow 16.16 fixed point version!!*/;
		return 1;
	default:
		return 0;
	}
}



GF_Node *CompositeTexture3D_Create()
{
	M_CompositeTexture3D *p;
	GF_SAFEALLOC(p, M_CompositeTexture3D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_CompositeTexture3D);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->pixelWidth = -1;
	p->pixelHeight = -1;
	p->repeatS = 1;
	p->repeatT = 1;
	return (GF_Node *)p;
}


/*
	Conditional Node deletion
*/

static void Conditional_Del(GF_Node *node)
{
	M_Conditional *p = (M_Conditional *) node;
	gf_sg_sfcommand_del(p->buffer);
	gf_node_free((GF_Node *) p);
}

static const u16 Conditional_Def2All[] = { 2};
static const u16 Conditional_In2All[] = { 0, 1, 2};
static const u16 Conditional_Out2All[] = { 2, 3};

static u32 Conditional_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 1;
	case GF_SG_FIELD_CODING_OUT: return 2;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err Conditional_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Conditional_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Conditional_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Conditional_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Conditional_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "activate";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Conditional *)node)->on_activate;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Conditional *) node)->activate;
		return GF_OK;
	case 1:
		info->name = "reverseActivate";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Conditional *)node)->on_reverseActivate;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Conditional *) node)->reverseActivate;
		return GF_OK;
	case 2:
		info->name = "buffer";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFCOMMANDBUFFER;
		info->far_ptr = & ((M_Conditional *) node)->buffer;
		return GF_OK;
	case 3:
		info->name = "isActive";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Conditional *) node)->isActive;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Conditional_get_field_index_by_name(char *name)
{
	if (!strcmp("activate", name)) return 0;
	if (!strcmp("reverseActivate", name)) return 1;
	if (!strcmp("buffer", name)) return 2;
	if (!strcmp("isActive", name)) return 3;
	return -1;
	}
static Bool Conditional_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *Conditional_Create()
{
	M_Conditional *p;
	GF_SAFEALLOC(p, M_Conditional);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Conditional);
	p->buffer.commandList = gf_list_new();	

	/*default field values*/
	return (GF_Node *)p;
}


/*
	Cone Node deletion
*/

static void Cone_Del(GF_Node *node)
{
	M_Cone *p = (M_Cone *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 Cone_Def2All[] = { 0, 1, 2, 3};

static u32 Cone_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 0;
	case GF_SG_FIELD_CODING_DEF: return 4;
	case GF_SG_FIELD_CODING_OUT: return 0;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err Cone_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_DEF:
		*allField = Cone_Def2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Cone_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "bottomRadius";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Cone *) node)->bottomRadius;
		return GF_OK;
	case 1:
		info->name = "height";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Cone *) node)->height;
		return GF_OK;
	case 2:
		info->name = "side";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Cone *) node)->side;
		return GF_OK;
	case 3:
		info->name = "bottom";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Cone *) node)->bottom;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Cone_get_field_index_by_name(char *name)
{
	if (!strcmp("bottomRadius", name)) return 0;
	if (!strcmp("height", name)) return 1;
	if (!strcmp("side", name)) return 2;
	if (!strcmp("bottom", name)) return 3;
	return -1;
	}
static Bool Cone_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 0;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 1:
		*AType = 0;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Cone_Create()
{
	M_Cone *p;
	GF_SAFEALLOC(p, M_Cone);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Cone);

	/*default field values*/
	p->bottomRadius = FLT2FIX(1);
	p->height = FLT2FIX(2);
	p->side = 1;
	p->bottom = 1;
	return (GF_Node *)p;
}


/*
	Coordinate Node deletion
*/

static void Coordinate_Del(GF_Node *node)
{
	M_Coordinate *p = (M_Coordinate *) node;
	gf_sg_mfvec3f_del(p->point);
	gf_node_free((GF_Node *) p);
}

static const u16 Coordinate_Def2All[] = { 0};
static const u16 Coordinate_In2All[] = { 0};
static const u16 Coordinate_Out2All[] = { 0};
static const u16 Coordinate_Dyn2All[] = { 0};

static u32 Coordinate_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 1;
	case GF_SG_FIELD_CODING_DEF: return 1;
	case GF_SG_FIELD_CODING_OUT: return 1;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 1;
	}
}

static GF_Err Coordinate_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Coordinate_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Coordinate_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Coordinate_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Coordinate_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Coordinate_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "point";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC3F;
		info->far_ptr = & ((M_Coordinate *) node)->point;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Coordinate_get_field_index_by_name(char *name)
{
	if (!strcmp("point", name)) return 0;
	return -1;
	}
static Bool Coordinate_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 1;
		*QType = 1;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Coordinate_Create()
{
	M_Coordinate *p;
	GF_SAFEALLOC(p, M_Coordinate);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Coordinate);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	Coordinate2D Node deletion
*/

static void Coordinate2D_Del(GF_Node *node)
{
	M_Coordinate2D *p = (M_Coordinate2D *) node;
	gf_sg_mfvec2f_del(p->point);
	gf_node_free((GF_Node *) p);
}

static const u16 Coordinate2D_Def2All[] = { 0};
static const u16 Coordinate2D_In2All[] = { 0};
static const u16 Coordinate2D_Out2All[] = { 0};
static const u16 Coordinate2D_Dyn2All[] = { 0};

static u32 Coordinate2D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 1;
	case GF_SG_FIELD_CODING_DEF: return 1;
	case GF_SG_FIELD_CODING_OUT: return 1;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 1;
	}
}

static GF_Err Coordinate2D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Coordinate2D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Coordinate2D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Coordinate2D_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Coordinate2D_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Coordinate2D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "point";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC2F;
		info->far_ptr = & ((M_Coordinate2D *) node)->point;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Coordinate2D_get_field_index_by_name(char *name)
{
	if (!strcmp("point", name)) return 0;
	return -1;
	}
static Bool Coordinate2D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 2;
		*QType = 2;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Coordinate2D_Create()
{
	M_Coordinate2D *p;
	GF_SAFEALLOC(p, M_Coordinate2D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Coordinate2D);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	CoordinateInterpolator Node deletion
*/

static void CoordinateInterpolator_Del(GF_Node *node)
{
	M_CoordinateInterpolator *p = (M_CoordinateInterpolator *) node;
	gf_sg_mffloat_del(p->key);
	gf_sg_mfvec3f_del(p->keyValue);
	gf_sg_mfvec3f_del(p->value_changed);
	gf_node_free((GF_Node *) p);
}

static const u16 CoordinateInterpolator_Def2All[] = { 1, 2};
static const u16 CoordinateInterpolator_In2All[] = { 0, 1, 2};
static const u16 CoordinateInterpolator_Out2All[] = { 1, 2, 3};

static u32 CoordinateInterpolator_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err CoordinateInterpolator_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = CoordinateInterpolator_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = CoordinateInterpolator_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = CoordinateInterpolator_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err CoordinateInterpolator_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_fraction";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_CoordinateInterpolator *)node)->on_set_fraction;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_CoordinateInterpolator *) node)->set_fraction;
		return GF_OK;
	case 1:
		info->name = "key";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_CoordinateInterpolator *) node)->key;
		return GF_OK;
	case 2:
		info->name = "keyValue";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC3F;
		info->far_ptr = & ((M_CoordinateInterpolator *) node)->keyValue;
		return GF_OK;
	case 3:
		info->name = "value_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_MFVEC3F;
		info->far_ptr = & ((M_CoordinateInterpolator *) node)->value_changed;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 CoordinateInterpolator_get_field_index_by_name(char *name)
{
	if (!strcmp("set_fraction", name)) return 0;
	if (!strcmp("key", name)) return 1;
	if (!strcmp("keyValue", name)) return 2;
	if (!strcmp("value_changed", name)) return 3;
	return -1;
	}
static Bool CoordinateInterpolator_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 2:
		*AType = 0;
		*QType = 1;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *CoordinateInterpolator_Create()
{
	M_CoordinateInterpolator *p;
	GF_SAFEALLOC(p, M_CoordinateInterpolator);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_CoordinateInterpolator);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	CoordinateInterpolator2D Node deletion
*/

static void CoordinateInterpolator2D_Del(GF_Node *node)
{
	M_CoordinateInterpolator2D *p = (M_CoordinateInterpolator2D *) node;
	gf_sg_mffloat_del(p->key);
	gf_sg_mfvec2f_del(p->keyValue);
	gf_sg_mfvec2f_del(p->value_changed);
	gf_node_free((GF_Node *) p);
}

static const u16 CoordinateInterpolator2D_Def2All[] = { 1, 2};
static const u16 CoordinateInterpolator2D_In2All[] = { 0, 1, 2};
static const u16 CoordinateInterpolator2D_Out2All[] = { 1, 2, 3};

static u32 CoordinateInterpolator2D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err CoordinateInterpolator2D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = CoordinateInterpolator2D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = CoordinateInterpolator2D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = CoordinateInterpolator2D_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err CoordinateInterpolator2D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_fraction";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_CoordinateInterpolator2D *)node)->on_set_fraction;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_CoordinateInterpolator2D *) node)->set_fraction;
		return GF_OK;
	case 1:
		info->name = "key";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_CoordinateInterpolator2D *) node)->key;
		return GF_OK;
	case 2:
		info->name = "keyValue";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC2F;
		info->far_ptr = & ((M_CoordinateInterpolator2D *) node)->keyValue;
		return GF_OK;
	case 3:
		info->name = "value_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_MFVEC2F;
		info->far_ptr = & ((M_CoordinateInterpolator2D *) node)->value_changed;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 CoordinateInterpolator2D_get_field_index_by_name(char *name)
{
	if (!strcmp("set_fraction", name)) return 0;
	if (!strcmp("key", name)) return 1;
	if (!strcmp("keyValue", name)) return 2;
	if (!strcmp("value_changed", name)) return 3;
	return -1;
	}
static Bool CoordinateInterpolator2D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 2:
		*AType = 0;
		*QType = 2;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *CoordinateInterpolator2D_Create()
{
	M_CoordinateInterpolator2D *p;
	GF_SAFEALLOC(p, M_CoordinateInterpolator2D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_CoordinateInterpolator2D);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	Curve2D Node deletion
*/

static void Curve2D_Del(GF_Node *node)
{
	M_Curve2D *p = (M_Curve2D *) node;
	gf_node_unregister((GF_Node *) p->point, (GF_Node *) p);	
	gf_sg_mfint32_del(p->type);
	gf_node_free((GF_Node *) p);
}

static const u16 Curve2D_Def2All[] = { 0, 1, 2};
static const u16 Curve2D_In2All[] = { 0, 1, 2};
static const u16 Curve2D_Out2All[] = { 0, 1, 2};
static const u16 Curve2D_Dyn2All[] = { 1};

static u32 Curve2D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 3;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 3;
	}
}

static GF_Err Curve2D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Curve2D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Curve2D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Curve2D_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Curve2D_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Curve2D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "point";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFCoordinate2DNode;
		info->far_ptr = & ((M_Curve2D *)node)->point;
		return GF_OK;
	case 1:
		info->name = "fineness";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Curve2D *) node)->fineness;
		return GF_OK;
	case 2:
		info->name = "type";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_Curve2D *) node)->type;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Curve2D_get_field_index_by_name(char *name)
{
	if (!strcmp("point", name)) return 0;
	if (!strcmp("fineness", name)) return 1;
	if (!strcmp("type", name)) return 2;
	return -1;
	}
static Bool Curve2D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 7;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 2:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 2;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(3);
		return 1;
	default:
		return 0;
	}
}



GF_Node *Curve2D_Create()
{
	M_Curve2D *p;
	GF_SAFEALLOC(p, M_Curve2D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Curve2D);

	/*default field values*/
	p->fineness = FLT2FIX(0.5);
	return (GF_Node *)p;
}


/*
	Cylinder Node deletion
*/

static void Cylinder_Del(GF_Node *node)
{
	M_Cylinder *p = (M_Cylinder *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 Cylinder_Def2All[] = { 0, 1, 2, 3, 4};

static u32 Cylinder_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 0;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 0;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 5;
	}
}

static GF_Err Cylinder_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_DEF:
		*allField = Cylinder_Def2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Cylinder_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "bottom";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Cylinder *) node)->bottom;
		return GF_OK;
	case 1:
		info->name = "height";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Cylinder *) node)->height;
		return GF_OK;
	case 2:
		info->name = "radius";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Cylinder *) node)->radius;
		return GF_OK;
	case 3:
		info->name = "side";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Cylinder *) node)->side;
		return GF_OK;
	case 4:
		info->name = "top";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Cylinder *) node)->top;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Cylinder_get_field_index_by_name(char *name)
{
	if (!strcmp("bottom", name)) return 0;
	if (!strcmp("height", name)) return 1;
	if (!strcmp("radius", name)) return 2;
	if (!strcmp("side", name)) return 3;
	if (!strcmp("top", name)) return 4;
	return -1;
	}
static Bool Cylinder_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 2:
		*AType = 0;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Cylinder_Create()
{
	M_Cylinder *p;
	GF_SAFEALLOC(p, M_Cylinder);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Cylinder);

	/*default field values*/
	p->bottom = 1;
	p->height = FLT2FIX(2);
	p->radius = FLT2FIX(1);
	p->side = 1;
	p->top = 1;
	return (GF_Node *)p;
}


/*
	CylinderSensor Node deletion
*/

static void CylinderSensor_Del(GF_Node *node)
{
	M_CylinderSensor *p = (M_CylinderSensor *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 CylinderSensor_Def2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 CylinderSensor_In2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 CylinderSensor_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};

static u32 CylinderSensor_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 6;
	case GF_SG_FIELD_CODING_DEF: return 6;
	case GF_SG_FIELD_CODING_OUT: return 9;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 9;
	}
}

static GF_Err CylinderSensor_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = CylinderSensor_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = CylinderSensor_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = CylinderSensor_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err CylinderSensor_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "autoOffset";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_CylinderSensor *) node)->autoOffset;
		return GF_OK;
	case 1:
		info->name = "diskAngle";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_CylinderSensor *) node)->diskAngle;
		return GF_OK;
	case 2:
		info->name = "enabled";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_CylinderSensor *) node)->enabled;
		return GF_OK;
	case 3:
		info->name = "maxAngle";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_CylinderSensor *) node)->maxAngle;
		return GF_OK;
	case 4:
		info->name = "minAngle";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_CylinderSensor *) node)->minAngle;
		return GF_OK;
	case 5:
		info->name = "offset";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_CylinderSensor *) node)->offset;
		return GF_OK;
	case 6:
		info->name = "isActive";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_CylinderSensor *) node)->isActive;
		return GF_OK;
	case 7:
		info->name = "rotation_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFROTATION;
		info->far_ptr = & ((M_CylinderSensor *) node)->rotation_changed;
		return GF_OK;
	case 8:
		info->name = "trackPoint_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_CylinderSensor *) node)->trackPoint_changed;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 CylinderSensor_get_field_index_by_name(char *name)
{
	if (!strcmp("autoOffset", name)) return 0;
	if (!strcmp("diskAngle", name)) return 1;
	if (!strcmp("enabled", name)) return 2;
	if (!strcmp("maxAngle", name)) return 3;
	if (!strcmp("minAngle", name)) return 4;
	if (!strcmp("offset", name)) return 5;
	if (!strcmp("isActive", name)) return 6;
	if (!strcmp("rotation_changed", name)) return 7;
	if (!strcmp("trackPoint_changed", name)) return 8;
	return -1;
	}
static Bool CylinderSensor_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 6;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1.5707963);
		return 1;
	case 3:
		*AType = 0;
		*QType = 6;
		*b_min = FLT2FIX(-6.2831853);
		*b_max = FLT2FIX(6.2831853);
		return 1;
	case 4:
		*AType = 0;
		*QType = 6;
		*b_min = FLT2FIX(-6.2831853);
		*b_max = FLT2FIX(6.2831853);
		return 1;
	case 5:
		*AType = 0;
		*QType = 6;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(6.2831853);
		return 1;
	default:
		return 0;
	}
}



GF_Node *CylinderSensor_Create()
{
	M_CylinderSensor *p;
	GF_SAFEALLOC(p, M_CylinderSensor);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_CylinderSensor);

	/*default field values*/
	p->autoOffset = 1;
	p->diskAngle = FLT2FIX(0.262);
	p->enabled = 1;
	p->maxAngle = FLT2FIX(-1);
	p->minAngle = FLT2FIX(0);
	p->offset = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	DirectionalLight Node deletion
*/

static void DirectionalLight_Del(GF_Node *node)
{
	M_DirectionalLight *p = (M_DirectionalLight *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 DirectionalLight_Def2All[] = { 0, 1, 2, 3, 4};
static const u16 DirectionalLight_In2All[] = { 0, 1, 2, 3, 4};
static const u16 DirectionalLight_Out2All[] = { 0, 1, 2, 3, 4};
static const u16 DirectionalLight_Dyn2All[] = { 0, 1, 2, 3};

static u32 DirectionalLight_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 5;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 5;
	case GF_SG_FIELD_CODING_DYN: return 4;
	default:
		return 5;
	}
}

static GF_Err DirectionalLight_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = DirectionalLight_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = DirectionalLight_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = DirectionalLight_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = DirectionalLight_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err DirectionalLight_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "ambientIntensity";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_DirectionalLight *) node)->ambientIntensity;
		return GF_OK;
	case 1:
		info->name = "color";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFCOLOR;
		info->far_ptr = & ((M_DirectionalLight *) node)->color;
		return GF_OK;
	case 2:
		info->name = "direction";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_DirectionalLight *) node)->direction;
		return GF_OK;
	case 3:
		info->name = "intensity";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_DirectionalLight *) node)->intensity;
		return GF_OK;
	case 4:
		info->name = "on";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_DirectionalLight *) node)->on;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 DirectionalLight_get_field_index_by_name(char *name)
{
	if (!strcmp("ambientIntensity", name)) return 0;
	if (!strcmp("color", name)) return 1;
	if (!strcmp("direction", name)) return 2;
	if (!strcmp("intensity", name)) return 3;
	if (!strcmp("on", name)) return 4;
	return -1;
	}
static Bool DirectionalLight_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 8;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 1:
		*AType = 4;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 2:
		*AType = 9;
		*QType = 9;
		return 1;
	case 3:
		*AType = 8;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	default:
		return 0;
	}
}



GF_Node *DirectionalLight_Create()
{
	M_DirectionalLight *p;
	GF_SAFEALLOC(p, M_DirectionalLight);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_DirectionalLight);

	/*default field values*/
	p->ambientIntensity = FLT2FIX(0);
	p->color.red = FLT2FIX(1);
	p->color.green = FLT2FIX(1);
	p->color.blue = FLT2FIX(1);
	p->direction.x = FLT2FIX(0);
	p->direction.y = FLT2FIX(0);
	p->direction.z = FLT2FIX(-1);
	p->intensity = FLT2FIX(1);
	p->on = 1;
	return (GF_Node *)p;
}


/*
	DiscSensor Node deletion
*/

static void DiscSensor_Del(GF_Node *node)
{
	M_DiscSensor *p = (M_DiscSensor *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 DiscSensor_Def2All[] = { 0, 1, 2, 3, 4};
static const u16 DiscSensor_In2All[] = { 0, 1, 2, 3, 4};
static const u16 DiscSensor_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7};

static u32 DiscSensor_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 5;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 8;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 8;
	}
}

static GF_Err DiscSensor_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = DiscSensor_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = DiscSensor_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = DiscSensor_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err DiscSensor_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "autoOffset";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_DiscSensor *) node)->autoOffset;
		return GF_OK;
	case 1:
		info->name = "enabled";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_DiscSensor *) node)->enabled;
		return GF_OK;
	case 2:
		info->name = "maxAngle";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_DiscSensor *) node)->maxAngle;
		return GF_OK;
	case 3:
		info->name = "minAngle";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_DiscSensor *) node)->minAngle;
		return GF_OK;
	case 4:
		info->name = "offset";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_DiscSensor *) node)->offset;
		return GF_OK;
	case 5:
		info->name = "isActive";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_DiscSensor *) node)->isActive;
		return GF_OK;
	case 6:
		info->name = "rotation_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_DiscSensor *) node)->rotation_changed;
		return GF_OK;
	case 7:
		info->name = "trackPoint_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_DiscSensor *) node)->trackPoint_changed;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 DiscSensor_get_field_index_by_name(char *name)
{
	if (!strcmp("autoOffset", name)) return 0;
	if (!strcmp("enabled", name)) return 1;
	if (!strcmp("maxAngle", name)) return 2;
	if (!strcmp("minAngle", name)) return 3;
	if (!strcmp("offset", name)) return 4;
	if (!strcmp("isActive", name)) return 5;
	if (!strcmp("rotation_changed", name)) return 6;
	if (!strcmp("trackPoint_changed", name)) return 7;
	return -1;
	}
static Bool DiscSensor_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 2:
		*AType = 0;
		*QType = 6;
		*b_min = FLT2FIX(-6.2831853);
		*b_max = FLT2FIX(6.2831853);
		return 1;
	case 3:
		*AType = 0;
		*QType = 6;
		*b_min = FLT2FIX(-6.2831853);
		*b_max = FLT2FIX(6.2831853);
		return 1;
	case 4:
		*AType = 0;
		*QType = 6;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(6.2831853);
		return 1;
	default:
		return 0;
	}
}



GF_Node *DiscSensor_Create()
{
	M_DiscSensor *p;
	GF_SAFEALLOC(p, M_DiscSensor);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_DiscSensor);

	/*default field values*/
	p->autoOffset = 1;
	p->enabled = 1;
	p->maxAngle = FLT2FIX(-1);
	p->minAngle = FLT2FIX(0);
	p->offset = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	ElevationGrid Node deletion
*/

static void ElevationGrid_Del(GF_Node *node)
{
	M_ElevationGrid *p = (M_ElevationGrid *) node;
	gf_sg_mffloat_del(p->set_height);
	gf_node_unregister((GF_Node *) p->color, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->normal, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->texCoord, (GF_Node *) p);	
	gf_sg_mffloat_del(p->height);
	gf_node_free((GF_Node *) p);
}

static const u16 ElevationGrid_Def2All[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
static const u16 ElevationGrid_In2All[] = { 0, 1, 2, 3};
static const u16 ElevationGrid_Out2All[] = { 1, 2, 3};

static u32 ElevationGrid_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 13;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 14;
	}
}

static GF_Err ElevationGrid_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = ElevationGrid_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = ElevationGrid_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = ElevationGrid_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err ElevationGrid_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_height";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_ElevationGrid *)node)->on_set_height;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_ElevationGrid *) node)->set_height;
		return GF_OK;
	case 1:
		info->name = "color";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFColorNode;
		info->far_ptr = & ((M_ElevationGrid *)node)->color;
		return GF_OK;
	case 2:
		info->name = "normal";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFNormalNode;
		info->far_ptr = & ((M_ElevationGrid *)node)->normal;
		return GF_OK;
	case 3:
		info->name = "texCoord";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFTextureCoordinateNode;
		info->far_ptr = & ((M_ElevationGrid *)node)->texCoord;
		return GF_OK;
	case 4:
		info->name = "height";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_ElevationGrid *) node)->height;
		return GF_OK;
	case 5:
		info->name = "ccw";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_ElevationGrid *) node)->ccw;
		return GF_OK;
	case 6:
		info->name = "colorPerVertex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_ElevationGrid *) node)->colorPerVertex;
		return GF_OK;
	case 7:
		info->name = "creaseAngle";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ElevationGrid *) node)->creaseAngle;
		return GF_OK;
	case 8:
		info->name = "normalPerVertex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_ElevationGrid *) node)->normalPerVertex;
		return GF_OK;
	case 9:
		info->name = "solid";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_ElevationGrid *) node)->solid;
		return GF_OK;
	case 10:
		info->name = "xDimension";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_ElevationGrid *) node)->xDimension;
		return GF_OK;
	case 11:
		info->name = "xSpacing";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ElevationGrid *) node)->xSpacing;
		return GF_OK;
	case 12:
		info->name = "zDimension";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_ElevationGrid *) node)->zDimension;
		return GF_OK;
	case 13:
		info->name = "zSpacing";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ElevationGrid *) node)->zSpacing;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 ElevationGrid_get_field_index_by_name(char *name)
{
	if (!strcmp("set_height", name)) return 0;
	if (!strcmp("color", name)) return 1;
	if (!strcmp("normal", name)) return 2;
	if (!strcmp("texCoord", name)) return 3;
	if (!strcmp("height", name)) return 4;
	if (!strcmp("ccw", name)) return 5;
	if (!strcmp("colorPerVertex", name)) return 6;
	if (!strcmp("creaseAngle", name)) return 7;
	if (!strcmp("normalPerVertex", name)) return 8;
	if (!strcmp("solid", name)) return 9;
	if (!strcmp("xDimension", name)) return 10;
	if (!strcmp("xSpacing", name)) return 11;
	if (!strcmp("zDimension", name)) return 12;
	if (!strcmp("zSpacing", name)) return 13;
	return -1;
	}
static Bool ElevationGrid_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 4:
		*AType = 7;
		*QType = 11;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 7:
		*AType = 0;
		*QType = 6;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(6.2831853);
		return 1;
	case 10:
		*AType = 0;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 11:
		*AType = 0;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 12:
		*AType = 0;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 13:
		*AType = 0;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *ElevationGrid_Create()
{
	M_ElevationGrid *p;
	GF_SAFEALLOC(p, M_ElevationGrid);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_ElevationGrid);

	/*default field values*/
	p->ccw = 1;
	p->colorPerVertex = 1;
	p->creaseAngle = FLT2FIX(0.0);
	p->normalPerVertex = 1;
	p->solid = 1;
	p->xDimension = 0;
	p->xSpacing = FLT2FIX(1.0);
	p->zDimension = 0;
	p->zSpacing = FLT2FIX(1.0);
	return (GF_Node *)p;
}


/*
	Expression Node deletion
*/

static void Expression_Del(GF_Node *node)
{
	M_Expression *p = (M_Expression *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 Expression_Def2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 Expression_In2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 Expression_Out2All[] = { 0, 1, 2, 3, 4, 5};

static u32 Expression_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 6;
	case GF_SG_FIELD_CODING_DEF: return 6;
	case GF_SG_FIELD_CODING_OUT: return 6;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 6;
	}
}

static GF_Err Expression_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Expression_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Expression_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Expression_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Expression_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "expression_select1";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_Expression *) node)->expression_select1;
		return GF_OK;
	case 1:
		info->name = "expression_intensity1";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_Expression *) node)->expression_intensity1;
		return GF_OK;
	case 2:
		info->name = "expression_select2";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_Expression *) node)->expression_select2;
		return GF_OK;
	case 3:
		info->name = "expression_intensity2";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_Expression *) node)->expression_intensity2;
		return GF_OK;
	case 4:
		info->name = "init_face";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Expression *) node)->init_face;
		return GF_OK;
	case 5:
		info->name = "expression_def";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Expression *) node)->expression_def;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Expression_get_field_index_by_name(char *name)
{
	if (!strcmp("expression_select1", name)) return 0;
	if (!strcmp("expression_intensity1", name)) return 1;
	if (!strcmp("expression_select2", name)) return 2;
	if (!strcmp("expression_intensity2", name)) return 3;
	if (!strcmp("init_face", name)) return 4;
	if (!strcmp("expression_def", name)) return 5;
	return -1;
	}
static Bool Expression_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 5;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(31);
		return 1;
	case 1:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 6;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(63);
		return 1;
	case 2:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 5;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(31);
		return 1;
	case 3:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 6;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(63);
		return 1;
	default:
		return 0;
	}
}



GF_Node *Expression_Create()
{
	M_Expression *p;
	GF_SAFEALLOC(p, M_Expression);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Expression);

	/*default field values*/
	p->expression_select1 = 0;
	p->expression_intensity1 = 0;
	p->expression_select2 = 0;
	p->expression_intensity2 = 0;
	return (GF_Node *)p;
}


/*
	Extrusion Node deletion
*/

static void Extrusion_Del(GF_Node *node)
{
	M_Extrusion *p = (M_Extrusion *) node;
	gf_sg_mfvec2f_del(p->set_crossSection);
	gf_sg_mfrotation_del(p->set_orientation);
	gf_sg_mfvec2f_del(p->set_scale);
	gf_sg_mfvec3f_del(p->set_spine);
	gf_sg_mfvec2f_del(p->crossSection);
	gf_sg_mfrotation_del(p->orientation);
	gf_sg_mfvec2f_del(p->scale);
	gf_sg_mfvec3f_del(p->spine);
	gf_node_free((GF_Node *) p);
}

static const u16 Extrusion_Def2All[] = { 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
static const u16 Extrusion_In2All[] = { 0, 1, 2, 3};

static u32 Extrusion_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 10;
	case GF_SG_FIELD_CODING_OUT: return 0;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 14;
	}
}

static GF_Err Extrusion_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Extrusion_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Extrusion_Def2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Extrusion_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_crossSection";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Extrusion *)node)->on_set_crossSection;
		info->fieldType = GF_SG_VRML_MFVEC2F;
		info->far_ptr = & ((M_Extrusion *) node)->set_crossSection;
		return GF_OK;
	case 1:
		info->name = "set_orientation";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Extrusion *)node)->on_set_orientation;
		info->fieldType = GF_SG_VRML_MFROTATION;
		info->far_ptr = & ((M_Extrusion *) node)->set_orientation;
		return GF_OK;
	case 2:
		info->name = "set_scale";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Extrusion *)node)->on_set_scale;
		info->fieldType = GF_SG_VRML_MFVEC2F;
		info->far_ptr = & ((M_Extrusion *) node)->set_scale;
		return GF_OK;
	case 3:
		info->name = "set_spine";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Extrusion *)node)->on_set_spine;
		info->fieldType = GF_SG_VRML_MFVEC3F;
		info->far_ptr = & ((M_Extrusion *) node)->set_spine;
		return GF_OK;
	case 4:
		info->name = "beginCap";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Extrusion *) node)->beginCap;
		return GF_OK;
	case 5:
		info->name = "ccw";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Extrusion *) node)->ccw;
		return GF_OK;
	case 6:
		info->name = "convex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Extrusion *) node)->convex;
		return GF_OK;
	case 7:
		info->name = "creaseAngle";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Extrusion *) node)->creaseAngle;
		return GF_OK;
	case 8:
		info->name = "crossSection";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC2F;
		info->far_ptr = & ((M_Extrusion *) node)->crossSection;
		return GF_OK;
	case 9:
		info->name = "endCap";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Extrusion *) node)->endCap;
		return GF_OK;
	case 10:
		info->name = "orientation";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFROTATION;
		info->far_ptr = & ((M_Extrusion *) node)->orientation;
		return GF_OK;
	case 11:
		info->name = "scale";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC2F;
		info->far_ptr = & ((M_Extrusion *) node)->scale;
		return GF_OK;
	case 12:
		info->name = "solid";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Extrusion *) node)->solid;
		return GF_OK;
	case 13:
		info->name = "spine";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC3F;
		info->far_ptr = & ((M_Extrusion *) node)->spine;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Extrusion_get_field_index_by_name(char *name)
{
	if (!strcmp("set_crossSection", name)) return 0;
	if (!strcmp("set_orientation", name)) return 1;
	if (!strcmp("set_scale", name)) return 2;
	if (!strcmp("set_spine", name)) return 3;
	if (!strcmp("beginCap", name)) return 4;
	if (!strcmp("ccw", name)) return 5;
	if (!strcmp("convex", name)) return 6;
	if (!strcmp("creaseAngle", name)) return 7;
	if (!strcmp("crossSection", name)) return 8;
	if (!strcmp("endCap", name)) return 9;
	if (!strcmp("orientation", name)) return 10;
	if (!strcmp("scale", name)) return 11;
	if (!strcmp("solid", name)) return 12;
	if (!strcmp("spine", name)) return 13;
	return -1;
	}
static Bool Extrusion_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 7:
		*AType = 0;
		*QType = 6;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(6.2831853);
		return 1;
	case 8:
		*AType = 0;
		*QType = 2;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 10:
		*AType = 0;
		*QType = 10;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 11:
		*AType = 0;
		*QType = 7;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 13:
		*AType = 0;
		*QType = 1;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Extrusion_Create()
{
	M_Extrusion *p;
	GF_SAFEALLOC(p, M_Extrusion);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Extrusion);

	/*default field values*/
	p->beginCap = 1;
	p->ccw = 1;
	p->convex = 1;
	p->creaseAngle = FLT2FIX(0.0);
	p->crossSection.vals = (SFVec2f*)malloc(sizeof(SFVec2f)*5);
	p->crossSection.count = 5;
	p->crossSection.vals[0].x = FLT2FIX(1);
	p->crossSection.vals[0].y = FLT2FIX(1);
	p->crossSection.vals[1].x = FLT2FIX(1);
	p->crossSection.vals[1].y = FLT2FIX(-1);
	p->crossSection.vals[2].x = FLT2FIX(-1);
	p->crossSection.vals[2].y = FLT2FIX(-1);
	p->crossSection.vals[3].x = FLT2FIX(-1);
	p->crossSection.vals[3].y = FLT2FIX(1);
	p->crossSection.vals[4].x = FLT2FIX(1);
	p->crossSection.vals[4].y = FLT2FIX(1);
	p->endCap = 1;
	p->orientation.vals = (GF_Vec4*)malloc(sizeof(GF_Vec4)*1);
	p->orientation.count = 1;
	p->orientation.vals[0].x = FLT2FIX(0);
	p->orientation.vals[0].y = FLT2FIX(0);
	p->orientation.vals[0].z = FLT2FIX(1);
	p->orientation.vals[0].q = FLT2FIX(0);
	p->scale.vals = (SFVec2f*)malloc(sizeof(SFVec2f)*1);
	p->scale.count = 1;
	p->scale.vals[0].x = FLT2FIX(1);
	p->scale.vals[0].y = FLT2FIX(1);
	p->solid = 1;
	p->spine.vals = (SFVec3f *)malloc(sizeof(SFVec3f)*2);
	p->spine.count = 2;
	p->spine.vals[0].x = FLT2FIX(0);
	p->spine.vals[0].y = FLT2FIX(0);
	p->spine.vals[0].z = FLT2FIX(0);
	p->spine.vals[1].x = FLT2FIX(0);
	p->spine.vals[1].y = FLT2FIX(1);
	p->spine.vals[1].z = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	Face Node deletion
*/

static void Face_Del(GF_Node *node)
{
	M_Face *p = (M_Face *) node;
	gf_node_unregister((GF_Node *) p->fap, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->fdp, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->fit, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->ttsSource, (GF_Node *) p);	
	gf_node_unregister_children((GF_Node *) p, p->renderedFace);	
	gf_node_free((GF_Node *) p);
}

static const u16 Face_Def2All[] = { 0, 1, 2, 3, 4};
static const u16 Face_In2All[] = { 0, 1, 2, 3, 4};
static const u16 Face_Out2All[] = { 0, 1, 2, 3, 4};

static u32 Face_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 5;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 5;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 5;
	}
}

static GF_Err Face_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Face_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Face_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Face_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Face_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "fap";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFFAPNode;
		info->far_ptr = & ((M_Face *)node)->fap;
		return GF_OK;
	case 1:
		info->name = "fdp";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFFDPNode;
		info->far_ptr = & ((M_Face *)node)->fdp;
		return GF_OK;
	case 2:
		info->name = "fit";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFFITNode;
		info->far_ptr = & ((M_Face *)node)->fit;
		return GF_OK;
	case 3:
		info->name = "ttsSource";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFAudioNode;
		info->far_ptr = & ((M_Face *)node)->ttsSource;
		return GF_OK;
	case 4:
		info->name = "renderedFace";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_Face *)node)->renderedFace;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Face_get_field_index_by_name(char *name)
{
	if (!strcmp("fap", name)) return 0;
	if (!strcmp("fdp", name)) return 1;
	if (!strcmp("fit", name)) return 2;
	if (!strcmp("ttsSource", name)) return 3;
	if (!strcmp("renderedFace", name)) return 4;
	return -1;
	}
static Bool Face_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *Face_Create()
{
	M_Face *p;
	GF_SAFEALLOC(p, M_Face);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Face);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	FaceDefMesh Node deletion
*/

static void FaceDefMesh_Del(GF_Node *node)
{
	M_FaceDefMesh *p = (M_FaceDefMesh *) node;
	gf_node_unregister((GF_Node *) p->faceSceneGraphNode, (GF_Node *) p);	
	gf_sg_mfint32_del(p->intervalBorders);
	gf_sg_mfint32_del(p->coordIndex);
	gf_sg_mfvec3f_del(p->displacements);
	gf_node_free((GF_Node *) p);
}

static const u16 FaceDefMesh_Def2All[] = { 0, 1, 2, 3};

static u32 FaceDefMesh_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 0;
	case GF_SG_FIELD_CODING_DEF: return 4;
	case GF_SG_FIELD_CODING_OUT: return 0;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err FaceDefMesh_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_DEF:
		*allField = FaceDefMesh_Def2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err FaceDefMesh_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "faceSceneGraphNode";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_FaceDefMesh *)node)->faceSceneGraphNode;
		return GF_OK;
	case 1:
		info->name = "intervalBorders";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_FaceDefMesh *) node)->intervalBorders;
		return GF_OK;
	case 2:
		info->name = "coordIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_FaceDefMesh *) node)->coordIndex;
		return GF_OK;
	case 3:
		info->name = "displacements";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC3F;
		info->far_ptr = & ((M_FaceDefMesh *) node)->displacements;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 FaceDefMesh_get_field_index_by_name(char *name)
{
	if (!strcmp("faceSceneGraphNode", name)) return 0;
	if (!strcmp("intervalBorders", name)) return 1;
	if (!strcmp("coordIndex", name)) return 2;
	if (!strcmp("displacements", name)) return 3;
	return -1;
	}
static Bool FaceDefMesh_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 0;
		return 1;
	case 2:
		*AType = 0;
		*QType = 0;
		return 1;
	case 3:
		*AType = 0;
		*QType = 0;
		return 1;
	default:
		return 0;
	}
}



GF_Node *FaceDefMesh_Create()
{
	M_FaceDefMesh *p;
	GF_SAFEALLOC(p, M_FaceDefMesh);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_FaceDefMesh);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	FaceDefTables Node deletion
*/

static void FaceDefTables_Del(GF_Node *node)
{
	M_FaceDefTables *p = (M_FaceDefTables *) node;
	gf_node_unregister_children((GF_Node *) p, p->faceDefMesh);	
	gf_node_unregister_children((GF_Node *) p, p->faceDefTransform);	
	gf_node_free((GF_Node *) p);
}

static const u16 FaceDefTables_Def2All[] = { 0, 1, 2, 3};
static const u16 FaceDefTables_In2All[] = { 2, 3};
static const u16 FaceDefTables_Out2All[] = { 2, 3};

static u32 FaceDefTables_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 2;
	case GF_SG_FIELD_CODING_DEF: return 4;
	case GF_SG_FIELD_CODING_OUT: return 2;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err FaceDefTables_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = FaceDefTables_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = FaceDefTables_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = FaceDefTables_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err FaceDefTables_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "fapID";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FaceDefTables *) node)->fapID;
		return GF_OK;
	case 1:
		info->name = "highLevelSelect";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FaceDefTables *) node)->highLevelSelect;
		return GF_OK;
	case 2:
		info->name = "faceDefMesh";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFFaceDefMeshNode;
		info->far_ptr = & ((M_FaceDefTables *)node)->faceDefMesh;
		return GF_OK;
	case 3:
		info->name = "faceDefTransform";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFFaceDefTransformNode;
		info->far_ptr = & ((M_FaceDefTables *)node)->faceDefTransform;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 FaceDefTables_get_field_index_by_name(char *name)
{
	if (!strcmp("fapID", name)) return 0;
	if (!strcmp("highLevelSelect", name)) return 1;
	if (!strcmp("faceDefMesh", name)) return 2;
	if (!strcmp("faceDefTransform", name)) return 3;
	return -1;
	}
static Bool FaceDefTables_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 7;
		*b_min = FLT2FIX(1);
		*b_max = FLT2FIX( 68);
		return 1;
	case 1:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 6;
		*b_min = FLT2FIX(1);
		*b_max = FLT2FIX( 64);
		return 1;
	default:
		return 0;
	}
}



GF_Node *FaceDefTables_Create()
{
	M_FaceDefTables *p;
	GF_SAFEALLOC(p, M_FaceDefTables);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_FaceDefTables);

	/*default field values*/
	p->fapID = 1;
	p->highLevelSelect = 1;
	return (GF_Node *)p;
}


/*
	FaceDefTransform Node deletion
*/

static void FaceDefTransform_Del(GF_Node *node)
{
	M_FaceDefTransform *p = (M_FaceDefTransform *) node;
	gf_node_unregister((GF_Node *) p->faceSceneGraphNode, (GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 FaceDefTransform_Def2All[] = { 0, 1, 2, 3, 4};

static u32 FaceDefTransform_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 0;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 0;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 5;
	}
}

static GF_Err FaceDefTransform_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_DEF:
		*allField = FaceDefTransform_Def2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err FaceDefTransform_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "faceSceneGraphNode";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_FaceDefTransform *)node)->faceSceneGraphNode;
		return GF_OK;
	case 1:
		info->name = "fieldId";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FaceDefTransform *) node)->fieldId;
		return GF_OK;
	case 2:
		info->name = "rotationDef";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFROTATION;
		info->far_ptr = & ((M_FaceDefTransform *) node)->rotationDef;
		return GF_OK;
	case 3:
		info->name = "scaleDef";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_FaceDefTransform *) node)->scaleDef;
		return GF_OK;
	case 4:
		info->name = "translationDef";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_FaceDefTransform *) node)->translationDef;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 FaceDefTransform_get_field_index_by_name(char *name)
{
	if (!strcmp("faceSceneGraphNode", name)) return 0;
	if (!strcmp("fieldId", name)) return 1;
	if (!strcmp("rotationDef", name)) return 2;
	if (!strcmp("scaleDef", name)) return 3;
	if (!strcmp("translationDef", name)) return 4;
	return -1;
	}
static Bool FaceDefTransform_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 2:
		*AType = 0;
		*QType = 10;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 3:
		*AType = 0;
		*QType = 7;
		return 1;
	case 4:
		*AType = 0;
		*QType = 1;
		return 1;
	default:
		return 0;
	}
}



GF_Node *FaceDefTransform_Create()
{
	M_FaceDefTransform *p;
	GF_SAFEALLOC(p, M_FaceDefTransform);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_FaceDefTransform);

	/*default field values*/
	p->fieldId = 1;
	p->rotationDef.x = FLT2FIX(0);
	p->rotationDef.y = FLT2FIX(0);
	p->rotationDef.z = FLT2FIX(1);
	p->rotationDef.q = FLT2FIX(0);
	p->scaleDef.x = FLT2FIX(1);
	p->scaleDef.y = FLT2FIX(1);
	p->scaleDef.z = FLT2FIX(1);
	p->translationDef.x = FLT2FIX(0);
	p->translationDef.y = FLT2FIX(0);
	p->translationDef.z = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	FAP Node deletion
*/

static void FAP_Del(GF_Node *node)
{
	M_FAP *p = (M_FAP *) node;
	gf_node_unregister((GF_Node *) p->viseme, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->expression, (GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 FAP_Def2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67};
static const u16 FAP_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67};
static const u16 FAP_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67};

static u32 FAP_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 68;
	case GF_SG_FIELD_CODING_DEF: return 68;
	case GF_SG_FIELD_CODING_OUT: return 68;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 68;
	}
}

static GF_Err FAP_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = FAP_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = FAP_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = FAP_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err FAP_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "viseme";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFVisemeNode;
		info->far_ptr = & ((M_FAP *)node)->viseme;
		return GF_OK;
	case 1:
		info->name = "expression";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFExpressionNode;
		info->far_ptr = & ((M_FAP *)node)->expression;
		return GF_OK;
	case 2:
		info->name = "open_jaw";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->open_jaw;
		return GF_OK;
	case 3:
		info->name = "lower_t_midlip";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->lower_t_midlip;
		return GF_OK;
	case 4:
		info->name = "raise_b_midlip";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->raise_b_midlip;
		return GF_OK;
	case 5:
		info->name = "stretch_l_corner";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->stretch_l_corner;
		return GF_OK;
	case 6:
		info->name = "stretch_r_corner";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->stretch_r_corner;
		return GF_OK;
	case 7:
		info->name = "lower_t_lip_lm";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->lower_t_lip_lm;
		return GF_OK;
	case 8:
		info->name = "lower_t_lip_rm";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->lower_t_lip_rm;
		return GF_OK;
	case 9:
		info->name = "lower_b_lip_lm";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->lower_b_lip_lm;
		return GF_OK;
	case 10:
		info->name = "lower_b_lip_rm";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->lower_b_lip_rm;
		return GF_OK;
	case 11:
		info->name = "raise_l_cornerlip";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->raise_l_cornerlip;
		return GF_OK;
	case 12:
		info->name = "raise_r_cornerlip";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->raise_r_cornerlip;
		return GF_OK;
	case 13:
		info->name = "thrust_jaw";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->thrust_jaw;
		return GF_OK;
	case 14:
		info->name = "shift_jaw";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->shift_jaw;
		return GF_OK;
	case 15:
		info->name = "push_b_lip";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->push_b_lip;
		return GF_OK;
	case 16:
		info->name = "push_t_lip";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->push_t_lip;
		return GF_OK;
	case 17:
		info->name = "depress_chin";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->depress_chin;
		return GF_OK;
	case 18:
		info->name = "close_t_l_eyelid";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->close_t_l_eyelid;
		return GF_OK;
	case 19:
		info->name = "close_t_r_eyelid";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->close_t_r_eyelid;
		return GF_OK;
	case 20:
		info->name = "close_b_l_eyelid";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->close_b_l_eyelid;
		return GF_OK;
	case 21:
		info->name = "close_b_r_eyelid";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->close_b_r_eyelid;
		return GF_OK;
	case 22:
		info->name = "yaw_l_eyeball";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->yaw_l_eyeball;
		return GF_OK;
	case 23:
		info->name = "yaw_r_eyeball";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->yaw_r_eyeball;
		return GF_OK;
	case 24:
		info->name = "pitch_l_eyeball";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->pitch_l_eyeball;
		return GF_OK;
	case 25:
		info->name = "pitch_r_eyeball";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->pitch_r_eyeball;
		return GF_OK;
	case 26:
		info->name = "thrust_l_eyeball";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->thrust_l_eyeball;
		return GF_OK;
	case 27:
		info->name = "thrust_r_eyeball";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->thrust_r_eyeball;
		return GF_OK;
	case 28:
		info->name = "dilate_l_pupil";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->dilate_l_pupil;
		return GF_OK;
	case 29:
		info->name = "dilate_r_pupil";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->dilate_r_pupil;
		return GF_OK;
	case 30:
		info->name = "raise_l_i_eyebrow";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->raise_l_i_eyebrow;
		return GF_OK;
	case 31:
		info->name = "raise_r_i_eyebrow";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->raise_r_i_eyebrow;
		return GF_OK;
	case 32:
		info->name = "raise_l_m_eyebrow";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->raise_l_m_eyebrow;
		return GF_OK;
	case 33:
		info->name = "raise_r_m_eyebrow";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->raise_r_m_eyebrow;
		return GF_OK;
	case 34:
		info->name = "raise_l_o_eyebrow";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->raise_l_o_eyebrow;
		return GF_OK;
	case 35:
		info->name = "raise_r_o_eyebrow";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->raise_r_o_eyebrow;
		return GF_OK;
	case 36:
		info->name = "squeeze_l_eyebrow";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->squeeze_l_eyebrow;
		return GF_OK;
	case 37:
		info->name = "squeeze_r_eyebrow";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->squeeze_r_eyebrow;
		return GF_OK;
	case 38:
		info->name = "puff_l_cheek";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->puff_l_cheek;
		return GF_OK;
	case 39:
		info->name = "puff_r_cheek";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->puff_r_cheek;
		return GF_OK;
	case 40:
		info->name = "lift_l_cheek";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->lift_l_cheek;
		return GF_OK;
	case 41:
		info->name = "lift_r_cheek";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->lift_r_cheek;
		return GF_OK;
	case 42:
		info->name = "shift_tongue_tip";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->shift_tongue_tip;
		return GF_OK;
	case 43:
		info->name = "raise_tongue_tip";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->raise_tongue_tip;
		return GF_OK;
	case 44:
		info->name = "thrust_tongue_tip";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->thrust_tongue_tip;
		return GF_OK;
	case 45:
		info->name = "raise_tongue";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->raise_tongue;
		return GF_OK;
	case 46:
		info->name = "tongue_roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->tongue_roll;
		return GF_OK;
	case 47:
		info->name = "head_pitch";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->head_pitch;
		return GF_OK;
	case 48:
		info->name = "head_yaw";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->head_yaw;
		return GF_OK;
	case 49:
		info->name = "head_roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->head_roll;
		return GF_OK;
	case 50:
		info->name = "lower_t_midlip_o";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->lower_t_midlip_o;
		return GF_OK;
	case 51:
		info->name = "raise_b_midlip_o";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->raise_b_midlip_o;
		return GF_OK;
	case 52:
		info->name = "stretch_l_cornerlip";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->stretch_l_cornerlip;
		return GF_OK;
	case 53:
		info->name = "stretch_r_cornerlip";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->stretch_r_cornerlip;
		return GF_OK;
	case 54:
		info->name = "lower_t_lip_lm_o";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->lower_t_lip_lm_o;
		return GF_OK;
	case 55:
		info->name = "lower_t_lip_rm_o";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->lower_t_lip_rm_o;
		return GF_OK;
	case 56:
		info->name = "raise_b_lip_lm_o";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->raise_b_lip_lm_o;
		return GF_OK;
	case 57:
		info->name = "raise_b_lip_rm_o";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->raise_b_lip_rm_o;
		return GF_OK;
	case 58:
		info->name = "raise_l_cornerlip_o";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->raise_l_cornerlip_o;
		return GF_OK;
	case 59:
		info->name = "raise_r_cornerlip_o";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->raise_r_cornerlip_o;
		return GF_OK;
	case 60:
		info->name = "stretch_l_nose";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->stretch_l_nose;
		return GF_OK;
	case 61:
		info->name = "stretch_r_nose";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->stretch_r_nose;
		return GF_OK;
	case 62:
		info->name = "raise_nose";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->raise_nose;
		return GF_OK;
	case 63:
		info->name = "bend_nose";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->bend_nose;
		return GF_OK;
	case 64:
		info->name = "raise_l_ear";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->raise_l_ear;
		return GF_OK;
	case 65:
		info->name = "raise_r_ear";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->raise_r_ear;
		return GF_OK;
	case 66:
		info->name = "pull_l_ear";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->pull_l_ear;
		return GF_OK;
	case 67:
		info->name = "pull_r_ear";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FAP *) node)->pull_r_ear;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 FAP_get_field_index_by_name(char *name)
{
	if (!strcmp("viseme", name)) return 0;
	if (!strcmp("expression", name)) return 1;
	if (!strcmp("open_jaw", name)) return 2;
	if (!strcmp("lower_t_midlip", name)) return 3;
	if (!strcmp("raise_b_midlip", name)) return 4;
	if (!strcmp("stretch_l_corner", name)) return 5;
	if (!strcmp("stretch_r_corner", name)) return 6;
	if (!strcmp("lower_t_lip_lm", name)) return 7;
	if (!strcmp("lower_t_lip_rm", name)) return 8;
	if (!strcmp("lower_b_lip_lm", name)) return 9;
	if (!strcmp("lower_b_lip_rm", name)) return 10;
	if (!strcmp("raise_l_cornerlip", name)) return 11;
	if (!strcmp("raise_r_cornerlip", name)) return 12;
	if (!strcmp("thrust_jaw", name)) return 13;
	if (!strcmp("shift_jaw", name)) return 14;
	if (!strcmp("push_b_lip", name)) return 15;
	if (!strcmp("push_t_lip", name)) return 16;
	if (!strcmp("depress_chin", name)) return 17;
	if (!strcmp("close_t_l_eyelid", name)) return 18;
	if (!strcmp("close_t_r_eyelid", name)) return 19;
	if (!strcmp("close_b_l_eyelid", name)) return 20;
	if (!strcmp("close_b_r_eyelid", name)) return 21;
	if (!strcmp("yaw_l_eyeball", name)) return 22;
	if (!strcmp("yaw_r_eyeball", name)) return 23;
	if (!strcmp("pitch_l_eyeball", name)) return 24;
	if (!strcmp("pitch_r_eyeball", name)) return 25;
	if (!strcmp("thrust_l_eyeball", name)) return 26;
	if (!strcmp("thrust_r_eyeball", name)) return 27;
	if (!strcmp("dilate_l_pupil", name)) return 28;
	if (!strcmp("dilate_r_pupil", name)) return 29;
	if (!strcmp("raise_l_i_eyebrow", name)) return 30;
	if (!strcmp("raise_r_i_eyebrow", name)) return 31;
	if (!strcmp("raise_l_m_eyebrow", name)) return 32;
	if (!strcmp("raise_r_m_eyebrow", name)) return 33;
	if (!strcmp("raise_l_o_eyebrow", name)) return 34;
	if (!strcmp("raise_r_o_eyebrow", name)) return 35;
	if (!strcmp("squeeze_l_eyebrow", name)) return 36;
	if (!strcmp("squeeze_r_eyebrow", name)) return 37;
	if (!strcmp("puff_l_cheek", name)) return 38;
	if (!strcmp("puff_r_cheek", name)) return 39;
	if (!strcmp("lift_l_cheek", name)) return 40;
	if (!strcmp("lift_r_cheek", name)) return 41;
	if (!strcmp("shift_tongue_tip", name)) return 42;
	if (!strcmp("raise_tongue_tip", name)) return 43;
	if (!strcmp("thrust_tongue_tip", name)) return 44;
	if (!strcmp("raise_tongue", name)) return 45;
	if (!strcmp("tongue_roll", name)) return 46;
	if (!strcmp("head_pitch", name)) return 47;
	if (!strcmp("head_yaw", name)) return 48;
	if (!strcmp("head_roll", name)) return 49;
	if (!strcmp("lower_t_midlip_o", name)) return 50;
	if (!strcmp("raise_b_midlip_o", name)) return 51;
	if (!strcmp("stretch_l_cornerlip", name)) return 52;
	if (!strcmp("stretch_r_cornerlip", name)) return 53;
	if (!strcmp("lower_t_lip_lm_o", name)) return 54;
	if (!strcmp("lower_t_lip_rm_o", name)) return 55;
	if (!strcmp("raise_b_lip_lm_o", name)) return 56;
	if (!strcmp("raise_b_lip_rm_o", name)) return 57;
	if (!strcmp("raise_l_cornerlip_o", name)) return 58;
	if (!strcmp("raise_r_cornerlip_o", name)) return 59;
	if (!strcmp("stretch_l_nose", name)) return 60;
	if (!strcmp("stretch_r_nose", name)) return 61;
	if (!strcmp("raise_nose", name)) return 62;
	if (!strcmp("bend_nose", name)) return 63;
	if (!strcmp("raise_l_ear", name)) return 64;
	if (!strcmp("raise_r_ear", name)) return 65;
	if (!strcmp("pull_l_ear", name)) return 66;
	if (!strcmp("pull_r_ear", name)) return 67;
	return -1;
	}
static Bool FAP_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 2:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 3:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 4:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 5:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 6:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 7:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 8:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 9:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 10:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 11:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 12:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 13:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 14:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 15:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 16:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 17:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 18:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 19:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 20:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 21:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 22:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 23:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 24:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 25:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 26:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 27:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 28:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 29:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 30:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 31:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 32:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 33:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 34:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 35:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 36:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 37:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 38:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 39:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 40:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 41:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 42:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 43:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 44:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 45:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 46:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 47:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 48:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 49:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 50:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 51:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 52:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 53:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 54:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 55:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 56:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 57:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 58:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 59:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 60:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 61:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 62:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 63:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 64:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 65:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 66:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 67:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *FAP_Create()
{
	M_FAP *p;
	GF_SAFEALLOC(p, M_FAP);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_FAP);

	/*default field values*/
	p->open_jaw = 2 << 31;
	p->lower_t_midlip = 2 << 31;
	p->raise_b_midlip = 2 << 31;
	p->stretch_l_corner = 2 << 31;
	p->stretch_r_corner = 2 << 31;
	p->lower_t_lip_lm = 2 << 31;
	p->lower_t_lip_rm = 2 << 31;
	p->lower_b_lip_lm = 2 << 31;
	p->lower_b_lip_rm = 2 << 31;
	p->raise_l_cornerlip = 2 << 31;
	p->raise_r_cornerlip = 2 << 31;
	p->thrust_jaw = 2 << 31;
	p->shift_jaw = 2 << 31;
	p->push_b_lip = 2 << 31;
	p->push_t_lip = 2 << 31;
	p->depress_chin = 2 << 31;
	p->close_t_l_eyelid = 2 << 31;
	p->close_t_r_eyelid = 2 << 31;
	p->close_b_l_eyelid = 2 << 31;
	p->close_b_r_eyelid = 2 << 31;
	p->yaw_l_eyeball = 2 << 31;
	p->yaw_r_eyeball = 2 << 31;
	p->pitch_l_eyeball = 2 << 31;
	p->pitch_r_eyeball = 2 << 31;
	p->thrust_l_eyeball = 2 << 31;
	p->thrust_r_eyeball = 2 << 31;
	p->dilate_l_pupil = 2 << 31;
	p->dilate_r_pupil = 2 << 31;
	p->raise_l_i_eyebrow = 2 << 31;
	p->raise_r_i_eyebrow = 2 << 31;
	p->raise_l_m_eyebrow = 2 << 31;
	p->raise_r_m_eyebrow = 2 << 31;
	p->raise_l_o_eyebrow = 2 << 31;
	p->raise_r_o_eyebrow = 2 << 31;
	p->squeeze_l_eyebrow = 2 << 31;
	p->squeeze_r_eyebrow = 2 << 31;
	p->puff_l_cheek = 2 << 31;
	p->puff_r_cheek = 2 << 31;
	p->lift_l_cheek = 2 << 31;
	p->lift_r_cheek = 2 << 31;
	p->shift_tongue_tip = 2 << 31;
	p->raise_tongue_tip = 2 << 31;
	p->thrust_tongue_tip = 2 << 31;
	p->raise_tongue = 2 << 31;
	p->tongue_roll = 2 << 31;
	p->head_pitch = 2 << 31;
	p->head_yaw = 2 << 31;
	p->head_roll = 2 << 31;
	p->lower_t_midlip_o = 2 << 31;
	p->raise_b_midlip_o = 2 << 31;
	p->stretch_l_cornerlip = 2 << 31;
	p->stretch_r_cornerlip = 2 << 31;
	p->lower_t_lip_lm_o = 2 << 31;
	p->lower_t_lip_rm_o = 2 << 31;
	p->raise_b_lip_lm_o = 2 << 31;
	p->raise_b_lip_rm_o = 2 << 31;
	p->raise_l_cornerlip_o = 2 << 31;
	p->raise_r_cornerlip_o = 2 << 31;
	p->stretch_l_nose = 2 << 31;
	p->stretch_r_nose = 2 << 31;
	p->raise_nose = 2 << 31;
	p->bend_nose = 2 << 31;
	p->raise_l_ear = 2 << 31;
	p->raise_r_ear = 2 << 31;
	p->pull_l_ear = 2 << 31;
	p->pull_r_ear = 2 << 31;
	return (GF_Node *)p;
}


/*
	FDP Node deletion
*/

static void FDP_Del(GF_Node *node)
{
	M_FDP *p = (M_FDP *) node;
	gf_node_unregister((GF_Node *) p->featurePointsCoord, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->textureCoord, (GF_Node *) p);	
	gf_node_unregister_children((GF_Node *) p, p->faceDefTables);	
	gf_node_unregister_children((GF_Node *) p, p->faceSceneGraph);	
	gf_node_free((GF_Node *) p);
}

static const u16 FDP_Def2All[] = { 0, 1, 2, 3, 4};
static const u16 FDP_In2All[] = { 0, 1, 2, 3};
static const u16 FDP_Out2All[] = { 0, 1, 2, 3};

static u32 FDP_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 4;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 5;
	}
}

static GF_Err FDP_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = FDP_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = FDP_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = FDP_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err FDP_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "featurePointsCoord";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFCoordinateNode;
		info->far_ptr = & ((M_FDP *)node)->featurePointsCoord;
		return GF_OK;
	case 1:
		info->name = "textureCoord";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFTextureCoordinateNode;
		info->far_ptr = & ((M_FDP *)node)->textureCoord;
		return GF_OK;
	case 2:
		info->name = "faceDefTables";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFFaceDefTablesNode;
		info->far_ptr = & ((M_FDP *)node)->faceDefTables;
		return GF_OK;
	case 3:
		info->name = "faceSceneGraph";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_FDP *)node)->faceSceneGraph;
		return GF_OK;
	case 4:
		info->name = "useOrthoTexture";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_FDP *) node)->useOrthoTexture;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 FDP_get_field_index_by_name(char *name)
{
	if (!strcmp("featurePointsCoord", name)) return 0;
	if (!strcmp("textureCoord", name)) return 1;
	if (!strcmp("faceDefTables", name)) return 2;
	if (!strcmp("faceSceneGraph", name)) return 3;
	if (!strcmp("useOrthoTexture", name)) return 4;
	return -1;
	}
static Bool FDP_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *FDP_Create()
{
	M_FDP *p;
	GF_SAFEALLOC(p, M_FDP);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_FDP);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	FIT Node deletion
*/

static void FIT_Del(GF_Node *node)
{
	M_FIT *p = (M_FIT *) node;
	gf_sg_mfint32_del(p->FAPs);
	gf_sg_mfint32_del(p->Graph);
	gf_sg_mfint32_del(p->numeratorExp);
	gf_sg_mfint32_del(p->denominatorExp);
	gf_sg_mfint32_del(p->numeratorImpulse);
	gf_sg_mfint32_del(p->numeratorTerms);
	gf_sg_mfint32_del(p->denominatorTerms);
	gf_sg_mffloat_del(p->numeratorCoefs);
	gf_sg_mffloat_del(p->denominatorCoefs);
	gf_node_free((GF_Node *) p);
}

static const u16 FIT_Def2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};
static const u16 FIT_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};
static const u16 FIT_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};

static u32 FIT_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 9;
	case GF_SG_FIELD_CODING_DEF: return 9;
	case GF_SG_FIELD_CODING_OUT: return 9;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 9;
	}
}

static GF_Err FIT_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = FIT_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = FIT_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = FIT_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err FIT_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "FAPs";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_FIT *) node)->FAPs;
		return GF_OK;
	case 1:
		info->name = "Graph";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_FIT *) node)->Graph;
		return GF_OK;
	case 2:
		info->name = "numeratorExp";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_FIT *) node)->numeratorExp;
		return GF_OK;
	case 3:
		info->name = "denominatorExp";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_FIT *) node)->denominatorExp;
		return GF_OK;
	case 4:
		info->name = "numeratorImpulse";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_FIT *) node)->numeratorImpulse;
		return GF_OK;
	case 5:
		info->name = "numeratorTerms";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_FIT *) node)->numeratorTerms;
		return GF_OK;
	case 6:
		info->name = "denominatorTerms";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_FIT *) node)->denominatorTerms;
		return GF_OK;
	case 7:
		info->name = "numeratorCoefs";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_FIT *) node)->numeratorCoefs;
		return GF_OK;
	case 8:
		info->name = "denominatorCoefs";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_FIT *) node)->denominatorCoefs;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 FIT_get_field_index_by_name(char *name)
{
	if (!strcmp("FAPs", name)) return 0;
	if (!strcmp("Graph", name)) return 1;
	if (!strcmp("numeratorExp", name)) return 2;
	if (!strcmp("denominatorExp", name)) return 3;
	if (!strcmp("numeratorImpulse", name)) return 4;
	if (!strcmp("numeratorTerms", name)) return 5;
	if (!strcmp("denominatorTerms", name)) return 6;
	if (!strcmp("numeratorCoefs", name)) return 7;
	if (!strcmp("denominatorCoefs", name)) return 8;
	return -1;
	}
static Bool FIT_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 7;
		*b_min = FLT2FIX(-1);
		*b_max = FLT2FIX(68);
		return 1;
	case 1:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 7;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(68);
		return 1;
	case 2:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(15);
		return 1;
	case 3:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(15);
		return 1;
	case 4:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 10;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1023);
		return 1;
	case 5:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(10);
		return 1;
	case 6:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(10);
		return 1;
	default:
		return 0;
	}
}



GF_Node *FIT_Create()
{
	M_FIT *p;
	GF_SAFEALLOC(p, M_FIT);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_FIT);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	Fog Node deletion
*/

static void Fog_Del(GF_Node *node)
{
	M_Fog *p = (M_Fog *) node;
	gf_sg_sfstring_del(p->fogType);
	gf_node_free((GF_Node *) p);
}

static const u16 Fog_Def2All[] = { 0, 1, 2};
static const u16 Fog_In2All[] = { 0, 1, 2, 3};
static const u16 Fog_Out2All[] = { 0, 1, 2, 4};
static const u16 Fog_Dyn2All[] = { 0, 2};

static u32 Fog_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 3;
	case GF_SG_FIELD_CODING_OUT: return 4;
	case GF_SG_FIELD_CODING_DYN: return 2;
	default:
		return 5;
	}
}

static GF_Err Fog_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Fog_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Fog_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Fog_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Fog_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Fog_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "color";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFCOLOR;
		info->far_ptr = & ((M_Fog *) node)->color;
		return GF_OK;
	case 1:
		info->name = "fogType";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_Fog *) node)->fogType;
		return GF_OK;
	case 2:
		info->name = "visibilityRange";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Fog *) node)->visibilityRange;
		return GF_OK;
	case 3:
		info->name = "set_bind";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Fog *)node)->on_set_bind;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Fog *) node)->set_bind;
		return GF_OK;
	case 4:
		info->name = "isBound";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Fog *) node)->isBound;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Fog_get_field_index_by_name(char *name)
{
	if (!strcmp("color", name)) return 0;
	if (!strcmp("fogType", name)) return 1;
	if (!strcmp("visibilityRange", name)) return 2;
	if (!strcmp("set_bind", name)) return 3;
	if (!strcmp("isBound", name)) return 4;
	return -1;
	}
static Bool Fog_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 4;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 2:
		*AType = 7;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Fog_Create()
{
	M_Fog *p;
	GF_SAFEALLOC(p, M_Fog);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Fog);

	/*default field values*/
	p->color.red = FLT2FIX(1);
	p->color.green = FLT2FIX(1);
	p->color.blue = FLT2FIX(1);
	p->fogType.buffer = (char*)malloc(sizeof(char) * 7);
	strcpy(p->fogType.buffer, "LINEAR");
	p->visibilityRange = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	FontStyle Node deletion
*/

static void FontStyle_Del(GF_Node *node)
{
	M_FontStyle *p = (M_FontStyle *) node;
	gf_sg_mfstring_del(p->family);
	gf_sg_mfstring_del(p->justify);
	gf_sg_sfstring_del(p->language);
	gf_sg_sfstring_del(p->style);
	gf_node_free((GF_Node *) p);
}

static const u16 FontStyle_Def2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};
static const u16 FontStyle_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};
static const u16 FontStyle_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};

static u32 FontStyle_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 9;
	case GF_SG_FIELD_CODING_DEF: return 9;
	case GF_SG_FIELD_CODING_OUT: return 9;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 9;
	}
}

static GF_Err FontStyle_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = FontStyle_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = FontStyle_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = FontStyle_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err FontStyle_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "family";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFSTRING;
		info->far_ptr = & ((M_FontStyle *) node)->family;
		return GF_OK;
	case 1:
		info->name = "horizontal";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_FontStyle *) node)->horizontal;
		return GF_OK;
	case 2:
		info->name = "justify";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFSTRING;
		info->far_ptr = & ((M_FontStyle *) node)->justify;
		return GF_OK;
	case 3:
		info->name = "language";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_FontStyle *) node)->language;
		return GF_OK;
	case 4:
		info->name = "leftToRight";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_FontStyle *) node)->leftToRight;
		return GF_OK;
	case 5:
		info->name = "size";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_FontStyle *) node)->size;
		return GF_OK;
	case 6:
		info->name = "spacing";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_FontStyle *) node)->spacing;
		return GF_OK;
	case 7:
		info->name = "style";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_FontStyle *) node)->style;
		return GF_OK;
	case 8:
		info->name = "topToBottom";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_FontStyle *) node)->topToBottom;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 FontStyle_get_field_index_by_name(char *name)
{
	if (!strcmp("family", name)) return 0;
	if (!strcmp("horizontal", name)) return 1;
	if (!strcmp("justify", name)) return 2;
	if (!strcmp("language", name)) return 3;
	if (!strcmp("leftToRight", name)) return 4;
	if (!strcmp("size", name)) return 5;
	if (!strcmp("spacing", name)) return 6;
	if (!strcmp("style", name)) return 7;
	if (!strcmp("topToBottom", name)) return 8;
	return -1;
	}
static Bool FontStyle_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 5:
		*AType = 0;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 6:
		*AType = 0;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *FontStyle_Create()
{
	M_FontStyle *p;
	GF_SAFEALLOC(p, M_FontStyle);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_FontStyle);

	/*default field values*/
	p->family.vals = (char**)malloc(sizeof(SFString)*1);
	p->family.count = 1;
	p->family.vals[0] = (char*)malloc(sizeof(char) * 6);
	strcpy(p->family.vals[0], "SERIF");
	p->horizontal = 1;
	p->justify.vals = (char**)malloc(sizeof(SFString)*1);
	p->justify.count = 1;
	p->justify.vals[0] = (char*)malloc(sizeof(char) * 6);
	strcpy(p->justify.vals[0], "BEGIN");
	p->leftToRight = 1;
	p->size = FLT2FIX(1.0);
	p->spacing = FLT2FIX(1.0);
	p->style.buffer = (char*)malloc(sizeof(char) * 6);
	strcpy(p->style.buffer, "PLAIN");
	p->topToBottom = 1;
	return (GF_Node *)p;
}


/*
	Form Node deletion
*/

static void Form_Del(GF_Node *node)
{
	M_Form *p = (M_Form *) node;
	gf_sg_mfint32_del(p->groups);
	gf_sg_mfstring_del(p->constraints);
	gf_sg_mfint32_del(p->groupsIndex);
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 Form_Def2All[] = { 2, 3, 4, 5, 6};
static const u16 Form_In2All[] = { 0, 1, 2, 3, 4, 5, 6};
static const u16 Form_Out2All[] = { 2, 3, 4, 5, 6};
static const u16 Form_Dyn2All[] = { 3};

static u32 Form_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 7;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 5;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 7;
	}
}

static GF_Err Form_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Form_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Form_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Form_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Form_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Form_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Form *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_Form *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Form *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_Form *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_Form *)node)->children;
		return GF_OK;
	case 3:
		info->name = "size";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_Form *) node)->size;
		return GF_OK;
	case 4:
		info->name = "groups";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_Form *) node)->groups;
		return GF_OK;
	case 5:
		info->name = "constraints";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFSTRING;
		info->far_ptr = & ((M_Form *) node)->constraints;
		return GF_OK;
	case 6:
		info->name = "groupsIndex";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_Form *) node)->groupsIndex;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Form_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	if (!strcmp("size", name)) return 3;
	if (!strcmp("groups", name)) return 4;
	if (!strcmp("constraints", name)) return 5;
	if (!strcmp("groupsIndex", name)) return 6;
	return -1;
	}
static Bool Form_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 3:
		*AType = 12;
		*QType = 12;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 4:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 10;
		*b_min = FLT2FIX(-1);
		*b_max = FLT2FIX(1022);
		return 1;
	case 6:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 10;
		*b_min = FLT2FIX(-1);
		*b_max = FLT2FIX(1022);
		return 1;
	default:
		return 0;
	}
}



GF_Node *Form_Create()
{
	M_Form *p;
	GF_SAFEALLOC(p, M_Form);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Form);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->size.x = FLT2FIX(-1);
	p->size.y = FLT2FIX(-1);
	return (GF_Node *)p;
}


/*
	Group Node deletion
*/

static void Group_Del(GF_Node *node)
{
	M_Group *p = (M_Group *) node;
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 Group_Def2All[] = { 2};
static const u16 Group_In2All[] = { 0, 1, 2};
static const u16 Group_Out2All[] = { 2};

static u32 Group_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 1;
	case GF_SG_FIELD_CODING_OUT: return 1;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 3;
	}
}

static GF_Err Group_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Group_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Group_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Group_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Group_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Group *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_Group *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Group *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_Group *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_Group *)node)->children;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Group_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	return -1;
	}
static Bool Group_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *Group_Create()
{
	M_Group *p;
	GF_SAFEALLOC(p, M_Group);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Group);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	ImageTexture Node deletion
*/

static void ImageTexture_Del(GF_Node *node)
{
	M_ImageTexture *p = (M_ImageTexture *) node;
	gf_sg_mfurl_del(p->url);
	gf_node_free((GF_Node *) p);
}

static const u16 ImageTexture_Def2All[] = { 0, 1, 2};
static const u16 ImageTexture_In2All[] = { 0};
static const u16 ImageTexture_Out2All[] = { 0};

static u32 ImageTexture_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 1;
	case GF_SG_FIELD_CODING_DEF: return 3;
	case GF_SG_FIELD_CODING_OUT: return 1;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 3;
	}
}

static GF_Err ImageTexture_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = ImageTexture_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = ImageTexture_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = ImageTexture_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err ImageTexture_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "url";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_ImageTexture *) node)->url;
		return GF_OK;
	case 1:
		info->name = "repeatS";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_ImageTexture *) node)->repeatS;
		return GF_OK;
	case 2:
		info->name = "repeatT";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_ImageTexture *) node)->repeatT;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 ImageTexture_get_field_index_by_name(char *name)
{
	if (!strcmp("url", name)) return 0;
	if (!strcmp("repeatS", name)) return 1;
	if (!strcmp("repeatT", name)) return 2;
	return -1;
	}
static Bool ImageTexture_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *ImageTexture_Create()
{
	M_ImageTexture *p;
	GF_SAFEALLOC(p, M_ImageTexture);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_ImageTexture);

	/*default field values*/
	p->repeatS = 1;
	p->repeatT = 1;
	return (GF_Node *)p;
}


/*
	IndexedFaceSet Node deletion
*/

static void IndexedFaceSet_Del(GF_Node *node)
{
	M_IndexedFaceSet *p = (M_IndexedFaceSet *) node;
	gf_sg_mfint32_del(p->set_colorIndex);
	gf_sg_mfint32_del(p->set_coordIndex);
	gf_sg_mfint32_del(p->set_normalIndex);
	gf_sg_mfint32_del(p->set_texCoordIndex);
	gf_node_unregister((GF_Node *) p->color, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->coord, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->normal, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->texCoord, (GF_Node *) p);	
	gf_sg_mfint32_del(p->colorIndex);
	gf_sg_mfint32_del(p->coordIndex);
	gf_sg_mfint32_del(p->normalIndex);
	gf_sg_mfint32_del(p->texCoordIndex);
	gf_node_free((GF_Node *) p);
}

static const u16 IndexedFaceSet_Def2All[] = { 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
static const u16 IndexedFaceSet_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7};
static const u16 IndexedFaceSet_Out2All[] = { 4, 5, 6, 7};

static u32 IndexedFaceSet_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 8;
	case GF_SG_FIELD_CODING_DEF: return 14;
	case GF_SG_FIELD_CODING_OUT: return 4;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 18;
	}
}

static GF_Err IndexedFaceSet_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = IndexedFaceSet_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = IndexedFaceSet_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = IndexedFaceSet_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err IndexedFaceSet_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_colorIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_IndexedFaceSet *)node)->on_set_colorIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_IndexedFaceSet *) node)->set_colorIndex;
		return GF_OK;
	case 1:
		info->name = "set_coordIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_IndexedFaceSet *)node)->on_set_coordIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_IndexedFaceSet *) node)->set_coordIndex;
		return GF_OK;
	case 2:
		info->name = "set_normalIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_IndexedFaceSet *)node)->on_set_normalIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_IndexedFaceSet *) node)->set_normalIndex;
		return GF_OK;
	case 3:
		info->name = "set_texCoordIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_IndexedFaceSet *)node)->on_set_texCoordIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_IndexedFaceSet *) node)->set_texCoordIndex;
		return GF_OK;
	case 4:
		info->name = "color";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFColorNode;
		info->far_ptr = & ((M_IndexedFaceSet *)node)->color;
		return GF_OK;
	case 5:
		info->name = "coord";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFCoordinateNode;
		info->far_ptr = & ((M_IndexedFaceSet *)node)->coord;
		return GF_OK;
	case 6:
		info->name = "normal";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFNormalNode;
		info->far_ptr = & ((M_IndexedFaceSet *)node)->normal;
		return GF_OK;
	case 7:
		info->name = "texCoord";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFTextureCoordinateNode;
		info->far_ptr = & ((M_IndexedFaceSet *)node)->texCoord;
		return GF_OK;
	case 8:
		info->name = "ccw";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_IndexedFaceSet *) node)->ccw;
		return GF_OK;
	case 9:
		info->name = "colorIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_IndexedFaceSet *) node)->colorIndex;
		return GF_OK;
	case 10:
		info->name = "colorPerVertex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_IndexedFaceSet *) node)->colorPerVertex;
		return GF_OK;
	case 11:
		info->name = "convex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_IndexedFaceSet *) node)->convex;
		return GF_OK;
	case 12:
		info->name = "coordIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_IndexedFaceSet *) node)->coordIndex;
		return GF_OK;
	case 13:
		info->name = "creaseAngle";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_IndexedFaceSet *) node)->creaseAngle;
		return GF_OK;
	case 14:
		info->name = "normalIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_IndexedFaceSet *) node)->normalIndex;
		return GF_OK;
	case 15:
		info->name = "normalPerVertex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_IndexedFaceSet *) node)->normalPerVertex;
		return GF_OK;
	case 16:
		info->name = "solid";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_IndexedFaceSet *) node)->solid;
		return GF_OK;
	case 17:
		info->name = "texCoordIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_IndexedFaceSet *) node)->texCoordIndex;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 IndexedFaceSet_get_field_index_by_name(char *name)
{
	if (!strcmp("set_colorIndex", name)) return 0;
	if (!strcmp("set_coordIndex", name)) return 1;
	if (!strcmp("set_normalIndex", name)) return 2;
	if (!strcmp("set_texCoordIndex", name)) return 3;
	if (!strcmp("color", name)) return 4;
	if (!strcmp("coord", name)) return 5;
	if (!strcmp("normal", name)) return 6;
	if (!strcmp("texCoord", name)) return 7;
	if (!strcmp("ccw", name)) return 8;
	if (!strcmp("colorIndex", name)) return 9;
	if (!strcmp("colorPerVertex", name)) return 10;
	if (!strcmp("convex", name)) return 11;
	if (!strcmp("coordIndex", name)) return 12;
	if (!strcmp("creaseAngle", name)) return 13;
	if (!strcmp("normalIndex", name)) return 14;
	if (!strcmp("normalPerVertex", name)) return 15;
	if (!strcmp("solid", name)) return 16;
	if (!strcmp("texCoordIndex", name)) return 17;
	return -1;
	}
static Bool IndexedFaceSet_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 9:
		*AType = 0;
		*QType = 14;
		*b_min = FLT2FIX(-1);
		*b_max = FIX_MAX;
		return 1;
	case 12:
		*AType = 0;
		*QType = 14;
		*b_min = FLT2FIX(-1);
		*b_max = FIX_MAX;
		return 1;
	case 13:
		*AType = 0;
		*QType = 6;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(6.2831853);
		return 1;
	case 14:
		*AType = 0;
		*QType = 14;
		*b_min = FLT2FIX(-1);
		*b_max = FIX_MAX;
		return 1;
	case 17:
		*AType = 0;
		*QType = 14;
		*b_min = FLT2FIX(-1);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *IndexedFaceSet_Create()
{
	M_IndexedFaceSet *p;
	GF_SAFEALLOC(p, M_IndexedFaceSet);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_IndexedFaceSet);

	/*default field values*/
	p->ccw = 1;
	p->colorPerVertex = 1;
	p->convex = 1;
	p->creaseAngle = FLT2FIX(0.0);
	p->normalPerVertex = 1;
	p->solid = 1;
	return (GF_Node *)p;
}


/*
	IndexedFaceSet2D Node deletion
*/

static void IndexedFaceSet2D_Del(GF_Node *node)
{
	M_IndexedFaceSet2D *p = (M_IndexedFaceSet2D *) node;
	gf_sg_mfint32_del(p->set_colorIndex);
	gf_sg_mfint32_del(p->set_coordIndex);
	gf_sg_mfint32_del(p->set_texCoordIndex);
	gf_node_unregister((GF_Node *) p->color, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->coord, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->texCoord, (GF_Node *) p);	
	gf_sg_mfint32_del(p->colorIndex);
	gf_sg_mfint32_del(p->coordIndex);
	gf_sg_mfint32_del(p->texCoordIndex);
	gf_node_free((GF_Node *) p);
}

static const u16 IndexedFaceSet2D_Def2All[] = { 3, 4, 5, 6, 7, 8, 9, 10};
static const u16 IndexedFaceSet2D_In2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 IndexedFaceSet2D_Out2All[] = { 3, 4, 5};

static u32 IndexedFaceSet2D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 6;
	case GF_SG_FIELD_CODING_DEF: return 8;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 11;
	}
}

static GF_Err IndexedFaceSet2D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = IndexedFaceSet2D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = IndexedFaceSet2D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = IndexedFaceSet2D_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err IndexedFaceSet2D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_colorIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_IndexedFaceSet2D *)node)->on_set_colorIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_IndexedFaceSet2D *) node)->set_colorIndex;
		return GF_OK;
	case 1:
		info->name = "set_coordIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_IndexedFaceSet2D *)node)->on_set_coordIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_IndexedFaceSet2D *) node)->set_coordIndex;
		return GF_OK;
	case 2:
		info->name = "set_texCoordIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_IndexedFaceSet2D *)node)->on_set_texCoordIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_IndexedFaceSet2D *) node)->set_texCoordIndex;
		return GF_OK;
	case 3:
		info->name = "color";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFColorNode;
		info->far_ptr = & ((M_IndexedFaceSet2D *)node)->color;
		return GF_OK;
	case 4:
		info->name = "coord";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFCoordinate2DNode;
		info->far_ptr = & ((M_IndexedFaceSet2D *)node)->coord;
		return GF_OK;
	case 5:
		info->name = "texCoord";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFTextureCoordinateNode;
		info->far_ptr = & ((M_IndexedFaceSet2D *)node)->texCoord;
		return GF_OK;
	case 6:
		info->name = "colorIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_IndexedFaceSet2D *) node)->colorIndex;
		return GF_OK;
	case 7:
		info->name = "colorPerVertex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_IndexedFaceSet2D *) node)->colorPerVertex;
		return GF_OK;
	case 8:
		info->name = "convex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_IndexedFaceSet2D *) node)->convex;
		return GF_OK;
	case 9:
		info->name = "coordIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_IndexedFaceSet2D *) node)->coordIndex;
		return GF_OK;
	case 10:
		info->name = "texCoordIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_IndexedFaceSet2D *) node)->texCoordIndex;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 IndexedFaceSet2D_get_field_index_by_name(char *name)
{
	if (!strcmp("set_colorIndex", name)) return 0;
	if (!strcmp("set_coordIndex", name)) return 1;
	if (!strcmp("set_texCoordIndex", name)) return 2;
	if (!strcmp("color", name)) return 3;
	if (!strcmp("coord", name)) return 4;
	if (!strcmp("texCoord", name)) return 5;
	if (!strcmp("colorIndex", name)) return 6;
	if (!strcmp("colorPerVertex", name)) return 7;
	if (!strcmp("convex", name)) return 8;
	if (!strcmp("coordIndex", name)) return 9;
	if (!strcmp("texCoordIndex", name)) return 10;
	return -1;
	}
static Bool IndexedFaceSet2D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 6:
		*AType = 0;
		*QType = 14;
		*b_min = FLT2FIX(-1);
		*b_max = FIX_MAX;
		return 1;
	case 9:
		*AType = 0;
		*QType = 14;
		*b_min = FLT2FIX(-1);
		*b_max = FIX_MAX;
		return 1;
	case 10:
		*AType = 0;
		*QType = 14;
		*b_min = FLT2FIX(-1);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *IndexedFaceSet2D_Create()
{
	M_IndexedFaceSet2D *p;
	GF_SAFEALLOC(p, M_IndexedFaceSet2D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_IndexedFaceSet2D);

	/*default field values*/
	p->colorPerVertex = 1;
	p->convex = 1;
	return (GF_Node *)p;
}


/*
	IndexedLineSet Node deletion
*/

static void IndexedLineSet_Del(GF_Node *node)
{
	M_IndexedLineSet *p = (M_IndexedLineSet *) node;
	gf_sg_mfint32_del(p->set_colorIndex);
	gf_sg_mfint32_del(p->set_coordIndex);
	gf_node_unregister((GF_Node *) p->color, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->coord, (GF_Node *) p);	
	gf_sg_mfint32_del(p->colorIndex);
	gf_sg_mfint32_del(p->coordIndex);
	gf_node_free((GF_Node *) p);
}

static const u16 IndexedLineSet_Def2All[] = { 2, 3, 4, 5, 6};
static const u16 IndexedLineSet_In2All[] = { 0, 1, 2, 3};
static const u16 IndexedLineSet_Out2All[] = { 2, 3};

static u32 IndexedLineSet_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 2;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 7;
	}
}

static GF_Err IndexedLineSet_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = IndexedLineSet_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = IndexedLineSet_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = IndexedLineSet_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err IndexedLineSet_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_colorIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_IndexedLineSet *)node)->on_set_colorIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_IndexedLineSet *) node)->set_colorIndex;
		return GF_OK;
	case 1:
		info->name = "set_coordIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_IndexedLineSet *)node)->on_set_coordIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_IndexedLineSet *) node)->set_coordIndex;
		return GF_OK;
	case 2:
		info->name = "color";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFColorNode;
		info->far_ptr = & ((M_IndexedLineSet *)node)->color;
		return GF_OK;
	case 3:
		info->name = "coord";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFCoordinateNode;
		info->far_ptr = & ((M_IndexedLineSet *)node)->coord;
		return GF_OK;
	case 4:
		info->name = "colorIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_IndexedLineSet *) node)->colorIndex;
		return GF_OK;
	case 5:
		info->name = "colorPerVertex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_IndexedLineSet *) node)->colorPerVertex;
		return GF_OK;
	case 6:
		info->name = "coordIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_IndexedLineSet *) node)->coordIndex;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 IndexedLineSet_get_field_index_by_name(char *name)
{
	if (!strcmp("set_colorIndex", name)) return 0;
	if (!strcmp("set_coordIndex", name)) return 1;
	if (!strcmp("color", name)) return 2;
	if (!strcmp("coord", name)) return 3;
	if (!strcmp("colorIndex", name)) return 4;
	if (!strcmp("colorPerVertex", name)) return 5;
	if (!strcmp("coordIndex", name)) return 6;
	return -1;
	}
static Bool IndexedLineSet_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 4:
		*AType = 0;
		*QType = 14;
		*b_min = FLT2FIX(-1);
		*b_max = FIX_MAX;
		return 1;
	case 6:
		*AType = 0;
		*QType = 14;
		*b_min = FLT2FIX(-1);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *IndexedLineSet_Create()
{
	M_IndexedLineSet *p;
	GF_SAFEALLOC(p, M_IndexedLineSet);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_IndexedLineSet);

	/*default field values*/
	p->colorPerVertex = 1;
	return (GF_Node *)p;
}


/*
	IndexedLineSet2D Node deletion
*/

static void IndexedLineSet2D_Del(GF_Node *node)
{
	M_IndexedLineSet2D *p = (M_IndexedLineSet2D *) node;
	gf_sg_mfint32_del(p->set_colorIndex);
	gf_sg_mfint32_del(p->set_coordIndex);
	gf_node_unregister((GF_Node *) p->color, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->coord, (GF_Node *) p);	
	gf_sg_mfint32_del(p->colorIndex);
	gf_sg_mfint32_del(p->coordIndex);
	gf_node_free((GF_Node *) p);
}

static const u16 IndexedLineSet2D_Def2All[] = { 2, 3, 4, 5, 6};
static const u16 IndexedLineSet2D_In2All[] = { 0, 1, 2, 3};
static const u16 IndexedLineSet2D_Out2All[] = { 2, 3};

static u32 IndexedLineSet2D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 2;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 7;
	}
}

static GF_Err IndexedLineSet2D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = IndexedLineSet2D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = IndexedLineSet2D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = IndexedLineSet2D_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err IndexedLineSet2D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_colorIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_IndexedLineSet2D *)node)->on_set_colorIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_IndexedLineSet2D *) node)->set_colorIndex;
		return GF_OK;
	case 1:
		info->name = "set_coordIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_IndexedLineSet2D *)node)->on_set_coordIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_IndexedLineSet2D *) node)->set_coordIndex;
		return GF_OK;
	case 2:
		info->name = "color";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFColorNode;
		info->far_ptr = & ((M_IndexedLineSet2D *)node)->color;
		return GF_OK;
	case 3:
		info->name = "coord";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFCoordinate2DNode;
		info->far_ptr = & ((M_IndexedLineSet2D *)node)->coord;
		return GF_OK;
	case 4:
		info->name = "colorIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_IndexedLineSet2D *) node)->colorIndex;
		return GF_OK;
	case 5:
		info->name = "colorPerVertex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_IndexedLineSet2D *) node)->colorPerVertex;
		return GF_OK;
	case 6:
		info->name = "coordIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_IndexedLineSet2D *) node)->coordIndex;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 IndexedLineSet2D_get_field_index_by_name(char *name)
{
	if (!strcmp("set_colorIndex", name)) return 0;
	if (!strcmp("set_coordIndex", name)) return 1;
	if (!strcmp("color", name)) return 2;
	if (!strcmp("coord", name)) return 3;
	if (!strcmp("colorIndex", name)) return 4;
	if (!strcmp("colorPerVertex", name)) return 5;
	if (!strcmp("coordIndex", name)) return 6;
	return -1;
	}
static Bool IndexedLineSet2D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 4:
		*AType = 0;
		*QType = 14;
		*b_min = FLT2FIX(-1);
		*b_max = FIX_MAX;
		return 1;
	case 6:
		*AType = 0;
		*QType = 14;
		*b_min = FLT2FIX(-1);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *IndexedLineSet2D_Create()
{
	M_IndexedLineSet2D *p;
	GF_SAFEALLOC(p, M_IndexedLineSet2D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_IndexedLineSet2D);

	/*default field values*/
	p->colorPerVertex = 1;
	return (GF_Node *)p;
}


/*
	Inline Node deletion
*/

static void Inline_Del(GF_Node *node)
{
	M_Inline *p = (M_Inline *) node;
	gf_sg_mfurl_del(p->url);
	gf_node_free((GF_Node *) p);
}

static const u16 Inline_Def2All[] = { 0};
static const u16 Inline_In2All[] = { 0};
static const u16 Inline_Out2All[] = { 0};

static u32 Inline_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 1;
	case GF_SG_FIELD_CODING_DEF: return 1;
	case GF_SG_FIELD_CODING_OUT: return 1;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 1;
	}
}

static GF_Err Inline_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Inline_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Inline_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Inline_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Inline_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "url";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_Inline *) node)->url;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Inline_get_field_index_by_name(char *name)
{
	if (!strcmp("url", name)) return 0;
	return -1;
	}
static Bool Inline_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *Inline_Create()
{
	M_Inline *p;
	GF_SAFEALLOC(p, M_Inline);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Inline);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	LOD Node deletion
*/

static void LOD_Del(GF_Node *node)
{
	M_LOD *p = (M_LOD *) node;
	gf_node_unregister_children((GF_Node *) p, p->level);	
	gf_sg_mffloat_del(p->range);
	gf_node_free((GF_Node *) p);
}

static const u16 LOD_Def2All[] = { 0, 1, 2};
static const u16 LOD_In2All[] = { 0};
static const u16 LOD_Out2All[] = { 0};

static u32 LOD_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 1;
	case GF_SG_FIELD_CODING_DEF: return 3;
	case GF_SG_FIELD_CODING_OUT: return 1;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 3;
	}
}

static GF_Err LOD_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = LOD_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = LOD_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = LOD_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err LOD_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "level";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_LOD *)node)->level;
		return GF_OK;
	case 1:
		info->name = "center";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_LOD *) node)->center;
		return GF_OK;
	case 2:
		info->name = "range";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_LOD *) node)->range;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 LOD_get_field_index_by_name(char *name)
{
	if (!strcmp("level", name)) return 0;
	if (!strcmp("center", name)) return 1;
	if (!strcmp("range", name)) return 2;
	return -1;
	}
static Bool LOD_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 1;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 2:
		*AType = 0;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *LOD_Create()
{
	M_LOD *p;
	GF_SAFEALLOC(p, M_LOD);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_LOD);

	/*default field values*/
	p->center.x = FLT2FIX(0);
	p->center.y = FLT2FIX(0);
	p->center.z = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	Layer2D Node deletion
*/

static void Layer2D_Del(GF_Node *node)
{
	M_Layer2D *p = (M_Layer2D *) node;
	gf_node_unregister((GF_Node *) p->background, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->viewport, (GF_Node *) p);	
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 Layer2D_Def2All[] = { 2, 3, 4, 5};
static const u16 Layer2D_In2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 Layer2D_Out2All[] = { 2, 3, 4, 5};
static const u16 Layer2D_Dyn2All[] = { 3};

static u32 Layer2D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 6;
	case GF_SG_FIELD_CODING_DEF: return 4;
	case GF_SG_FIELD_CODING_OUT: return 4;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 6;
	}
}

static GF_Err Layer2D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Layer2D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Layer2D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Layer2D_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Layer2D_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Layer2D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Layer2D *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_Layer2D *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Layer2D *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_Layer2D *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_Layer2D *)node)->children;
		return GF_OK;
	case 3:
		info->name = "size";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_Layer2D *) node)->size;
		return GF_OK;
	case 4:
		info->name = "background";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFBackground2DNode;
		info->far_ptr = & ((M_Layer2D *)node)->background;
		return GF_OK;
	case 5:
		info->name = "viewport";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFViewportNode;
		info->far_ptr = & ((M_Layer2D *)node)->viewport;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Layer2D_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	if (!strcmp("size", name)) return 3;
	if (!strcmp("background", name)) return 4;
	if (!strcmp("viewport", name)) return 5;
	return -1;
	}
static Bool Layer2D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 3:
		*AType = 12;
		*QType = 12;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Layer2D_Create()
{
	M_Layer2D *p;
	GF_SAFEALLOC(p, M_Layer2D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Layer2D);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->size.x = FLT2FIX(-1);
	p->size.y = FLT2FIX(-1);
	return (GF_Node *)p;
}


/*
	Layer3D Node deletion
*/

static void Layer3D_Del(GF_Node *node)
{
	M_Layer3D *p = (M_Layer3D *) node;
	gf_node_unregister((GF_Node *) p->background, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->fog, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->navigationInfo, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->viewpoint, (GF_Node *) p);	
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 Layer3D_Def2All[] = { 2, 3, 4, 5, 6, 7};
static const u16 Layer3D_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7};
static const u16 Layer3D_Out2All[] = { 2, 3, 4, 5, 6, 7};
static const u16 Layer3D_Dyn2All[] = { 3};

static u32 Layer3D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 8;
	case GF_SG_FIELD_CODING_DEF: return 6;
	case GF_SG_FIELD_CODING_OUT: return 6;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 8;
	}
}

static GF_Err Layer3D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Layer3D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Layer3D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Layer3D_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Layer3D_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Layer3D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Layer3D *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_Layer3D *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Layer3D *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_Layer3D *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_Layer3D *)node)->children;
		return GF_OK;
	case 3:
		info->name = "size";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_Layer3D *) node)->size;
		return GF_OK;
	case 4:
		info->name = "background";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFBackground3DNode;
		info->far_ptr = & ((M_Layer3D *)node)->background;
		return GF_OK;
	case 5:
		info->name = "fog";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFFogNode;
		info->far_ptr = & ((M_Layer3D *)node)->fog;
		return GF_OK;
	case 6:
		info->name = "navigationInfo";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFNavigationInfoNode;
		info->far_ptr = & ((M_Layer3D *)node)->navigationInfo;
		return GF_OK;
	case 7:
		info->name = "viewpoint";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFViewpointNode;
		info->far_ptr = & ((M_Layer3D *)node)->viewpoint;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Layer3D_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	if (!strcmp("size", name)) return 3;
	if (!strcmp("background", name)) return 4;
	if (!strcmp("fog", name)) return 5;
	if (!strcmp("navigationInfo", name)) return 6;
	if (!strcmp("viewpoint", name)) return 7;
	return -1;
	}
static Bool Layer3D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 3:
		*AType = 12;
		*QType = 12;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Layer3D_Create()
{
	M_Layer3D *p;
	GF_SAFEALLOC(p, M_Layer3D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Layer3D);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->size.x = FLT2FIX(-1);
	p->size.y = FLT2FIX(-1);
	return (GF_Node *)p;
}


/*
	Layout Node deletion
*/

static void Layout_Del(GF_Node *node)
{
	M_Layout *p = (M_Layout *) node;
	gf_sg_mfstring_del(p->justify);
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 Layout_Def2All[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
static const u16 Layout_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
static const u16 Layout_Out2All[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
static const u16 Layout_Dyn2All[] = { 4, 9, 13};

static u32 Layout_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 15;
	case GF_SG_FIELD_CODING_DEF: return 13;
	case GF_SG_FIELD_CODING_OUT: return 13;
	case GF_SG_FIELD_CODING_DYN: return 3;
	default:
		return 15;
	}
}

static GF_Err Layout_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Layout_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Layout_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Layout_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Layout_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Layout_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Layout *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_Layout *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Layout *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_Layout *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_Layout *)node)->children;
		return GF_OK;
	case 3:
		info->name = "wrap";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Layout *) node)->wrap;
		return GF_OK;
	case 4:
		info->name = "size";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_Layout *) node)->size;
		return GF_OK;
	case 5:
		info->name = "horizontal";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Layout *) node)->horizontal;
		return GF_OK;
	case 6:
		info->name = "justify";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFSTRING;
		info->far_ptr = & ((M_Layout *) node)->justify;
		return GF_OK;
	case 7:
		info->name = "leftToRight";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Layout *) node)->leftToRight;
		return GF_OK;
	case 8:
		info->name = "topToBottom";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Layout *) node)->topToBottom;
		return GF_OK;
	case 9:
		info->name = "spacing";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Layout *) node)->spacing;
		return GF_OK;
	case 10:
		info->name = "smoothScroll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Layout *) node)->smoothScroll;
		return GF_OK;
	case 11:
		info->name = "loop";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Layout *) node)->loop;
		return GF_OK;
	case 12:
		info->name = "scrollVertical";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Layout *) node)->scrollVertical;
		return GF_OK;
	case 13:
		info->name = "scrollRate";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Layout *) node)->scrollRate;
		return GF_OK;
	case 14:
		info->name = "scrollMode";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_Layout *) node)->scrollMode;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Layout_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	if (!strcmp("wrap", name)) return 3;
	if (!strcmp("size", name)) return 4;
	if (!strcmp("horizontal", name)) return 5;
	if (!strcmp("justify", name)) return 6;
	if (!strcmp("leftToRight", name)) return 7;
	if (!strcmp("topToBottom", name)) return 8;
	if (!strcmp("spacing", name)) return 9;
	if (!strcmp("smoothScroll", name)) return 10;
	if (!strcmp("loop", name)) return 11;
	if (!strcmp("scrollVertical", name)) return 12;
	if (!strcmp("scrollRate", name)) return 13;
	if (!strcmp("scrollMode", name)) return 14;
	return -1;
	}
static Bool Layout_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 4:
		*AType = 12;
		*QType = 12;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 9:
		*AType = 7;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 13:
		*AType = 7;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 14:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 2;
		*b_min = FLT2FIX(-1);
		*b_max = FLT2FIX(1);
		return 1;
	default:
		return 0;
	}
}



GF_Node *Layout_Create()
{
	M_Layout *p;
	GF_SAFEALLOC(p, M_Layout);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Layout);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->size.x = FLT2FIX(-1);
	p->size.y = FLT2FIX(-1);
	p->horizontal = 1;
	p->justify.vals = (char**)malloc(sizeof(SFString)*1);
	p->justify.count = 1;
	p->justify.vals[0] = (char*)malloc(sizeof(char) * 6);
	strcpy(p->justify.vals[0], "BEGIN");
	p->leftToRight = 1;
	p->topToBottom = 1;
	p->spacing = FLT2FIX(1);
	p->scrollVertical = 1;
	p->scrollRate = FLT2FIX(0);
	p->scrollMode = 0;
	return (GF_Node *)p;
}


/*
	LineProperties Node deletion
*/

static void LineProperties_Del(GF_Node *node)
{
	M_LineProperties *p = (M_LineProperties *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 LineProperties_Def2All[] = { 0, 1, 2};
static const u16 LineProperties_In2All[] = { 0, 1, 2};
static const u16 LineProperties_Out2All[] = { 0, 1, 2};
static const u16 LineProperties_Dyn2All[] = { 0, 2};

static u32 LineProperties_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 3;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 2;
	default:
		return 3;
	}
}

static GF_Err LineProperties_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = LineProperties_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = LineProperties_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = LineProperties_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = LineProperties_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err LineProperties_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "lineColor";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFCOLOR;
		info->far_ptr = & ((M_LineProperties *) node)->lineColor;
		return GF_OK;
	case 1:
		info->name = "lineStyle";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_LineProperties *) node)->lineStyle;
		return GF_OK;
	case 2:
		info->name = "width";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_LineProperties *) node)->width;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 LineProperties_get_field_index_by_name(char *name)
{
	if (!strcmp("lineColor", name)) return 0;
	if (!strcmp("lineStyle", name)) return 1;
	if (!strcmp("width", name)) return 2;
	return -1;
	}
static Bool LineProperties_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 4;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 1:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 3;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(5);
		return 1;
	case 2:
		*AType = 7;
		*QType = 12;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *LineProperties_Create()
{
	M_LineProperties *p;
	GF_SAFEALLOC(p, M_LineProperties);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_LineProperties);

	/*default field values*/
	p->lineColor.red = FLT2FIX(0);
	p->lineColor.green = FLT2FIX(0);
	p->lineColor.blue = FLT2FIX(0);
	p->lineStyle = 0;
	p->width = FLT2FIX(1);
	return (GF_Node *)p;
}


/*
	ListeningPoint Node deletion
*/

static void ListeningPoint_Del(GF_Node *node)
{
	M_ListeningPoint *p = (M_ListeningPoint *) node;
	gf_sg_sfstring_del(p->description);
	gf_node_free((GF_Node *) p);
}

static const u16 ListeningPoint_Def2All[] = { 1, 2, 3, 4};
static const u16 ListeningPoint_In2All[] = { 0, 1, 2, 3};
static const u16 ListeningPoint_Out2All[] = { 1, 2, 3, 5, 6};
static const u16 ListeningPoint_Dyn2All[] = { 2, 3};

static u32 ListeningPoint_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 4;
	case GF_SG_FIELD_CODING_OUT: return 5;
	case GF_SG_FIELD_CODING_DYN: return 2;
	default:
		return 7;
	}
}

static GF_Err ListeningPoint_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = ListeningPoint_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = ListeningPoint_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = ListeningPoint_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = ListeningPoint_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err ListeningPoint_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_bind";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_ListeningPoint *)node)->on_set_bind;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_ListeningPoint *) node)->set_bind;
		return GF_OK;
	case 1:
		info->name = "jump";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_ListeningPoint *) node)->jump;
		return GF_OK;
	case 2:
		info->name = "orientation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFROTATION;
		info->far_ptr = & ((M_ListeningPoint *) node)->orientation;
		return GF_OK;
	case 3:
		info->name = "position";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_ListeningPoint *) node)->position;
		return GF_OK;
	case 4:
		info->name = "description";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_ListeningPoint *) node)->description;
		return GF_OK;
	case 5:
		info->name = "bindTime";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_ListeningPoint *) node)->bindTime;
		return GF_OK;
	case 6:
		info->name = "isBound";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_ListeningPoint *) node)->isBound;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 ListeningPoint_get_field_index_by_name(char *name)
{
	if (!strcmp("set_bind", name)) return 0;
	if (!strcmp("jump", name)) return 1;
	if (!strcmp("orientation", name)) return 2;
	if (!strcmp("position", name)) return 3;
	if (!strcmp("description", name)) return 4;
	if (!strcmp("bindTime", name)) return 5;
	if (!strcmp("isBound", name)) return 6;
	return -1;
	}
static Bool ListeningPoint_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 2:
		*AType = 10;
		*QType = 10;
		return 1;
	case 3:
		*AType = 1;
		*QType = 1;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *ListeningPoint_Create()
{
	M_ListeningPoint *p;
	GF_SAFEALLOC(p, M_ListeningPoint);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_ListeningPoint);

	/*default field values*/
	p->jump = 1;
	p->orientation.x = FLT2FIX(0);
	p->orientation.y = FLT2FIX(0);
	p->orientation.z = FLT2FIX(1);
	p->orientation.q = FLT2FIX(0);
	p->position.x = FLT2FIX(0);
	p->position.y = FLT2FIX(0);
	p->position.z = FLT2FIX(10);
	return (GF_Node *)p;
}


/*
	Material Node deletion
*/

static void Material_Del(GF_Node *node)
{
	M_Material *p = (M_Material *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 Material_Def2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 Material_In2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 Material_Out2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 Material_Dyn2All[] = { 0, 1, 2, 3, 4, 5};

static u32 Material_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 6;
	case GF_SG_FIELD_CODING_DEF: return 6;
	case GF_SG_FIELD_CODING_OUT: return 6;
	case GF_SG_FIELD_CODING_DYN: return 6;
	default:
		return 6;
	}
}

static GF_Err Material_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Material_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Material_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Material_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Material_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Material_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "ambientIntensity";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Material *) node)->ambientIntensity;
		return GF_OK;
	case 1:
		info->name = "diffuseColor";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFCOLOR;
		info->far_ptr = & ((M_Material *) node)->diffuseColor;
		return GF_OK;
	case 2:
		info->name = "emissiveColor";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFCOLOR;
		info->far_ptr = & ((M_Material *) node)->emissiveColor;
		return GF_OK;
	case 3:
		info->name = "shininess";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Material *) node)->shininess;
		return GF_OK;
	case 4:
		info->name = "specularColor";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFCOLOR;
		info->far_ptr = & ((M_Material *) node)->specularColor;
		return GF_OK;
	case 5:
		info->name = "transparency";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Material *) node)->transparency;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Material_get_field_index_by_name(char *name)
{
	if (!strcmp("ambientIntensity", name)) return 0;
	if (!strcmp("diffuseColor", name)) return 1;
	if (!strcmp("emissiveColor", name)) return 2;
	if (!strcmp("shininess", name)) return 3;
	if (!strcmp("specularColor", name)) return 4;
	if (!strcmp("transparency", name)) return 5;
	return -1;
	}
static Bool Material_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 8;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 1:
		*AType = 4;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 2:
		*AType = 4;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 3:
		*AType = 8;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 4:
		*AType = 4;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 5:
		*AType = 8;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	default:
		return 0;
	}
}



GF_Node *Material_Create()
{
	M_Material *p;
	GF_SAFEALLOC(p, M_Material);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Material);

	/*default field values*/
	p->ambientIntensity = FLT2FIX(0.2);
	p->diffuseColor.red = FLT2FIX(0.8);
	p->diffuseColor.green = FLT2FIX(0.8);
	p->diffuseColor.blue = FLT2FIX(0.8);
	p->emissiveColor.red = FLT2FIX(0);
	p->emissiveColor.green = FLT2FIX(0);
	p->emissiveColor.blue = FLT2FIX(0);
	p->shininess = FLT2FIX(0.2);
	p->specularColor.red = FLT2FIX(0);
	p->specularColor.green = FLT2FIX(0);
	p->specularColor.blue = FLT2FIX(0);
	p->transparency = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	Material2D Node deletion
*/

static void Material2D_Del(GF_Node *node)
{
	M_Material2D *p = (M_Material2D *) node;
	gf_node_unregister((GF_Node *) p->lineProps, (GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 Material2D_Def2All[] = { 0, 1, 2, 3};
static const u16 Material2D_In2All[] = { 0, 1, 2, 3};
static const u16 Material2D_Out2All[] = { 0, 1, 2, 3};
static const u16 Material2D_Dyn2All[] = { 0, 3};

static u32 Material2D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 4;
	case GF_SG_FIELD_CODING_OUT: return 4;
	case GF_SG_FIELD_CODING_DYN: return 2;
	default:
		return 4;
	}
}

static GF_Err Material2D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Material2D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Material2D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Material2D_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Material2D_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Material2D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "emissiveColor";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFCOLOR;
		info->far_ptr = & ((M_Material2D *) node)->emissiveColor;
		return GF_OK;
	case 1:
		info->name = "filled";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Material2D *) node)->filled;
		return GF_OK;
	case 2:
		info->name = "lineProps";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFLinePropertiesNode;
		info->far_ptr = & ((M_Material2D *)node)->lineProps;
		return GF_OK;
	case 3:
		info->name = "transparency";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Material2D *) node)->transparency;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Material2D_get_field_index_by_name(char *name)
{
	if (!strcmp("emissiveColor", name)) return 0;
	if (!strcmp("filled", name)) return 1;
	if (!strcmp("lineProps", name)) return 2;
	if (!strcmp("transparency", name)) return 3;
	return -1;
	}
static Bool Material2D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 4;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 3:
		*AType = 8;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	default:
		return 0;
	}
}



GF_Node *Material2D_Create()
{
	M_Material2D *p;
	GF_SAFEALLOC(p, M_Material2D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Material2D);

	/*default field values*/
	p->emissiveColor.red = FLT2FIX(0.8);
	p->emissiveColor.green = FLT2FIX(0.8);
	p->emissiveColor.blue = FLT2FIX(0.8);
	p->transparency = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	MovieTexture Node deletion
*/

static void MovieTexture_Del(GF_Node *node)
{
	M_MovieTexture *p = (M_MovieTexture *) node;
	gf_sg_mfurl_del(p->url);
	gf_node_free((GF_Node *) p);
}

static const u16 MovieTexture_Def2All[] = { 0, 1, 2, 3, 4, 5, 6};
static const u16 MovieTexture_In2All[] = { 0, 1, 2, 3, 4};
static const u16 MovieTexture_Out2All[] = { 0, 1, 2, 3, 4, 7, 8};
static const u16 MovieTexture_Dyn2All[] = { 1};

static u32 MovieTexture_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 5;
	case GF_SG_FIELD_CODING_DEF: return 7;
	case GF_SG_FIELD_CODING_OUT: return 7;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 9;
	}
}

static GF_Err MovieTexture_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = MovieTexture_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = MovieTexture_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = MovieTexture_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = MovieTexture_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err MovieTexture_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "loop";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_MovieTexture *) node)->loop;
		return GF_OK;
	case 1:
		info->name = "speed";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_MovieTexture *) node)->speed;
		return GF_OK;
	case 2:
		info->name = "startTime";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_MovieTexture *) node)->startTime;
		return GF_OK;
	case 3:
		info->name = "stopTime";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_MovieTexture *) node)->stopTime;
		return GF_OK;
	case 4:
		info->name = "url";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_MovieTexture *) node)->url;
		return GF_OK;
	case 5:
		info->name = "repeatS";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_MovieTexture *) node)->repeatS;
		return GF_OK;
	case 6:
		info->name = "repeatT";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_MovieTexture *) node)->repeatT;
		return GF_OK;
	case 7:
		info->name = "duration_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_MovieTexture *) node)->duration_changed;
		return GF_OK;
	case 8:
		info->name = "isActive";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_MovieTexture *) node)->isActive;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 MovieTexture_get_field_index_by_name(char *name)
{
	if (!strcmp("loop", name)) return 0;
	if (!strcmp("speed", name)) return 1;
	if (!strcmp("startTime", name)) return 2;
	if (!strcmp("stopTime", name)) return 3;
	if (!strcmp("url", name)) return 4;
	if (!strcmp("repeatS", name)) return 5;
	if (!strcmp("repeatT", name)) return 6;
	if (!strcmp("duration_changed", name)) return 7;
	if (!strcmp("isActive", name)) return 8;
	return -1;
	}
static Bool MovieTexture_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 7;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *MovieTexture_Create()
{
	M_MovieTexture *p;
	GF_SAFEALLOC(p, M_MovieTexture);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_MovieTexture);

	/*default field values*/
	p->speed = FLT2FIX(1.0);
	p->startTime = 0;
	p->stopTime = 0;
	p->repeatS = 1;
	p->repeatT = 1;
	return (GF_Node *)p;
}


/*
	NavigationInfo Node deletion
*/

static void NavigationInfo_Del(GF_Node *node)
{
	M_NavigationInfo *p = (M_NavigationInfo *) node;
	gf_sg_mffloat_del(p->avatarSize);
	gf_sg_mfstring_del(p->type);
	gf_node_free((GF_Node *) p);
}

static const u16 NavigationInfo_Def2All[] = { 1, 2, 3, 4, 5};
static const u16 NavigationInfo_In2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 NavigationInfo_Out2All[] = { 1, 2, 3, 4, 5, 6};
static const u16 NavigationInfo_Dyn2All[] = { 5};

static u32 NavigationInfo_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 6;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 6;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 7;
	}
}

static GF_Err NavigationInfo_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = NavigationInfo_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = NavigationInfo_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = NavigationInfo_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = NavigationInfo_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err NavigationInfo_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_bind";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_NavigationInfo *)node)->on_set_bind;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_NavigationInfo *) node)->set_bind;
		return GF_OK;
	case 1:
		info->name = "avatarSize";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_NavigationInfo *) node)->avatarSize;
		return GF_OK;
	case 2:
		info->name = "headlight";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_NavigationInfo *) node)->headlight;
		return GF_OK;
	case 3:
		info->name = "speed";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_NavigationInfo *) node)->speed;
		return GF_OK;
	case 4:
		info->name = "type";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFSTRING;
		info->far_ptr = & ((M_NavigationInfo *) node)->type;
		return GF_OK;
	case 5:
		info->name = "visibilityLimit";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_NavigationInfo *) node)->visibilityLimit;
		return GF_OK;
	case 6:
		info->name = "isBound";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_NavigationInfo *) node)->isBound;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 NavigationInfo_get_field_index_by_name(char *name)
{
	if (!strcmp("set_bind", name)) return 0;
	if (!strcmp("avatarSize", name)) return 1;
	if (!strcmp("headlight", name)) return 2;
	if (!strcmp("speed", name)) return 3;
	if (!strcmp("type", name)) return 4;
	if (!strcmp("visibilityLimit", name)) return 5;
	if (!strcmp("isBound", name)) return 6;
	return -1;
	}
static Bool NavigationInfo_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 3:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 5:
		*AType = 7;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *NavigationInfo_Create()
{
	M_NavigationInfo *p;
	GF_SAFEALLOC(p, M_NavigationInfo);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_NavigationInfo);

	/*default field values*/
	p->avatarSize.vals = (SFFloat*)malloc(sizeof(SFFloat)*3);
	p->avatarSize.count = 3;
	p->avatarSize.vals[0] = FLT2FIX(0.25);
	p->avatarSize.vals[1] = FLT2FIX(1.6);
	p->avatarSize.vals[2] = FLT2FIX(0.75);
	p->headlight = 1;
	p->speed = FLT2FIX(1.0);
	p->type.vals = (char**)malloc(sizeof(SFString)*2);
	p->type.count = 2;
	p->type.vals[0] = (char*)malloc(sizeof(char) * 5);
	strcpy(p->type.vals[0], "WALK");
	p->type.vals[1] = (char*)malloc(sizeof(char) * 4);
	strcpy(p->type.vals[1], "ANY");
	p->visibilityLimit = FLT2FIX(0.0);
	return (GF_Node *)p;
}


/*
	Normal Node deletion
*/

static void Normal_Del(GF_Node *node)
{
	M_Normal *p = (M_Normal *) node;
	gf_sg_mfvec3f_del(p->vector);
	gf_node_free((GF_Node *) p);
}

static const u16 Normal_Def2All[] = { 0};
static const u16 Normal_In2All[] = { 0};
static const u16 Normal_Out2All[] = { 0};
static const u16 Normal_Dyn2All[] = { 0};

static u32 Normal_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 1;
	case GF_SG_FIELD_CODING_DEF: return 1;
	case GF_SG_FIELD_CODING_OUT: return 1;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 1;
	}
}

static GF_Err Normal_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Normal_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Normal_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Normal_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Normal_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Normal_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "vector";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC3F;
		info->far_ptr = & ((M_Normal *) node)->vector;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Normal_get_field_index_by_name(char *name)
{
	if (!strcmp("vector", name)) return 0;
	return -1;
	}
static Bool Normal_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 9;
		*QType = 9;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Normal_Create()
{
	M_Normal *p;
	GF_SAFEALLOC(p, M_Normal);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Normal);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	NormalInterpolator Node deletion
*/

static void NormalInterpolator_Del(GF_Node *node)
{
	M_NormalInterpolator *p = (M_NormalInterpolator *) node;
	gf_sg_mffloat_del(p->key);
	gf_sg_mfvec3f_del(p->keyValue);
	gf_sg_mfvec3f_del(p->value_changed);
	gf_node_free((GF_Node *) p);
}

static const u16 NormalInterpolator_Def2All[] = { 1, 2};
static const u16 NormalInterpolator_In2All[] = { 0, 1, 2};
static const u16 NormalInterpolator_Out2All[] = { 1, 2, 3};

static u32 NormalInterpolator_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err NormalInterpolator_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = NormalInterpolator_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = NormalInterpolator_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = NormalInterpolator_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err NormalInterpolator_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_fraction";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_NormalInterpolator *)node)->on_set_fraction;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_NormalInterpolator *) node)->set_fraction;
		return GF_OK;
	case 1:
		info->name = "key";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_NormalInterpolator *) node)->key;
		return GF_OK;
	case 2:
		info->name = "keyValue";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC3F;
		info->far_ptr = & ((M_NormalInterpolator *) node)->keyValue;
		return GF_OK;
	case 3:
		info->name = "value_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_MFVEC3F;
		info->far_ptr = & ((M_NormalInterpolator *) node)->value_changed;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 NormalInterpolator_get_field_index_by_name(char *name)
{
	if (!strcmp("set_fraction", name)) return 0;
	if (!strcmp("key", name)) return 1;
	if (!strcmp("keyValue", name)) return 2;
	if (!strcmp("value_changed", name)) return 3;
	return -1;
	}
static Bool NormalInterpolator_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 2:
		*AType = 0;
		*QType = 9;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *NormalInterpolator_Create()
{
	M_NormalInterpolator *p;
	GF_SAFEALLOC(p, M_NormalInterpolator);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_NormalInterpolator);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	OrderedGroup Node deletion
*/

static void OrderedGroup_Del(GF_Node *node)
{
	M_OrderedGroup *p = (M_OrderedGroup *) node;
	gf_sg_mffloat_del(p->order);
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 OrderedGroup_Def2All[] = { 2, 3};
static const u16 OrderedGroup_In2All[] = { 0, 1, 2, 3};
static const u16 OrderedGroup_Out2All[] = { 2, 3};

static u32 OrderedGroup_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 2;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err OrderedGroup_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = OrderedGroup_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = OrderedGroup_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = OrderedGroup_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err OrderedGroup_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_OrderedGroup *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_OrderedGroup *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_OrderedGroup *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_OrderedGroup *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_OrderedGroup *)node)->children;
		return GF_OK;
	case 3:
		info->name = "order";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_OrderedGroup *) node)->order;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 OrderedGroup_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	if (!strcmp("order", name)) return 3;
	return -1;
	}
static Bool OrderedGroup_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 3:
		*AType = 0;
		*QType = 3;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *OrderedGroup_Create()
{
	M_OrderedGroup *p;
	GF_SAFEALLOC(p, M_OrderedGroup);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_OrderedGroup);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	OrientationInterpolator Node deletion
*/

static void OrientationInterpolator_Del(GF_Node *node)
{
	M_OrientationInterpolator *p = (M_OrientationInterpolator *) node;
	gf_sg_mffloat_del(p->key);
	gf_sg_mfrotation_del(p->keyValue);
	gf_node_free((GF_Node *) p);
}

static const u16 OrientationInterpolator_Def2All[] = { 1, 2};
static const u16 OrientationInterpolator_In2All[] = { 0, 1, 2};
static const u16 OrientationInterpolator_Out2All[] = { 1, 2, 3};

static u32 OrientationInterpolator_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err OrientationInterpolator_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = OrientationInterpolator_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = OrientationInterpolator_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = OrientationInterpolator_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err OrientationInterpolator_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_fraction";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_OrientationInterpolator *)node)->on_set_fraction;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_OrientationInterpolator *) node)->set_fraction;
		return GF_OK;
	case 1:
		info->name = "key";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_OrientationInterpolator *) node)->key;
		return GF_OK;
	case 2:
		info->name = "keyValue";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFROTATION;
		info->far_ptr = & ((M_OrientationInterpolator *) node)->keyValue;
		return GF_OK;
	case 3:
		info->name = "value_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFROTATION;
		info->far_ptr = & ((M_OrientationInterpolator *) node)->value_changed;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 OrientationInterpolator_get_field_index_by_name(char *name)
{
	if (!strcmp("set_fraction", name)) return 0;
	if (!strcmp("key", name)) return 1;
	if (!strcmp("keyValue", name)) return 2;
	if (!strcmp("value_changed", name)) return 3;
	return -1;
	}
static Bool OrientationInterpolator_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 2:
		*AType = 0;
		*QType = 10;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *OrientationInterpolator_Create()
{
	M_OrientationInterpolator *p;
	GF_SAFEALLOC(p, M_OrientationInterpolator);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_OrientationInterpolator);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	PixelTexture Node deletion
*/

static void PixelTexture_Del(GF_Node *node)
{
	M_PixelTexture *p = (M_PixelTexture *) node;
	gf_sg_sfimage_del(p->image);
	gf_node_free((GF_Node *) p);
}

static const u16 PixelTexture_Def2All[] = { 0, 1, 2};
static const u16 PixelTexture_In2All[] = { 0};
static const u16 PixelTexture_Out2All[] = { 0};

static u32 PixelTexture_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 1;
	case GF_SG_FIELD_CODING_DEF: return 3;
	case GF_SG_FIELD_CODING_OUT: return 1;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 3;
	}
}

static GF_Err PixelTexture_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = PixelTexture_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = PixelTexture_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = PixelTexture_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err PixelTexture_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "image";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFIMAGE;
		info->far_ptr = & ((M_PixelTexture *) node)->image;
		return GF_OK;
	case 1:
		info->name = "repeatS";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_PixelTexture *) node)->repeatS;
		return GF_OK;
	case 2:
		info->name = "repeatT";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_PixelTexture *) node)->repeatT;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 PixelTexture_get_field_index_by_name(char *name)
{
	if (!strcmp("image", name)) return 0;
	if (!strcmp("repeatS", name)) return 1;
	if (!strcmp("repeatT", name)) return 2;
	return -1;
	}
static Bool PixelTexture_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 0;
		*QType = 0;
		return 1;
	default:
		return 0;
	}
}



GF_Node *PixelTexture_Create()
{
	M_PixelTexture *p;
	GF_SAFEALLOC(p, M_PixelTexture);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_PixelTexture);

	/*default field values*/
	p->repeatS = 1;
	p->repeatT = 1;
	return (GF_Node *)p;
}


/*
	PlaneSensor Node deletion
*/

static void PlaneSensor_Del(GF_Node *node)
{
	M_PlaneSensor *p = (M_PlaneSensor *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 PlaneSensor_Def2All[] = { 0, 1, 2, 3, 4};
static const u16 PlaneSensor_In2All[] = { 0, 1, 2, 3, 4};
static const u16 PlaneSensor_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7};

static u32 PlaneSensor_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 5;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 8;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 8;
	}
}

static GF_Err PlaneSensor_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = PlaneSensor_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = PlaneSensor_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = PlaneSensor_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err PlaneSensor_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "autoOffset";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_PlaneSensor *) node)->autoOffset;
		return GF_OK;
	case 1:
		info->name = "enabled";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_PlaneSensor *) node)->enabled;
		return GF_OK;
	case 2:
		info->name = "maxPosition";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_PlaneSensor *) node)->maxPosition;
		return GF_OK;
	case 3:
		info->name = "minPosition";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_PlaneSensor *) node)->minPosition;
		return GF_OK;
	case 4:
		info->name = "offset";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_PlaneSensor *) node)->offset;
		return GF_OK;
	case 5:
		info->name = "isActive";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_PlaneSensor *) node)->isActive;
		return GF_OK;
	case 6:
		info->name = "trackPoint_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_PlaneSensor *) node)->trackPoint_changed;
		return GF_OK;
	case 7:
		info->name = "translation_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_PlaneSensor *) node)->translation_changed;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 PlaneSensor_get_field_index_by_name(char *name)
{
	if (!strcmp("autoOffset", name)) return 0;
	if (!strcmp("enabled", name)) return 1;
	if (!strcmp("maxPosition", name)) return 2;
	if (!strcmp("minPosition", name)) return 3;
	if (!strcmp("offset", name)) return 4;
	if (!strcmp("isActive", name)) return 5;
	if (!strcmp("trackPoint_changed", name)) return 6;
	if (!strcmp("translation_changed", name)) return 7;
	return -1;
	}
static Bool PlaneSensor_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 2:
		*AType = 0;
		*QType = 2;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 3:
		*AType = 0;
		*QType = 2;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 4:
		*AType = 0;
		*QType = 1;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *PlaneSensor_Create()
{
	M_PlaneSensor *p;
	GF_SAFEALLOC(p, M_PlaneSensor);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_PlaneSensor);

	/*default field values*/
	p->autoOffset = 1;
	p->enabled = 1;
	p->maxPosition.x = FLT2FIX(-1);
	p->maxPosition.y = FLT2FIX(-1);
	p->minPosition.x = FLT2FIX(0);
	p->minPosition.y = FLT2FIX(0);
	p->offset.x = FLT2FIX(0);
	p->offset.y = FLT2FIX(0);
	p->offset.z = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	PlaneSensor2D Node deletion
*/

static void PlaneSensor2D_Del(GF_Node *node)
{
	M_PlaneSensor2D *p = (M_PlaneSensor2D *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 PlaneSensor2D_Def2All[] = { 0, 1, 2, 3, 4};
static const u16 PlaneSensor2D_In2All[] = { 0, 1, 2, 3, 4};
static const u16 PlaneSensor2D_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7};

static u32 PlaneSensor2D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 5;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 8;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 8;
	}
}

static GF_Err PlaneSensor2D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = PlaneSensor2D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = PlaneSensor2D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = PlaneSensor2D_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err PlaneSensor2D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "autoOffset";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_PlaneSensor2D *) node)->autoOffset;
		return GF_OK;
	case 1:
		info->name = "enabled";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_PlaneSensor2D *) node)->enabled;
		return GF_OK;
	case 2:
		info->name = "maxPosition";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_PlaneSensor2D *) node)->maxPosition;
		return GF_OK;
	case 3:
		info->name = "minPosition";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_PlaneSensor2D *) node)->minPosition;
		return GF_OK;
	case 4:
		info->name = "offset";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_PlaneSensor2D *) node)->offset;
		return GF_OK;
	case 5:
		info->name = "isActive";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_PlaneSensor2D *) node)->isActive;
		return GF_OK;
	case 6:
		info->name = "trackPoint_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_PlaneSensor2D *) node)->trackPoint_changed;
		return GF_OK;
	case 7:
		info->name = "translation_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_PlaneSensor2D *) node)->translation_changed;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 PlaneSensor2D_get_field_index_by_name(char *name)
{
	if (!strcmp("autoOffset", name)) return 0;
	if (!strcmp("enabled", name)) return 1;
	if (!strcmp("maxPosition", name)) return 2;
	if (!strcmp("minPosition", name)) return 3;
	if (!strcmp("offset", name)) return 4;
	if (!strcmp("isActive", name)) return 5;
	if (!strcmp("trackPoint_changed", name)) return 6;
	if (!strcmp("translation_changed", name)) return 7;
	return -1;
	}
static Bool PlaneSensor2D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 2:
		*AType = 0;
		*QType = 2;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 3:
		*AType = 0;
		*QType = 2;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 4:
		*AType = 0;
		*QType = 12;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *PlaneSensor2D_Create()
{
	M_PlaneSensor2D *p;
	GF_SAFEALLOC(p, M_PlaneSensor2D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_PlaneSensor2D);

	/*default field values*/
	p->autoOffset = 1;
	p->enabled = 1;
	p->maxPosition.x = FLT2FIX(0);
	p->maxPosition.y = FLT2FIX(0);
	p->minPosition.x = FLT2FIX(0);
	p->minPosition.y = FLT2FIX(0);
	p->offset.x = FLT2FIX(0);
	p->offset.y = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	PointLight Node deletion
*/

static void PointLight_Del(GF_Node *node)
{
	M_PointLight *p = (M_PointLight *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 PointLight_Def2All[] = { 0, 1, 2, 3, 4, 5, 6};
static const u16 PointLight_In2All[] = { 0, 1, 2, 3, 4, 5, 6};
static const u16 PointLight_Out2All[] = { 0, 1, 2, 3, 4, 5, 6};
static const u16 PointLight_Dyn2All[] = { 0, 1, 2, 3, 4, 6};

static u32 PointLight_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 7;
	case GF_SG_FIELD_CODING_DEF: return 7;
	case GF_SG_FIELD_CODING_OUT: return 7;
	case GF_SG_FIELD_CODING_DYN: return 6;
	default:
		return 7;
	}
}

static GF_Err PointLight_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = PointLight_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = PointLight_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = PointLight_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = PointLight_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err PointLight_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "ambientIntensity";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_PointLight *) node)->ambientIntensity;
		return GF_OK;
	case 1:
		info->name = "attenuation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_PointLight *) node)->attenuation;
		return GF_OK;
	case 2:
		info->name = "color";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFCOLOR;
		info->far_ptr = & ((M_PointLight *) node)->color;
		return GF_OK;
	case 3:
		info->name = "intensity";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_PointLight *) node)->intensity;
		return GF_OK;
	case 4:
		info->name = "location";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_PointLight *) node)->location;
		return GF_OK;
	case 5:
		info->name = "on";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_PointLight *) node)->on;
		return GF_OK;
	case 6:
		info->name = "radius";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_PointLight *) node)->radius;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 PointLight_get_field_index_by_name(char *name)
{
	if (!strcmp("ambientIntensity", name)) return 0;
	if (!strcmp("attenuation", name)) return 1;
	if (!strcmp("color", name)) return 2;
	if (!strcmp("intensity", name)) return 3;
	if (!strcmp("location", name)) return 4;
	if (!strcmp("on", name)) return 5;
	if (!strcmp("radius", name)) return 6;
	return -1;
	}
static Bool PointLight_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 8;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 1:
		*AType = 1;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 2:
		*AType = 4;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 3:
		*AType = 8;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 4:
		*AType = 1;
		*QType = 1;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 6:
		*AType = 7;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *PointLight_Create()
{
	M_PointLight *p;
	GF_SAFEALLOC(p, M_PointLight);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_PointLight);

	/*default field values*/
	p->ambientIntensity = FLT2FIX(0);
	p->attenuation.x = FLT2FIX(1);
	p->attenuation.y = FLT2FIX(0);
	p->attenuation.z = FLT2FIX(0);
	p->color.red = FLT2FIX(1);
	p->color.green = FLT2FIX(1);
	p->color.blue = FLT2FIX(1);
	p->intensity = FLT2FIX(1);
	p->location.x = FLT2FIX(0);
	p->location.y = FLT2FIX(0);
	p->location.z = FLT2FIX(0);
	p->on = 1;
	p->radius = FLT2FIX(100);
	return (GF_Node *)p;
}


/*
	PointSet Node deletion
*/

static void PointSet_Del(GF_Node *node)
{
	M_PointSet *p = (M_PointSet *) node;
	gf_node_unregister((GF_Node *) p->color, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->coord, (GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 PointSet_Def2All[] = { 0, 1};
static const u16 PointSet_In2All[] = { 0, 1};
static const u16 PointSet_Out2All[] = { 0, 1};

static u32 PointSet_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 2;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 2;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 2;
	}
}

static GF_Err PointSet_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = PointSet_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = PointSet_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = PointSet_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err PointSet_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "color";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFColorNode;
		info->far_ptr = & ((M_PointSet *)node)->color;
		return GF_OK;
	case 1:
		info->name = "coord";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFCoordinateNode;
		info->far_ptr = & ((M_PointSet *)node)->coord;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 PointSet_get_field_index_by_name(char *name)
{
	if (!strcmp("color", name)) return 0;
	if (!strcmp("coord", name)) return 1;
	return -1;
	}
static Bool PointSet_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *PointSet_Create()
{
	M_PointSet *p;
	GF_SAFEALLOC(p, M_PointSet);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_PointSet);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	PointSet2D Node deletion
*/

static void PointSet2D_Del(GF_Node *node)
{
	M_PointSet2D *p = (M_PointSet2D *) node;
	gf_node_unregister((GF_Node *) p->color, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->coord, (GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 PointSet2D_Def2All[] = { 0, 1};
static const u16 PointSet2D_In2All[] = { 0, 1};
static const u16 PointSet2D_Out2All[] = { 0, 1};

static u32 PointSet2D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 2;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 2;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 2;
	}
}

static GF_Err PointSet2D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = PointSet2D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = PointSet2D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = PointSet2D_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err PointSet2D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "color";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFColorNode;
		info->far_ptr = & ((M_PointSet2D *)node)->color;
		return GF_OK;
	case 1:
		info->name = "coord";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFCoordinate2DNode;
		info->far_ptr = & ((M_PointSet2D *)node)->coord;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 PointSet2D_get_field_index_by_name(char *name)
{
	if (!strcmp("color", name)) return 0;
	if (!strcmp("coord", name)) return 1;
	return -1;
	}
static Bool PointSet2D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *PointSet2D_Create()
{
	M_PointSet2D *p;
	GF_SAFEALLOC(p, M_PointSet2D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_PointSet2D);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	PositionInterpolator Node deletion
*/

static void PositionInterpolator_Del(GF_Node *node)
{
	M_PositionInterpolator *p = (M_PositionInterpolator *) node;
	gf_sg_mffloat_del(p->key);
	gf_sg_mfvec3f_del(p->keyValue);
	gf_node_free((GF_Node *) p);
}

static const u16 PositionInterpolator_Def2All[] = { 1, 2};
static const u16 PositionInterpolator_In2All[] = { 0, 1, 2};
static const u16 PositionInterpolator_Out2All[] = { 1, 2, 3};

static u32 PositionInterpolator_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err PositionInterpolator_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = PositionInterpolator_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = PositionInterpolator_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = PositionInterpolator_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err PositionInterpolator_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_fraction";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_PositionInterpolator *)node)->on_set_fraction;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_PositionInterpolator *) node)->set_fraction;
		return GF_OK;
	case 1:
		info->name = "key";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_PositionInterpolator *) node)->key;
		return GF_OK;
	case 2:
		info->name = "keyValue";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC3F;
		info->far_ptr = & ((M_PositionInterpolator *) node)->keyValue;
		return GF_OK;
	case 3:
		info->name = "value_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_PositionInterpolator *) node)->value_changed;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 PositionInterpolator_get_field_index_by_name(char *name)
{
	if (!strcmp("set_fraction", name)) return 0;
	if (!strcmp("key", name)) return 1;
	if (!strcmp("keyValue", name)) return 2;
	if (!strcmp("value_changed", name)) return 3;
	return -1;
	}
static Bool PositionInterpolator_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 2:
		*AType = 0;
		*QType = 1;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *PositionInterpolator_Create()
{
	M_PositionInterpolator *p;
	GF_SAFEALLOC(p, M_PositionInterpolator);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_PositionInterpolator);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	PositionInterpolator2D Node deletion
*/

static void PositionInterpolator2D_Del(GF_Node *node)
{
	M_PositionInterpolator2D *p = (M_PositionInterpolator2D *) node;
	gf_sg_mffloat_del(p->key);
	gf_sg_mfvec2f_del(p->keyValue);
	gf_node_free((GF_Node *) p);
}

static const u16 PositionInterpolator2D_Def2All[] = { 1, 2};
static const u16 PositionInterpolator2D_In2All[] = { 0, 1, 2};
static const u16 PositionInterpolator2D_Out2All[] = { 1, 2, 3};

static u32 PositionInterpolator2D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err PositionInterpolator2D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = PositionInterpolator2D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = PositionInterpolator2D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = PositionInterpolator2D_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err PositionInterpolator2D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_fraction";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_PositionInterpolator2D *)node)->on_set_fraction;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_PositionInterpolator2D *) node)->set_fraction;
		return GF_OK;
	case 1:
		info->name = "key";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_PositionInterpolator2D *) node)->key;
		return GF_OK;
	case 2:
		info->name = "keyValue";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC2F;
		info->far_ptr = & ((M_PositionInterpolator2D *) node)->keyValue;
		return GF_OK;
	case 3:
		info->name = "value_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_PositionInterpolator2D *) node)->value_changed;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 PositionInterpolator2D_get_field_index_by_name(char *name)
{
	if (!strcmp("set_fraction", name)) return 0;
	if (!strcmp("key", name)) return 1;
	if (!strcmp("keyValue", name)) return 2;
	if (!strcmp("value_changed", name)) return 3;
	return -1;
	}
static Bool PositionInterpolator2D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 2:
		*AType = 0;
		*QType = 2;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *PositionInterpolator2D_Create()
{
	M_PositionInterpolator2D *p;
	GF_SAFEALLOC(p, M_PositionInterpolator2D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_PositionInterpolator2D);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	ProximitySensor2D Node deletion
*/

static void ProximitySensor2D_Del(GF_Node *node)
{
	M_ProximitySensor2D *p = (M_ProximitySensor2D *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 ProximitySensor2D_Def2All[] = { 0, 1, 2};
static const u16 ProximitySensor2D_In2All[] = { 0, 1, 2};
static const u16 ProximitySensor2D_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7};

static u32 ProximitySensor2D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 3;
	case GF_SG_FIELD_CODING_OUT: return 8;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 8;
	}
}

static GF_Err ProximitySensor2D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = ProximitySensor2D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = ProximitySensor2D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = ProximitySensor2D_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err ProximitySensor2D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "center";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_ProximitySensor2D *) node)->center;
		return GF_OK;
	case 1:
		info->name = "size";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_ProximitySensor2D *) node)->size;
		return GF_OK;
	case 2:
		info->name = "enabled";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_ProximitySensor2D *) node)->enabled;
		return GF_OK;
	case 3:
		info->name = "isActive";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_ProximitySensor2D *) node)->isActive;
		return GF_OK;
	case 4:
		info->name = "position_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_ProximitySensor2D *) node)->position_changed;
		return GF_OK;
	case 5:
		info->name = "orientation_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ProximitySensor2D *) node)->orientation_changed;
		return GF_OK;
	case 6:
		info->name = "enterTime";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_ProximitySensor2D *) node)->enterTime;
		return GF_OK;
	case 7:
		info->name = "exitTime";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_ProximitySensor2D *) node)->exitTime;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 ProximitySensor2D_get_field_index_by_name(char *name)
{
	if (!strcmp("center", name)) return 0;
	if (!strcmp("size", name)) return 1;
	if (!strcmp("enabled", name)) return 2;
	if (!strcmp("isActive", name)) return 3;
	if (!strcmp("position_changed", name)) return 4;
	if (!strcmp("orientation_changed", name)) return 5;
	if (!strcmp("enterTime", name)) return 6;
	if (!strcmp("exitTime", name)) return 7;
	return -1;
	}
static Bool ProximitySensor2D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 0;
		*QType = 2;
		*b_min = FLT2FIX(-1);
		*b_max = FIX_MAX;
		return 1;
	case 1:
		*AType = 0;
		*QType = 12;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *ProximitySensor2D_Create()
{
	M_ProximitySensor2D *p;
	GF_SAFEALLOC(p, M_ProximitySensor2D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_ProximitySensor2D);

	/*default field values*/
	p->center.x = FLT2FIX(0);
	p->center.y = FLT2FIX(0);
	p->size.x = FLT2FIX(0);
	p->size.y = FLT2FIX(0);
	p->enabled = 1;
	return (GF_Node *)p;
}


/*
	ProximitySensor Node deletion
*/

static void ProximitySensor_Del(GF_Node *node)
{
	M_ProximitySensor *p = (M_ProximitySensor *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 ProximitySensor_Def2All[] = { 0, 1, 2};
static const u16 ProximitySensor_In2All[] = { 0, 1, 2};
static const u16 ProximitySensor_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7};

static u32 ProximitySensor_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 3;
	case GF_SG_FIELD_CODING_OUT: return 8;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 8;
	}
}

static GF_Err ProximitySensor_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = ProximitySensor_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = ProximitySensor_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = ProximitySensor_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err ProximitySensor_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "center";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_ProximitySensor *) node)->center;
		return GF_OK;
	case 1:
		info->name = "size";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_ProximitySensor *) node)->size;
		return GF_OK;
	case 2:
		info->name = "enabled";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_ProximitySensor *) node)->enabled;
		return GF_OK;
	case 3:
		info->name = "isActive";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_ProximitySensor *) node)->isActive;
		return GF_OK;
	case 4:
		info->name = "position_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_ProximitySensor *) node)->position_changed;
		return GF_OK;
	case 5:
		info->name = "orientation_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFROTATION;
		info->far_ptr = & ((M_ProximitySensor *) node)->orientation_changed;
		return GF_OK;
	case 6:
		info->name = "enterTime";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_ProximitySensor *) node)->enterTime;
		return GF_OK;
	case 7:
		info->name = "exitTime";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_ProximitySensor *) node)->exitTime;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 ProximitySensor_get_field_index_by_name(char *name)
{
	if (!strcmp("center", name)) return 0;
	if (!strcmp("size", name)) return 1;
	if (!strcmp("enabled", name)) return 2;
	if (!strcmp("isActive", name)) return 3;
	if (!strcmp("position_changed", name)) return 4;
	if (!strcmp("orientation_changed", name)) return 5;
	if (!strcmp("enterTime", name)) return 6;
	if (!strcmp("exitTime", name)) return 7;
	return -1;
	}
static Bool ProximitySensor_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 0;
		*QType = 1;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 1:
		*AType = 0;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *ProximitySensor_Create()
{
	M_ProximitySensor *p;
	GF_SAFEALLOC(p, M_ProximitySensor);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_ProximitySensor);

	/*default field values*/
	p->center.x = FLT2FIX(0);
	p->center.y = FLT2FIX(0);
	p->center.z = FLT2FIX(0);
	p->size.x = FLT2FIX(0);
	p->size.y = FLT2FIX(0);
	p->size.z = FLT2FIX(0);
	p->enabled = 1;
	return (GF_Node *)p;
}


/*
	QuantizationParameter Node deletion
*/

static void QuantizationParameter_Del(GF_Node *node)
{
	M_QuantizationParameter *p = (M_QuantizationParameter *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 QuantizationParameter_Def2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39};

static u32 QuantizationParameter_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 0;
	case GF_SG_FIELD_CODING_DEF: return 40;
	case GF_SG_FIELD_CODING_OUT: return 0;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 40;
	}
}

static GF_Err QuantizationParameter_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_DEF:
		*allField = QuantizationParameter_Def2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err QuantizationParameter_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "isLocal";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_QuantizationParameter *) node)->isLocal;
		return GF_OK;
	case 1:
		info->name = "position3DQuant";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_QuantizationParameter *) node)->position3DQuant;
		return GF_OK;
	case 2:
		info->name = "position3DMin";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_QuantizationParameter *) node)->position3DMin;
		return GF_OK;
	case 3:
		info->name = "position3DMax";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_QuantizationParameter *) node)->position3DMax;
		return GF_OK;
	case 4:
		info->name = "position3DNbBits";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_QuantizationParameter *) node)->position3DNbBits;
		return GF_OK;
	case 5:
		info->name = "position2DQuant";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_QuantizationParameter *) node)->position2DQuant;
		return GF_OK;
	case 6:
		info->name = "position2DMin";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_QuantizationParameter *) node)->position2DMin;
		return GF_OK;
	case 7:
		info->name = "position2DMax";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_QuantizationParameter *) node)->position2DMax;
		return GF_OK;
	case 8:
		info->name = "position2DNbBits";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_QuantizationParameter *) node)->position2DNbBits;
		return GF_OK;
	case 9:
		info->name = "drawOrderQuant";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_QuantizationParameter *) node)->drawOrderQuant;
		return GF_OK;
	case 10:
		info->name = "drawOrderMin";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_QuantizationParameter *) node)->drawOrderMin;
		return GF_OK;
	case 11:
		info->name = "drawOrderMax";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_QuantizationParameter *) node)->drawOrderMax;
		return GF_OK;
	case 12:
		info->name = "drawOrderNbBits";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_QuantizationParameter *) node)->drawOrderNbBits;
		return GF_OK;
	case 13:
		info->name = "colorQuant";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_QuantizationParameter *) node)->colorQuant;
		return GF_OK;
	case 14:
		info->name = "colorMin";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_QuantizationParameter *) node)->colorMin;
		return GF_OK;
	case 15:
		info->name = "colorMax";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_QuantizationParameter *) node)->colorMax;
		return GF_OK;
	case 16:
		info->name = "colorNbBits";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_QuantizationParameter *) node)->colorNbBits;
		return GF_OK;
	case 17:
		info->name = "textureCoordinateQuant";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_QuantizationParameter *) node)->textureCoordinateQuant;
		return GF_OK;
	case 18:
		info->name = "textureCoordinateMin";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_QuantizationParameter *) node)->textureCoordinateMin;
		return GF_OK;
	case 19:
		info->name = "textureCoordinateMax";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_QuantizationParameter *) node)->textureCoordinateMax;
		return GF_OK;
	case 20:
		info->name = "textureCoordinateNbBits";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_QuantizationParameter *) node)->textureCoordinateNbBits;
		return GF_OK;
	case 21:
		info->name = "angleQuant";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_QuantizationParameter *) node)->angleQuant;
		return GF_OK;
	case 22:
		info->name = "angleMin";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_QuantizationParameter *) node)->angleMin;
		return GF_OK;
	case 23:
		info->name = "angleMax";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_QuantizationParameter *) node)->angleMax;
		return GF_OK;
	case 24:
		info->name = "angleNbBits";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_QuantizationParameter *) node)->angleNbBits;
		return GF_OK;
	case 25:
		info->name = "scaleQuant";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_QuantizationParameter *) node)->scaleQuant;
		return GF_OK;
	case 26:
		info->name = "scaleMin";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_QuantizationParameter *) node)->scaleMin;
		return GF_OK;
	case 27:
		info->name = "scaleMax";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_QuantizationParameter *) node)->scaleMax;
		return GF_OK;
	case 28:
		info->name = "scaleNbBits";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_QuantizationParameter *) node)->scaleNbBits;
		return GF_OK;
	case 29:
		info->name = "keyQuant";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_QuantizationParameter *) node)->keyQuant;
		return GF_OK;
	case 30:
		info->name = "keyMin";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_QuantizationParameter *) node)->keyMin;
		return GF_OK;
	case 31:
		info->name = "keyMax";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_QuantizationParameter *) node)->keyMax;
		return GF_OK;
	case 32:
		info->name = "keyNbBits";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_QuantizationParameter *) node)->keyNbBits;
		return GF_OK;
	case 33:
		info->name = "normalQuant";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_QuantizationParameter *) node)->normalQuant;
		return GF_OK;
	case 34:
		info->name = "normalNbBits";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_QuantizationParameter *) node)->normalNbBits;
		return GF_OK;
	case 35:
		info->name = "sizeQuant";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_QuantizationParameter *) node)->sizeQuant;
		return GF_OK;
	case 36:
		info->name = "sizeMin";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_QuantizationParameter *) node)->sizeMin;
		return GF_OK;
	case 37:
		info->name = "sizeMax";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_QuantizationParameter *) node)->sizeMax;
		return GF_OK;
	case 38:
		info->name = "sizeNbBits";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_QuantizationParameter *) node)->sizeNbBits;
		return GF_OK;
	case 39:
		info->name = "useEfficientCoding";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_QuantizationParameter *) node)->useEfficientCoding;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 QuantizationParameter_get_field_index_by_name(char *name)
{
	if (!strcmp("isLocal", name)) return 0;
	if (!strcmp("position3DQuant", name)) return 1;
	if (!strcmp("position3DMin", name)) return 2;
	if (!strcmp("position3DMax", name)) return 3;
	if (!strcmp("position3DNbBits", name)) return 4;
	if (!strcmp("position2DQuant", name)) return 5;
	if (!strcmp("position2DMin", name)) return 6;
	if (!strcmp("position2DMax", name)) return 7;
	if (!strcmp("position2DNbBits", name)) return 8;
	if (!strcmp("drawOrderQuant", name)) return 9;
	if (!strcmp("drawOrderMin", name)) return 10;
	if (!strcmp("drawOrderMax", name)) return 11;
	if (!strcmp("drawOrderNbBits", name)) return 12;
	if (!strcmp("colorQuant", name)) return 13;
	if (!strcmp("colorMin", name)) return 14;
	if (!strcmp("colorMax", name)) return 15;
	if (!strcmp("colorNbBits", name)) return 16;
	if (!strcmp("textureCoordinateQuant", name)) return 17;
	if (!strcmp("textureCoordinateMin", name)) return 18;
	if (!strcmp("textureCoordinateMax", name)) return 19;
	if (!strcmp("textureCoordinateNbBits", name)) return 20;
	if (!strcmp("angleQuant", name)) return 21;
	if (!strcmp("angleMin", name)) return 22;
	if (!strcmp("angleMax", name)) return 23;
	if (!strcmp("angleNbBits", name)) return 24;
	if (!strcmp("scaleQuant", name)) return 25;
	if (!strcmp("scaleMin", name)) return 26;
	if (!strcmp("scaleMax", name)) return 27;
	if (!strcmp("scaleNbBits", name)) return 28;
	if (!strcmp("keyQuant", name)) return 29;
	if (!strcmp("keyMin", name)) return 30;
	if (!strcmp("keyMax", name)) return 31;
	if (!strcmp("keyNbBits", name)) return 32;
	if (!strcmp("normalQuant", name)) return 33;
	if (!strcmp("normalNbBits", name)) return 34;
	if (!strcmp("sizeQuant", name)) return 35;
	if (!strcmp("sizeMin", name)) return 36;
	if (!strcmp("sizeMax", name)) return 37;
	if (!strcmp("sizeNbBits", name)) return 38;
	if (!strcmp("useEfficientCoding", name)) return 39;
	return -1;
	}
static Bool QuantizationParameter_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 2:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 3:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 4:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 5;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(31);
		return 1;
	case 6:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 7:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 8:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 5;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(31);
		return 1;
	case 10:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 11:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 12:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 5;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(31);
		return 1;
	case 14:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 15:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 16:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 5;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(31);
		return 1;
	case 18:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 19:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 20:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 5;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(31);
		return 1;
	case 22:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(6.2831853);
		return 1;
	case 23:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(6.2831853);
		return 1;
	case 24:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 5;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(31);
		return 1;
	case 26:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 27:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 28:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 5;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(31);
		return 1;
	case 30:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 31:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 32:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 5;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(31);
		return 1;
	case 34:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 5;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(31);
		return 1;
	case 36:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 37:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 38:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 5;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(31);
		return 1;
	default:
		return 0;
	}
}



GF_Node *QuantizationParameter_Create()
{
	M_QuantizationParameter *p;
	GF_SAFEALLOC(p, M_QuantizationParameter);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_QuantizationParameter);

	/*default field values*/
	p->position3DMin.x = FIX_MIN;
	p->position3DMin.y = FIX_MIN;
	p->position3DMin.z = FIX_MIN;
	p->position3DMax.x = FIX_MAX;
	p->position3DMax.y = FIX_MAX;
	p->position3DMax.z = FIX_MAX;
	p->position3DNbBits = 16;
	p->position2DMin.x = FIX_MIN;
	p->position2DMin.y = FIX_MIN;
	p->position2DMax.x = FIX_MAX;
	p->position2DMax.y = FIX_MAX;
	p->position2DNbBits = 16;
	p->drawOrderMin = FIX_MIN;
	p->drawOrderMax = FIX_MAX;
	p->drawOrderNbBits = 8;
	p->colorQuant = 1;
	p->colorMin = FLT2FIX(0.0);
	p->colorMax = FLT2FIX(1.0);
	p->colorNbBits = 8;
	p->textureCoordinateQuant = 1;
	p->textureCoordinateMin = FLT2FIX(0);
	p->textureCoordinateMax = FLT2FIX(1);
	p->textureCoordinateNbBits = 16;
	p->angleQuant = 1;
	p->angleMin = FLT2FIX(0.0);
	p->angleMax = FLT2FIX(6.2831853);
	p->angleNbBits = 16;
	p->scaleMin = FLT2FIX(0.0);
	p->scaleMax = FIX_MAX;
	p->scaleNbBits = 8;
	p->keyQuant = 1;
	p->keyMin = FLT2FIX(0.0);
	p->keyMax = FLT2FIX(1.0);
	p->keyNbBits = 8;
	p->normalQuant = 1;
	p->normalNbBits = 8;
	p->sizeMin = FLT2FIX(0);
	p->sizeMax = FIX_MAX;
	p->sizeNbBits = 8;
	return (GF_Node *)p;
}


/*
	Rectangle Node deletion
*/

static void Rectangle_Del(GF_Node *node)
{
	M_Rectangle *p = (M_Rectangle *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 Rectangle_Def2All[] = { 0};
static const u16 Rectangle_In2All[] = { 0};
static const u16 Rectangle_Out2All[] = { 0};
static const u16 Rectangle_Dyn2All[] = { 0};

static u32 Rectangle_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 1;
	case GF_SG_FIELD_CODING_DEF: return 1;
	case GF_SG_FIELD_CODING_OUT: return 1;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 1;
	}
}

static GF_Err Rectangle_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Rectangle_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Rectangle_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Rectangle_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Rectangle_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Rectangle_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "size";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_Rectangle *) node)->size;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Rectangle_get_field_index_by_name(char *name)
{
	if (!strcmp("size", name)) return 0;
	return -1;
	}
static Bool Rectangle_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 2;
		*QType = 12;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Rectangle_Create()
{
	M_Rectangle *p;
	GF_SAFEALLOC(p, M_Rectangle);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Rectangle);

	/*default field values*/
	p->size.x = FLT2FIX(2);
	p->size.y = FLT2FIX(2);
	return (GF_Node *)p;
}


/*
	ScalarInterpolator Node deletion
*/

static void ScalarInterpolator_Del(GF_Node *node)
{
	M_ScalarInterpolator *p = (M_ScalarInterpolator *) node;
	gf_sg_mffloat_del(p->key);
	gf_sg_mffloat_del(p->keyValue);
	gf_node_free((GF_Node *) p);
}

static const u16 ScalarInterpolator_Def2All[] = { 1, 2};
static const u16 ScalarInterpolator_In2All[] = { 0, 1, 2};
static const u16 ScalarInterpolator_Out2All[] = { 1, 2, 3};

static u32 ScalarInterpolator_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err ScalarInterpolator_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = ScalarInterpolator_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = ScalarInterpolator_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = ScalarInterpolator_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err ScalarInterpolator_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_fraction";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_ScalarInterpolator *)node)->on_set_fraction;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ScalarInterpolator *) node)->set_fraction;
		return GF_OK;
	case 1:
		info->name = "key";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_ScalarInterpolator *) node)->key;
		return GF_OK;
	case 2:
		info->name = "keyValue";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_ScalarInterpolator *) node)->keyValue;
		return GF_OK;
	case 3:
		info->name = "value_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ScalarInterpolator *) node)->value_changed;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 ScalarInterpolator_get_field_index_by_name(char *name)
{
	if (!strcmp("set_fraction", name)) return 0;
	if (!strcmp("key", name)) return 1;
	if (!strcmp("keyValue", name)) return 2;
	if (!strcmp("value_changed", name)) return 3;
	return -1;
	}
static Bool ScalarInterpolator_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 2:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *ScalarInterpolator_Create()
{
	M_ScalarInterpolator *p;
	GF_SAFEALLOC(p, M_ScalarInterpolator);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_ScalarInterpolator);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	Script Node deletion
*/

static void Script_Del(GF_Node *node)
{
	M_Script *p = (M_Script *) node;
	gf_sg_mfscript_del(p->url);
	gf_node_free((GF_Node *) p);
}

static const u16 Script_Def2All[] = { 0, 1, 2};
static const u16 Script_In2All[] = { 0};
static const u16 Script_Out2All[] = { 0};

static u32 Script_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 1;
	case GF_SG_FIELD_CODING_DEF: return 3;
	case GF_SG_FIELD_CODING_OUT: return 1;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 3;
	}
}

static GF_Err Script_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Script_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Script_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Script_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Script_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "url";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFSCRIPT;
		info->far_ptr = & ((M_Script *) node)->url;
		return GF_OK;
	case 1:
		info->name = "directOutput";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Script *) node)->directOutput;
		return GF_OK;
	case 2:
		info->name = "mustEvaluate";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Script *) node)->mustEvaluate;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Script_get_field_index_by_name(char *name)
{
	if (!strcmp("url", name)) return 0;
	if (!strcmp("directOutput", name)) return 1;
	if (!strcmp("mustEvaluate", name)) return 2;
	return -1;
	}
static Bool Script_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *Script_Create()
{
	M_Script *p;
	GF_SAFEALLOC(p, M_Script);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Script);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	Shape Node deletion
*/

static void Shape_Del(GF_Node *node)
{
	M_Shape *p = (M_Shape *) node;
	gf_node_unregister((GF_Node *) p->appearance, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->geometry, (GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 Shape_Def2All[] = { 0, 1};
static const u16 Shape_In2All[] = { 0, 1};
static const u16 Shape_Out2All[] = { 0, 1};

static u32 Shape_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 2;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 2;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 2;
	}
}

static GF_Err Shape_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Shape_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Shape_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Shape_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Shape_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "appearance";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFAppearanceNode;
		info->far_ptr = & ((M_Shape *)node)->appearance;
		return GF_OK;
	case 1:
		info->name = "geometry";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFGeometryNode;
		info->far_ptr = & ((M_Shape *)node)->geometry;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Shape_get_field_index_by_name(char *name)
{
	if (!strcmp("appearance", name)) return 0;
	if (!strcmp("geometry", name)) return 1;
	return -1;
	}
static Bool Shape_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *Shape_Create()
{
	M_Shape *p;
	GF_SAFEALLOC(p, M_Shape);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Shape);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	Sound Node deletion
*/

static void Sound_Del(GF_Node *node)
{
	M_Sound *p = (M_Sound *) node;
	gf_node_unregister((GF_Node *) p->source, (GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 Sound_Def2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
static const u16 Sound_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};
static const u16 Sound_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};
static const u16 Sound_Dyn2All[] = { 1, 2, 3, 4, 5, 6};

static u32 Sound_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 9;
	case GF_SG_FIELD_CODING_DEF: return 10;
	case GF_SG_FIELD_CODING_OUT: return 9;
	case GF_SG_FIELD_CODING_DYN: return 6;
	default:
		return 10;
	}
}

static GF_Err Sound_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Sound_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Sound_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Sound_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Sound_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Sound_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "direction";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_Sound *) node)->direction;
		return GF_OK;
	case 1:
		info->name = "intensity";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Sound *) node)->intensity;
		return GF_OK;
	case 2:
		info->name = "location";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_Sound *) node)->location;
		return GF_OK;
	case 3:
		info->name = "maxBack";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Sound *) node)->maxBack;
		return GF_OK;
	case 4:
		info->name = "maxFront";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Sound *) node)->maxFront;
		return GF_OK;
	case 5:
		info->name = "minBack";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Sound *) node)->minBack;
		return GF_OK;
	case 6:
		info->name = "minFront";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Sound *) node)->minFront;
		return GF_OK;
	case 7:
		info->name = "priority";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Sound *) node)->priority;
		return GF_OK;
	case 8:
		info->name = "source";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFAudioNode;
		info->far_ptr = & ((M_Sound *)node)->source;
		return GF_OK;
	case 9:
		info->name = "spatialize";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Sound *) node)->spatialize;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Sound_get_field_index_by_name(char *name)
{
	if (!strcmp("direction", name)) return 0;
	if (!strcmp("intensity", name)) return 1;
	if (!strcmp("location", name)) return 2;
	if (!strcmp("maxBack", name)) return 3;
	if (!strcmp("maxFront", name)) return 4;
	if (!strcmp("minBack", name)) return 5;
	if (!strcmp("minFront", name)) return 6;
	if (!strcmp("priority", name)) return 7;
	if (!strcmp("source", name)) return 8;
	if (!strcmp("spatialize", name)) return 9;
	return -1;
	}
static Bool Sound_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 0;
		*QType = 9;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 1:
		*AType = 7;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 2:
		*AType = 1;
		*QType = 1;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 3:
		*AType = 7;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 4:
		*AType = 7;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 5:
		*AType = 7;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 6:
		*AType = 7;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 7:
		*AType = 0;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	default:
		return 0;
	}
}



GF_Node *Sound_Create()
{
	M_Sound *p;
	GF_SAFEALLOC(p, M_Sound);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Sound);

	/*default field values*/
	p->direction.x = FLT2FIX(0);
	p->direction.y = FLT2FIX(0);
	p->direction.z = FLT2FIX(1);
	p->intensity = FLT2FIX(1);
	p->location.x = FLT2FIX(0);
	p->location.y = FLT2FIX(0);
	p->location.z = FLT2FIX(0);
	p->maxBack = FLT2FIX(10);
	p->maxFront = FLT2FIX(10);
	p->minBack = FLT2FIX(1);
	p->minFront = FLT2FIX(1);
	p->priority = FLT2FIX(0);
	p->spatialize = 1;
	return (GF_Node *)p;
}


/*
	Sound2D Node deletion
*/

static void Sound2D_Del(GF_Node *node)
{
	M_Sound2D *p = (M_Sound2D *) node;
	gf_node_unregister((GF_Node *) p->source, (GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 Sound2D_Def2All[] = { 0, 1, 2, 3};
static const u16 Sound2D_In2All[] = { 0, 1, 2};
static const u16 Sound2D_Out2All[] = { 0, 1, 2};
static const u16 Sound2D_Dyn2All[] = { 0, 1};

static u32 Sound2D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 4;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 2;
	default:
		return 4;
	}
}

static GF_Err Sound2D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Sound2D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Sound2D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Sound2D_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Sound2D_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Sound2D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "intensity";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Sound2D *) node)->intensity;
		return GF_OK;
	case 1:
		info->name = "location";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_Sound2D *) node)->location;
		return GF_OK;
	case 2:
		info->name = "source";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFAudioNode;
		info->far_ptr = & ((M_Sound2D *)node)->source;
		return GF_OK;
	case 3:
		info->name = "spatialize";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Sound2D *) node)->spatialize;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Sound2D_get_field_index_by_name(char *name)
{
	if (!strcmp("intensity", name)) return 0;
	if (!strcmp("location", name)) return 1;
	if (!strcmp("source", name)) return 2;
	if (!strcmp("spatialize", name)) return 3;
	return -1;
	}
static Bool Sound2D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 7;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 1:
		*AType = 2;
		*QType = 2;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Sound2D_Create()
{
	M_Sound2D *p;
	GF_SAFEALLOC(p, M_Sound2D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Sound2D);

	/*default field values*/
	p->intensity = FLT2FIX(1);
	p->location.x = FLT2FIX(0);
	p->location.y = FLT2FIX(0);
	p->spatialize = 1;
	return (GF_Node *)p;
}


/*
	Sphere Node deletion
*/

static void Sphere_Del(GF_Node *node)
{
	M_Sphere *p = (M_Sphere *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 Sphere_Def2All[] = { 0};

static u32 Sphere_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 0;
	case GF_SG_FIELD_CODING_DEF: return 1;
	case GF_SG_FIELD_CODING_OUT: return 0;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 1;
	}
}

static GF_Err Sphere_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_DEF:
		*allField = Sphere_Def2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Sphere_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "radius";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Sphere *) node)->radius;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Sphere_get_field_index_by_name(char *name)
{
	if (!strcmp("radius", name)) return 0;
	return -1;
	}
static Bool Sphere_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 0;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Sphere_Create()
{
	M_Sphere *p;
	GF_SAFEALLOC(p, M_Sphere);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Sphere);

	/*default field values*/
	p->radius = FLT2FIX(1);
	return (GF_Node *)p;
}


/*
	SphereSensor Node deletion
*/

static void SphereSensor_Del(GF_Node *node)
{
	M_SphereSensor *p = (M_SphereSensor *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 SphereSensor_Def2All[] = { 0, 1, 2};
static const u16 SphereSensor_In2All[] = { 0, 1, 2};
static const u16 SphereSensor_Out2All[] = { 0, 1, 2, 3, 4, 5};

static u32 SphereSensor_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 3;
	case GF_SG_FIELD_CODING_OUT: return 6;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 6;
	}
}

static GF_Err SphereSensor_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = SphereSensor_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = SphereSensor_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = SphereSensor_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err SphereSensor_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "autoOffset";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_SphereSensor *) node)->autoOffset;
		return GF_OK;
	case 1:
		info->name = "enabled";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_SphereSensor *) node)->enabled;
		return GF_OK;
	case 2:
		info->name = "offset";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFROTATION;
		info->far_ptr = & ((M_SphereSensor *) node)->offset;
		return GF_OK;
	case 3:
		info->name = "isActive";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_SphereSensor *) node)->isActive;
		return GF_OK;
	case 4:
		info->name = "rotation_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFROTATION;
		info->far_ptr = & ((M_SphereSensor *) node)->rotation_changed;
		return GF_OK;
	case 5:
		info->name = "trackPoint_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_SphereSensor *) node)->trackPoint_changed;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 SphereSensor_get_field_index_by_name(char *name)
{
	if (!strcmp("autoOffset", name)) return 0;
	if (!strcmp("enabled", name)) return 1;
	if (!strcmp("offset", name)) return 2;
	if (!strcmp("isActive", name)) return 3;
	if (!strcmp("rotation_changed", name)) return 4;
	if (!strcmp("trackPoint_changed", name)) return 5;
	return -1;
	}
static Bool SphereSensor_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 2:
		*AType = 0;
		*QType = 10;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *SphereSensor_Create()
{
	M_SphereSensor *p;
	GF_SAFEALLOC(p, M_SphereSensor);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_SphereSensor);

	/*default field values*/
	p->autoOffset = 1;
	p->enabled = 1;
	p->offset.x = FLT2FIX(0);
	p->offset.y = FLT2FIX(1);
	p->offset.z = FLT2FIX(0);
	p->offset.q = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	SpotLight Node deletion
*/

static void SpotLight_Del(GF_Node *node)
{
	M_SpotLight *p = (M_SpotLight *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 SpotLight_Def2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
static const u16 SpotLight_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
static const u16 SpotLight_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
static const u16 SpotLight_Dyn2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 9};

static u32 SpotLight_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 10;
	case GF_SG_FIELD_CODING_DEF: return 10;
	case GF_SG_FIELD_CODING_OUT: return 10;
	case GF_SG_FIELD_CODING_DYN: return 9;
	default:
		return 10;
	}
}

static GF_Err SpotLight_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = SpotLight_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = SpotLight_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = SpotLight_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = SpotLight_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err SpotLight_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "ambientIntensity";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_SpotLight *) node)->ambientIntensity;
		return GF_OK;
	case 1:
		info->name = "attenuation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_SpotLight *) node)->attenuation;
		return GF_OK;
	case 2:
		info->name = "beamWidth";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_SpotLight *) node)->beamWidth;
		return GF_OK;
	case 3:
		info->name = "color";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFCOLOR;
		info->far_ptr = & ((M_SpotLight *) node)->color;
		return GF_OK;
	case 4:
		info->name = "cutOffAngle";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_SpotLight *) node)->cutOffAngle;
		return GF_OK;
	case 5:
		info->name = "direction";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_SpotLight *) node)->direction;
		return GF_OK;
	case 6:
		info->name = "intensity";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_SpotLight *) node)->intensity;
		return GF_OK;
	case 7:
		info->name = "location";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_SpotLight *) node)->location;
		return GF_OK;
	case 8:
		info->name = "on";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_SpotLight *) node)->on;
		return GF_OK;
	case 9:
		info->name = "radius";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_SpotLight *) node)->radius;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 SpotLight_get_field_index_by_name(char *name)
{
	if (!strcmp("ambientIntensity", name)) return 0;
	if (!strcmp("attenuation", name)) return 1;
	if (!strcmp("beamWidth", name)) return 2;
	if (!strcmp("color", name)) return 3;
	if (!strcmp("cutOffAngle", name)) return 4;
	if (!strcmp("direction", name)) return 5;
	if (!strcmp("intensity", name)) return 6;
	if (!strcmp("location", name)) return 7;
	if (!strcmp("on", name)) return 8;
	if (!strcmp("radius", name)) return 9;
	return -1;
	}
static Bool SpotLight_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 8;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 1:
		*AType = 1;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 2:
		*AType = 8;
		*QType = 6;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1.5707963);
		return 1;
	case 3:
		*AType = 4;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 4:
		*AType = 8;
		*QType = 6;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1.5707963);
		return 1;
	case 5:
		*AType = 9;
		*QType = 9;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 6:
		*AType = 8;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 7:
		*AType = 1;
		*QType = 1;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 9:
		*AType = 7;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *SpotLight_Create()
{
	M_SpotLight *p;
	GF_SAFEALLOC(p, M_SpotLight);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_SpotLight);

	/*default field values*/
	p->ambientIntensity = FLT2FIX(0);
	p->attenuation.x = FLT2FIX(1);
	p->attenuation.y = FLT2FIX(0);
	p->attenuation.z = FLT2FIX(0);
	p->beamWidth = FLT2FIX(1.570796);
	p->color.red = FLT2FIX(1);
	p->color.green = FLT2FIX(1);
	p->color.blue = FLT2FIX(1);
	p->cutOffAngle = FLT2FIX(0.785398);
	p->direction.x = FLT2FIX(0);
	p->direction.y = FLT2FIX(0);
	p->direction.z = FLT2FIX(-1);
	p->intensity = FLT2FIX(1);
	p->location.x = FLT2FIX(0);
	p->location.y = FLT2FIX(0);
	p->location.z = FLT2FIX(0);
	p->on = 1;
	p->radius = FLT2FIX(100);
	return (GF_Node *)p;
}


/*
	Switch Node deletion
*/

static void Switch_Del(GF_Node *node)
{
	M_Switch *p = (M_Switch *) node;
	gf_node_unregister_children((GF_Node *) p, p->choice);	
	gf_node_free((GF_Node *) p);
}

static const u16 Switch_Def2All[] = { 0, 1};
static const u16 Switch_In2All[] = { 0, 1};
static const u16 Switch_Out2All[] = { 0, 1};

static u32 Switch_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 2;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 2;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 2;
	}
}

static GF_Err Switch_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Switch_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Switch_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Switch_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Switch_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "choice";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_Switch *)node)->choice;
		return GF_OK;
	case 1:
		info->name = "whichChoice";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_Switch *) node)->whichChoice;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Switch_get_field_index_by_name(char *name)
{
	if (!strcmp("choice", name)) return 0;
	if (!strcmp("whichChoice", name)) return 1;
	return -1;
	}
static Bool Switch_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 10;
		*b_min = FLT2FIX(-1);
		*b_max = FLT2FIX( 1022);
		return 1;
	default:
		return 0;
	}
}



GF_Node *Switch_Create()
{
	M_Switch *p;
	GF_SAFEALLOC(p, M_Switch);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Switch);

	/*default field values*/
	p->whichChoice = -1;
	return (GF_Node *)p;
}


/*
	TermCap Node deletion
*/

static void TermCap_Del(GF_Node *node)
{
	M_TermCap *p = (M_TermCap *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 TermCap_Def2All[] = { 1};
static const u16 TermCap_In2All[] = { 0, 1};
static const u16 TermCap_Out2All[] = { 1, 2};

static u32 TermCap_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 2;
	case GF_SG_FIELD_CODING_DEF: return 1;
	case GF_SG_FIELD_CODING_OUT: return 2;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 3;
	}
}

static GF_Err TermCap_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = TermCap_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = TermCap_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = TermCap_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err TermCap_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "evaluate";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_TermCap *)node)->on_evaluate;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_TermCap *) node)->evaluate;
		return GF_OK;
	case 1:
		info->name = "capability";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_TermCap *) node)->capability;
		return GF_OK;
	case 2:
		info->name = "value";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_TermCap *) node)->value;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 TermCap_get_field_index_by_name(char *name)
{
	if (!strcmp("evaluate", name)) return 0;
	if (!strcmp("capability", name)) return 1;
	if (!strcmp("value", name)) return 2;
	return -1;
	}
static Bool TermCap_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 7;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(127);
		return 1;
	case 2:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 3;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(7);
		return 1;
	default:
		return 0;
	}
}



GF_Node *TermCap_Create()
{
	M_TermCap *p;
	GF_SAFEALLOC(p, M_TermCap);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_TermCap);

	/*default field values*/
	p->capability = 0;
	return (GF_Node *)p;
}


/*
	Text Node deletion
*/

static void Text_Del(GF_Node *node)
{
	M_Text *p = (M_Text *) node;
	gf_sg_mfstring_del(p->string);
	gf_sg_mffloat_del(p->length);
	gf_node_unregister((GF_Node *) p->fontStyle, (GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 Text_Def2All[] = { 0, 1, 2, 3};
static const u16 Text_In2All[] = { 0, 1, 2, 3};
static const u16 Text_Out2All[] = { 0, 1, 2, 3};
static const u16 Text_Dyn2All[] = { 1, 3};

static u32 Text_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 4;
	case GF_SG_FIELD_CODING_OUT: return 4;
	case GF_SG_FIELD_CODING_DYN: return 2;
	default:
		return 4;
	}
}

static GF_Err Text_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Text_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Text_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Text_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Text_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Text_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "string";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFSTRING;
		info->far_ptr = & ((M_Text *) node)->string;
		return GF_OK;
	case 1:
		info->name = "length";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_Text *) node)->length;
		return GF_OK;
	case 2:
		info->name = "fontStyle";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFFontStyleNode;
		info->far_ptr = & ((M_Text *)node)->fontStyle;
		return GF_OK;
	case 3:
		info->name = "maxExtent";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Text *) node)->maxExtent;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Text_get_field_index_by_name(char *name)
{
	if (!strcmp("string", name)) return 0;
	if (!strcmp("length", name)) return 1;
	if (!strcmp("fontStyle", name)) return 2;
	if (!strcmp("maxExtent", name)) return 3;
	return -1;
	}
static Bool Text_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 7;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 3:
		*AType = 7;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Text_Create()
{
	M_Text *p;
	GF_SAFEALLOC(p, M_Text);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Text);

	/*default field values*/
	p->maxExtent = FLT2FIX(0.0);
	return (GF_Node *)p;
}


/*
	TextureCoordinate Node deletion
*/

static void TextureCoordinate_Del(GF_Node *node)
{
	M_TextureCoordinate *p = (M_TextureCoordinate *) node;
	gf_sg_mfvec2f_del(p->point);
	gf_node_free((GF_Node *) p);
}

static const u16 TextureCoordinate_Def2All[] = { 0};
static const u16 TextureCoordinate_In2All[] = { 0};
static const u16 TextureCoordinate_Out2All[] = { 0};
static const u16 TextureCoordinate_Dyn2All[] = { 0};

static u32 TextureCoordinate_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 1;
	case GF_SG_FIELD_CODING_DEF: return 1;
	case GF_SG_FIELD_CODING_OUT: return 1;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 1;
	}
}

static GF_Err TextureCoordinate_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = TextureCoordinate_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = TextureCoordinate_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = TextureCoordinate_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = TextureCoordinate_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err TextureCoordinate_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "point";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC2F;
		info->far_ptr = & ((M_TextureCoordinate *) node)->point;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 TextureCoordinate_get_field_index_by_name(char *name)
{
	if (!strcmp("point", name)) return 0;
	return -1;
	}
static Bool TextureCoordinate_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 2;
		*QType = 5;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *TextureCoordinate_Create()
{
	M_TextureCoordinate *p;
	GF_SAFEALLOC(p, M_TextureCoordinate);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_TextureCoordinate);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	TextureTransform Node deletion
*/

static void TextureTransform_Del(GF_Node *node)
{
	M_TextureTransform *p = (M_TextureTransform *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 TextureTransform_Def2All[] = { 0, 1, 2, 3};
static const u16 TextureTransform_In2All[] = { 0, 1, 2, 3};
static const u16 TextureTransform_Out2All[] = { 0, 1, 2, 3};
static const u16 TextureTransform_Dyn2All[] = { 0, 1, 2, 3};

static u32 TextureTransform_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 4;
	case GF_SG_FIELD_CODING_OUT: return 4;
	case GF_SG_FIELD_CODING_DYN: return 4;
	default:
		return 4;
	}
}

static GF_Err TextureTransform_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = TextureTransform_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = TextureTransform_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = TextureTransform_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = TextureTransform_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err TextureTransform_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "center";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_TextureTransform *) node)->center;
		return GF_OK;
	case 1:
		info->name = "rotation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_TextureTransform *) node)->rotation;
		return GF_OK;
	case 2:
		info->name = "scale";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_TextureTransform *) node)->scale;
		return GF_OK;
	case 3:
		info->name = "translation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_TextureTransform *) node)->translation;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 TextureTransform_get_field_index_by_name(char *name)
{
	if (!strcmp("center", name)) return 0;
	if (!strcmp("rotation", name)) return 1;
	if (!strcmp("scale", name)) return 2;
	if (!strcmp("translation", name)) return 3;
	return -1;
	}
static Bool TextureTransform_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 2;
		*QType = 2;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 1:
		*AType = 6;
		*QType = 6;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(6.2831853);
		return 1;
	case 2:
		*AType = 12;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 3:
		*AType = 2;
		*QType = 2;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *TextureTransform_Create()
{
	M_TextureTransform *p;
	GF_SAFEALLOC(p, M_TextureTransform);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_TextureTransform);

	/*default field values*/
	p->center.x = FLT2FIX(0);
	p->center.y = FLT2FIX(0);
	p->rotation = FLT2FIX(0);
	p->scale.x = FLT2FIX(1);
	p->scale.y = FLT2FIX(1);
	p->translation.x = FLT2FIX(0);
	p->translation.y = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	TimeSensor Node deletion
*/

static void TimeSensor_Del(GF_Node *node)
{
	M_TimeSensor *p = (M_TimeSensor *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 TimeSensor_Def2All[] = { 0, 1, 2, 3, 4};
static const u16 TimeSensor_In2All[] = { 0, 1, 2, 3, 4};
static const u16 TimeSensor_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};

static u32 TimeSensor_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 5;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 9;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 9;
	}
}

static GF_Err TimeSensor_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = TimeSensor_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = TimeSensor_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = TimeSensor_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err TimeSensor_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "cycleInterval";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_TimeSensor *) node)->cycleInterval;
		return GF_OK;
	case 1:
		info->name = "enabled";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_TimeSensor *) node)->enabled;
		return GF_OK;
	case 2:
		info->name = "loop";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_TimeSensor *) node)->loop;
		return GF_OK;
	case 3:
		info->name = "startTime";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_TimeSensor *) node)->startTime;
		return GF_OK;
	case 4:
		info->name = "stopTime";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_TimeSensor *) node)->stopTime;
		return GF_OK;
	case 5:
		info->name = "cycleTime";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_TimeSensor *) node)->cycleTime;
		return GF_OK;
	case 6:
		info->name = "fraction_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_TimeSensor *) node)->fraction_changed;
		return GF_OK;
	case 7:
		info->name = "isActive";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_TimeSensor *) node)->isActive;
		return GF_OK;
	case 8:
		info->name = "time";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_TimeSensor *) node)->time;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 TimeSensor_get_field_index_by_name(char *name)
{
	if (!strcmp("cycleInterval", name)) return 0;
	if (!strcmp("enabled", name)) return 1;
	if (!strcmp("loop", name)) return 2;
	if (!strcmp("startTime", name)) return 3;
	if (!strcmp("stopTime", name)) return 4;
	if (!strcmp("cycleTime", name)) return 5;
	if (!strcmp("fraction_changed", name)) return 6;
	if (!strcmp("isActive", name)) return 7;
	if (!strcmp("time", name)) return 8;
	return -1;
	}
static Bool TimeSensor_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *TimeSensor_Create()
{
	M_TimeSensor *p;
	GF_SAFEALLOC(p, M_TimeSensor);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_TimeSensor);

	/*default field values*/
	p->cycleInterval = 1;
	p->enabled = 1;
	p->startTime = 0;
	p->stopTime = 0;
	return (GF_Node *)p;
}


/*
	TouchSensor Node deletion
*/

static void TouchSensor_Del(GF_Node *node)
{
	M_TouchSensor *p = (M_TouchSensor *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 TouchSensor_Def2All[] = { 0};
static const u16 TouchSensor_In2All[] = { 0};
static const u16 TouchSensor_Out2All[] = { 0, 1, 2, 3, 4, 5, 6};

static u32 TouchSensor_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 1;
	case GF_SG_FIELD_CODING_DEF: return 1;
	case GF_SG_FIELD_CODING_OUT: return 7;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 7;
	}
}

static GF_Err TouchSensor_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = TouchSensor_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = TouchSensor_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = TouchSensor_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err TouchSensor_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "enabled";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_TouchSensor *) node)->enabled;
		return GF_OK;
	case 1:
		info->name = "hitNormal_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_TouchSensor *) node)->hitNormal_changed;
		return GF_OK;
	case 2:
		info->name = "hitPoint_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_TouchSensor *) node)->hitPoint_changed;
		return GF_OK;
	case 3:
		info->name = "hitTexCoord_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_TouchSensor *) node)->hitTexCoord_changed;
		return GF_OK;
	case 4:
		info->name = "isActive";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_TouchSensor *) node)->isActive;
		return GF_OK;
	case 5:
		info->name = "isOver";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_TouchSensor *) node)->isOver;
		return GF_OK;
	case 6:
		info->name = "touchTime";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_TouchSensor *) node)->touchTime;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 TouchSensor_get_field_index_by_name(char *name)
{
	if (!strcmp("enabled", name)) return 0;
	if (!strcmp("hitNormal_changed", name)) return 1;
	if (!strcmp("hitPoint_changed", name)) return 2;
	if (!strcmp("hitTexCoord_changed", name)) return 3;
	if (!strcmp("isActive", name)) return 4;
	if (!strcmp("isOver", name)) return 5;
	if (!strcmp("touchTime", name)) return 6;
	return -1;
	}
static Bool TouchSensor_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *TouchSensor_Create()
{
	M_TouchSensor *p;
	GF_SAFEALLOC(p, M_TouchSensor);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_TouchSensor);

	/*default field values*/
	p->enabled = 1;
	return (GF_Node *)p;
}


/*
	Transform Node deletion
*/

static void Transform_Del(GF_Node *node)
{
	M_Transform *p = (M_Transform *) node;
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 Transform_Def2All[] = { 2, 3, 4, 5, 6, 7};
static const u16 Transform_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7};
static const u16 Transform_Out2All[] = { 2, 3, 4, 5, 6, 7};
static const u16 Transform_Dyn2All[] = { 2, 4, 5, 6, 7};

static u32 Transform_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 8;
	case GF_SG_FIELD_CODING_DEF: return 6;
	case GF_SG_FIELD_CODING_OUT: return 6;
	case GF_SG_FIELD_CODING_DYN: return 5;
	default:
		return 8;
	}
}

static GF_Err Transform_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Transform_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Transform_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Transform_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Transform_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Transform_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Transform *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_Transform *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Transform *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_Transform *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "center";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_Transform *) node)->center;
		return GF_OK;
	case 3:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_Transform *)node)->children;
		return GF_OK;
	case 4:
		info->name = "rotation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFROTATION;
		info->far_ptr = & ((M_Transform *) node)->rotation;
		return GF_OK;
	case 5:
		info->name = "scale";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_Transform *) node)->scale;
		return GF_OK;
	case 6:
		info->name = "scaleOrientation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFROTATION;
		info->far_ptr = & ((M_Transform *) node)->scaleOrientation;
		return GF_OK;
	case 7:
		info->name = "translation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_Transform *) node)->translation;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Transform_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("center", name)) return 2;
	if (!strcmp("children", name)) return 3;
	if (!strcmp("rotation", name)) return 4;
	if (!strcmp("scale", name)) return 5;
	if (!strcmp("scaleOrientation", name)) return 6;
	if (!strcmp("translation", name)) return 7;
	return -1;
	}
static Bool Transform_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 2:
		*AType = 1;
		*QType = 1;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 4:
		*AType = 10;
		*QType = 10;
		return 1;
	case 5:
		*AType = 11;
		*QType = 7;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 6:
		*AType = 10;
		*QType = 10;
		return 1;
	case 7:
		*AType = 1;
		*QType = 1;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Transform_Create()
{
	M_Transform *p;
	GF_SAFEALLOC(p, M_Transform);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Transform);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->center.x = FLT2FIX(0);
	p->center.y = FLT2FIX(0);
	p->center.z = FLT2FIX(0);
	p->rotation.x = FLT2FIX(0);
	p->rotation.y = FLT2FIX(0);
	p->rotation.z = FLT2FIX(1);
	p->rotation.q = FLT2FIX(0);
	p->scale.x = FLT2FIX(1);
	p->scale.y = FLT2FIX(1);
	p->scale.z = FLT2FIX(1);
	p->scaleOrientation.x = FLT2FIX(0);
	p->scaleOrientation.y = FLT2FIX(0);
	p->scaleOrientation.z = FLT2FIX(1);
	p->scaleOrientation.q = FLT2FIX(0);
	p->translation.x = FLT2FIX(0);
	p->translation.y = FLT2FIX(0);
	p->translation.z = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	Transform2D Node deletion
*/

static void Transform2D_Del(GF_Node *node)
{
	M_Transform2D *p = (M_Transform2D *) node;
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 Transform2D_Def2All[] = { 2, 3, 4, 5, 6, 7};
static const u16 Transform2D_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7};
static const u16 Transform2D_Out2All[] = { 2, 3, 4, 5, 6, 7};
static const u16 Transform2D_Dyn2All[] = { 3, 4, 5, 6, 7};

static u32 Transform2D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 8;
	case GF_SG_FIELD_CODING_DEF: return 6;
	case GF_SG_FIELD_CODING_OUT: return 6;
	case GF_SG_FIELD_CODING_DYN: return 5;
	default:
		return 8;
	}
}

static GF_Err Transform2D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Transform2D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Transform2D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Transform2D_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Transform2D_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Transform2D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Transform2D *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_Transform2D *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Transform2D *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_Transform2D *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_Transform2D *)node)->children;
		return GF_OK;
	case 3:
		info->name = "center";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_Transform2D *) node)->center;
		return GF_OK;
	case 4:
		info->name = "rotationAngle";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Transform2D *) node)->rotationAngle;
		return GF_OK;
	case 5:
		info->name = "scale";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_Transform2D *) node)->scale;
		return GF_OK;
	case 6:
		info->name = "scaleOrientation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Transform2D *) node)->scaleOrientation;
		return GF_OK;
	case 7:
		info->name = "translation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_Transform2D *) node)->translation;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Transform2D_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	if (!strcmp("center", name)) return 3;
	if (!strcmp("rotationAngle", name)) return 4;
	if (!strcmp("scale", name)) return 5;
	if (!strcmp("scaleOrientation", name)) return 6;
	if (!strcmp("translation", name)) return 7;
	return -1;
	}
static Bool Transform2D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 3:
		*AType = 2;
		*QType = 2;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 4:
		*AType = 6;
		*QType = 6;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(6.2831853);
		return 1;
	case 5:
		*AType = 12;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 6:
		*AType = 6;
		*QType = 6;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(6.2831853);
		return 1;
	case 7:
		*AType = 2;
		*QType = 2;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Transform2D_Create()
{
	M_Transform2D *p;
	GF_SAFEALLOC(p, M_Transform2D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Transform2D);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->center.x = FLT2FIX(0);
	p->center.y = FLT2FIX(0);
	p->rotationAngle = FLT2FIX(0);
	p->scale.x = FLT2FIX(1);
	p->scale.y = FLT2FIX(1);
	p->scaleOrientation = FLT2FIX(0);
	p->translation.x = FLT2FIX(0);
	p->translation.y = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	Valuator Node deletion
*/

static void Valuator_Del(GF_Node *node)
{
	M_Valuator *p = (M_Valuator *) node;
	gf_sg_mfcolor_del(p->inMFColor);
	gf_sg_mffloat_del(p->inMFFloat);
	gf_sg_mfint32_del(p->inMFInt32);
	gf_sg_mfrotation_del(p->inMFRotation);
	gf_sg_sfstring_del(p->inSFString);
	gf_sg_mfstring_del(p->inMFString);
	gf_sg_mfvec2f_del(p->inMFVec2f);
	gf_sg_mfvec3f_del(p->inMFVec3f);
	gf_sg_mfcolor_del(p->outMFColor);
	gf_sg_mffloat_del(p->outMFFloat);
	gf_sg_mfint32_del(p->outMFInt32);
	gf_sg_mfrotation_del(p->outMFRotation);
	gf_sg_sfstring_del(p->outSFString);
	gf_sg_mfstring_del(p->outMFString);
	gf_sg_mfvec2f_del(p->outMFVec2f);
	gf_sg_mfvec3f_del(p->outMFVec3f);
	gf_node_free((GF_Node *) p);
}

static const u16 Valuator_Def2All[] = { 32, 33, 34, 35, 36, 37, 38, 39, 40};
static const u16 Valuator_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 32, 33, 34, 35, 36, 37, 38, 39, 40};
static const u16 Valuator_Out2All[] = { 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40};

static u32 Valuator_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 25;
	case GF_SG_FIELD_CODING_DEF: return 9;
	case GF_SG_FIELD_CODING_OUT: return 25;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 41;
	}
}

static GF_Err Valuator_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Valuator_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Valuator_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Valuator_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Valuator_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "inSFBool";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Valuator *)node)->on_inSFBool;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Valuator *) node)->inSFBool;
		return GF_OK;
	case 1:
		info->name = "inSFColor";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Valuator *)node)->on_inSFColor;
		info->fieldType = GF_SG_VRML_SFCOLOR;
		info->far_ptr = & ((M_Valuator *) node)->inSFColor;
		return GF_OK;
	case 2:
		info->name = "inMFColor";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Valuator *)node)->on_inMFColor;
		info->fieldType = GF_SG_VRML_MFCOLOR;
		info->far_ptr = & ((M_Valuator *) node)->inMFColor;
		return GF_OK;
	case 3:
		info->name = "inSFFloat";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Valuator *)node)->on_inSFFloat;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Valuator *) node)->inSFFloat;
		return GF_OK;
	case 4:
		info->name = "inMFFloat";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Valuator *)node)->on_inMFFloat;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_Valuator *) node)->inMFFloat;
		return GF_OK;
	case 5:
		info->name = "inSFInt32";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Valuator *)node)->on_inSFInt32;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_Valuator *) node)->inSFInt32;
		return GF_OK;
	case 6:
		info->name = "inMFInt32";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Valuator *)node)->on_inMFInt32;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_Valuator *) node)->inMFInt32;
		return GF_OK;
	case 7:
		info->name = "inSFRotation";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Valuator *)node)->on_inSFRotation;
		info->fieldType = GF_SG_VRML_SFROTATION;
		info->far_ptr = & ((M_Valuator *) node)->inSFRotation;
		return GF_OK;
	case 8:
		info->name = "inMFRotation";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Valuator *)node)->on_inMFRotation;
		info->fieldType = GF_SG_VRML_MFROTATION;
		info->far_ptr = & ((M_Valuator *) node)->inMFRotation;
		return GF_OK;
	case 9:
		info->name = "inSFString";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Valuator *)node)->on_inSFString;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_Valuator *) node)->inSFString;
		return GF_OK;
	case 10:
		info->name = "inMFString";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Valuator *)node)->on_inMFString;
		info->fieldType = GF_SG_VRML_MFSTRING;
		info->far_ptr = & ((M_Valuator *) node)->inMFString;
		return GF_OK;
	case 11:
		info->name = "inSFTime";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Valuator *)node)->on_inSFTime;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_Valuator *) node)->inSFTime;
		return GF_OK;
	case 12:
		info->name = "inSFVec2f";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Valuator *)node)->on_inSFVec2f;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_Valuator *) node)->inSFVec2f;
		return GF_OK;
	case 13:
		info->name = "inMFVec2f";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Valuator *)node)->on_inMFVec2f;
		info->fieldType = GF_SG_VRML_MFVEC2F;
		info->far_ptr = & ((M_Valuator *) node)->inMFVec2f;
		return GF_OK;
	case 14:
		info->name = "inSFVec3f";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Valuator *)node)->on_inSFVec3f;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_Valuator *) node)->inSFVec3f;
		return GF_OK;
	case 15:
		info->name = "inMFVec3f";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Valuator *)node)->on_inMFVec3f;
		info->fieldType = GF_SG_VRML_MFVEC3F;
		info->far_ptr = & ((M_Valuator *) node)->inMFVec3f;
		return GF_OK;
	case 16:
		info->name = "outSFBool";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Valuator *) node)->outSFBool;
		return GF_OK;
	case 17:
		info->name = "outSFColor";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFCOLOR;
		info->far_ptr = & ((M_Valuator *) node)->outSFColor;
		return GF_OK;
	case 18:
		info->name = "outMFColor";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_MFCOLOR;
		info->far_ptr = & ((M_Valuator *) node)->outMFColor;
		return GF_OK;
	case 19:
		info->name = "outSFFloat";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Valuator *) node)->outSFFloat;
		return GF_OK;
	case 20:
		info->name = "outMFFloat";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_Valuator *) node)->outMFFloat;
		return GF_OK;
	case 21:
		info->name = "outSFInt32";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_Valuator *) node)->outSFInt32;
		return GF_OK;
	case 22:
		info->name = "outMFInt32";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_Valuator *) node)->outMFInt32;
		return GF_OK;
	case 23:
		info->name = "outSFRotation";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFROTATION;
		info->far_ptr = & ((M_Valuator *) node)->outSFRotation;
		return GF_OK;
	case 24:
		info->name = "outMFRotation";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_MFROTATION;
		info->far_ptr = & ((M_Valuator *) node)->outMFRotation;
		return GF_OK;
	case 25:
		info->name = "outSFString";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_Valuator *) node)->outSFString;
		return GF_OK;
	case 26:
		info->name = "outMFString";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_MFSTRING;
		info->far_ptr = & ((M_Valuator *) node)->outMFString;
		return GF_OK;
	case 27:
		info->name = "outSFTime";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_Valuator *) node)->outSFTime;
		return GF_OK;
	case 28:
		info->name = "outSFVec2f";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_Valuator *) node)->outSFVec2f;
		return GF_OK;
	case 29:
		info->name = "outMFVec2f";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_MFVEC2F;
		info->far_ptr = & ((M_Valuator *) node)->outMFVec2f;
		return GF_OK;
	case 30:
		info->name = "outSFVec3f";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_Valuator *) node)->outSFVec3f;
		return GF_OK;
	case 31:
		info->name = "outMFVec3f";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_MFVEC3F;
		info->far_ptr = & ((M_Valuator *) node)->outMFVec3f;
		return GF_OK;
	case 32:
		info->name = "Factor1";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Valuator *) node)->Factor1;
		return GF_OK;
	case 33:
		info->name = "Factor2";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Valuator *) node)->Factor2;
		return GF_OK;
	case 34:
		info->name = "Factor3";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Valuator *) node)->Factor3;
		return GF_OK;
	case 35:
		info->name = "Factor4";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Valuator *) node)->Factor4;
		return GF_OK;
	case 36:
		info->name = "Offset1";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Valuator *) node)->Offset1;
		return GF_OK;
	case 37:
		info->name = "Offset2";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Valuator *) node)->Offset2;
		return GF_OK;
	case 38:
		info->name = "Offset3";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Valuator *) node)->Offset3;
		return GF_OK;
	case 39:
		info->name = "Offset4";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Valuator *) node)->Offset4;
		return GF_OK;
	case 40:
		info->name = "Sum";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Valuator *) node)->Sum;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Valuator_get_field_index_by_name(char *name)
{
	if (!strcmp("inSFBool", name)) return 0;
	if (!strcmp("inSFColor", name)) return 1;
	if (!strcmp("inMFColor", name)) return 2;
	if (!strcmp("inSFFloat", name)) return 3;
	if (!strcmp("inMFFloat", name)) return 4;
	if (!strcmp("inSFInt32", name)) return 5;
	if (!strcmp("inMFInt32", name)) return 6;
	if (!strcmp("inSFRotation", name)) return 7;
	if (!strcmp("inMFRotation", name)) return 8;
	if (!strcmp("inSFString", name)) return 9;
	if (!strcmp("inMFString", name)) return 10;
	if (!strcmp("inSFTime", name)) return 11;
	if (!strcmp("inSFVec2f", name)) return 12;
	if (!strcmp("inMFVec2f", name)) return 13;
	if (!strcmp("inSFVec3f", name)) return 14;
	if (!strcmp("inMFVec3f", name)) return 15;
	if (!strcmp("outSFBool", name)) return 16;
	if (!strcmp("outSFColor", name)) return 17;
	if (!strcmp("outMFColor", name)) return 18;
	if (!strcmp("outSFFloat", name)) return 19;
	if (!strcmp("outMFFloat", name)) return 20;
	if (!strcmp("outSFInt32", name)) return 21;
	if (!strcmp("outMFInt32", name)) return 22;
	if (!strcmp("outSFRotation", name)) return 23;
	if (!strcmp("outMFRotation", name)) return 24;
	if (!strcmp("outSFString", name)) return 25;
	if (!strcmp("outMFString", name)) return 26;
	if (!strcmp("outSFTime", name)) return 27;
	if (!strcmp("outSFVec2f", name)) return 28;
	if (!strcmp("outMFVec2f", name)) return 29;
	if (!strcmp("outSFVec3f", name)) return 30;
	if (!strcmp("outMFVec3f", name)) return 31;
	if (!strcmp("Factor1", name)) return 32;
	if (!strcmp("Factor2", name)) return 33;
	if (!strcmp("Factor3", name)) return 34;
	if (!strcmp("Factor4", name)) return 35;
	if (!strcmp("Offset1", name)) return 36;
	if (!strcmp("Offset2", name)) return 37;
	if (!strcmp("Offset3", name)) return 38;
	if (!strcmp("Offset4", name)) return 39;
	if (!strcmp("Sum", name)) return 40;
	return -1;
	}
static Bool Valuator_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 32:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 33:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 34:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 35:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 36:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 37:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 38:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 39:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Valuator_Create()
{
	M_Valuator *p;
	GF_SAFEALLOC(p, M_Valuator);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Valuator);

	/*default field values*/
	p->Factor1 = FLT2FIX(1.0);
	p->Factor2 = FLT2FIX(1.0);
	p->Factor3 = FLT2FIX(1.0);
	p->Factor4 = FLT2FIX(1.0);
	p->Offset1 = FLT2FIX(0.0);
	p->Offset2 = FLT2FIX(0.0);
	p->Offset3 = FLT2FIX(0.0);
	p->Offset4 = FLT2FIX(0.0);
	return (GF_Node *)p;
}


/*
	Viewpoint Node deletion
*/

static void Viewpoint_Del(GF_Node *node)
{
	M_Viewpoint *p = (M_Viewpoint *) node;
	gf_sg_sfstring_del(p->description);
	gf_node_free((GF_Node *) p);
}

static const u16 Viewpoint_Def2All[] = { 1, 2, 3, 4, 5};
static const u16 Viewpoint_In2All[] = { 0, 1, 2, 3, 4};
static const u16 Viewpoint_Out2All[] = { 1, 2, 3, 4, 6, 7};
static const u16 Viewpoint_Dyn2All[] = { 1, 3, 4};

static u32 Viewpoint_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 5;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 6;
	case GF_SG_FIELD_CODING_DYN: return 3;
	default:
		return 8;
	}
}

static GF_Err Viewpoint_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Viewpoint_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Viewpoint_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Viewpoint_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Viewpoint_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Viewpoint_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_bind";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Viewpoint *)node)->on_set_bind;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Viewpoint *) node)->set_bind;
		return GF_OK;
	case 1:
		info->name = "fieldOfView";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Viewpoint *) node)->fieldOfView;
		return GF_OK;
	case 2:
		info->name = "jump";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Viewpoint *) node)->jump;
		return GF_OK;
	case 3:
		info->name = "orientation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFROTATION;
		info->far_ptr = & ((M_Viewpoint *) node)->orientation;
		return GF_OK;
	case 4:
		info->name = "position";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_Viewpoint *) node)->position;
		return GF_OK;
	case 5:
		info->name = "description";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_Viewpoint *) node)->description;
		return GF_OK;
	case 6:
		info->name = "bindTime";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_Viewpoint *) node)->bindTime;
		return GF_OK;
	case 7:
		info->name = "isBound";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Viewpoint *) node)->isBound;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Viewpoint_get_field_index_by_name(char *name)
{
	if (!strcmp("set_bind", name)) return 0;
	if (!strcmp("fieldOfView", name)) return 1;
	if (!strcmp("jump", name)) return 2;
	if (!strcmp("orientation", name)) return 3;
	if (!strcmp("position", name)) return 4;
	if (!strcmp("description", name)) return 5;
	if (!strcmp("bindTime", name)) return 6;
	if (!strcmp("isBound", name)) return 7;
	return -1;
	}
static Bool Viewpoint_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 8;
		*QType = 6;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(3.1415927);
		return 1;
	case 3:
		*AType = 10;
		*QType = 10;
		return 1;
	case 4:
		*AType = 1;
		*QType = 1;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Viewpoint_Create()
{
	M_Viewpoint *p;
	GF_SAFEALLOC(p, M_Viewpoint);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Viewpoint);

	/*default field values*/
	p->fieldOfView = FLT2FIX(0.785398);
	p->jump = 1;
	p->orientation.x = FLT2FIX(0);
	p->orientation.y = FLT2FIX(0);
	p->orientation.z = FLT2FIX(1);
	p->orientation.q = FLT2FIX(0);
	p->position.x = FLT2FIX(0);
	p->position.y = FLT2FIX(0);
	p->position.z = FLT2FIX(10);
	return (GF_Node *)p;
}


/*
	VisibilitySensor Node deletion
*/

static void VisibilitySensor_Del(GF_Node *node)
{
	M_VisibilitySensor *p = (M_VisibilitySensor *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 VisibilitySensor_Def2All[] = { 0, 1, 2};
static const u16 VisibilitySensor_In2All[] = { 0, 1, 2};
static const u16 VisibilitySensor_Out2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 VisibilitySensor_Dyn2All[] = { 0, 2};

static u32 VisibilitySensor_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 3;
	case GF_SG_FIELD_CODING_OUT: return 6;
	case GF_SG_FIELD_CODING_DYN: return 2;
	default:
		return 6;
	}
}

static GF_Err VisibilitySensor_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = VisibilitySensor_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = VisibilitySensor_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = VisibilitySensor_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = VisibilitySensor_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err VisibilitySensor_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "center";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_VisibilitySensor *) node)->center;
		return GF_OK;
	case 1:
		info->name = "enabled";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_VisibilitySensor *) node)->enabled;
		return GF_OK;
	case 2:
		info->name = "size";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_VisibilitySensor *) node)->size;
		return GF_OK;
	case 3:
		info->name = "enterTime";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_VisibilitySensor *) node)->enterTime;
		return GF_OK;
	case 4:
		info->name = "exitTime";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_VisibilitySensor *) node)->exitTime;
		return GF_OK;
	case 5:
		info->name = "isActive";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_VisibilitySensor *) node)->isActive;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 VisibilitySensor_get_field_index_by_name(char *name)
{
	if (!strcmp("center", name)) return 0;
	if (!strcmp("enabled", name)) return 1;
	if (!strcmp("size", name)) return 2;
	if (!strcmp("enterTime", name)) return 3;
	if (!strcmp("exitTime", name)) return 4;
	if (!strcmp("isActive", name)) return 5;
	return -1;
	}
static Bool VisibilitySensor_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 1;
		*QType = 1;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 2:
		*AType = 11;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *VisibilitySensor_Create()
{
	M_VisibilitySensor *p;
	GF_SAFEALLOC(p, M_VisibilitySensor);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_VisibilitySensor);

	/*default field values*/
	p->center.x = FLT2FIX(0);
	p->center.y = FLT2FIX(0);
	p->center.z = FLT2FIX(0);
	p->enabled = 1;
	p->size.x = FLT2FIX(0);
	p->size.y = FLT2FIX(0);
	p->size.z = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	Viseme Node deletion
*/

static void Viseme_Del(GF_Node *node)
{
	M_Viseme *p = (M_Viseme *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 Viseme_Def2All[] = { 0, 1, 2, 3};
static const u16 Viseme_In2All[] = { 0, 1, 2, 3};
static const u16 Viseme_Out2All[] = { 0, 1, 2, 3};

static u32 Viseme_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 4;
	case GF_SG_FIELD_CODING_OUT: return 4;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err Viseme_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Viseme_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Viseme_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Viseme_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Viseme_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "viseme_select1";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_Viseme *) node)->viseme_select1;
		return GF_OK;
	case 1:
		info->name = "viseme_select2";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_Viseme *) node)->viseme_select2;
		return GF_OK;
	case 2:
		info->name = "viseme_blend";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_Viseme *) node)->viseme_blend;
		return GF_OK;
	case 3:
		info->name = "viseme_def";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Viseme *) node)->viseme_def;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Viseme_get_field_index_by_name(char *name)
{
	if (!strcmp("viseme_select1", name)) return 0;
	if (!strcmp("viseme_select2", name)) return 1;
	if (!strcmp("viseme_blend", name)) return 2;
	if (!strcmp("viseme_def", name)) return 3;
	return -1;
	}
static Bool Viseme_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 5;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(31);
		return 1;
	case 1:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 5;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(31);
		return 1;
	case 2:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 6;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(63);
		return 1;
	default:
		return 0;
	}
}



GF_Node *Viseme_Create()
{
	M_Viseme *p;
	GF_SAFEALLOC(p, M_Viseme);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Viseme);

	/*default field values*/
	p->viseme_select1 = 0;
	p->viseme_select2 = 0;
	p->viseme_blend = 0;
	return (GF_Node *)p;
}


/*
	WorldInfo Node deletion
*/

static void WorldInfo_Del(GF_Node *node)
{
	M_WorldInfo *p = (M_WorldInfo *) node;
	gf_sg_mfstring_del(p->info);
	gf_sg_sfstring_del(p->title);
	gf_node_free((GF_Node *) p);
}

static const u16 WorldInfo_Def2All[] = { 0, 1};

static u32 WorldInfo_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 0;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 0;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 2;
	}
}

static GF_Err WorldInfo_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_DEF:
		*allField = WorldInfo_Def2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err WorldInfo_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "info";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFSTRING;
		info->far_ptr = & ((M_WorldInfo *) node)->info;
		return GF_OK;
	case 1:
		info->name = "title";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_WorldInfo *) node)->title;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 WorldInfo_get_field_index_by_name(char *name)
{
	if (!strcmp("info", name)) return 0;
	if (!strcmp("title", name)) return 1;
	return -1;
	}
static Bool WorldInfo_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *WorldInfo_Create()
{
	M_WorldInfo *p;
	GF_SAFEALLOC(p, M_WorldInfo);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_WorldInfo);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	AcousticMaterial Node deletion
*/

static void AcousticMaterial_Del(GF_Node *node)
{
	M_AcousticMaterial *p = (M_AcousticMaterial *) node;
	gf_sg_mffloat_del(p->reffunc);
	gf_sg_mffloat_del(p->transfunc);
	gf_sg_mffloat_del(p->refFrequency);
	gf_sg_mffloat_del(p->transFrequency);
	gf_node_free((GF_Node *) p);
}

static const u16 AcousticMaterial_Def2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
static const u16 AcousticMaterial_In2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 AcousticMaterial_Out2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 AcousticMaterial_Dyn2All[] = { 0, 1, 2, 3, 4, 5};

static u32 AcousticMaterial_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 6;
	case GF_SG_FIELD_CODING_DEF: return 10;
	case GF_SG_FIELD_CODING_OUT: return 6;
	case GF_SG_FIELD_CODING_DYN: return 6;
	default:
		return 10;
	}
}

static GF_Err AcousticMaterial_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = AcousticMaterial_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = AcousticMaterial_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = AcousticMaterial_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = AcousticMaterial_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err AcousticMaterial_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "ambientIntensity";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_AcousticMaterial *) node)->ambientIntensity;
		return GF_OK;
	case 1:
		info->name = "diffuseColor";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFCOLOR;
		info->far_ptr = & ((M_AcousticMaterial *) node)->diffuseColor;
		return GF_OK;
	case 2:
		info->name = "emissiveColor";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFCOLOR;
		info->far_ptr = & ((M_AcousticMaterial *) node)->emissiveColor;
		return GF_OK;
	case 3:
		info->name = "shininess";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_AcousticMaterial *) node)->shininess;
		return GF_OK;
	case 4:
		info->name = "specularColor";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFCOLOR;
		info->far_ptr = & ((M_AcousticMaterial *) node)->specularColor;
		return GF_OK;
	case 5:
		info->name = "transparency";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_AcousticMaterial *) node)->transparency;
		return GF_OK;
	case 6:
		info->name = "reffunc";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_AcousticMaterial *) node)->reffunc;
		return GF_OK;
	case 7:
		info->name = "transfunc";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_AcousticMaterial *) node)->transfunc;
		return GF_OK;
	case 8:
		info->name = "refFrequency";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_AcousticMaterial *) node)->refFrequency;
		return GF_OK;
	case 9:
		info->name = "transFrequency";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_AcousticMaterial *) node)->transFrequency;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 AcousticMaterial_get_field_index_by_name(char *name)
{
	if (!strcmp("ambientIntensity", name)) return 0;
	if (!strcmp("diffuseColor", name)) return 1;
	if (!strcmp("emissiveColor", name)) return 2;
	if (!strcmp("shininess", name)) return 3;
	if (!strcmp("specularColor", name)) return 4;
	if (!strcmp("transparency", name)) return 5;
	if (!strcmp("reffunc", name)) return 6;
	if (!strcmp("transfunc", name)) return 7;
	if (!strcmp("refFrequency", name)) return 8;
	if (!strcmp("transFrequency", name)) return 9;
	return -1;
	}
static Bool AcousticMaterial_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 8;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 1:
		*AType = 8;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 2:
		*AType = 8;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 3:
		*AType = 8;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 4:
		*AType = 8;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 5:
		*AType = 8;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 6:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 7:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 8:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 9:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *AcousticMaterial_Create()
{
	M_AcousticMaterial *p;
	GF_SAFEALLOC(p, M_AcousticMaterial);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_AcousticMaterial);

	/*default field values*/
	p->ambientIntensity = FLT2FIX(0.2);
	p->diffuseColor.red = FLT2FIX(0.8);
	p->diffuseColor.green = FLT2FIX(0.8);
	p->diffuseColor.blue = FLT2FIX(0.8);
	p->emissiveColor.red = FLT2FIX(0);
	p->emissiveColor.green = FLT2FIX(0);
	p->emissiveColor.blue = FLT2FIX(0);
	p->shininess = FLT2FIX(0.2);
	p->specularColor.red = FLT2FIX(0);
	p->specularColor.green = FLT2FIX(0);
	p->specularColor.blue = FLT2FIX(0);
	p->transparency = FLT2FIX(0);
	p->reffunc.vals = (SFFloat*)malloc(sizeof(SFFloat)*1);
	p->reffunc.count = 1;
	p->reffunc.vals[0] = FLT2FIX(0);
	p->transfunc.vals = (SFFloat*)malloc(sizeof(SFFloat)*1);
	p->transfunc.count = 1;
	p->transfunc.vals[0] = FLT2FIX(1);
	p->refFrequency.vals = (SFFloat*)malloc(sizeof(SFFloat)*1);
	p->refFrequency.count = 1;
	p->refFrequency.vals[0] = FLT2FIX(0);
	p->transFrequency.vals = (SFFloat*)malloc(sizeof(SFFloat)*1);
	p->transFrequency.count = 1;
	p->transFrequency.vals[0] = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	AcousticScene Node deletion
*/

static void AcousticScene_Del(GF_Node *node)
{
	M_AcousticScene *p = (M_AcousticScene *) node;
	gf_sg_mftime_del(p->reverbTime);
	gf_sg_mffloat_del(p->reverbFreq);
	gf_node_free((GF_Node *) p);
}

static const u16 AcousticScene_Def2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 AcousticScene_In2All[] = { 4, 5};
static const u16 AcousticScene_Out2All[] = { 4, 5};
static const u16 AcousticScene_Dyn2All[] = { 4};

static u32 AcousticScene_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 2;
	case GF_SG_FIELD_CODING_DEF: return 6;
	case GF_SG_FIELD_CODING_OUT: return 2;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 6;
	}
}

static GF_Err AcousticScene_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = AcousticScene_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = AcousticScene_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = AcousticScene_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = AcousticScene_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err AcousticScene_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "center";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_AcousticScene *) node)->center;
		return GF_OK;
	case 1:
		info->name = "Size";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_AcousticScene *) node)->Size;
		return GF_OK;
	case 2:
		info->name = "reverbTime";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFTIME;
		info->far_ptr = & ((M_AcousticScene *) node)->reverbTime;
		return GF_OK;
	case 3:
		info->name = "reverbFreq";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_AcousticScene *) node)->reverbFreq;
		return GF_OK;
	case 4:
		info->name = "reverbLevel";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_AcousticScene *) node)->reverbLevel;
		return GF_OK;
	case 5:
		info->name = "reverbDelay";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_AcousticScene *) node)->reverbDelay;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 AcousticScene_get_field_index_by_name(char *name)
{
	if (!strcmp("center", name)) return 0;
	if (!strcmp("Size", name)) return 1;
	if (!strcmp("reverbTime", name)) return 2;
	if (!strcmp("reverbFreq", name)) return 3;
	if (!strcmp("reverbLevel", name)) return 4;
	if (!strcmp("reverbDelay", name)) return 5;
	return -1;
	}
static Bool AcousticScene_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 0;
		*QType = 1;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 1:
		*AType = 0;
		*QType = 11;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 2:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0 );
		*b_max = FIX_MAX;
		return 1;
	case 3:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0 );
		*b_max = FIX_MAX;
		return 1;
	case 4:
		*AType = 7;
		*QType = 0;
		*b_min = FLT2FIX(0 );
		*b_max = FIX_MAX;
		return 1;
	case 5:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0 );
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *AcousticScene_Create()
{
	M_AcousticScene *p;
	GF_SAFEALLOC(p, M_AcousticScene);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_AcousticScene);

	/*default field values*/
	p->center.x = FLT2FIX(0);
	p->center.y = FLT2FIX(0);
	p->center.z = FLT2FIX(0);
	p->Size.x = FLT2FIX(-1);
	p->Size.y = FLT2FIX(-1);
	p->Size.z = FLT2FIX(-1);
	p->reverbTime.vals = (SFTime*)malloc(sizeof(SFTime)*1);
	p->reverbTime.count = 1;
	p->reverbTime.vals[0] = 0;
	p->reverbFreq.vals = (SFFloat*)malloc(sizeof(SFFloat)*1);
	p->reverbFreq.count = 1;
	p->reverbFreq.vals[0] = FLT2FIX(1000);
	p->reverbLevel = FLT2FIX(0.4);
	p->reverbDelay = 0.5;
	return (GF_Node *)p;
}


/*
	ApplicationWindow Node deletion
*/

static void ApplicationWindow_Del(GF_Node *node)
{
	M_ApplicationWindow *p = (M_ApplicationWindow *) node;
	gf_sg_sfstring_del(p->description);
	gf_sg_mfstring_del(p->parameter);
	gf_sg_mfurl_del(p->url);
	gf_node_free((GF_Node *) p);
}

static const u16 ApplicationWindow_Def2All[] = { 0, 1, 2, 3, 4, 5, 6};
static const u16 ApplicationWindow_In2All[] = { 0, 1, 2, 3, 4, 5, 6};
static const u16 ApplicationWindow_Out2All[] = { 0, 1, 2, 3, 4, 5, 6};
static const u16 ApplicationWindow_Dyn2All[] = { 6};

static u32 ApplicationWindow_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 7;
	case GF_SG_FIELD_CODING_DEF: return 7;
	case GF_SG_FIELD_CODING_OUT: return 7;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 7;
	}
}

static GF_Err ApplicationWindow_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = ApplicationWindow_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = ApplicationWindow_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = ApplicationWindow_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = ApplicationWindow_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err ApplicationWindow_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "isActive";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_ApplicationWindow *) node)->isActive;
		return GF_OK;
	case 1:
		info->name = "startTime";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_ApplicationWindow *) node)->startTime;
		return GF_OK;
	case 2:
		info->name = "stopTime";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_ApplicationWindow *) node)->stopTime;
		return GF_OK;
	case 3:
		info->name = "description";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_ApplicationWindow *) node)->description;
		return GF_OK;
	case 4:
		info->name = "parameter";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFSTRING;
		info->far_ptr = & ((M_ApplicationWindow *) node)->parameter;
		return GF_OK;
	case 5:
		info->name = "url";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_ApplicationWindow *) node)->url;
		return GF_OK;
	case 6:
		info->name = "size";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_ApplicationWindow *) node)->size;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 ApplicationWindow_get_field_index_by_name(char *name)
{
	if (!strcmp("isActive", name)) return 0;
	if (!strcmp("startTime", name)) return 1;
	if (!strcmp("stopTime", name)) return 2;
	if (!strcmp("description", name)) return 3;
	if (!strcmp("parameter", name)) return 4;
	if (!strcmp("url", name)) return 5;
	if (!strcmp("size", name)) return 6;
	return -1;
	}
static Bool ApplicationWindow_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 2:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 6:
		*AType = 12;
		*QType = 12;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *ApplicationWindow_Create()
{
	M_ApplicationWindow *p;
	GF_SAFEALLOC(p, M_ApplicationWindow);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_ApplicationWindow);

	/*default field values*/
	p->startTime = 0;
	p->stopTime = 0;
	p->size.x = FLT2FIX(0);
	p->size.y = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	BAP Node deletion
*/

static void BAP_Del(GF_Node *node)
{
	M_BAP *p = (M_BAP *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 BAP_Def2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295};
static const u16 BAP_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295};
static const u16 BAP_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31, 32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47, 48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63, 64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79, 80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95, 96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111, 112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127, 128, 129, 130, 131, 132, 133, 134, 135, 136, 137, 138, 139, 140, 141, 142, 143, 144, 145, 146, 147, 148, 149, 150, 151, 152, 153, 154, 155, 156, 157, 158, 159, 160, 161, 162, 163, 164, 165, 166, 167, 168, 169, 170, 171, 172, 173, 174, 175, 176, 177, 178, 179, 180, 181, 182, 183, 184, 185, 186, 187, 188, 189, 190, 191, 192, 193, 194, 195, 196, 197, 198, 199, 200, 201, 202, 203, 204, 205, 206, 207, 208, 209, 210, 211, 212, 213, 214, 215, 216, 217, 218, 219, 220, 221, 222, 223, 224, 225, 226, 227, 228, 229, 230, 231, 232, 233, 234, 235, 236, 237, 238, 239, 240, 241, 242, 243, 244, 245, 246, 247, 248, 249, 250, 251, 252, 253, 254, 255, 256, 257, 258, 259, 260, 261, 262, 263, 264, 265, 266, 267, 268, 269, 270, 271, 272, 273, 274, 275, 276, 277, 278, 279, 280, 281, 282, 283, 284, 285, 286, 287, 288, 289, 290, 291, 292, 293, 294, 295};

static u32 BAP_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 296;
	case GF_SG_FIELD_CODING_DEF: return 296;
	case GF_SG_FIELD_CODING_OUT: return 296;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 296;
	}
}

static GF_Err BAP_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = BAP_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = BAP_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = BAP_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err BAP_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "sacroiliac_tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->sacroiliac_tilt;
		return GF_OK;
	case 1:
		info->name = "sacroiliac_torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->sacroiliac_torsion;
		return GF_OK;
	case 2:
		info->name = "sacroiliac_roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->sacroiliac_roll;
		return GF_OK;
	case 3:
		info->name = "l_hip_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_hip_flexion;
		return GF_OK;
	case 4:
		info->name = "r_hip_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_hip_flexion;
		return GF_OK;
	case 5:
		info->name = "l_hip_abduct";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_hip_abduct;
		return GF_OK;
	case 6:
		info->name = "r_hip_abduct";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_hip_abduct;
		return GF_OK;
	case 7:
		info->name = "l_hip_twisting";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_hip_twisting;
		return GF_OK;
	case 8:
		info->name = "r_hip_twisting";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_hip_twisting;
		return GF_OK;
	case 9:
		info->name = "l_knee_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_knee_flexion;
		return GF_OK;
	case 10:
		info->name = "r_knee_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_knee_flexion;
		return GF_OK;
	case 11:
		info->name = "l_knee_twisting";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_knee_twisting;
		return GF_OK;
	case 12:
		info->name = "r_knee_twisting";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_knee_twisting;
		return GF_OK;
	case 13:
		info->name = "l_ankle_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_ankle_flexion;
		return GF_OK;
	case 14:
		info->name = "r_ankle_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_ankle_flexion;
		return GF_OK;
	case 15:
		info->name = "l_ankle_twisting";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_ankle_twisting;
		return GF_OK;
	case 16:
		info->name = "r_ankle_twisting";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_ankle_twisting;
		return GF_OK;
	case 17:
		info->name = "l_subtalar_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_subtalar_flexion;
		return GF_OK;
	case 18:
		info->name = "r_subtalar_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_subtalar_flexion;
		return GF_OK;
	case 19:
		info->name = "l_midtarsal_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_midtarsal_flexion;
		return GF_OK;
	case 20:
		info->name = "r_midtarsal_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_midtarsal_flexion;
		return GF_OK;
	case 21:
		info->name = "l_metatarsal_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_metatarsal_flexion;
		return GF_OK;
	case 22:
		info->name = "r_metatarsal_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_metatarsal_flexion;
		return GF_OK;
	case 23:
		info->name = "l_sternoclavicular_abduct";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_sternoclavicular_abduct;
		return GF_OK;
	case 24:
		info->name = "r_sternoclavicular_abduct";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_sternoclavicular_abduct;
		return GF_OK;
	case 25:
		info->name = "l_sternoclavicular_rotate";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_sternoclavicular_rotate;
		return GF_OK;
	case 26:
		info->name = "r_sternoclavicular_rotate";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_sternoclavicular_rotate;
		return GF_OK;
	case 27:
		info->name = "l_acromioclavicular_abduct";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_acromioclavicular_abduct;
		return GF_OK;
	case 28:
		info->name = "r_acromioclavicular_abduct";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_acromioclavicular_abduct;
		return GF_OK;
	case 29:
		info->name = "l_acromioclavicular_rotate";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_acromioclavicular_rotate;
		return GF_OK;
	case 30:
		info->name = "r_acromioclavicular_rotate";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_acromioclavicular_rotate;
		return GF_OK;
	case 31:
		info->name = "l_shoulder_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_shoulder_flexion;
		return GF_OK;
	case 32:
		info->name = "r_shoulder_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_shoulder_flexion;
		return GF_OK;
	case 33:
		info->name = "l_shoulder_abduct";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_shoulder_abduct;
		return GF_OK;
	case 34:
		info->name = "r_shoulder_abduct";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_shoulder_abduct;
		return GF_OK;
	case 35:
		info->name = "l_shoulder_twisting";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_shoulder_twisting;
		return GF_OK;
	case 36:
		info->name = "r_shoulder_twisting";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_shoulder_twisting;
		return GF_OK;
	case 37:
		info->name = "l_elbow_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_elbow_flexion;
		return GF_OK;
	case 38:
		info->name = "r_elbow_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_elbow_flexion;
		return GF_OK;
	case 39:
		info->name = "l_elbow_twisting";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_elbow_twisting;
		return GF_OK;
	case 40:
		info->name = "r_elbow_twisting";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_elbow_twisting;
		return GF_OK;
	case 41:
		info->name = "l_wrist_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_wrist_flexion;
		return GF_OK;
	case 42:
		info->name = "r_wrist_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_wrist_flexion;
		return GF_OK;
	case 43:
		info->name = "l_wrist_pivot";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_wrist_pivot;
		return GF_OK;
	case 44:
		info->name = "r_wrist_pivot";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_wrist_pivot;
		return GF_OK;
	case 45:
		info->name = "l_wrist_twisting";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_wrist_twisting;
		return GF_OK;
	case 46:
		info->name = "r_wrist_twisting";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_wrist_twisting;
		return GF_OK;
	case 47:
		info->name = "skullbase_roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->skullbase_roll;
		return GF_OK;
	case 48:
		info->name = "skullbase_torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->skullbase_torsion;
		return GF_OK;
	case 49:
		info->name = "skullbase_tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->skullbase_tilt;
		return GF_OK;
	case 50:
		info->name = "vc1roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vc1roll;
		return GF_OK;
	case 51:
		info->name = "vc1torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vc1torsion;
		return GF_OK;
	case 52:
		info->name = "vc1tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vc1tilt;
		return GF_OK;
	case 53:
		info->name = "vc2roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vc2roll;
		return GF_OK;
	case 54:
		info->name = "vc2torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vc2torsion;
		return GF_OK;
	case 55:
		info->name = "vc2tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vc2tilt;
		return GF_OK;
	case 56:
		info->name = "vc3roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vc3roll;
		return GF_OK;
	case 57:
		info->name = "vc3torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vc3torsion;
		return GF_OK;
	case 58:
		info->name = "vc3tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vc3tilt;
		return GF_OK;
	case 59:
		info->name = "vc4roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vc4roll;
		return GF_OK;
	case 60:
		info->name = "vc4torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vc4torsion;
		return GF_OK;
	case 61:
		info->name = "vc4tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vc4tilt;
		return GF_OK;
	case 62:
		info->name = "vc5roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vc5roll;
		return GF_OK;
	case 63:
		info->name = "vc5torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vc5torsion;
		return GF_OK;
	case 64:
		info->name = "vc5tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vc5tilt;
		return GF_OK;
	case 65:
		info->name = "vc6roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vc6roll;
		return GF_OK;
	case 66:
		info->name = "vc6torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vc6torsion;
		return GF_OK;
	case 67:
		info->name = "vc6tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vc6tilt;
		return GF_OK;
	case 68:
		info->name = "vc7roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vc7roll;
		return GF_OK;
	case 69:
		info->name = "vc7torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vc7torsion;
		return GF_OK;
	case 70:
		info->name = "vc7tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vc7tilt;
		return GF_OK;
	case 71:
		info->name = "vt1roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt1roll;
		return GF_OK;
	case 72:
		info->name = "vt1torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt1torsion;
		return GF_OK;
	case 73:
		info->name = "vt1tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt1tilt;
		return GF_OK;
	case 74:
		info->name = "vt2roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt2roll;
		return GF_OK;
	case 75:
		info->name = "vt2torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt2torsion;
		return GF_OK;
	case 76:
		info->name = "vt2tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt2tilt;
		return GF_OK;
	case 77:
		info->name = "vt3roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt3roll;
		return GF_OK;
	case 78:
		info->name = "vt3torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt3torsion;
		return GF_OK;
	case 79:
		info->name = "vt3tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt3tilt;
		return GF_OK;
	case 80:
		info->name = "vt4roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt4roll;
		return GF_OK;
	case 81:
		info->name = "vt4torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt4torsion;
		return GF_OK;
	case 82:
		info->name = "vt4tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt4tilt;
		return GF_OK;
	case 83:
		info->name = "vt5roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt5roll;
		return GF_OK;
	case 84:
		info->name = "vt5torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt5torsion;
		return GF_OK;
	case 85:
		info->name = "vt5tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt5tilt;
		return GF_OK;
	case 86:
		info->name = "vt6roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt6roll;
		return GF_OK;
	case 87:
		info->name = "vt6torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt6torsion;
		return GF_OK;
	case 88:
		info->name = "vt6tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt6tilt;
		return GF_OK;
	case 89:
		info->name = "vt7roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt7roll;
		return GF_OK;
	case 90:
		info->name = "vt7torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt7torsion;
		return GF_OK;
	case 91:
		info->name = "vt7tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt7tilt;
		return GF_OK;
	case 92:
		info->name = "vt8roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt8roll;
		return GF_OK;
	case 93:
		info->name = "vt8torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt8torsion;
		return GF_OK;
	case 94:
		info->name = "vt8tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt8tilt;
		return GF_OK;
	case 95:
		info->name = "vt9roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt9roll;
		return GF_OK;
	case 96:
		info->name = "vt9torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt9torsion;
		return GF_OK;
	case 97:
		info->name = "vt9tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt9tilt;
		return GF_OK;
	case 98:
		info->name = "vt10roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt10roll;
		return GF_OK;
	case 99:
		info->name = "vt10torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt10torsion;
		return GF_OK;
	case 100:
		info->name = "vt10tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt10tilt;
		return GF_OK;
	case 101:
		info->name = "vt11roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt11roll;
		return GF_OK;
	case 102:
		info->name = "vt11torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt11torsion;
		return GF_OK;
	case 103:
		info->name = "vt11tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt11tilt;
		return GF_OK;
	case 104:
		info->name = "vt12roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt12roll;
		return GF_OK;
	case 105:
		info->name = "vt12torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt12torsion;
		return GF_OK;
	case 106:
		info->name = "vt12tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vt12tilt;
		return GF_OK;
	case 107:
		info->name = "vl1roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vl1roll;
		return GF_OK;
	case 108:
		info->name = "vl1torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vl1torsion;
		return GF_OK;
	case 109:
		info->name = "vl1tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vl1tilt;
		return GF_OK;
	case 110:
		info->name = "vl2roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vl2roll;
		return GF_OK;
	case 111:
		info->name = "vl2torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vl2torsion;
		return GF_OK;
	case 112:
		info->name = "vl2tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vl2tilt;
		return GF_OK;
	case 113:
		info->name = "vl3roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vl3roll;
		return GF_OK;
	case 114:
		info->name = "vl3torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vl3torsion;
		return GF_OK;
	case 115:
		info->name = "vl3tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vl3tilt;
		return GF_OK;
	case 116:
		info->name = "vl4roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vl4roll;
		return GF_OK;
	case 117:
		info->name = "vl4torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vl4torsion;
		return GF_OK;
	case 118:
		info->name = "vl4tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vl4tilt;
		return GF_OK;
	case 119:
		info->name = "vl5roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vl5roll;
		return GF_OK;
	case 120:
		info->name = "vl5torsion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vl5torsion;
		return GF_OK;
	case 121:
		info->name = "vl5tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->vl5tilt;
		return GF_OK;
	case 122:
		info->name = "l_pinky0_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_pinky0_flexion;
		return GF_OK;
	case 123:
		info->name = "r_pinky0_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_pinky0_flexion;
		return GF_OK;
	case 124:
		info->name = "l_pinky1_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_pinky1_flexion;
		return GF_OK;
	case 125:
		info->name = "r_pinky1_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_pinky1_flexion;
		return GF_OK;
	case 126:
		info->name = "l_pinky1_pivot";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_pinky1_pivot;
		return GF_OK;
	case 127:
		info->name = "r_pinky1_pivot";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_pinky1_pivot;
		return GF_OK;
	case 128:
		info->name = "l_pinky1_twisting";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_pinky1_twisting;
		return GF_OK;
	case 129:
		info->name = "r_pinky1_twisting";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_pinky1_twisting;
		return GF_OK;
	case 130:
		info->name = "l_pinky2_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_pinky2_flexion;
		return GF_OK;
	case 131:
		info->name = "r_pinky2_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_pinky2_flexion;
		return GF_OK;
	case 132:
		info->name = "l_pinky3_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_pinky3_flexion;
		return GF_OK;
	case 133:
		info->name = "r_pinky3_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_pinky3_flexion;
		return GF_OK;
	case 134:
		info->name = "l_ring0_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_ring0_flexion;
		return GF_OK;
	case 135:
		info->name = "r_ring0_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_ring0_flexion;
		return GF_OK;
	case 136:
		info->name = "l_ring1_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_ring1_flexion;
		return GF_OK;
	case 137:
		info->name = "r_ring1_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_ring1_flexion;
		return GF_OK;
	case 138:
		info->name = "l_ring1_pivot";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_ring1_pivot;
		return GF_OK;
	case 139:
		info->name = "r_ring1_pivot";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_ring1_pivot;
		return GF_OK;
	case 140:
		info->name = "l_ring1_twisting";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_ring1_twisting;
		return GF_OK;
	case 141:
		info->name = "r_ring1_twisting";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_ring1_twisting;
		return GF_OK;
	case 142:
		info->name = "l_ring2_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_ring2_flexion;
		return GF_OK;
	case 143:
		info->name = "r_ring2_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_ring2_flexion;
		return GF_OK;
	case 144:
		info->name = "l_ring3_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_ring3_flexion;
		return GF_OK;
	case 145:
		info->name = "r_ring3_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_ring3_flexion;
		return GF_OK;
	case 146:
		info->name = "l_middle0_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_middle0_flexion;
		return GF_OK;
	case 147:
		info->name = "r_middle0_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_middle0_flexion;
		return GF_OK;
	case 148:
		info->name = "l_middle1_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_middle1_flexion;
		return GF_OK;
	case 149:
		info->name = "r_middle1_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_middle1_flexion;
		return GF_OK;
	case 150:
		info->name = "l_middle1_pivot";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_middle1_pivot;
		return GF_OK;
	case 151:
		info->name = "r_middle1_pivot";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_middle1_pivot;
		return GF_OK;
	case 152:
		info->name = "l_middle1_twisting";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_middle1_twisting;
		return GF_OK;
	case 153:
		info->name = "r_middle1_twisting";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_middle1_twisting;
		return GF_OK;
	case 154:
		info->name = "l_middle2_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_middle2_flexion;
		return GF_OK;
	case 155:
		info->name = "r_middle2_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_middle2_flexion;
		return GF_OK;
	case 156:
		info->name = "l_middle3_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_middle3_flexion;
		return GF_OK;
	case 157:
		info->name = "r_middle3_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_middle3_flexion;
		return GF_OK;
	case 158:
		info->name = "l_index0_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_index0_flexion;
		return GF_OK;
	case 159:
		info->name = "r_index0_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_index0_flexion;
		return GF_OK;
	case 160:
		info->name = "l_index1_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_index1_flexion;
		return GF_OK;
	case 161:
		info->name = "r_index1_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_index1_flexion;
		return GF_OK;
	case 162:
		info->name = "l_index1_pivot";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_index1_pivot;
		return GF_OK;
	case 163:
		info->name = "r_index1_pivot";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_index1_pivot;
		return GF_OK;
	case 164:
		info->name = "l_index1_twisting";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_index1_twisting;
		return GF_OK;
	case 165:
		info->name = "r_index1_twisting";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_index1_twisting;
		return GF_OK;
	case 166:
		info->name = "l_index2_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_index2_flexion;
		return GF_OK;
	case 167:
		info->name = "r_index2_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_index2_flexion;
		return GF_OK;
	case 168:
		info->name = "l_index3_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_index3_flexion;
		return GF_OK;
	case 169:
		info->name = "r_index3_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_index3_flexion;
		return GF_OK;
	case 170:
		info->name = "l_thumb1_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_thumb1_flexion;
		return GF_OK;
	case 171:
		info->name = "r_thumb1_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_thumb1_flexion;
		return GF_OK;
	case 172:
		info->name = "l_thumb1_pivot";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_thumb1_pivot;
		return GF_OK;
	case 173:
		info->name = "r_thumb1_pivot";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_thumb1_pivot;
		return GF_OK;
	case 174:
		info->name = "l_thumb1_twisting";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_thumb1_twisting;
		return GF_OK;
	case 175:
		info->name = "r_thumb1_twisting";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_thumb1_twisting;
		return GF_OK;
	case 176:
		info->name = "l_thumb2_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_thumb2_flexion;
		return GF_OK;
	case 177:
		info->name = "r_thumb2_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_thumb2_flexion;
		return GF_OK;
	case 178:
		info->name = "l_thumb3_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->l_thumb3_flexion;
		return GF_OK;
	case 179:
		info->name = "r_thumb3_flexion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->r_thumb3_flexion;
		return GF_OK;
	case 180:
		info->name = "HumanoidRoot_tr_vertical";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->HumanoidRoot_tr_vertical;
		return GF_OK;
	case 181:
		info->name = "HumanoidRoot_tr_lateral";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->HumanoidRoot_tr_lateral;
		return GF_OK;
	case 182:
		info->name = "HumanoidRoot_tr_frontal";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->HumanoidRoot_tr_frontal;
		return GF_OK;
	case 183:
		info->name = "HumanoidRoot_rt_body_turn";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->HumanoidRoot_rt_body_turn;
		return GF_OK;
	case 184:
		info->name = "HumanoidRoot_rt_body_roll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->HumanoidRoot_rt_body_roll;
		return GF_OK;
	case 185:
		info->name = "HumanoidRoot_rt_body_tilt";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->HumanoidRoot_rt_body_tilt;
		return GF_OK;
	case 186:
		info->name = "extensionBap187";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap187;
		return GF_OK;
	case 187:
		info->name = "extensionBap188";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap188;
		return GF_OK;
	case 188:
		info->name = "extensionBap189";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap189;
		return GF_OK;
	case 189:
		info->name = "extensionBap190";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap190;
		return GF_OK;
	case 190:
		info->name = "extensionBap191";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap191;
		return GF_OK;
	case 191:
		info->name = "extensionBap192";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap192;
		return GF_OK;
	case 192:
		info->name = "extensionBap193";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap193;
		return GF_OK;
	case 193:
		info->name = "extensionBap194";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap194;
		return GF_OK;
	case 194:
		info->name = "extensionBap195";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap195;
		return GF_OK;
	case 195:
		info->name = "extensionBap196";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap196;
		return GF_OK;
	case 196:
		info->name = "extensionBap197";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap197;
		return GF_OK;
	case 197:
		info->name = "extensionBap198";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap198;
		return GF_OK;
	case 198:
		info->name = "extensionBap199";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap199;
		return GF_OK;
	case 199:
		info->name = "extensionBap200";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap200;
		return GF_OK;
	case 200:
		info->name = "extensionBap201";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap201;
		return GF_OK;
	case 201:
		info->name = "extensionBap202";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap202;
		return GF_OK;
	case 202:
		info->name = "extensionBap203";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap203;
		return GF_OK;
	case 203:
		info->name = "extensionBap204";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap204;
		return GF_OK;
	case 204:
		info->name = "extensionBap205";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap205;
		return GF_OK;
	case 205:
		info->name = "extensionBap206";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap206;
		return GF_OK;
	case 206:
		info->name = "extensionBap207";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap207;
		return GF_OK;
	case 207:
		info->name = "extensionBap208";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap208;
		return GF_OK;
	case 208:
		info->name = "extensionBap209";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap209;
		return GF_OK;
	case 209:
		info->name = "extensionBap210";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap210;
		return GF_OK;
	case 210:
		info->name = "extensionBap211";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap211;
		return GF_OK;
	case 211:
		info->name = "extensionBap212";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap212;
		return GF_OK;
	case 212:
		info->name = "extensionBap213";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap213;
		return GF_OK;
	case 213:
		info->name = "extensionBap214";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap214;
		return GF_OK;
	case 214:
		info->name = "extensionBap215";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap215;
		return GF_OK;
	case 215:
		info->name = "extensionBap216";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap216;
		return GF_OK;
	case 216:
		info->name = "extensionBap217";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap217;
		return GF_OK;
	case 217:
		info->name = "extensionBap218";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap218;
		return GF_OK;
	case 218:
		info->name = "extensionBap219";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap219;
		return GF_OK;
	case 219:
		info->name = "extensionBap220";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap220;
		return GF_OK;
	case 220:
		info->name = "extensionBap221";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap221;
		return GF_OK;
	case 221:
		info->name = "extensionBap222";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap222;
		return GF_OK;
	case 222:
		info->name = "extensionBap223";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap223;
		return GF_OK;
	case 223:
		info->name = "extensionBap224";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap224;
		return GF_OK;
	case 224:
		info->name = "extensionBap225";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap225;
		return GF_OK;
	case 225:
		info->name = "extensionBap226";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap226;
		return GF_OK;
	case 226:
		info->name = "extensionBap227";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap227;
		return GF_OK;
	case 227:
		info->name = "extensionBap228";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap228;
		return GF_OK;
	case 228:
		info->name = "extensionBap229";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap229;
		return GF_OK;
	case 229:
		info->name = "extensionBap230";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap230;
		return GF_OK;
	case 230:
		info->name = "extensionBap231";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap231;
		return GF_OK;
	case 231:
		info->name = "extensionBap232";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap232;
		return GF_OK;
	case 232:
		info->name = "extensionBap233";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap233;
		return GF_OK;
	case 233:
		info->name = "extensionBap234";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap234;
		return GF_OK;
	case 234:
		info->name = "extensionBap235";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap235;
		return GF_OK;
	case 235:
		info->name = "extensionBap236";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap236;
		return GF_OK;
	case 236:
		info->name = "extensionBap237";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap237;
		return GF_OK;
	case 237:
		info->name = "extensionBap238";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap238;
		return GF_OK;
	case 238:
		info->name = "extensionBap239";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap239;
		return GF_OK;
	case 239:
		info->name = "extensionBap240";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap240;
		return GF_OK;
	case 240:
		info->name = "extensionBap241";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap241;
		return GF_OK;
	case 241:
		info->name = "extensionBap242";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap242;
		return GF_OK;
	case 242:
		info->name = "extensionBap243";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap243;
		return GF_OK;
	case 243:
		info->name = "extensionBap244";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap244;
		return GF_OK;
	case 244:
		info->name = "extensionBap245";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap245;
		return GF_OK;
	case 245:
		info->name = "extensionBap246";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap246;
		return GF_OK;
	case 246:
		info->name = "extensionBap247";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap247;
		return GF_OK;
	case 247:
		info->name = "extensionBap248";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap248;
		return GF_OK;
	case 248:
		info->name = "extensionBap249";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap249;
		return GF_OK;
	case 249:
		info->name = "extensionBap250";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap250;
		return GF_OK;
	case 250:
		info->name = "extensionBap251";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap251;
		return GF_OK;
	case 251:
		info->name = "extensionBap252";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap252;
		return GF_OK;
	case 252:
		info->name = "extensionBap253";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap253;
		return GF_OK;
	case 253:
		info->name = "extensionBap254";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap254;
		return GF_OK;
	case 254:
		info->name = "extensionBap255";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap255;
		return GF_OK;
	case 255:
		info->name = "extensionBap256";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap256;
		return GF_OK;
	case 256:
		info->name = "extensionBap257";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap257;
		return GF_OK;
	case 257:
		info->name = "extensionBap258";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap258;
		return GF_OK;
	case 258:
		info->name = "extensionBap259";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap259;
		return GF_OK;
	case 259:
		info->name = "extensionBap260";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap260;
		return GF_OK;
	case 260:
		info->name = "extensionBap261";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap261;
		return GF_OK;
	case 261:
		info->name = "extensionBap262";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap262;
		return GF_OK;
	case 262:
		info->name = "extensionBap263";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap263;
		return GF_OK;
	case 263:
		info->name = "extensionBap264";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap264;
		return GF_OK;
	case 264:
		info->name = "extensionBap265";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap265;
		return GF_OK;
	case 265:
		info->name = "extensionBap266";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap266;
		return GF_OK;
	case 266:
		info->name = "extensionBap267";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap267;
		return GF_OK;
	case 267:
		info->name = "extensionBap268";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap268;
		return GF_OK;
	case 268:
		info->name = "extensionBap269";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap269;
		return GF_OK;
	case 269:
		info->name = "extensionBap270";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap270;
		return GF_OK;
	case 270:
		info->name = "extensionBap271";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap271;
		return GF_OK;
	case 271:
		info->name = "extensionBap272";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap272;
		return GF_OK;
	case 272:
		info->name = "extensionBap273";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap273;
		return GF_OK;
	case 273:
		info->name = "extensionBap274";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap274;
		return GF_OK;
	case 274:
		info->name = "extensionBap275";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap275;
		return GF_OK;
	case 275:
		info->name = "extensionBap276";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap276;
		return GF_OK;
	case 276:
		info->name = "extensionBap277";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap277;
		return GF_OK;
	case 277:
		info->name = "extensionBap278";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap278;
		return GF_OK;
	case 278:
		info->name = "extensionBap279";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap279;
		return GF_OK;
	case 279:
		info->name = "extensionBap280";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap280;
		return GF_OK;
	case 280:
		info->name = "extensionBap281";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap281;
		return GF_OK;
	case 281:
		info->name = "extensionBap282";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap282;
		return GF_OK;
	case 282:
		info->name = "extensionBap283";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap283;
		return GF_OK;
	case 283:
		info->name = "extensionBap284";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap284;
		return GF_OK;
	case 284:
		info->name = "extensionBap285";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap285;
		return GF_OK;
	case 285:
		info->name = "extensionBap286";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap286;
		return GF_OK;
	case 286:
		info->name = "extensionBap287";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap287;
		return GF_OK;
	case 287:
		info->name = "extensionBap288";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap288;
		return GF_OK;
	case 288:
		info->name = "extensionBap289";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap289;
		return GF_OK;
	case 289:
		info->name = "extensionBap290";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap290;
		return GF_OK;
	case 290:
		info->name = "extensionBap291";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap291;
		return GF_OK;
	case 291:
		info->name = "extensionBap292";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap292;
		return GF_OK;
	case 292:
		info->name = "extensionBap293";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap293;
		return GF_OK;
	case 293:
		info->name = "extensionBap294";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap294;
		return GF_OK;
	case 294:
		info->name = "extensionBap295";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap295;
		return GF_OK;
	case 295:
		info->name = "extensionBap296";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BAP *) node)->extensionBap296;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 BAP_get_field_index_by_name(char *name)
{
	if (!strcmp("sacroiliac_tilt", name)) return 0;
	if (!strcmp("sacroiliac_torsion", name)) return 1;
	if (!strcmp("sacroiliac_roll", name)) return 2;
	if (!strcmp("l_hip_flexion", name)) return 3;
	if (!strcmp("r_hip_flexion", name)) return 4;
	if (!strcmp("l_hip_abduct", name)) return 5;
	if (!strcmp("r_hip_abduct", name)) return 6;
	if (!strcmp("l_hip_twisting", name)) return 7;
	if (!strcmp("r_hip_twisting", name)) return 8;
	if (!strcmp("l_knee_flexion", name)) return 9;
	if (!strcmp("r_knee_flexion", name)) return 10;
	if (!strcmp("l_knee_twisting", name)) return 11;
	if (!strcmp("r_knee_twisting", name)) return 12;
	if (!strcmp("l_ankle_flexion", name)) return 13;
	if (!strcmp("r_ankle_flexion", name)) return 14;
	if (!strcmp("l_ankle_twisting", name)) return 15;
	if (!strcmp("r_ankle_twisting", name)) return 16;
	if (!strcmp("l_subtalar_flexion", name)) return 17;
	if (!strcmp("r_subtalar_flexion", name)) return 18;
	if (!strcmp("l_midtarsal_flexion", name)) return 19;
	if (!strcmp("r_midtarsal_flexion", name)) return 20;
	if (!strcmp("l_metatarsal_flexion", name)) return 21;
	if (!strcmp("r_metatarsal_flexion", name)) return 22;
	if (!strcmp("l_sternoclavicular_abduct", name)) return 23;
	if (!strcmp("r_sternoclavicular_abduct", name)) return 24;
	if (!strcmp("l_sternoclavicular_rotate", name)) return 25;
	if (!strcmp("r_sternoclavicular_rotate", name)) return 26;
	if (!strcmp("l_acromioclavicular_abduct", name)) return 27;
	if (!strcmp("r_acromioclavicular_abduct", name)) return 28;
	if (!strcmp("l_acromioclavicular_rotate", name)) return 29;
	if (!strcmp("r_acromioclavicular_rotate", name)) return 30;
	if (!strcmp("l_shoulder_flexion", name)) return 31;
	if (!strcmp("r_shoulder_flexion", name)) return 32;
	if (!strcmp("l_shoulder_abduct", name)) return 33;
	if (!strcmp("r_shoulder_abduct", name)) return 34;
	if (!strcmp("l_shoulder_twisting", name)) return 35;
	if (!strcmp("r_shoulder_twisting", name)) return 36;
	if (!strcmp("l_elbow_flexion", name)) return 37;
	if (!strcmp("r_elbow_flexion", name)) return 38;
	if (!strcmp("l_elbow_twisting", name)) return 39;
	if (!strcmp("r_elbow_twisting", name)) return 40;
	if (!strcmp("l_wrist_flexion", name)) return 41;
	if (!strcmp("r_wrist_flexion", name)) return 42;
	if (!strcmp("l_wrist_pivot", name)) return 43;
	if (!strcmp("r_wrist_pivot", name)) return 44;
	if (!strcmp("l_wrist_twisting", name)) return 45;
	if (!strcmp("r_wrist_twisting", name)) return 46;
	if (!strcmp("skullbase_roll", name)) return 47;
	if (!strcmp("skullbase_torsion", name)) return 48;
	if (!strcmp("skullbase_tilt", name)) return 49;
	if (!strcmp("vc1roll", name)) return 50;
	if (!strcmp("vc1torsion", name)) return 51;
	if (!strcmp("vc1tilt", name)) return 52;
	if (!strcmp("vc2roll", name)) return 53;
	if (!strcmp("vc2torsion", name)) return 54;
	if (!strcmp("vc2tilt", name)) return 55;
	if (!strcmp("vc3roll", name)) return 56;
	if (!strcmp("vc3torsion", name)) return 57;
	if (!strcmp("vc3tilt", name)) return 58;
	if (!strcmp("vc4roll", name)) return 59;
	if (!strcmp("vc4torsion", name)) return 60;
	if (!strcmp("vc4tilt", name)) return 61;
	if (!strcmp("vc5roll", name)) return 62;
	if (!strcmp("vc5torsion", name)) return 63;
	if (!strcmp("vc5tilt", name)) return 64;
	if (!strcmp("vc6roll", name)) return 65;
	if (!strcmp("vc6torsion", name)) return 66;
	if (!strcmp("vc6tilt", name)) return 67;
	if (!strcmp("vc7roll", name)) return 68;
	if (!strcmp("vc7torsion", name)) return 69;
	if (!strcmp("vc7tilt", name)) return 70;
	if (!strcmp("vt1roll", name)) return 71;
	if (!strcmp("vt1torsion", name)) return 72;
	if (!strcmp("vt1tilt", name)) return 73;
	if (!strcmp("vt2roll", name)) return 74;
	if (!strcmp("vt2torsion", name)) return 75;
	if (!strcmp("vt2tilt", name)) return 76;
	if (!strcmp("vt3roll", name)) return 77;
	if (!strcmp("vt3torsion", name)) return 78;
	if (!strcmp("vt3tilt", name)) return 79;
	if (!strcmp("vt4roll", name)) return 80;
	if (!strcmp("vt4torsion", name)) return 81;
	if (!strcmp("vt4tilt", name)) return 82;
	if (!strcmp("vt5roll", name)) return 83;
	if (!strcmp("vt5torsion", name)) return 84;
	if (!strcmp("vt5tilt", name)) return 85;
	if (!strcmp("vt6roll", name)) return 86;
	if (!strcmp("vt6torsion", name)) return 87;
	if (!strcmp("vt6tilt", name)) return 88;
	if (!strcmp("vt7roll", name)) return 89;
	if (!strcmp("vt7torsion", name)) return 90;
	if (!strcmp("vt7tilt", name)) return 91;
	if (!strcmp("vt8roll", name)) return 92;
	if (!strcmp("vt8torsion", name)) return 93;
	if (!strcmp("vt8tilt", name)) return 94;
	if (!strcmp("vt9roll", name)) return 95;
	if (!strcmp("vt9torsion", name)) return 96;
	if (!strcmp("vt9tilt", name)) return 97;
	if (!strcmp("vt10roll", name)) return 98;
	if (!strcmp("vt10torsion", name)) return 99;
	if (!strcmp("vt10tilt", name)) return 100;
	if (!strcmp("vt11roll", name)) return 101;
	if (!strcmp("vt11torsion", name)) return 102;
	if (!strcmp("vt11tilt", name)) return 103;
	if (!strcmp("vt12roll", name)) return 104;
	if (!strcmp("vt12torsion", name)) return 105;
	if (!strcmp("vt12tilt", name)) return 106;
	if (!strcmp("vl1roll", name)) return 107;
	if (!strcmp("vl1torsion", name)) return 108;
	if (!strcmp("vl1tilt", name)) return 109;
	if (!strcmp("vl2roll", name)) return 110;
	if (!strcmp("vl2torsion", name)) return 111;
	if (!strcmp("vl2tilt", name)) return 112;
	if (!strcmp("vl3roll", name)) return 113;
	if (!strcmp("vl3torsion", name)) return 114;
	if (!strcmp("vl3tilt", name)) return 115;
	if (!strcmp("vl4roll", name)) return 116;
	if (!strcmp("vl4torsion", name)) return 117;
	if (!strcmp("vl4tilt", name)) return 118;
	if (!strcmp("vl5roll", name)) return 119;
	if (!strcmp("vl5torsion", name)) return 120;
	if (!strcmp("vl5tilt", name)) return 121;
	if (!strcmp("l_pinky0_flexion", name)) return 122;
	if (!strcmp("r_pinky0_flexion", name)) return 123;
	if (!strcmp("l_pinky1_flexion", name)) return 124;
	if (!strcmp("r_pinky1_flexion", name)) return 125;
	if (!strcmp("l_pinky1_pivot", name)) return 126;
	if (!strcmp("r_pinky1_pivot", name)) return 127;
	if (!strcmp("l_pinky1_twisting", name)) return 128;
	if (!strcmp("r_pinky1_twisting", name)) return 129;
	if (!strcmp("l_pinky2_flexion", name)) return 130;
	if (!strcmp("r_pinky2_flexion", name)) return 131;
	if (!strcmp("l_pinky3_flexion", name)) return 132;
	if (!strcmp("r_pinky3_flexion", name)) return 133;
	if (!strcmp("l_ring0_flexion", name)) return 134;
	if (!strcmp("r_ring0_flexion", name)) return 135;
	if (!strcmp("l_ring1_flexion", name)) return 136;
	if (!strcmp("r_ring1_flexion", name)) return 137;
	if (!strcmp("l_ring1_pivot", name)) return 138;
	if (!strcmp("r_ring1_pivot", name)) return 139;
	if (!strcmp("l_ring1_twisting", name)) return 140;
	if (!strcmp("r_ring1_twisting", name)) return 141;
	if (!strcmp("l_ring2_flexion", name)) return 142;
	if (!strcmp("r_ring2_flexion", name)) return 143;
	if (!strcmp("l_ring3_flexion", name)) return 144;
	if (!strcmp("r_ring3_flexion", name)) return 145;
	if (!strcmp("l_middle0_flexion", name)) return 146;
	if (!strcmp("r_middle0_flexion", name)) return 147;
	if (!strcmp("l_middle1_flexion", name)) return 148;
	if (!strcmp("r_middle1_flexion", name)) return 149;
	if (!strcmp("l_middle1_pivot", name)) return 150;
	if (!strcmp("r_middle1_pivot", name)) return 151;
	if (!strcmp("l_middle1_twisting", name)) return 152;
	if (!strcmp("r_middle1_twisting", name)) return 153;
	if (!strcmp("l_middle2_flexion", name)) return 154;
	if (!strcmp("r_middle2_flexion", name)) return 155;
	if (!strcmp("l_middle3_flexion", name)) return 156;
	if (!strcmp("r_middle3_flexion", name)) return 157;
	if (!strcmp("l_index0_flexion", name)) return 158;
	if (!strcmp("r_index0_flexion", name)) return 159;
	if (!strcmp("l_index1_flexion", name)) return 160;
	if (!strcmp("r_index1_flexion", name)) return 161;
	if (!strcmp("l_index1_pivot", name)) return 162;
	if (!strcmp("r_index1_pivot", name)) return 163;
	if (!strcmp("l_index1_twisting", name)) return 164;
	if (!strcmp("r_index1_twisting", name)) return 165;
	if (!strcmp("l_index2_flexion", name)) return 166;
	if (!strcmp("r_index2_flexion", name)) return 167;
	if (!strcmp("l_index3_flexion", name)) return 168;
	if (!strcmp("r_index3_flexion", name)) return 169;
	if (!strcmp("l_thumb1_flexion", name)) return 170;
	if (!strcmp("r_thumb1_flexion", name)) return 171;
	if (!strcmp("l_thumb1_pivot", name)) return 172;
	if (!strcmp("r_thumb1_pivot", name)) return 173;
	if (!strcmp("l_thumb1_twisting", name)) return 174;
	if (!strcmp("r_thumb1_twisting", name)) return 175;
	if (!strcmp("l_thumb2_flexion", name)) return 176;
	if (!strcmp("r_thumb2_flexion", name)) return 177;
	if (!strcmp("l_thumb3_flexion", name)) return 178;
	if (!strcmp("r_thumb3_flexion", name)) return 179;
	if (!strcmp("HumanoidRoot_tr_vertical", name)) return 180;
	if (!strcmp("HumanoidRoot_tr_lateral", name)) return 181;
	if (!strcmp("HumanoidRoot_tr_frontal", name)) return 182;
	if (!strcmp("HumanoidRoot_rt_body_turn", name)) return 183;
	if (!strcmp("HumanoidRoot_rt_body_roll", name)) return 184;
	if (!strcmp("HumanoidRoot_rt_body_tilt", name)) return 185;
	if (!strcmp("extensionBap187", name)) return 186;
	if (!strcmp("extensionBap188", name)) return 187;
	if (!strcmp("extensionBap189", name)) return 188;
	if (!strcmp("extensionBap190", name)) return 189;
	if (!strcmp("extensionBap191", name)) return 190;
	if (!strcmp("extensionBap192", name)) return 191;
	if (!strcmp("extensionBap193", name)) return 192;
	if (!strcmp("extensionBap194", name)) return 193;
	if (!strcmp("extensionBap195", name)) return 194;
	if (!strcmp("extensionBap196", name)) return 195;
	if (!strcmp("extensionBap197", name)) return 196;
	if (!strcmp("extensionBap198", name)) return 197;
	if (!strcmp("extensionBap199", name)) return 198;
	if (!strcmp("extensionBap200", name)) return 199;
	if (!strcmp("extensionBap201", name)) return 200;
	if (!strcmp("extensionBap202", name)) return 201;
	if (!strcmp("extensionBap203", name)) return 202;
	if (!strcmp("extensionBap204", name)) return 203;
	if (!strcmp("extensionBap205", name)) return 204;
	if (!strcmp("extensionBap206", name)) return 205;
	if (!strcmp("extensionBap207", name)) return 206;
	if (!strcmp("extensionBap208", name)) return 207;
	if (!strcmp("extensionBap209", name)) return 208;
	if (!strcmp("extensionBap210", name)) return 209;
	if (!strcmp("extensionBap211", name)) return 210;
	if (!strcmp("extensionBap212", name)) return 211;
	if (!strcmp("extensionBap213", name)) return 212;
	if (!strcmp("extensionBap214", name)) return 213;
	if (!strcmp("extensionBap215", name)) return 214;
	if (!strcmp("extensionBap216", name)) return 215;
	if (!strcmp("extensionBap217", name)) return 216;
	if (!strcmp("extensionBap218", name)) return 217;
	if (!strcmp("extensionBap219", name)) return 218;
	if (!strcmp("extensionBap220", name)) return 219;
	if (!strcmp("extensionBap221", name)) return 220;
	if (!strcmp("extensionBap222", name)) return 221;
	if (!strcmp("extensionBap223", name)) return 222;
	if (!strcmp("extensionBap224", name)) return 223;
	if (!strcmp("extensionBap225", name)) return 224;
	if (!strcmp("extensionBap226", name)) return 225;
	if (!strcmp("extensionBap227", name)) return 226;
	if (!strcmp("extensionBap228", name)) return 227;
	if (!strcmp("extensionBap229", name)) return 228;
	if (!strcmp("extensionBap230", name)) return 229;
	if (!strcmp("extensionBap231", name)) return 230;
	if (!strcmp("extensionBap232", name)) return 231;
	if (!strcmp("extensionBap233", name)) return 232;
	if (!strcmp("extensionBap234", name)) return 233;
	if (!strcmp("extensionBap235", name)) return 234;
	if (!strcmp("extensionBap236", name)) return 235;
	if (!strcmp("extensionBap237", name)) return 236;
	if (!strcmp("extensionBap238", name)) return 237;
	if (!strcmp("extensionBap239", name)) return 238;
	if (!strcmp("extensionBap240", name)) return 239;
	if (!strcmp("extensionBap241", name)) return 240;
	if (!strcmp("extensionBap242", name)) return 241;
	if (!strcmp("extensionBap243", name)) return 242;
	if (!strcmp("extensionBap244", name)) return 243;
	if (!strcmp("extensionBap245", name)) return 244;
	if (!strcmp("extensionBap246", name)) return 245;
	if (!strcmp("extensionBap247", name)) return 246;
	if (!strcmp("extensionBap248", name)) return 247;
	if (!strcmp("extensionBap249", name)) return 248;
	if (!strcmp("extensionBap250", name)) return 249;
	if (!strcmp("extensionBap251", name)) return 250;
	if (!strcmp("extensionBap252", name)) return 251;
	if (!strcmp("extensionBap253", name)) return 252;
	if (!strcmp("extensionBap254", name)) return 253;
	if (!strcmp("extensionBap255", name)) return 254;
	if (!strcmp("extensionBap256", name)) return 255;
	if (!strcmp("extensionBap257", name)) return 256;
	if (!strcmp("extensionBap258", name)) return 257;
	if (!strcmp("extensionBap259", name)) return 258;
	if (!strcmp("extensionBap260", name)) return 259;
	if (!strcmp("extensionBap261", name)) return 260;
	if (!strcmp("extensionBap262", name)) return 261;
	if (!strcmp("extensionBap263", name)) return 262;
	if (!strcmp("extensionBap264", name)) return 263;
	if (!strcmp("extensionBap265", name)) return 264;
	if (!strcmp("extensionBap266", name)) return 265;
	if (!strcmp("extensionBap267", name)) return 266;
	if (!strcmp("extensionBap268", name)) return 267;
	if (!strcmp("extensionBap269", name)) return 268;
	if (!strcmp("extensionBap270", name)) return 269;
	if (!strcmp("extensionBap271", name)) return 270;
	if (!strcmp("extensionBap272", name)) return 271;
	if (!strcmp("extensionBap273", name)) return 272;
	if (!strcmp("extensionBap274", name)) return 273;
	if (!strcmp("extensionBap275", name)) return 274;
	if (!strcmp("extensionBap276", name)) return 275;
	if (!strcmp("extensionBap277", name)) return 276;
	if (!strcmp("extensionBap278", name)) return 277;
	if (!strcmp("extensionBap279", name)) return 278;
	if (!strcmp("extensionBap280", name)) return 279;
	if (!strcmp("extensionBap281", name)) return 280;
	if (!strcmp("extensionBap282", name)) return 281;
	if (!strcmp("extensionBap283", name)) return 282;
	if (!strcmp("extensionBap284", name)) return 283;
	if (!strcmp("extensionBap285", name)) return 284;
	if (!strcmp("extensionBap286", name)) return 285;
	if (!strcmp("extensionBap287", name)) return 286;
	if (!strcmp("extensionBap288", name)) return 287;
	if (!strcmp("extensionBap289", name)) return 288;
	if (!strcmp("extensionBap290", name)) return 289;
	if (!strcmp("extensionBap291", name)) return 290;
	if (!strcmp("extensionBap292", name)) return 291;
	if (!strcmp("extensionBap293", name)) return 292;
	if (!strcmp("extensionBap294", name)) return 293;
	if (!strcmp("extensionBap295", name)) return 294;
	if (!strcmp("extensionBap296", name)) return 295;
	return -1;
	}
static Bool BAP_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 1:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 2:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 3:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 4:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 5:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 6:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 7:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 8:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 9:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 10:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 11:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 12:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 13:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 14:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 15:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 16:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 17:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 18:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 19:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 20:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 21:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 22:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 23:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 24:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 25:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 26:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 27:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 28:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 29:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 30:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 31:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 32:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 33:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 34:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 35:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 36:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 37:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 38:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 39:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 40:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 41:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 42:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 43:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 44:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 45:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 46:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 47:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 48:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 49:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 50:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 51:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 52:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 53:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 54:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 55:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 56:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 57:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 58:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 59:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 60:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 61:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 62:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 63:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 64:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 65:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 66:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 67:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 68:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 69:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 70:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 71:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 72:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 73:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 74:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 75:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 76:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 77:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 78:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 79:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 80:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 81:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 82:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 83:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 84:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 85:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 86:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 87:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 88:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 89:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 90:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 91:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 92:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 93:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 94:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 95:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 96:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 97:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 98:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 99:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 100:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 101:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 102:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 103:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 104:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 105:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 106:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 107:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 108:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 109:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 110:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 111:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 112:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 113:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 114:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 115:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 116:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 117:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 118:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 119:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 120:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 121:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 122:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 123:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 124:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 125:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 126:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 127:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 128:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 129:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 130:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 131:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 132:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 133:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 134:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 135:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 136:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 137:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 138:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 139:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 140:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 141:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 142:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 143:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 144:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 145:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 146:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 147:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 148:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 149:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 150:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 151:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 152:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 153:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 154:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 155:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 156:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 157:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 158:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 159:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 160:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 161:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 162:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 163:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 164:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 165:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 166:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 167:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 168:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 169:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 170:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 171:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 172:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 173:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 174:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 175:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 176:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 177:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 178:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 179:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 180:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 181:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 182:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 183:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 184:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 185:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 186:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 187:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 188:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 189:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 190:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 191:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 192:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 193:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 194:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 195:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 196:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 197:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 198:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 199:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 200:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 201:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 202:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 203:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 204:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 205:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 206:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 207:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 208:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 209:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 210:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 211:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 212:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 213:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 214:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 215:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 216:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 217:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 218:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 219:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 220:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 221:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 222:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 223:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 224:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 225:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 226:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 227:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 228:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 229:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 230:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 231:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 232:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 233:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 234:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 235:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 236:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 237:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 238:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 239:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 240:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 241:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 242:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 243:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 244:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 245:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 246:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 247:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 248:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 249:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 250:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 251:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 252:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 253:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 254:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 255:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 256:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 257:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 258:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 259:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 260:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 261:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 262:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 263:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 264:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 265:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 266:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 267:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 268:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 269:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 270:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 271:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 272:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 273:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 274:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 275:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 276:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 277:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 278:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 279:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 280:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 281:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 282:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 283:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 284:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 285:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 286:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 287:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 288:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 289:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 290:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 291:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 292:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 293:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 294:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 295:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *BAP_Create()
{
	M_BAP *p;
	GF_SAFEALLOC(p, M_BAP);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_BAP);

	/*default field values*/
	p->sacroiliac_tilt = 2 << 31;
	p->sacroiliac_torsion = 2 << 31;
	p->sacroiliac_roll = 2 << 31;
	p->l_hip_flexion = 2 << 31;
	p->r_hip_flexion = 2 << 31;
	p->l_hip_abduct = 2 << 31;
	p->r_hip_abduct = 2 << 31;
	p->l_hip_twisting = 2 << 31;
	p->r_hip_twisting = 2 << 31;
	p->l_knee_flexion = 2 << 31;
	p->r_knee_flexion = 2 << 31;
	p->l_knee_twisting = 2 << 31;
	p->r_knee_twisting = 2 << 31;
	p->l_ankle_flexion = 2 << 31;
	p->r_ankle_flexion = 2 << 31;
	p->l_ankle_twisting = 2 << 31;
	p->r_ankle_twisting = 2 << 31;
	p->l_subtalar_flexion = 2 << 31;
	p->r_subtalar_flexion = 2 << 31;
	p->l_midtarsal_flexion = 2 << 31;
	p->r_midtarsal_flexion = 2 << 31;
	p->l_metatarsal_flexion = 2 << 31;
	p->r_metatarsal_flexion = 2 << 31;
	p->l_sternoclavicular_abduct = 2 << 31;
	p->r_sternoclavicular_abduct = 2 << 31;
	p->l_sternoclavicular_rotate = 2 << 31;
	p->r_sternoclavicular_rotate = 2 << 31;
	p->l_acromioclavicular_abduct = 2 << 31;
	p->r_acromioclavicular_abduct = 2 << 31;
	p->l_acromioclavicular_rotate = 2 << 31;
	p->r_acromioclavicular_rotate = 2 << 31;
	p->l_shoulder_flexion = 2 << 31;
	p->r_shoulder_flexion = 2 << 31;
	p->l_shoulder_abduct = 2 << 31;
	p->r_shoulder_abduct = 2 << 31;
	p->l_shoulder_twisting = 2 << 31;
	p->r_shoulder_twisting = 2 << 31;
	p->l_elbow_flexion = 2 << 31;
	p->r_elbow_flexion = 2 << 31;
	p->l_elbow_twisting = 2 << 31;
	p->r_elbow_twisting = 2 << 31;
	p->l_wrist_flexion = 2 << 31;
	p->r_wrist_flexion = 2 << 31;
	p->l_wrist_pivot = 2 << 31;
	p->r_wrist_pivot = 2 << 31;
	p->l_wrist_twisting = 2 << 31;
	p->r_wrist_twisting = 2 << 31;
	p->skullbase_roll = 2 << 31;
	p->skullbase_torsion = 2 << 31;
	p->skullbase_tilt = 2 << 31;
	p->vc1roll = 2 << 31;
	p->vc1torsion = 2 << 31;
	p->vc1tilt = 2 << 31;
	p->vc2roll = 2 << 31;
	p->vc2torsion = 2 << 31;
	p->vc2tilt = 2 << 31;
	p->vc3roll = 2 << 31;
	p->vc3torsion = 2 << 31;
	p->vc3tilt = 2 << 31;
	p->vc4roll = 2 << 31;
	p->vc4torsion = 2 << 31;
	p->vc4tilt = 2 << 31;
	p->vc5roll = 2 << 31;
	p->vc5torsion = 2 << 31;
	p->vc5tilt = 2 << 31;
	p->vc6roll = 2 << 31;
	p->vc6torsion = 2 << 31;
	p->vc6tilt = 2 << 31;
	p->vc7roll = 2 << 31;
	p->vc7torsion = 2 << 31;
	p->vc7tilt = 2 << 31;
	p->vt1roll = 2 << 31;
	p->vt1torsion = 2 << 31;
	p->vt1tilt = 2 << 31;
	p->vt2roll = 2 << 31;
	p->vt2torsion = 2 << 31;
	p->vt2tilt = 2 << 31;
	p->vt3roll = 2 << 31;
	p->vt3torsion = 2 << 31;
	p->vt3tilt = 2 << 31;
	p->vt4roll = 2 << 31;
	p->vt4torsion = 2 << 31;
	p->vt4tilt = 2 << 31;
	p->vt5roll = 2 << 31;
	p->vt5torsion = 2 << 31;
	p->vt5tilt = 2 << 31;
	p->vt6roll = 2 << 31;
	p->vt6torsion = 2 << 31;
	p->vt6tilt = 2 << 31;
	p->vt7roll = 2 << 31;
	p->vt7torsion = 2 << 31;
	p->vt7tilt = 2 << 31;
	p->vt8roll = 2 << 31;
	p->vt8torsion = 2 << 31;
	p->vt8tilt = 2 << 31;
	p->vt9roll = 2 << 31;
	p->vt9torsion = 2 << 31;
	p->vt9tilt = 2 << 31;
	p->vt10roll = 2 << 31;
	p->vt10torsion = 2 << 31;
	p->vt10tilt = 2 << 31;
	p->vt11roll = 2 << 31;
	p->vt11torsion = 2 << 31;
	p->vt11tilt = 2 << 31;
	p->vt12roll = 2 << 31;
	p->vt12torsion = 2 << 31;
	p->vt12tilt = 2 << 31;
	p->vl1roll = 2 << 31;
	p->vl1torsion = 2 << 31;
	p->vl1tilt = 2 << 31;
	p->vl2roll = 2 << 31;
	p->vl2torsion = 2 << 31;
	p->vl2tilt = 2 << 31;
	p->vl3roll = 2 << 31;
	p->vl3torsion = 2 << 31;
	p->vl3tilt = 2 << 31;
	p->vl4roll = 2 << 31;
	p->vl4torsion = 2 << 31;
	p->vl4tilt = 2 << 31;
	p->vl5roll = 2 << 31;
	p->vl5torsion = 2 << 31;
	p->vl5tilt = 2 << 31;
	p->l_pinky0_flexion = 2 << 31;
	p->r_pinky0_flexion = 2 << 31;
	p->l_pinky1_flexion = 2 << 31;
	p->r_pinky1_flexion = 2 << 31;
	p->l_pinky1_pivot = 2 << 31;
	p->r_pinky1_pivot = 2 << 31;
	p->l_pinky1_twisting = 2 << 31;
	p->r_pinky1_twisting = 2 << 31;
	p->l_pinky2_flexion = 2 << 31;
	p->r_pinky2_flexion = 2 << 31;
	p->l_pinky3_flexion = 2 << 31;
	p->r_pinky3_flexion = 2 << 31;
	p->l_ring0_flexion = 2 << 31;
	p->r_ring0_flexion = 2 << 31;
	p->l_ring1_flexion = 2 << 31;
	p->r_ring1_flexion = 2 << 31;
	p->l_ring1_pivot = 2 << 31;
	p->r_ring1_pivot = 2 << 31;
	p->l_ring1_twisting = 2 << 31;
	p->r_ring1_twisting = 2 << 31;
	p->l_ring2_flexion = 2 << 31;
	p->r_ring2_flexion = 2 << 31;
	p->l_ring3_flexion = 2 << 31;
	p->r_ring3_flexion = 2 << 31;
	p->l_middle0_flexion = 2 << 31;
	p->r_middle0_flexion = 2 << 31;
	p->l_middle1_flexion = 2 << 31;
	p->r_middle1_flexion = 2 << 31;
	p->l_middle1_pivot = 2 << 31;
	p->r_middle1_pivot = 2 << 31;
	p->l_middle1_twisting = 2 << 31;
	p->r_middle1_twisting = 2 << 31;
	p->l_middle2_flexion = 2 << 31;
	p->r_middle2_flexion = 2 << 31;
	p->l_middle3_flexion = 2 << 31;
	p->r_middle3_flexion = 2 << 31;
	p->l_index0_flexion = 2 << 31;
	p->r_index0_flexion = 2 << 31;
	p->l_index1_flexion = 2 << 31;
	p->r_index1_flexion = 2 << 31;
	p->l_index1_pivot = 2 << 31;
	p->r_index1_pivot = 2 << 31;
	p->l_index1_twisting = 2 << 31;
	p->r_index1_twisting = 2 << 31;
	p->l_index2_flexion = 2 << 31;
	p->r_index2_flexion = 2 << 31;
	p->l_index3_flexion = 2 << 31;
	p->r_index3_flexion = 2 << 31;
	p->l_thumb1_flexion = 2 << 31;
	p->r_thumb1_flexion = 2 << 31;
	p->l_thumb1_pivot = 2 << 31;
	p->r_thumb1_pivot = 2 << 31;
	p->l_thumb1_twisting = 2 << 31;
	p->r_thumb1_twisting = 2 << 31;
	p->l_thumb2_flexion = 2 << 31;
	p->r_thumb2_flexion = 2 << 31;
	p->l_thumb3_flexion = 2 << 31;
	p->r_thumb3_flexion = 2 << 31;
	p->HumanoidRoot_tr_vertical = 2 << 31;
	p->HumanoidRoot_tr_lateral = 2 << 31;
	p->HumanoidRoot_tr_frontal = 2 << 31;
	p->HumanoidRoot_rt_body_turn = 2 << 31;
	p->HumanoidRoot_rt_body_roll = 2 << 31;
	p->HumanoidRoot_rt_body_tilt = 2 << 31;
	p->extensionBap187 = 2 << 31;
	p->extensionBap188 = 2 << 31;
	p->extensionBap189 = 2 << 31;
	p->extensionBap190 = 2 << 31;
	p->extensionBap191 = 2 << 31;
	p->extensionBap192 = 2 << 31;
	p->extensionBap193 = 2 << 31;
	p->extensionBap194 = 2 << 31;
	p->extensionBap195 = 2 << 31;
	p->extensionBap196 = 2 << 31;
	p->extensionBap197 = 2 << 31;
	p->extensionBap198 = 2 << 31;
	p->extensionBap199 = 2 << 31;
	p->extensionBap200 = 2 << 31;
	p->extensionBap201 = 2 << 31;
	p->extensionBap202 = 2 << 31;
	p->extensionBap203 = 2 << 31;
	p->extensionBap204 = 2 << 31;
	p->extensionBap205 = 2 << 31;
	p->extensionBap206 = 2 << 31;
	p->extensionBap207 = 2 << 31;
	p->extensionBap208 = 2 << 31;
	p->extensionBap209 = 2 << 31;
	p->extensionBap210 = 2 << 31;
	p->extensionBap211 = 2 << 31;
	p->extensionBap212 = 2 << 31;
	p->extensionBap213 = 2 << 31;
	p->extensionBap214 = 2 << 31;
	p->extensionBap215 = 2 << 31;
	p->extensionBap216 = 2 << 31;
	p->extensionBap217 = 2 << 31;
	p->extensionBap218 = 2 << 31;
	p->extensionBap219 = 2 << 31;
	p->extensionBap220 = 2 << 31;
	p->extensionBap221 = 2 << 31;
	p->extensionBap222 = 2 << 31;
	p->extensionBap223 = 2 << 31;
	p->extensionBap224 = 2 << 31;
	p->extensionBap225 = 2 << 31;
	p->extensionBap226 = 2 << 31;
	p->extensionBap227 = 2 << 31;
	p->extensionBap228 = 2 << 31;
	p->extensionBap229 = 2 << 31;
	p->extensionBap230 = 2 << 31;
	p->extensionBap231 = 2 << 31;
	p->extensionBap232 = 2 << 31;
	p->extensionBap233 = 2 << 31;
	p->extensionBap234 = 2 << 31;
	p->extensionBap235 = 2 << 31;
	p->extensionBap236 = 2 << 31;
	p->extensionBap237 = 2 << 31;
	p->extensionBap238 = 2 << 31;
	p->extensionBap239 = 2 << 31;
	p->extensionBap240 = 2 << 31;
	p->extensionBap241 = 2 << 31;
	p->extensionBap242 = 2 << 31;
	p->extensionBap243 = 2 << 31;
	p->extensionBap244 = 2 << 31;
	p->extensionBap245 = 2 << 31;
	p->extensionBap246 = 2 << 31;
	p->extensionBap247 = 2 << 31;
	p->extensionBap248 = 2 << 31;
	p->extensionBap249 = 2 << 31;
	p->extensionBap250 = 2 << 31;
	p->extensionBap251 = 2 << 31;
	p->extensionBap252 = 2 << 31;
	p->extensionBap253 = 2 << 31;
	p->extensionBap254 = 2 << 31;
	p->extensionBap255 = 2 << 31;
	p->extensionBap256 = 2 << 31;
	p->extensionBap257 = 2 << 31;
	p->extensionBap258 = 2 << 31;
	p->extensionBap259 = 2 << 31;
	p->extensionBap260 = 2 << 31;
	p->extensionBap261 = 2 << 31;
	p->extensionBap262 = 2 << 31;
	p->extensionBap263 = 2 << 31;
	p->extensionBap264 = 2 << 31;
	p->extensionBap265 = 2 << 31;
	p->extensionBap266 = 2 << 31;
	p->extensionBap267 = 2 << 31;
	p->extensionBap268 = 2 << 31;
	p->extensionBap269 = 2 << 31;
	p->extensionBap270 = 2 << 31;
	p->extensionBap271 = 2 << 31;
	p->extensionBap272 = 2 << 31;
	p->extensionBap273 = 2 << 31;
	p->extensionBap274 = 2 << 31;
	p->extensionBap275 = 2 << 31;
	p->extensionBap276 = 2 << 31;
	p->extensionBap277 = 2 << 31;
	p->extensionBap278 = 2 << 31;
	p->extensionBap279 = 2 << 31;
	p->extensionBap280 = 2 << 31;
	p->extensionBap281 = 2 << 31;
	p->extensionBap282 = 2 << 31;
	p->extensionBap283 = 2 << 31;
	p->extensionBap284 = 2 << 31;
	p->extensionBap285 = 2 << 31;
	p->extensionBap286 = 2 << 31;
	p->extensionBap287 = 2 << 31;
	p->extensionBap288 = 2 << 31;
	p->extensionBap289 = 2 << 31;
	p->extensionBap290 = 2 << 31;
	p->extensionBap291 = 2 << 31;
	p->extensionBap292 = 2 << 31;
	p->extensionBap293 = 2 << 31;
	p->extensionBap294 = 2 << 31;
	p->extensionBap295 = 2 << 31;
	p->extensionBap296 = 2 << 31;
	return (GF_Node *)p;
}


/*
	BDP Node deletion
*/

static void BDP_Del(GF_Node *node)
{
	M_BDP *p = (M_BDP *) node;
	gf_node_unregister_children((GF_Node *) p, p->bodyDefTables);	
	gf_node_unregister_children((GF_Node *) p, p->bodySceneGraph);	
	gf_node_free((GF_Node *) p);
}

static const u16 BDP_Def2All[] = { 0, 1};
static const u16 BDP_In2All[] = { 0, 1};
static const u16 BDP_Out2All[] = { 0, 1};

static u32 BDP_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 2;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 2;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 2;
	}
}

static GF_Err BDP_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = BDP_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = BDP_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = BDP_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err BDP_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "bodyDefTables";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFBodyDefTableNode;
		info->far_ptr = & ((M_BDP *)node)->bodyDefTables;
		return GF_OK;
	case 1:
		info->name = "bodySceneGraph";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_BDP *)node)->bodySceneGraph;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 BDP_get_field_index_by_name(char *name)
{
	if (!strcmp("bodyDefTables", name)) return 0;
	if (!strcmp("bodySceneGraph", name)) return 1;
	return -1;
	}
static Bool BDP_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *BDP_Create()
{
	M_BDP *p;
	GF_SAFEALLOC(p, M_BDP);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_BDP);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	Body Node deletion
*/

static void Body_Del(GF_Node *node)
{
	M_Body *p = (M_Body *) node;
	gf_node_unregister((GF_Node *) p->bdp, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->bap, (GF_Node *) p);	
	gf_node_unregister_children((GF_Node *) p, p->renderedBody);	
	gf_node_free((GF_Node *) p);
}

static const u16 Body_Def2All[] = { 0, 1, 2};
static const u16 Body_In2All[] = { 0, 1, 2};
static const u16 Body_Out2All[] = { 0, 1, 2};

static u32 Body_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 3;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 3;
	}
}

static GF_Err Body_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Body_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Body_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Body_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Body_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "bdp";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFBDPNode;
		info->far_ptr = & ((M_Body *)node)->bdp;
		return GF_OK;
	case 1:
		info->name = "bap";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFBAPNode;
		info->far_ptr = & ((M_Body *)node)->bap;
		return GF_OK;
	case 2:
		info->name = "renderedBody";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_Body *)node)->renderedBody;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Body_get_field_index_by_name(char *name)
{
	if (!strcmp("bdp", name)) return 0;
	if (!strcmp("bap", name)) return 1;
	if (!strcmp("renderedBody", name)) return 2;
	return -1;
	}
static Bool Body_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *Body_Create()
{
	M_Body *p;
	GF_SAFEALLOC(p, M_Body);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Body);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	BodyDefTable Node deletion
*/

static void BodyDefTable_Del(GF_Node *node)
{
	M_BodyDefTable *p = (M_BodyDefTable *) node;
	gf_sg_sfstring_del(p->bodySceneGraphNodeName);
	gf_sg_mfint32_del(p->bapIDs);
	gf_sg_mfint32_del(p->vertexIds);
	gf_sg_mfint32_del(p->bapCombinations);
	gf_sg_mfvec3f_del(p->displacements);
	gf_node_free((GF_Node *) p);
}

static const u16 BodyDefTable_Def2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 BodyDefTable_In2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 BodyDefTable_Out2All[] = { 0, 1, 2, 3, 4, 5};

static u32 BodyDefTable_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 6;
	case GF_SG_FIELD_CODING_DEF: return 6;
	case GF_SG_FIELD_CODING_OUT: return 6;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 6;
	}
}

static GF_Err BodyDefTable_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = BodyDefTable_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = BodyDefTable_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = BodyDefTable_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err BodyDefTable_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "bodySceneGraphNodeName";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_BodyDefTable *) node)->bodySceneGraphNodeName;
		return GF_OK;
	case 1:
		info->name = "bapIDs";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_BodyDefTable *) node)->bapIDs;
		return GF_OK;
	case 2:
		info->name = "vertexIds";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_BodyDefTable *) node)->vertexIds;
		return GF_OK;
	case 3:
		info->name = "bapCombinations";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_BodyDefTable *) node)->bapCombinations;
		return GF_OK;
	case 4:
		info->name = "displacements";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC3F;
		info->far_ptr = & ((M_BodyDefTable *) node)->displacements;
		return GF_OK;
	case 5:
		info->name = "numInterpolateKeys";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BodyDefTable *) node)->numInterpolateKeys;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 BodyDefTable_get_field_index_by_name(char *name)
{
	if (!strcmp("bodySceneGraphNodeName", name)) return 0;
	if (!strcmp("bapIDs", name)) return 1;
	if (!strcmp("vertexIds", name)) return 2;
	if (!strcmp("bapCombinations", name)) return 3;
	if (!strcmp("displacements", name)) return 4;
	if (!strcmp("numInterpolateKeys", name)) return 5;
	return -1;
	}
static Bool BodyDefTable_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 9;
		*b_min = FLT2FIX(1);
		*b_max = FLT2FIX(296);
		return 1;
	case 2:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 3:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 5:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(2);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *BodyDefTable_Create()
{
	M_BodyDefTable *p;
	GF_SAFEALLOC(p, M_BodyDefTable);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_BodyDefTable);

	/*default field values*/
	p->numInterpolateKeys = 2;
	return (GF_Node *)p;
}


/*
	BodySegmentConnectionHint Node deletion
*/

static void BodySegmentConnectionHint_Del(GF_Node *node)
{
	M_BodySegmentConnectionHint *p = (M_BodySegmentConnectionHint *) node;
	gf_sg_sfstring_del(p->firstSegmentNodeName);
	gf_sg_sfstring_del(p->secondSegmentNodeName);
	gf_sg_mfint32_del(p->firstVertexIdList);
	gf_sg_mfint32_del(p->secondVertexIdList);
	gf_node_free((GF_Node *) p);
}

static const u16 BodySegmentConnectionHint_Def2All[] = { 0, 1, 2, 3};
static const u16 BodySegmentConnectionHint_In2All[] = { 0, 1, 2, 3};
static const u16 BodySegmentConnectionHint_Out2All[] = { 0, 1, 2, 3};

static u32 BodySegmentConnectionHint_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 4;
	case GF_SG_FIELD_CODING_OUT: return 4;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err BodySegmentConnectionHint_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = BodySegmentConnectionHint_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = BodySegmentConnectionHint_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = BodySegmentConnectionHint_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err BodySegmentConnectionHint_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "firstSegmentNodeName";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_BodySegmentConnectionHint *) node)->firstSegmentNodeName;
		return GF_OK;
	case 1:
		info->name = "secondSegmentNodeName";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_BodySegmentConnectionHint *) node)->secondSegmentNodeName;
		return GF_OK;
	case 2:
		info->name = "firstVertexIdList";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_BodySegmentConnectionHint *) node)->firstVertexIdList;
		return GF_OK;
	case 3:
		info->name = "secondVertexIdList";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_BodySegmentConnectionHint *) node)->secondVertexIdList;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 BodySegmentConnectionHint_get_field_index_by_name(char *name)
{
	if (!strcmp("firstSegmentNodeName", name)) return 0;
	if (!strcmp("secondSegmentNodeName", name)) return 1;
	if (!strcmp("firstVertexIdList", name)) return 2;
	if (!strcmp("secondVertexIdList", name)) return 3;
	return -1;
	}
static Bool BodySegmentConnectionHint_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 2:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 3:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *BodySegmentConnectionHint_Create()
{
	M_BodySegmentConnectionHint *p;
	GF_SAFEALLOC(p, M_BodySegmentConnectionHint);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_BodySegmentConnectionHint);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	DirectiveSound Node deletion
*/

static void DirectiveSound_Del(GF_Node *node)
{
	M_DirectiveSound *p = (M_DirectiveSound *) node;
	gf_node_unregister((GF_Node *) p->source, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->perceptualParameters, (GF_Node *) p);	
	gf_sg_mffloat_del(p->directivity);
	gf_sg_mffloat_del(p->angles);
	gf_sg_mffloat_del(p->frequency);
	gf_node_free((GF_Node *) p);
}

static const u16 DirectiveSound_Def2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
static const u16 DirectiveSound_In2All[] = { 0, 1, 2, 3, 4, 5, 6};
static const u16 DirectiveSound_Out2All[] = { 0, 1, 2, 3, 4, 5, 6};
static const u16 DirectiveSound_Dyn2All[] = { 0, 1, 2};

static u32 DirectiveSound_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 7;
	case GF_SG_FIELD_CODING_DEF: return 13;
	case GF_SG_FIELD_CODING_OUT: return 7;
	case GF_SG_FIELD_CODING_DYN: return 3;
	default:
		return 13;
	}
}

static GF_Err DirectiveSound_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = DirectiveSound_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = DirectiveSound_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = DirectiveSound_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = DirectiveSound_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err DirectiveSound_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "direction";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_DirectiveSound *) node)->direction;
		return GF_OK;
	case 1:
		info->name = "intensity";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_DirectiveSound *) node)->intensity;
		return GF_OK;
	case 2:
		info->name = "location";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_DirectiveSound *) node)->location;
		return GF_OK;
	case 3:
		info->name = "source";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFAudioNode;
		info->far_ptr = & ((M_DirectiveSound *)node)->source;
		return GF_OK;
	case 4:
		info->name = "perceptualParameters";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFPerceptualParameterNode;
		info->far_ptr = & ((M_DirectiveSound *)node)->perceptualParameters;
		return GF_OK;
	case 5:
		info->name = "roomEffect";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_DirectiveSound *) node)->roomEffect;
		return GF_OK;
	case 6:
		info->name = "spatialize";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_DirectiveSound *) node)->spatialize;
		return GF_OK;
	case 7:
		info->name = "directivity";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_DirectiveSound *) node)->directivity;
		return GF_OK;
	case 8:
		info->name = "angles";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_DirectiveSound *) node)->angles;
		return GF_OK;
	case 9:
		info->name = "frequency";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_DirectiveSound *) node)->frequency;
		return GF_OK;
	case 10:
		info->name = "speedOfSound";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_DirectiveSound *) node)->speedOfSound;
		return GF_OK;
	case 11:
		info->name = "distance";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_DirectiveSound *) node)->distance;
		return GF_OK;
	case 12:
		info->name = "useAirabs";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_DirectiveSound *) node)->useAirabs;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 DirectiveSound_get_field_index_by_name(char *name)
{
	if (!strcmp("direction", name)) return 0;
	if (!strcmp("intensity", name)) return 1;
	if (!strcmp("location", name)) return 2;
	if (!strcmp("source", name)) return 3;
	if (!strcmp("perceptualParameters", name)) return 4;
	if (!strcmp("roomEffect", name)) return 5;
	if (!strcmp("spatialize", name)) return 6;
	if (!strcmp("directivity", name)) return 7;
	if (!strcmp("angles", name)) return 8;
	if (!strcmp("frequency", name)) return 9;
	if (!strcmp("speedOfSound", name)) return 10;
	if (!strcmp("distance", name)) return 11;
	if (!strcmp("useAirabs", name)) return 12;
	return -1;
	}
static Bool DirectiveSound_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 9;
		*QType = 9;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 1:
		*AType = 7;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 2:
		*AType = 1;
		*QType = 1;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 7:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 8:
		*AType = 0;
		*QType = 6;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(3.14159265);
		return 1;
	case 9:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 10:
		*AType = 0;
		*QType = 1;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 11:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *DirectiveSound_Create()
{
	M_DirectiveSound *p;
	GF_SAFEALLOC(p, M_DirectiveSound);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_DirectiveSound);

	/*default field values*/
	p->direction.x = FLT2FIX(0);
	p->direction.y = FLT2FIX(0);
	p->direction.z = FLT2FIX(-1);
	p->intensity = FLT2FIX(1);
	p->location.x = FLT2FIX(0);
	p->location.y = FLT2FIX(0);
	p->location.z = FLT2FIX(0);
	p->spatialize = 1;
	p->directivity.vals = (SFFloat*)malloc(sizeof(SFFloat)*1);
	p->directivity.count = 1;
	p->directivity.vals[0] = FLT2FIX(1);
	p->angles.vals = (SFFloat*)malloc(sizeof(SFFloat)*1);
	p->angles.count = 1;
	p->angles.vals[0] = FLT2FIX(1);
	p->speedOfSound = FLT2FIX(340);
	p->distance = FLT2FIX(100);
	return (GF_Node *)p;
}


/*
	Hierarchical3DMesh Node deletion
*/

static void Hierarchical3DMesh_Del(GF_Node *node)
{
	M_Hierarchical3DMesh *p = (M_Hierarchical3DMesh *) node;
	gf_sg_mfurl_del(p->url);
	gf_node_free((GF_Node *) p);
}

static const u16 Hierarchical3DMesh_Def2All[] = { 1, 2};
static const u16 Hierarchical3DMesh_In2All[] = { 0, 1};
static const u16 Hierarchical3DMesh_Out2All[] = { 1, 3};

static u32 Hierarchical3DMesh_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 2;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 2;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err Hierarchical3DMesh_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Hierarchical3DMesh_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Hierarchical3DMesh_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Hierarchical3DMesh_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Hierarchical3DMesh_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "triangleBudget";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Hierarchical3DMesh *)node)->on_triangleBudget;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_Hierarchical3DMesh *) node)->triangleBudget;
		return GF_OK;
	case 1:
		info->name = "level";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Hierarchical3DMesh *) node)->level;
		return GF_OK;
	case 2:
		info->name = "url";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_Hierarchical3DMesh *) node)->url;
		return GF_OK;
	case 3:
		info->name = "doneLoading";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Hierarchical3DMesh *) node)->doneLoading;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Hierarchical3DMesh_get_field_index_by_name(char *name)
{
	if (!strcmp("triangleBudget", name)) return 0;
	if (!strcmp("level", name)) return 1;
	if (!strcmp("url", name)) return 2;
	if (!strcmp("doneLoading", name)) return 3;
	return -1;
	}
static Bool Hierarchical3DMesh_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(-1);
		*b_max = FIX_MAX;
		return 1;
	case 1:
		*AType = 0;
		*QType = 0;
		*b_min = FLT2FIX(-1);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Hierarchical3DMesh_Create()
{
	M_Hierarchical3DMesh *p;
	GF_SAFEALLOC(p, M_Hierarchical3DMesh);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Hierarchical3DMesh);

	/*default field values*/
	p->level = FLT2FIX(1);
	return (GF_Node *)p;
}


/*
	MaterialKey Node deletion
*/

static void MaterialKey_Del(GF_Node *node)
{
	M_MaterialKey *p = (M_MaterialKey *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 MaterialKey_Def2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 MaterialKey_In2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 MaterialKey_Out2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 MaterialKey_Dyn2All[] = { 2, 3, 4, 5};

static u32 MaterialKey_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 6;
	case GF_SG_FIELD_CODING_DEF: return 6;
	case GF_SG_FIELD_CODING_OUT: return 6;
	case GF_SG_FIELD_CODING_DYN: return 4;
	default:
		return 6;
	}
}

static GF_Err MaterialKey_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = MaterialKey_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = MaterialKey_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = MaterialKey_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = MaterialKey_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err MaterialKey_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "isKeyed";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_MaterialKey *) node)->isKeyed;
		return GF_OK;
	case 1:
		info->name = "isRGB";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_MaterialKey *) node)->isRGB;
		return GF_OK;
	case 2:
		info->name = "keyColor";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFCOLOR;
		info->far_ptr = & ((M_MaterialKey *) node)->keyColor;
		return GF_OK;
	case 3:
		info->name = "lowThreshold";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_MaterialKey *) node)->lowThreshold;
		return GF_OK;
	case 4:
		info->name = "highThreshold";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_MaterialKey *) node)->highThreshold;
		return GF_OK;
	case 5:
		info->name = "transparency";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_MaterialKey *) node)->transparency;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 MaterialKey_get_field_index_by_name(char *name)
{
	if (!strcmp("isKeyed", name)) return 0;
	if (!strcmp("isRGB", name)) return 1;
	if (!strcmp("keyColor", name)) return 2;
	if (!strcmp("lowThreshold", name)) return 3;
	if (!strcmp("highThreshold", name)) return 4;
	if (!strcmp("transparency", name)) return 5;
	return -1;
	}
static Bool MaterialKey_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 2:
		*AType = 4;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 3:
		*AType = 8;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 4:
		*AType = 8;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 5:
		*AType = 8;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	default:
		return 0;
	}
}



GF_Node *MaterialKey_Create()
{
	M_MaterialKey *p;
	GF_SAFEALLOC(p, M_MaterialKey);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_MaterialKey);

	/*default field values*/
	p->isKeyed = 1;
	p->isRGB = 1;
	p->keyColor.red = FLT2FIX(0);
	p->keyColor.green = FLT2FIX(0);
	p->keyColor.blue = FLT2FIX(0);
	p->lowThreshold = FLT2FIX(0);
	p->highThreshold = FLT2FIX(0);
	p->transparency = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	PerceptualParameters Node deletion
*/

static void PerceptualParameters_Del(GF_Node *node)
{
	M_PerceptualParameters *p = (M_PerceptualParameters *) node;
	gf_sg_mffloat_del(p->omniDirectivity);
	gf_sg_mffloat_del(p->directFilterGains);
	gf_sg_mffloat_del(p->inputFilterGains);
	gf_node_free((GF_Node *) p);
}

static const u16 PerceptualParameters_Def2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
static const u16 PerceptualParameters_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
static const u16 PerceptualParameters_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
static const u16 PerceptualParameters_Dyn2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};

static u32 PerceptualParameters_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 19;
	case GF_SG_FIELD_CODING_DEF: return 19;
	case GF_SG_FIELD_CODING_OUT: return 19;
	case GF_SG_FIELD_CODING_DYN: return 15;
	default:
		return 19;
	}
}

static GF_Err PerceptualParameters_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = PerceptualParameters_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = PerceptualParameters_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = PerceptualParameters_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = PerceptualParameters_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err PerceptualParameters_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "sourcePresence";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_PerceptualParameters *) node)->sourcePresence;
		return GF_OK;
	case 1:
		info->name = "sourceWarmth";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_PerceptualParameters *) node)->sourceWarmth;
		return GF_OK;
	case 2:
		info->name = "sourceBrilliance";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_PerceptualParameters *) node)->sourceBrilliance;
		return GF_OK;
	case 3:
		info->name = "roomPresence";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_PerceptualParameters *) node)->roomPresence;
		return GF_OK;
	case 4:
		info->name = "runningReverberance";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_PerceptualParameters *) node)->runningReverberance;
		return GF_OK;
	case 5:
		info->name = "envelopment";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_PerceptualParameters *) node)->envelopment;
		return GF_OK;
	case 6:
		info->name = "lateReverberance";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_PerceptualParameters *) node)->lateReverberance;
		return GF_OK;
	case 7:
		info->name = "heavyness";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_PerceptualParameters *) node)->heavyness;
		return GF_OK;
	case 8:
		info->name = "liveness";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_PerceptualParameters *) node)->liveness;
		return GF_OK;
	case 9:
		info->name = "omniDirectivity";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_PerceptualParameters *) node)->omniDirectivity;
		return GF_OK;
	case 10:
		info->name = "directFilterGains";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_PerceptualParameters *) node)->directFilterGains;
		return GF_OK;
	case 11:
		info->name = "inputFilterGains";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_PerceptualParameters *) node)->inputFilterGains;
		return GF_OK;
	case 12:
		info->name = "refDistance";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_PerceptualParameters *) node)->refDistance;
		return GF_OK;
	case 13:
		info->name = "freqLow";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_PerceptualParameters *) node)->freqLow;
		return GF_OK;
	case 14:
		info->name = "freqHigh";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_PerceptualParameters *) node)->freqHigh;
		return GF_OK;
	case 15:
		info->name = "timeLimit1";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_PerceptualParameters *) node)->timeLimit1;
		return GF_OK;
	case 16:
		info->name = "timeLimit2";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_PerceptualParameters *) node)->timeLimit2;
		return GF_OK;
	case 17:
		info->name = "timeLimit3";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_PerceptualParameters *) node)->timeLimit3;
		return GF_OK;
	case 18:
		info->name = "modalDensity";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_PerceptualParameters *) node)->modalDensity;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 PerceptualParameters_get_field_index_by_name(char *name)
{
	if (!strcmp("sourcePresence", name)) return 0;
	if (!strcmp("sourceWarmth", name)) return 1;
	if (!strcmp("sourceBrilliance", name)) return 2;
	if (!strcmp("roomPresence", name)) return 3;
	if (!strcmp("runningReverberance", name)) return 4;
	if (!strcmp("envelopment", name)) return 5;
	if (!strcmp("lateReverberance", name)) return 6;
	if (!strcmp("heavyness", name)) return 7;
	if (!strcmp("liveness", name)) return 8;
	if (!strcmp("omniDirectivity", name)) return 9;
	if (!strcmp("directFilterGains", name)) return 10;
	if (!strcmp("inputFilterGains", name)) return 11;
	if (!strcmp("refDistance", name)) return 12;
	if (!strcmp("freqLow", name)) return 13;
	if (!strcmp("freqHigh", name)) return 14;
	if (!strcmp("timeLimit1", name)) return 15;
	if (!strcmp("timeLimit2", name)) return 16;
	if (!strcmp("timeLimit3", name)) return 17;
	if (!strcmp("modalDensity", name)) return 18;
	return -1;
	}
static Bool PerceptualParameters_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 7;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 1:
		*AType = 7;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 2:
		*AType = 7;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 3:
		*AType = 7;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 4:
		*AType = 7;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 5:
		*AType = 7;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 6:
		*AType = 7;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 7:
		*AType = 7;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 8:
		*AType = 7;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 9:
		*AType = 7;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 10:
		*AType = 7;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 11:
		*AType = 7;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 12:
		*AType = 7;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 13:
		*AType = 7;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 14:
		*AType = 7;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 15:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 16:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 17:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 18:
		*AType = 0;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *PerceptualParameters_Create()
{
	M_PerceptualParameters *p;
	GF_SAFEALLOC(p, M_PerceptualParameters);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_PerceptualParameters);

	/*default field values*/
	p->sourcePresence = FLT2FIX(1.0);
	p->sourceWarmth = FLT2FIX(1.0);
	p->sourceBrilliance = FLT2FIX(1.0);
	p->roomPresence = FLT2FIX(1.0);
	p->runningReverberance = FLT2FIX(1.0);
	p->envelopment = FLT2FIX(0.0);
	p->lateReverberance = FLT2FIX(1.0);
	p->heavyness = FLT2FIX(1.0);
	p->liveness = FLT2FIX(1.0);
	p->omniDirectivity.vals = (SFFloat*)malloc(sizeof(SFFloat)*1);
	p->omniDirectivity.count = 1;
	p->omniDirectivity.vals[0] = FLT2FIX(1.0);
	p->directFilterGains.vals = (SFFloat*)malloc(sizeof(SFFloat)*3);
	p->directFilterGains.count = 3;
	p->directFilterGains.vals[0] = FLT2FIX(1.0);
	p->directFilterGains.vals[1] = FLT2FIX(1.0);
	p->directFilterGains.vals[2] = FLT2FIX(1.0);
	p->inputFilterGains.vals = (SFFloat*)malloc(sizeof(SFFloat)*3);
	p->inputFilterGains.count = 3;
	p->inputFilterGains.vals[0] = FLT2FIX(1.0);
	p->inputFilterGains.vals[1] = FLT2FIX(1.0);
	p->inputFilterGains.vals[2] = FLT2FIX(1.0);
	p->refDistance = FLT2FIX(1.0);
	p->freqLow = FLT2FIX(250.0);
	p->freqHigh = FLT2FIX(4000.0);
	p->timeLimit1 = 0.02;
	p->timeLimit2 = 0.04;
	p->timeLimit3 = 0.1;
	p->modalDensity = 0.8;
	return (GF_Node *)p;
}


/*
	TemporalTransform Node deletion
*/

static void TemporalTransform_Del(GF_Node *node)
{
	M_TemporalTransform *p = (M_TemporalTransform *) node;
	gf_sg_mfurl_del(p->url);
	gf_sg_mfint32_del(p->stretchMode);
	gf_sg_mfint32_del(p->shrinkMode);
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 TemporalTransform_Def2All[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
static const u16 TemporalTransform_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
static const u16 TemporalTransform_Out2All[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
static const u16 TemporalTransform_Dyn2All[] = { 7, 8};

static u32 TemporalTransform_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 12;
	case GF_SG_FIELD_CODING_DEF: return 10;
	case GF_SG_FIELD_CODING_OUT: return 11;
	case GF_SG_FIELD_CODING_DYN: return 2;
	default:
		return 13;
	}
}

static GF_Err TemporalTransform_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = TemporalTransform_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = TemporalTransform_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = TemporalTransform_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = TemporalTransform_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err TemporalTransform_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_TemporalTransform *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_TemporalTransform *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_TemporalTransform *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_TemporalTransform *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_TemporalTransform *)node)->children;
		return GF_OK;
	case 3:
		info->name = "url";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_TemporalTransform *) node)->url;
		return GF_OK;
	case 4:
		info->name = "startTime";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_TemporalTransform *) node)->startTime;
		return GF_OK;
	case 5:
		info->name = "optimalDuration";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_TemporalTransform *) node)->optimalDuration;
		return GF_OK;
	case 6:
		info->name = "active";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_TemporalTransform *) node)->active;
		return GF_OK;
	case 7:
		info->name = "speed";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_TemporalTransform *) node)->speed;
		return GF_OK;
	case 8:
		info->name = "scalability";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_TemporalTransform *) node)->scalability;
		return GF_OK;
	case 9:
		info->name = "stretchMode";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_TemporalTransform *) node)->stretchMode;
		return GF_OK;
	case 10:
		info->name = "shrinkMode";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_TemporalTransform *) node)->shrinkMode;
		return GF_OK;
	case 11:
		info->name = "maxDelay";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_TemporalTransform *) node)->maxDelay;
		return GF_OK;
	case 12:
		info->name = "actualDuration";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_TemporalTransform *) node)->actualDuration;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 TemporalTransform_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	if (!strcmp("url", name)) return 3;
	if (!strcmp("startTime", name)) return 4;
	if (!strcmp("optimalDuration", name)) return 5;
	if (!strcmp("active", name)) return 6;
	if (!strcmp("speed", name)) return 7;
	if (!strcmp("scalability", name)) return 8;
	if (!strcmp("stretchMode", name)) return 9;
	if (!strcmp("shrinkMode", name)) return 10;
	if (!strcmp("maxDelay", name)) return 11;
	if (!strcmp("actualDuration", name)) return 12;
	return -1;
	}
static Bool TemporalTransform_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 7:
		*AType = 7;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 8:
		*AType = 12;
		*QType = 12;
		*b_min = FLT2FIX(-1);
		*b_max = FIX_MAX;
		return 1;
	case 9:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 2;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(2);
		return 1;
	case 10:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 1;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	default:
		return 0;
	}
}



GF_Node *TemporalTransform_Create()
{
	M_TemporalTransform *p;
	GF_SAFEALLOC(p, M_TemporalTransform);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_TemporalTransform);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->startTime = -1.0;
	p->optimalDuration = -1.0;
	p->speed = FLT2FIX(1.0);
	p->scalability.x = FLT2FIX(1.0);
	p->scalability.y = FLT2FIX(1.0);
	p->stretchMode.vals = (SFInt32*)malloc(sizeof(SFInt32)*1);
	p->stretchMode.count = 1;
	p->stretchMode.vals[0] = 0;
	p->shrinkMode.vals = (SFInt32*)malloc(sizeof(SFInt32)*1);
	p->shrinkMode.count = 1;
	p->shrinkMode.vals[0] = 0;
	p->maxDelay = 0;
	return (GF_Node *)p;
}


/*
	TemporalGroup Node deletion
*/

static void TemporalGroup_Del(GF_Node *node)
{
	M_TemporalGroup *p = (M_TemporalGroup *) node;
	gf_sg_mffloat_del(p->priority);
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 TemporalGroup_Def2All[] = { 2, 3, 4, 5, 6};
static const u16 TemporalGroup_In2All[] = { 0, 1, 2, 6};
static const u16 TemporalGroup_Out2All[] = { 2, 6, 7, 8};

static u32 TemporalGroup_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 4;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 9;
	}
}

static GF_Err TemporalGroup_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = TemporalGroup_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = TemporalGroup_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = TemporalGroup_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err TemporalGroup_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_TemporalGroup *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFTemporalNode;
		info->far_ptr = & ((M_TemporalGroup *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_TemporalGroup *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFTemporalNode;
		info->far_ptr = & ((M_TemporalGroup *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFTemporalNode;
		info->far_ptr = & ((M_TemporalGroup *)node)->children;
		return GF_OK;
	case 3:
		info->name = "costart";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_TemporalGroup *) node)->costart;
		return GF_OK;
	case 4:
		info->name = "coend";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_TemporalGroup *) node)->coend;
		return GF_OK;
	case 5:
		info->name = "meet";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_TemporalGroup *) node)->meet;
		return GF_OK;
	case 6:
		info->name = "priority";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_TemporalGroup *) node)->priority;
		return GF_OK;
	case 7:
		info->name = "isActive";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_TemporalGroup *) node)->isActive;
		return GF_OK;
	case 8:
		info->name = "activeChild";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_TemporalGroup *) node)->activeChild;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 TemporalGroup_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	if (!strcmp("costart", name)) return 3;
	if (!strcmp("coend", name)) return 4;
	if (!strcmp("meet", name)) return 5;
	if (!strcmp("priority", name)) return 6;
	if (!strcmp("isActive", name)) return 7;
	if (!strcmp("activeChild", name)) return 8;
	return -1;
	}
static Bool TemporalGroup_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 6:
		*AType = 0;
		*QType = 3;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *TemporalGroup_Create()
{
	M_TemporalGroup *p;
	GF_SAFEALLOC(p, M_TemporalGroup);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_TemporalGroup);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->costart = 1;
	return (GF_Node *)p;
}


/*
	ServerCommand Node deletion
*/

static void ServerCommand_Del(GF_Node *node)
{
	M_ServerCommand *p = (M_ServerCommand *) node;
	gf_sg_mfurl_del(p->url);
	gf_sg_sfstring_del(p->command);
	gf_node_free((GF_Node *) p);
}

static const u16 ServerCommand_Def2All[] = { 1, 2, 3};
static const u16 ServerCommand_In2All[] = { 0, 1, 2, 3};
static const u16 ServerCommand_Out2All[] = { 1, 2, 3};

static u32 ServerCommand_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 3;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err ServerCommand_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = ServerCommand_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = ServerCommand_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = ServerCommand_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err ServerCommand_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "trigger";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_ServerCommand *)node)->on_trigger;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_ServerCommand *) node)->trigger;
		return GF_OK;
	case 1:
		info->name = "enable";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_ServerCommand *) node)->enable;
		return GF_OK;
	case 2:
		info->name = "url";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_ServerCommand *) node)->url;
		return GF_OK;
	case 3:
		info->name = "command";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_ServerCommand *) node)->command;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 ServerCommand_get_field_index_by_name(char *name)
{
	if (!strcmp("trigger", name)) return 0;
	if (!strcmp("enable", name)) return 1;
	if (!strcmp("url", name)) return 2;
	if (!strcmp("command", name)) return 3;
	return -1;
	}
static Bool ServerCommand_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *ServerCommand_Create()
{
	M_ServerCommand *p;
	GF_SAFEALLOC(p, M_ServerCommand);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_ServerCommand);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	InputSensor Node deletion
*/

static void InputSensor_Del(GF_Node *node)
{
	M_InputSensor *p = (M_InputSensor *) node;
	gf_sg_sfcommand_del(p->buffer);
	gf_sg_mfurl_del(p->url);
	gf_node_free((GF_Node *) p);
}

static const u16 InputSensor_Def2All[] = { 0, 1, 2};
static const u16 InputSensor_In2All[] = { 0, 1, 2};
static const u16 InputSensor_Out2All[] = { 0, 1, 2, 3};

static u32 InputSensor_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 3;
	case GF_SG_FIELD_CODING_OUT: return 4;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err InputSensor_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = InputSensor_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = InputSensor_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = InputSensor_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err InputSensor_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "enabled";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_InputSensor *) node)->enabled;
		return GF_OK;
	case 1:
		info->name = "buffer";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFCOMMANDBUFFER;
		info->far_ptr = & ((M_InputSensor *) node)->buffer;
		return GF_OK;
	case 2:
		info->name = "url";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_InputSensor *) node)->url;
		return GF_OK;
	case 3:
		info->name = "eventTime";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_InputSensor *) node)->eventTime;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 InputSensor_get_field_index_by_name(char *name)
{
	if (!strcmp("enabled", name)) return 0;
	if (!strcmp("buffer", name)) return 1;
	if (!strcmp("url", name)) return 2;
	if (!strcmp("eventTime", name)) return 3;
	return -1;
	}
static Bool InputSensor_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *InputSensor_Create()
{
	M_InputSensor *p;
	GF_SAFEALLOC(p, M_InputSensor);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_InputSensor);
	p->buffer.commandList = gf_list_new();	

	/*default field values*/
	p->enabled = 1;
	return (GF_Node *)p;
}


/*
	MatteTexture Node deletion
*/

static void MatteTexture_Del(GF_Node *node)
{
	M_MatteTexture *p = (M_MatteTexture *) node;
	gf_node_unregister((GF_Node *) p->surfaceA, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->surfaceB, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->alphaSurface, (GF_Node *) p);	
	gf_sg_sfstring_del(p->operation);
	gf_sg_mffloat_del(p->parameter);
	gf_node_free((GF_Node *) p);
}

static const u16 MatteTexture_Def2All[] = { 0, 1, 2, 3, 4, 5, 6};
static const u16 MatteTexture_In2All[] = { 3, 5, 6};
static const u16 MatteTexture_Out2All[] = { 3, 5, 6};

static u32 MatteTexture_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 7;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 7;
	}
}

static GF_Err MatteTexture_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = MatteTexture_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = MatteTexture_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = MatteTexture_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err MatteTexture_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "surfaceA";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFTextureNode;
		info->far_ptr = & ((M_MatteTexture *)node)->surfaceA;
		return GF_OK;
	case 1:
		info->name = "surfaceB";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFTextureNode;
		info->far_ptr = & ((M_MatteTexture *)node)->surfaceB;
		return GF_OK;
	case 2:
		info->name = "alphaSurface";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFTextureNode;
		info->far_ptr = & ((M_MatteTexture *)node)->alphaSurface;
		return GF_OK;
	case 3:
		info->name = "operation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_MatteTexture *) node)->operation;
		return GF_OK;
	case 4:
		info->name = "overwrite";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_MatteTexture *) node)->overwrite;
		return GF_OK;
	case 5:
		info->name = "fraction";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_MatteTexture *) node)->fraction;
		return GF_OK;
	case 6:
		info->name = "parameter";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_MatteTexture *) node)->parameter;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 MatteTexture_get_field_index_by_name(char *name)
{
	if (!strcmp("surfaceA", name)) return 0;
	if (!strcmp("surfaceB", name)) return 1;
	if (!strcmp("alphaSurface", name)) return 2;
	if (!strcmp("operation", name)) return 3;
	if (!strcmp("overwrite", name)) return 4;
	if (!strcmp("fraction", name)) return 5;
	if (!strcmp("parameter", name)) return 6;
	return -1;
	}
static Bool MatteTexture_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *MatteTexture_Create()
{
	M_MatteTexture *p;
	GF_SAFEALLOC(p, M_MatteTexture);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_MatteTexture);

	/*default field values*/
	p->fraction = FLT2FIX(0);
	p->parameter.vals = (SFFloat*)malloc(sizeof(SFFloat)*1);
	p->parameter.count = 1;
	p->parameter.vals[0] = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	MediaBuffer Node deletion
*/

static void MediaBuffer_Del(GF_Node *node)
{
	M_MediaBuffer *p = (M_MediaBuffer *) node;
	gf_sg_mfurl_del(p->url);
	gf_node_free((GF_Node *) p);
}

static const u16 MediaBuffer_Def2All[] = { 0, 1, 2, 3, 5};
static const u16 MediaBuffer_In2All[] = { 0, 1, 2, 3, 5};
static const u16 MediaBuffer_Out2All[] = { 0, 1, 2, 3, 4, 5};

static u32 MediaBuffer_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 5;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 6;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 6;
	}
}

static GF_Err MediaBuffer_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = MediaBuffer_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = MediaBuffer_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = MediaBuffer_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err MediaBuffer_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "bufferSize";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_MediaBuffer *) node)->bufferSize;
		return GF_OK;
	case 1:
		info->name = "url";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_MediaBuffer *) node)->url;
		return GF_OK;
	case 2:
		info->name = "mediaStartTime";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_MediaBuffer *) node)->mediaStartTime;
		return GF_OK;
	case 3:
		info->name = "mediaStopTime";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_MediaBuffer *) node)->mediaStopTime;
		return GF_OK;
	case 4:
		info->name = "isBuffered";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_MediaBuffer *) node)->isBuffered;
		return GF_OK;
	case 5:
		info->name = "enabled";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_MediaBuffer *) node)->enabled;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 MediaBuffer_get_field_index_by_name(char *name)
{
	if (!strcmp("bufferSize", name)) return 0;
	if (!strcmp("url", name)) return 1;
	if (!strcmp("mediaStartTime", name)) return 2;
	if (!strcmp("mediaStopTime", name)) return 3;
	if (!strcmp("isBuffered", name)) return 4;
	if (!strcmp("enabled", name)) return 5;
	return -1;
	}
static Bool MediaBuffer_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *MediaBuffer_Create()
{
	M_MediaBuffer *p;
	GF_SAFEALLOC(p, M_MediaBuffer);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_MediaBuffer);

	/*default field values*/
	p->bufferSize = FLT2FIX(0.0);
	p->mediaStartTime = -1;
	p->mediaStopTime = FIX_MAX;
	p->enabled = 1;
	return (GF_Node *)p;
}


/*
	MediaControl Node deletion
*/

static void MediaControl_Del(GF_Node *node)
{
	M_MediaControl *p = (M_MediaControl *) node;
	gf_sg_mfurl_del(p->url);
	gf_node_free((GF_Node *) p);
}

static const u16 MediaControl_Def2All[] = { 0, 1, 2, 3, 4, 5, 6, 7};
static const u16 MediaControl_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7};
static const u16 MediaControl_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};

static u32 MediaControl_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 8;
	case GF_SG_FIELD_CODING_DEF: return 8;
	case GF_SG_FIELD_CODING_OUT: return 9;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 9;
	}
}

static GF_Err MediaControl_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = MediaControl_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = MediaControl_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = MediaControl_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err MediaControl_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "url";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_MediaControl *) node)->url;
		return GF_OK;
	case 1:
		info->name = "mediaStartTime";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_MediaControl *) node)->mediaStartTime;
		return GF_OK;
	case 2:
		info->name = "mediaStopTime";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_MediaControl *) node)->mediaStopTime;
		return GF_OK;
	case 3:
		info->name = "mediaSpeed";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_MediaControl *) node)->mediaSpeed;
		return GF_OK;
	case 4:
		info->name = "loop";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_MediaControl *) node)->loop;
		return GF_OK;
	case 5:
		info->name = "preRoll";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_MediaControl *) node)->preRoll;
		return GF_OK;
	case 6:
		info->name = "mute";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_MediaControl *) node)->mute;
		return GF_OK;
	case 7:
		info->name = "enabled";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_MediaControl *) node)->enabled;
		return GF_OK;
	case 8:
		info->name = "isPreRolled";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_MediaControl *) node)->isPreRolled;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 MediaControl_get_field_index_by_name(char *name)
{
	if (!strcmp("url", name)) return 0;
	if (!strcmp("mediaStartTime", name)) return 1;
	if (!strcmp("mediaStopTime", name)) return 2;
	if (!strcmp("mediaSpeed", name)) return 3;
	if (!strcmp("loop", name)) return 4;
	if (!strcmp("preRoll", name)) return 5;
	if (!strcmp("mute", name)) return 6;
	if (!strcmp("enabled", name)) return 7;
	if (!strcmp("isPreRolled", name)) return 8;
	return -1;
	}
static Bool MediaControl_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *MediaControl_Create()
{
	M_MediaControl *p;
	GF_SAFEALLOC(p, M_MediaControl);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_MediaControl);

	/*default field values*/
	p->mediaStartTime = -1;
	p->mediaStopTime = FIX_MAX;
	p->mediaSpeed = FLT2FIX(1.0);
	p->preRoll = 1;
	p->enabled = 1;
	return (GF_Node *)p;
}


/*
	MediaSensor Node deletion
*/

static void MediaSensor_Del(GF_Node *node)
{
	M_MediaSensor *p = (M_MediaSensor *) node;
	gf_sg_mfurl_del(p->url);
	gf_sg_mfstring_del(p->info);
	gf_node_free((GF_Node *) p);
}

static const u16 MediaSensor_Def2All[] = { 0};
static const u16 MediaSensor_In2All[] = { 0};
static const u16 MediaSensor_Out2All[] = { 0, 1, 2, 3, 4, 5};

static u32 MediaSensor_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 1;
	case GF_SG_FIELD_CODING_DEF: return 1;
	case GF_SG_FIELD_CODING_OUT: return 6;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 6;
	}
}

static GF_Err MediaSensor_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = MediaSensor_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = MediaSensor_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = MediaSensor_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err MediaSensor_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "url";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_MediaSensor *) node)->url;
		return GF_OK;
	case 1:
		info->name = "mediaCurrentTime";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_MediaSensor *) node)->mediaCurrentTime;
		return GF_OK;
	case 2:
		info->name = "streamObjectStartTime";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_MediaSensor *) node)->streamObjectStartTime;
		return GF_OK;
	case 3:
		info->name = "mediaDuration";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_MediaSensor *) node)->mediaDuration;
		return GF_OK;
	case 4:
		info->name = "isActive";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_MediaSensor *) node)->isActive;
		return GF_OK;
	case 5:
		info->name = "info";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_MFSTRING;
		info->far_ptr = & ((M_MediaSensor *) node)->info;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 MediaSensor_get_field_index_by_name(char *name)
{
	if (!strcmp("url", name)) return 0;
	if (!strcmp("mediaCurrentTime", name)) return 1;
	if (!strcmp("streamObjectStartTime", name)) return 2;
	if (!strcmp("mediaDuration", name)) return 3;
	if (!strcmp("isActive", name)) return 4;
	if (!strcmp("info", name)) return 5;
	return -1;
	}
static Bool MediaSensor_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *MediaSensor_Create()
{
	M_MediaSensor *p;
	GF_SAFEALLOC(p, M_MediaSensor);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_MediaSensor);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	BitWrapper Node deletion
*/

static void BitWrapper_Del(GF_Node *node)
{
	M_BitWrapper *p = (M_BitWrapper *) node;
	gf_node_unregister((GF_Node *) p->node, (GF_Node *) p);	
	gf_sg_mfurl_del(p->url);
	gf_sg_sfstring_del(p->buffer);
	gf_node_free((GF_Node *) p);
}

static const u16 BitWrapper_Def2All[] = { 0, 1, 2, 3};

static u32 BitWrapper_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 0;
	case GF_SG_FIELD_CODING_DEF: return 4;
	case GF_SG_FIELD_CODING_OUT: return 0;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err BitWrapper_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_DEF:
		*allField = BitWrapper_Def2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err BitWrapper_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "node";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFWorldNode;
		info->far_ptr = & ((M_BitWrapper *)node)->node;
		return GF_OK;
	case 1:
		info->name = "type";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_BitWrapper *) node)->type;
		return GF_OK;
	case 2:
		info->name = "url";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_BitWrapper *) node)->url;
		return GF_OK;
	case 3:
		info->name = "buffer";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_BitWrapper *) node)->buffer;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 BitWrapper_get_field_index_by_name(char *name)
{
	if (!strcmp("node", name)) return 0;
	if (!strcmp("type", name)) return 1;
	if (!strcmp("url", name)) return 2;
	if (!strcmp("buffer", name)) return 3;
	return -1;
	}
static Bool BitWrapper_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *BitWrapper_Create()
{
	M_BitWrapper *p;
	GF_SAFEALLOC(p, M_BitWrapper);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_BitWrapper);

	/*default field values*/
	p->type = 0;
	return (GF_Node *)p;
}


/*
	CoordinateInterpolator4D Node deletion
*/

static void CoordinateInterpolator4D_Del(GF_Node *node)
{
	M_CoordinateInterpolator4D *p = (M_CoordinateInterpolator4D *) node;
	gf_sg_mffloat_del(p->key);
	gf_sg_mfvec4f_del(p->keyValue);
	gf_sg_mfvec4f_del(p->value_changed);
	gf_node_free((GF_Node *) p);
}

static const u16 CoordinateInterpolator4D_Def2All[] = { 1, 2};
static const u16 CoordinateInterpolator4D_In2All[] = { 0, 1, 2};
static const u16 CoordinateInterpolator4D_Out2All[] = { 1, 2, 3};

static u32 CoordinateInterpolator4D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err CoordinateInterpolator4D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = CoordinateInterpolator4D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = CoordinateInterpolator4D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = CoordinateInterpolator4D_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err CoordinateInterpolator4D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_fraction";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_CoordinateInterpolator4D *)node)->on_set_fraction;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_CoordinateInterpolator4D *) node)->set_fraction;
		return GF_OK;
	case 1:
		info->name = "key";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_CoordinateInterpolator4D *) node)->key;
		return GF_OK;
	case 2:
		info->name = "keyValue";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC4F;
		info->far_ptr = & ((M_CoordinateInterpolator4D *) node)->keyValue;
		return GF_OK;
	case 3:
		info->name = "value_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_MFVEC4F;
		info->far_ptr = & ((M_CoordinateInterpolator4D *) node)->value_changed;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 CoordinateInterpolator4D_get_field_index_by_name(char *name)
{
	if (!strcmp("set_fraction", name)) return 0;
	if (!strcmp("key", name)) return 1;
	if (!strcmp("keyValue", name)) return 2;
	if (!strcmp("value_changed", name)) return 3;
	return -1;
	}
static Bool CoordinateInterpolator4D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 2:
		*AType = 0;
		*QType = 15;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *CoordinateInterpolator4D_Create()
{
	M_CoordinateInterpolator4D *p;
	GF_SAFEALLOC(p, M_CoordinateInterpolator4D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_CoordinateInterpolator4D);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	DepthImage Node deletion
*/

static void DepthImage_Del(GF_Node *node)
{
	M_DepthImage *p = (M_DepthImage *) node;
	gf_node_unregister((GF_Node *) p->diTexture, (GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 DepthImage_Def2All[] = { 0, 1, 2, 3, 4, 5, 6};

static u32 DepthImage_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 0;
	case GF_SG_FIELD_CODING_DEF: return 7;
	case GF_SG_FIELD_CODING_OUT: return 0;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 7;
	}
}

static GF_Err DepthImage_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_DEF:
		*allField = DepthImage_Def2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err DepthImage_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "diTexture";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFDepthTextureNode;
		info->far_ptr = & ((M_DepthImage *)node)->diTexture;
		return GF_OK;
	case 1:
		info->name = "farPlane";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_DepthImage *) node)->farPlane;
		return GF_OK;
	case 2:
		info->name = "fieldOfView";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_DepthImage *) node)->fieldOfView;
		return GF_OK;
	case 3:
		info->name = "nearPlane";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_DepthImage *) node)->nearPlane;
		return GF_OK;
	case 4:
		info->name = "orientation";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFROTATION;
		info->far_ptr = & ((M_DepthImage *) node)->orientation;
		return GF_OK;
	case 5:
		info->name = "orthographic";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_DepthImage *) node)->orthographic;
		return GF_OK;
	case 6:
		info->name = "position";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_DepthImage *) node)->position;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 DepthImage_get_field_index_by_name(char *name)
{
	if (!strcmp("diTexture", name)) return 0;
	if (!strcmp("farPlane", name)) return 1;
	if (!strcmp("fieldOfView", name)) return 2;
	if (!strcmp("nearPlane", name)) return 3;
	if (!strcmp("orientation", name)) return 4;
	if (!strcmp("orthographic", name)) return 5;
	if (!strcmp("position", name)) return 6;
	return -1;
	}
static Bool DepthImage_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *DepthImage_Create()
{
	M_DepthImage *p;
	GF_SAFEALLOC(p, M_DepthImage);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_DepthImage);

	/*default field values*/
	p->farPlane = FLT2FIX(100);
	p->fieldOfView.x = FLT2FIX(0.785398);
	p->fieldOfView.y = FLT2FIX(0.785398);
	p->nearPlane = FLT2FIX(10);
	p->orientation.x = FLT2FIX(0);
	p->orientation.y = FLT2FIX(0);
	p->orientation.z = FLT2FIX(1);
	p->orientation.q = FLT2FIX(0);
	p->orthographic = 1;
	p->position.x = FLT2FIX(0);
	p->position.y = FLT2FIX(0);
	p->position.z = FLT2FIX(10);
	return (GF_Node *)p;
}


/*
	FFD Node deletion
*/

static void FFD_Del(GF_Node *node)
{
	M_FFD *p = (M_FFD *) node;
	gf_sg_mfvec4f_del(p->controlPoint);
	gf_sg_mffloat_del(p->uKnot);
	gf_sg_mffloat_del(p->vKnot);
	gf_sg_mffloat_del(p->wKnot);
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 FFD_Def2All[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
static const u16 FFD_In2All[] = { 0, 1, 2, 3};
static const u16 FFD_Out2All[] = { 2, 3};
static const u16 FFD_Dyn2All[] = { 3};

static u32 FFD_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 11;
	case GF_SG_FIELD_CODING_OUT: return 2;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 13;
	}
}

static GF_Err FFD_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = FFD_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = FFD_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = FFD_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = FFD_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err FFD_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_FFD *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_FFD *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_FFD *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_FFD *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_FFD *)node)->children;
		return GF_OK;
	case 3:
		info->name = "controlPoint";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC4F;
		info->far_ptr = & ((M_FFD *) node)->controlPoint;
		return GF_OK;
	case 4:
		info->name = "uDimension";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FFD *) node)->uDimension;
		return GF_OK;
	case 5:
		info->name = "uKnot";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_FFD *) node)->uKnot;
		return GF_OK;
	case 6:
		info->name = "uOrder";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FFD *) node)->uOrder;
		return GF_OK;
	case 7:
		info->name = "vDimension";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FFD *) node)->vDimension;
		return GF_OK;
	case 8:
		info->name = "vKnot";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_FFD *) node)->vKnot;
		return GF_OK;
	case 9:
		info->name = "vOrder";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FFD *) node)->vOrder;
		return GF_OK;
	case 10:
		info->name = "wDimension";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FFD *) node)->wDimension;
		return GF_OK;
	case 11:
		info->name = "wKnot";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_FFD *) node)->wKnot;
		return GF_OK;
	case 12:
		info->name = "wOrder";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_FFD *) node)->wOrder;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 FFD_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	if (!strcmp("controlPoint", name)) return 3;
	if (!strcmp("uDimension", name)) return 4;
	if (!strcmp("uKnot", name)) return 5;
	if (!strcmp("uOrder", name)) return 6;
	if (!strcmp("vDimension", name)) return 7;
	if (!strcmp("vKnot", name)) return 8;
	if (!strcmp("vOrder", name)) return 9;
	if (!strcmp("wDimension", name)) return 10;
	if (!strcmp("wKnot", name)) return 11;
	if (!strcmp("wOrder", name)) return 12;
	return -1;
	}
static Bool FFD_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 3:
		*AType = 15;
		*QType = 15;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 4:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 8;
		*b_min = FLT2FIX(2);
		*b_max = FLT2FIX(257);
		return 1;
	case 6:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 5;
		*b_min = FLT2FIX(2);
		*b_max = FLT2FIX(33);
		return 1;
	case 7:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 8;
		*b_min = FLT2FIX(2);
		*b_max = FLT2FIX(257);
		return 1;
	case 9:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 5;
		*b_min = FLT2FIX(2);
		*b_max = FLT2FIX(33);
		return 1;
	case 10:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 8;
		*b_min = FLT2FIX(2);
		*b_max = FLT2FIX(257);
		return 1;
	case 12:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 5;
		*b_min = FLT2FIX(2);
		*b_max = FLT2FIX(33);
		return 1;
	default:
		return 0;
	}
}



GF_Node *FFD_Create()
{
	M_FFD *p;
	GF_SAFEALLOC(p, M_FFD);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_FFD);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->uDimension = 2;
	p->uOrder = 2;
	p->vDimension = 2;
	p->vOrder = 2;
	p->wDimension = 2;
	p->wOrder = 2;
	return (GF_Node *)p;
}


/*
	Implicit Node deletion
*/

static void Implicit_Del(GF_Node *node)
{
	M_Implicit *p = (M_Implicit *) node;
	gf_sg_mffloat_del(p->c);
	gf_sg_mfint32_del(p->densities);
	gf_node_free((GF_Node *) p);
}

static const u16 Implicit_Def2All[] = { 0, 1, 2, 3, 4};
static const u16 Implicit_In2All[] = { 0, 1, 2, 3, 4};
static const u16 Implicit_Out2All[] = { 0, 1, 2, 3, 4};
static const u16 Implicit_Dyn2All[] = { 0, 1};

static u32 Implicit_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 5;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 5;
	case GF_SG_FIELD_CODING_DYN: return 2;
	default:
		return 5;
	}
}

static GF_Err Implicit_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Implicit_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Implicit_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Implicit_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Implicit_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Implicit_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "bboxSize";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_Implicit *) node)->bboxSize;
		return GF_OK;
	case 1:
		info->name = "c";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_Implicit *) node)->c;
		return GF_OK;
	case 2:
		info->name = "densities";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_Implicit *) node)->densities;
		return GF_OK;
	case 3:
		info->name = "dual";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Implicit *) node)->dual;
		return GF_OK;
	case 4:
		info->name = "solid";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Implicit *) node)->solid;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Implicit_get_field_index_by_name(char *name)
{
	if (!strcmp("bboxSize", name)) return 0;
	if (!strcmp("c", name)) return 1;
	if (!strcmp("densities", name)) return 2;
	if (!strcmp("dual", name)) return 3;
	if (!strcmp("solid", name)) return 4;
	return -1;
	}
static Bool Implicit_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 11;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 1:
		*AType = 7;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Implicit_Create()
{
	M_Implicit *p;
	GF_SAFEALLOC(p, M_Implicit);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Implicit);

	/*default field values*/
	p->bboxSize.x = FLT2FIX(2);
	p->bboxSize.y = FLT2FIX(2);
	p->bboxSize.z = FLT2FIX(2);
	return (GF_Node *)p;
}


/*
	XXLFM_Appearance Node deletion
*/

static void XXLFM_Appearance_Del(GF_Node *node)
{
	M_XXLFM_Appearance *p = (M_XXLFM_Appearance *) node;
	gf_node_unregister((GF_Node *) p->blendList, (GF_Node *) p);	
	gf_node_unregister_children((GF_Node *) p, p->lightMapList);	
	gf_node_unregister_children((GF_Node *) p, p->tileList);	
	gf_node_unregister((GF_Node *) p->vertexFrameList, (GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 XXLFM_Appearance_Def2All[] = { 0, 1, 2, 3};
static const u16 XXLFM_Appearance_In2All[] = { 0, 1, 2, 3};
static const u16 XXLFM_Appearance_Out2All[] = { 0, 1, 2, 3};

static u32 XXLFM_Appearance_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 4;
	case GF_SG_FIELD_CODING_OUT: return 4;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err XXLFM_Appearance_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = XXLFM_Appearance_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = XXLFM_Appearance_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = XXLFM_Appearance_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err XXLFM_Appearance_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "blendList";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFBlendListNode;
		info->far_ptr = & ((M_XXLFM_Appearance *)node)->blendList;
		return GF_OK;
	case 1:
		info->name = "lightMapList";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFLightMapNode;
		info->far_ptr = & ((M_XXLFM_Appearance *)node)->lightMapList;
		return GF_OK;
	case 2:
		info->name = "tileList";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFTextureNode;
		info->far_ptr = & ((M_XXLFM_Appearance *)node)->tileList;
		return GF_OK;
	case 3:
		info->name = "vertexFrameList";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFFrameListNode;
		info->far_ptr = & ((M_XXLFM_Appearance *)node)->vertexFrameList;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 XXLFM_Appearance_get_field_index_by_name(char *name)
{
	if (!strcmp("blendList", name)) return 0;
	if (!strcmp("lightMapList", name)) return 1;
	if (!strcmp("tileList", name)) return 2;
	if (!strcmp("vertexFrameList", name)) return 3;
	return -1;
	}
static Bool XXLFM_Appearance_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *XXLFM_Appearance_Create()
{
	M_XXLFM_Appearance *p;
	GF_SAFEALLOC(p, M_XXLFM_Appearance);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_XXLFM_Appearance);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	XXLFM_BlendList Node deletion
*/

static void XXLFM_BlendList_Del(GF_Node *node)
{
	M_XXLFM_BlendList *p = (M_XXLFM_BlendList *) node;
	gf_sg_mfint32_del(p->blendMode);
	gf_sg_mfint32_del(p->lightMapIndex);
	gf_node_free((GF_Node *) p);
}

static const u16 XXLFM_BlendList_Def2All[] = { 0, 1};
static const u16 XXLFM_BlendList_In2All[] = { 0, 1};
static const u16 XXLFM_BlendList_Out2All[] = { 0, 1};

static u32 XXLFM_BlendList_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 2;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 2;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 2;
	}
}

static GF_Err XXLFM_BlendList_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = XXLFM_BlendList_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = XXLFM_BlendList_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = XXLFM_BlendList_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err XXLFM_BlendList_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "blendMode";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_XXLFM_BlendList *) node)->blendMode;
		return GF_OK;
	case 1:
		info->name = "lightMapIndex";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_XXLFM_BlendList *) node)->lightMapIndex;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 XXLFM_BlendList_get_field_index_by_name(char *name)
{
	if (!strcmp("blendMode", name)) return 0;
	if (!strcmp("lightMapIndex", name)) return 1;
	return -1;
	}
static Bool XXLFM_BlendList_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 1;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 1:
		*AType = 0;
		*QType = 14;
		return 1;
	default:
		return 0;
	}
}



GF_Node *XXLFM_BlendList_Create()
{
	M_XXLFM_BlendList *p;
	GF_SAFEALLOC(p, M_XXLFM_BlendList);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_XXLFM_BlendList);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	XXLFM_FrameList Node deletion
*/

static void XXLFM_FrameList_Del(GF_Node *node)
{
	M_XXLFM_FrameList *p = (M_XXLFM_FrameList *) node;
	gf_sg_mfint32_del(p->index);
	gf_sg_mfvec3f_del(p->frame);
	gf_node_free((GF_Node *) p);
}

static const u16 XXLFM_FrameList_Def2All[] = { 0, 1};
static const u16 XXLFM_FrameList_In2All[] = { 0, 1};
static const u16 XXLFM_FrameList_Out2All[] = { 0, 1};

static u32 XXLFM_FrameList_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 2;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 2;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 2;
	}
}

static GF_Err XXLFM_FrameList_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = XXLFM_FrameList_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = XXLFM_FrameList_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = XXLFM_FrameList_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err XXLFM_FrameList_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "index";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_XXLFM_FrameList *) node)->index;
		return GF_OK;
	case 1:
		info->name = "frame";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC3F;
		info->far_ptr = & ((M_XXLFM_FrameList *) node)->frame;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 XXLFM_FrameList_get_field_index_by_name(char *name)
{
	if (!strcmp("index", name)) return 0;
	if (!strcmp("frame", name)) return 1;
	return -1;
	}
static Bool XXLFM_FrameList_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 0;
		*QType = 14;
		return 1;
	case 1:
		*AType = 0;
		*QType = 1;
		*b_min = FLT2FIX(-1);
		*b_max = FLT2FIX(1);
		return 1;
	default:
		return 0;
	}
}



GF_Node *XXLFM_FrameList_Create()
{
	M_XXLFM_FrameList *p;
	GF_SAFEALLOC(p, M_XXLFM_FrameList);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_XXLFM_FrameList);

	/*default field values*/
	p->index.vals = (SFInt32*)malloc(sizeof(SFInt32)*1);
	p->index.count = 1;
	p->index.vals[0] = -1;
	p->frame.vals = (SFVec3f *)malloc(sizeof(SFVec3f)*3);
	p->frame.count = 3;
	p->frame.vals[0].x = FLT2FIX(1);
	p->frame.vals[0].y = FLT2FIX(0);
	p->frame.vals[0].z = FLT2FIX(0);
	p->frame.vals[1].x = FLT2FIX(0);
	p->frame.vals[1].y = FLT2FIX(1);
	p->frame.vals[1].z = FLT2FIX(0);
	p->frame.vals[2].x = FLT2FIX(0);
	p->frame.vals[2].y = FLT2FIX(0);
	p->frame.vals[2].z = FLT2FIX(1);
	return (GF_Node *)p;
}


/*
	XXLFM_LightMap Node deletion
*/

static void XXLFM_LightMap_Del(GF_Node *node)
{
	M_XXLFM_LightMap *p = (M_XXLFM_LightMap *) node;
	gf_node_unregister((GF_Node *) p->surfaceMapList, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->viewMapList, (GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 XXLFM_LightMap_Def2All[] = { 0, 1, 2, 3, 4};
static const u16 XXLFM_LightMap_In2All[] = { 0, 1, 2, 3, 4};
static const u16 XXLFM_LightMap_Out2All[] = { 0, 1, 2, 3, 4};

static u32 XXLFM_LightMap_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 5;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 5;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 5;
	}
}

static GF_Err XXLFM_LightMap_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = XXLFM_LightMap_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = XXLFM_LightMap_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = XXLFM_LightMap_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err XXLFM_LightMap_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "biasRGB";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_XXLFM_LightMap *) node)->biasRGB;
		return GF_OK;
	case 1:
		info->name = "priorityLevel";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_XXLFM_LightMap *) node)->priorityLevel;
		return GF_OK;
	case 2:
		info->name = "scaleRGB";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_XXLFM_LightMap *) node)->scaleRGB;
		return GF_OK;
	case 3:
		info->name = "surfaceMapList";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFSurfaceMapNode;
		info->far_ptr = & ((M_XXLFM_LightMap *)node)->surfaceMapList;
		return GF_OK;
	case 4:
		info->name = "viewMapList";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFViewMapNode;
		info->far_ptr = & ((M_XXLFM_LightMap *)node)->viewMapList;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 XXLFM_LightMap_get_field_index_by_name(char *name)
{
	if (!strcmp("biasRGB", name)) return 0;
	if (!strcmp("priorityLevel", name)) return 1;
	if (!strcmp("scaleRGB", name)) return 2;
	if (!strcmp("surfaceMapList", name)) return 3;
	if (!strcmp("viewMapList", name)) return 4;
	return -1;
	}
static Bool XXLFM_LightMap_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 0;
		*QType = 7;
		*b_min = FLT2FIX(-1);
		*b_max = FLT2FIX(1);
		return 1;
	case 1:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(255);
		return 1;
	case 2:
		*AType = 0;
		*QType = 7;
		*b_min = FLT2FIX(-1);
		*b_max = FLT2FIX(1);
		return 1;
	default:
		return 0;
	}
}



GF_Node *XXLFM_LightMap_Create()
{
	M_XXLFM_LightMap *p;
	GF_SAFEALLOC(p, M_XXLFM_LightMap);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_XXLFM_LightMap);

	/*default field values*/
	p->biasRGB.x = FLT2FIX(0);
	p->biasRGB.y = FLT2FIX(0);
	p->biasRGB.z = FLT2FIX(0);
	p->priorityLevel = 0;
	p->scaleRGB.x = FLT2FIX(1);
	p->scaleRGB.y = FLT2FIX(1);
	p->scaleRGB.z = FLT2FIX(1);
	return (GF_Node *)p;
}


/*
	XXLFM_SurfaceMapList Node deletion
*/

static void XXLFM_SurfaceMapList_Del(GF_Node *node)
{
	M_XXLFM_SurfaceMapList *p = (M_XXLFM_SurfaceMapList *) node;
	gf_sg_mfint32_del(p->tileIndex);
	gf_node_unregister((GF_Node *) p->triangleCoordinate, (GF_Node *) p);	
	gf_sg_mfint32_del(p->triangleIndex);
	gf_sg_mfint32_del(p->viewMapIndex);
	gf_node_free((GF_Node *) p);
}

static const u16 XXLFM_SurfaceMapList_Def2All[] = { 0, 1, 2, 3};
static const u16 XXLFM_SurfaceMapList_In2All[] = { 0, 1, 2, 3};
static const u16 XXLFM_SurfaceMapList_Out2All[] = { 0, 1, 2, 3};

static u32 XXLFM_SurfaceMapList_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 4;
	case GF_SG_FIELD_CODING_OUT: return 4;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err XXLFM_SurfaceMapList_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = XXLFM_SurfaceMapList_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = XXLFM_SurfaceMapList_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = XXLFM_SurfaceMapList_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err XXLFM_SurfaceMapList_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "tileIndex";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_XXLFM_SurfaceMapList *) node)->tileIndex;
		return GF_OK;
	case 1:
		info->name = "triangleCoordinate";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFTextureCoordinateNode;
		info->far_ptr = & ((M_XXLFM_SurfaceMapList *)node)->triangleCoordinate;
		return GF_OK;
	case 2:
		info->name = "triangleIndex";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_XXLFM_SurfaceMapList *) node)->triangleIndex;
		return GF_OK;
	case 3:
		info->name = "viewMapIndex";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_XXLFM_SurfaceMapList *) node)->viewMapIndex;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 XXLFM_SurfaceMapList_get_field_index_by_name(char *name)
{
	if (!strcmp("tileIndex", name)) return 0;
	if (!strcmp("triangleCoordinate", name)) return 1;
	if (!strcmp("triangleIndex", name)) return 2;
	if (!strcmp("viewMapIndex", name)) return 3;
	return -1;
	}
static Bool XXLFM_SurfaceMapList_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 0;
		*QType = 14;
		return 1;
	case 2:
		*AType = 0;
		*QType = 14;
		return 1;
	case 3:
		*AType = 0;
		*QType = 14;
		return 1;
	default:
		return 0;
	}
}



GF_Node *XXLFM_SurfaceMapList_Create()
{
	M_XXLFM_SurfaceMapList *p;
	GF_SAFEALLOC(p, M_XXLFM_SurfaceMapList);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_XXLFM_SurfaceMapList);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	XXLFM_ViewMapList Node deletion
*/

static void XXLFM_ViewMapList_Del(GF_Node *node)
{
	M_XXLFM_ViewMapList *p = (M_XXLFM_ViewMapList *) node;
	gf_node_unregister((GF_Node *) p->textureOrigin, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->textureSize, (GF_Node *) p);	
	gf_sg_mfint32_del(p->tileIndex);
	gf_sg_mfint32_del(p->vertexIndex);
	gf_node_free((GF_Node *) p);
}

static const u16 XXLFM_ViewMapList_Def2All[] = { 0, 1, 2, 3};
static const u16 XXLFM_ViewMapList_In2All[] = { 0, 1, 2, 3};
static const u16 XXLFM_ViewMapList_Out2All[] = { 0, 1, 2, 3};

static u32 XXLFM_ViewMapList_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 4;
	case GF_SG_FIELD_CODING_OUT: return 4;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err XXLFM_ViewMapList_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = XXLFM_ViewMapList_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = XXLFM_ViewMapList_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = XXLFM_ViewMapList_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err XXLFM_ViewMapList_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "textureOrigin";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFTextureCoordinateNode;
		info->far_ptr = & ((M_XXLFM_ViewMapList *)node)->textureOrigin;
		return GF_OK;
	case 1:
		info->name = "textureSize";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFTextureCoordinateNode;
		info->far_ptr = & ((M_XXLFM_ViewMapList *)node)->textureSize;
		return GF_OK;
	case 2:
		info->name = "tileIndex";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_XXLFM_ViewMapList *) node)->tileIndex;
		return GF_OK;
	case 3:
		info->name = "vertexIndex";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_XXLFM_ViewMapList *) node)->vertexIndex;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 XXLFM_ViewMapList_get_field_index_by_name(char *name)
{
	if (!strcmp("textureOrigin", name)) return 0;
	if (!strcmp("textureSize", name)) return 1;
	if (!strcmp("tileIndex", name)) return 2;
	if (!strcmp("vertexIndex", name)) return 3;
	return -1;
	}
static Bool XXLFM_ViewMapList_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 2:
		*AType = 0;
		*QType = 14;
		return 1;
	case 3:
		*AType = 0;
		*QType = 14;
		return 1;
	default:
		return 0;
	}
}



GF_Node *XXLFM_ViewMapList_Create()
{
	M_XXLFM_ViewMapList *p;
	GF_SAFEALLOC(p, M_XXLFM_ViewMapList);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_XXLFM_ViewMapList);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	MeshGrid Node deletion
*/

static void MeshGrid_Del(GF_Node *node)
{
	M_MeshGrid *p = (M_MeshGrid *) node;
	gf_sg_mfint32_del(p->set_colorIndex);
	gf_sg_mfint32_del(p->set_coordIndex);
	gf_sg_mfint32_del(p->set_normalIndex);
	gf_sg_mfint32_del(p->set_texCoordIndex);
	gf_node_unregister((GF_Node *) p->color, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->coord, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->gridCoord, (GF_Node *) p);	
	gf_sg_mfint32_del(p->nLevels);
	gf_node_unregister((GF_Node *) p->normal, (GF_Node *) p);	
	gf_sg_mfint32_del(p->nSlices);
	gf_node_unregister((GF_Node *) p->texCoord, (GF_Node *) p);	
	gf_sg_mffloat_del(p->vertexOffset);
	gf_sg_mfint32_del(p->vertexLink);
	gf_sg_mfint32_del(p->colorIndex);
	gf_sg_mfint32_del(p->coordIndex);
	gf_sg_mfint32_del(p->normalIndex);
	gf_sg_mfint32_del(p->texCoordIndex);
	gf_sg_mfint32_del(p->nVertices);
	gf_node_free((GF_Node *) p);
}

static const u16 MeshGrid_Def2All[] = { 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
static const u16 MeshGrid_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
static const u16 MeshGrid_Out2All[] = { 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 21, 22};
static const u16 MeshGrid_Dyn2All[] = { 6, 7, 9, 10, 12, 14};

static u32 MeshGrid_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 16;
	case GF_SG_FIELD_CODING_DEF: return 17;
	case GF_SG_FIELD_CODING_OUT: return 14;
	case GF_SG_FIELD_CODING_DYN: return 6;
	default:
		return 23;
	}
}

static GF_Err MeshGrid_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = MeshGrid_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = MeshGrid_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = MeshGrid_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = MeshGrid_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err MeshGrid_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_colorIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_MeshGrid *)node)->on_set_colorIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_MeshGrid *) node)->set_colorIndex;
		return GF_OK;
	case 1:
		info->name = "set_coordIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_MeshGrid *)node)->on_set_coordIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_MeshGrid *) node)->set_coordIndex;
		return GF_OK;
	case 2:
		info->name = "set_normalIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_MeshGrid *)node)->on_set_normalIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_MeshGrid *) node)->set_normalIndex;
		return GF_OK;
	case 3:
		info->name = "set_texCoordIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_MeshGrid *)node)->on_set_texCoordIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_MeshGrid *) node)->set_texCoordIndex;
		return GF_OK;
	case 4:
		info->name = "color";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFColorNode;
		info->far_ptr = & ((M_MeshGrid *)node)->color;
		return GF_OK;
	case 5:
		info->name = "coord";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFCoordinateNode;
		info->far_ptr = & ((M_MeshGrid *)node)->coord;
		return GF_OK;
	case 6:
		info->name = "displayLevel";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_MeshGrid *) node)->displayLevel;
		return GF_OK;
	case 7:
		info->name = "filterType";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_MeshGrid *) node)->filterType;
		return GF_OK;
	case 8:
		info->name = "gridCoord";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFCoordinateNode;
		info->far_ptr = & ((M_MeshGrid *)node)->gridCoord;
		return GF_OK;
	case 9:
		info->name = "hierarchicalLevel";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_MeshGrid *) node)->hierarchicalLevel;
		return GF_OK;
	case 10:
		info->name = "nLevels";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_MeshGrid *) node)->nLevels;
		return GF_OK;
	case 11:
		info->name = "normal";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFNormalNode;
		info->far_ptr = & ((M_MeshGrid *)node)->normal;
		return GF_OK;
	case 12:
		info->name = "nSlices";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_MeshGrid *) node)->nSlices;
		return GF_OK;
	case 13:
		info->name = "texCoord";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFTextureCoordinateNode;
		info->far_ptr = & ((M_MeshGrid *)node)->texCoord;
		return GF_OK;
	case 14:
		info->name = "vertexOffset";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_MeshGrid *) node)->vertexOffset;
		return GF_OK;
	case 15:
		info->name = "vertexLink";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_MeshGrid *) node)->vertexLink;
		return GF_OK;
	case 16:
		info->name = "colorIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_MeshGrid *) node)->colorIndex;
		return GF_OK;
	case 17:
		info->name = "coordIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_MeshGrid *) node)->coordIndex;
		return GF_OK;
	case 18:
		info->name = "normalIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_MeshGrid *) node)->normalIndex;
		return GF_OK;
	case 19:
		info->name = "solid";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_MeshGrid *) node)->solid;
		return GF_OK;
	case 20:
		info->name = "texCoordIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_MeshGrid *) node)->texCoordIndex;
		return GF_OK;
	case 21:
		info->name = "isLoading";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_MeshGrid *) node)->isLoading;
		return GF_OK;
	case 22:
		info->name = "nVertices";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_MeshGrid *) node)->nVertices;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 MeshGrid_get_field_index_by_name(char *name)
{
	if (!strcmp("set_colorIndex", name)) return 0;
	if (!strcmp("set_coordIndex", name)) return 1;
	if (!strcmp("set_normalIndex", name)) return 2;
	if (!strcmp("set_texCoordIndex", name)) return 3;
	if (!strcmp("color", name)) return 4;
	if (!strcmp("coord", name)) return 5;
	if (!strcmp("displayLevel", name)) return 6;
	if (!strcmp("filterType", name)) return 7;
	if (!strcmp("gridCoord", name)) return 8;
	if (!strcmp("hierarchicalLevel", name)) return 9;
	if (!strcmp("nLevels", name)) return 10;
	if (!strcmp("normal", name)) return 11;
	if (!strcmp("nSlices", name)) return 12;
	if (!strcmp("texCoord", name)) return 13;
	if (!strcmp("vertexOffset", name)) return 14;
	if (!strcmp("vertexLink", name)) return 15;
	if (!strcmp("colorIndex", name)) return 16;
	if (!strcmp("coordIndex", name)) return 17;
	if (!strcmp("normalIndex", name)) return 18;
	if (!strcmp("solid", name)) return 19;
	if (!strcmp("texCoordIndex", name)) return 20;
	if (!strcmp("isLoading", name)) return 21;
	if (!strcmp("nVertices", name)) return 22;
	return -1;
	}
static Bool MeshGrid_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 6:
		*AType = 13;
		*QType = 13;
		*QT13_bits = 32;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 7:
		*AType = 13;
		*QType = 13;
		*QT13_bits = 2;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX( 1);
		return 1;
	case 9:
		*AType = 13;
		*QType = 13;
		*QT13_bits = 32;
		*b_min = FLT2FIX(-1);
		*b_max = FIX_MAX;
		return 1;
	case 10:
		*AType = 7;
		*QType = 7;
		return 1;
	case 12:
		*AType = 7;
		*QType = 7;
		return 1;
	case 14:
		*AType = 7;
		*QType = 7;
		*b_min = FLT2FIX(0.0);
		*b_max = FLT2FIX( 2.0);
		return 1;
	case 15:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 2;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX( 3);
		return 1;
	case 16:
		*AType = 0;
		*QType = 14;
		*b_min = FLT2FIX(-1);
		*b_max = FIX_MAX;
		return 1;
	case 17:
		*AType = 0;
		*QType = 14;
		*b_min = FLT2FIX(-1);
		*b_max = FIX_MAX;
		return 1;
	case 18:
		*AType = 0;
		*QType = 14;
		*b_min = FLT2FIX(-1);
		*b_max = FIX_MAX;
		return 1;
	case 20:
		*AType = 0;
		*QType = 14;
		*b_min = FLT2FIX(-1);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *MeshGrid_Create()
{
	M_MeshGrid *p;
	GF_SAFEALLOC(p, M_MeshGrid);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_MeshGrid);

	/*default field values*/
	p->displayLevel = 0;
	p->filterType = 0;
	p->hierarchicalLevel = 0;
	p->solid = 1;
	return (GF_Node *)p;
}


/*
	NonLinearDeformer Node deletion
*/

static void NonLinearDeformer_Del(GF_Node *node)
{
	M_NonLinearDeformer *p = (M_NonLinearDeformer *) node;
	gf_sg_mffloat_del(p->extend);
	gf_node_unregister((GF_Node *) p->geometry, (GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 NonLinearDeformer_Def2All[] = { 0, 1, 2, 3, 4};
static const u16 NonLinearDeformer_In2All[] = { 0, 1, 2, 3, 4};
static const u16 NonLinearDeformer_Out2All[] = { 0, 1, 2, 3, 4};

static u32 NonLinearDeformer_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 5;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 5;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 5;
	}
}

static GF_Err NonLinearDeformer_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = NonLinearDeformer_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = NonLinearDeformer_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = NonLinearDeformer_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err NonLinearDeformer_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "axis";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_NonLinearDeformer *) node)->axis;
		return GF_OK;
	case 1:
		info->name = "extend";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_NonLinearDeformer *) node)->extend;
		return GF_OK;
	case 2:
		info->name = "geometry";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFGeometryNode;
		info->far_ptr = & ((M_NonLinearDeformer *)node)->geometry;
		return GF_OK;
	case 3:
		info->name = "param";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_NonLinearDeformer *) node)->param;
		return GF_OK;
	case 4:
		info->name = "type";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_NonLinearDeformer *) node)->type;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 NonLinearDeformer_get_field_index_by_name(char *name)
{
	if (!strcmp("axis", name)) return 0;
	if (!strcmp("extend", name)) return 1;
	if (!strcmp("geometry", name)) return 2;
	if (!strcmp("param", name)) return 3;
	if (!strcmp("type", name)) return 4;
	return -1;
	}
static Bool NonLinearDeformer_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *NonLinearDeformer_Create()
{
	M_NonLinearDeformer *p;
	GF_SAFEALLOC(p, M_NonLinearDeformer);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_NonLinearDeformer);

	/*default field values*/
	p->axis.x = FLT2FIX(0);
	p->axis.y = FLT2FIX(0);
	p->axis.z = FLT2FIX(1);
	p->param = FLT2FIX(0);
	p->type = 0;
	return (GF_Node *)p;
}


/*
	NurbsCurve Node deletion
*/

static void NurbsCurve_Del(GF_Node *node)
{
	M_NurbsCurve *p = (M_NurbsCurve *) node;
	gf_sg_mfint32_del(p->set_colorIndex);
	gf_node_unregister((GF_Node *) p->color, (GF_Node *) p);	
	gf_sg_mfvec4f_del(p->controlPoint);
	gf_sg_mfint32_del(p->colorIndex);
	gf_sg_mffloat_del(p->knot);
	gf_node_free((GF_Node *) p);
}

static const u16 NurbsCurve_Def2All[] = { 1, 2, 3, 4, 5, 6, 7};
static const u16 NurbsCurve_In2All[] = { 0, 1, 2, 3};
static const u16 NurbsCurve_Out2All[] = { 1, 2, 3};
static const u16 NurbsCurve_Dyn2All[] = { 2};

static u32 NurbsCurve_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 7;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 8;
	}
}

static GF_Err NurbsCurve_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = NurbsCurve_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = NurbsCurve_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = NurbsCurve_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = NurbsCurve_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err NurbsCurve_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_colorIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_NurbsCurve *)node)->on_set_colorIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_NurbsCurve *) node)->set_colorIndex;
		return GF_OK;
	case 1:
		info->name = "color";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFColorNode;
		info->far_ptr = & ((M_NurbsCurve *)node)->color;
		return GF_OK;
	case 2:
		info->name = "controlPoint";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC4F;
		info->far_ptr = & ((M_NurbsCurve *) node)->controlPoint;
		return GF_OK;
	case 3:
		info->name = "tessellation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_NurbsCurve *) node)->tessellation;
		return GF_OK;
	case 4:
		info->name = "colorIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_NurbsCurve *) node)->colorIndex;
		return GF_OK;
	case 5:
		info->name = "colorPerVertex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_NurbsCurve *) node)->colorPerVertex;
		return GF_OK;
	case 6:
		info->name = "knot";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_NurbsCurve *) node)->knot;
		return GF_OK;
	case 7:
		info->name = "order";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_NurbsCurve *) node)->order;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 NurbsCurve_get_field_index_by_name(char *name)
{
	if (!strcmp("set_colorIndex", name)) return 0;
	if (!strcmp("color", name)) return 1;
	if (!strcmp("controlPoint", name)) return 2;
	if (!strcmp("tessellation", name)) return 3;
	if (!strcmp("colorIndex", name)) return 4;
	if (!strcmp("colorPerVertex", name)) return 5;
	if (!strcmp("knot", name)) return 6;
	if (!strcmp("order", name)) return 7;
	return -1;
	}
static Bool NurbsCurve_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 2:
		*AType = 15;
		*QType = 15;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 4:
		*AType = 0;
		*QType = 14;
		return 1;
	case 7:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 5;
		*b_min = FLT2FIX(3);
		*b_max = FLT2FIX(34);
		return 1;
	default:
		return 0;
	}
}



GF_Node *NurbsCurve_Create()
{
	M_NurbsCurve *p;
	GF_SAFEALLOC(p, M_NurbsCurve);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_NurbsCurve);

	/*default field values*/
	p->tessellation = 0;
	p->colorPerVertex = 1;
	p->order = 4;
	return (GF_Node *)p;
}


/*
	NurbsCurve2D Node deletion
*/

static void NurbsCurve2D_Del(GF_Node *node)
{
	M_NurbsCurve2D *p = (M_NurbsCurve2D *) node;
	gf_sg_mfint32_del(p->set_colorIndex);
	gf_node_unregister((GF_Node *) p->color, (GF_Node *) p);	
	gf_sg_mfvec3f_del(p->controlPoint);
	gf_sg_mfint32_del(p->colorIndex);
	gf_sg_mffloat_del(p->knot);
	gf_node_free((GF_Node *) p);
}

static const u16 NurbsCurve2D_Def2All[] = { 1, 2, 3, 4, 5, 6, 7};
static const u16 NurbsCurve2D_In2All[] = { 0, 1, 2, 3};
static const u16 NurbsCurve2D_Out2All[] = { 1, 2, 3};
static const u16 NurbsCurve2D_Dyn2All[] = { 2};

static u32 NurbsCurve2D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 7;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 8;
	}
}

static GF_Err NurbsCurve2D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = NurbsCurve2D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = NurbsCurve2D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = NurbsCurve2D_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = NurbsCurve2D_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err NurbsCurve2D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_colorIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_NurbsCurve2D *)node)->on_set_colorIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_NurbsCurve2D *) node)->set_colorIndex;
		return GF_OK;
	case 1:
		info->name = "color";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFColorNode;
		info->far_ptr = & ((M_NurbsCurve2D *)node)->color;
		return GF_OK;
	case 2:
		info->name = "controlPoint";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC3F;
		info->far_ptr = & ((M_NurbsCurve2D *) node)->controlPoint;
		return GF_OK;
	case 3:
		info->name = "tessellation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_NurbsCurve2D *) node)->tessellation;
		return GF_OK;
	case 4:
		info->name = "colorIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_NurbsCurve2D *) node)->colorIndex;
		return GF_OK;
	case 5:
		info->name = "colorPerVertex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_NurbsCurve2D *) node)->colorPerVertex;
		return GF_OK;
	case 6:
		info->name = "knot";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_NurbsCurve2D *) node)->knot;
		return GF_OK;
	case 7:
		info->name = "order";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_NurbsCurve2D *) node)->order;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 NurbsCurve2D_get_field_index_by_name(char *name)
{
	if (!strcmp("set_colorIndex", name)) return 0;
	if (!strcmp("color", name)) return 1;
	if (!strcmp("controlPoint", name)) return 2;
	if (!strcmp("tessellation", name)) return 3;
	if (!strcmp("colorIndex", name)) return 4;
	if (!strcmp("colorPerVertex", name)) return 5;
	if (!strcmp("knot", name)) return 6;
	if (!strcmp("order", name)) return 7;
	return -1;
	}
static Bool NurbsCurve2D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 2:
		*AType = 2;
		*QType = 2;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 4:
		*AType = 0;
		*QType = 14;
		return 1;
	case 7:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 5;
		*b_min = FLT2FIX(3);
		*b_max = FLT2FIX(34);
		return 1;
	default:
		return 0;
	}
}



GF_Node *NurbsCurve2D_Create()
{
	M_NurbsCurve2D *p;
	GF_SAFEALLOC(p, M_NurbsCurve2D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_NurbsCurve2D);

	/*default field values*/
	p->tessellation = 0;
	p->colorPerVertex = 1;
	p->order = 4;
	return (GF_Node *)p;
}


/*
	NurbsSurface Node deletion
*/

static void NurbsSurface_Del(GF_Node *node)
{
	M_NurbsSurface *p = (M_NurbsSurface *) node;
	gf_sg_mfint32_del(p->set_colorIndex);
	gf_sg_mfint32_del(p->set_texColorIndex);
	gf_node_unregister((GF_Node *) p->color, (GF_Node *) p);	
	gf_sg_mfvec4f_del(p->controlPoint);
	gf_node_unregister((GF_Node *) p->texCoord, (GF_Node *) p);	
	gf_sg_mfint32_del(p->colorIndex);
	gf_sg_mfint32_del(p->texColorIndex);
	gf_sg_mffloat_del(p->uKnot);
	gf_sg_mffloat_del(p->vKnot);
	gf_node_free((GF_Node *) p);
}

static const u16 NurbsSurface_Def2All[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17};
static const u16 NurbsSurface_In2All[] = { 0, 1, 2, 3, 4, 5, 6};
static const u16 NurbsSurface_Out2All[] = { 2, 3, 4, 5, 6};
static const u16 NurbsSurface_Dyn2All[] = { 3};

static u32 NurbsSurface_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 7;
	case GF_SG_FIELD_CODING_DEF: return 16;
	case GF_SG_FIELD_CODING_OUT: return 5;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 18;
	}
}

static GF_Err NurbsSurface_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = NurbsSurface_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = NurbsSurface_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = NurbsSurface_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = NurbsSurface_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err NurbsSurface_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_colorIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_NurbsSurface *)node)->on_set_colorIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_NurbsSurface *) node)->set_colorIndex;
		return GF_OK;
	case 1:
		info->name = "set_texColorIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_NurbsSurface *)node)->on_set_texColorIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_NurbsSurface *) node)->set_texColorIndex;
		return GF_OK;
	case 2:
		info->name = "color";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFColorNode;
		info->far_ptr = & ((M_NurbsSurface *)node)->color;
		return GF_OK;
	case 3:
		info->name = "controlPoint";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC4F;
		info->far_ptr = & ((M_NurbsSurface *) node)->controlPoint;
		return GF_OK;
	case 4:
		info->name = "texCoord";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFTextureCoordinateNode;
		info->far_ptr = & ((M_NurbsSurface *)node)->texCoord;
		return GF_OK;
	case 5:
		info->name = "uTessellation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_NurbsSurface *) node)->uTessellation;
		return GF_OK;
	case 6:
		info->name = "vTessellation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_NurbsSurface *) node)->vTessellation;
		return GF_OK;
	case 7:
		info->name = "ccw";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_NurbsSurface *) node)->ccw;
		return GF_OK;
	case 8:
		info->name = "colorIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_NurbsSurface *) node)->colorIndex;
		return GF_OK;
	case 9:
		info->name = "colorPerVertex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_NurbsSurface *) node)->colorPerVertex;
		return GF_OK;
	case 10:
		info->name = "solid";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_NurbsSurface *) node)->solid;
		return GF_OK;
	case 11:
		info->name = "texColorIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_NurbsSurface *) node)->texColorIndex;
		return GF_OK;
	case 12:
		info->name = "uDimension";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_NurbsSurface *) node)->uDimension;
		return GF_OK;
	case 13:
		info->name = "uKnot";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_NurbsSurface *) node)->uKnot;
		return GF_OK;
	case 14:
		info->name = "uOrder";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_NurbsSurface *) node)->uOrder;
		return GF_OK;
	case 15:
		info->name = "vDimension";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_NurbsSurface *) node)->vDimension;
		return GF_OK;
	case 16:
		info->name = "vKnot";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_NurbsSurface *) node)->vKnot;
		return GF_OK;
	case 17:
		info->name = "vOrder";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_NurbsSurface *) node)->vOrder;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 NurbsSurface_get_field_index_by_name(char *name)
{
	if (!strcmp("set_colorIndex", name)) return 0;
	if (!strcmp("set_texColorIndex", name)) return 1;
	if (!strcmp("color", name)) return 2;
	if (!strcmp("controlPoint", name)) return 3;
	if (!strcmp("texCoord", name)) return 4;
	if (!strcmp("uTessellation", name)) return 5;
	if (!strcmp("vTessellation", name)) return 6;
	if (!strcmp("ccw", name)) return 7;
	if (!strcmp("colorIndex", name)) return 8;
	if (!strcmp("colorPerVertex", name)) return 9;
	if (!strcmp("solid", name)) return 10;
	if (!strcmp("texColorIndex", name)) return 11;
	if (!strcmp("uDimension", name)) return 12;
	if (!strcmp("uKnot", name)) return 13;
	if (!strcmp("uOrder", name)) return 14;
	if (!strcmp("vDimension", name)) return 15;
	if (!strcmp("vKnot", name)) return 16;
	if (!strcmp("vOrder", name)) return 17;
	return -1;
	}
static Bool NurbsSurface_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 3:
		*AType = 15;
		*QType = 15;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 8:
		*AType = 0;
		*QType = 14;
		return 1;
	case 11:
		*AType = 0;
		*QType = 14;
		return 1;
	case 12:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 8;
		*b_min = FLT2FIX(3);
		*b_max = FLT2FIX(258);
		return 1;
	case 14:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 5;
		*b_min = FLT2FIX(3);
		*b_max = FLT2FIX(34);
		return 1;
	case 15:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 8;
		*b_min = FLT2FIX(3);
		*b_max = FLT2FIX(258);
		return 1;
	case 17:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 5;
		*b_min = FLT2FIX(3);
		*b_max = FLT2FIX(34);
		return 1;
	default:
		return 0;
	}
}



GF_Node *NurbsSurface_Create()
{
	M_NurbsSurface *p;
	GF_SAFEALLOC(p, M_NurbsSurface);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_NurbsSurface);

	/*default field values*/
	p->uTessellation = 0;
	p->vTessellation = 0;
	p->ccw = 1;
	p->colorPerVertex = 1;
	p->solid = 1;
	p->uDimension = 4;
	p->uOrder = 4;
	p->vDimension = 4;
	p->vOrder = 4;
	return (GF_Node *)p;
}


/*
	OctreeImage Node deletion
*/

static void OctreeImage_Del(GF_Node *node)
{
	M_OctreeImage *p = (M_OctreeImage *) node;
	gf_node_unregister_children((GF_Node *) p, p->images);	
	gf_sg_mfint32_del(p->octree);
	gf_sg_mfint32_del(p->voxelImageIndex);
	gf_node_free((GF_Node *) p);
}

static const u16 OctreeImage_Def2All[] = { 0, 1, 2, 3};

static u32 OctreeImage_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 0;
	case GF_SG_FIELD_CODING_DEF: return 4;
	case GF_SG_FIELD_CODING_OUT: return 0;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err OctreeImage_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_DEF:
		*allField = OctreeImage_Def2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err OctreeImage_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "images";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFDepthImageNode;
		info->far_ptr = & ((M_OctreeImage *)node)->images;
		return GF_OK;
	case 1:
		info->name = "octree";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_OctreeImage *) node)->octree;
		return GF_OK;
	case 2:
		info->name = "octreeResolution";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_OctreeImage *) node)->octreeResolution;
		return GF_OK;
	case 3:
		info->name = "voxelImageIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_OctreeImage *) node)->voxelImageIndex;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 OctreeImage_get_field_index_by_name(char *name)
{
	if (!strcmp("images", name)) return 0;
	if (!strcmp("octree", name)) return 1;
	if (!strcmp("octreeResolution", name)) return 2;
	if (!strcmp("voxelImageIndex", name)) return 3;
	return -1;
	}
static Bool OctreeImage_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(255);
		return 1;
	case 3:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(255);
		return 1;
	default:
		return 0;
	}
}



GF_Node *OctreeImage_Create()
{
	M_OctreeImage *p;
	GF_SAFEALLOC(p, M_OctreeImage);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_OctreeImage);

	/*default field values*/
	p->octreeResolution = 256;
	return (GF_Node *)p;
}


/*
	XXParticles Node deletion
*/

static void XXParticles_Del(GF_Node *node)
{
	M_XXParticles *p = (M_XXParticles *) node;
	gf_node_unregister_children((GF_Node *) p, p->influences);	
	gf_node_unregister((GF_Node *) p->init, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->primitive, (GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 XXParticles_Def2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
static const u16 XXParticles_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};
static const u16 XXParticles_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24};

static u32 XXParticles_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 25;
	case GF_SG_FIELD_CODING_DEF: return 25;
	case GF_SG_FIELD_CODING_OUT: return 25;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 25;
	}
}

static GF_Err XXParticles_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = XXParticles_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = XXParticles_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = XXParticles_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err XXParticles_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "creationRate";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XXParticles *) node)->creationRate;
		return GF_OK;
	case 1:
		info->name = "creationRateVariation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XXParticles *) node)->creationRateVariation;
		return GF_OK;
	case 2:
		info->name = "emitAlpha";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XXParticles *) node)->emitAlpha;
		return GF_OK;
	case 3:
		info->name = "emitColor";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFCOLOR;
		info->far_ptr = & ((M_XXParticles *) node)->emitColor;
		return GF_OK;
	case 4:
		info->name = "emitColorVariation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFCOLOR;
		info->far_ptr = & ((M_XXParticles *) node)->emitColorVariation;
		return GF_OK;
	case 5:
		info->name = "emitterPosition";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_XXParticles *) node)->emitterPosition;
		return GF_OK;
	case 6:
		info->name = "emitVelocity";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_XXParticles *) node)->emitVelocity;
		return GF_OK;
	case 7:
		info->name = "emitVelocityVariation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_XXParticles *) node)->emitVelocityVariation;
		return GF_OK;
	case 8:
		info->name = "enabled";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_XXParticles *) node)->enabled;
		return GF_OK;
	case 9:
		info->name = "fadeAlpha";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XXParticles *) node)->fadeAlpha;
		return GF_OK;
	case 10:
		info->name = "fadeColor";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFCOLOR;
		info->far_ptr = & ((M_XXParticles *) node)->fadeColor;
		return GF_OK;
	case 11:
		info->name = "fadeRate";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XXParticles *) node)->fadeRate;
		return GF_OK;
	case 12:
		info->name = "force";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_XXParticles *) node)->force;
		return GF_OK;
	case 13:
		info->name = "influences";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFInfluenceNode;
		info->far_ptr = & ((M_XXParticles *)node)->influences;
		return GF_OK;
	case 14:
		info->name = "init";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFWorldNode;
		info->far_ptr = & ((M_XXParticles *)node)->init;
		return GF_OK;
	case 15:
		info->name = "maxLifeTime";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_XXParticles *) node)->maxLifeTime;
		return GF_OK;
	case 16:
		info->name = "maxLifeTimeVariation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XXParticles *) node)->maxLifeTimeVariation;
		return GF_OK;
	case 17:
		info->name = "maxParticles";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_XXParticles *) node)->maxParticles;
		return GF_OK;
	case 18:
		info->name = "minRange";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XXParticles *) node)->minRange;
		return GF_OK;
	case 19:
		info->name = "maxRange";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XXParticles *) node)->maxRange;
		return GF_OK;
	case 20:
		info->name = "primitive";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFWorldNode;
		info->far_ptr = & ((M_XXParticles *)node)->primitive;
		return GF_OK;
	case 21:
		info->name = "primitiveType";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_XXParticles *) node)->primitiveType;
		return GF_OK;
	case 22:
		info->name = "particleRadius";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XXParticles *) node)->particleRadius;
		return GF_OK;
	case 23:
		info->name = "particleRadiusRate";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XXParticles *) node)->particleRadiusRate;
		return GF_OK;
	case 24:
		info->name = "particleRadiusVariation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XXParticles *) node)->particleRadiusVariation;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 XXParticles_get_field_index_by_name(char *name)
{
	if (!strcmp("creationRate", name)) return 0;
	if (!strcmp("creationRateVariation", name)) return 1;
	if (!strcmp("emitAlpha", name)) return 2;
	if (!strcmp("emitColor", name)) return 3;
	if (!strcmp("emitColorVariation", name)) return 4;
	if (!strcmp("emitterPosition", name)) return 5;
	if (!strcmp("emitVelocity", name)) return 6;
	if (!strcmp("emitVelocityVariation", name)) return 7;
	if (!strcmp("enabled", name)) return 8;
	if (!strcmp("fadeAlpha", name)) return 9;
	if (!strcmp("fadeColor", name)) return 10;
	if (!strcmp("fadeRate", name)) return 11;
	if (!strcmp("force", name)) return 12;
	if (!strcmp("influences", name)) return 13;
	if (!strcmp("init", name)) return 14;
	if (!strcmp("maxLifeTime", name)) return 15;
	if (!strcmp("maxLifeTimeVariation", name)) return 16;
	if (!strcmp("maxParticles", name)) return 17;
	if (!strcmp("minRange", name)) return 18;
	if (!strcmp("maxRange", name)) return 19;
	if (!strcmp("primitive", name)) return 20;
	if (!strcmp("primitiveType", name)) return 21;
	if (!strcmp("particleRadius", name)) return 22;
	if (!strcmp("particleRadiusRate", name)) return 23;
	if (!strcmp("particleRadiusVariation", name)) return 24;
	return -1;
	}
static Bool XXParticles_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *XXParticles_Create()
{
	M_XXParticles *p;
	GF_SAFEALLOC(p, M_XXParticles);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_XXParticles);

	/*default field values*/
	p->creationRate = FLT2FIX(500);
	p->creationRateVariation = FLT2FIX(0);
	p->emitAlpha = FLT2FIX(1.0);
	p->emitColor.red = FLT2FIX(1);
	p->emitColor.green = FLT2FIX(1);
	p->emitColor.blue = FLT2FIX(1);
	p->emitColorVariation.red = FLT2FIX(0);
	p->emitColorVariation.green = FLT2FIX(0);
	p->emitColorVariation.blue = FLT2FIX(0);
	p->emitterPosition.x = FLT2FIX(0);
	p->emitterPosition.y = FLT2FIX(3);
	p->emitterPosition.z = FLT2FIX(0);
	p->emitVelocity.x = FLT2FIX(0);
	p->emitVelocity.y = FLT2FIX(0);
	p->emitVelocity.z = FLT2FIX(0);
	p->emitVelocityVariation.x = FLT2FIX(1);
	p->emitVelocityVariation.y = FLT2FIX(1);
	p->emitVelocityVariation.z = FLT2FIX(1);
	p->enabled = 1;
	p->fadeAlpha = FLT2FIX(1.0);
	p->fadeColor.red = FLT2FIX(0.25);
	p->fadeColor.green = FLT2FIX(0.25);
	p->fadeColor.blue = FLT2FIX(0.25);
	p->fadeRate = FLT2FIX(0.25);
	p->force.x = FLT2FIX(0);
	p->force.y = FLT2FIX(-9.8);
	p->force.z = FLT2FIX(0);
	p->maxLifeTime = 5;
	p->maxLifeTimeVariation = FLT2FIX(0);
	p->maxParticles = 500;
	p->minRange = FLT2FIX(1);
	p->maxRange = FLT2FIX(-1);
	p->primitiveType = 2;
	p->particleRadius = FLT2FIX(0.1);
	p->particleRadiusRate = FLT2FIX(0);
	p->particleRadiusVariation = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	XXParticleInitBox Node deletion
*/

static void XXParticleInitBox_Del(GF_Node *node)
{
	M_XXParticleInitBox *p = (M_XXParticleInitBox *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 XXParticleInitBox_Def2All[] = { 0, 1};
static const u16 XXParticleInitBox_In2All[] = { 0, 1};
static const u16 XXParticleInitBox_Out2All[] = { 0, 1};

static u32 XXParticleInitBox_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 2;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 2;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 2;
	}
}

static GF_Err XXParticleInitBox_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = XXParticleInitBox_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = XXParticleInitBox_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = XXParticleInitBox_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err XXParticleInitBox_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "falloff";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XXParticleInitBox *) node)->falloff;
		return GF_OK;
	case 1:
		info->name = "size";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_XXParticleInitBox *) node)->size;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 XXParticleInitBox_get_field_index_by_name(char *name)
{
	if (!strcmp("falloff", name)) return 0;
	if (!strcmp("size", name)) return 1;
	return -1;
	}
static Bool XXParticleInitBox_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *XXParticleInitBox_Create()
{
	M_XXParticleInitBox *p;
	GF_SAFEALLOC(p, M_XXParticleInitBox);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_XXParticleInitBox);

	/*default field values*/
	p->falloff = FLT2FIX(0);
	p->size.x = FLT2FIX(1);
	p->size.y = FLT2FIX(1);
	p->size.z = FLT2FIX(1);
	return (GF_Node *)p;
}


/*
	XXPlanarObstacle Node deletion
*/

static void XXPlanarObstacle_Del(GF_Node *node)
{
	M_XXPlanarObstacle *p = (M_XXPlanarObstacle *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 XXPlanarObstacle_Def2All[] = { 0, 1, 2, 3};
static const u16 XXPlanarObstacle_In2All[] = { 0, 1, 2, 3};
static const u16 XXPlanarObstacle_Out2All[] = { 0, 1, 2, 3};

static u32 XXPlanarObstacle_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 4;
	case GF_SG_FIELD_CODING_OUT: return 4;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err XXPlanarObstacle_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = XXPlanarObstacle_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = XXPlanarObstacle_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = XXPlanarObstacle_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err XXPlanarObstacle_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "distance";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_XXPlanarObstacle *) node)->distance;
		return GF_OK;
	case 1:
		info->name = "normal";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_XXPlanarObstacle *) node)->normal;
		return GF_OK;
	case 2:
		info->name = "reflection";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XXPlanarObstacle *) node)->reflection;
		return GF_OK;
	case 3:
		info->name = "absorption";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XXPlanarObstacle *) node)->absorption;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 XXPlanarObstacle_get_field_index_by_name(char *name)
{
	if (!strcmp("distance", name)) return 0;
	if (!strcmp("normal", name)) return 1;
	if (!strcmp("reflection", name)) return 2;
	if (!strcmp("absorption", name)) return 3;
	return -1;
	}
static Bool XXPlanarObstacle_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *XXPlanarObstacle_Create()
{
	M_XXPlanarObstacle *p;
	GF_SAFEALLOC(p, M_XXPlanarObstacle);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_XXPlanarObstacle);

	/*default field values*/
	p->distance.x = FLT2FIX(0);
	p->distance.y = FLT2FIX(0);
	p->distance.z = FLT2FIX(0);
	p->normal.x = FLT2FIX(0);
	p->normal.y = FLT2FIX(1);
	p->normal.z = FLT2FIX(0);
	p->reflection = FLT2FIX(0);
	p->absorption = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	XXPointAttractor Node deletion
*/

static void XXPointAttractor_Del(GF_Node *node)
{
	M_XXPointAttractor *p = (M_XXPointAttractor *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 XXPointAttractor_Def2All[] = { 0, 1, 2, 3};
static const u16 XXPointAttractor_In2All[] = { 0, 1, 2, 3};
static const u16 XXPointAttractor_Out2All[] = { 0, 1, 2, 3};

static u32 XXPointAttractor_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 4;
	case GF_SG_FIELD_CODING_OUT: return 4;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err XXPointAttractor_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = XXPointAttractor_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = XXPointAttractor_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = XXPointAttractor_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err XXPointAttractor_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "innerRadius";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XXPointAttractor *) node)->innerRadius;
		return GF_OK;
	case 1:
		info->name = "outerRadius";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XXPointAttractor *) node)->outerRadius;
		return GF_OK;
	case 2:
		info->name = "position";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_XXPointAttractor *) node)->position;
		return GF_OK;
	case 3:
		info->name = "rate";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XXPointAttractor *) node)->rate;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 XXPointAttractor_get_field_index_by_name(char *name)
{
	if (!strcmp("innerRadius", name)) return 0;
	if (!strcmp("outerRadius", name)) return 1;
	if (!strcmp("position", name)) return 2;
	if (!strcmp("rate", name)) return 3;
	return -1;
	}
static Bool XXPointAttractor_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *XXPointAttractor_Create()
{
	M_XXPointAttractor *p;
	GF_SAFEALLOC(p, M_XXPointAttractor);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_XXPointAttractor);

	/*default field values*/
	p->innerRadius = FLT2FIX(10);
	p->outerRadius = FLT2FIX(100);
	p->position.x = FLT2FIX(0);
	p->position.y = FLT2FIX(0);
	p->position.z = FLT2FIX(0);
	p->rate = FLT2FIX(1);
	return (GF_Node *)p;
}


/*
	PointTexture Node deletion
*/

static void PointTexture_Del(GF_Node *node)
{
	M_PointTexture *p = (M_PointTexture *) node;
	gf_sg_mfcolor_del(p->color);
	gf_sg_mfint32_del(p->depth);
	gf_node_free((GF_Node *) p);
}

static const u16 PointTexture_Def2All[] = { 0, 1, 2, 3, 4};

static u32 PointTexture_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 0;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 0;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 5;
	}
}

static GF_Err PointTexture_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_DEF:
		*allField = PointTexture_Def2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err PointTexture_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "color";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFCOLOR;
		info->far_ptr = & ((M_PointTexture *) node)->color;
		return GF_OK;
	case 1:
		info->name = "depth";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_PointTexture *) node)->depth;
		return GF_OK;
	case 2:
		info->name = "depthNbBits";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_PointTexture *) node)->depthNbBits;
		return GF_OK;
	case 3:
		info->name = "height";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_PointTexture *) node)->height;
		return GF_OK;
	case 4:
		info->name = "width";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_PointTexture *) node)->width;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 PointTexture_get_field_index_by_name(char *name)
{
	if (!strcmp("color", name)) return 0;
	if (!strcmp("depth", name)) return 1;
	if (!strcmp("depthNbBits", name)) return 2;
	if (!strcmp("height", name)) return 3;
	if (!strcmp("width", name)) return 4;
	return -1;
	}
static Bool PointTexture_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 2:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 5;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(31);
		return 1;
	default:
		return 0;
	}
}



GF_Node *PointTexture_Create()
{
	M_PointTexture *p;
	GF_SAFEALLOC(p, M_PointTexture);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_PointTexture);

	/*default field values*/
	p->depthNbBits = 7;
	p->height = 256;
	p->width = 256;
	return (GF_Node *)p;
}


/*
	PositionAnimator Node deletion
*/

static void PositionAnimator_Del(GF_Node *node)
{
	M_PositionAnimator *p = (M_PositionAnimator *) node;
	gf_sg_mffloat_del(p->key);
	gf_sg_mfrotation_del(p->keyOrientation);
	gf_sg_mfvec2f_del(p->keySpline);
	gf_sg_mfvec3f_del(p->keyValue);
	gf_sg_mffloat_del(p->weight);
	gf_node_free((GF_Node *) p);
}

static const u16 PositionAnimator_Def2All[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9};
static const u16 PositionAnimator_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
static const u16 PositionAnimator_Out2All[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

static u32 PositionAnimator_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 10;
	case GF_SG_FIELD_CODING_DEF: return 9;
	case GF_SG_FIELD_CODING_OUT: return 12;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 13;
	}
}

static GF_Err PositionAnimator_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = PositionAnimator_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = PositionAnimator_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = PositionAnimator_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err PositionAnimator_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_fraction";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_PositionAnimator *)node)->on_set_fraction;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_PositionAnimator *) node)->set_fraction;
		return GF_OK;
	case 1:
		info->name = "fromTo";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_PositionAnimator *) node)->fromTo;
		return GF_OK;
	case 2:
		info->name = "key";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_PositionAnimator *) node)->key;
		return GF_OK;
	case 3:
		info->name = "keyOrientation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFROTATION;
		info->far_ptr = & ((M_PositionAnimator *) node)->keyOrientation;
		return GF_OK;
	case 4:
		info->name = "keyType";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_PositionAnimator *) node)->keyType;
		return GF_OK;
	case 5:
		info->name = "keySpline";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC2F;
		info->far_ptr = & ((M_PositionAnimator *) node)->keySpline;
		return GF_OK;
	case 6:
		info->name = "keyValue";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC3F;
		info->far_ptr = & ((M_PositionAnimator *) node)->keyValue;
		return GF_OK;
	case 7:
		info->name = "keyValueType";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_PositionAnimator *) node)->keyValueType;
		return GF_OK;
	case 8:
		info->name = "offset";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_PositionAnimator *) node)->offset;
		return GF_OK;
	case 9:
		info->name = "weight";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_PositionAnimator *) node)->weight;
		return GF_OK;
	case 10:
		info->name = "endValue";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_PositionAnimator *) node)->endValue;
		return GF_OK;
	case 11:
		info->name = "rotation_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFROTATION;
		info->far_ptr = & ((M_PositionAnimator *) node)->rotation_changed;
		return GF_OK;
	case 12:
		info->name = "value_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_PositionAnimator *) node)->value_changed;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 PositionAnimator_get_field_index_by_name(char *name)
{
	if (!strcmp("set_fraction", name)) return 0;
	if (!strcmp("fromTo", name)) return 1;
	if (!strcmp("key", name)) return 2;
	if (!strcmp("keyOrientation", name)) return 3;
	if (!strcmp("keyType", name)) return 4;
	if (!strcmp("keySpline", name)) return 5;
	if (!strcmp("keyValue", name)) return 6;
	if (!strcmp("keyValueType", name)) return 7;
	if (!strcmp("offset", name)) return 8;
	if (!strcmp("weight", name)) return 9;
	if (!strcmp("endValue", name)) return 10;
	if (!strcmp("rotation_changed", name)) return 11;
	if (!strcmp("value_changed", name)) return 12;
	return -1;
	}
static Bool PositionAnimator_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 8;
		return 1;
	case 2:
		*AType = 0;
		*QType = 8;
		return 1;
	case 5:
		*AType = 0;
		*QType = 8;
		return 1;
	case 6:
		*AType = 0;
		*QType = 4;
		return 1;
	case 8:
		*AType = 0;
		*QType = 1;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *PositionAnimator_Create()
{
	M_PositionAnimator *p;
	GF_SAFEALLOC(p, M_PositionAnimator);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_PositionAnimator);

	/*default field values*/
	p->fromTo.x = FLT2FIX(0);
	p->fromTo.y = FLT2FIX(1);
	p->keyType = 0;
	p->keySpline.vals = (SFVec2f*)malloc(sizeof(SFVec2f)*2);
	p->keySpline.count = 2;
	p->keySpline.vals[0].x = FLT2FIX(0);
	p->keySpline.vals[0].y = FLT2FIX(0);
	p->keySpline.vals[1].x = FLT2FIX(1);
	p->keySpline.vals[1].y = FLT2FIX(1);
	p->keyValueType = 0;
	p->offset.x = FLT2FIX(0);
	p->offset.y = FLT2FIX(0);
	p->offset.z = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	PositionAnimator2D Node deletion
*/

static void PositionAnimator2D_Del(GF_Node *node)
{
	M_PositionAnimator2D *p = (M_PositionAnimator2D *) node;
	gf_sg_mffloat_del(p->key);
	gf_sg_mfvec2f_del(p->keySpline);
	gf_sg_mfvec2f_del(p->keyValue);
	gf_sg_mffloat_del(p->weight);
	gf_node_free((GF_Node *) p);
}

static const u16 PositionAnimator2D_Def2All[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9};
static const u16 PositionAnimator2D_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
static const u16 PositionAnimator2D_Out2All[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};

static u32 PositionAnimator2D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 10;
	case GF_SG_FIELD_CODING_DEF: return 9;
	case GF_SG_FIELD_CODING_OUT: return 12;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 13;
	}
}

static GF_Err PositionAnimator2D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = PositionAnimator2D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = PositionAnimator2D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = PositionAnimator2D_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err PositionAnimator2D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_fraction";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_PositionAnimator2D *)node)->on_set_fraction;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_PositionAnimator2D *) node)->set_fraction;
		return GF_OK;
	case 1:
		info->name = "fromTo";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_PositionAnimator2D *) node)->fromTo;
		return GF_OK;
	case 2:
		info->name = "key";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_PositionAnimator2D *) node)->key;
		return GF_OK;
	case 3:
		info->name = "keyOrientation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_PositionAnimator2D *) node)->keyOrientation;
		return GF_OK;
	case 4:
		info->name = "keyType";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_PositionAnimator2D *) node)->keyType;
		return GF_OK;
	case 5:
		info->name = "keySpline";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC2F;
		info->far_ptr = & ((M_PositionAnimator2D *) node)->keySpline;
		return GF_OK;
	case 6:
		info->name = "keyValue";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC2F;
		info->far_ptr = & ((M_PositionAnimator2D *) node)->keyValue;
		return GF_OK;
	case 7:
		info->name = "keyValueType";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_PositionAnimator2D *) node)->keyValueType;
		return GF_OK;
	case 8:
		info->name = "offset";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_PositionAnimator2D *) node)->offset;
		return GF_OK;
	case 9:
		info->name = "weight";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_PositionAnimator2D *) node)->weight;
		return GF_OK;
	case 10:
		info->name = "endValue";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_PositionAnimator2D *) node)->endValue;
		return GF_OK;
	case 11:
		info->name = "rotation_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_PositionAnimator2D *) node)->rotation_changed;
		return GF_OK;
	case 12:
		info->name = "value_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_PositionAnimator2D *) node)->value_changed;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 PositionAnimator2D_get_field_index_by_name(char *name)
{
	if (!strcmp("set_fraction", name)) return 0;
	if (!strcmp("fromTo", name)) return 1;
	if (!strcmp("key", name)) return 2;
	if (!strcmp("keyOrientation", name)) return 3;
	if (!strcmp("keyType", name)) return 4;
	if (!strcmp("keySpline", name)) return 5;
	if (!strcmp("keyValue", name)) return 6;
	if (!strcmp("keyValueType", name)) return 7;
	if (!strcmp("offset", name)) return 8;
	if (!strcmp("weight", name)) return 9;
	if (!strcmp("endValue", name)) return 10;
	if (!strcmp("rotation_changed", name)) return 11;
	if (!strcmp("value_changed", name)) return 12;
	return -1;
	}
static Bool PositionAnimator2D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 8;
		return 1;
	case 2:
		*AType = 0;
		*QType = 8;
		return 1;
	case 5:
		*AType = 0;
		*QType = 8;
		return 1;
	case 6:
		*AType = 0;
		*QType = 4;
		return 1;
	case 8:
		*AType = 0;
		*QType = 2;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *PositionAnimator2D_Create()
{
	M_PositionAnimator2D *p;
	GF_SAFEALLOC(p, M_PositionAnimator2D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_PositionAnimator2D);

	/*default field values*/
	p->fromTo.x = FLT2FIX(0);
	p->fromTo.y = FLT2FIX(1);
	p->keyOrientation = 0;
	p->keyType = 0;
	p->keySpline.vals = (SFVec2f*)malloc(sizeof(SFVec2f)*2);
	p->keySpline.count = 2;
	p->keySpline.vals[0].x = FLT2FIX(0);
	p->keySpline.vals[0].y = FLT2FIX(0);
	p->keySpline.vals[1].x = FLT2FIX(1);
	p->keySpline.vals[1].y = FLT2FIX(1);
	p->keyValueType = 0;
	p->offset.x = FLT2FIX(0);
	p->offset.y = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	PositionInterpolator4D Node deletion
*/

static void PositionInterpolator4D_Del(GF_Node *node)
{
	M_PositionInterpolator4D *p = (M_PositionInterpolator4D *) node;
	gf_sg_mffloat_del(p->key);
	gf_sg_mfvec4f_del(p->keyValue);
	gf_node_free((GF_Node *) p);
}

static const u16 PositionInterpolator4D_Def2All[] = { 1, 2};
static const u16 PositionInterpolator4D_In2All[] = { 0, 1, 2};
static const u16 PositionInterpolator4D_Out2All[] = { 1, 2, 3};

static u32 PositionInterpolator4D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err PositionInterpolator4D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = PositionInterpolator4D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = PositionInterpolator4D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = PositionInterpolator4D_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err PositionInterpolator4D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_fraction";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_PositionInterpolator4D *)node)->on_set_fraction;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_PositionInterpolator4D *) node)->set_fraction;
		return GF_OK;
	case 1:
		info->name = "key";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_PositionInterpolator4D *) node)->key;
		return GF_OK;
	case 2:
		info->name = "keyValue";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC4F;
		info->far_ptr = & ((M_PositionInterpolator4D *) node)->keyValue;
		return GF_OK;
	case 3:
		info->name = "value_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFVEC4F;
		info->far_ptr = & ((M_PositionInterpolator4D *) node)->value_changed;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 PositionInterpolator4D_get_field_index_by_name(char *name)
{
	if (!strcmp("set_fraction", name)) return 0;
	if (!strcmp("key", name)) return 1;
	if (!strcmp("keyValue", name)) return 2;
	if (!strcmp("value_changed", name)) return 3;
	return -1;
	}
static Bool PositionInterpolator4D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 2:
		*AType = 0;
		*QType = 15;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *PositionInterpolator4D_Create()
{
	M_PositionInterpolator4D *p;
	GF_SAFEALLOC(p, M_PositionInterpolator4D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_PositionInterpolator4D);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	ProceduralTexture Node deletion
*/

static void ProceduralTexture_Del(GF_Node *node)
{
	M_ProceduralTexture *p = (M_ProceduralTexture *) node;
	gf_sg_mfvec2f_del(p->aWarpmap);
	gf_sg_mffloat_del(p->aWeights);
	gf_sg_mfvec2f_del(p->bWarpmap);
	gf_sg_mffloat_del(p->bWeights);
	gf_sg_mfcolor_del(p->color);
	gf_sg_mfvec2f_del(p->xWarpmap);
	gf_sg_mfvec2f_del(p->yWarpmap);
	gf_sg_sfimage_del(p->image_changed);
	gf_node_free((GF_Node *) p);
}

static const u16 ProceduralTexture_Def2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
static const u16 ProceduralTexture_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18};
static const u16 ProceduralTexture_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19};

static u32 ProceduralTexture_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 19;
	case GF_SG_FIELD_CODING_DEF: return 19;
	case GF_SG_FIELD_CODING_OUT: return 20;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 20;
	}
}

static GF_Err ProceduralTexture_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = ProceduralTexture_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = ProceduralTexture_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = ProceduralTexture_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err ProceduralTexture_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "aSmooth";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_ProceduralTexture *) node)->aSmooth;
		return GF_OK;
	case 1:
		info->name = "aWarpmap";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC2F;
		info->far_ptr = & ((M_ProceduralTexture *) node)->aWarpmap;
		return GF_OK;
	case 2:
		info->name = "aWeights";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_ProceduralTexture *) node)->aWeights;
		return GF_OK;
	case 3:
		info->name = "bSmooth";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_ProceduralTexture *) node)->bSmooth;
		return GF_OK;
	case 4:
		info->name = "bWarpmap";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC2F;
		info->far_ptr = & ((M_ProceduralTexture *) node)->bWarpmap;
		return GF_OK;
	case 5:
		info->name = "bWeights";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_ProceduralTexture *) node)->bWeights;
		return GF_OK;
	case 6:
		info->name = "cellWidth";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_ProceduralTexture *) node)->cellWidth;
		return GF_OK;
	case 7:
		info->name = "cellHeight";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_ProceduralTexture *) node)->cellHeight;
		return GF_OK;
	case 8:
		info->name = "color";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFCOLOR;
		info->far_ptr = & ((M_ProceduralTexture *) node)->color;
		return GF_OK;
	case 9:
		info->name = "distortion";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ProceduralTexture *) node)->distortion;
		return GF_OK;
	case 10:
		info->name = "height";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_ProceduralTexture *) node)->height;
		return GF_OK;
	case 11:
		info->name = "roughness";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_ProceduralTexture *) node)->roughness;
		return GF_OK;
	case 12:
		info->name = "seed";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_ProceduralTexture *) node)->seed;
		return GF_OK;
	case 13:
		info->name = "type";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_ProceduralTexture *) node)->type;
		return GF_OK;
	case 14:
		info->name = "xSmooth";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_ProceduralTexture *) node)->xSmooth;
		return GF_OK;
	case 15:
		info->name = "xWarpmap";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC2F;
		info->far_ptr = & ((M_ProceduralTexture *) node)->xWarpmap;
		return GF_OK;
	case 16:
		info->name = "ySmooth";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_ProceduralTexture *) node)->ySmooth;
		return GF_OK;
	case 17:
		info->name = "yWarpmap";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC2F;
		info->far_ptr = & ((M_ProceduralTexture *) node)->yWarpmap;
		return GF_OK;
	case 18:
		info->name = "width";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_ProceduralTexture *) node)->width;
		return GF_OK;
	case 19:
		info->name = "image_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFIMAGE;
		info->far_ptr = & ((M_ProceduralTexture *) node)->image_changed;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 ProceduralTexture_get_field_index_by_name(char *name)
{
	if (!strcmp("aSmooth", name)) return 0;
	if (!strcmp("aWarpmap", name)) return 1;
	if (!strcmp("aWeights", name)) return 2;
	if (!strcmp("bSmooth", name)) return 3;
	if (!strcmp("bWarpmap", name)) return 4;
	if (!strcmp("bWeights", name)) return 5;
	if (!strcmp("cellWidth", name)) return 6;
	if (!strcmp("cellHeight", name)) return 7;
	if (!strcmp("color", name)) return 8;
	if (!strcmp("distortion", name)) return 9;
	if (!strcmp("height", name)) return 10;
	if (!strcmp("roughness", name)) return 11;
	if (!strcmp("seed", name)) return 12;
	if (!strcmp("type", name)) return 13;
	if (!strcmp("xSmooth", name)) return 14;
	if (!strcmp("xWarpmap", name)) return 15;
	if (!strcmp("ySmooth", name)) return 16;
	if (!strcmp("yWarpmap", name)) return 17;
	if (!strcmp("width", name)) return 18;
	if (!strcmp("image_changed", name)) return 19;
	return -1;
	}
static Bool ProceduralTexture_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 2;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 4:
		*AType = 0;
		*QType = 2;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX( 1);
		return 1;
	case 6:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(15);
		return 1;
	case 7:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(15);
		return 1;
	case 8:
		*AType = 0;
		*QType = 4;
		return 1;
	case 9:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 16;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 10:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 4;
		*b_min = FLT2FIX(1);
		*b_max = FLT2FIX(15);
		return 1;
	case 11:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(15);
		return 1;
	case 13:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 3;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(4);
		return 1;
	case 15:
		*AType = 0;
		*QType = 2;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 17:
		*AType = 0;
		*QType = 2;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 18:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 4;
		*b_min = FLT2FIX(1);
		*b_max = FLT2FIX(15);
		return 1;
	default:
		return 0;
	}
}



GF_Node *ProceduralTexture_Create()
{
	M_ProceduralTexture *p;
	GF_SAFEALLOC(p, M_ProceduralTexture);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_ProceduralTexture);

	/*default field values*/
	p->aWarpmap.vals = (SFVec2f*)malloc(sizeof(SFVec2f)*2);
	p->aWarpmap.count = 2;
	p->aWarpmap.vals[0].x = FLT2FIX(0);
	p->aWarpmap.vals[0].y = FLT2FIX(0);
	p->aWarpmap.vals[1].x = FLT2FIX(1);
	p->aWarpmap.vals[1].y = FLT2FIX(1);
	p->aWeights.vals = (SFFloat*)malloc(sizeof(SFFloat)*16);
	p->aWeights.count = 16;
	p->aWeights.vals[0] = FLT2FIX(0);
	p->aWeights.vals[1] = FLT2FIX(0);
	p->aWeights.vals[2] = FLT2FIX(0);
	p->aWeights.vals[3] = FLT2FIX(0);
	p->aWeights.vals[4] = FLT2FIX(0);
	p->aWeights.vals[5] = FLT2FIX(0);
	p->aWeights.vals[6] = FLT2FIX(0);
	p->aWeights.vals[7] = FLT2FIX(0);
	p->aWeights.vals[8] = FLT2FIX(0);
	p->aWeights.vals[9] = FLT2FIX(0);
	p->aWeights.vals[10] = FLT2FIX(0);
	p->aWeights.vals[11] = FLT2FIX(0);
	p->aWeights.vals[12] = FLT2FIX(1);
	p->aWeights.vals[13] = FLT2FIX(0);
	p->aWeights.vals[14] = FLT2FIX(0);
	p->aWeights.vals[15] = FLT2FIX(0);
	p->bWarpmap.vals = (SFVec2f*)malloc(sizeof(SFVec2f)*2);
	p->bWarpmap.count = 2;
	p->bWarpmap.vals[0].x = FLT2FIX(0);
	p->bWarpmap.vals[0].y = FLT2FIX(0);
	p->bWarpmap.vals[1].x = FLT2FIX(1);
	p->bWarpmap.vals[1].y = FLT2FIX(1);
	p->bWeights.vals = (SFFloat*)malloc(sizeof(SFFloat)*16);
	p->bWeights.count = 16;
	p->bWeights.vals[0] = FLT2FIX(0);
	p->bWeights.vals[1] = FLT2FIX(0);
	p->bWeights.vals[2] = FLT2FIX(0);
	p->bWeights.vals[3] = FLT2FIX(0);
	p->bWeights.vals[4] = FLT2FIX(0);
	p->bWeights.vals[5] = FLT2FIX(1);
	p->bWeights.vals[6] = FLT2FIX(0);
	p->bWeights.vals[7] = FLT2FIX(0);
	p->bWeights.vals[8] = FLT2FIX(0);
	p->bWeights.vals[9] = FLT2FIX(0);
	p->bWeights.vals[10] = FLT2FIX(0);
	p->bWeights.vals[11] = FLT2FIX(0);
	p->bWeights.vals[12] = FLT2FIX(0);
	p->bWeights.vals[13] = FLT2FIX(0);
	p->bWeights.vals[14] = FLT2FIX(0);
	p->bWeights.vals[15] = FLT2FIX(0);
	p->cellWidth = 4;
	p->cellHeight = 4;
	p->color.vals = (SFColor*)malloc(sizeof(SFColor)*4);
	p->color.count = 4;
	p->color.vals[0].red = FLT2FIX(0.3);
	p->color.vals[0].green = FLT2FIX(0.698);
	p->color.vals[0].blue = FLT2FIX(1);
	p->color.vals[1].red = FLT2FIX(0.8);
	p->color.vals[1].green = FLT2FIX(0.8);
	p->color.vals[1].blue = FLT2FIX(0.8);
	p->color.vals[2].red = FLT2FIX(1);
	p->color.vals[2].green = FLT2FIX(1);
	p->color.vals[2].blue = FLT2FIX(1);
	p->color.vals[3].red = FLT2FIX(0);
	p->color.vals[3].green = FLT2FIX(0);
	p->color.vals[3].blue = FLT2FIX(0);
	p->distortion = FLT2FIX(0);
	p->height = 7;
	p->roughness = 0;
	p->seed = 129093;
	p->type = 0;
	p->width = 7;
	return (GF_Node *)p;
}


/*
	Quadric Node deletion
*/

static void Quadric_Del(GF_Node *node)
{
	M_Quadric *p = (M_Quadric *) node;
	gf_sg_mfint32_del(p->densities);
	gf_node_free((GF_Node *) p);
}

static const u16 Quadric_Def2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
static const u16 Quadric_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
static const u16 Quadric_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
static const u16 Quadric_Dyn2All[] = { 0, 3, 4, 5, 6, 7, 8};

static u32 Quadric_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 10;
	case GF_SG_FIELD_CODING_DEF: return 10;
	case GF_SG_FIELD_CODING_OUT: return 10;
	case GF_SG_FIELD_CODING_DYN: return 7;
	default:
		return 10;
	}
}

static GF_Err Quadric_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Quadric_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Quadric_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Quadric_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Quadric_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Quadric_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "bboxSize";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_Quadric *) node)->bboxSize;
		return GF_OK;
	case 1:
		info->name = "densities";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_Quadric *) node)->densities;
		return GF_OK;
	case 2:
		info->name = "dual";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Quadric *) node)->dual;
		return GF_OK;
	case 3:
		info->name = "P0";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC4F;
		info->far_ptr = & ((M_Quadric *) node)->P0;
		return GF_OK;
	case 4:
		info->name = "P1";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC4F;
		info->far_ptr = & ((M_Quadric *) node)->P1;
		return GF_OK;
	case 5:
		info->name = "P2";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC4F;
		info->far_ptr = & ((M_Quadric *) node)->P2;
		return GF_OK;
	case 6:
		info->name = "P3";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC4F;
		info->far_ptr = & ((M_Quadric *) node)->P3;
		return GF_OK;
	case 7:
		info->name = "P4";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC4F;
		info->far_ptr = & ((M_Quadric *) node)->P4;
		return GF_OK;
	case 8:
		info->name = "P5";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC4F;
		info->far_ptr = & ((M_Quadric *) node)->P5;
		return GF_OK;
	case 9:
		info->name = "solid";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Quadric *) node)->solid;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Quadric_get_field_index_by_name(char *name)
{
	if (!strcmp("bboxSize", name)) return 0;
	if (!strcmp("densities", name)) return 1;
	if (!strcmp("dual", name)) return 2;
	if (!strcmp("P0", name)) return 3;
	if (!strcmp("P1", name)) return 4;
	if (!strcmp("P2", name)) return 5;
	if (!strcmp("P3", name)) return 6;
	if (!strcmp("P4", name)) return 7;
	if (!strcmp("P5", name)) return 8;
	if (!strcmp("solid", name)) return 9;
	return -1;
	}
static Bool Quadric_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 11;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 3:
		*AType = 15;
		*QType = 15;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 4:
		*AType = 15;
		*QType = 15;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 5:
		*AType = 15;
		*QType = 15;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 6:
		*AType = 15;
		*QType = 15;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 7:
		*AType = 15;
		*QType = 15;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 8:
		*AType = 15;
		*QType = 15;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Quadric_Create()
{
	M_Quadric *p;
	GF_SAFEALLOC(p, M_Quadric);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Quadric);

	/*default field values*/
	p->bboxSize.x = FLT2FIX(2);
	p->bboxSize.y = FLT2FIX(2);
	p->bboxSize.z = FLT2FIX(2);
	p->P0.x = FLT2FIX(-1);
	p->P0.y = FLT2FIX(0);
	p->P0.z = FLT2FIX(0);
	p->P0.q = FLT2FIX(1);
	p->P1.x = FLT2FIX(1);
	p->P1.y = FLT2FIX(0);
	p->P1.z = FLT2FIX(0);
	p->P1.q = FLT2FIX(1);
	p->P2.x = FLT2FIX(0);
	p->P2.y = FLT2FIX(1);
	p->P2.z = FLT2FIX(0);
	p->P2.q = FLT2FIX(0);
	p->P3.x = FLT2FIX(0);
	p->P3.y = FLT2FIX(0);
	p->P3.z = FLT2FIX(1);
	p->P3.q = FLT2FIX(0);
	p->P4.x = FLT2FIX(0);
	p->P4.y = FLT2FIX(1);
	p->P4.z = FLT2FIX(0);
	p->P4.q = FLT2FIX(1);
	p->P5.x = FLT2FIX(0);
	p->P5.y = FLT2FIX(0);
	p->P5.z = FLT2FIX(1);
	p->P5.q = FLT2FIX(1);
	return (GF_Node *)p;
}


/*
	SBBone Node deletion
*/

static void SBBone_Del(GF_Node *node)
{
	M_SBBone *p = (M_SBBone *) node;
	gf_sg_mffloat_del(p->ikPitchLimit);
	gf_sg_mffloat_del(p->ikRollLimit);
	gf_sg_mffloat_del(p->ikTxLimit);
	gf_sg_mffloat_del(p->ikTyLimit);
	gf_sg_mffloat_del(p->ikTzLimit);
	gf_sg_mffloat_del(p->ikYawLimit);
	gf_sg_mffloat_del(p->sectionInner);
	gf_sg_mffloat_del(p->sectionOuter);
	gf_sg_mffloat_del(p->sectionPosition);
	gf_sg_mfint32_del(p->skinCoordIndex);
	gf_sg_mffloat_del(p->skinCoordWeight);
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 SBBone_Def2All[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
static const u16 SBBone_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
static const u16 SBBone_Out2All[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23};
static const u16 SBBone_Dyn2All[] = { 3, 5, 14, 16, 17, 23};

static u32 SBBone_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 24;
	case GF_SG_FIELD_CODING_DEF: return 22;
	case GF_SG_FIELD_CODING_OUT: return 22;
	case GF_SG_FIELD_CODING_DYN: return 6;
	default:
		return 24;
	}
}

static GF_Err SBBone_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = SBBone_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = SBBone_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = SBBone_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = SBBone_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err SBBone_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_SBBone *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_SBBone *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_SBBone *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_SBBone *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "boneID";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_SBBone *) node)->boneID;
		return GF_OK;
	case 3:
		info->name = "center";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_SBBone *) node)->center;
		return GF_OK;
	case 4:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_SBBone *)node)->children;
		return GF_OK;
	case 5:
		info->name = "endpoint";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_SBBone *) node)->endpoint;
		return GF_OK;
	case 6:
		info->name = "falloff";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_SBBone *) node)->falloff;
		return GF_OK;
	case 7:
		info->name = "ikChainPosition";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_SBBone *) node)->ikChainPosition;
		return GF_OK;
	case 8:
		info->name = "ikPitchLimit";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_SBBone *) node)->ikPitchLimit;
		return GF_OK;
	case 9:
		info->name = "ikRollLimit";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_SBBone *) node)->ikRollLimit;
		return GF_OK;
	case 10:
		info->name = "ikTxLimit";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_SBBone *) node)->ikTxLimit;
		return GF_OK;
	case 11:
		info->name = "ikTyLimit";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_SBBone *) node)->ikTyLimit;
		return GF_OK;
	case 12:
		info->name = "ikTzLimit";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_SBBone *) node)->ikTzLimit;
		return GF_OK;
	case 13:
		info->name = "ikYawLimit";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_SBBone *) node)->ikYawLimit;
		return GF_OK;
	case 14:
		info->name = "rotation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFROTATION;
		info->far_ptr = & ((M_SBBone *) node)->rotation;
		return GF_OK;
	case 15:
		info->name = "rotationOrder";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_SBBone *) node)->rotationOrder;
		return GF_OK;
	case 16:
		info->name = "scale";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_SBBone *) node)->scale;
		return GF_OK;
	case 17:
		info->name = "scaleOrientation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFROTATION;
		info->far_ptr = & ((M_SBBone *) node)->scaleOrientation;
		return GF_OK;
	case 18:
		info->name = "sectionInner";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_SBBone *) node)->sectionInner;
		return GF_OK;
	case 19:
		info->name = "sectionOuter";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_SBBone *) node)->sectionOuter;
		return GF_OK;
	case 20:
		info->name = "sectionPosition";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_SBBone *) node)->sectionPosition;
		return GF_OK;
	case 21:
		info->name = "skinCoordIndex";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_SBBone *) node)->skinCoordIndex;
		return GF_OK;
	case 22:
		info->name = "skinCoordWeight";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_SBBone *) node)->skinCoordWeight;
		return GF_OK;
	case 23:
		info->name = "translation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_SBBone *) node)->translation;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 SBBone_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("boneID", name)) return 2;
	if (!strcmp("center", name)) return 3;
	if (!strcmp("children", name)) return 4;
	if (!strcmp("endpoint", name)) return 5;
	if (!strcmp("falloff", name)) return 6;
	if (!strcmp("ikChainPosition", name)) return 7;
	if (!strcmp("ikPitchLimit", name)) return 8;
	if (!strcmp("ikRollLimit", name)) return 9;
	if (!strcmp("ikTxLimit", name)) return 10;
	if (!strcmp("ikTyLimit", name)) return 11;
	if (!strcmp("ikTzLimit", name)) return 12;
	if (!strcmp("ikYawLimit", name)) return 13;
	if (!strcmp("rotation", name)) return 14;
	if (!strcmp("rotationOrder", name)) return 15;
	if (!strcmp("scale", name)) return 16;
	if (!strcmp("scaleOrientation", name)) return 17;
	if (!strcmp("sectionInner", name)) return 18;
	if (!strcmp("sectionOuter", name)) return 19;
	if (!strcmp("sectionPosition", name)) return 20;
	if (!strcmp("skinCoordIndex", name)) return 21;
	if (!strcmp("skinCoordWeight", name)) return 22;
	if (!strcmp("translation", name)) return 23;
	return -1;
	}
static Bool SBBone_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 2:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 10;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1023);
		return 1;
	case 3:
		*AType = 1;
		*QType = 1;
		return 1;
	case 5:
		*AType = 1;
		*QType = 1;
		return 1;
	case 6:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 3;
		*b_min = FLT2FIX(-1);
		*b_max = FLT2FIX(4);
		return 1;
	case 7:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 2;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(3);
		return 1;
	case 14:
		*AType = 10;
		*QType = 10;
		return 1;
	case 15:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 5;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(23);
		return 1;
	case 16:
		*AType = 11;
		*QType = 7;
		return 1;
	case 17:
		*AType = 10;
		*QType = 10;
		return 1;
	case 21:
		*AType = 0;
		*QType = 14;
		return 1;
	case 23:
		*AType = 1;
		*QType = 1;
		return 1;
	default:
		return 0;
	}
}



GF_Node *SBBone_Create()
{
	M_SBBone *p;
	GF_SAFEALLOC(p, M_SBBone);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_SBBone);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->boneID = 0;
	p->center.x = FLT2FIX(0);
	p->center.y = FLT2FIX(0);
	p->center.z = FLT2FIX(0);
	p->endpoint.x = FLT2FIX(0);
	p->endpoint.y = FLT2FIX(0);
	p->endpoint.z = FLT2FIX(1);
	p->falloff = 1;
	p->ikChainPosition = 0;
	p->rotation.x = FLT2FIX(0);
	p->rotation.y = FLT2FIX(0);
	p->rotation.z = FLT2FIX(1);
	p->rotation.q = FLT2FIX(0);
	p->rotationOrder = 0;
	p->scale.x = FLT2FIX(0);
	p->scale.y = FLT2FIX(0);
	p->scale.z = FLT2FIX(0);
	p->scaleOrientation.x = FLT2FIX(0);
	p->scaleOrientation.y = FLT2FIX(0);
	p->scaleOrientation.z = FLT2FIX(1);
	p->scaleOrientation.q = FLT2FIX(0);
	p->translation.x = FLT2FIX(0);
	p->translation.y = FLT2FIX(0);
	p->translation.z = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	SBMuscle Node deletion
*/

static void SBMuscle_Del(GF_Node *node)
{
	M_SBMuscle *p = (M_SBMuscle *) node;
	gf_node_unregister((GF_Node *) p->muscleCurve, (GF_Node *) p);	
	gf_sg_mfint32_del(p->skinCoordIndex);
	gf_sg_mffloat_del(p->skinCoordWeight);
	gf_node_free((GF_Node *) p);
}

static const u16 SBMuscle_Def2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 SBMuscle_In2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 SBMuscle_Out2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 SBMuscle_Dyn2All[] = { 3};

static u32 SBMuscle_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 6;
	case GF_SG_FIELD_CODING_DEF: return 6;
	case GF_SG_FIELD_CODING_OUT: return 6;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 6;
	}
}

static GF_Err SBMuscle_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = SBMuscle_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = SBMuscle_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = SBMuscle_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = SBMuscle_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err SBMuscle_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "falloff";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_SBMuscle *) node)->falloff;
		return GF_OK;
	case 1:
		info->name = "muscleCurve";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFGeometryNode;
		info->far_ptr = & ((M_SBMuscle *)node)->muscleCurve;
		return GF_OK;
	case 2:
		info->name = "muscleID";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_SBMuscle *) node)->muscleID;
		return GF_OK;
	case 3:
		info->name = "radius";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_SBMuscle *) node)->radius;
		return GF_OK;
	case 4:
		info->name = "skinCoordIndex";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_SBMuscle *) node)->skinCoordIndex;
		return GF_OK;
	case 5:
		info->name = "skinCoordWeight";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_SBMuscle *) node)->skinCoordWeight;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 SBMuscle_get_field_index_by_name(char *name)
{
	if (!strcmp("falloff", name)) return 0;
	if (!strcmp("muscleCurve", name)) return 1;
	if (!strcmp("muscleID", name)) return 2;
	if (!strcmp("radius", name)) return 3;
	if (!strcmp("skinCoordIndex", name)) return 4;
	if (!strcmp("skinCoordWeight", name)) return 5;
	return -1;
	}
static Bool SBMuscle_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 3;
		*b_min = FLT2FIX(-1);
		*b_max = FLT2FIX(4);
		return 1;
	case 2:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 10;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1023);
		return 1;
	case 3:
		*AType = 11;
		*QType = 7;
		return 1;
	case 4:
		*AType = 0;
		*QType = 14;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *SBMuscle_Create()
{
	M_SBMuscle *p;
	GF_SAFEALLOC(p, M_SBMuscle);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_SBMuscle);

	/*default field values*/
	p->falloff = 1;
	p->muscleID = 0;
	p->radius = 1;
	return (GF_Node *)p;
}


/*
	SBSegment Node deletion
*/

static void SBSegment_Del(GF_Node *node)
{
	M_SBSegment *p = (M_SBSegment *) node;
	gf_sg_mfvec3f_del(p->momentsOfInertia);
	gf_sg_sfstring_del(p->name);
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 SBSegment_Def2All[] = { 2, 3, 4, 5, 6};
static const u16 SBSegment_In2All[] = { 0, 1, 2, 3, 4, 5, 6};
static const u16 SBSegment_Out2All[] = { 2, 3, 4, 5, 6};
static const u16 SBSegment_Dyn2All[] = { 2};

static u32 SBSegment_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 7;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 5;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 7;
	}
}

static GF_Err SBSegment_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = SBSegment_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = SBSegment_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = SBSegment_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = SBSegment_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err SBSegment_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_SBSegment *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_SBSegment *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_SBSegment *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_SBSegment *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "centerOfMass";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_SBSegment *) node)->centerOfMass;
		return GF_OK;
	case 3:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_SBSegment *)node)->children;
		return GF_OK;
	case 4:
		info->name = "mass";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_SBSegment *) node)->mass;
		return GF_OK;
	case 5:
		info->name = "momentsOfInertia";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC3F;
		info->far_ptr = & ((M_SBSegment *) node)->momentsOfInertia;
		return GF_OK;
	case 6:
		info->name = "name";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_SBSegment *) node)->name;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 SBSegment_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("centerOfMass", name)) return 2;
	if (!strcmp("children", name)) return 3;
	if (!strcmp("mass", name)) return 4;
	if (!strcmp("momentsOfInertia", name)) return 5;
	if (!strcmp("name", name)) return 6;
	return -1;
	}
static Bool SBSegment_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 2:
		*AType = 1;
		*QType = 1;
		return 1;
	default:
		return 0;
	}
}



GF_Node *SBSegment_Create()
{
	M_SBSegment *p;
	GF_SAFEALLOC(p, M_SBSegment);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_SBSegment);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->centerOfMass.x = FLT2FIX(0);
	p->centerOfMass.y = FLT2FIX(0);
	p->centerOfMass.z = FLT2FIX(0);
	p->mass = FLT2FIX(0);
	p->momentsOfInertia.vals = (SFVec3f *)malloc(sizeof(SFVec3f)*3);
	p->momentsOfInertia.count = 3;
	p->momentsOfInertia.vals[0].x = FLT2FIX(0);
	p->momentsOfInertia.vals[0].y = FLT2FIX(0);
	p->momentsOfInertia.vals[0].z = FLT2FIX(0);
	p->momentsOfInertia.vals[1].x = FLT2FIX(0);
	p->momentsOfInertia.vals[1].y = FLT2FIX(0);
	p->momentsOfInertia.vals[1].z = FLT2FIX(0);
	p->momentsOfInertia.vals[2].x = FLT2FIX(0);
	p->momentsOfInertia.vals[2].y = FLT2FIX(0);
	p->momentsOfInertia.vals[2].z = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	SBSite Node deletion
*/

static void SBSite_Del(GF_Node *node)
{
	M_SBSite *p = (M_SBSite *) node;
	gf_sg_sfstring_del(p->name);
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 SBSite_Def2All[] = { 2, 3, 4, 5, 6, 7, 8};
static const u16 SBSite_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};
static const u16 SBSite_Out2All[] = { 2, 3, 4, 5, 6, 7, 8};
static const u16 SBSite_Dyn2All[] = { 2, 5, 6, 7, 8};

static u32 SBSite_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 9;
	case GF_SG_FIELD_CODING_DEF: return 7;
	case GF_SG_FIELD_CODING_OUT: return 7;
	case GF_SG_FIELD_CODING_DYN: return 5;
	default:
		return 9;
	}
}

static GF_Err SBSite_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = SBSite_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = SBSite_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = SBSite_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = SBSite_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err SBSite_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_SBSite *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_SBSite *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_SBSite *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_SBSite *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "center";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_SBSite *) node)->center;
		return GF_OK;
	case 3:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_SBSite *)node)->children;
		return GF_OK;
	case 4:
		info->name = "name";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_SBSite *) node)->name;
		return GF_OK;
	case 5:
		info->name = "rotation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFROTATION;
		info->far_ptr = & ((M_SBSite *) node)->rotation;
		return GF_OK;
	case 6:
		info->name = "scale";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_SBSite *) node)->scale;
		return GF_OK;
	case 7:
		info->name = "scaleOrientation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFROTATION;
		info->far_ptr = & ((M_SBSite *) node)->scaleOrientation;
		return GF_OK;
	case 8:
		info->name = "translation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_SBSite *) node)->translation;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 SBSite_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("center", name)) return 2;
	if (!strcmp("children", name)) return 3;
	if (!strcmp("name", name)) return 4;
	if (!strcmp("rotation", name)) return 5;
	if (!strcmp("scale", name)) return 6;
	if (!strcmp("scaleOrientation", name)) return 7;
	if (!strcmp("translation", name)) return 8;
	return -1;
	}
static Bool SBSite_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 2:
		*AType = 1;
		*QType = 1;
		return 1;
	case 5:
		*AType = 10;
		*QType = 10;
		return 1;
	case 6:
		*AType = 11;
		*QType = 7;
		return 1;
	case 7:
		*AType = 10;
		*QType = 10;
		return 1;
	case 8:
		*AType = 1;
		*QType = 1;
		return 1;
	default:
		return 0;
	}
}



GF_Node *SBSite_Create()
{
	M_SBSite *p;
	GF_SAFEALLOC(p, M_SBSite);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_SBSite);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->center.x = FLT2FIX(0);
	p->center.y = FLT2FIX(0);
	p->center.z = FLT2FIX(0);
	p->rotation.x = FLT2FIX(0);
	p->rotation.y = FLT2FIX(0);
	p->rotation.z = FLT2FIX(1);
	p->rotation.q = FLT2FIX(0);
	p->scale.x = FLT2FIX(1);
	p->scale.y = FLT2FIX(1);
	p->scale.z = FLT2FIX(1);
	p->scaleOrientation.x = FLT2FIX(0);
	p->scaleOrientation.y = FLT2FIX(0);
	p->scaleOrientation.z = FLT2FIX(1);
	p->scaleOrientation.q = FLT2FIX(0);
	p->translation.x = FLT2FIX(0);
	p->translation.y = FLT2FIX(0);
	p->translation.z = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	SBSkinnedModel Node deletion
*/

static void SBSkinnedModel_Del(GF_Node *node)
{
	M_SBSkinnedModel *p = (M_SBSkinnedModel *) node;
	gf_node_unregister_children((GF_Node *) p, p->bones);	
	gf_node_unregister_children((GF_Node *) p, p->muscles);	
	gf_sg_sfstring_del(p->name);
	gf_node_unregister_children((GF_Node *) p, p->segments);	
	gf_node_unregister_children((GF_Node *) p, p->sites);	
	gf_node_unregister_children((GF_Node *) p, p->skeleton);	
	gf_node_unregister_children((GF_Node *) p, p->skin);	
	gf_node_unregister((GF_Node *) p->skinCoord, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->skinNormal, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->weighsComputationSkinCoord, (GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 SBSkinnedModel_Def2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
static const u16 SBSkinnedModel_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
static const u16 SBSkinnedModel_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
static const u16 SBSkinnedModel_Dyn2All[] = { 1, 4, 6, 7, 13};

static u32 SBSkinnedModel_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 15;
	case GF_SG_FIELD_CODING_DEF: return 15;
	case GF_SG_FIELD_CODING_OUT: return 15;
	case GF_SG_FIELD_CODING_DYN: return 5;
	default:
		return 15;
	}
}

static GF_Err SBSkinnedModel_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = SBSkinnedModel_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = SBSkinnedModel_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = SBSkinnedModel_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = SBSkinnedModel_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err SBSkinnedModel_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "bones";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFSBBoneNode;
		info->far_ptr = & ((M_SBSkinnedModel *)node)->bones;
		return GF_OK;
	case 1:
		info->name = "center";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_SBSkinnedModel *) node)->center;
		return GF_OK;
	case 2:
		info->name = "muscles";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFSBMuscleNode;
		info->far_ptr = & ((M_SBSkinnedModel *)node)->muscles;
		return GF_OK;
	case 3:
		info->name = "name";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_SBSkinnedModel *) node)->name;
		return GF_OK;
	case 4:
		info->name = "rotation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFROTATION;
		info->far_ptr = & ((M_SBSkinnedModel *) node)->rotation;
		return GF_OK;
	case 5:
		info->name = "segments";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFSBSegmentNode;
		info->far_ptr = & ((M_SBSkinnedModel *)node)->segments;
		return GF_OK;
	case 6:
		info->name = "scale";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_SBSkinnedModel *) node)->scale;
		return GF_OK;
	case 7:
		info->name = "scaleOrientation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFROTATION;
		info->far_ptr = & ((M_SBSkinnedModel *) node)->scaleOrientation;
		return GF_OK;
	case 8:
		info->name = "sites";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFSBSiteNode;
		info->far_ptr = & ((M_SBSkinnedModel *)node)->sites;
		return GF_OK;
	case 9:
		info->name = "skeleton";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_SBSkinnedModel *)node)->skeleton;
		return GF_OK;
	case 10:
		info->name = "skin";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_SBSkinnedModel *)node)->skin;
		return GF_OK;
	case 11:
		info->name = "skinCoord";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFCoordinateNode;
		info->far_ptr = & ((M_SBSkinnedModel *)node)->skinCoord;
		return GF_OK;
	case 12:
		info->name = "skinNormal";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFNormalNode;
		info->far_ptr = & ((M_SBSkinnedModel *)node)->skinNormal;
		return GF_OK;
	case 13:
		info->name = "translation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_SBSkinnedModel *) node)->translation;
		return GF_OK;
	case 14:
		info->name = "weighsComputationSkinCoord";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_SBSkinnedModel *)node)->weighsComputationSkinCoord;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 SBSkinnedModel_get_field_index_by_name(char *name)
{
	if (!strcmp("bones", name)) return 0;
	if (!strcmp("center", name)) return 1;
	if (!strcmp("muscles", name)) return 2;
	if (!strcmp("name", name)) return 3;
	if (!strcmp("rotation", name)) return 4;
	if (!strcmp("segments", name)) return 5;
	if (!strcmp("scale", name)) return 6;
	if (!strcmp("scaleOrientation", name)) return 7;
	if (!strcmp("sites", name)) return 8;
	if (!strcmp("skeleton", name)) return 9;
	if (!strcmp("skin", name)) return 10;
	if (!strcmp("skinCoord", name)) return 11;
	if (!strcmp("skinNormal", name)) return 12;
	if (!strcmp("translation", name)) return 13;
	if (!strcmp("weighsComputationSkinCoord", name)) return 14;
	return -1;
	}
static Bool SBSkinnedModel_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 1;
		*QType = 1;
		return 1;
	case 4:
		*AType = 10;
		*QType = 10;
		return 1;
	case 6:
		*AType = 11;
		*QType = 7;
		return 1;
	case 7:
		*AType = 10;
		*QType = 10;
		return 1;
	case 13:
		*AType = 1;
		*QType = 1;
		return 1;
	default:
		return 0;
	}
}



GF_Node *SBSkinnedModel_Create()
{
	M_SBSkinnedModel *p;
	GF_SAFEALLOC(p, M_SBSkinnedModel);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_SBSkinnedModel);

	/*default field values*/
	p->center.x = FLT2FIX(0);
	p->center.y = FLT2FIX(0);
	p->center.z = FLT2FIX(0);
	p->rotation.x = FLT2FIX(0);
	p->rotation.y = FLT2FIX(0);
	p->rotation.z = FLT2FIX(1);
	p->rotation.q = FLT2FIX(0);
	p->scale.x = FLT2FIX(1);
	p->scale.y = FLT2FIX(1);
	p->scale.z = FLT2FIX(1);
	p->scaleOrientation.x = FLT2FIX(0);
	p->scaleOrientation.y = FLT2FIX(0);
	p->scaleOrientation.z = FLT2FIX(1);
	p->scaleOrientation.q = FLT2FIX(0);
	p->translation.x = FLT2FIX(0);
	p->translation.y = FLT2FIX(0);
	p->translation.z = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	SBVCAnimation Node deletion
*/

static void SBVCAnimation_Del(GF_Node *node)
{
	M_SBVCAnimation *p = (M_SBVCAnimation *) node;
	gf_sg_mfurl_del(p->url);
	gf_node_unregister_children((GF_Node *) p, p->virtualCharacters);	
	gf_node_free((GF_Node *) p);
}

static const u16 SBVCAnimation_Def2All[] = { 0, 1};
static const u16 SBVCAnimation_In2All[] = { 0, 1};
static const u16 SBVCAnimation_Out2All[] = { 0, 1};

static u32 SBVCAnimation_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 2;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 2;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 2;
	}
}

static GF_Err SBVCAnimation_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = SBVCAnimation_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = SBVCAnimation_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = SBVCAnimation_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err SBVCAnimation_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "url";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_SBVCAnimation *) node)->url;
		return GF_OK;
	case 1:
		info->name = "virtualCharacters";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_SBVCAnimation *)node)->virtualCharacters;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 SBVCAnimation_get_field_index_by_name(char *name)
{
	if (!strcmp("url", name)) return 0;
	if (!strcmp("virtualCharacters", name)) return 1;
	return -1;
	}
static Bool SBVCAnimation_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *SBVCAnimation_Create()
{
	M_SBVCAnimation *p;
	GF_SAFEALLOC(p, M_SBVCAnimation);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_SBVCAnimation);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	ScalarAnimator Node deletion
*/

static void ScalarAnimator_Del(GF_Node *node)
{
	M_ScalarAnimator *p = (M_ScalarAnimator *) node;
	gf_sg_mffloat_del(p->key);
	gf_sg_mfvec2f_del(p->keySpline);
	gf_sg_mffloat_del(p->keyValue);
	gf_sg_mffloat_del(p->weight);
	gf_node_free((GF_Node *) p);
}

static const u16 ScalarAnimator_Def2All[] = { 1, 2, 3, 4, 5, 6, 7, 8};
static const u16 ScalarAnimator_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};
static const u16 ScalarAnimator_Out2All[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};

static u32 ScalarAnimator_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 9;
	case GF_SG_FIELD_CODING_DEF: return 8;
	case GF_SG_FIELD_CODING_OUT: return 10;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 11;
	}
}

static GF_Err ScalarAnimator_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = ScalarAnimator_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = ScalarAnimator_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = ScalarAnimator_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err ScalarAnimator_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_fraction";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_ScalarAnimator *)node)->on_set_fraction;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ScalarAnimator *) node)->set_fraction;
		return GF_OK;
	case 1:
		info->name = "fromTo";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_ScalarAnimator *) node)->fromTo;
		return GF_OK;
	case 2:
		info->name = "key";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_ScalarAnimator *) node)->key;
		return GF_OK;
	case 3:
		info->name = "keyType";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_ScalarAnimator *) node)->keyType;
		return GF_OK;
	case 4:
		info->name = "keySpline";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC2F;
		info->far_ptr = & ((M_ScalarAnimator *) node)->keySpline;
		return GF_OK;
	case 5:
		info->name = "keyValue";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_ScalarAnimator *) node)->keyValue;
		return GF_OK;
	case 6:
		info->name = "keyValueType";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_ScalarAnimator *) node)->keyValueType;
		return GF_OK;
	case 7:
		info->name = "offset";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ScalarAnimator *) node)->offset;
		return GF_OK;
	case 8:
		info->name = "weight";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_ScalarAnimator *) node)->weight;
		return GF_OK;
	case 9:
		info->name = "endValue";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ScalarAnimator *) node)->endValue;
		return GF_OK;
	case 10:
		info->name = "value_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ScalarAnimator *) node)->value_changed;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 ScalarAnimator_get_field_index_by_name(char *name)
{
	if (!strcmp("set_fraction", name)) return 0;
	if (!strcmp("fromTo", name)) return 1;
	if (!strcmp("key", name)) return 2;
	if (!strcmp("keyType", name)) return 3;
	if (!strcmp("keySpline", name)) return 4;
	if (!strcmp("keyValue", name)) return 5;
	if (!strcmp("keyValueType", name)) return 6;
	if (!strcmp("offset", name)) return 7;
	if (!strcmp("weight", name)) return 8;
	if (!strcmp("endValue", name)) return 9;
	if (!strcmp("value_changed", name)) return 10;
	return -1;
	}
static Bool ScalarAnimator_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 0;
		*QType = 8;
		return 1;
	case 2:
		*AType = 0;
		*QType = 8;
		return 1;
	case 4:
		*AType = 0;
		*QType = 8;
		return 1;
	case 5:
		*AType = 0;
		*QType = 0;
		return 1;
	default:
		return 0;
	}
}



GF_Node *ScalarAnimator_Create()
{
	M_ScalarAnimator *p;
	GF_SAFEALLOC(p, M_ScalarAnimator);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_ScalarAnimator);

	/*default field values*/
	p->fromTo.x = FLT2FIX(0);
	p->fromTo.y = FLT2FIX(1);
	p->keyType = 0;
	p->keySpline.vals = (SFVec2f*)malloc(sizeof(SFVec2f)*2);
	p->keySpline.count = 2;
	p->keySpline.vals[0].x = FLT2FIX(0);
	p->keySpline.vals[0].y = FLT2FIX(0);
	p->keySpline.vals[1].x = FLT2FIX(1);
	p->keySpline.vals[1].y = FLT2FIX(1);
	p->keyValueType = 0;
	p->offset = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	SimpleTexture Node deletion
*/

static void SimpleTexture_Del(GF_Node *node)
{
	M_SimpleTexture *p = (M_SimpleTexture *) node;
	gf_node_unregister((GF_Node *) p->depth, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->texture, (GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 SimpleTexture_Def2All[] = { 0, 1};

static u32 SimpleTexture_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 0;
	case GF_SG_FIELD_CODING_DEF: return 2;
	case GF_SG_FIELD_CODING_OUT: return 0;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 2;
	}
}

static GF_Err SimpleTexture_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_DEF:
		*allField = SimpleTexture_Def2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err SimpleTexture_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "depth";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFTextureNode;
		info->far_ptr = & ((M_SimpleTexture *)node)->depth;
		return GF_OK;
	case 1:
		info->name = "texture";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFTextureNode;
		info->far_ptr = & ((M_SimpleTexture *)node)->texture;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 SimpleTexture_get_field_index_by_name(char *name)
{
	if (!strcmp("depth", name)) return 0;
	if (!strcmp("texture", name)) return 1;
	return -1;
	}
static Bool SimpleTexture_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *SimpleTexture_Create()
{
	M_SimpleTexture *p;
	GF_SAFEALLOC(p, M_SimpleTexture);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_SimpleTexture);

	/*default field values*/
	return (GF_Node *)p;
}


/*
	SolidRep Node deletion
*/

static void SolidRep_Del(GF_Node *node)
{
	M_SolidRep *p = (M_SolidRep *) node;
	gf_sg_mfint32_del(p->densityList);
	gf_node_unregister((GF_Node *) p->solidTree, (GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 SolidRep_Def2All[] = { 0, 1, 2};
static const u16 SolidRep_In2All[] = { 0, 1, 2};
static const u16 SolidRep_Out2All[] = { 0, 1, 2};
static const u16 SolidRep_Dyn2All[] = { 0};

static u32 SolidRep_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 3;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 3;
	}
}

static GF_Err SolidRep_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = SolidRep_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = SolidRep_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = SolidRep_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = SolidRep_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err SolidRep_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "bboxSize";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_SolidRep *) node)->bboxSize;
		return GF_OK;
	case 1:
		info->name = "densityList";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_SolidRep *) node)->densityList;
		return GF_OK;
	case 2:
		info->name = "solidTree";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_SolidRep *)node)->solidTree;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 SolidRep_get_field_index_by_name(char *name)
{
	if (!strcmp("bboxSize", name)) return 0;
	if (!strcmp("densityList", name)) return 1;
	if (!strcmp("solidTree", name)) return 2;
	return -1;
	}
static Bool SolidRep_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 11;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *SolidRep_Create()
{
	M_SolidRep *p;
	GF_SAFEALLOC(p, M_SolidRep);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_SolidRep);

	/*default field values*/
	p->bboxSize.x = FLT2FIX(2);
	p->bboxSize.y = FLT2FIX(2);
	p->bboxSize.z = FLT2FIX(2);
	return (GF_Node *)p;
}


/*
	SubdivisionSurface Node deletion
*/

static void SubdivisionSurface_Del(GF_Node *node)
{
	M_SubdivisionSurface *p = (M_SubdivisionSurface *) node;
	gf_sg_mfint32_del(p->set_colorIndex);
	gf_sg_mfint32_del(p->set_coordIndex);
	gf_sg_mfint32_del(p->set_cornerVertexIndex);
	gf_sg_mfint32_del(p->set_creaseEdgeIndex);
	gf_sg_mfint32_del(p->set_creaseVertexIndex);
	gf_sg_mfint32_del(p->set_dartVertexIndex);
	gf_sg_mfint32_del(p->set_texCoordIndex);
	gf_node_unregister((GF_Node *) p->color, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->coord, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->texCoord, (GF_Node *) p);	
	gf_node_unregister_children((GF_Node *) p, p->sectors);	
	gf_sg_mfint32_del(p->invisibleEdgeIndex);
	gf_sg_mfint32_del(p->colorIndex);
	gf_sg_mfint32_del(p->coordIndex);
	gf_sg_mfint32_del(p->cornerVertexIndex);
	gf_sg_mfint32_del(p->creaseEdgeIndex);
	gf_sg_mfint32_del(p->creaseVertexIndex);
	gf_sg_mfint32_del(p->dartVertexIndex);
	gf_sg_mfint32_del(p->texCoordIndex);
	gf_node_free((GF_Node *) p);
}

static const u16 SubdivisionSurface_Def2All[] = { 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22, 23, 24, 25};
static const u16 SubdivisionSurface_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
static const u16 SubdivisionSurface_Out2All[] = { 7, 8, 9, 10, 11, 12, 13};

static u32 SubdivisionSurface_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 14;
	case GF_SG_FIELD_CODING_DEF: return 19;
	case GF_SG_FIELD_CODING_OUT: return 7;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 26;
	}
}

static GF_Err SubdivisionSurface_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = SubdivisionSurface_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = SubdivisionSurface_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = SubdivisionSurface_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err SubdivisionSurface_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_colorIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_SubdivisionSurface *)node)->on_set_colorIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_SubdivisionSurface *) node)->set_colorIndex;
		return GF_OK;
	case 1:
		info->name = "set_coordIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_SubdivisionSurface *)node)->on_set_coordIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_SubdivisionSurface *) node)->set_coordIndex;
		return GF_OK;
	case 2:
		info->name = "set_cornerVertexIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_SubdivisionSurface *)node)->on_set_cornerVertexIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_SubdivisionSurface *) node)->set_cornerVertexIndex;
		return GF_OK;
	case 3:
		info->name = "set_creaseEdgeIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_SubdivisionSurface *)node)->on_set_creaseEdgeIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_SubdivisionSurface *) node)->set_creaseEdgeIndex;
		return GF_OK;
	case 4:
		info->name = "set_creaseVertexIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_SubdivisionSurface *)node)->on_set_creaseVertexIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_SubdivisionSurface *) node)->set_creaseVertexIndex;
		return GF_OK;
	case 5:
		info->name = "set_dartVertexIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_SubdivisionSurface *)node)->on_set_dartVertexIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_SubdivisionSurface *) node)->set_dartVertexIndex;
		return GF_OK;
	case 6:
		info->name = "set_texCoordIndex";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_SubdivisionSurface *)node)->on_set_texCoordIndex;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_SubdivisionSurface *) node)->set_texCoordIndex;
		return GF_OK;
	case 7:
		info->name = "color";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFColorNode;
		info->far_ptr = & ((M_SubdivisionSurface *)node)->color;
		return GF_OK;
	case 8:
		info->name = "coord";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFCoordinateNode;
		info->far_ptr = & ((M_SubdivisionSurface *)node)->coord;
		return GF_OK;
	case 9:
		info->name = "texCoord";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFTextureCoordinateNode;
		info->far_ptr = & ((M_SubdivisionSurface *)node)->texCoord;
		return GF_OK;
	case 10:
		info->name = "sectors";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SFSubdivSurfaceSectorNode;
		info->far_ptr = & ((M_SubdivisionSurface *)node)->sectors;
		return GF_OK;
	case 11:
		info->name = "subdivisionLevel";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_SubdivisionSurface *) node)->subdivisionLevel;
		return GF_OK;
	case 12:
		info->name = "subdivisionType";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_SubdivisionSurface *) node)->subdivisionType;
		return GF_OK;
	case 13:
		info->name = "subdivisionSubType";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_SubdivisionSurface *) node)->subdivisionSubType;
		return GF_OK;
	case 14:
		info->name = "invisibleEdgeIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_SubdivisionSurface *) node)->invisibleEdgeIndex;
		return GF_OK;
	case 15:
		info->name = "ccw";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_SubdivisionSurface *) node)->ccw;
		return GF_OK;
	case 16:
		info->name = "colorIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_SubdivisionSurface *) node)->colorIndex;
		return GF_OK;
	case 17:
		info->name = "colorPerVertex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_SubdivisionSurface *) node)->colorPerVertex;
		return GF_OK;
	case 18:
		info->name = "convex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_SubdivisionSurface *) node)->convex;
		return GF_OK;
	case 19:
		info->name = "coordIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_SubdivisionSurface *) node)->coordIndex;
		return GF_OK;
	case 20:
		info->name = "cornerVertexIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_SubdivisionSurface *) node)->cornerVertexIndex;
		return GF_OK;
	case 21:
		info->name = "creaseEdgeIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_SubdivisionSurface *) node)->creaseEdgeIndex;
		return GF_OK;
	case 22:
		info->name = "creaseVertexIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_SubdivisionSurface *) node)->creaseVertexIndex;
		return GF_OK;
	case 23:
		info->name = "dartVertexIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_SubdivisionSurface *) node)->dartVertexIndex;
		return GF_OK;
	case 24:
		info->name = "solid";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_SubdivisionSurface *) node)->solid;
		return GF_OK;
	case 25:
		info->name = "texCoordIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_SubdivisionSurface *) node)->texCoordIndex;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 SubdivisionSurface_get_field_index_by_name(char *name)
{
	if (!strcmp("set_colorIndex", name)) return 0;
	if (!strcmp("set_coordIndex", name)) return 1;
	if (!strcmp("set_cornerVertexIndex", name)) return 2;
	if (!strcmp("set_creaseEdgeIndex", name)) return 3;
	if (!strcmp("set_creaseVertexIndex", name)) return 4;
	if (!strcmp("set_dartVertexIndex", name)) return 5;
	if (!strcmp("set_texCoordIndex", name)) return 6;
	if (!strcmp("color", name)) return 7;
	if (!strcmp("coord", name)) return 8;
	if (!strcmp("texCoord", name)) return 9;
	if (!strcmp("sectors", name)) return 10;
	if (!strcmp("subdivisionLevel", name)) return 11;
	if (!strcmp("subdivisionType", name)) return 12;
	if (!strcmp("subdivisionSubType", name)) return 13;
	if (!strcmp("invisibleEdgeIndex", name)) return 14;
	if (!strcmp("ccw", name)) return 15;
	if (!strcmp("colorIndex", name)) return 16;
	if (!strcmp("colorPerVertex", name)) return 17;
	if (!strcmp("convex", name)) return 18;
	if (!strcmp("coordIndex", name)) return 19;
	if (!strcmp("cornerVertexIndex", name)) return 20;
	if (!strcmp("creaseEdgeIndex", name)) return 21;
	if (!strcmp("creaseVertexIndex", name)) return 22;
	if (!strcmp("dartVertexIndex", name)) return 23;
	if (!strcmp("solid", name)) return 24;
	if (!strcmp("texCoordIndex", name)) return 25;
	return -1;
	}
static Bool SubdivisionSurface_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 12:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 2;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(3);
		return 1;
	case 13:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 2;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(3);
		return 1;
	default:
		return 0;
	}
}



GF_Node *SubdivisionSurface_Create()
{
	M_SubdivisionSurface *p;
	GF_SAFEALLOC(p, M_SubdivisionSurface);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_SubdivisionSurface);

	/*default field values*/
	p->subdivisionLevel = 0;
	p->subdivisionType = 0;
	p->subdivisionSubType = 0;
	p->ccw = 1;
	p->colorPerVertex = 1;
	p->convex = 1;
	p->solid = 1;
	return (GF_Node *)p;
}


/*
	SubdivSurfaceSector Node deletion
*/

static void SubdivSurfaceSector_Del(GF_Node *node)
{
	M_SubdivSurfaceSector *p = (M_SubdivSurfaceSector *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 SubdivSurfaceSector_Def2All[] = { 0, 1, 2, 3, 4, 5, 6};
static const u16 SubdivSurfaceSector_In2All[] = { 0, 1, 2, 3, 4};
static const u16 SubdivSurfaceSector_Out2All[] = { 0, 1, 2, 3, 4};

static u32 SubdivSurfaceSector_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 5;
	case GF_SG_FIELD_CODING_DEF: return 7;
	case GF_SG_FIELD_CODING_OUT: return 5;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 7;
	}
}

static GF_Err SubdivSurfaceSector_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = SubdivSurfaceSector_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = SubdivSurfaceSector_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = SubdivSurfaceSector_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err SubdivSurfaceSector_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "flatness";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_SubdivSurfaceSector *) node)->flatness;
		return GF_OK;
	case 1:
		info->name = "normal";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC3F;
		info->far_ptr = & ((M_SubdivSurfaceSector *) node)->normal;
		return GF_OK;
	case 2:
		info->name = "normalTension";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_SubdivSurfaceSector *) node)->normalTension;
		return GF_OK;
	case 3:
		info->name = "_tag";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_SubdivSurfaceSector *) node)->_tag;
		return GF_OK;
	case 4:
		info->name = "theta";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_SubdivSurfaceSector *) node)->theta;
		return GF_OK;
	case 5:
		info->name = "faceIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_SubdivSurfaceSector *) node)->faceIndex;
		return GF_OK;
	case 6:
		info->name = "vertexIndex";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_SubdivSurfaceSector *) node)->vertexIndex;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 SubdivSurfaceSector_get_field_index_by_name(char *name)
{
	if (!strcmp("flatness", name)) return 0;
	if (!strcmp("normal", name)) return 1;
	if (!strcmp("normalTension", name)) return 2;
	if (!strcmp("_tag", name)) return 3;
	if (!strcmp("theta", name)) return 4;
	if (!strcmp("faceIndex", name)) return 5;
	if (!strcmp("vertexIndex", name)) return 6;
	return -1;
	}
static Bool SubdivSurfaceSector_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 0;
		*QType = 7;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 1:
		*AType = 0;
		*QType = 9;
		return 1;
	case 2:
		*AType = 0;
		*QType = 7;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 3:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 2;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(2);
		return 1;
	case 4:
		*AType = 0;
		*QType = 6;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(6.2831853);
		return 1;
	case 5:
		*AType = 0;
		*QType = 14;
		return 1;
	case 6:
		*AType = 0;
		*QType = 14;
		return 1;
	default:
		return 0;
	}
}



GF_Node *SubdivSurfaceSector_Create()
{
	M_SubdivSurfaceSector *p;
	GF_SAFEALLOC(p, M_SubdivSurfaceSector);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_SubdivSurfaceSector);

	/*default field values*/
	p->flatness = FLT2FIX(0);
	p->normal.x = FLT2FIX(0);
	p->normal.y = FLT2FIX(0);
	p->normal.z = FLT2FIX(0);
	p->normalTension = FLT2FIX(0);
	p->_tag = 0;
	p->theta = FLT2FIX(0);
	p->faceIndex = 0;
	p->vertexIndex = 0;
	return (GF_Node *)p;
}


/*
	WaveletSubdivisionSurface Node deletion
*/

static void WaveletSubdivisionSurface_Del(GF_Node *node)
{
	M_WaveletSubdivisionSurface *p = (M_WaveletSubdivisionSurface *) node;
	gf_node_unregister((GF_Node *) p->baseMesh, (GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 WaveletSubdivisionSurface_Def2All[] = { 0, 1, 2, 3};
static const u16 WaveletSubdivisionSurface_In2All[] = { 0, 1, 2, 3};
static const u16 WaveletSubdivisionSurface_Out2All[] = { 0, 1, 2, 3};

static u32 WaveletSubdivisionSurface_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 4;
	case GF_SG_FIELD_CODING_DEF: return 4;
	case GF_SG_FIELD_CODING_OUT: return 4;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 4;
	}
}

static GF_Err WaveletSubdivisionSurface_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = WaveletSubdivisionSurface_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = WaveletSubdivisionSurface_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = WaveletSubdivisionSurface_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err WaveletSubdivisionSurface_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "baseMesh";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFGeometryNode;
		info->far_ptr = & ((M_WaveletSubdivisionSurface *)node)->baseMesh;
		return GF_OK;
	case 1:
		info->name = "fieldOfView";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_WaveletSubdivisionSurface *) node)->fieldOfView;
		return GF_OK;
	case 2:
		info->name = "frequency";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_WaveletSubdivisionSurface *) node)->frequency;
		return GF_OK;
	case 3:
		info->name = "quality";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_WaveletSubdivisionSurface *) node)->quality;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 WaveletSubdivisionSurface_get_field_index_by_name(char *name)
{
	if (!strcmp("baseMesh", name)) return 0;
	if (!strcmp("fieldOfView", name)) return 1;
	if (!strcmp("frequency", name)) return 2;
	if (!strcmp("quality", name)) return 3;
	return -1;
	}
static Bool WaveletSubdivisionSurface_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *WaveletSubdivisionSurface_Create()
{
	M_WaveletSubdivisionSurface *p;
	GF_SAFEALLOC(p, M_WaveletSubdivisionSurface);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_WaveletSubdivisionSurface);

	/*default field values*/
	p->fieldOfView = FLT2FIX(0.785398);
	p->frequency = FLT2FIX(1.0);
	p->quality = 1;
	return (GF_Node *)p;
}


/*
	Clipper2D Node deletion
*/

static void Clipper2D_Del(GF_Node *node)
{
	M_Clipper2D *p = (M_Clipper2D *) node;
	gf_node_unregister((GF_Node *) p->geometry, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->transform, (GF_Node *) p);	
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 Clipper2D_Def2All[] = { 2, 3, 4, 5, 6};
static const u16 Clipper2D_In2All[] = { 0, 1, 2, 3, 4, 5, 6};
static const u16 Clipper2D_Out2All[] = { 2, 3, 4, 5, 6};

static u32 Clipper2D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 7;
	case GF_SG_FIELD_CODING_DEF: return 5;
	case GF_SG_FIELD_CODING_OUT: return 5;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 7;
	}
}

static GF_Err Clipper2D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Clipper2D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Clipper2D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Clipper2D_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Clipper2D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Clipper2D *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_Clipper2D *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Clipper2D *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_Clipper2D *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_Clipper2D *)node)->children;
		return GF_OK;
	case 3:
		info->name = "geometry";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFGeometryNode;
		info->far_ptr = & ((M_Clipper2D *)node)->geometry;
		return GF_OK;
	case 4:
		info->name = "inside";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Clipper2D *) node)->inside;
		return GF_OK;
	case 5:
		info->name = "transform";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_Clipper2D *)node)->transform;
		return GF_OK;
	case 6:
		info->name = "XOR";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Clipper2D *) node)->XOR;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Clipper2D_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	if (!strcmp("geometry", name)) return 3;
	if (!strcmp("inside", name)) return 4;
	if (!strcmp("transform", name)) return 5;
	if (!strcmp("XOR", name)) return 6;
	return -1;
	}
static Bool Clipper2D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	default:
		return 0;
	}
}



GF_Node *Clipper2D_Create()
{
	M_Clipper2D *p;
	GF_SAFEALLOC(p, M_Clipper2D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Clipper2D);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->inside = 1;
	return (GF_Node *)p;
}


/*
	ColorTransform Node deletion
*/

static void ColorTransform_Del(GF_Node *node)
{
	M_ColorTransform *p = (M_ColorTransform *) node;
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 ColorTransform_Def2All[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22};
static const u16 ColorTransform_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22};
static const u16 ColorTransform_Out2All[] = { 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22};
static const u16 ColorTransform_Dyn2All[] = { 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21, 22};

static u32 ColorTransform_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 23;
	case GF_SG_FIELD_CODING_DEF: return 21;
	case GF_SG_FIELD_CODING_OUT: return 21;
	case GF_SG_FIELD_CODING_DYN: return 20;
	default:
		return 23;
	}
}

static GF_Err ColorTransform_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = ColorTransform_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = ColorTransform_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = ColorTransform_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = ColorTransform_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err ColorTransform_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_ColorTransform *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_ColorTransform *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_ColorTransform *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_ColorTransform *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_ColorTransform *)node)->children;
		return GF_OK;
	case 3:
		info->name = "mrr";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ColorTransform *) node)->mrr;
		return GF_OK;
	case 4:
		info->name = "mrg";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ColorTransform *) node)->mrg;
		return GF_OK;
	case 5:
		info->name = "mrb";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ColorTransform *) node)->mrb;
		return GF_OK;
	case 6:
		info->name = "mra";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ColorTransform *) node)->mra;
		return GF_OK;
	case 7:
		info->name = "tr";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ColorTransform *) node)->tr;
		return GF_OK;
	case 8:
		info->name = "mgr";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ColorTransform *) node)->mgr;
		return GF_OK;
	case 9:
		info->name = "mgg";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ColorTransform *) node)->mgg;
		return GF_OK;
	case 10:
		info->name = "mgb";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ColorTransform *) node)->mgb;
		return GF_OK;
	case 11:
		info->name = "mga";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ColorTransform *) node)->mga;
		return GF_OK;
	case 12:
		info->name = "tg";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ColorTransform *) node)->tg;
		return GF_OK;
	case 13:
		info->name = "mbr";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ColorTransform *) node)->mbr;
		return GF_OK;
	case 14:
		info->name = "mbg";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ColorTransform *) node)->mbg;
		return GF_OK;
	case 15:
		info->name = "mbb";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ColorTransform *) node)->mbb;
		return GF_OK;
	case 16:
		info->name = "mba";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ColorTransform *) node)->mba;
		return GF_OK;
	case 17:
		info->name = "tb";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ColorTransform *) node)->tb;
		return GF_OK;
	case 18:
		info->name = "mar";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ColorTransform *) node)->mar;
		return GF_OK;
	case 19:
		info->name = "mag";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ColorTransform *) node)->mag;
		return GF_OK;
	case 20:
		info->name = "mab";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ColorTransform *) node)->mab;
		return GF_OK;
	case 21:
		info->name = "maa";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ColorTransform *) node)->maa;
		return GF_OK;
	case 22:
		info->name = "ta";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_ColorTransform *) node)->ta;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 ColorTransform_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	if (!strcmp("mrr", name)) return 3;
	if (!strcmp("mrg", name)) return 4;
	if (!strcmp("mrb", name)) return 5;
	if (!strcmp("mra", name)) return 6;
	if (!strcmp("tr", name)) return 7;
	if (!strcmp("mgr", name)) return 8;
	if (!strcmp("mgg", name)) return 9;
	if (!strcmp("mgb", name)) return 10;
	if (!strcmp("mga", name)) return 11;
	if (!strcmp("tg", name)) return 12;
	if (!strcmp("mbr", name)) return 13;
	if (!strcmp("mbg", name)) return 14;
	if (!strcmp("mbb", name)) return 15;
	if (!strcmp("mba", name)) return 16;
	if (!strcmp("tb", name)) return 17;
	if (!strcmp("mar", name)) return 18;
	if (!strcmp("mag", name)) return 19;
	if (!strcmp("mab", name)) return 20;
	if (!strcmp("maa", name)) return 21;
	if (!strcmp("ta", name)) return 22;
	return -1;
	}
static Bool ColorTransform_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 3:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 4:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 5:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 6:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 7:
		*AType = 7;
		*QType = 4;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 8:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 9:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 10:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 11:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 12:
		*AType = 7;
		*QType = 4;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 13:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 14:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 15:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 16:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 17:
		*AType = 7;
		*QType = 4;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 18:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 19:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 20:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 21:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 22:
		*AType = 7;
		*QType = 4;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *ColorTransform_Create()
{
	M_ColorTransform *p;
	GF_SAFEALLOC(p, M_ColorTransform);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_ColorTransform);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->mrr = FLT2FIX(1);
	p->mrg = FLT2FIX(0);
	p->mrb = FLT2FIX(0);
	p->mra = FLT2FIX(0);
	p->tr = FLT2FIX(0);
	p->mgr = FLT2FIX(0);
	p->mgg = FLT2FIX(1);
	p->mgb = FLT2FIX(0);
	p->mga = FLT2FIX(0);
	p->tg = FLT2FIX(0);
	p->mbr = FLT2FIX(0);
	p->mbg = FLT2FIX(0);
	p->mbb = FLT2FIX(1);
	p->mba = FLT2FIX(0);
	p->tb = FLT2FIX(0);
	p->mar = FLT2FIX(0);
	p->mag = FLT2FIX(0);
	p->mab = FLT2FIX(0);
	p->maa = FLT2FIX(1);
	p->ta = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	Ellipse Node deletion
*/

static void Ellipse_Del(GF_Node *node)
{
	M_Ellipse *p = (M_Ellipse *) node;
	gf_node_free((GF_Node *) p);
}

static const u16 Ellipse_Def2All[] = { 0};
static const u16 Ellipse_In2All[] = { 0};
static const u16 Ellipse_Out2All[] = { 0};
static const u16 Ellipse_Dyn2All[] = { 0};

static u32 Ellipse_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 1;
	case GF_SG_FIELD_CODING_DEF: return 1;
	case GF_SG_FIELD_CODING_OUT: return 1;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 1;
	}
}

static GF_Err Ellipse_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Ellipse_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Ellipse_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Ellipse_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Ellipse_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Ellipse_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "radius";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_Ellipse *) node)->radius;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Ellipse_get_field_index_by_name(char *name)
{
	if (!strcmp("radius", name)) return 0;
	return -1;
	}
static Bool Ellipse_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 2;
		*QType = 12;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *Ellipse_Create()
{
	M_Ellipse *p;
	GF_SAFEALLOC(p, M_Ellipse);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Ellipse);

	/*default field values*/
	p->radius.x = FLT2FIX(1);
	p->radius.y = FLT2FIX(1);
	return (GF_Node *)p;
}


/*
	LinearGradient Node deletion
*/

static void LinearGradient_Del(GF_Node *node)
{
	M_LinearGradient *p = (M_LinearGradient *) node;
	gf_sg_mffloat_del(p->key);
	gf_sg_mfcolor_del(p->keyValue);
	gf_sg_mffloat_del(p->opacity);
	gf_node_unregister((GF_Node *) p->transform, (GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 LinearGradient_Def2All[] = { 0, 1, 2, 3, 4, 5, 6};
static const u16 LinearGradient_In2All[] = { 0, 1, 2, 3, 4, 5, 6};
static const u16 LinearGradient_Out2All[] = { 0, 1, 2, 3, 4, 5, 6};
static const u16 LinearGradient_Dyn2All[] = { 0, 5};

static u32 LinearGradient_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 7;
	case GF_SG_FIELD_CODING_DEF: return 7;
	case GF_SG_FIELD_CODING_OUT: return 7;
	case GF_SG_FIELD_CODING_DYN: return 2;
	default:
		return 7;
	}
}

static GF_Err LinearGradient_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = LinearGradient_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = LinearGradient_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = LinearGradient_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = LinearGradient_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err LinearGradient_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "endPoint";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_LinearGradient *) node)->endPoint;
		return GF_OK;
	case 1:
		info->name = "key";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_LinearGradient *) node)->key;
		return GF_OK;
	case 2:
		info->name = "keyValue";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFCOLOR;
		info->far_ptr = & ((M_LinearGradient *) node)->keyValue;
		return GF_OK;
	case 3:
		info->name = "opacity";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_LinearGradient *) node)->opacity;
		return GF_OK;
	case 4:
		info->name = "spreadMethod";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_LinearGradient *) node)->spreadMethod;
		return GF_OK;
	case 5:
		info->name = "startPoint";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_LinearGradient *) node)->startPoint;
		return GF_OK;
	case 6:
		info->name = "transform";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_LinearGradient *)node)->transform;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 LinearGradient_get_field_index_by_name(char *name)
{
	if (!strcmp("endPoint", name)) return 0;
	if (!strcmp("key", name)) return 1;
	if (!strcmp("keyValue", name)) return 2;
	if (!strcmp("opacity", name)) return 3;
	if (!strcmp("spreadMethod", name)) return 4;
	if (!strcmp("startPoint", name)) return 5;
	if (!strcmp("transform", name)) return 6;
	return -1;
	}
static Bool LinearGradient_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 2;
		*QType = 5;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 1:
		*AType = 0;
		*QType = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 2:
		*AType = 0;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 3:
		*AType = 0;
		*QType = 7;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 4:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 2;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(2);
		return 1;
	case 5:
		*AType = 2;
		*QType = 5;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *LinearGradient_Create()
{
	M_LinearGradient *p;
	GF_SAFEALLOC(p, M_LinearGradient);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_LinearGradient);

	/*default field values*/
	p->endPoint.x = FLT2FIX(1);
	p->endPoint.y = FLT2FIX(0);
	p->opacity.vals = (SFFloat*)malloc(sizeof(SFFloat)*1);
	p->opacity.count = 1;
	p->opacity.vals[0] = FLT2FIX(1);
	p->spreadMethod = 0;
	p->startPoint.x = FLT2FIX(0);
	p->startPoint.y = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	PathLayout Node deletion
*/

static void PathLayout_Del(GF_Node *node)
{
	M_PathLayout *p = (M_PathLayout *) node;
	gf_node_unregister((GF_Node *) p->geometry, (GF_Node *) p);	
	gf_sg_mfint32_del(p->alignment);
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 PathLayout_Def2All[] = { 2, 3, 4, 5, 6, 7, 8, 9};
static const u16 PathLayout_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
static const u16 PathLayout_Out2All[] = { 2, 3, 4, 5, 6, 7, 8, 9};
static const u16 PathLayout_Dyn2All[] = { 5, 6};

static u32 PathLayout_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 10;
	case GF_SG_FIELD_CODING_DEF: return 8;
	case GF_SG_FIELD_CODING_OUT: return 8;
	case GF_SG_FIELD_CODING_DYN: return 2;
	default:
		return 10;
	}
}

static GF_Err PathLayout_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = PathLayout_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = PathLayout_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = PathLayout_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = PathLayout_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err PathLayout_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_PathLayout *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_PathLayout *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_PathLayout *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_PathLayout *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_PathLayout *)node)->children;
		return GF_OK;
	case 3:
		info->name = "geometry";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFGeometryNode;
		info->far_ptr = & ((M_PathLayout *)node)->geometry;
		return GF_OK;
	case 4:
		info->name = "alignment";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_PathLayout *) node)->alignment;
		return GF_OK;
	case 5:
		info->name = "pathOffset";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_PathLayout *) node)->pathOffset;
		return GF_OK;
	case 6:
		info->name = "spacing";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_PathLayout *) node)->spacing;
		return GF_OK;
	case 7:
		info->name = "reverseLayout";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_PathLayout *) node)->reverseLayout;
		return GF_OK;
	case 8:
		info->name = "wrapMode";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_PathLayout *) node)->wrapMode;
		return GF_OK;
	case 9:
		info->name = "splitText";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_PathLayout *) node)->splitText;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 PathLayout_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	if (!strcmp("geometry", name)) return 3;
	if (!strcmp("alignment", name)) return 4;
	if (!strcmp("pathOffset", name)) return 5;
	if (!strcmp("spacing", name)) return 6;
	if (!strcmp("reverseLayout", name)) return 7;
	if (!strcmp("wrapMode", name)) return 8;
	if (!strcmp("splitText", name)) return 9;
	return -1;
	}
static Bool PathLayout_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 4:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 2;
		*b_min = FLT2FIX(-1);
		*b_max = FLT2FIX(1);
		return 1;
	case 5:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 6:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 8:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 2;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(2);
		return 1;
	default:
		return 0;
	}
}



GF_Node *PathLayout_Create()
{
	M_PathLayout *p;
	GF_SAFEALLOC(p, M_PathLayout);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_PathLayout);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->alignment.vals = (SFInt32*)malloc(sizeof(SFInt32)*1);
	p->alignment.count = 1;
	p->alignment.vals[0] = 0;
	p->pathOffset = FLT2FIX(0);
	p->spacing = FLT2FIX(1.0);
	p->wrapMode = 0;
	p->splitText = 1;
	return (GF_Node *)p;
}


/*
	RadialGradient Node deletion
*/

static void RadialGradient_Del(GF_Node *node)
{
	M_RadialGradient *p = (M_RadialGradient *) node;
	gf_sg_mffloat_del(p->key);
	gf_sg_mfcolor_del(p->keyValue);
	gf_sg_mffloat_del(p->opacity);
	gf_node_unregister((GF_Node *) p->transform, (GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 RadialGradient_Def2All[] = { 0, 1, 2, 3, 4, 5, 6, 7};
static const u16 RadialGradient_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7};
static const u16 RadialGradient_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7};
static const u16 RadialGradient_Dyn2All[] = { 0, 1, 5};

static u32 RadialGradient_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 8;
	case GF_SG_FIELD_CODING_DEF: return 8;
	case GF_SG_FIELD_CODING_OUT: return 8;
	case GF_SG_FIELD_CODING_DYN: return 3;
	default:
		return 8;
	}
}

static GF_Err RadialGradient_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = RadialGradient_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = RadialGradient_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = RadialGradient_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = RadialGradient_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err RadialGradient_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "center";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_RadialGradient *) node)->center;
		return GF_OK;
	case 1:
		info->name = "focalPoint";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_RadialGradient *) node)->focalPoint;
		return GF_OK;
	case 2:
		info->name = "key";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_RadialGradient *) node)->key;
		return GF_OK;
	case 3:
		info->name = "keyValue";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFCOLOR;
		info->far_ptr = & ((M_RadialGradient *) node)->keyValue;
		return GF_OK;
	case 4:
		info->name = "opacity";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_RadialGradient *) node)->opacity;
		return GF_OK;
	case 5:
		info->name = "radius";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_RadialGradient *) node)->radius;
		return GF_OK;
	case 6:
		info->name = "spreadMethod";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_RadialGradient *) node)->spreadMethod;
		return GF_OK;
	case 7:
		info->name = "transform";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SF3DNode;
		info->far_ptr = & ((M_RadialGradient *)node)->transform;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 RadialGradient_get_field_index_by_name(char *name)
{
	if (!strcmp("center", name)) return 0;
	if (!strcmp("focalPoint", name)) return 1;
	if (!strcmp("key", name)) return 2;
	if (!strcmp("keyValue", name)) return 3;
	if (!strcmp("opacity", name)) return 4;
	if (!strcmp("radius", name)) return 5;
	if (!strcmp("spreadMethod", name)) return 6;
	if (!strcmp("transform", name)) return 7;
	return -1;
	}
static Bool RadialGradient_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 2;
		*QType = 5;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 1:
		*AType = 2;
		*QType = 5;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 2:
		*AType = 0;
		*QType = 8;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 3:
		*AType = 0;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 4:
		*AType = 0;
		*QType = 7;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 5:
		*AType = 7;
		*QType = 12;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 6:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 2;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(2);
		return 1;
	default:
		return 0;
	}
}



GF_Node *RadialGradient_Create()
{
	M_RadialGradient *p;
	GF_SAFEALLOC(p, M_RadialGradient);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_RadialGradient);

	/*default field values*/
	p->center.x = FLT2FIX(0.5);
	p->center.y = FLT2FIX(0.5);
	p->focalPoint.x = FLT2FIX(0);
	p->focalPoint.y = FLT2FIX(0);
	p->opacity.vals = (SFFloat*)malloc(sizeof(SFFloat)*1);
	p->opacity.count = 1;
	p->opacity.vals[0] = FLT2FIX(1);
	p->radius = FLT2FIX(0.5);
	p->spreadMethod = 0;
	return (GF_Node *)p;
}


/*
	SynthesizedTexture Node deletion
*/

static void SynthesizedTexture_Del(GF_Node *node)
{
	M_SynthesizedTexture *p = (M_SynthesizedTexture *) node;
	gf_sg_mfvec3f_del(p->translation);
	gf_sg_mfrotation_del(p->rotation);
	gf_sg_mfurl_del(p->url);
	gf_node_free((GF_Node *) p);
}

static const u16 SynthesizedTexture_Def2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};
static const u16 SynthesizedTexture_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};
static const u16 SynthesizedTexture_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
static const u16 SynthesizedTexture_Dyn2All[] = { 0, 1, 5};

static u32 SynthesizedTexture_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 9;
	case GF_SG_FIELD_CODING_DEF: return 9;
	case GF_SG_FIELD_CODING_OUT: return 11;
	case GF_SG_FIELD_CODING_DYN: return 3;
	default:
		return 11;
	}
}

static GF_Err SynthesizedTexture_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = SynthesizedTexture_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = SynthesizedTexture_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = SynthesizedTexture_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = SynthesizedTexture_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err SynthesizedTexture_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "translation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFVEC3F;
		info->far_ptr = & ((M_SynthesizedTexture *) node)->translation;
		return GF_OK;
	case 1:
		info->name = "rotation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFROTATION;
		info->far_ptr = & ((M_SynthesizedTexture *) node)->rotation;
		return GF_OK;
	case 2:
		info->name = "pixelWidth";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_SynthesizedTexture *) node)->pixelWidth;
		return GF_OK;
	case 3:
		info->name = "pixelHeight";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_SynthesizedTexture *) node)->pixelHeight;
		return GF_OK;
	case 4:
		info->name = "loop";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_SynthesizedTexture *) node)->loop;
		return GF_OK;
	case 5:
		info->name = "speed";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_SynthesizedTexture *) node)->speed;
		return GF_OK;
	case 6:
		info->name = "startTime";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_SynthesizedTexture *) node)->startTime;
		return GF_OK;
	case 7:
		info->name = "stopTime";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_SynthesizedTexture *) node)->stopTime;
		return GF_OK;
	case 8:
		info->name = "url";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFURL;
		info->far_ptr = & ((M_SynthesizedTexture *) node)->url;
		return GF_OK;
	case 9:
		info->name = "duration_changed";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_SynthesizedTexture *) node)->duration_changed;
		return GF_OK;
	case 10:
		info->name = "isActive";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_SynthesizedTexture *) node)->isActive;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 SynthesizedTexture_get_field_index_by_name(char *name)
{
	if (!strcmp("translation", name)) return 0;
	if (!strcmp("rotation", name)) return 1;
	if (!strcmp("pixelWidth", name)) return 2;
	if (!strcmp("pixelHeight", name)) return 3;
	if (!strcmp("loop", name)) return 4;
	if (!strcmp("speed", name)) return 5;
	if (!strcmp("startTime", name)) return 6;
	if (!strcmp("stopTime", name)) return 7;
	if (!strcmp("url", name)) return 8;
	if (!strcmp("duration_changed", name)) return 9;
	if (!strcmp("isActive", name)) return 10;
	return -1;
	}
static Bool SynthesizedTexture_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 1;
		*QType = 1;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 1:
		*AType = 10;
		*QType = 10;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 2:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 16;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX /*WARNING: modified to allow 16.16 fixed point version!!*/;
		return 1;
	case 3:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 16;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX /*WARNING: modified to allow 16.16 fixed point version!!*/;
		return 1;
	case 5:
		*AType = 7;
		*QType = 0;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *SynthesizedTexture_Create()
{
	M_SynthesizedTexture *p;
	GF_SAFEALLOC(p, M_SynthesizedTexture);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_SynthesizedTexture);

	/*default field values*/
	p->pixelWidth = -1;
	p->pixelHeight = -1;
	p->speed = FLT2FIX(1.0);
	p->startTime = 0;
	p->stopTime = 0;
	return (GF_Node *)p;
}


/*
	TransformMatrix2D Node deletion
*/

static void TransformMatrix2D_Del(GF_Node *node)
{
	M_TransformMatrix2D *p = (M_TransformMatrix2D *) node;
	gf_sg_vrml_parent_destroy((GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 TransformMatrix2D_Def2All[] = { 2, 3, 4, 5, 6, 7, 8};
static const u16 TransformMatrix2D_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8};
static const u16 TransformMatrix2D_Out2All[] = { 2, 3, 4, 5, 6, 7, 8};
static const u16 TransformMatrix2D_Dyn2All[] = { 3, 4, 5, 6, 7, 8};

static u32 TransformMatrix2D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 9;
	case GF_SG_FIELD_CODING_DEF: return 7;
	case GF_SG_FIELD_CODING_OUT: return 7;
	case GF_SG_FIELD_CODING_DYN: return 6;
	default:
		return 9;
	}
}

static GF_Err TransformMatrix2D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = TransformMatrix2D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = TransformMatrix2D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = TransformMatrix2D_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = TransformMatrix2D_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err TransformMatrix2D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "addChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_TransformMatrix2D *)node)->on_addChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_TransformMatrix2D *)node)->addChildren;
		return GF_OK;
	case 1:
		info->name = "removeChildren";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_TransformMatrix2D *)node)->on_removeChildren;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_TransformMatrix2D *)node)->removeChildren;
		return GF_OK;
	case 2:
		info->name = "children";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFNODE;
		info->NDTtype = NDT_SF2DNode;
		info->far_ptr = & ((M_TransformMatrix2D *)node)->children;
		return GF_OK;
	case 3:
		info->name = "mxx";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_TransformMatrix2D *) node)->mxx;
		return GF_OK;
	case 4:
		info->name = "mxy";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_TransformMatrix2D *) node)->mxy;
		return GF_OK;
	case 5:
		info->name = "tx";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_TransformMatrix2D *) node)->tx;
		return GF_OK;
	case 6:
		info->name = "myx";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_TransformMatrix2D *) node)->myx;
		return GF_OK;
	case 7:
		info->name = "myy";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_TransformMatrix2D *) node)->myy;
		return GF_OK;
	case 8:
		info->name = "ty";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_TransformMatrix2D *) node)->ty;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 TransformMatrix2D_get_field_index_by_name(char *name)
{
	if (!strcmp("addChildren", name)) return 0;
	if (!strcmp("removeChildren", name)) return 1;
	if (!strcmp("children", name)) return 2;
	if (!strcmp("mxx", name)) return 3;
	if (!strcmp("mxy", name)) return 4;
	if (!strcmp("tx", name)) return 5;
	if (!strcmp("myx", name)) return 6;
	if (!strcmp("myy", name)) return 7;
	if (!strcmp("ty", name)) return 8;
	return -1;
	}
static Bool TransformMatrix2D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 3:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 4:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 5:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 6:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 7:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 8:
		*AType = 7;
		*QType = 7;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *TransformMatrix2D_Create()
{
	M_TransformMatrix2D *p;
	GF_SAFEALLOC(p, M_TransformMatrix2D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_TransformMatrix2D);
	gf_sg_vrml_parent_setup((GF_Node *) p);

	/*default field values*/
	p->mxx = FLT2FIX(1);
	p->mxy = FLT2FIX(0);
	p->tx = FLT2FIX(0);
	p->myx = FLT2FIX(0);
	p->myy = FLT2FIX(1);
	p->ty = FLT2FIX(0);
	return (GF_Node *)p;
}


/*
	Viewport Node deletion
*/

static void Viewport_Del(GF_Node *node)
{
	M_Viewport *p = (M_Viewport *) node;
	gf_sg_mfint32_del(p->alignment);
	gf_sg_sfstring_del(p->description);
	gf_node_free((GF_Node *) p);
}

static const u16 Viewport_Def2All[] = { 1, 2, 3, 4, 5, 6};
static const u16 Viewport_In2All[] = { 0, 1, 2, 3, 4, 5};
static const u16 Viewport_Out2All[] = { 1, 2, 3, 4, 5, 7, 8};
static const u16 Viewport_Dyn2All[] = { 1, 2, 3};

static u32 Viewport_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 6;
	case GF_SG_FIELD_CODING_DEF: return 6;
	case GF_SG_FIELD_CODING_OUT: return 7;
	case GF_SG_FIELD_CODING_DYN: return 3;
	default:
		return 9;
	}
}

static GF_Err Viewport_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = Viewport_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = Viewport_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = Viewport_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = Viewport_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err Viewport_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "set_bind";
		info->eventType = GF_SG_EVENT_IN;
		info->on_event_in = ((M_Viewport *)node)->on_set_bind;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Viewport *) node)->set_bind;
		return GF_OK;
	case 1:
		info->name = "position";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_Viewport *) node)->position;
		return GF_OK;
	case 2:
		info->name = "size";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFVEC2F;
		info->far_ptr = & ((M_Viewport *) node)->size;
		return GF_OK;
	case 3:
		info->name = "orientation";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_Viewport *) node)->orientation;
		return GF_OK;
	case 4:
		info->name = "alignment";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_Viewport *) node)->alignment;
		return GF_OK;
	case 5:
		info->name = "fit";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_Viewport *) node)->fit;
		return GF_OK;
	case 6:
		info->name = "description";
		info->eventType = GF_SG_EVENT_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_Viewport *) node)->description;
		return GF_OK;
	case 7:
		info->name = "bindTime";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFTIME;
		info->far_ptr = & ((M_Viewport *) node)->bindTime;
		return GF_OK;
	case 8:
		info->name = "isBound";
		info->eventType = GF_SG_EVENT_OUT;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_Viewport *) node)->isBound;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 Viewport_get_field_index_by_name(char *name)
{
	if (!strcmp("set_bind", name)) return 0;
	if (!strcmp("position", name)) return 1;
	if (!strcmp("size", name)) return 2;
	if (!strcmp("orientation", name)) return 3;
	if (!strcmp("alignment", name)) return 4;
	if (!strcmp("fit", name)) return 5;
	if (!strcmp("description", name)) return 6;
	if (!strcmp("bindTime", name)) return 7;
	if (!strcmp("isBound", name)) return 8;
	return -1;
	}
static Bool Viewport_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 1;
		*QType = 1;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 2:
		*AType = 12;
		*QType = 12;
		*b_min = FIX_MIN;
		*b_max = FIX_MAX;
		return 1;
	case 3:
		*AType = 6;
		*QType = 6;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(6.2831853);
		return 1;
	case 4:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 3;
		*b_min = FLT2FIX(-1);
		*b_max = FLT2FIX(1);
		return 1;
	case 5:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 3;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(2);
		return 1;
	default:
		return 0;
	}
}



GF_Node *Viewport_Create()
{
	M_Viewport *p;
	GF_SAFEALLOC(p, M_Viewport);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_Viewport);

	/*default field values*/
	p->position.x = FLT2FIX(0);
	p->position.y = FLT2FIX(0);
	p->size.x = FLT2FIX(-1);
	p->size.y = FLT2FIX(-1);
	p->orientation = FLT2FIX(0);
	p->alignment.vals = (SFInt32*)malloc(sizeof(SFInt32)*1);
	p->alignment.count = 1;
	p->alignment.vals[0] = 0;
	p->fit = 0;
	return (GF_Node *)p;
}


/*
	XCurve2D Node deletion
*/

static void XCurve2D_Del(GF_Node *node)
{
	M_XCurve2D *p = (M_XCurve2D *) node;
	gf_node_unregister((GF_Node *) p->point, (GF_Node *) p);	
	gf_sg_mfint32_del(p->type);
	gf_node_free((GF_Node *) p);
}

static const u16 XCurve2D_Def2All[] = { 0, 1, 2};
static const u16 XCurve2D_In2All[] = { 0, 1, 2};
static const u16 XCurve2D_Out2All[] = { 0, 1, 2};
static const u16 XCurve2D_Dyn2All[] = { 1};

static u32 XCurve2D_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 3;
	case GF_SG_FIELD_CODING_DEF: return 3;
	case GF_SG_FIELD_CODING_OUT: return 3;
	case GF_SG_FIELD_CODING_DYN: return 1;
	default:
		return 3;
	}
}

static GF_Err XCurve2D_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = XCurve2D_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = XCurve2D_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = XCurve2D_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = XCurve2D_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err XCurve2D_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "point";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFCoordinate2DNode;
		info->far_ptr = & ((M_XCurve2D *)node)->point;
		return GF_OK;
	case 1:
		info->name = "fineness";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XCurve2D *) node)->fineness;
		return GF_OK;
	case 2:
		info->name = "type";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_XCurve2D *) node)->type;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 XCurve2D_get_field_index_by_name(char *name)
{
	if (!strcmp("point", name)) return 0;
	if (!strcmp("fineness", name)) return 1;
	if (!strcmp("type", name)) return 2;
	return -1;
	}
static Bool XCurve2D_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 1:
		*AType = 7;
		*QType = 0;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 2:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(15);
		return 1;
	default:
		return 0;
	}
}



GF_Node *XCurve2D_Create()
{
	M_XCurve2D *p;
	GF_SAFEALLOC(p, M_XCurve2D);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_XCurve2D);

	/*default field values*/
	p->fineness = FLT2FIX(0.5);
	return (GF_Node *)p;
}


/*
	XFontStyle Node deletion
*/

static void XFontStyle_Del(GF_Node *node)
{
	M_XFontStyle *p = (M_XFontStyle *) node;
	gf_sg_mfstring_del(p->fontName);
	gf_sg_mfstring_del(p->justify);
	gf_sg_sfstring_del(p->language);
	gf_sg_sfstring_del(p->stretch);
	gf_sg_sfstring_del(p->style);
	gf_sg_mfstring_del(p->featureName);
	gf_sg_mfint32_del(p->featureStartOffset);
	gf_sg_mfint32_del(p->featureLength);
	gf_sg_mfint32_del(p->featureValue);
	gf_node_free((GF_Node *) p);
}

static const u16 XFontStyle_Def2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
static const u16 XFontStyle_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
static const u16 XFontStyle_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};

static u32 XFontStyle_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 17;
	case GF_SG_FIELD_CODING_DEF: return 17;
	case GF_SG_FIELD_CODING_OUT: return 17;
	case GF_SG_FIELD_CODING_DYN: return 0;
	default:
		return 17;
	}
}

static GF_Err XFontStyle_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = XFontStyle_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = XFontStyle_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = XFontStyle_Out2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err XFontStyle_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "fontName";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFSTRING;
		info->far_ptr = & ((M_XFontStyle *) node)->fontName;
		return GF_OK;
	case 1:
		info->name = "horizontal";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_XFontStyle *) node)->horizontal;
		return GF_OK;
	case 2:
		info->name = "justify";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFSTRING;
		info->far_ptr = & ((M_XFontStyle *) node)->justify;
		return GF_OK;
	case 3:
		info->name = "language";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_XFontStyle *) node)->language;
		return GF_OK;
	case 4:
		info->name = "leftToRight";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_XFontStyle *) node)->leftToRight;
		return GF_OK;
	case 5:
		info->name = "size";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XFontStyle *) node)->size;
		return GF_OK;
	case 6:
		info->name = "stretch";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_XFontStyle *) node)->stretch;
		return GF_OK;
	case 7:
		info->name = "letterSpacing";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XFontStyle *) node)->letterSpacing;
		return GF_OK;
	case 8:
		info->name = "wordSpacing";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XFontStyle *) node)->wordSpacing;
		return GF_OK;
	case 9:
		info->name = "weight";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_XFontStyle *) node)->weight;
		return GF_OK;
	case 10:
		info->name = "fontKerning";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_XFontStyle *) node)->fontKerning;
		return GF_OK;
	case 11:
		info->name = "style";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFSTRING;
		info->far_ptr = & ((M_XFontStyle *) node)->style;
		return GF_OK;
	case 12:
		info->name = "topToBottom";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_XFontStyle *) node)->topToBottom;
		return GF_OK;
	case 13:
		info->name = "featureName";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFSTRING;
		info->far_ptr = & ((M_XFontStyle *) node)->featureName;
		return GF_OK;
	case 14:
		info->name = "featureStartOffset";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_XFontStyle *) node)->featureStartOffset;
		return GF_OK;
	case 15:
		info->name = "featureLength";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_XFontStyle *) node)->featureLength;
		return GF_OK;
	case 16:
		info->name = "featureValue";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFINT32;
		info->far_ptr = & ((M_XFontStyle *) node)->featureValue;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 XFontStyle_get_field_index_by_name(char *name)
{
	if (!strcmp("fontName", name)) return 0;
	if (!strcmp("horizontal", name)) return 1;
	if (!strcmp("justify", name)) return 2;
	if (!strcmp("language", name)) return 3;
	if (!strcmp("leftToRight", name)) return 4;
	if (!strcmp("size", name)) return 5;
	if (!strcmp("stretch", name)) return 6;
	if (!strcmp("letterSpacing", name)) return 7;
	if (!strcmp("wordSpacing", name)) return 8;
	if (!strcmp("weight", name)) return 9;
	if (!strcmp("fontKerning", name)) return 10;
	if (!strcmp("style", name)) return 11;
	if (!strcmp("topToBottom", name)) return 12;
	if (!strcmp("featureName", name)) return 13;
	if (!strcmp("featureStartOffset", name)) return 14;
	if (!strcmp("featureLength", name)) return 15;
	if (!strcmp("featureValue", name)) return 16;
	return -1;
	}
static Bool XFontStyle_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 5:
		*AType = 0;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 7:
		*AType = 0;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 8:
		*AType = 0;
		*QType = 11;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *XFontStyle_Create()
{
	M_XFontStyle *p;
	GF_SAFEALLOC(p, M_XFontStyle);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_XFontStyle);

	/*default field values*/
	p->fontName.vals = (char**)malloc(sizeof(SFString)*1);
	p->fontName.count = 1;
	p->fontName.vals[0] = (char*)malloc(sizeof(char) * 6);
	strcpy(p->fontName.vals[0], "SERIF");
	p->horizontal = 1;
	p->justify.vals = (char**)malloc(sizeof(SFString)*1);
	p->justify.count = 1;
	p->justify.vals[0] = (char*)malloc(sizeof(char) * 6);
	strcpy(p->justify.vals[0], "BEGIN");
	p->leftToRight = 1;
	p->size = FLT2FIX(1.0);
	p->stretch.buffer = (char*)malloc(sizeof(char) * 7);
	strcpy(p->stretch.buffer, "NORMAL");
	p->letterSpacing = FLT2FIX(0.0);
	p->wordSpacing = FLT2FIX(0.0);
	p->weight = 400;
	p->fontKerning = 1;
	p->style.buffer = (char*)malloc(sizeof(char) * 6);
	strcpy(p->style.buffer, "PLAIN");
	p->topToBottom = 1;
	return (GF_Node *)p;
}


/*
	XLineProperties Node deletion
*/

static void XLineProperties_Del(GF_Node *node)
{
	M_XLineProperties *p = (M_XLineProperties *) node;
	gf_sg_mffloat_del(p->dashes);
	gf_node_unregister((GF_Node *) p->texture, (GF_Node *) p);	
	gf_node_unregister((GF_Node *) p->textureTransform, (GF_Node *) p);	
	gf_node_free((GF_Node *) p);
}

static const u16 XLineProperties_Def2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
static const u16 XLineProperties_In2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
static const u16 XLineProperties_Out2All[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12};
static const u16 XLineProperties_Dyn2All[] = { 0, 7, 8, 9, 10};

static u32 XLineProperties_get_field_count(GF_Node *node, u8 IndexMode)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN: return 13;
	case GF_SG_FIELD_CODING_DEF: return 13;
	case GF_SG_FIELD_CODING_OUT: return 13;
	case GF_SG_FIELD_CODING_DYN: return 5;
	default:
		return 13;
	}
}

static GF_Err XLineProperties_get_field_index(GF_Node *n, u32 inField, u8 IndexMode, u32 *allField)
{
	switch(IndexMode) {
	case GF_SG_FIELD_CODING_IN:
		*allField = XLineProperties_In2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DEF:
		*allField = XLineProperties_Def2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_OUT:
		*allField = XLineProperties_Out2All[inField];
		return GF_OK;
	case GF_SG_FIELD_CODING_DYN:
		*allField = XLineProperties_Dyn2All[inField];
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}
static GF_Err XLineProperties_get_field(GF_Node *node, GF_FieldInfo *info)
{
	switch (info->fieldIndex) {
	case 0:
		info->name = "lineColor";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFCOLOR;
		info->far_ptr = & ((M_XLineProperties *) node)->lineColor;
		return GF_OK;
	case 1:
		info->name = "lineStyle";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_XLineProperties *) node)->lineStyle;
		return GF_OK;
	case 2:
		info->name = "isCenterAligned";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_XLineProperties *) node)->isCenterAligned;
		return GF_OK;
	case 3:
		info->name = "isScalable";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFBOOL;
		info->far_ptr = & ((M_XLineProperties *) node)->isScalable;
		return GF_OK;
	case 4:
		info->name = "lineCap";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_XLineProperties *) node)->lineCap;
		return GF_OK;
	case 5:
		info->name = "lineJoin";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFINT32;
		info->far_ptr = & ((M_XLineProperties *) node)->lineJoin;
		return GF_OK;
	case 6:
		info->name = "miterLimit";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XLineProperties *) node)->miterLimit;
		return GF_OK;
	case 7:
		info->name = "transparency";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XLineProperties *) node)->transparency;
		return GF_OK;
	case 8:
		info->name = "width";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XLineProperties *) node)->width;
		return GF_OK;
	case 9:
		info->name = "dashOffset";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFFLOAT;
		info->far_ptr = & ((M_XLineProperties *) node)->dashOffset;
		return GF_OK;
	case 10:
		info->name = "dashes";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_MFFLOAT;
		info->far_ptr = & ((M_XLineProperties *) node)->dashes;
		return GF_OK;
	case 11:
		info->name = "texture";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFTextureNode;
		info->far_ptr = & ((M_XLineProperties *)node)->texture;
		return GF_OK;
	case 12:
		info->name = "textureTransform";
		info->eventType = GF_SG_EVENT_EXPOSED_FIELD;
		info->fieldType = GF_SG_VRML_SFNODE;
		info->NDTtype = NDT_SFTextureTransformNode;
		info->far_ptr = & ((M_XLineProperties *)node)->textureTransform;
		return GF_OK;
	default:
		return GF_BAD_PARAM;
	}
}


static s32 XLineProperties_get_field_index_by_name(char *name)
{
	if (!strcmp("lineColor", name)) return 0;
	if (!strcmp("lineStyle", name)) return 1;
	if (!strcmp("isCenterAligned", name)) return 2;
	if (!strcmp("isScalable", name)) return 3;
	if (!strcmp("lineCap", name)) return 4;
	if (!strcmp("lineJoin", name)) return 5;
	if (!strcmp("miterLimit", name)) return 6;
	if (!strcmp("transparency", name)) return 7;
	if (!strcmp("width", name)) return 8;
	if (!strcmp("dashOffset", name)) return 9;
	if (!strcmp("dashes", name)) return 10;
	if (!strcmp("texture", name)) return 11;
	if (!strcmp("textureTransform", name)) return 12;
	return -1;
	}
static Bool XLineProperties_get_aq_info(GF_Node *n, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (FieldIndex) {
	case 0:
		*AType = 4;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 1:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 3;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(5);
		return 1;
	case 4:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 3;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(2);
		return 1;
	case 5:
		*AType = 0;
		*QType = 13;
		*QT13_bits = 3;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(2);
		return 1;
	case 6:
		*AType = 0;
		*QType = 12;
		*b_min = FLT2FIX(1);
		*b_max = FIX_MAX;
		return 1;
	case 7:
		*AType = 8;
		*QType = 4;
		*b_min = FLT2FIX(0);
		*b_max = FLT2FIX(1);
		return 1;
	case 8:
		*AType = 7;
		*QType = 12;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 9:
		*AType = 7;
		*QType = 12;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	case 10:
		*AType = 7;
		*QType = 12;
		*b_min = FLT2FIX(0);
		*b_max = FIX_MAX;
		return 1;
	default:
		return 0;
	}
}



GF_Node *XLineProperties_Create()
{
	M_XLineProperties *p;
	GF_SAFEALLOC(p, M_XLineProperties);
	if(!p) return NULL;
	gf_node_setup((GF_Node *)p, TAG_MPEG4_XLineProperties);

	/*default field values*/
	p->lineColor.red = FLT2FIX(0);
	p->lineColor.green = FLT2FIX(0);
	p->lineColor.blue = FLT2FIX(0);
	p->lineStyle = 0;
	p->isCenterAligned = 1;
	p->isScalable = 1;
	p->lineCap = 0;
	p->lineJoin = 0;
	p->miterLimit = FLT2FIX(4);
	p->transparency = FLT2FIX(0);
	p->width = FLT2FIX(1);
	p->dashOffset = FLT2FIX(0);
	return (GF_Node *)p;
}




GF_Node *gf_sg_mpeg4_node_new(u32 NodeTag)
{
	switch (NodeTag) {
	case TAG_MPEG4_Anchor:
		return Anchor_Create();
	case TAG_MPEG4_AnimationStream:
		return AnimationStream_Create();
	case TAG_MPEG4_Appearance:
		return Appearance_Create();
	case TAG_MPEG4_AudioBuffer:
		return AudioBuffer_Create();
	case TAG_MPEG4_AudioClip:
		return AudioClip_Create();
	case TAG_MPEG4_AudioDelay:
		return AudioDelay_Create();
	case TAG_MPEG4_AudioFX:
		return AudioFX_Create();
	case TAG_MPEG4_AudioMix:
		return AudioMix_Create();
	case TAG_MPEG4_AudioSource:
		return AudioSource_Create();
	case TAG_MPEG4_AudioSwitch:
		return AudioSwitch_Create();
	case TAG_MPEG4_Background:
		return Background_Create();
	case TAG_MPEG4_Background2D:
		return Background2D_Create();
	case TAG_MPEG4_Billboard:
		return Billboard_Create();
	case TAG_MPEG4_Bitmap:
		return Bitmap_Create();
	case TAG_MPEG4_Box:
		return Box_Create();
	case TAG_MPEG4_Circle:
		return Circle_Create();
	case TAG_MPEG4_Collision:
		return Collision_Create();
	case TAG_MPEG4_Color:
		return Color_Create();
	case TAG_MPEG4_ColorInterpolator:
		return ColorInterpolator_Create();
	case TAG_MPEG4_CompositeTexture2D:
		return CompositeTexture2D_Create();
	case TAG_MPEG4_CompositeTexture3D:
		return CompositeTexture3D_Create();
	case TAG_MPEG4_Conditional:
		return Conditional_Create();
	case TAG_MPEG4_Cone:
		return Cone_Create();
	case TAG_MPEG4_Coordinate:
		return Coordinate_Create();
	case TAG_MPEG4_Coordinate2D:
		return Coordinate2D_Create();
	case TAG_MPEG4_CoordinateInterpolator:
		return CoordinateInterpolator_Create();
	case TAG_MPEG4_CoordinateInterpolator2D:
		return CoordinateInterpolator2D_Create();
	case TAG_MPEG4_Curve2D:
		return Curve2D_Create();
	case TAG_MPEG4_Cylinder:
		return Cylinder_Create();
	case TAG_MPEG4_CylinderSensor:
		return CylinderSensor_Create();
	case TAG_MPEG4_DirectionalLight:
		return DirectionalLight_Create();
	case TAG_MPEG4_DiscSensor:
		return DiscSensor_Create();
	case TAG_MPEG4_ElevationGrid:
		return ElevationGrid_Create();
	case TAG_MPEG4_Expression:
		return Expression_Create();
	case TAG_MPEG4_Extrusion:
		return Extrusion_Create();
	case TAG_MPEG4_Face:
		return Face_Create();
	case TAG_MPEG4_FaceDefMesh:
		return FaceDefMesh_Create();
	case TAG_MPEG4_FaceDefTables:
		return FaceDefTables_Create();
	case TAG_MPEG4_FaceDefTransform:
		return FaceDefTransform_Create();
	case TAG_MPEG4_FAP:
		return FAP_Create();
	case TAG_MPEG4_FDP:
		return FDP_Create();
	case TAG_MPEG4_FIT:
		return FIT_Create();
	case TAG_MPEG4_Fog:
		return Fog_Create();
	case TAG_MPEG4_FontStyle:
		return FontStyle_Create();
	case TAG_MPEG4_Form:
		return Form_Create();
	case TAG_MPEG4_Group:
		return Group_Create();
	case TAG_MPEG4_ImageTexture:
		return ImageTexture_Create();
	case TAG_MPEG4_IndexedFaceSet:
		return IndexedFaceSet_Create();
	case TAG_MPEG4_IndexedFaceSet2D:
		return IndexedFaceSet2D_Create();
	case TAG_MPEG4_IndexedLineSet:
		return IndexedLineSet_Create();
	case TAG_MPEG4_IndexedLineSet2D:
		return IndexedLineSet2D_Create();
	case TAG_MPEG4_Inline:
		return Inline_Create();
	case TAG_MPEG4_LOD:
		return LOD_Create();
	case TAG_MPEG4_Layer2D:
		return Layer2D_Create();
	case TAG_MPEG4_Layer3D:
		return Layer3D_Create();
	case TAG_MPEG4_Layout:
		return Layout_Create();
	case TAG_MPEG4_LineProperties:
		return LineProperties_Create();
	case TAG_MPEG4_ListeningPoint:
		return ListeningPoint_Create();
	case TAG_MPEG4_Material:
		return Material_Create();
	case TAG_MPEG4_Material2D:
		return Material2D_Create();
	case TAG_MPEG4_MovieTexture:
		return MovieTexture_Create();
	case TAG_MPEG4_NavigationInfo:
		return NavigationInfo_Create();
	case TAG_MPEG4_Normal:
		return Normal_Create();
	case TAG_MPEG4_NormalInterpolator:
		return NormalInterpolator_Create();
	case TAG_MPEG4_OrderedGroup:
		return OrderedGroup_Create();
	case TAG_MPEG4_OrientationInterpolator:
		return OrientationInterpolator_Create();
	case TAG_MPEG4_PixelTexture:
		return PixelTexture_Create();
	case TAG_MPEG4_PlaneSensor:
		return PlaneSensor_Create();
	case TAG_MPEG4_PlaneSensor2D:
		return PlaneSensor2D_Create();
	case TAG_MPEG4_PointLight:
		return PointLight_Create();
	case TAG_MPEG4_PointSet:
		return PointSet_Create();
	case TAG_MPEG4_PointSet2D:
		return PointSet2D_Create();
	case TAG_MPEG4_PositionInterpolator:
		return PositionInterpolator_Create();
	case TAG_MPEG4_PositionInterpolator2D:
		return PositionInterpolator2D_Create();
	case TAG_MPEG4_ProximitySensor2D:
		return ProximitySensor2D_Create();
	case TAG_MPEG4_ProximitySensor:
		return ProximitySensor_Create();
	case TAG_MPEG4_QuantizationParameter:
		return QuantizationParameter_Create();
	case TAG_MPEG4_Rectangle:
		return Rectangle_Create();
	case TAG_MPEG4_ScalarInterpolator:
		return ScalarInterpolator_Create();
	case TAG_MPEG4_Script:
		return Script_Create();
	case TAG_MPEG4_Shape:
		return Shape_Create();
	case TAG_MPEG4_Sound:
		return Sound_Create();
	case TAG_MPEG4_Sound2D:
		return Sound2D_Create();
	case TAG_MPEG4_Sphere:
		return Sphere_Create();
	case TAG_MPEG4_SphereSensor:
		return SphereSensor_Create();
	case TAG_MPEG4_SpotLight:
		return SpotLight_Create();
	case TAG_MPEG4_Switch:
		return Switch_Create();
	case TAG_MPEG4_TermCap:
		return TermCap_Create();
	case TAG_MPEG4_Text:
		return Text_Create();
	case TAG_MPEG4_TextureCoordinate:
		return TextureCoordinate_Create();
	case TAG_MPEG4_TextureTransform:
		return TextureTransform_Create();
	case TAG_MPEG4_TimeSensor:
		return TimeSensor_Create();
	case TAG_MPEG4_TouchSensor:
		return TouchSensor_Create();
	case TAG_MPEG4_Transform:
		return Transform_Create();
	case TAG_MPEG4_Transform2D:
		return Transform2D_Create();
	case TAG_MPEG4_Valuator:
		return Valuator_Create();
	case TAG_MPEG4_Viewpoint:
		return Viewpoint_Create();
	case TAG_MPEG4_VisibilitySensor:
		return VisibilitySensor_Create();
	case TAG_MPEG4_Viseme:
		return Viseme_Create();
	case TAG_MPEG4_WorldInfo:
		return WorldInfo_Create();
	case TAG_MPEG4_AcousticMaterial:
		return AcousticMaterial_Create();
	case TAG_MPEG4_AcousticScene:
		return AcousticScene_Create();
	case TAG_MPEG4_ApplicationWindow:
		return ApplicationWindow_Create();
	case TAG_MPEG4_BAP:
		return BAP_Create();
	case TAG_MPEG4_BDP:
		return BDP_Create();
	case TAG_MPEG4_Body:
		return Body_Create();
	case TAG_MPEG4_BodyDefTable:
		return BodyDefTable_Create();
	case TAG_MPEG4_BodySegmentConnectionHint:
		return BodySegmentConnectionHint_Create();
	case TAG_MPEG4_DirectiveSound:
		return DirectiveSound_Create();
	case TAG_MPEG4_Hierarchical3DMesh:
		return Hierarchical3DMesh_Create();
	case TAG_MPEG4_MaterialKey:
		return MaterialKey_Create();
	case TAG_MPEG4_PerceptualParameters:
		return PerceptualParameters_Create();
	case TAG_MPEG4_TemporalTransform:
		return TemporalTransform_Create();
	case TAG_MPEG4_TemporalGroup:
		return TemporalGroup_Create();
	case TAG_MPEG4_ServerCommand:
		return ServerCommand_Create();
	case TAG_MPEG4_InputSensor:
		return InputSensor_Create();
	case TAG_MPEG4_MatteTexture:
		return MatteTexture_Create();
	case TAG_MPEG4_MediaBuffer:
		return MediaBuffer_Create();
	case TAG_MPEG4_MediaControl:
		return MediaControl_Create();
	case TAG_MPEG4_MediaSensor:
		return MediaSensor_Create();
	case TAG_MPEG4_BitWrapper:
		return BitWrapper_Create();
	case TAG_MPEG4_CoordinateInterpolator4D:
		return CoordinateInterpolator4D_Create();
	case TAG_MPEG4_DepthImage:
		return DepthImage_Create();
	case TAG_MPEG4_FFD:
		return FFD_Create();
	case TAG_MPEG4_Implicit:
		return Implicit_Create();
	case TAG_MPEG4_XXLFM_Appearance:
		return XXLFM_Appearance_Create();
	case TAG_MPEG4_XXLFM_BlendList:
		return XXLFM_BlendList_Create();
	case TAG_MPEG4_XXLFM_FrameList:
		return XXLFM_FrameList_Create();
	case TAG_MPEG4_XXLFM_LightMap:
		return XXLFM_LightMap_Create();
	case TAG_MPEG4_XXLFM_SurfaceMapList:
		return XXLFM_SurfaceMapList_Create();
	case TAG_MPEG4_XXLFM_ViewMapList:
		return XXLFM_ViewMapList_Create();
	case TAG_MPEG4_MeshGrid:
		return MeshGrid_Create();
	case TAG_MPEG4_NonLinearDeformer:
		return NonLinearDeformer_Create();
	case TAG_MPEG4_NurbsCurve:
		return NurbsCurve_Create();
	case TAG_MPEG4_NurbsCurve2D:
		return NurbsCurve2D_Create();
	case TAG_MPEG4_NurbsSurface:
		return NurbsSurface_Create();
	case TAG_MPEG4_OctreeImage:
		return OctreeImage_Create();
	case TAG_MPEG4_XXParticles:
		return XXParticles_Create();
	case TAG_MPEG4_XXParticleInitBox:
		return XXParticleInitBox_Create();
	case TAG_MPEG4_XXPlanarObstacle:
		return XXPlanarObstacle_Create();
	case TAG_MPEG4_XXPointAttractor:
		return XXPointAttractor_Create();
	case TAG_MPEG4_PointTexture:
		return PointTexture_Create();
	case TAG_MPEG4_PositionAnimator:
		return PositionAnimator_Create();
	case TAG_MPEG4_PositionAnimator2D:
		return PositionAnimator2D_Create();
	case TAG_MPEG4_PositionInterpolator4D:
		return PositionInterpolator4D_Create();
	case TAG_MPEG4_ProceduralTexture:
		return ProceduralTexture_Create();
	case TAG_MPEG4_Quadric:
		return Quadric_Create();
	case TAG_MPEG4_SBBone:
		return SBBone_Create();
	case TAG_MPEG4_SBMuscle:
		return SBMuscle_Create();
	case TAG_MPEG4_SBSegment:
		return SBSegment_Create();
	case TAG_MPEG4_SBSite:
		return SBSite_Create();
	case TAG_MPEG4_SBSkinnedModel:
		return SBSkinnedModel_Create();
	case TAG_MPEG4_SBVCAnimation:
		return SBVCAnimation_Create();
	case TAG_MPEG4_ScalarAnimator:
		return ScalarAnimator_Create();
	case TAG_MPEG4_SimpleTexture:
		return SimpleTexture_Create();
	case TAG_MPEG4_SolidRep:
		return SolidRep_Create();
	case TAG_MPEG4_SubdivisionSurface:
		return SubdivisionSurface_Create();
	case TAG_MPEG4_SubdivSurfaceSector:
		return SubdivSurfaceSector_Create();
	case TAG_MPEG4_WaveletSubdivisionSurface:
		return WaveletSubdivisionSurface_Create();
	case TAG_MPEG4_Clipper2D:
		return Clipper2D_Create();
	case TAG_MPEG4_ColorTransform:
		return ColorTransform_Create();
	case TAG_MPEG4_Ellipse:
		return Ellipse_Create();
	case TAG_MPEG4_LinearGradient:
		return LinearGradient_Create();
	case TAG_MPEG4_PathLayout:
		return PathLayout_Create();
	case TAG_MPEG4_RadialGradient:
		return RadialGradient_Create();
	case TAG_MPEG4_SynthesizedTexture:
		return SynthesizedTexture_Create();
	case TAG_MPEG4_TransformMatrix2D:
		return TransformMatrix2D_Create();
	case TAG_MPEG4_Viewport:
		return Viewport_Create();
	case TAG_MPEG4_XCurve2D:
		return XCurve2D_Create();
	case TAG_MPEG4_XFontStyle:
		return XFontStyle_Create();
	case TAG_MPEG4_XLineProperties:
		return XLineProperties_Create();
	default:
		return NULL;
	}
}

const char *gf_sg_mpeg4_node_get_class_name(u32 NodeTag)
{
	switch (NodeTag) {
	case TAG_MPEG4_Anchor:
		return "Anchor";
	case TAG_MPEG4_AnimationStream:
		return "AnimationStream";
	case TAG_MPEG4_Appearance:
		return "Appearance";
	case TAG_MPEG4_AudioBuffer:
		return "AudioBuffer";
	case TAG_MPEG4_AudioClip:
		return "AudioClip";
	case TAG_MPEG4_AudioDelay:
		return "AudioDelay";
	case TAG_MPEG4_AudioFX:
		return "AudioFX";
	case TAG_MPEG4_AudioMix:
		return "AudioMix";
	case TAG_MPEG4_AudioSource:
		return "AudioSource";
	case TAG_MPEG4_AudioSwitch:
		return "AudioSwitch";
	case TAG_MPEG4_Background:
		return "Background";
	case TAG_MPEG4_Background2D:
		return "Background2D";
	case TAG_MPEG4_Billboard:
		return "Billboard";
	case TAG_MPEG4_Bitmap:
		return "Bitmap";
	case TAG_MPEG4_Box:
		return "Box";
	case TAG_MPEG4_Circle:
		return "Circle";
	case TAG_MPEG4_Collision:
		return "Collision";
	case TAG_MPEG4_Color:
		return "Color";
	case TAG_MPEG4_ColorInterpolator:
		return "ColorInterpolator";
	case TAG_MPEG4_CompositeTexture2D:
		return "CompositeTexture2D";
	case TAG_MPEG4_CompositeTexture3D:
		return "CompositeTexture3D";
	case TAG_MPEG4_Conditional:
		return "Conditional";
	case TAG_MPEG4_Cone:
		return "Cone";
	case TAG_MPEG4_Coordinate:
		return "Coordinate";
	case TAG_MPEG4_Coordinate2D:
		return "Coordinate2D";
	case TAG_MPEG4_CoordinateInterpolator:
		return "CoordinateInterpolator";
	case TAG_MPEG4_CoordinateInterpolator2D:
		return "CoordinateInterpolator2D";
	case TAG_MPEG4_Curve2D:
		return "Curve2D";
	case TAG_MPEG4_Cylinder:
		return "Cylinder";
	case TAG_MPEG4_CylinderSensor:
		return "CylinderSensor";
	case TAG_MPEG4_DirectionalLight:
		return "DirectionalLight";
	case TAG_MPEG4_DiscSensor:
		return "DiscSensor";
	case TAG_MPEG4_ElevationGrid:
		return "ElevationGrid";
	case TAG_MPEG4_Expression:
		return "Expression";
	case TAG_MPEG4_Extrusion:
		return "Extrusion";
	case TAG_MPEG4_Face:
		return "Face";
	case TAG_MPEG4_FaceDefMesh:
		return "FaceDefMesh";
	case TAG_MPEG4_FaceDefTables:
		return "FaceDefTables";
	case TAG_MPEG4_FaceDefTransform:
		return "FaceDefTransform";
	case TAG_MPEG4_FAP:
		return "FAP";
	case TAG_MPEG4_FDP:
		return "FDP";
	case TAG_MPEG4_FIT:
		return "FIT";
	case TAG_MPEG4_Fog:
		return "Fog";
	case TAG_MPEG4_FontStyle:
		return "FontStyle";
	case TAG_MPEG4_Form:
		return "Form";
	case TAG_MPEG4_Group:
		return "Group";
	case TAG_MPEG4_ImageTexture:
		return "ImageTexture";
	case TAG_MPEG4_IndexedFaceSet:
		return "IndexedFaceSet";
	case TAG_MPEG4_IndexedFaceSet2D:
		return "IndexedFaceSet2D";
	case TAG_MPEG4_IndexedLineSet:
		return "IndexedLineSet";
	case TAG_MPEG4_IndexedLineSet2D:
		return "IndexedLineSet2D";
	case TAG_MPEG4_Inline:
		return "Inline";
	case TAG_MPEG4_LOD:
		return "LOD";
	case TAG_MPEG4_Layer2D:
		return "Layer2D";
	case TAG_MPEG4_Layer3D:
		return "Layer3D";
	case TAG_MPEG4_Layout:
		return "Layout";
	case TAG_MPEG4_LineProperties:
		return "LineProperties";
	case TAG_MPEG4_ListeningPoint:
		return "ListeningPoint";
	case TAG_MPEG4_Material:
		return "Material";
	case TAG_MPEG4_Material2D:
		return "Material2D";
	case TAG_MPEG4_MovieTexture:
		return "MovieTexture";
	case TAG_MPEG4_NavigationInfo:
		return "NavigationInfo";
	case TAG_MPEG4_Normal:
		return "Normal";
	case TAG_MPEG4_NormalInterpolator:
		return "NormalInterpolator";
	case TAG_MPEG4_OrderedGroup:
		return "OrderedGroup";
	case TAG_MPEG4_OrientationInterpolator:
		return "OrientationInterpolator";
	case TAG_MPEG4_PixelTexture:
		return "PixelTexture";
	case TAG_MPEG4_PlaneSensor:
		return "PlaneSensor";
	case TAG_MPEG4_PlaneSensor2D:
		return "PlaneSensor2D";
	case TAG_MPEG4_PointLight:
		return "PointLight";
	case TAG_MPEG4_PointSet:
		return "PointSet";
	case TAG_MPEG4_PointSet2D:
		return "PointSet2D";
	case TAG_MPEG4_PositionInterpolator:
		return "PositionInterpolator";
	case TAG_MPEG4_PositionInterpolator2D:
		return "PositionInterpolator2D";
	case TAG_MPEG4_ProximitySensor2D:
		return "ProximitySensor2D";
	case TAG_MPEG4_ProximitySensor:
		return "ProximitySensor";
	case TAG_MPEG4_QuantizationParameter:
		return "QuantizationParameter";
	case TAG_MPEG4_Rectangle:
		return "Rectangle";
	case TAG_MPEG4_ScalarInterpolator:
		return "ScalarInterpolator";
	case TAG_MPEG4_Script:
		return "Script";
	case TAG_MPEG4_Shape:
		return "Shape";
	case TAG_MPEG4_Sound:
		return "Sound";
	case TAG_MPEG4_Sound2D:
		return "Sound2D";
	case TAG_MPEG4_Sphere:
		return "Sphere";
	case TAG_MPEG4_SphereSensor:
		return "SphereSensor";
	case TAG_MPEG4_SpotLight:
		return "SpotLight";
	case TAG_MPEG4_Switch:
		return "Switch";
	case TAG_MPEG4_TermCap:
		return "TermCap";
	case TAG_MPEG4_Text:
		return "Text";
	case TAG_MPEG4_TextureCoordinate:
		return "TextureCoordinate";
	case TAG_MPEG4_TextureTransform:
		return "TextureTransform";
	case TAG_MPEG4_TimeSensor:
		return "TimeSensor";
	case TAG_MPEG4_TouchSensor:
		return "TouchSensor";
	case TAG_MPEG4_Transform:
		return "Transform";
	case TAG_MPEG4_Transform2D:
		return "Transform2D";
	case TAG_MPEG4_Valuator:
		return "Valuator";
	case TAG_MPEG4_Viewpoint:
		return "Viewpoint";
	case TAG_MPEG4_VisibilitySensor:
		return "VisibilitySensor";
	case TAG_MPEG4_Viseme:
		return "Viseme";
	case TAG_MPEG4_WorldInfo:
		return "WorldInfo";
	case TAG_MPEG4_AcousticMaterial:
		return "AcousticMaterial";
	case TAG_MPEG4_AcousticScene:
		return "AcousticScene";
	case TAG_MPEG4_ApplicationWindow:
		return "ApplicationWindow";
	case TAG_MPEG4_BAP:
		return "BAP";
	case TAG_MPEG4_BDP:
		return "BDP";
	case TAG_MPEG4_Body:
		return "Body";
	case TAG_MPEG4_BodyDefTable:
		return "BodyDefTable";
	case TAG_MPEG4_BodySegmentConnectionHint:
		return "BodySegmentConnectionHint";
	case TAG_MPEG4_DirectiveSound:
		return "DirectiveSound";
	case TAG_MPEG4_Hierarchical3DMesh:
		return "Hierarchical3DMesh";
	case TAG_MPEG4_MaterialKey:
		return "MaterialKey";
	case TAG_MPEG4_PerceptualParameters:
		return "PerceptualParameters";
	case TAG_MPEG4_TemporalTransform:
		return "TemporalTransform";
	case TAG_MPEG4_TemporalGroup:
		return "TemporalGroup";
	case TAG_MPEG4_ServerCommand:
		return "ServerCommand";
	case TAG_MPEG4_InputSensor:
		return "InputSensor";
	case TAG_MPEG4_MatteTexture:
		return "MatteTexture";
	case TAG_MPEG4_MediaBuffer:
		return "MediaBuffer";
	case TAG_MPEG4_MediaControl:
		return "MediaControl";
	case TAG_MPEG4_MediaSensor:
		return "MediaSensor";
	case TAG_MPEG4_BitWrapper:
		return "BitWrapper";
	case TAG_MPEG4_CoordinateInterpolator4D:
		return "CoordinateInterpolator4D";
	case TAG_MPEG4_DepthImage:
		return "DepthImage";
	case TAG_MPEG4_FFD:
		return "FFD";
	case TAG_MPEG4_Implicit:
		return "Implicit";
	case TAG_MPEG4_XXLFM_Appearance:
		return "XXLFM_Appearance";
	case TAG_MPEG4_XXLFM_BlendList:
		return "XXLFM_BlendList";
	case TAG_MPEG4_XXLFM_FrameList:
		return "XXLFM_FrameList";
	case TAG_MPEG4_XXLFM_LightMap:
		return "XXLFM_LightMap";
	case TAG_MPEG4_XXLFM_SurfaceMapList:
		return "XXLFM_SurfaceMapList";
	case TAG_MPEG4_XXLFM_ViewMapList:
		return "XXLFM_ViewMapList";
	case TAG_MPEG4_MeshGrid:
		return "MeshGrid";
	case TAG_MPEG4_NonLinearDeformer:
		return "NonLinearDeformer";
	case TAG_MPEG4_NurbsCurve:
		return "NurbsCurve";
	case TAG_MPEG4_NurbsCurve2D:
		return "NurbsCurve2D";
	case TAG_MPEG4_NurbsSurface:
		return "NurbsSurface";
	case TAG_MPEG4_OctreeImage:
		return "OctreeImage";
	case TAG_MPEG4_XXParticles:
		return "XXParticles";
	case TAG_MPEG4_XXParticleInitBox:
		return "XXParticleInitBox";
	case TAG_MPEG4_XXPlanarObstacle:
		return "XXPlanarObstacle";
	case TAG_MPEG4_XXPointAttractor:
		return "XXPointAttractor";
	case TAG_MPEG4_PointTexture:
		return "PointTexture";
	case TAG_MPEG4_PositionAnimator:
		return "PositionAnimator";
	case TAG_MPEG4_PositionAnimator2D:
		return "PositionAnimator2D";
	case TAG_MPEG4_PositionInterpolator4D:
		return "PositionInterpolator4D";
	case TAG_MPEG4_ProceduralTexture:
		return "ProceduralTexture";
	case TAG_MPEG4_Quadric:
		return "Quadric";
	case TAG_MPEG4_SBBone:
		return "SBBone";
	case TAG_MPEG4_SBMuscle:
		return "SBMuscle";
	case TAG_MPEG4_SBSegment:
		return "SBSegment";
	case TAG_MPEG4_SBSite:
		return "SBSite";
	case TAG_MPEG4_SBSkinnedModel:
		return "SBSkinnedModel";
	case TAG_MPEG4_SBVCAnimation:
		return "SBVCAnimation";
	case TAG_MPEG4_ScalarAnimator:
		return "ScalarAnimator";
	case TAG_MPEG4_SimpleTexture:
		return "SimpleTexture";
	case TAG_MPEG4_SolidRep:
		return "SolidRep";
	case TAG_MPEG4_SubdivisionSurface:
		return "SubdivisionSurface";
	case TAG_MPEG4_SubdivSurfaceSector:
		return "SubdivSurfaceSector";
	case TAG_MPEG4_WaveletSubdivisionSurface:
		return "WaveletSubdivisionSurface";
	case TAG_MPEG4_Clipper2D:
		return "Clipper2D";
	case TAG_MPEG4_ColorTransform:
		return "ColorTransform";
	case TAG_MPEG4_Ellipse:
		return "Ellipse";
	case TAG_MPEG4_LinearGradient:
		return "LinearGradient";
	case TAG_MPEG4_PathLayout:
		return "PathLayout";
	case TAG_MPEG4_RadialGradient:
		return "RadialGradient";
	case TAG_MPEG4_SynthesizedTexture:
		return "SynthesizedTexture";
	case TAG_MPEG4_TransformMatrix2D:
		return "TransformMatrix2D";
	case TAG_MPEG4_Viewport:
		return "Viewport";
	case TAG_MPEG4_XCurve2D:
		return "XCurve2D";
	case TAG_MPEG4_XFontStyle:
		return "XFontStyle";
	case TAG_MPEG4_XLineProperties:
		return "XLineProperties";
	default:
		return "Unknown Node";
	}
}

void gf_sg_mpeg4_node_del(GF_Node *node)
{
	switch (node->sgprivate->tag) {
	case TAG_MPEG4_Anchor:
		Anchor_Del(node); return;
	case TAG_MPEG4_AnimationStream:
		AnimationStream_Del(node); return;
	case TAG_MPEG4_Appearance:
		Appearance_Del(node); return;
	case TAG_MPEG4_AudioBuffer:
		AudioBuffer_Del(node); return;
	case TAG_MPEG4_AudioClip:
		AudioClip_Del(node); return;
	case TAG_MPEG4_AudioDelay:
		AudioDelay_Del(node); return;
	case TAG_MPEG4_AudioFX:
		AudioFX_Del(node); return;
	case TAG_MPEG4_AudioMix:
		AudioMix_Del(node); return;
	case TAG_MPEG4_AudioSource:
		AudioSource_Del(node); return;
	case TAG_MPEG4_AudioSwitch:
		AudioSwitch_Del(node); return;
	case TAG_MPEG4_Background:
		Background_Del(node); return;
	case TAG_MPEG4_Background2D:
		Background2D_Del(node); return;
	case TAG_MPEG4_Billboard:
		Billboard_Del(node); return;
	case TAG_MPEG4_Bitmap:
		Bitmap_Del(node); return;
	case TAG_MPEG4_Box:
		Box_Del(node); return;
	case TAG_MPEG4_Circle:
		Circle_Del(node); return;
	case TAG_MPEG4_Collision:
		Collision_Del(node); return;
	case TAG_MPEG4_Color:
		Color_Del(node); return;
	case TAG_MPEG4_ColorInterpolator:
		ColorInterpolator_Del(node); return;
	case TAG_MPEG4_CompositeTexture2D:
		CompositeTexture2D_Del(node); return;
	case TAG_MPEG4_CompositeTexture3D:
		CompositeTexture3D_Del(node); return;
	case TAG_MPEG4_Conditional:
		Conditional_Del(node); return;
	case TAG_MPEG4_Cone:
		Cone_Del(node); return;
	case TAG_MPEG4_Coordinate:
		Coordinate_Del(node); return;
	case TAG_MPEG4_Coordinate2D:
		Coordinate2D_Del(node); return;
	case TAG_MPEG4_CoordinateInterpolator:
		CoordinateInterpolator_Del(node); return;
	case TAG_MPEG4_CoordinateInterpolator2D:
		CoordinateInterpolator2D_Del(node); return;
	case TAG_MPEG4_Curve2D:
		Curve2D_Del(node); return;
	case TAG_MPEG4_Cylinder:
		Cylinder_Del(node); return;
	case TAG_MPEG4_CylinderSensor:
		CylinderSensor_Del(node); return;
	case TAG_MPEG4_DirectionalLight:
		DirectionalLight_Del(node); return;
	case TAG_MPEG4_DiscSensor:
		DiscSensor_Del(node); return;
	case TAG_MPEG4_ElevationGrid:
		ElevationGrid_Del(node); return;
	case TAG_MPEG4_Expression:
		Expression_Del(node); return;
	case TAG_MPEG4_Extrusion:
		Extrusion_Del(node); return;
	case TAG_MPEG4_Face:
		Face_Del(node); return;
	case TAG_MPEG4_FaceDefMesh:
		FaceDefMesh_Del(node); return;
	case TAG_MPEG4_FaceDefTables:
		FaceDefTables_Del(node); return;
	case TAG_MPEG4_FaceDefTransform:
		FaceDefTransform_Del(node); return;
	case TAG_MPEG4_FAP:
		FAP_Del(node); return;
	case TAG_MPEG4_FDP:
		FDP_Del(node); return;
	case TAG_MPEG4_FIT:
		FIT_Del(node); return;
	case TAG_MPEG4_Fog:
		Fog_Del(node); return;
	case TAG_MPEG4_FontStyle:
		FontStyle_Del(node); return;
	case TAG_MPEG4_Form:
		Form_Del(node); return;
	case TAG_MPEG4_Group:
		Group_Del(node); return;
	case TAG_MPEG4_ImageTexture:
		ImageTexture_Del(node); return;
	case TAG_MPEG4_IndexedFaceSet:
		IndexedFaceSet_Del(node); return;
	case TAG_MPEG4_IndexedFaceSet2D:
		IndexedFaceSet2D_Del(node); return;
	case TAG_MPEG4_IndexedLineSet:
		IndexedLineSet_Del(node); return;
	case TAG_MPEG4_IndexedLineSet2D:
		IndexedLineSet2D_Del(node); return;
	case TAG_MPEG4_Inline:
		Inline_Del(node); return;
	case TAG_MPEG4_LOD:
		LOD_Del(node); return;
	case TAG_MPEG4_Layer2D:
		Layer2D_Del(node); return;
	case TAG_MPEG4_Layer3D:
		Layer3D_Del(node); return;
	case TAG_MPEG4_Layout:
		Layout_Del(node); return;
	case TAG_MPEG4_LineProperties:
		LineProperties_Del(node); return;
	case TAG_MPEG4_ListeningPoint:
		ListeningPoint_Del(node); return;
	case TAG_MPEG4_Material:
		Material_Del(node); return;
	case TAG_MPEG4_Material2D:
		Material2D_Del(node); return;
	case TAG_MPEG4_MovieTexture:
		MovieTexture_Del(node); return;
	case TAG_MPEG4_NavigationInfo:
		NavigationInfo_Del(node); return;
	case TAG_MPEG4_Normal:
		Normal_Del(node); return;
	case TAG_MPEG4_NormalInterpolator:
		NormalInterpolator_Del(node); return;
	case TAG_MPEG4_OrderedGroup:
		OrderedGroup_Del(node); return;
	case TAG_MPEG4_OrientationInterpolator:
		OrientationInterpolator_Del(node); return;
	case TAG_MPEG4_PixelTexture:
		PixelTexture_Del(node); return;
	case TAG_MPEG4_PlaneSensor:
		PlaneSensor_Del(node); return;
	case TAG_MPEG4_PlaneSensor2D:
		PlaneSensor2D_Del(node); return;
	case TAG_MPEG4_PointLight:
		PointLight_Del(node); return;
	case TAG_MPEG4_PointSet:
		PointSet_Del(node); return;
	case TAG_MPEG4_PointSet2D:
		PointSet2D_Del(node); return;
	case TAG_MPEG4_PositionInterpolator:
		PositionInterpolator_Del(node); return;
	case TAG_MPEG4_PositionInterpolator2D:
		PositionInterpolator2D_Del(node); return;
	case TAG_MPEG4_ProximitySensor2D:
		ProximitySensor2D_Del(node); return;
	case TAG_MPEG4_ProximitySensor:
		ProximitySensor_Del(node); return;
	case TAG_MPEG4_QuantizationParameter:
		QuantizationParameter_Del(node); return;
	case TAG_MPEG4_Rectangle:
		Rectangle_Del(node); return;
	case TAG_MPEG4_ScalarInterpolator:
		ScalarInterpolator_Del(node); return;
	case TAG_MPEG4_Script:
		Script_Del(node); return;
	case TAG_MPEG4_Shape:
		Shape_Del(node); return;
	case TAG_MPEG4_Sound:
		Sound_Del(node); return;
	case TAG_MPEG4_Sound2D:
		Sound2D_Del(node); return;
	case TAG_MPEG4_Sphere:
		Sphere_Del(node); return;
	case TAG_MPEG4_SphereSensor:
		SphereSensor_Del(node); return;
	case TAG_MPEG4_SpotLight:
		SpotLight_Del(node); return;
	case TAG_MPEG4_Switch:
		Switch_Del(node); return;
	case TAG_MPEG4_TermCap:
		TermCap_Del(node); return;
	case TAG_MPEG4_Text:
		Text_Del(node); return;
	case TAG_MPEG4_TextureCoordinate:
		TextureCoordinate_Del(node); return;
	case TAG_MPEG4_TextureTransform:
		TextureTransform_Del(node); return;
	case TAG_MPEG4_TimeSensor:
		TimeSensor_Del(node); return;
	case TAG_MPEG4_TouchSensor:
		TouchSensor_Del(node); return;
	case TAG_MPEG4_Transform:
		Transform_Del(node); return;
	case TAG_MPEG4_Transform2D:
		Transform2D_Del(node); return;
	case TAG_MPEG4_Valuator:
		Valuator_Del(node); return;
	case TAG_MPEG4_Viewpoint:
		Viewpoint_Del(node); return;
	case TAG_MPEG4_VisibilitySensor:
		VisibilitySensor_Del(node); return;
	case TAG_MPEG4_Viseme:
		Viseme_Del(node); return;
	case TAG_MPEG4_WorldInfo:
		WorldInfo_Del(node); return;
	case TAG_MPEG4_AcousticMaterial:
		AcousticMaterial_Del(node); return;
	case TAG_MPEG4_AcousticScene:
		AcousticScene_Del(node); return;
	case TAG_MPEG4_ApplicationWindow:
		ApplicationWindow_Del(node); return;
	case TAG_MPEG4_BAP:
		BAP_Del(node); return;
	case TAG_MPEG4_BDP:
		BDP_Del(node); return;
	case TAG_MPEG4_Body:
		Body_Del(node); return;
	case TAG_MPEG4_BodyDefTable:
		BodyDefTable_Del(node); return;
	case TAG_MPEG4_BodySegmentConnectionHint:
		BodySegmentConnectionHint_Del(node); return;
	case TAG_MPEG4_DirectiveSound:
		DirectiveSound_Del(node); return;
	case TAG_MPEG4_Hierarchical3DMesh:
		Hierarchical3DMesh_Del(node); return;
	case TAG_MPEG4_MaterialKey:
		MaterialKey_Del(node); return;
	case TAG_MPEG4_PerceptualParameters:
		PerceptualParameters_Del(node); return;
	case TAG_MPEG4_TemporalTransform:
		TemporalTransform_Del(node); return;
	case TAG_MPEG4_TemporalGroup:
		TemporalGroup_Del(node); return;
	case TAG_MPEG4_ServerCommand:
		ServerCommand_Del(node); return;
	case TAG_MPEG4_InputSensor:
		InputSensor_Del(node); return;
	case TAG_MPEG4_MatteTexture:
		MatteTexture_Del(node); return;
	case TAG_MPEG4_MediaBuffer:
		MediaBuffer_Del(node); return;
	case TAG_MPEG4_MediaControl:
		MediaControl_Del(node); return;
	case TAG_MPEG4_MediaSensor:
		MediaSensor_Del(node); return;
	case TAG_MPEG4_BitWrapper:
		BitWrapper_Del(node); return;
	case TAG_MPEG4_CoordinateInterpolator4D:
		CoordinateInterpolator4D_Del(node); return;
	case TAG_MPEG4_DepthImage:
		DepthImage_Del(node); return;
	case TAG_MPEG4_FFD:
		FFD_Del(node); return;
	case TAG_MPEG4_Implicit:
		Implicit_Del(node); return;
	case TAG_MPEG4_XXLFM_Appearance:
		XXLFM_Appearance_Del(node); return;
	case TAG_MPEG4_XXLFM_BlendList:
		XXLFM_BlendList_Del(node); return;
	case TAG_MPEG4_XXLFM_FrameList:
		XXLFM_FrameList_Del(node); return;
	case TAG_MPEG4_XXLFM_LightMap:
		XXLFM_LightMap_Del(node); return;
	case TAG_MPEG4_XXLFM_SurfaceMapList:
		XXLFM_SurfaceMapList_Del(node); return;
	case TAG_MPEG4_XXLFM_ViewMapList:
		XXLFM_ViewMapList_Del(node); return;
	case TAG_MPEG4_MeshGrid:
		MeshGrid_Del(node); return;
	case TAG_MPEG4_NonLinearDeformer:
		NonLinearDeformer_Del(node); return;
	case TAG_MPEG4_NurbsCurve:
		NurbsCurve_Del(node); return;
	case TAG_MPEG4_NurbsCurve2D:
		NurbsCurve2D_Del(node); return;
	case TAG_MPEG4_NurbsSurface:
		NurbsSurface_Del(node); return;
	case TAG_MPEG4_OctreeImage:
		OctreeImage_Del(node); return;
	case TAG_MPEG4_XXParticles:
		XXParticles_Del(node); return;
	case TAG_MPEG4_XXParticleInitBox:
		XXParticleInitBox_Del(node); return;
	case TAG_MPEG4_XXPlanarObstacle:
		XXPlanarObstacle_Del(node); return;
	case TAG_MPEG4_XXPointAttractor:
		XXPointAttractor_Del(node); return;
	case TAG_MPEG4_PointTexture:
		PointTexture_Del(node); return;
	case TAG_MPEG4_PositionAnimator:
		PositionAnimator_Del(node); return;
	case TAG_MPEG4_PositionAnimator2D:
		PositionAnimator2D_Del(node); return;
	case TAG_MPEG4_PositionInterpolator4D:
		PositionInterpolator4D_Del(node); return;
	case TAG_MPEG4_ProceduralTexture:
		ProceduralTexture_Del(node); return;
	case TAG_MPEG4_Quadric:
		Quadric_Del(node); return;
	case TAG_MPEG4_SBBone:
		SBBone_Del(node); return;
	case TAG_MPEG4_SBMuscle:
		SBMuscle_Del(node); return;
	case TAG_MPEG4_SBSegment:
		SBSegment_Del(node); return;
	case TAG_MPEG4_SBSite:
		SBSite_Del(node); return;
	case TAG_MPEG4_SBSkinnedModel:
		SBSkinnedModel_Del(node); return;
	case TAG_MPEG4_SBVCAnimation:
		SBVCAnimation_Del(node); return;
	case TAG_MPEG4_ScalarAnimator:
		ScalarAnimator_Del(node); return;
	case TAG_MPEG4_SimpleTexture:
		SimpleTexture_Del(node); return;
	case TAG_MPEG4_SolidRep:
		SolidRep_Del(node); return;
	case TAG_MPEG4_SubdivisionSurface:
		SubdivisionSurface_Del(node); return;
	case TAG_MPEG4_SubdivSurfaceSector:
		SubdivSurfaceSector_Del(node); return;
	case TAG_MPEG4_WaveletSubdivisionSurface:
		WaveletSubdivisionSurface_Del(node); return;
	case TAG_MPEG4_Clipper2D:
		Clipper2D_Del(node); return;
	case TAG_MPEG4_ColorTransform:
		ColorTransform_Del(node); return;
	case TAG_MPEG4_Ellipse:
		Ellipse_Del(node); return;
	case TAG_MPEG4_LinearGradient:
		LinearGradient_Del(node); return;
	case TAG_MPEG4_PathLayout:
		PathLayout_Del(node); return;
	case TAG_MPEG4_RadialGradient:
		RadialGradient_Del(node); return;
	case TAG_MPEG4_SynthesizedTexture:
		SynthesizedTexture_Del(node); return;
	case TAG_MPEG4_TransformMatrix2D:
		TransformMatrix2D_Del(node); return;
	case TAG_MPEG4_Viewport:
		Viewport_Del(node); return;
	case TAG_MPEG4_XCurve2D:
		XCurve2D_Del(node); return;
	case TAG_MPEG4_XFontStyle:
		XFontStyle_Del(node); return;
	case TAG_MPEG4_XLineProperties:
		XLineProperties_Del(node); return;
	default:
		return;
	}
}

u32 gf_sg_mpeg4_node_get_field_count(GF_Node *node, u8 code_mode)
{
	switch (node->sgprivate->tag) {
	case TAG_MPEG4_Anchor:return Anchor_get_field_count(node, code_mode);
	case TAG_MPEG4_AnimationStream:return AnimationStream_get_field_count(node, code_mode);
	case TAG_MPEG4_Appearance:return Appearance_get_field_count(node, code_mode);
	case TAG_MPEG4_AudioBuffer:return AudioBuffer_get_field_count(node, code_mode);
	case TAG_MPEG4_AudioClip:return AudioClip_get_field_count(node, code_mode);
	case TAG_MPEG4_AudioDelay:return AudioDelay_get_field_count(node, code_mode);
	case TAG_MPEG4_AudioFX:return AudioFX_get_field_count(node, code_mode);
	case TAG_MPEG4_AudioMix:return AudioMix_get_field_count(node, code_mode);
	case TAG_MPEG4_AudioSource:return AudioSource_get_field_count(node, code_mode);
	case TAG_MPEG4_AudioSwitch:return AudioSwitch_get_field_count(node, code_mode);
	case TAG_MPEG4_Background:return Background_get_field_count(node, code_mode);
	case TAG_MPEG4_Background2D:return Background2D_get_field_count(node, code_mode);
	case TAG_MPEG4_Billboard:return Billboard_get_field_count(node, code_mode);
	case TAG_MPEG4_Bitmap:return Bitmap_get_field_count(node, code_mode);
	case TAG_MPEG4_Box:return Box_get_field_count(node, code_mode);
	case TAG_MPEG4_Circle:return Circle_get_field_count(node, code_mode);
	case TAG_MPEG4_Collision:return Collision_get_field_count(node, code_mode);
	case TAG_MPEG4_Color:return Color_get_field_count(node, code_mode);
	case TAG_MPEG4_ColorInterpolator:return ColorInterpolator_get_field_count(node, code_mode);
	case TAG_MPEG4_CompositeTexture2D:return CompositeTexture2D_get_field_count(node, code_mode);
	case TAG_MPEG4_CompositeTexture3D:return CompositeTexture3D_get_field_count(node, code_mode);
	case TAG_MPEG4_Conditional:return Conditional_get_field_count(node, code_mode);
	case TAG_MPEG4_Cone:return Cone_get_field_count(node, code_mode);
	case TAG_MPEG4_Coordinate:return Coordinate_get_field_count(node, code_mode);
	case TAG_MPEG4_Coordinate2D:return Coordinate2D_get_field_count(node, code_mode);
	case TAG_MPEG4_CoordinateInterpolator:return CoordinateInterpolator_get_field_count(node, code_mode);
	case TAG_MPEG4_CoordinateInterpolator2D:return CoordinateInterpolator2D_get_field_count(node, code_mode);
	case TAG_MPEG4_Curve2D:return Curve2D_get_field_count(node, code_mode);
	case TAG_MPEG4_Cylinder:return Cylinder_get_field_count(node, code_mode);
	case TAG_MPEG4_CylinderSensor:return CylinderSensor_get_field_count(node, code_mode);
	case TAG_MPEG4_DirectionalLight:return DirectionalLight_get_field_count(node, code_mode);
	case TAG_MPEG4_DiscSensor:return DiscSensor_get_field_count(node, code_mode);
	case TAG_MPEG4_ElevationGrid:return ElevationGrid_get_field_count(node, code_mode);
	case TAG_MPEG4_Expression:return Expression_get_field_count(node, code_mode);
	case TAG_MPEG4_Extrusion:return Extrusion_get_field_count(node, code_mode);
	case TAG_MPEG4_Face:return Face_get_field_count(node, code_mode);
	case TAG_MPEG4_FaceDefMesh:return FaceDefMesh_get_field_count(node, code_mode);
	case TAG_MPEG4_FaceDefTables:return FaceDefTables_get_field_count(node, code_mode);
	case TAG_MPEG4_FaceDefTransform:return FaceDefTransform_get_field_count(node, code_mode);
	case TAG_MPEG4_FAP:return FAP_get_field_count(node, code_mode);
	case TAG_MPEG4_FDP:return FDP_get_field_count(node, code_mode);
	case TAG_MPEG4_FIT:return FIT_get_field_count(node, code_mode);
	case TAG_MPEG4_Fog:return Fog_get_field_count(node, code_mode);
	case TAG_MPEG4_FontStyle:return FontStyle_get_field_count(node, code_mode);
	case TAG_MPEG4_Form:return Form_get_field_count(node, code_mode);
	case TAG_MPEG4_Group:return Group_get_field_count(node, code_mode);
	case TAG_MPEG4_ImageTexture:return ImageTexture_get_field_count(node, code_mode);
	case TAG_MPEG4_IndexedFaceSet:return IndexedFaceSet_get_field_count(node, code_mode);
	case TAG_MPEG4_IndexedFaceSet2D:return IndexedFaceSet2D_get_field_count(node, code_mode);
	case TAG_MPEG4_IndexedLineSet:return IndexedLineSet_get_field_count(node, code_mode);
	case TAG_MPEG4_IndexedLineSet2D:return IndexedLineSet2D_get_field_count(node, code_mode);
	case TAG_MPEG4_Inline:return Inline_get_field_count(node, code_mode);
	case TAG_MPEG4_LOD:return LOD_get_field_count(node, code_mode);
	case TAG_MPEG4_Layer2D:return Layer2D_get_field_count(node, code_mode);
	case TAG_MPEG4_Layer3D:return Layer3D_get_field_count(node, code_mode);
	case TAG_MPEG4_Layout:return Layout_get_field_count(node, code_mode);
	case TAG_MPEG4_LineProperties:return LineProperties_get_field_count(node, code_mode);
	case TAG_MPEG4_ListeningPoint:return ListeningPoint_get_field_count(node, code_mode);
	case TAG_MPEG4_Material:return Material_get_field_count(node, code_mode);
	case TAG_MPEG4_Material2D:return Material2D_get_field_count(node, code_mode);
	case TAG_MPEG4_MovieTexture:return MovieTexture_get_field_count(node, code_mode);
	case TAG_MPEG4_NavigationInfo:return NavigationInfo_get_field_count(node, code_mode);
	case TAG_MPEG4_Normal:return Normal_get_field_count(node, code_mode);
	case TAG_MPEG4_NormalInterpolator:return NormalInterpolator_get_field_count(node, code_mode);
	case TAG_MPEG4_OrderedGroup:return OrderedGroup_get_field_count(node, code_mode);
	case TAG_MPEG4_OrientationInterpolator:return OrientationInterpolator_get_field_count(node, code_mode);
	case TAG_MPEG4_PixelTexture:return PixelTexture_get_field_count(node, code_mode);
	case TAG_MPEG4_PlaneSensor:return PlaneSensor_get_field_count(node, code_mode);
	case TAG_MPEG4_PlaneSensor2D:return PlaneSensor2D_get_field_count(node, code_mode);
	case TAG_MPEG4_PointLight:return PointLight_get_field_count(node, code_mode);
	case TAG_MPEG4_PointSet:return PointSet_get_field_count(node, code_mode);
	case TAG_MPEG4_PointSet2D:return PointSet2D_get_field_count(node, code_mode);
	case TAG_MPEG4_PositionInterpolator:return PositionInterpolator_get_field_count(node, code_mode);
	case TAG_MPEG4_PositionInterpolator2D:return PositionInterpolator2D_get_field_count(node, code_mode);
	case TAG_MPEG4_ProximitySensor2D:return ProximitySensor2D_get_field_count(node, code_mode);
	case TAG_MPEG4_ProximitySensor:return ProximitySensor_get_field_count(node, code_mode);
	case TAG_MPEG4_QuantizationParameter:return QuantizationParameter_get_field_count(node, code_mode);
	case TAG_MPEG4_Rectangle:return Rectangle_get_field_count(node, code_mode);
	case TAG_MPEG4_ScalarInterpolator:return ScalarInterpolator_get_field_count(node, code_mode);
	case TAG_MPEG4_Script:return Script_get_field_count(node, code_mode);
	case TAG_MPEG4_Shape:return Shape_get_field_count(node, code_mode);
	case TAG_MPEG4_Sound:return Sound_get_field_count(node, code_mode);
	case TAG_MPEG4_Sound2D:return Sound2D_get_field_count(node, code_mode);
	case TAG_MPEG4_Sphere:return Sphere_get_field_count(node, code_mode);
	case TAG_MPEG4_SphereSensor:return SphereSensor_get_field_count(node, code_mode);
	case TAG_MPEG4_SpotLight:return SpotLight_get_field_count(node, code_mode);
	case TAG_MPEG4_Switch:return Switch_get_field_count(node, code_mode);
	case TAG_MPEG4_TermCap:return TermCap_get_field_count(node, code_mode);
	case TAG_MPEG4_Text:return Text_get_field_count(node, code_mode);
	case TAG_MPEG4_TextureCoordinate:return TextureCoordinate_get_field_count(node, code_mode);
	case TAG_MPEG4_TextureTransform:return TextureTransform_get_field_count(node, code_mode);
	case TAG_MPEG4_TimeSensor:return TimeSensor_get_field_count(node, code_mode);
	case TAG_MPEG4_TouchSensor:return TouchSensor_get_field_count(node, code_mode);
	case TAG_MPEG4_Transform:return Transform_get_field_count(node, code_mode);
	case TAG_MPEG4_Transform2D:return Transform2D_get_field_count(node, code_mode);
	case TAG_MPEG4_Valuator:return Valuator_get_field_count(node, code_mode);
	case TAG_MPEG4_Viewpoint:return Viewpoint_get_field_count(node, code_mode);
	case TAG_MPEG4_VisibilitySensor:return VisibilitySensor_get_field_count(node, code_mode);
	case TAG_MPEG4_Viseme:return Viseme_get_field_count(node, code_mode);
	case TAG_MPEG4_WorldInfo:return WorldInfo_get_field_count(node, code_mode);
	case TAG_MPEG4_AcousticMaterial:return AcousticMaterial_get_field_count(node, code_mode);
	case TAG_MPEG4_AcousticScene:return AcousticScene_get_field_count(node, code_mode);
	case TAG_MPEG4_ApplicationWindow:return ApplicationWindow_get_field_count(node, code_mode);
	case TAG_MPEG4_BAP:return BAP_get_field_count(node, code_mode);
	case TAG_MPEG4_BDP:return BDP_get_field_count(node, code_mode);
	case TAG_MPEG4_Body:return Body_get_field_count(node, code_mode);
	case TAG_MPEG4_BodyDefTable:return BodyDefTable_get_field_count(node, code_mode);
	case TAG_MPEG4_BodySegmentConnectionHint:return BodySegmentConnectionHint_get_field_count(node, code_mode);
	case TAG_MPEG4_DirectiveSound:return DirectiveSound_get_field_count(node, code_mode);
	case TAG_MPEG4_Hierarchical3DMesh:return Hierarchical3DMesh_get_field_count(node, code_mode);
	case TAG_MPEG4_MaterialKey:return MaterialKey_get_field_count(node, code_mode);
	case TAG_MPEG4_PerceptualParameters:return PerceptualParameters_get_field_count(node, code_mode);
	case TAG_MPEG4_TemporalTransform:return TemporalTransform_get_field_count(node, code_mode);
	case TAG_MPEG4_TemporalGroup:return TemporalGroup_get_field_count(node, code_mode);
	case TAG_MPEG4_ServerCommand:return ServerCommand_get_field_count(node, code_mode);
	case TAG_MPEG4_InputSensor:return InputSensor_get_field_count(node, code_mode);
	case TAG_MPEG4_MatteTexture:return MatteTexture_get_field_count(node, code_mode);
	case TAG_MPEG4_MediaBuffer:return MediaBuffer_get_field_count(node, code_mode);
	case TAG_MPEG4_MediaControl:return MediaControl_get_field_count(node, code_mode);
	case TAG_MPEG4_MediaSensor:return MediaSensor_get_field_count(node, code_mode);
	case TAG_MPEG4_BitWrapper:return BitWrapper_get_field_count(node, code_mode);
	case TAG_MPEG4_CoordinateInterpolator4D:return CoordinateInterpolator4D_get_field_count(node, code_mode);
	case TAG_MPEG4_DepthImage:return DepthImage_get_field_count(node, code_mode);
	case TAG_MPEG4_FFD:return FFD_get_field_count(node, code_mode);
	case TAG_MPEG4_Implicit:return Implicit_get_field_count(node, code_mode);
	case TAG_MPEG4_XXLFM_Appearance:return XXLFM_Appearance_get_field_count(node, code_mode);
	case TAG_MPEG4_XXLFM_BlendList:return XXLFM_BlendList_get_field_count(node, code_mode);
	case TAG_MPEG4_XXLFM_FrameList:return XXLFM_FrameList_get_field_count(node, code_mode);
	case TAG_MPEG4_XXLFM_LightMap:return XXLFM_LightMap_get_field_count(node, code_mode);
	case TAG_MPEG4_XXLFM_SurfaceMapList:return XXLFM_SurfaceMapList_get_field_count(node, code_mode);
	case TAG_MPEG4_XXLFM_ViewMapList:return XXLFM_ViewMapList_get_field_count(node, code_mode);
	case TAG_MPEG4_MeshGrid:return MeshGrid_get_field_count(node, code_mode);
	case TAG_MPEG4_NonLinearDeformer:return NonLinearDeformer_get_field_count(node, code_mode);
	case TAG_MPEG4_NurbsCurve:return NurbsCurve_get_field_count(node, code_mode);
	case TAG_MPEG4_NurbsCurve2D:return NurbsCurve2D_get_field_count(node, code_mode);
	case TAG_MPEG4_NurbsSurface:return NurbsSurface_get_field_count(node, code_mode);
	case TAG_MPEG4_OctreeImage:return OctreeImage_get_field_count(node, code_mode);
	case TAG_MPEG4_XXParticles:return XXParticles_get_field_count(node, code_mode);
	case TAG_MPEG4_XXParticleInitBox:return XXParticleInitBox_get_field_count(node, code_mode);
	case TAG_MPEG4_XXPlanarObstacle:return XXPlanarObstacle_get_field_count(node, code_mode);
	case TAG_MPEG4_XXPointAttractor:return XXPointAttractor_get_field_count(node, code_mode);
	case TAG_MPEG4_PointTexture:return PointTexture_get_field_count(node, code_mode);
	case TAG_MPEG4_PositionAnimator:return PositionAnimator_get_field_count(node, code_mode);
	case TAG_MPEG4_PositionAnimator2D:return PositionAnimator2D_get_field_count(node, code_mode);
	case TAG_MPEG4_PositionInterpolator4D:return PositionInterpolator4D_get_field_count(node, code_mode);
	case TAG_MPEG4_ProceduralTexture:return ProceduralTexture_get_field_count(node, code_mode);
	case TAG_MPEG4_Quadric:return Quadric_get_field_count(node, code_mode);
	case TAG_MPEG4_SBBone:return SBBone_get_field_count(node, code_mode);
	case TAG_MPEG4_SBMuscle:return SBMuscle_get_field_count(node, code_mode);
	case TAG_MPEG4_SBSegment:return SBSegment_get_field_count(node, code_mode);
	case TAG_MPEG4_SBSite:return SBSite_get_field_count(node, code_mode);
	case TAG_MPEG4_SBSkinnedModel:return SBSkinnedModel_get_field_count(node, code_mode);
	case TAG_MPEG4_SBVCAnimation:return SBVCAnimation_get_field_count(node, code_mode);
	case TAG_MPEG4_ScalarAnimator:return ScalarAnimator_get_field_count(node, code_mode);
	case TAG_MPEG4_SimpleTexture:return SimpleTexture_get_field_count(node, code_mode);
	case TAG_MPEG4_SolidRep:return SolidRep_get_field_count(node, code_mode);
	case TAG_MPEG4_SubdivisionSurface:return SubdivisionSurface_get_field_count(node, code_mode);
	case TAG_MPEG4_SubdivSurfaceSector:return SubdivSurfaceSector_get_field_count(node, code_mode);
	case TAG_MPEG4_WaveletSubdivisionSurface:return WaveletSubdivisionSurface_get_field_count(node, code_mode);
	case TAG_MPEG4_Clipper2D:return Clipper2D_get_field_count(node, code_mode);
	case TAG_MPEG4_ColorTransform:return ColorTransform_get_field_count(node, code_mode);
	case TAG_MPEG4_Ellipse:return Ellipse_get_field_count(node, code_mode);
	case TAG_MPEG4_LinearGradient:return LinearGradient_get_field_count(node, code_mode);
	case TAG_MPEG4_PathLayout:return PathLayout_get_field_count(node, code_mode);
	case TAG_MPEG4_RadialGradient:return RadialGradient_get_field_count(node, code_mode);
	case TAG_MPEG4_SynthesizedTexture:return SynthesizedTexture_get_field_count(node, code_mode);
	case TAG_MPEG4_TransformMatrix2D:return TransformMatrix2D_get_field_count(node, code_mode);
	case TAG_MPEG4_Viewport:return Viewport_get_field_count(node, code_mode);
	case TAG_MPEG4_XCurve2D:return XCurve2D_get_field_count(node, code_mode);
	case TAG_MPEG4_XFontStyle:return XFontStyle_get_field_count(node, code_mode);
	case TAG_MPEG4_XLineProperties:return XLineProperties_get_field_count(node, code_mode);
	default:
		return 0;
	}
}

GF_Err gf_sg_mpeg4_node_get_field(GF_Node *node, GF_FieldInfo *field)
{
	switch (node->sgprivate->tag) {
	case TAG_MPEG4_Anchor: return Anchor_get_field(node, field);
	case TAG_MPEG4_AnimationStream: return AnimationStream_get_field(node, field);
	case TAG_MPEG4_Appearance: return Appearance_get_field(node, field);
	case TAG_MPEG4_AudioBuffer: return AudioBuffer_get_field(node, field);
	case TAG_MPEG4_AudioClip: return AudioClip_get_field(node, field);
	case TAG_MPEG4_AudioDelay: return AudioDelay_get_field(node, field);
	case TAG_MPEG4_AudioFX: return AudioFX_get_field(node, field);
	case TAG_MPEG4_AudioMix: return AudioMix_get_field(node, field);
	case TAG_MPEG4_AudioSource: return AudioSource_get_field(node, field);
	case TAG_MPEG4_AudioSwitch: return AudioSwitch_get_field(node, field);
	case TAG_MPEG4_Background: return Background_get_field(node, field);
	case TAG_MPEG4_Background2D: return Background2D_get_field(node, field);
	case TAG_MPEG4_Billboard: return Billboard_get_field(node, field);
	case TAG_MPEG4_Bitmap: return Bitmap_get_field(node, field);
	case TAG_MPEG4_Box: return Box_get_field(node, field);
	case TAG_MPEG4_Circle: return Circle_get_field(node, field);
	case TAG_MPEG4_Collision: return Collision_get_field(node, field);
	case TAG_MPEG4_Color: return Color_get_field(node, field);
	case TAG_MPEG4_ColorInterpolator: return ColorInterpolator_get_field(node, field);
	case TAG_MPEG4_CompositeTexture2D: return CompositeTexture2D_get_field(node, field);
	case TAG_MPEG4_CompositeTexture3D: return CompositeTexture3D_get_field(node, field);
	case TAG_MPEG4_Conditional: return Conditional_get_field(node, field);
	case TAG_MPEG4_Cone: return Cone_get_field(node, field);
	case TAG_MPEG4_Coordinate: return Coordinate_get_field(node, field);
	case TAG_MPEG4_Coordinate2D: return Coordinate2D_get_field(node, field);
	case TAG_MPEG4_CoordinateInterpolator: return CoordinateInterpolator_get_field(node, field);
	case TAG_MPEG4_CoordinateInterpolator2D: return CoordinateInterpolator2D_get_field(node, field);
	case TAG_MPEG4_Curve2D: return Curve2D_get_field(node, field);
	case TAG_MPEG4_Cylinder: return Cylinder_get_field(node, field);
	case TAG_MPEG4_CylinderSensor: return CylinderSensor_get_field(node, field);
	case TAG_MPEG4_DirectionalLight: return DirectionalLight_get_field(node, field);
	case TAG_MPEG4_DiscSensor: return DiscSensor_get_field(node, field);
	case TAG_MPEG4_ElevationGrid: return ElevationGrid_get_field(node, field);
	case TAG_MPEG4_Expression: return Expression_get_field(node, field);
	case TAG_MPEG4_Extrusion: return Extrusion_get_field(node, field);
	case TAG_MPEG4_Face: return Face_get_field(node, field);
	case TAG_MPEG4_FaceDefMesh: return FaceDefMesh_get_field(node, field);
	case TAG_MPEG4_FaceDefTables: return FaceDefTables_get_field(node, field);
	case TAG_MPEG4_FaceDefTransform: return FaceDefTransform_get_field(node, field);
	case TAG_MPEG4_FAP: return FAP_get_field(node, field);
	case TAG_MPEG4_FDP: return FDP_get_field(node, field);
	case TAG_MPEG4_FIT: return FIT_get_field(node, field);
	case TAG_MPEG4_Fog: return Fog_get_field(node, field);
	case TAG_MPEG4_FontStyle: return FontStyle_get_field(node, field);
	case TAG_MPEG4_Form: return Form_get_field(node, field);
	case TAG_MPEG4_Group: return Group_get_field(node, field);
	case TAG_MPEG4_ImageTexture: return ImageTexture_get_field(node, field);
	case TAG_MPEG4_IndexedFaceSet: return IndexedFaceSet_get_field(node, field);
	case TAG_MPEG4_IndexedFaceSet2D: return IndexedFaceSet2D_get_field(node, field);
	case TAG_MPEG4_IndexedLineSet: return IndexedLineSet_get_field(node, field);
	case TAG_MPEG4_IndexedLineSet2D: return IndexedLineSet2D_get_field(node, field);
	case TAG_MPEG4_Inline: return Inline_get_field(node, field);
	case TAG_MPEG4_LOD: return LOD_get_field(node, field);
	case TAG_MPEG4_Layer2D: return Layer2D_get_field(node, field);
	case TAG_MPEG4_Layer3D: return Layer3D_get_field(node, field);
	case TAG_MPEG4_Layout: return Layout_get_field(node, field);
	case TAG_MPEG4_LineProperties: return LineProperties_get_field(node, field);
	case TAG_MPEG4_ListeningPoint: return ListeningPoint_get_field(node, field);
	case TAG_MPEG4_Material: return Material_get_field(node, field);
	case TAG_MPEG4_Material2D: return Material2D_get_field(node, field);
	case TAG_MPEG4_MovieTexture: return MovieTexture_get_field(node, field);
	case TAG_MPEG4_NavigationInfo: return NavigationInfo_get_field(node, field);
	case TAG_MPEG4_Normal: return Normal_get_field(node, field);
	case TAG_MPEG4_NormalInterpolator: return NormalInterpolator_get_field(node, field);
	case TAG_MPEG4_OrderedGroup: return OrderedGroup_get_field(node, field);
	case TAG_MPEG4_OrientationInterpolator: return OrientationInterpolator_get_field(node, field);
	case TAG_MPEG4_PixelTexture: return PixelTexture_get_field(node, field);
	case TAG_MPEG4_PlaneSensor: return PlaneSensor_get_field(node, field);
	case TAG_MPEG4_PlaneSensor2D: return PlaneSensor2D_get_field(node, field);
	case TAG_MPEG4_PointLight: return PointLight_get_field(node, field);
	case TAG_MPEG4_PointSet: return PointSet_get_field(node, field);
	case TAG_MPEG4_PointSet2D: return PointSet2D_get_field(node, field);
	case TAG_MPEG4_PositionInterpolator: return PositionInterpolator_get_field(node, field);
	case TAG_MPEG4_PositionInterpolator2D: return PositionInterpolator2D_get_field(node, field);
	case TAG_MPEG4_ProximitySensor2D: return ProximitySensor2D_get_field(node, field);
	case TAG_MPEG4_ProximitySensor: return ProximitySensor_get_field(node, field);
	case TAG_MPEG4_QuantizationParameter: return QuantizationParameter_get_field(node, field);
	case TAG_MPEG4_Rectangle: return Rectangle_get_field(node, field);
	case TAG_MPEG4_ScalarInterpolator: return ScalarInterpolator_get_field(node, field);
	case TAG_MPEG4_Script: return Script_get_field(node, field);
	case TAG_MPEG4_Shape: return Shape_get_field(node, field);
	case TAG_MPEG4_Sound: return Sound_get_field(node, field);
	case TAG_MPEG4_Sound2D: return Sound2D_get_field(node, field);
	case TAG_MPEG4_Sphere: return Sphere_get_field(node, field);
	case TAG_MPEG4_SphereSensor: return SphereSensor_get_field(node, field);
	case TAG_MPEG4_SpotLight: return SpotLight_get_field(node, field);
	case TAG_MPEG4_Switch: return Switch_get_field(node, field);
	case TAG_MPEG4_TermCap: return TermCap_get_field(node, field);
	case TAG_MPEG4_Text: return Text_get_field(node, field);
	case TAG_MPEG4_TextureCoordinate: return TextureCoordinate_get_field(node, field);
	case TAG_MPEG4_TextureTransform: return TextureTransform_get_field(node, field);
	case TAG_MPEG4_TimeSensor: return TimeSensor_get_field(node, field);
	case TAG_MPEG4_TouchSensor: return TouchSensor_get_field(node, field);
	case TAG_MPEG4_Transform: return Transform_get_field(node, field);
	case TAG_MPEG4_Transform2D: return Transform2D_get_field(node, field);
	case TAG_MPEG4_Valuator: return Valuator_get_field(node, field);
	case TAG_MPEG4_Viewpoint: return Viewpoint_get_field(node, field);
	case TAG_MPEG4_VisibilitySensor: return VisibilitySensor_get_field(node, field);
	case TAG_MPEG4_Viseme: return Viseme_get_field(node, field);
	case TAG_MPEG4_WorldInfo: return WorldInfo_get_field(node, field);
	case TAG_MPEG4_AcousticMaterial: return AcousticMaterial_get_field(node, field);
	case TAG_MPEG4_AcousticScene: return AcousticScene_get_field(node, field);
	case TAG_MPEG4_ApplicationWindow: return ApplicationWindow_get_field(node, field);
	case TAG_MPEG4_BAP: return BAP_get_field(node, field);
	case TAG_MPEG4_BDP: return BDP_get_field(node, field);
	case TAG_MPEG4_Body: return Body_get_field(node, field);
	case TAG_MPEG4_BodyDefTable: return BodyDefTable_get_field(node, field);
	case TAG_MPEG4_BodySegmentConnectionHint: return BodySegmentConnectionHint_get_field(node, field);
	case TAG_MPEG4_DirectiveSound: return DirectiveSound_get_field(node, field);
	case TAG_MPEG4_Hierarchical3DMesh: return Hierarchical3DMesh_get_field(node, field);
	case TAG_MPEG4_MaterialKey: return MaterialKey_get_field(node, field);
	case TAG_MPEG4_PerceptualParameters: return PerceptualParameters_get_field(node, field);
	case TAG_MPEG4_TemporalTransform: return TemporalTransform_get_field(node, field);
	case TAG_MPEG4_TemporalGroup: return TemporalGroup_get_field(node, field);
	case TAG_MPEG4_ServerCommand: return ServerCommand_get_field(node, field);
	case TAG_MPEG4_InputSensor: return InputSensor_get_field(node, field);
	case TAG_MPEG4_MatteTexture: return MatteTexture_get_field(node, field);
	case TAG_MPEG4_MediaBuffer: return MediaBuffer_get_field(node, field);
	case TAG_MPEG4_MediaControl: return MediaControl_get_field(node, field);
	case TAG_MPEG4_MediaSensor: return MediaSensor_get_field(node, field);
	case TAG_MPEG4_BitWrapper: return BitWrapper_get_field(node, field);
	case TAG_MPEG4_CoordinateInterpolator4D: return CoordinateInterpolator4D_get_field(node, field);
	case TAG_MPEG4_DepthImage: return DepthImage_get_field(node, field);
	case TAG_MPEG4_FFD: return FFD_get_field(node, field);
	case TAG_MPEG4_Implicit: return Implicit_get_field(node, field);
	case TAG_MPEG4_XXLFM_Appearance: return XXLFM_Appearance_get_field(node, field);
	case TAG_MPEG4_XXLFM_BlendList: return XXLFM_BlendList_get_field(node, field);
	case TAG_MPEG4_XXLFM_FrameList: return XXLFM_FrameList_get_field(node, field);
	case TAG_MPEG4_XXLFM_LightMap: return XXLFM_LightMap_get_field(node, field);
	case TAG_MPEG4_XXLFM_SurfaceMapList: return XXLFM_SurfaceMapList_get_field(node, field);
	case TAG_MPEG4_XXLFM_ViewMapList: return XXLFM_ViewMapList_get_field(node, field);
	case TAG_MPEG4_MeshGrid: return MeshGrid_get_field(node, field);
	case TAG_MPEG4_NonLinearDeformer: return NonLinearDeformer_get_field(node, field);
	case TAG_MPEG4_NurbsCurve: return NurbsCurve_get_field(node, field);
	case TAG_MPEG4_NurbsCurve2D: return NurbsCurve2D_get_field(node, field);
	case TAG_MPEG4_NurbsSurface: return NurbsSurface_get_field(node, field);
	case TAG_MPEG4_OctreeImage: return OctreeImage_get_field(node, field);
	case TAG_MPEG4_XXParticles: return XXParticles_get_field(node, field);
	case TAG_MPEG4_XXParticleInitBox: return XXParticleInitBox_get_field(node, field);
	case TAG_MPEG4_XXPlanarObstacle: return XXPlanarObstacle_get_field(node, field);
	case TAG_MPEG4_XXPointAttractor: return XXPointAttractor_get_field(node, field);
	case TAG_MPEG4_PointTexture: return PointTexture_get_field(node, field);
	case TAG_MPEG4_PositionAnimator: return PositionAnimator_get_field(node, field);
	case TAG_MPEG4_PositionAnimator2D: return PositionAnimator2D_get_field(node, field);
	case TAG_MPEG4_PositionInterpolator4D: return PositionInterpolator4D_get_field(node, field);
	case TAG_MPEG4_ProceduralTexture: return ProceduralTexture_get_field(node, field);
	case TAG_MPEG4_Quadric: return Quadric_get_field(node, field);
	case TAG_MPEG4_SBBone: return SBBone_get_field(node, field);
	case TAG_MPEG4_SBMuscle: return SBMuscle_get_field(node, field);
	case TAG_MPEG4_SBSegment: return SBSegment_get_field(node, field);
	case TAG_MPEG4_SBSite: return SBSite_get_field(node, field);
	case TAG_MPEG4_SBSkinnedModel: return SBSkinnedModel_get_field(node, field);
	case TAG_MPEG4_SBVCAnimation: return SBVCAnimation_get_field(node, field);
	case TAG_MPEG4_ScalarAnimator: return ScalarAnimator_get_field(node, field);
	case TAG_MPEG4_SimpleTexture: return SimpleTexture_get_field(node, field);
	case TAG_MPEG4_SolidRep: return SolidRep_get_field(node, field);
	case TAG_MPEG4_SubdivisionSurface: return SubdivisionSurface_get_field(node, field);
	case TAG_MPEG4_SubdivSurfaceSector: return SubdivSurfaceSector_get_field(node, field);
	case TAG_MPEG4_WaveletSubdivisionSurface: return WaveletSubdivisionSurface_get_field(node, field);
	case TAG_MPEG4_Clipper2D: return Clipper2D_get_field(node, field);
	case TAG_MPEG4_ColorTransform: return ColorTransform_get_field(node, field);
	case TAG_MPEG4_Ellipse: return Ellipse_get_field(node, field);
	case TAG_MPEG4_LinearGradient: return LinearGradient_get_field(node, field);
	case TAG_MPEG4_PathLayout: return PathLayout_get_field(node, field);
	case TAG_MPEG4_RadialGradient: return RadialGradient_get_field(node, field);
	case TAG_MPEG4_SynthesizedTexture: return SynthesizedTexture_get_field(node, field);
	case TAG_MPEG4_TransformMatrix2D: return TransformMatrix2D_get_field(node, field);
	case TAG_MPEG4_Viewport: return Viewport_get_field(node, field);
	case TAG_MPEG4_XCurve2D: return XCurve2D_get_field(node, field);
	case TAG_MPEG4_XFontStyle: return XFontStyle_get_field(node, field);
	case TAG_MPEG4_XLineProperties: return XLineProperties_get_field(node, field);
	default:
		return GF_BAD_PARAM;
	}
}

GF_Err gf_sg_mpeg4_node_get_field_index(GF_Node *node, u32 inField, u8 code_mode, u32 *fieldIndex)
{
	switch (node->sgprivate->tag) {
	case TAG_MPEG4_Anchor: return Anchor_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_AnimationStream: return AnimationStream_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Appearance: return Appearance_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_AudioBuffer: return AudioBuffer_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_AudioClip: return AudioClip_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_AudioDelay: return AudioDelay_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_AudioFX: return AudioFX_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_AudioMix: return AudioMix_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_AudioSource: return AudioSource_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_AudioSwitch: return AudioSwitch_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Background: return Background_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Background2D: return Background2D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Billboard: return Billboard_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Bitmap: return Bitmap_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Box: return Box_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Circle: return Circle_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Collision: return Collision_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Color: return Color_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_ColorInterpolator: return ColorInterpolator_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_CompositeTexture2D: return CompositeTexture2D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_CompositeTexture3D: return CompositeTexture3D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Conditional: return Conditional_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Cone: return Cone_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Coordinate: return Coordinate_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Coordinate2D: return Coordinate2D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_CoordinateInterpolator: return CoordinateInterpolator_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_CoordinateInterpolator2D: return CoordinateInterpolator2D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Curve2D: return Curve2D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Cylinder: return Cylinder_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_CylinderSensor: return CylinderSensor_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_DirectionalLight: return DirectionalLight_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_DiscSensor: return DiscSensor_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_ElevationGrid: return ElevationGrid_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Expression: return Expression_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Extrusion: return Extrusion_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Face: return Face_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_FaceDefMesh: return FaceDefMesh_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_FaceDefTables: return FaceDefTables_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_FaceDefTransform: return FaceDefTransform_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_FAP: return FAP_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_FDP: return FDP_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_FIT: return FIT_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Fog: return Fog_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_FontStyle: return FontStyle_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Form: return Form_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Group: return Group_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_ImageTexture: return ImageTexture_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_IndexedFaceSet: return IndexedFaceSet_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_IndexedFaceSet2D: return IndexedFaceSet2D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_IndexedLineSet: return IndexedLineSet_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_IndexedLineSet2D: return IndexedLineSet2D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Inline: return Inline_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_LOD: return LOD_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Layer2D: return Layer2D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Layer3D: return Layer3D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Layout: return Layout_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_LineProperties: return LineProperties_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_ListeningPoint: return ListeningPoint_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Material: return Material_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Material2D: return Material2D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_MovieTexture: return MovieTexture_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_NavigationInfo: return NavigationInfo_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Normal: return Normal_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_NormalInterpolator: return NormalInterpolator_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_OrderedGroup: return OrderedGroup_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_OrientationInterpolator: return OrientationInterpolator_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_PixelTexture: return PixelTexture_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_PlaneSensor: return PlaneSensor_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_PlaneSensor2D: return PlaneSensor2D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_PointLight: return PointLight_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_PointSet: return PointSet_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_PointSet2D: return PointSet2D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_PositionInterpolator: return PositionInterpolator_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_PositionInterpolator2D: return PositionInterpolator2D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_ProximitySensor2D: return ProximitySensor2D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_ProximitySensor: return ProximitySensor_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_QuantizationParameter: return QuantizationParameter_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Rectangle: return Rectangle_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_ScalarInterpolator: return ScalarInterpolator_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Script: return Script_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Shape: return Shape_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Sound: return Sound_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Sound2D: return Sound2D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Sphere: return Sphere_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_SphereSensor: return SphereSensor_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_SpotLight: return SpotLight_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Switch: return Switch_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_TermCap: return TermCap_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Text: return Text_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_TextureCoordinate: return TextureCoordinate_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_TextureTransform: return TextureTransform_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_TimeSensor: return TimeSensor_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_TouchSensor: return TouchSensor_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Transform: return Transform_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Transform2D: return Transform2D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Valuator: return Valuator_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Viewpoint: return Viewpoint_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_VisibilitySensor: return VisibilitySensor_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Viseme: return Viseme_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_WorldInfo: return WorldInfo_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_AcousticMaterial: return AcousticMaterial_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_AcousticScene: return AcousticScene_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_ApplicationWindow: return ApplicationWindow_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_BAP: return BAP_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_BDP: return BDP_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Body: return Body_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_BodyDefTable: return BodyDefTable_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_BodySegmentConnectionHint: return BodySegmentConnectionHint_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_DirectiveSound: return DirectiveSound_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Hierarchical3DMesh: return Hierarchical3DMesh_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_MaterialKey: return MaterialKey_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_PerceptualParameters: return PerceptualParameters_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_TemporalTransform: return TemporalTransform_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_TemporalGroup: return TemporalGroup_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_ServerCommand: return ServerCommand_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_InputSensor: return InputSensor_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_MatteTexture: return MatteTexture_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_MediaBuffer: return MediaBuffer_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_MediaControl: return MediaControl_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_MediaSensor: return MediaSensor_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_BitWrapper: return BitWrapper_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_CoordinateInterpolator4D: return CoordinateInterpolator4D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_DepthImage: return DepthImage_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_FFD: return FFD_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Implicit: return Implicit_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_XXLFM_Appearance: return XXLFM_Appearance_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_XXLFM_BlendList: return XXLFM_BlendList_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_XXLFM_FrameList: return XXLFM_FrameList_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_XXLFM_LightMap: return XXLFM_LightMap_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_XXLFM_SurfaceMapList: return XXLFM_SurfaceMapList_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_XXLFM_ViewMapList: return XXLFM_ViewMapList_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_MeshGrid: return MeshGrid_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_NonLinearDeformer: return NonLinearDeformer_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_NurbsCurve: return NurbsCurve_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_NurbsCurve2D: return NurbsCurve2D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_NurbsSurface: return NurbsSurface_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_OctreeImage: return OctreeImage_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_XXParticles: return XXParticles_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_XXParticleInitBox: return XXParticleInitBox_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_XXPlanarObstacle: return XXPlanarObstacle_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_XXPointAttractor: return XXPointAttractor_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_PointTexture: return PointTexture_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_PositionAnimator: return PositionAnimator_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_PositionAnimator2D: return PositionAnimator2D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_PositionInterpolator4D: return PositionInterpolator4D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_ProceduralTexture: return ProceduralTexture_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Quadric: return Quadric_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_SBBone: return SBBone_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_SBMuscle: return SBMuscle_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_SBSegment: return SBSegment_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_SBSite: return SBSite_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_SBSkinnedModel: return SBSkinnedModel_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_SBVCAnimation: return SBVCAnimation_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_ScalarAnimator: return ScalarAnimator_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_SimpleTexture: return SimpleTexture_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_SolidRep: return SolidRep_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_SubdivisionSurface: return SubdivisionSurface_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_SubdivSurfaceSector: return SubdivSurfaceSector_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_WaveletSubdivisionSurface: return WaveletSubdivisionSurface_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Clipper2D: return Clipper2D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_ColorTransform: return ColorTransform_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Ellipse: return Ellipse_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_LinearGradient: return LinearGradient_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_PathLayout: return PathLayout_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_RadialGradient: return RadialGradient_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_SynthesizedTexture: return SynthesizedTexture_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_TransformMatrix2D: return TransformMatrix2D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_Viewport: return Viewport_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_XCurve2D: return XCurve2D_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_XFontStyle: return XFontStyle_get_field_index(node, inField, code_mode, fieldIndex);
	case TAG_MPEG4_XLineProperties: return XLineProperties_get_field_index(node, inField, code_mode, fieldIndex);
	default:
		return GF_BAD_PARAM;
	}
}

Bool gf_sg_mpeg4_node_get_aq_info(GF_Node *node, u32 FieldIndex, u8 *QType, u8 *AType, Fixed *b_min, Fixed *b_max, u32 *QT13_bits)
{
	switch (node->sgprivate->tag) {
	case TAG_MPEG4_Anchor: return Anchor_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_AnimationStream: return AnimationStream_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Appearance: return Appearance_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_AudioBuffer: return AudioBuffer_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_AudioClip: return AudioClip_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_AudioDelay: return AudioDelay_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_AudioFX: return AudioFX_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_AudioMix: return AudioMix_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_AudioSource: return AudioSource_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_AudioSwitch: return AudioSwitch_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Background: return Background_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Background2D: return Background2D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Billboard: return Billboard_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Bitmap: return Bitmap_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Box: return Box_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Circle: return Circle_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Collision: return Collision_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Color: return Color_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_ColorInterpolator: return ColorInterpolator_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_CompositeTexture2D: return CompositeTexture2D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_CompositeTexture3D: return CompositeTexture3D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Conditional: return Conditional_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Cone: return Cone_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Coordinate: return Coordinate_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Coordinate2D: return Coordinate2D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_CoordinateInterpolator: return CoordinateInterpolator_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_CoordinateInterpolator2D: return CoordinateInterpolator2D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Curve2D: return Curve2D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Cylinder: return Cylinder_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_CylinderSensor: return CylinderSensor_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_DirectionalLight: return DirectionalLight_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_DiscSensor: return DiscSensor_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_ElevationGrid: return ElevationGrid_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Expression: return Expression_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Extrusion: return Extrusion_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Face: return Face_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_FaceDefMesh: return FaceDefMesh_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_FaceDefTables: return FaceDefTables_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_FaceDefTransform: return FaceDefTransform_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_FAP: return FAP_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_FDP: return FDP_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_FIT: return FIT_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Fog: return Fog_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_FontStyle: return FontStyle_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Form: return Form_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Group: return Group_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_ImageTexture: return ImageTexture_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_IndexedFaceSet: return IndexedFaceSet_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_IndexedFaceSet2D: return IndexedFaceSet2D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_IndexedLineSet: return IndexedLineSet_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_IndexedLineSet2D: return IndexedLineSet2D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Inline: return Inline_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_LOD: return LOD_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Layer2D: return Layer2D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Layer3D: return Layer3D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Layout: return Layout_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_LineProperties: return LineProperties_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_ListeningPoint: return ListeningPoint_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Material: return Material_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Material2D: return Material2D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_MovieTexture: return MovieTexture_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_NavigationInfo: return NavigationInfo_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Normal: return Normal_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_NormalInterpolator: return NormalInterpolator_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_OrderedGroup: return OrderedGroup_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_OrientationInterpolator: return OrientationInterpolator_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_PixelTexture: return PixelTexture_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_PlaneSensor: return PlaneSensor_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_PlaneSensor2D: return PlaneSensor2D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_PointLight: return PointLight_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_PointSet: return PointSet_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_PointSet2D: return PointSet2D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_PositionInterpolator: return PositionInterpolator_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_PositionInterpolator2D: return PositionInterpolator2D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_ProximitySensor2D: return ProximitySensor2D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_ProximitySensor: return ProximitySensor_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_QuantizationParameter: return QuantizationParameter_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Rectangle: return Rectangle_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_ScalarInterpolator: return ScalarInterpolator_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Script: return Script_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Shape: return Shape_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Sound: return Sound_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Sound2D: return Sound2D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Sphere: return Sphere_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_SphereSensor: return SphereSensor_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_SpotLight: return SpotLight_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Switch: return Switch_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_TermCap: return TermCap_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Text: return Text_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_TextureCoordinate: return TextureCoordinate_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_TextureTransform: return TextureTransform_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_TimeSensor: return TimeSensor_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_TouchSensor: return TouchSensor_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Transform: return Transform_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Transform2D: return Transform2D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Valuator: return Valuator_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Viewpoint: return Viewpoint_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_VisibilitySensor: return VisibilitySensor_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Viseme: return Viseme_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_WorldInfo: return WorldInfo_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_AcousticMaterial: return AcousticMaterial_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_AcousticScene: return AcousticScene_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_ApplicationWindow: return ApplicationWindow_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_BAP: return BAP_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_BDP: return BDP_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Body: return Body_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_BodyDefTable: return BodyDefTable_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_BodySegmentConnectionHint: return BodySegmentConnectionHint_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_DirectiveSound: return DirectiveSound_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Hierarchical3DMesh: return Hierarchical3DMesh_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_MaterialKey: return MaterialKey_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_PerceptualParameters: return PerceptualParameters_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_TemporalTransform: return TemporalTransform_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_TemporalGroup: return TemporalGroup_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_ServerCommand: return ServerCommand_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_InputSensor: return InputSensor_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_MatteTexture: return MatteTexture_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_MediaBuffer: return MediaBuffer_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_MediaControl: return MediaControl_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_MediaSensor: return MediaSensor_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_BitWrapper: return BitWrapper_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_CoordinateInterpolator4D: return CoordinateInterpolator4D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_DepthImage: return DepthImage_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_FFD: return FFD_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Implicit: return Implicit_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_XXLFM_Appearance: return XXLFM_Appearance_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_XXLFM_BlendList: return XXLFM_BlendList_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_XXLFM_FrameList: return XXLFM_FrameList_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_XXLFM_LightMap: return XXLFM_LightMap_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_XXLFM_SurfaceMapList: return XXLFM_SurfaceMapList_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_XXLFM_ViewMapList: return XXLFM_ViewMapList_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_MeshGrid: return MeshGrid_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_NonLinearDeformer: return NonLinearDeformer_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_NurbsCurve: return NurbsCurve_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_NurbsCurve2D: return NurbsCurve2D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_NurbsSurface: return NurbsSurface_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_OctreeImage: return OctreeImage_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_XXParticles: return XXParticles_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_XXParticleInitBox: return XXParticleInitBox_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_XXPlanarObstacle: return XXPlanarObstacle_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_XXPointAttractor: return XXPointAttractor_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_PointTexture: return PointTexture_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_PositionAnimator: return PositionAnimator_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_PositionAnimator2D: return PositionAnimator2D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_PositionInterpolator4D: return PositionInterpolator4D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_ProceduralTexture: return ProceduralTexture_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Quadric: return Quadric_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_SBBone: return SBBone_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_SBMuscle: return SBMuscle_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_SBSegment: return SBSegment_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_SBSite: return SBSite_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_SBSkinnedModel: return SBSkinnedModel_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_SBVCAnimation: return SBVCAnimation_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_ScalarAnimator: return ScalarAnimator_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_SimpleTexture: return SimpleTexture_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_SolidRep: return SolidRep_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_SubdivisionSurface: return SubdivisionSurface_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_SubdivSurfaceSector: return SubdivSurfaceSector_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_WaveletSubdivisionSurface: return WaveletSubdivisionSurface_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Clipper2D: return Clipper2D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_ColorTransform: return ColorTransform_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Ellipse: return Ellipse_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_LinearGradient: return LinearGradient_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_PathLayout: return PathLayout_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_RadialGradient: return RadialGradient_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_SynthesizedTexture: return SynthesizedTexture_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_TransformMatrix2D: return TransformMatrix2D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_Viewport: return Viewport_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_XCurve2D: return XCurve2D_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_XFontStyle: return XFontStyle_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	case TAG_MPEG4_XLineProperties: return XLineProperties_get_aq_info(node, FieldIndex, QType, AType, b_min, b_max, QT13_bits);
	default:
		return 0;
	}
}

u32 gf_sg_mpeg4_node_get_child_ndt(GF_Node *node)
{
	switch (node->sgprivate->tag) {
	case TAG_MPEG4_Anchor: return NDT_SF3DNode;
	case TAG_MPEG4_AudioBuffer: return NDT_SFAudioNode;
	case TAG_MPEG4_AudioDelay: return NDT_SFAudioNode;
	case TAG_MPEG4_AudioFX: return NDT_SFAudioNode;
	case TAG_MPEG4_AudioMix: return NDT_SFAudioNode;
	case TAG_MPEG4_AudioSource: return NDT_SFAudioNode;
	case TAG_MPEG4_AudioSwitch: return NDT_SFAudioNode;
	case TAG_MPEG4_Billboard: return NDT_SF3DNode;
	case TAG_MPEG4_Collision: return NDT_SF3DNode;
	case TAG_MPEG4_CompositeTexture2D: return NDT_SF2DNode;
	case TAG_MPEG4_CompositeTexture3D: return NDT_SF3DNode;
	case TAG_MPEG4_Face: return NDT_SF3DNode;
	case TAG_MPEG4_FaceDefTables: return NDT_SFFaceDefMeshNode;
	case TAG_MPEG4_FDP: return NDT_SFFaceDefTablesNode;
	case TAG_MPEG4_Form: return NDT_SF2DNode;
	case TAG_MPEG4_Group: return NDT_SF3DNode;
	case TAG_MPEG4_LOD: return NDT_SF3DNode;
	case TAG_MPEG4_Layer2D: return NDT_SF2DNode;
	case TAG_MPEG4_Layer3D: return NDT_SF3DNode;
	case TAG_MPEG4_Layout: return NDT_SF2DNode;
	case TAG_MPEG4_OrderedGroup: return NDT_SF3DNode;
	case TAG_MPEG4_Switch: return NDT_SF3DNode;
	case TAG_MPEG4_Transform: return NDT_SF3DNode;
	case TAG_MPEG4_Transform2D: return NDT_SF2DNode;
	case TAG_MPEG4_BDP: return NDT_SFBodyDefTableNode;
	case TAG_MPEG4_Body: return NDT_SF3DNode;
	case TAG_MPEG4_TemporalTransform: return NDT_SF3DNode;
	case TAG_MPEG4_TemporalGroup: return NDT_SFTemporalNode;
	case TAG_MPEG4_FFD: return NDT_SF3DNode;
	case TAG_MPEG4_XXLFM_Appearance: return NDT_SFLightMapNode;
	case TAG_MPEG4_OctreeImage: return NDT_SFDepthImageNode;
	case TAG_MPEG4_XXParticles: return NDT_SFInfluenceNode;
	case TAG_MPEG4_SBBone: return NDT_SF3DNode;
	case TAG_MPEG4_SBSegment: return NDT_SF3DNode;
	case TAG_MPEG4_SBSite: return NDT_SF3DNode;
	case TAG_MPEG4_SBSkinnedModel: return NDT_SFSBBoneNode;
	case TAG_MPEG4_SBVCAnimation: return NDT_SF3DNode;
	case TAG_MPEG4_SubdivisionSurface: return NDT_SFSubdivSurfaceSectorNode;
	case TAG_MPEG4_Clipper2D: return NDT_SF2DNode;
	case TAG_MPEG4_ColorTransform: return NDT_SF3DNode;
	case TAG_MPEG4_PathLayout: return NDT_SF2DNode;
	case TAG_MPEG4_TransformMatrix2D: return NDT_SF2DNode;
	default:
		return 0;
	}
}


u32 gf_node_mpeg4_type_by_class_name(const char *node_name)
{
	if(!node_name) return 0;
	if (!strcmp(node_name, "Anchor")) return TAG_MPEG4_Anchor;
	if (!strcmp(node_name, "AnimationStream")) return TAG_MPEG4_AnimationStream;
	if (!strcmp(node_name, "Appearance")) return TAG_MPEG4_Appearance;
	if (!strcmp(node_name, "AudioBuffer")) return TAG_MPEG4_AudioBuffer;
	if (!strcmp(node_name, "AudioClip")) return TAG_MPEG4_AudioClip;
	if (!strcmp(node_name, "AudioDelay")) return TAG_MPEG4_AudioDelay;
	if (!strcmp(node_name, "AudioFX")) return TAG_MPEG4_AudioFX;
	if (!strcmp(node_name, "AudioMix")) return TAG_MPEG4_AudioMix;
	if (!strcmp(node_name, "AudioSource")) return TAG_MPEG4_AudioSource;
	if (!strcmp(node_name, "AudioSwitch")) return TAG_MPEG4_AudioSwitch;
	if (!strcmp(node_name, "Background")) return TAG_MPEG4_Background;
	if (!strcmp(node_name, "Background2D")) return TAG_MPEG4_Background2D;
	if (!strcmp(node_name, "Billboard")) return TAG_MPEG4_Billboard;
	if (!strcmp(node_name, "Bitmap")) return TAG_MPEG4_Bitmap;
	if (!strcmp(node_name, "Box")) return TAG_MPEG4_Box;
	if (!strcmp(node_name, "Circle")) return TAG_MPEG4_Circle;
	if (!strcmp(node_name, "Collision")) return TAG_MPEG4_Collision;
	if (!strcmp(node_name, "Color")) return TAG_MPEG4_Color;
	if (!strcmp(node_name, "ColorInterpolator")) return TAG_MPEG4_ColorInterpolator;
	if (!strcmp(node_name, "CompositeTexture2D")) return TAG_MPEG4_CompositeTexture2D;
	if (!strcmp(node_name, "CompositeTexture3D")) return TAG_MPEG4_CompositeTexture3D;
	if (!strcmp(node_name, "Conditional")) return TAG_MPEG4_Conditional;
	if (!strcmp(node_name, "Cone")) return TAG_MPEG4_Cone;
	if (!strcmp(node_name, "Coordinate")) return TAG_MPEG4_Coordinate;
	if (!strcmp(node_name, "Coordinate2D")) return TAG_MPEG4_Coordinate2D;
	if (!strcmp(node_name, "CoordinateInterpolator")) return TAG_MPEG4_CoordinateInterpolator;
	if (!strcmp(node_name, "CoordinateInterpolator2D")) return TAG_MPEG4_CoordinateInterpolator2D;
	if (!strcmp(node_name, "Curve2D")) return TAG_MPEG4_Curve2D;
	if (!strcmp(node_name, "Cylinder")) return TAG_MPEG4_Cylinder;
	if (!strcmp(node_name, "CylinderSensor")) return TAG_MPEG4_CylinderSensor;
	if (!strcmp(node_name, "DirectionalLight")) return TAG_MPEG4_DirectionalLight;
	if (!strcmp(node_name, "DiscSensor")) return TAG_MPEG4_DiscSensor;
	if (!strcmp(node_name, "ElevationGrid")) return TAG_MPEG4_ElevationGrid;
	if (!strcmp(node_name, "Expression")) return TAG_MPEG4_Expression;
	if (!strcmp(node_name, "Extrusion")) return TAG_MPEG4_Extrusion;
	if (!strcmp(node_name, "Face")) return TAG_MPEG4_Face;
	if (!strcmp(node_name, "FaceDefMesh")) return TAG_MPEG4_FaceDefMesh;
	if (!strcmp(node_name, "FaceDefTables")) return TAG_MPEG4_FaceDefTables;
	if (!strcmp(node_name, "FaceDefTransform")) return TAG_MPEG4_FaceDefTransform;
	if (!strcmp(node_name, "FAP")) return TAG_MPEG4_FAP;
	if (!strcmp(node_name, "FDP")) return TAG_MPEG4_FDP;
	if (!strcmp(node_name, "FIT")) return TAG_MPEG4_FIT;
	if (!strcmp(node_name, "Fog")) return TAG_MPEG4_Fog;
	if (!strcmp(node_name, "FontStyle")) return TAG_MPEG4_FontStyle;
	if (!strcmp(node_name, "Form")) return TAG_MPEG4_Form;
	if (!strcmp(node_name, "Group")) return TAG_MPEG4_Group;
	if (!strcmp(node_name, "ImageTexture")) return TAG_MPEG4_ImageTexture;
	if (!strcmp(node_name, "IndexedFaceSet")) return TAG_MPEG4_IndexedFaceSet;
	if (!strcmp(node_name, "IndexedFaceSet2D")) return TAG_MPEG4_IndexedFaceSet2D;
	if (!strcmp(node_name, "IndexedLineSet")) return TAG_MPEG4_IndexedLineSet;
	if (!strcmp(node_name, "IndexedLineSet2D")) return TAG_MPEG4_IndexedLineSet2D;
	if (!strcmp(node_name, "Inline")) return TAG_MPEG4_Inline;
	if (!strcmp(node_name, "LOD")) return TAG_MPEG4_LOD;
	if (!strcmp(node_name, "Layer2D")) return TAG_MPEG4_Layer2D;
	if (!strcmp(node_name, "Layer3D")) return TAG_MPEG4_Layer3D;
	if (!strcmp(node_name, "Layout")) return TAG_MPEG4_Layout;
	if (!strcmp(node_name, "LineProperties")) return TAG_MPEG4_LineProperties;
	if (!strcmp(node_name, "ListeningPoint")) return TAG_MPEG4_ListeningPoint;
	if (!strcmp(node_name, "Material")) return TAG_MPEG4_Material;
	if (!strcmp(node_name, "Material2D")) return TAG_MPEG4_Material2D;
	if (!strcmp(node_name, "MovieTexture")) return TAG_MPEG4_MovieTexture;
	if (!strcmp(node_name, "NavigationInfo")) return TAG_MPEG4_NavigationInfo;
	if (!strcmp(node_name, "Normal")) return TAG_MPEG4_Normal;
	if (!strcmp(node_name, "NormalInterpolator")) return TAG_MPEG4_NormalInterpolator;
	if (!strcmp(node_name, "OrderedGroup")) return TAG_MPEG4_OrderedGroup;
	if (!strcmp(node_name, "OrientationInterpolator")) return TAG_MPEG4_OrientationInterpolator;
	if (!strcmp(node_name, "PixelTexture")) return TAG_MPEG4_PixelTexture;
	if (!strcmp(node_name, "PlaneSensor")) return TAG_MPEG4_PlaneSensor;
	if (!strcmp(node_name, "PlaneSensor2D")) return TAG_MPEG4_PlaneSensor2D;
	if (!strcmp(node_name, "PointLight")) return TAG_MPEG4_PointLight;
	if (!strcmp(node_name, "PointSet")) return TAG_MPEG4_PointSet;
	if (!strcmp(node_name, "PointSet2D")) return TAG_MPEG4_PointSet2D;
	if (!strcmp(node_name, "PositionInterpolator")) return TAG_MPEG4_PositionInterpolator;
	if (!strcmp(node_name, "PositionInterpolator2D")) return TAG_MPEG4_PositionInterpolator2D;
	if (!strcmp(node_name, "ProximitySensor2D")) return TAG_MPEG4_ProximitySensor2D;
	if (!strcmp(node_name, "ProximitySensor")) return TAG_MPEG4_ProximitySensor;
	if (!strcmp(node_name, "QuantizationParameter")) return TAG_MPEG4_QuantizationParameter;
	if (!strcmp(node_name, "Rectangle")) return TAG_MPEG4_Rectangle;
	if (!strcmp(node_name, "ScalarInterpolator")) return TAG_MPEG4_ScalarInterpolator;
	if (!strcmp(node_name, "Script")) return TAG_MPEG4_Script;
	if (!strcmp(node_name, "Shape")) return TAG_MPEG4_Shape;
	if (!strcmp(node_name, "Sound")) return TAG_MPEG4_Sound;
	if (!strcmp(node_name, "Sound2D")) return TAG_MPEG4_Sound2D;
	if (!strcmp(node_name, "Sphere")) return TAG_MPEG4_Sphere;
	if (!strcmp(node_name, "SphereSensor")) return TAG_MPEG4_SphereSensor;
	if (!strcmp(node_name, "SpotLight")) return TAG_MPEG4_SpotLight;
	if (!strcmp(node_name, "Switch")) return TAG_MPEG4_Switch;
	if (!strcmp(node_name, "TermCap")) return TAG_MPEG4_TermCap;
	if (!strcmp(node_name, "Text")) return TAG_MPEG4_Text;
	if (!strcmp(node_name, "TextureCoordinate")) return TAG_MPEG4_TextureCoordinate;
	if (!strcmp(node_name, "TextureTransform")) return TAG_MPEG4_TextureTransform;
	if (!strcmp(node_name, "TimeSensor")) return TAG_MPEG4_TimeSensor;
	if (!strcmp(node_name, "TouchSensor")) return TAG_MPEG4_TouchSensor;
	if (!strcmp(node_name, "Transform")) return TAG_MPEG4_Transform;
	if (!strcmp(node_name, "Transform2D")) return TAG_MPEG4_Transform2D;
	if (!strcmp(node_name, "Valuator")) return TAG_MPEG4_Valuator;
	if (!strcmp(node_name, "Viewpoint")) return TAG_MPEG4_Viewpoint;
	if (!strcmp(node_name, "VisibilitySensor")) return TAG_MPEG4_VisibilitySensor;
	if (!strcmp(node_name, "Viseme")) return TAG_MPEG4_Viseme;
	if (!strcmp(node_name, "WorldInfo")) return TAG_MPEG4_WorldInfo;
	if (!strcmp(node_name, "AcousticMaterial")) return TAG_MPEG4_AcousticMaterial;
	if (!strcmp(node_name, "AcousticScene")) return TAG_MPEG4_AcousticScene;
	if (!strcmp(node_name, "ApplicationWindow")) return TAG_MPEG4_ApplicationWindow;
	if (!strcmp(node_name, "BAP")) return TAG_MPEG4_BAP;
	if (!strcmp(node_name, "BDP")) return TAG_MPEG4_BDP;
	if (!strcmp(node_name, "Body")) return TAG_MPEG4_Body;
	if (!strcmp(node_name, "BodyDefTable")) return TAG_MPEG4_BodyDefTable;
	if (!strcmp(node_name, "BodySegmentConnectionHint")) return TAG_MPEG4_BodySegmentConnectionHint;
	if (!strcmp(node_name, "DirectiveSound")) return TAG_MPEG4_DirectiveSound;
	if (!strcmp(node_name, "Hierarchical3DMesh")) return TAG_MPEG4_Hierarchical3DMesh;
	if (!strcmp(node_name, "MaterialKey")) return TAG_MPEG4_MaterialKey;
	if (!strcmp(node_name, "PerceptualParameters")) return TAG_MPEG4_PerceptualParameters;
	if (!strcmp(node_name, "TemporalTransform")) return TAG_MPEG4_TemporalTransform;
	if (!strcmp(node_name, "TemporalGroup")) return TAG_MPEG4_TemporalGroup;
	if (!strcmp(node_name, "ServerCommand")) return TAG_MPEG4_ServerCommand;
	if (!strcmp(node_name, "InputSensor")) return TAG_MPEG4_InputSensor;
	if (!strcmp(node_name, "MatteTexture")) return TAG_MPEG4_MatteTexture;
	if (!strcmp(node_name, "MediaBuffer")) return TAG_MPEG4_MediaBuffer;
	if (!strcmp(node_name, "MediaControl")) return TAG_MPEG4_MediaControl;
	if (!strcmp(node_name, "MediaSensor")) return TAG_MPEG4_MediaSensor;
	if (!strcmp(node_name, "BitWrapper")) return TAG_MPEG4_BitWrapper;
	if (!strcmp(node_name, "CoordinateInterpolator4D")) return TAG_MPEG4_CoordinateInterpolator4D;
	if (!strcmp(node_name, "DepthImage")) return TAG_MPEG4_DepthImage;
	if (!strcmp(node_name, "FFD")) return TAG_MPEG4_FFD;
	if (!strcmp(node_name, "Implicit")) return TAG_MPEG4_Implicit;
	if (!strcmp(node_name, "XXLFM_Appearance")) return TAG_MPEG4_XXLFM_Appearance;
	if (!strcmp(node_name, "XXLFM_BlendList")) return TAG_MPEG4_XXLFM_BlendList;
	if (!strcmp(node_name, "XXLFM_FrameList")) return TAG_MPEG4_XXLFM_FrameList;
	if (!strcmp(node_name, "XXLFM_LightMap")) return TAG_MPEG4_XXLFM_LightMap;
	if (!strcmp(node_name, "XXLFM_SurfaceMapList")) return TAG_MPEG4_XXLFM_SurfaceMapList;
	if (!strcmp(node_name, "XXLFM_ViewMapList")) return TAG_MPEG4_XXLFM_ViewMapList;
	if (!strcmp(node_name, "MeshGrid")) return TAG_MPEG4_MeshGrid;
	if (!strcmp(node_name, "NonLinearDeformer")) return TAG_MPEG4_NonLinearDeformer;
	if (!strcmp(node_name, "NurbsCurve")) return TAG_MPEG4_NurbsCurve;
	if (!strcmp(node_name, "NurbsCurve2D")) return TAG_MPEG4_NurbsCurve2D;
	if (!strcmp(node_name, "NurbsSurface")) return TAG_MPEG4_NurbsSurface;
	if (!strcmp(node_name, "OctreeImage")) return TAG_MPEG4_OctreeImage;
	if (!strcmp(node_name, "XXParticles")) return TAG_MPEG4_XXParticles;
	if (!strcmp(node_name, "XXParticleInitBox")) return TAG_MPEG4_XXParticleInitBox;
	if (!strcmp(node_name, "XXPlanarObstacle")) return TAG_MPEG4_XXPlanarObstacle;
	if (!strcmp(node_name, "XXPointAttractor")) return TAG_MPEG4_XXPointAttractor;
	if (!strcmp(node_name, "PointTexture")) return TAG_MPEG4_PointTexture;
	if (!strcmp(node_name, "PositionAnimator")) return TAG_MPEG4_PositionAnimator;
	if (!strcmp(node_name, "PositionAnimator2D")) return TAG_MPEG4_PositionAnimator2D;
	if (!strcmp(node_name, "PositionInterpolator4D")) return TAG_MPEG4_PositionInterpolator4D;
	if (!strcmp(node_name, "ProceduralTexture")) return TAG_MPEG4_ProceduralTexture;
	if (!strcmp(node_name, "Quadric")) return TAG_MPEG4_Quadric;
	if (!strcmp(node_name, "SBBone")) return TAG_MPEG4_SBBone;
	if (!strcmp(node_name, "SBMuscle")) return TAG_MPEG4_SBMuscle;
	if (!strcmp(node_name, "SBSegment")) return TAG_MPEG4_SBSegment;
	if (!strcmp(node_name, "SBSite")) return TAG_MPEG4_SBSite;
	if (!strcmp(node_name, "SBSkinnedModel")) return TAG_MPEG4_SBSkinnedModel;
	if (!strcmp(node_name, "SBVCAnimation")) return TAG_MPEG4_SBVCAnimation;
	if (!strcmp(node_name, "ScalarAnimator")) return TAG_MPEG4_ScalarAnimator;
	if (!strcmp(node_name, "SimpleTexture")) return TAG_MPEG4_SimpleTexture;
	if (!strcmp(node_name, "SolidRep")) return TAG_MPEG4_SolidRep;
	if (!strcmp(node_name, "SubdivisionSurface")) return TAG_MPEG4_SubdivisionSurface;
	if (!strcmp(node_name, "SubdivSurfaceSector")) return TAG_MPEG4_SubdivSurfaceSector;
	if (!strcmp(node_name, "WaveletSubdivisionSurface")) return TAG_MPEG4_WaveletSubdivisionSurface;
	if (!strcmp(node_name, "Clipper2D")) return TAG_MPEG4_Clipper2D;
	if (!strcmp(node_name, "ColorTransform")) return TAG_MPEG4_ColorTransform;
	if (!strcmp(node_name, "Ellipse")) return TAG_MPEG4_Ellipse;
	if (!strcmp(node_name, "LinearGradient")) return TAG_MPEG4_LinearGradient;
	if (!strcmp(node_name, "PathLayout")) return TAG_MPEG4_PathLayout;
	if (!strcmp(node_name, "RadialGradient")) return TAG_MPEG4_RadialGradient;
	if (!strcmp(node_name, "SynthesizedTexture")) return TAG_MPEG4_SynthesizedTexture;
	if (!strcmp(node_name, "TransformMatrix2D")) return TAG_MPEG4_TransformMatrix2D;
	if (!strcmp(node_name, "Viewport")) return TAG_MPEG4_Viewport;
	if (!strcmp(node_name, "XCurve2D")) return TAG_MPEG4_XCurve2D;
	if (!strcmp(node_name, "XFontStyle")) return TAG_MPEG4_XFontStyle;
	if (!strcmp(node_name, "XLineProperties")) return TAG_MPEG4_XLineProperties;
	return 0;
}

s32 gf_sg_mpeg4_node_get_field_index_by_name(GF_Node *node, char *name)
{
	switch (node->sgprivate->tag) {
	case TAG_MPEG4_Anchor: return Anchor_get_field_index_by_name(name);
	case TAG_MPEG4_AnimationStream: return AnimationStream_get_field_index_by_name(name);
	case TAG_MPEG4_Appearance: return Appearance_get_field_index_by_name(name);
	case TAG_MPEG4_AudioBuffer: return AudioBuffer_get_field_index_by_name(name);
	case TAG_MPEG4_AudioClip: return AudioClip_get_field_index_by_name(name);
	case TAG_MPEG4_AudioDelay: return AudioDelay_get_field_index_by_name(name);
	case TAG_MPEG4_AudioFX: return AudioFX_get_field_index_by_name(name);
	case TAG_MPEG4_AudioMix: return AudioMix_get_field_index_by_name(name);
	case TAG_MPEG4_AudioSource: return AudioSource_get_field_index_by_name(name);
	case TAG_MPEG4_AudioSwitch: return AudioSwitch_get_field_index_by_name(name);
	case TAG_MPEG4_Background: return Background_get_field_index_by_name(name);
	case TAG_MPEG4_Background2D: return Background2D_get_field_index_by_name(name);
	case TAG_MPEG4_Billboard: return Billboard_get_field_index_by_name(name);
	case TAG_MPEG4_Bitmap: return Bitmap_get_field_index_by_name(name);
	case TAG_MPEG4_Box: return Box_get_field_index_by_name(name);
	case TAG_MPEG4_Circle: return Circle_get_field_index_by_name(name);
	case TAG_MPEG4_Collision: return Collision_get_field_index_by_name(name);
	case TAG_MPEG4_Color: return Color_get_field_index_by_name(name);
	case TAG_MPEG4_ColorInterpolator: return ColorInterpolator_get_field_index_by_name(name);
	case TAG_MPEG4_CompositeTexture2D: return CompositeTexture2D_get_field_index_by_name(name);
	case TAG_MPEG4_CompositeTexture3D: return CompositeTexture3D_get_field_index_by_name(name);
	case TAG_MPEG4_Conditional: return Conditional_get_field_index_by_name(name);
	case TAG_MPEG4_Cone: return Cone_get_field_index_by_name(name);
	case TAG_MPEG4_Coordinate: return Coordinate_get_field_index_by_name(name);
	case TAG_MPEG4_Coordinate2D: return Coordinate2D_get_field_index_by_name(name);
	case TAG_MPEG4_CoordinateInterpolator: return CoordinateInterpolator_get_field_index_by_name(name);
	case TAG_MPEG4_CoordinateInterpolator2D: return CoordinateInterpolator2D_get_field_index_by_name(name);
	case TAG_MPEG4_Curve2D: return Curve2D_get_field_index_by_name(name);
	case TAG_MPEG4_Cylinder: return Cylinder_get_field_index_by_name(name);
	case TAG_MPEG4_CylinderSensor: return CylinderSensor_get_field_index_by_name(name);
	case TAG_MPEG4_DirectionalLight: return DirectionalLight_get_field_index_by_name(name);
	case TAG_MPEG4_DiscSensor: return DiscSensor_get_field_index_by_name(name);
	case TAG_MPEG4_ElevationGrid: return ElevationGrid_get_field_index_by_name(name);
	case TAG_MPEG4_Expression: return Expression_get_field_index_by_name(name);
	case TAG_MPEG4_Extrusion: return Extrusion_get_field_index_by_name(name);
	case TAG_MPEG4_Face: return Face_get_field_index_by_name(name);
	case TAG_MPEG4_FaceDefMesh: return FaceDefMesh_get_field_index_by_name(name);
	case TAG_MPEG4_FaceDefTables: return FaceDefTables_get_field_index_by_name(name);
	case TAG_MPEG4_FaceDefTransform: return FaceDefTransform_get_field_index_by_name(name);
	case TAG_MPEG4_FAP: return FAP_get_field_index_by_name(name);
	case TAG_MPEG4_FDP: return FDP_get_field_index_by_name(name);
	case TAG_MPEG4_FIT: return FIT_get_field_index_by_name(name);
	case TAG_MPEG4_Fog: return Fog_get_field_index_by_name(name);
	case TAG_MPEG4_FontStyle: return FontStyle_get_field_index_by_name(name);
	case TAG_MPEG4_Form: return Form_get_field_index_by_name(name);
	case TAG_MPEG4_Group: return Group_get_field_index_by_name(name);
	case TAG_MPEG4_ImageTexture: return ImageTexture_get_field_index_by_name(name);
	case TAG_MPEG4_IndexedFaceSet: return IndexedFaceSet_get_field_index_by_name(name);
	case TAG_MPEG4_IndexedFaceSet2D: return IndexedFaceSet2D_get_field_index_by_name(name);
	case TAG_MPEG4_IndexedLineSet: return IndexedLineSet_get_field_index_by_name(name);
	case TAG_MPEG4_IndexedLineSet2D: return IndexedLineSet2D_get_field_index_by_name(name);
	case TAG_MPEG4_Inline: return Inline_get_field_index_by_name(name);
	case TAG_MPEG4_LOD: return LOD_get_field_index_by_name(name);
	case TAG_MPEG4_Layer2D: return Layer2D_get_field_index_by_name(name);
	case TAG_MPEG4_Layer3D: return Layer3D_get_field_index_by_name(name);
	case TAG_MPEG4_Layout: return Layout_get_field_index_by_name(name);
	case TAG_MPEG4_LineProperties: return LineProperties_get_field_index_by_name(name);
	case TAG_MPEG4_ListeningPoint: return ListeningPoint_get_field_index_by_name(name);
	case TAG_MPEG4_Material: return Material_get_field_index_by_name(name);
	case TAG_MPEG4_Material2D: return Material2D_get_field_index_by_name(name);
	case TAG_MPEG4_MovieTexture: return MovieTexture_get_field_index_by_name(name);
	case TAG_MPEG4_NavigationInfo: return NavigationInfo_get_field_index_by_name(name);
	case TAG_MPEG4_Normal: return Normal_get_field_index_by_name(name);
	case TAG_MPEG4_NormalInterpolator: return NormalInterpolator_get_field_index_by_name(name);
	case TAG_MPEG4_OrderedGroup: return OrderedGroup_get_field_index_by_name(name);
	case TAG_MPEG4_OrientationInterpolator: return OrientationInterpolator_get_field_index_by_name(name);
	case TAG_MPEG4_PixelTexture: return PixelTexture_get_field_index_by_name(name);
	case TAG_MPEG4_PlaneSensor: return PlaneSensor_get_field_index_by_name(name);
	case TAG_MPEG4_PlaneSensor2D: return PlaneSensor2D_get_field_index_by_name(name);
	case TAG_MPEG4_PointLight: return PointLight_get_field_index_by_name(name);
	case TAG_MPEG4_PointSet: return PointSet_get_field_index_by_name(name);
	case TAG_MPEG4_PointSet2D: return PointSet2D_get_field_index_by_name(name);
	case TAG_MPEG4_PositionInterpolator: return PositionInterpolator_get_field_index_by_name(name);
	case TAG_MPEG4_PositionInterpolator2D: return PositionInterpolator2D_get_field_index_by_name(name);
	case TAG_MPEG4_ProximitySensor2D: return ProximitySensor2D_get_field_index_by_name(name);
	case TAG_MPEG4_ProximitySensor: return ProximitySensor_get_field_index_by_name(name);
	case TAG_MPEG4_QuantizationParameter: return QuantizationParameter_get_field_index_by_name(name);
	case TAG_MPEG4_Rectangle: return Rectangle_get_field_index_by_name(name);
	case TAG_MPEG4_ScalarInterpolator: return ScalarInterpolator_get_field_index_by_name(name);
	case TAG_MPEG4_Script: return Script_get_field_index_by_name(name);
	case TAG_MPEG4_Shape: return Shape_get_field_index_by_name(name);
	case TAG_MPEG4_Sound: return Sound_get_field_index_by_name(name);
	case TAG_MPEG4_Sound2D: return Sound2D_get_field_index_by_name(name);
	case TAG_MPEG4_Sphere: return Sphere_get_field_index_by_name(name);
	case TAG_MPEG4_SphereSensor: return SphereSensor_get_field_index_by_name(name);
	case TAG_MPEG4_SpotLight: return SpotLight_get_field_index_by_name(name);
	case TAG_MPEG4_Switch: return Switch_get_field_index_by_name(name);
	case TAG_MPEG4_TermCap: return TermCap_get_field_index_by_name(name);
	case TAG_MPEG4_Text: return Text_get_field_index_by_name(name);
	case TAG_MPEG4_TextureCoordinate: return TextureCoordinate_get_field_index_by_name(name);
	case TAG_MPEG4_TextureTransform: return TextureTransform_get_field_index_by_name(name);
	case TAG_MPEG4_TimeSensor: return TimeSensor_get_field_index_by_name(name);
	case TAG_MPEG4_TouchSensor: return TouchSensor_get_field_index_by_name(name);
	case TAG_MPEG4_Transform: return Transform_get_field_index_by_name(name);
	case TAG_MPEG4_Transform2D: return Transform2D_get_field_index_by_name(name);
	case TAG_MPEG4_Valuator: return Valuator_get_field_index_by_name(name);
	case TAG_MPEG4_Viewpoint: return Viewpoint_get_field_index_by_name(name);
	case TAG_MPEG4_VisibilitySensor: return VisibilitySensor_get_field_index_by_name(name);
	case TAG_MPEG4_Viseme: return Viseme_get_field_index_by_name(name);
	case TAG_MPEG4_WorldInfo: return WorldInfo_get_field_index_by_name(name);
	case TAG_MPEG4_AcousticMaterial: return AcousticMaterial_get_field_index_by_name(name);
	case TAG_MPEG4_AcousticScene: return AcousticScene_get_field_index_by_name(name);
	case TAG_MPEG4_ApplicationWindow: return ApplicationWindow_get_field_index_by_name(name);
	case TAG_MPEG4_BAP: return BAP_get_field_index_by_name(name);
	case TAG_MPEG4_BDP: return BDP_get_field_index_by_name(name);
	case TAG_MPEG4_Body: return Body_get_field_index_by_name(name);
	case TAG_MPEG4_BodyDefTable: return BodyDefTable_get_field_index_by_name(name);
	case TAG_MPEG4_BodySegmentConnectionHint: return BodySegmentConnectionHint_get_field_index_by_name(name);
	case TAG_MPEG4_DirectiveSound: return DirectiveSound_get_field_index_by_name(name);
	case TAG_MPEG4_Hierarchical3DMesh: return Hierarchical3DMesh_get_field_index_by_name(name);
	case TAG_MPEG4_MaterialKey: return MaterialKey_get_field_index_by_name(name);
	case TAG_MPEG4_PerceptualParameters: return PerceptualParameters_get_field_index_by_name(name);
	case TAG_MPEG4_TemporalTransform: return TemporalTransform_get_field_index_by_name(name);
	case TAG_MPEG4_TemporalGroup: return TemporalGroup_get_field_index_by_name(name);
	case TAG_MPEG4_ServerCommand: return ServerCommand_get_field_index_by_name(name);
	case TAG_MPEG4_InputSensor: return InputSensor_get_field_index_by_name(name);
	case TAG_MPEG4_MatteTexture: return MatteTexture_get_field_index_by_name(name);
	case TAG_MPEG4_MediaBuffer: return MediaBuffer_get_field_index_by_name(name);
	case TAG_MPEG4_MediaControl: return MediaControl_get_field_index_by_name(name);
	case TAG_MPEG4_MediaSensor: return MediaSensor_get_field_index_by_name(name);
	case TAG_MPEG4_BitWrapper: return BitWrapper_get_field_index_by_name(name);
	case TAG_MPEG4_CoordinateInterpolator4D: return CoordinateInterpolator4D_get_field_index_by_name(name);
	case TAG_MPEG4_DepthImage: return DepthImage_get_field_index_by_name(name);
	case TAG_MPEG4_FFD: return FFD_get_field_index_by_name(name);
	case TAG_MPEG4_Implicit: return Implicit_get_field_index_by_name(name);
	case TAG_MPEG4_XXLFM_Appearance: return XXLFM_Appearance_get_field_index_by_name(name);
	case TAG_MPEG4_XXLFM_BlendList: return XXLFM_BlendList_get_field_index_by_name(name);
	case TAG_MPEG4_XXLFM_FrameList: return XXLFM_FrameList_get_field_index_by_name(name);
	case TAG_MPEG4_XXLFM_LightMap: return XXLFM_LightMap_get_field_index_by_name(name);
	case TAG_MPEG4_XXLFM_SurfaceMapList: return XXLFM_SurfaceMapList_get_field_index_by_name(name);
	case TAG_MPEG4_XXLFM_ViewMapList: return XXLFM_ViewMapList_get_field_index_by_name(name);
	case TAG_MPEG4_MeshGrid: return MeshGrid_get_field_index_by_name(name);
	case TAG_MPEG4_NonLinearDeformer: return NonLinearDeformer_get_field_index_by_name(name);
	case TAG_MPEG4_NurbsCurve: return NurbsCurve_get_field_index_by_name(name);
	case TAG_MPEG4_NurbsCurve2D: return NurbsCurve2D_get_field_index_by_name(name);
	case TAG_MPEG4_NurbsSurface: return NurbsSurface_get_field_index_by_name(name);
	case TAG_MPEG4_OctreeImage: return OctreeImage_get_field_index_by_name(name);
	case TAG_MPEG4_XXParticles: return XXParticles_get_field_index_by_name(name);
	case TAG_MPEG4_XXParticleInitBox: return XXParticleInitBox_get_field_index_by_name(name);
	case TAG_MPEG4_XXPlanarObstacle: return XXPlanarObstacle_get_field_index_by_name(name);
	case TAG_MPEG4_XXPointAttractor: return XXPointAttractor_get_field_index_by_name(name);
	case TAG_MPEG4_PointTexture: return PointTexture_get_field_index_by_name(name);
	case TAG_MPEG4_PositionAnimator: return PositionAnimator_get_field_index_by_name(name);
	case TAG_MPEG4_PositionAnimator2D: return PositionAnimator2D_get_field_index_by_name(name);
	case TAG_MPEG4_PositionInterpolator4D: return PositionInterpolator4D_get_field_index_by_name(name);
	case TAG_MPEG4_ProceduralTexture: return ProceduralTexture_get_field_index_by_name(name);
	case TAG_MPEG4_Quadric: return Quadric_get_field_index_by_name(name);
	case TAG_MPEG4_SBBone: return SBBone_get_field_index_by_name(name);
	case TAG_MPEG4_SBMuscle: return SBMuscle_get_field_index_by_name(name);
	case TAG_MPEG4_SBSegment: return SBSegment_get_field_index_by_name(name);
	case TAG_MPEG4_SBSite: return SBSite_get_field_index_by_name(name);
	case TAG_MPEG4_SBSkinnedModel: return SBSkinnedModel_get_field_index_by_name(name);
	case TAG_MPEG4_SBVCAnimation: return SBVCAnimation_get_field_index_by_name(name);
	case TAG_MPEG4_ScalarAnimator: return ScalarAnimator_get_field_index_by_name(name);
	case TAG_MPEG4_SimpleTexture: return SimpleTexture_get_field_index_by_name(name);
	case TAG_MPEG4_SolidRep: return SolidRep_get_field_index_by_name(name);
	case TAG_MPEG4_SubdivisionSurface: return SubdivisionSurface_get_field_index_by_name(name);
	case TAG_MPEG4_SubdivSurfaceSector: return SubdivSurfaceSector_get_field_index_by_name(name);
	case TAG_MPEG4_WaveletSubdivisionSurface: return WaveletSubdivisionSurface_get_field_index_by_name(name);
	case TAG_MPEG4_Clipper2D: return Clipper2D_get_field_index_by_name(name);
	case TAG_MPEG4_ColorTransform: return ColorTransform_get_field_index_by_name(name);
	case TAG_MPEG4_Ellipse: return Ellipse_get_field_index_by_name(name);
	case TAG_MPEG4_LinearGradient: return LinearGradient_get_field_index_by_name(name);
	case TAG_MPEG4_PathLayout: return PathLayout_get_field_index_by_name(name);
	case TAG_MPEG4_RadialGradient: return RadialGradient_get_field_index_by_name(name);
	case TAG_MPEG4_SynthesizedTexture: return SynthesizedTexture_get_field_index_by_name(name);
	case TAG_MPEG4_TransformMatrix2D: return TransformMatrix2D_get_field_index_by_name(name);
	case TAG_MPEG4_Viewport: return Viewport_get_field_index_by_name(name);
	case TAG_MPEG4_XCurve2D: return XCurve2D_get_field_index_by_name(name);
	case TAG_MPEG4_XFontStyle: return XFontStyle_get_field_index_by_name(name);
	case TAG_MPEG4_XLineProperties: return XLineProperties_get_field_index_by_name(name);
	default:
		return -1;
	}
}


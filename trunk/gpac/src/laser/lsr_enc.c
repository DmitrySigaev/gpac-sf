/*
 *			GPAC - Multimedia Framework C SDK
 *
 *			Authors: Jean le Feuvre
 *				Copyright (c) 2005-200X ENST
 *					All rights reserved
 *
 *  This file is part of GPAC / LASeR codec sub-project
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

#include <gpac/internal/laser_dev.h>
#include <gpac/bitstream.h>
#include <gpac/math.h>

#define GF_LSR_WRITE_INT(_codec, _val, _nbBits, _str)	{\
	gf_bs_write_int(_codec->bs, _val, _nbBits);	\
	}\


static void lsr_write_group_content(GF_LASeRCodec *lsr, SVGElement *elt);
static GF_Err lsr_write_command_list(GF_LASeRCodec *lsr, GF_List *comList, SVGscriptElement *script);
static GF_Err lsr_write_laser_unit(GF_LASeRCodec *lsr, GF_List *com_list, Bool reset_encoding_context);

GF_LASeRCodec *gf_laser_encoder_new(GF_SceneGraph *graph)
{
	GF_LASeRCodec *tmp;
	GF_SAFEALLOC(tmp, sizeof(GF_LASeRCodec));
	if (!tmp) return NULL;
	tmp->streamInfo = gf_list_new();
	tmp->font_table = gf_list_new();
	tmp->sg = graph;
	return tmp;
}

void gf_laser_encoder_del(GF_LASeRCodec *codec)
{	
	/*destroy all config*/
	while (gf_list_count(codec->streamInfo)) {
		LASeRStreamInfo *p = gf_list_last(codec->streamInfo);
		free(p);
		gf_list_rem_last(codec->streamInfo);
	}
	gf_list_del(codec->streamInfo);
	if (codec->col_table) free(codec->col_table);
	while (gf_list_count(codec->font_table)) {
		char *ft = gf_list_last(codec->font_table);
		free(ft);
		gf_list_rem_last(codec->font_table);
	}
	gf_list_del(codec->font_table);
	free(codec);
}


void gf_laser_set_trace(GF_LASeRCodec *codec, FILE *trace)
{
	codec->trace = trace;
	if (trace) fprintf(codec->trace, "Name\t\tNbBits\t\tValue\t\t//comment\n\n");
}

static LASeRStreamInfo *lsr_get_stream(GF_LASeRCodec *codec, u16 ESID)
{
	u32 i;
	for (i=0;i<gf_list_count(codec->streamInfo);i++) {
		LASeRStreamInfo *ptr = gf_list_get(codec->streamInfo, i);
		if(ptr->ESID==ESID) return ptr;
	}
	return NULL;
}


GF_Err gf_laser_encoder_new_stream(GF_LASeRCodec *codec, u16 ESID, GF_LASERConfig *cfg)
{
	LASeRStreamInfo *pInfo;
	if (lsr_get_stream(codec, ESID) != NULL) return GF_BAD_PARAM;
	GF_SAFEALLOC(pInfo, sizeof(LASeRStreamInfo));
	pInfo->ESID = ESID;
	memcpy(&pInfo->cfg, cfg, sizeof(GF_LASERConfig));
	if (!pInfo->cfg.time_resolution) pInfo->cfg.time_resolution = 1000;
	if (!pInfo->cfg.colorComponentBits) pInfo->cfg.colorComponentBits = 8;
	if (!pInfo->cfg.coord_bits) pInfo->cfg.coord_bits = 12;

	gf_list_add(codec->streamInfo, pInfo);
	return GF_OK;
}

GF_Err gf_laser_encoder_get_config(GF_LASeRCodec *codec, u16 ESID, char **out_data, u32 *out_data_length)
{
	GF_BitStream *bs;
	if (!codec || !out_data || !out_data_length) return GF_BAD_PARAM;

	codec->info = lsr_get_stream(codec, ESID);
	if (!codec->info) return GF_BAD_PARAM;

	bs = gf_bs_new(NULL, 0, GF_BITSTREAM_WRITE);
	gf_bs_write_int(bs, codec->info->cfg.profile, 8);
	gf_bs_write_int(bs, codec->info->cfg.level, 8);
	gf_bs_write_int(bs, codec->info->cfg.encoding, 2);
	gf_bs_write_int(bs, codec->info->cfg.pointsCodec, 2);
	gf_bs_write_int(bs, codec->info->cfg.pathComponents, 8);
	gf_bs_write_int(bs, codec->info->cfg.fullRequestHost, 1);
	if (codec->info->cfg.time_resolution != 1000) {
		gf_bs_write_int(bs, 1, 1);
		gf_bs_write_int(bs, codec->info->cfg.time_resolution , 16);
	} else {
		gf_bs_write_int(bs, 0, 1);
	}
	gf_bs_write_int(bs, codec->info->cfg.colorComponentBits - 1, 4);
	gf_bs_write_int(bs, codec->info->cfg.resolution, 4);
	gf_bs_write_int(bs, codec->info->cfg.scale_bits, 4);
	gf_bs_write_int(bs, codec->info->cfg.coord_bits, 5);
	gf_bs_write_int(bs, codec->info->cfg.append ? 1 : 0, 1);
	gf_bs_write_int(bs, codec->info->cfg.has_string_ids ? 1 : 0, 1);
	gf_bs_write_int(bs, codec->info->cfg.has_private_data ? 1 : 0, 1);
	gf_bs_write_int(bs, codec->info->cfg.hasExtendedAttributes ? 1 : 0, 1);
	gf_bs_write_int(bs, codec->info->cfg.extensionIDBits, 4);

	gf_bs_align(bs);
	gf_bs_get_content(bs, (unsigned char **) out_data, out_data_length);
	gf_bs_del(bs);
	return GF_OK;
}


GF_Err gf_laser_encode_au(GF_LASeRCodec *codec, u16 ESID, GF_List *command_list, Bool reset_context, char **out_data, u32 *out_data_length)
{
	GF_Err e;
	if (!codec || !command_list || !out_data || !out_data_length) return GF_BAD_PARAM;

	codec->info = lsr_get_stream(codec, ESID);
	if (!codec->info) return GF_BAD_PARAM;
	codec->coord_bits = codec->info->cfg.coord_bits;
	codec->scale_bits = codec->info->cfg.scale_bits + codec->coord_bits;
	codec->time_resolution = codec->info->cfg.time_resolution;
	codec->color_scale = (1<<codec->info->cfg.colorComponentBits) - 1;
	if (codec->info->cfg.resolution>=0)
		codec->res_factor = INT2FIX(1<<codec->info->cfg.resolution);
	else 
		codec->res_factor = gf_divfix(FIX_ONE, INT2FIX(1 << (-codec->info->cfg.resolution)) );

	codec->bs = gf_bs_new(NULL, 0, GF_BITSTREAM_WRITE);
	e = lsr_write_laser_unit(codec, command_list, reset_context);
	if (!e) {
		gf_bs_align(codec->bs);
		gf_bs_get_content(codec->bs, (unsigned char **) out_data, out_data_length);
	}
	gf_bs_del(codec->bs);
	codec->bs = NULL;
	return e;
}

GF_Err gf_laser_encoder_get_rap(GF_LASeRCodec *codec, char **out_data, u32 *out_data_length)
{
	GF_Err e;
	if (!codec->info) codec->info = gf_list_get(codec->streamInfo, 0);
	codec->bs = gf_bs_new(NULL, 0, GF_BITSTREAM_WRITE);
	e = lsr_write_laser_unit(codec, NULL, 0);
	if (e == GF_OK) gf_bs_get_content(codec->bs, (unsigned char **)out_data, out_data_length);
	gf_bs_del(codec->bs);
	codec->bs = NULL;
	return e;
}


static void lsr_enc_log_bits(GF_LASeRCodec *lsr, u32 val, u32 nb_bits, const char *name)
{
}

static void lsr_write_vluimsbf5(GF_LASeRCodec *lsr, u32 val, const char *name)
{
	u32 nb_words;
	u32 nb_tot, nb_bits = gf_get_bit_size(val);
	nb_words = nb_bits / 4;
	if (nb_bits%4) nb_words++;
	assert(nb_words * 4 >= nb_bits);
	nb_bits = nb_words * 4;
	nb_tot = nb_words+nb_bits;
	while (nb_words) {
		nb_words--;
		gf_bs_write_int(lsr->bs, nb_words ? 1 : 0, 1);
	}
	gf_bs_write_int(lsr->bs, val, nb_bits);
	lsr_enc_log_bits(lsr, val, nb_tot, name);
}

static void lsr_write_extension_class(GF_LASeRCodec *lsr, char *data, u32 len, const char *name)
{
	if (!len) len = strlen(name);
	lsr_write_vluimsbf5(lsr, len, name);
	gf_bs_write_data(lsr->bs, data, len);
}

static void lsr_write_extend_class(GF_LASeRCodec *lsr, char *data, u32 len, const char *name)
{
	GF_LSR_WRITE_INT(lsr, 0, lsr->info->cfg.extensionIDBits, "reserved");
	lsr_write_vluimsbf5(lsr, len, "byteLength");
	gf_bs_write_data(lsr->bs, data, len);
}

static void lsr_write_codec_IDREF(GF_LASeRCodec *lsr, SVG_IRI *href, const char *name)
{
	u32 nID = 0;
	if (href && href->target) nID = gf_node_get_id((GF_Node *)href->target);
	else if (name[0]=='#') {
		GF_Node *n = gf_sg_find_node_by_name(lsr->sg, (char *) name + 1);
		if (n) nID = gf_node_get_id((GF_Node *)href->target);
	}
	assert(nID);

	lsr_write_vluimsbf5(lsr, nID, name);
}

static void lsr_write_vl5string(GF_LASeRCodec *lsr, char *string, const char *name)
{
	u32 len = strlen(string);
	lsr_write_vluimsbf5(lsr, len, name);
	gf_bs_write_data(lsr->bs, string, len);
}

static void lsr_write_fixed_16_8(GF_LASeRCodec *lsr, Fixed fix, const char *name)
{
#ifdef GPAC_FIXED_POINT
	s32 val = fix >> 8;
#else
	s32 val = (s32) (fix * (1<<8) );
#endif
	val &= 0x00FFFFFF;
	GF_LSR_WRITE_INT(lsr, val, 24, name);
}

static s32 lsr_get_font_index(GF_LASeRCodec *lsr, SVG_FontFamily *font)
{
	u32 i, count;
	if ((font->type!=SVG_FONTFAMILY_VALUE) || !font->value) return -1;
	count = gf_list_count(lsr->font_table);
	for (i=0; i<count; i++) {
		char *n = gf_list_get(lsr->font_table, i);
		if (!strcmp(n, font->value)) return (s32) i;
	}
	return -2;
}

static s32 lsr_get_col_index(GF_LASeRCodec *lsr, SVG_Color *color)
{
	u16 r, g, b;
	u32 i;
	if (color->type!=SVG_COLOR_RGBCOLOR) return -1;
	r = FIX2INT(color->red*lsr->color_scale);
	g = FIX2INT(color->green*lsr->color_scale);
	b = FIX2INT(color->blue*lsr->color_scale);
	for (i=0; i<lsr->nb_cols; i++) {
		LSRCol *c = &lsr->col_table[i];
		if ((c->r == r) && (c->g == g) && (c->b == b)) return (s32) i;
	}
	return -2;
}

static void lsr_write_color(GF_LASeRCodec *lsr, SVG_Color *color, const char *name)
{
	s32 index = -1;
	if (color) index = lsr_get_col_index(lsr, color);
	if (index>=0) {
		GF_LSR_WRITE_INT(lsr, 1, 1, "hasIndex");
		GF_LSR_WRITE_INT(lsr, (u32) index, lsr->colorIndexBits, name);
	} else {
		GF_LSR_WRITE_INT(lsr, 0, 1, "hasIndex");
		if (!color) {
			GF_LSR_WRITE_INT(lsr, 1, 1, "isEnum");
			GF_LSR_WRITE_INT(lsr, 2, 2, "none");
		} else if (color->type==SVG_COLOR_INHERIT) {
			GF_LSR_WRITE_INT(lsr, 1, 1, "isEnum");
			GF_LSR_WRITE_INT(lsr, 0, 2, "inherit");
		} else if (color->type==SVG_COLOR_CURRENTCOLOR) {
			GF_LSR_WRITE_INT(lsr, 1, 1, "isEnum");
			GF_LSR_WRITE_INT(lsr, 1, 2, "inherit");
		} else {
			GF_LSR_WRITE_INT(lsr, 0, 1, "isEnum");
			lsr_write_vl5string(lsr, "WHATHEHECK", "colorExType0");
		}
	}
}

static void lsr_write_color_class(GF_LASeRCodec *lsr, SVG_Paint *paint, const char *name)
{
	if (paint->type == SVG_PAINT_NONE) {
		GF_LSR_WRITE_INT(lsr, 3, 2, "choice");
		GF_LSR_WRITE_INT(lsr, 2, 2, "none");
	} else if (paint->type == SVG_PAINT_INHERIT) {
		GF_LSR_WRITE_INT(lsr, 3, 2, "choice");
		GF_LSR_WRITE_INT(lsr, 1, 2, "inherit");
	} else if ((paint->type==SVG_PAINT_COLOR) && (paint->color->type==SVG_COLOR_CURRENTCOLOR) ) {
		GF_LSR_WRITE_INT(lsr, 3, 2, "choice");
		GF_LSR_WRITE_INT(lsr, 0, 2, "currentColor");
	} else if (paint->type==SVG_PAINT_COLOR) {
		GF_LSR_WRITE_INT(lsr, 0, 2, "choice");
		lsr_write_color(lsr, paint->color, name);
	} else if (paint->type==SVG_PAINT_URI) {
		GF_LSR_WRITE_INT(lsr, 2, 2, "choice");
		lsr_write_codec_IDREF(lsr, NULL, paint->uri);
	} else {
		GF_LSR_WRITE_INT(lsr, 1, 2, "choice");
		lsr_write_vl5string(lsr, "WHATHEHECK", "colorExType0");
	}
}

static void lsr_write_line_increment_type(GF_LASeRCodec *lsr, SVG_LineIncrement *li, const char *name)
{
	if (li->type==SVG_NUMBER_INHERIT) {
		GF_LSR_WRITE_INT(lsr, 1, 1, "choice");
		GF_LSR_WRITE_INT(lsr, 1, 1, "inherit");
	} else if (li->type==SVG_NUMBER_AUTO) {
		GF_LSR_WRITE_INT(lsr, 1, 1, "choice");
		GF_LSR_WRITE_INT(lsr, 0, 1, "auto");
	} else {
		GF_LSR_WRITE_INT(lsr, 0, 1, "choice");
		lsr_write_fixed_16_8(lsr, li->value, "line-increment-value");
	}
}

static void lsr_write_byte_align_string(GF_LASeRCodec *lsr, char *str, const char *name)
{
	u32 len = strlen(str);
	gf_bs_align(lsr->bs);
	gf_bs_write_u8(lsr->bs, len);
	gf_bs_write_data(lsr->bs, str, len);
	lsr_enc_log_bits(lsr, 0, 8+8*len, name);
}
static void lsr_write_byte_align_string_list(GF_LASeRCodec *lsr, GF_List *l, const char *name)
{
	char text[4096];
	u32 i, count = gf_list_count(l);
	text[0] = 0;
	for (i=0; i<count; i++) {
		char *str = gf_list_get(l, count);
		strcat(text, "'");
		strcat(text, str);
		strcat(text, "'");
		if (i+1<count) strcat(text, ",");
	}
	lsr_write_byte_align_string(lsr, text, name);
}

static void lsr_write_any_uri(GF_LASeRCodec *lsr, SVG_IRI *iri, const char *name)
{
	GF_LSR_WRITE_INT(lsr, (iri->type==SVG_IRI_IRI) ? 1 : 0, 1, "hasUri");
	if (iri->type==SVG_IRI_IRI) {
		if (!iri->iri || strnicmp(iri->iri, "data:", 5)) {
			lsr_write_byte_align_string(lsr, iri->iri, "uri");
			GF_LSR_WRITE_INT(lsr, 0, 1, "hasData");
		} else {
			u32 len;
			char *sep = strchr(iri->iri, ',');
			sep[0] = 0;
			lsr_write_byte_align_string(lsr, sep, "uri");
			sep[0] = ',';
			len = strlen(sep+1);
			GF_LSR_WRITE_INT(lsr, 1, 1, "hasData");
			lsr_write_vluimsbf5(lsr, len, "len");
			gf_bs_write_data(lsr->bs, sep+1, len);
		}
    }
	GF_LSR_WRITE_INT(lsr, (iri->type==SVG_IRI_ELEMENTID) ? 1 : 0, 1, "hasID");
	if (iri->type==SVG_IRI_ELEMENTID) lsr_write_codec_IDREF(lsr, iri, "idref");

	GF_LSR_WRITE_INT(lsr, 0, 1, "hasStreamID");
    //if (hasStreamID) lsr_write_codec_IDREF(lsr, iri, "idref");
}

static void lsr_write_private_att_class(GF_LASeRCodec *lsr)
{
	/*NO PRIVATE DATA ON ENCODING YET*/
	assert(0);
}

static void lsr_write_private_attr_container(GF_LASeRCodec *lsr, u32 index, const char *name)
{
	assert(0);
}

static void lsr_write_any_attribute(GF_LASeRCodec *lsr, GF_Node *node, SVGElement *clone)
{
	if (1) {
		GF_LSR_WRITE_INT(lsr, 0, 1, "has_attrs");
	} else {
		GF_LSR_WRITE_INT(lsr, 1, 1, "has_attrs");
/*
		do () {
			GF_LSR_WRITE_INT(lsr, 0, lsr->info->cfg.extensionIDBits, "reserved");
		    lsr_write_vluimsbf5(lsr, 0, "len");//len in BITS
			GF_LSR_WRITE_INT(lsr, 0, 0, "reserved_val");
		} while () 
*/
	}
}

static void lsr_write_object_content(GF_LASeRCodec *lsr, SVGElement *elt)
{
	if (1) {
		GF_LSR_WRITE_INT(lsr, 0, 1, "opt_group");
	} else {
		GF_LSR_WRITE_INT(lsr, 1, 1, "opt_group");
		lsr_write_private_att_class(lsr);
	}
}
static void lsr_write_string_attribute(GF_LASeRCodec *lsr, char *class_attr, char *name)
{
	if (class_attr) {
		GF_LSR_WRITE_INT(lsr, 1, 1, name);
		lsr_write_byte_align_string(lsr, class_attr, name);
	} else {
		GF_LSR_WRITE_INT(lsr, 0, 1, name);
	}
}
static void lsr_write_id(GF_LASeRCodec *lsr, GF_Node *n)
{
	u32 id = gf_node_get_id(n);
	if (id) {
		GF_LSR_WRITE_INT(lsr, 1, 1, "has__0_id");
	    lsr_write_vluimsbf5(lsr, id, "ID");
	    if (lsr->info->cfg.has_string_ids) lsr_write_byte_align_string(lsr, (char *) gf_node_get_name(n), "stringId");
		GF_LSR_WRITE_INT(lsr, 0, 1, "reserved");
#if TODO_LASER_EXTENSIONS	
		if (0) {
		    lsr_write_vluimsbf5(lsr, reserved_len, "len");
			GF_LSR_WRITE_INT(lsr, 0, reserved_len, "reserved");
		}
#endif
	} else {
		GF_LSR_WRITE_INT(lsr, 0, 1, "has__0_id");
	}
}

/*start of RARE properties*/
#define RARE_AUDIO_LEVEL		1
#define RARE_COLOR				2
#define RARE_COLOR_RENDERING	3
#define RARE_DISPLAY			4
#define RARE_DISPLAY_ALIGN		5
#define RARE_FILL_OPACITY		6
#define RARE_FILL_RULE			7
#define RARE_IMAGE_RENDERING	8
#define RARE_POINTER_EVENTS		10
#define RARE_SHAPE_RENDERING	11
#define RARE_SOLID_COLOR		12
#define RARE_SOLID_OPACITY		13
#define RARE_STOP_COLOR			14
#define RARE_STOP_OPACITY		15
#define RARE_STROKE_DASHARRAY	16
#define RARE_STROKE_DASHOFFSET	17
#define RARE_STROKE_LINECAP		18
#define RARE_STROKE_LINEJOIN	19
#define RARE_STROKE_MITERLIMIT	20
#define RARE_STROKE_OPACITY		21
#define RARE_STROKE_WIDTH		22
#define RARE_TEXT_ANCHOR		23
#define RARE_TEXT_RENDERING		24
#define RARE_VIEWPORT_FILL		25
#define RARE_VIEWPORT_FILL_OPACITY	26
#define RARE_VECTOR_EFFECT		27
#define RARE_VISIBILITY			28
#define RARE_FONT_FAMILY		51
#define RARE_FONT_SIZE			52
#define RARE_FONT_STYLE			53
#define RARE_FONT_WEIGHT		54
/*end of RARE properties*/
/*conditional processing*/
#define RARE_REQUIREDEXTENSIONS	29
#define RARE_REQUIREDFEATURES	30
#define RARE_REQUIREDFORMATS	31
#define RARE_SYSTEMLANGUAGE		32
/*XML*/
#define RARE_XML_BASE			33
#define RARE_XML_LANG			34
#define RARE_XML_SPACE			35
/*focus*/
#define RARE_FOCUSNEXT			36
#define RARE_FOCUSNORTH			37
#define RARE_FOCUSNORTHEAST		38
#define RARE_FOCUSNORTHWEST		39
#define RARE_FOCUSPREV			40
#define RARE_FOCUSSOUTH			41
#define RARE_FOCUSSOUTHEAST		42
#define RARE_FOCUSSOUTHWEST		43
#define RARE_FOCUSWEST			44
#define RARE_FOCUSABLE			45
#define RARE_FOCUSEAST			46
/*href*/
#define RARE_HREF_TITLE			55
#define RARE_HREF_TYPE			56
#define RARE_HREF_ROLE			57
#define RARE_HREF_ARCROLE		58
#define RARE_HREF_ACTUATE		59
#define RARE_HREF_SHOW			60
/*timing*/
#define RARE_END				61
#define RARE_MAX				62
#define RARE_MIN				63

#define RARE_TRANSFORM			47
#define RARE_LSR_ROTATION		48
#define RARE_LSR_SCALE			49
#define RARE_LSR_TRANSLATION	50


static u32 lsr_get_rare_props_idx(SVGElement *n, GF_FieldInfo *info)
{
	if (&n->properties->audio_level == info->far_ptr) return RARE_AUDIO_LEVEL;
	else if (&n->properties->color == info->far_ptr) return RARE_COLOR;
	else if (&n->properties->color_rendering == info->far_ptr) return RARE_COLOR_RENDERING;
	else if (&n->properties->display == info->far_ptr) return RARE_DISPLAY;
	else if (&n->properties->display_align == info->far_ptr) return RARE_DISPLAY_ALIGN;
	else if (&n->properties->fill_opacity == info->far_ptr) return RARE_FILL_OPACITY;
	else if (&n->properties->fill_rule == info->far_ptr) return RARE_FILL_RULE;
	else if (&n->properties->image_rendering == info->far_ptr) return RARE_IMAGE_RENDERING;
	else if (&n->properties->pointer_events == info->far_ptr) return RARE_POINTER_EVENTS;
	else if (&n->properties->shape_rendering == info->far_ptr) return RARE_SHAPE_RENDERING;
	else if (&n->properties->solid_color == info->far_ptr) return RARE_SOLID_COLOR;
	else if (&n->properties->solid_opacity == info->far_ptr) return RARE_SOLID_OPACITY;
	else if (&n->properties->stop_color == info->far_ptr) return RARE_STOP_COLOR;
	else if (&n->properties->stop_opacity == info->far_ptr) return RARE_STOP_OPACITY;
	else if (&n->properties->stroke_dasharray == info->far_ptr) return RARE_STROKE_DASHARRAY;
	else if (&n->properties->stroke_dashoffset == info->far_ptr) return RARE_STROKE_DASHOFFSET;
	else if (&n->properties->stroke_linecap == info->far_ptr) return RARE_STROKE_LINECAP;
	else if (&n->properties->stroke_linejoin == info->far_ptr) return RARE_STROKE_LINEJOIN;
	else if (&n->properties->stroke_miterlimit == info->far_ptr) return RARE_STROKE_MITERLIMIT;
	else if (&n->properties->stroke_opacity == info->far_ptr) return RARE_STROKE_OPACITY;
	else if (&n->properties->stroke_width == info->far_ptr) return RARE_STROKE_WIDTH;
	else if (&n->properties->text_anchor == info->far_ptr) return RARE_TEXT_ANCHOR;
	else if (&n->properties->text_rendering == info->far_ptr) return RARE_TEXT_RENDERING;
	else if (&n->properties->viewport_fill == info->far_ptr) return RARE_VIEWPORT_FILL;
	else if (&n->properties->viewport_fill_opacity == info->far_ptr) return RARE_VIEWPORT_FILL_OPACITY;
	else if (&n->properties->vector_effect == info->far_ptr) return RARE_VECTOR_EFFECT;
	else if (&n->properties->visibility == info->far_ptr) return RARE_VISIBILITY;
	else if (&n->properties->font_family == info->far_ptr) return RARE_FONT_FAMILY;
	else if (&n->properties->font_size == info->far_ptr) return RARE_FONT_SIZE;
	else if (&n->properties->font_style == info->far_ptr) return RARE_FONT_STYLE;
	else if (&n->properties->font_weight == info->far_ptr) return RARE_FONT_WEIGHT;

	return 0;
}

static void lsr_write_fixed_clamp(GF_LASeRCodec *lsr, Fixed f, const char *name)
{
#ifdef GPAC_FIXED_POINT
	s32 val = f >> 8;
#else
	s32 val = (u32) (255 * f);
#endif
	if (val<0) val = 0;
	else if (val>255) val = 255;
	GF_LSR_WRITE_INT(lsr, (u32) val, 8, name);
}

static void lsr_write_focus(GF_LASeRCodec *lsr, void *foc, const char *name)
{
	fprintf(stdout, "ERROR: FOCUS NOT IMPLEMENTED\n");
}

static void lsr_write_rare(GF_LASeRCodec *lsr, GF_Node *n, GF_Node *default_node)
{
	GF_FieldInfo all_info[100];
	u32 i, count, nb_rare, field_rare;

	nb_rare = 0;
	count = gf_node_get_field_count(n);
	for (i=0; i<count; i++) {
		GF_FieldInfo def_info;
		gf_node_get_field(n, i, &all_info[nb_rare]);
		/*check if rare*/
		field_rare = lsr_get_rare_props_idx((SVGElement *)n, &all_info[nb_rare]);
		if (!field_rare) continue;
		/*check if default*/
		gf_node_get_field(default_node, i, &def_info);
		if (svg_attributes_equal(&all_info[nb_rare], &def_info)) continue;
		/*override field index to store rare val*/
		all_info[nb_rare].fieldIndex = field_rare;
		nb_rare++;
	}

	GF_LSR_WRITE_INT(lsr, nb_rare ? 1 : 0, 1, "has__0_rare");
	if (!nb_rare) return;

	GF_LSR_WRITE_INT(lsr, nb_rare, 6, "nbOfAttributes");
	for (i=0; i<nb_rare; i++) {
		GF_FieldInfo *fi = &all_info[i];
		GF_LSR_WRITE_INT(lsr, fi->fieldIndex, 6, "attributeRARE");
		switch (fi->fieldIndex) {
		/*properties*/

		/*TODO !!!! what about inherit types??*/
		case RARE_AUDIO_LEVEL: lsr_write_fixed_clamp(lsr, ((SVG_Number *) fi->far_ptr)->value, "audio-level"); break;
		case RARE_FILL_OPACITY: lsr_write_fixed_clamp(lsr, ((SVG_Number *)fi->far_ptr)->value, "fill-opacity"); break;
		case RARE_SOLID_OPACITY: lsr_write_fixed_clamp(lsr, ((SVG_Number *)fi->far_ptr)->value, "solid-opacity"); break;
		case RARE_STOP_OPACITY: lsr_write_fixed_clamp(lsr, ((SVG_Number *)fi->far_ptr)->value, "stop-opacity"); break;
		case RARE_STROKE_OPACITY: lsr_write_fixed_clamp(lsr, ((SVG_Number *)fi->far_ptr)->value, "stroke-opacity"); break;
		case RARE_VIEWPORT_FILL_OPACITY: lsr_write_fixed_clamp(lsr, ((SVG_Number *)fi->far_ptr)->value, "viewport-fill-opacity"); break;

	    case RARE_COLOR: lsr_write_color(lsr, fi->far_ptr, "color"); break;
	    case RARE_SOLID_COLOR: lsr_write_color_class(lsr, fi->far_ptr, "solid-color"); break;
	    case RARE_STOP_COLOR: lsr_write_color_class(lsr, fi->far_ptr, "stop-color"); break;
	    case RARE_VIEWPORT_FILL: lsr_write_color_class(lsr, fi->far_ptr, "viewport-fill"); break;

		case RARE_DISPLAY: GF_LSR_WRITE_INT(lsr, *(SVG_Display*)fi->far_ptr, 5, "display"); break;
	    case RARE_DISPLAY_ALIGN: GF_LSR_WRITE_INT(lsr, *(SVG_DisplayAlign*)fi->far_ptr, 2, "display-align"); break;
	    case RARE_FILL_RULE: GF_LSR_WRITE_INT(lsr, *(SVG_FillRule*)fi->far_ptr, 2, "fill-rule"); break;

		case RARE_COLOR_RENDERING: GF_LSR_WRITE_INT(lsr, *(SVG_RenderingHint*)fi->far_ptr, 2, "color-rendering"); break;
		case RARE_IMAGE_RENDERING: GF_LSR_WRITE_INT(lsr, *(SVG_RenderingHint*)fi->far_ptr, 2, "image-rendering"); break;
		case RARE_SHAPE_RENDERING: GF_LSR_WRITE_INT(lsr, *(SVG_RenderingHint*)fi->far_ptr, 3, "shape-rendering"); break;
		case RARE_TEXT_RENDERING: GF_LSR_WRITE_INT(lsr, *(SVG_RenderingHint*)fi->far_ptr, 2, "text-rendering"); break;
		/*TODO FIXME - SVG values are not in sync with LASeR*/
		case RARE_STROKE_LINECAP: GF_LSR_WRITE_INT(lsr, *(SVG_StrokeLineCap*)fi->far_ptr, 2, "stroke-linecap"); break;
		case RARE_STROKE_LINEJOIN: GF_LSR_WRITE_INT(lsr, *(SVG_StrokeLineJoin*)fi->far_ptr, 2, "stroke-linejoin"); break;
		case RARE_TEXT_ANCHOR: GF_LSR_WRITE_INT(lsr, *(SVG_TextAnchor*)fi->far_ptr, 2, "text-achor"); break;
		case RARE_VECTOR_EFFECT: GF_LSR_WRITE_INT(lsr, *(SVG_VectorEffect*)fi->far_ptr, 4, "vector-effect"); break;
	    case RARE_POINTER_EVENTS: GF_LSR_WRITE_INT(lsr, *(SVG_PointerEvents*)fi->far_ptr, 4, "pointer-events"); break;
	    case RARE_VISIBILITY: GF_LSR_WRITE_INT(lsr, *(SVG_PointerEvents*)fi->far_ptr, 2, "visibility"); break;

		case RARE_FONT_FAMILY:
		{
			s32 idx = lsr_get_font_index(lsr, fi->far_ptr);
			if (idx<0) {
				GF_LSR_WRITE_INT(lsr, 1, 1, "isInherit");
			} else {
				GF_LSR_WRITE_INT(lsr, 0, 1, "isInherit");
				GF_LSR_WRITE_INT(lsr, idx, lsr->fontIndexBits, "fontIndex");
			}
		}
			break;
		case RARE_FONT_SIZE: lsr_write_fixed_16_8(lsr, ((SVG_FontSize *)fi->far_ptr)->value, "fontSize"); break;
		/*TODO not specified in spec !!*/
		case RARE_FONT_STYLE: GF_LSR_WRITE_INT(lsr, *((SVG_FontStyle *)fi->far_ptr), 5, "fontStyle"); break;
		/*TODO not specified in spec !!*/
		case RARE_FONT_WEIGHT: GF_LSR_WRITE_INT(lsr, *((SVG_FontWeight *)fi->far_ptr), 4, "fontWeight"); break;

		/*other stuff */
	    case RARE_REQUIREDEXTENSIONS: lsr_write_byte_align_string_list(lsr, *(GF_List **)fi->far_ptr, "requiredExtensions");
	    case RARE_REQUIREDFORMATS: lsr_write_byte_align_string_list(lsr, *(GF_List **)fi->far_ptr, "requiredFormats");
	    case RARE_REQUIREDFEATURES: lsr_write_byte_align_string_list(lsr, *(GF_List **)fi->far_ptr, "requiredFeatures");
	    case RARE_SYSTEMLANGUAGE: lsr_write_byte_align_string_list(lsr, *(GF_List **)fi->far_ptr, "systemLanguage");
	    case RARE_XML_BASE: lsr_write_byte_align_string(lsr, *(SVG_String *)fi->far_ptr, "xml:base"); break;
	    case RARE_XML_LANG: lsr_write_byte_align_string(lsr, *(SVG_String *)fi->far_ptr, "xml:lang"); break;
	    case RARE_XML_SPACE: GF_LSR_WRITE_INT(lsr, *(XML_Space *)fi->far_ptr, 1, "xml:space"); break;
		/*focusable*/
		case RARE_FOCUSNEXT: lsr_write_focus(lsr, fi->far_ptr, "focusNext"); break;
		case RARE_FOCUSNORTH: lsr_write_focus(lsr, fi->far_ptr, "focusNorth"); break;
		case RARE_FOCUSNORTHEAST: lsr_write_focus(lsr, fi->far_ptr, "focusNorthEast"); break;
		case RARE_FOCUSNORTHWEST: lsr_write_focus(lsr, fi->far_ptr, "focusNorthWest"); break;
		case RARE_FOCUSPREV: lsr_write_focus(lsr, fi->far_ptr, "focusPrev"); break;
		case RARE_FOCUSSOUTH: lsr_write_focus(lsr, fi->far_ptr, "focusSouth"); break;
		case RARE_FOCUSSOUTHEAST: lsr_write_focus(lsr, fi->far_ptr, "focusSouthEast"); break;
		case RARE_FOCUSSOUTHWEST: lsr_write_focus(lsr, fi->far_ptr, "focusSouthWest"); break;
		case RARE_FOCUSWEST: lsr_write_focus(lsr, fi->far_ptr, "focusWest"); break;
		case RARE_FOCUSEAST: lsr_write_focus(lsr, fi->far_ptr, "focusEast"); break;

		}
	}
}

static void lsr_write_fill(GF_LASeRCodec *lsr, SVGElement *n, SVGElement *clone)
{
	GF_FieldInfo f1, f2;
	Bool has_fill;
	f1.fieldType = f2.fieldType = SVG_Paint_datatype;
	f1.far_ptr = &n->properties->fill;
	f2.far_ptr = &clone->properties->fill;
	has_fill = svg_attributes_equal(&f1, &f2) ? 0 : 1;
	GF_LSR_WRITE_INT(lsr, has_fill, 1, "has__1_fill");
	if (has_fill) lsr_write_color_class(lsr, f1.far_ptr, "_1_fill");
}

static void lsr_write_line_increment(GF_LASeRCodec *lsr, SVGElement *n, SVGElement *clone)
{
	GF_FieldInfo f1, f2;
	Bool has_line_inc;
	f1.fieldType = f2.fieldType = SVG_LineIncrement_datatype;
	f1.far_ptr = &n->properties->line_increment;
	f2.far_ptr = &clone->properties->line_increment;
	has_line_inc = svg_attributes_equal(&f1, &f2) ? 0 : 1;
	GF_LSR_WRITE_INT(lsr, has_line_inc, 1, "has__1_line-increment");
	if (has_line_inc) lsr_write_line_increment_type(lsr, f1.far_ptr, "_1_line-increment");
}

static void lsr_write_stroke(GF_LASeRCodec *lsr, SVGElement *n, SVGElement *clone)
{
	GF_FieldInfo f1, f2;
	Bool has_stroke;
	f1.fieldType = f2.fieldType = SVG_Paint_datatype;
	f1.far_ptr = &n->properties->stroke;
	f2.far_ptr = &clone->properties->stroke;
	has_stroke = svg_attributes_equal(&f1, &f2) ? 0 : 1;
	GF_LSR_WRITE_INT(lsr, has_stroke, 1, "has__1_stroke");
	if (has_stroke) lsr_write_color_class(lsr, f1.far_ptr, "_1_stroke");
}
static void lsr_write_href(GF_LASeRCodec *lsr, SVG_IRI *iri)
{
	if (!iri || ((iri->type==SVG_IRI_ELEMENTID) && !iri->target)) {
		GF_LSR_WRITE_INT(lsr, 0, 1, "has_href");
	} else {
		GF_LSR_WRITE_INT(lsr, 1, 1, "has_href");
		lsr_write_any_uri(lsr, iri, "href");
	}
}

static void lsr_write_accumulate(GF_LASeRCodec *lsr, u8 accum_type)
{
	Bool v = accum_type ? 1 : 0;
	GF_LSR_WRITE_INT(lsr, v ? 1 : 0, 1, "has__4_accumulate");
	if (v) GF_LSR_WRITE_INT(lsr, v ? 1 : 0, 1, "_4_accumulate");
}
static void lsr_write_additive(GF_LASeRCodec *lsr, u8 add_type)
{
	Bool v = add_type ? 1 : 0;
	GF_LSR_WRITE_INT(lsr, v ? 1 : 0, 1, "has__4_additive");
	if (v) GF_LSR_WRITE_INT(lsr, v ? 1 : 0, 1, "_4_additive");
}
static void lsr_write_calc_mode(GF_LASeRCodec *lsr, u8 calc_mode)
{
	/*SMIL_CALCMODE_LINEAR is default and 0 in our code*/
	GF_LSR_WRITE_INT(lsr, calc_mode ? 0 : 1, 1, "has__4_calcMode");
	if (calc_mode) {
		/*SMIL_CALCMODE_DISCRETE is 0 in LASeR, 1 in our code*/
		if (calc_mode==1) calc_mode = 0;
		GF_LSR_WRITE_INT(lsr, calc_mode, 2, name);
	}
}

static void lsr_write_animatable(GF_LASeRCodec *lsr, SMIL_AttributeName *anim_type, SVGElement *elt, const char *name)
{
/*enumeration 
	audio-level{0} choice{1} color{2} color-rendering{3} cx{4} cy{5} d{6} display{7} display-align{8} editable{9} 
	fill{10} fill-opacity{11} fill-rule{12} 
	focusEast{13} focusNorth{14} focusNorthEast{15} focusNorthWest{16} focusSouth{17} focusSouthEast{18} 
	focusSouthWest{19} focusWest{20} focusable{21} font-family{22} font-size{23} font-style{24} font-weight{25} 
	gradientUnits{26} height{27} image-rendering{28} line-increment{29} opacity{30} pathLength{31} pointer-events{32} 
	points{33} preserveAspectRatio{34} r{35} rotate{36} rx{37} ry{38} shape-rendering{39} size{40} solid-color{41} 
	solid-opacity{42} stop-color{43} stop-opacity{44} stroke{45} stroke-dasharray{46} stroke-dashoffset{47} 
	stroke-linecap{48} stroke-linejoin{49} stroke-miterlimit{50} stroke-opacity{51} stroke-width{52} 
	target{53} text-anchor{54} transform{55} type{56} vector-effect{57} viewBox{58} viewport-fill{59} 
	viewport-fill-opacity{60} visibility{61} width{62} x{63} x1{64} x2{65} xlink:href{66} y{67} y1{68} y2{69} 
*/
	//bit(8) animatable;
	GF_LSR_WRITE_INT(lsr, anim_type->type, 8, "attributeType");
}
static void lsr_write_time(GF_LASeRCodec *lsr, GF_List *l, const char *name)
{
	SMIL_Time *v;
	u32 count = gf_list_count(l);

	if (!count) {
		GF_LSR_WRITE_INT(lsr, 0, 1, name);
		return;
	}

	/*TODO FIX SDL SYNTAX*/
	v = gf_list_get(l, 0);
	if (v->dynamic_type) {
		fprintf(stdout, "LSR SMIL TIME EVENT NOT SUPPORTED\n");
		GF_LSR_WRITE_INT(lsr, 0, 1, name);
		return;
	}

	GF_LSR_WRITE_INT(lsr, 1, 1, name);

	if (v->type==SMIL_TIME_CLOCK) {
		s32 now = (s32) (v->clock * lsr->time_resolution);
		GF_LSR_WRITE_INT(lsr, 0, 1, "choice");
		/*TODO - SPEC IS UNCLEAR HERE*/
		GF_LSR_WRITE_INT(lsr, (now<0) ? 1 : 0, 1, "sign");
		if (now<0) now = -now;
		lsr_write_vluimsbf5(lsr, now, "value");
	} else {
		GF_LSR_WRITE_INT(lsr, 1, 1, "choice");
		GF_LSR_WRITE_INT(lsr, (v->type==SMIL_TIME_INDEFINITE) ? 0 : 1, 1, "time");
	}
}

static void lsr_write_single_time(GF_LASeRCodec *lsr, SMIL_Time *v, const char *name)
{
	if (!v || v->dynamic_type) {
		GF_LSR_WRITE_INT(lsr, 0, 1, name);
		return;
	}
	GF_LSR_WRITE_INT(lsr, 1, 1, name);

	if (v->type==SMIL_TIME_CLOCK) {
		s32 now = (s32) (v->clock * lsr->time_resolution);
		GF_LSR_WRITE_INT(lsr, 0, 1, "choice");
		/*TODO - SPEC IS UNCLEAR HERE*/
		GF_LSR_WRITE_INT(lsr, (now<0) ? 1 : 0, 1, "sign");
		if (now<0) now = -now;
		lsr_write_vluimsbf5(lsr, now, "value");
	} else {
		GF_LSR_WRITE_INT(lsr, 1, 1, "choice");
		GF_LSR_WRITE_INT(lsr, (v->type==SMIL_TIME_INDEFINITE) ? 0 : 1, 1, "time");
	}
}

static void lsr_write_duration(GF_LASeRCodec *lsr, SMIL_Duration *smil, const char *name)
{
	GF_LSR_WRITE_INT(lsr, smil->type ? 1 : 0, 1, "has__5_dur");
	if (!smil->type) return;

	if (smil->type==SMIL_DURATION_DEFINED) {
		s32 now = (s32) (smil->clock_value * lsr->time_resolution);
		GF_LSR_WRITE_INT(lsr, 0, 1, "choice");
		/*TODO - SPEC IS UNCLEAR HERE*/
		GF_LSR_WRITE_INT(lsr, (now<0) ? 1 : 0, 1, "sign");
		if (now<0) now = -now;
		lsr_write_vluimsbf5(lsr, now, "value");
	} else {
		GF_LSR_WRITE_INT(lsr, 1, 1, "choice");
		GF_LSR_WRITE_INT(lsr, (smil->type==SMIL_DURATION_INDEFINITE) ? 0 : 1, 1, "time");
	}
}
static void lsr_write_anim_fill(GF_LASeRCodec *lsr, u8 animFreeze, const char *name)
{
	/*don't write if default !!*/
	if (animFreeze==SMIL_FILL_FREEZE) {
		GF_LSR_WRITE_INT(lsr, 0, 1, name);
	} else {
		GF_LSR_WRITE_INT(lsr, 1, 1, name);
		/*enumeration freeze{0} remove{1}*/
		GF_LSR_WRITE_INT(lsr, 1, 1, name);
	}
}
static void lsr_write_anim_repeat(GF_LASeRCodec *lsr, SMIL_RepeatCount *repeat, const char *name)
{
	GF_LSR_WRITE_INT(lsr, repeat->type ? 1 : 0, 1, name);
	if (!repeat->type) return;
	if (repeat->type==SMIL_REPEATCOUNT_DEFINED) {
		GF_LSR_WRITE_INT(lsr, 0, 1, name);
		/*TODO - SPEC IS WRONG HERE*/
		lsr_write_vluimsbf5(lsr, FIX2INT(repeat->count), name);
	} else {
		/*enumeration indefinite{0}*/
		GF_LSR_WRITE_INT(lsr, 1, 1, name);
	}
}
static void lsr_write_anim_restart(GF_LASeRCodec *lsr, u8 animRestart, const char *name)
{
	if (animRestart == SMIL_RESTART_ALWAYS) {
		GF_LSR_WRITE_INT(lsr, 0, 1, name);
	} else {
		GF_LSR_WRITE_INT(lsr, 1, 1, name);
		/*enumeration always{0} never{1} whenNotActive{2}*/
		GF_LSR_WRITE_INT(lsr, animRestart, 2, name);
	}
}

static void lsr_write_an_anim_value(GF_LASeRCodec *lsr, SMIL_AnimateValue *val, u32 type, const char *name)
{
	GF_LSR_WRITE_INT(lsr, 0, 1, "escapeFlag");
    if (0) GF_LSR_WRITE_INT(lsr, 0, 2, "escapeEnum");

    switch(type) {
    case 0: lsr_write_byte_align_string(lsr, *(DOM_String *)val->value, name); break;
    case 1: lsr_write_fixed_16_8(lsr, *(Fixed *) val->value, name); break;
    case 12: lsr_write_any_uri(lsr, val->value, name); break;
#if TODO_LASER_EXTENSIONS	
    case 2: lsr_write_path(lsr, val->value, name); break;
    case 3: lsr_write_point_sequence(lsr, val->value, name); break;
#endif
    case 4: lsr_write_fixed_clamp(lsr, *(Fixed *) val->value, name); break;
    case 5: lsr_write_color_class(lsr, val->value, name); break;
    case 6: lsr_write_vluimsbf5(lsr, (u32) *(u8 *) val->value, name); break;
    case 10: lsr_write_vluimsbf5(lsr, *(u32 *) val->value, name); break;
#if TODO_LASER_EXTENSIONS	
    case 11: // font
        vluimsbf5 j;
        value = fontTable[j];
        break;
#endif
    case 7:
	{
		GF_List *l = *(GF_List **)val->value;
		u32 i, count = gf_list_count(l);
		lsr_write_vluimsbf5(lsr, count, "count");
        for (i=0; i<count; i++) {
			u8 *v = gf_list_get(l, i);
			lsr_write_vluimsbf5(lsr, *v, "val");
        }
	}
        break;
    case 8: // floats
	{
		GF_List *l = *(GF_List **)val->value;
		u32 i, count = gf_list_count(l);
		lsr_write_vluimsbf5(lsr, count, "count");
        for (i=0; i<count; i++) {
			Fixed *v = gf_list_get(l, i);
			lsr_write_fixed_16_8(lsr, *v, "val");
        }
	}
        break;
    case 9: // point
		lsr_write_fixed_16_8(lsr, ((SVG_Point *)val->value)->x, "val");
		lsr_write_fixed_16_8(lsr, ((SVG_Point *)val->value)->y, "val");
        break;
    default:
		lsr_write_extension_class(lsr, NULL, 0, name);
        break;
    }
}

static void lsr_write_anim_value(GF_LASeRCodec *lsr, SMIL_AnimateValue *val, const char *name)
{
	u32 type = val->type;
	if (!val->type) {
		GF_LSR_WRITE_INT(lsr, 0, 1, name);
	} else {
		GF_LSR_WRITE_INT(lsr, 1, 1, name);
		GF_LSR_WRITE_INT(lsr, type, 4, "type");
		lsr_write_an_anim_value(lsr, val, type, name);
	}
}

static void lsr_write_anim_values(GF_LASeRCodec *lsr, SMIL_AnimateValues *anims, const char *name)
{
	u32 i, count = 0;
	u32 type = anims->type;
	if (anims->type) count = gf_list_count(anims->values);

	if (!count) {
		GF_LSR_WRITE_INT(lsr, 0, 1, name);
		return;
	}
	GF_LSR_WRITE_INT(lsr, 1, 1, name);
	GF_LSR_WRITE_INT(lsr, type, 4, "type");
	lsr_write_vluimsbf5(lsr, count, "count");
	for (i=0; i<count; i++) {
		SMIL_AnimateValue *att = gf_list_get(anims->values, i);
		lsr_write_an_anim_value(lsr, att, type, name);
	}
}

static void lsr_write_fraction_12(GF_LASeRCodec *lsr, GF_List *l, const char *name)
{
	u32 i, count = gf_list_count(l);
	if (!count) {
		GF_LSR_WRITE_INT(lsr, 0, 1, name);
		return;
	}
	GF_LSR_WRITE_INT(lsr, 1, 1, name);
	lsr_write_vluimsbf5(lsr, count, "name");
	for (i=0; i<count; i++) {
		Fixed f = * (Fixed *) gf_list_get(l, i);
		if (!f || (f == FIX_ONE)) {
			GF_LSR_WRITE_INT(lsr, 1, 1, "hasShort");
			GF_LSR_WRITE_INT(lsr, f ? 1 : 0, 1, "isZero");
		} else {
			u32 ft = (u32) ( FIX2FLT(f) * 4096/*(1<<12)*/ );
			GF_LSR_WRITE_INT(lsr, 0, 1, "hasShort");
			GF_LSR_WRITE_INT(lsr, ft, 12, "val");
		}
	}
}
static void lsr_write_float_list(GF_LASeRCodec *lsr, GF_List *l, const char *name)
{
	u32 i, count = gf_list_count(l);
	if (!count) {
		GF_LSR_WRITE_INT(lsr, 0, 1, name);
		return;
	}
	GF_LSR_WRITE_INT(lsr, 1, 1, name);
	lsr_write_vluimsbf5(lsr, count, "count");
	for (i=0;i<count;i++) {
		Fixed *v = gf_list_get(l, i);
		lsr_write_fixed_16_8(lsr, *v, "val");
	}
}

static u32 lsr_translate_coords(GF_LASeRCodec *lsr, Fixed x)
{
	u32 res;
	Fixed r = gf_divfix(x, lsr->res_factor);
	if (r>=0) return FIX2INT(r);
	r += INT2FIX(1<<lsr->coord_bits);
	if (r<0) fprintf(stdout, "resolution not high enough!!!\n");
	res = FIX2INT(r);
	res |= 1<<(lsr->coord_bits-1);
	return res;
}


static void lsr_write_point_sequence(GF_LASeRCodec *lsr, GF_List *pts, const char *name)
{
	u32 i, count = gf_list_count(pts);
	if (!count) return;
	lsr_write_vluimsbf5(lsr, count, "nbPoints");
	/*TODO laser point encoding*/
	GF_LSR_WRITE_INT(lsr, 0, 1, "flag");
    if (1) {
        if (count < 3) {
			u32 nb_bits = 0;
			for (i=0; i<count; i++) {
				u32 k;
				SVG_Point *pt = gf_list_get(pts, i);
				k = gf_get_bit_size(lsr_translate_coords(lsr, pt->x)); if (k>nb_bits) nb_bits = k;
				k = gf_get_bit_size(lsr_translate_coords(lsr, pt->y)); if (k>nb_bits) nb_bits = k;
			}

			GF_LSR_WRITE_INT(lsr, nb_bits, 5, "bits");
            for (i=0; i<count; i++) {
				SVG_Point *pt = gf_list_get(pts, i);
				u32 v = lsr_translate_coords(lsr, pt->x);
				GF_LSR_WRITE_INT(lsr, v, nb_bits, "bits");
				v = lsr_translate_coords(lsr, pt->y);
				GF_LSR_WRITE_INT(lsr, v, nb_bits, "bits");
            }
        } else {
			u32 nb_dx, nb_dy, k, x, y, dx, dy;
			SVG_Point *pt = gf_list_get(pts, 0);
			nb_dx = 0;
			x = lsr_translate_coords(lsr, pt->x);
			y = lsr_translate_coords(lsr, pt->y);
			k = gf_get_bit_size(x); if (k>nb_dx) nb_dx = k;
			k = gf_get_bit_size(y); if (k>nb_dx) nb_dx = k;
			GF_LSR_WRITE_INT(lsr, nb_dx, 5, "bits");
			GF_LSR_WRITE_INT(lsr, x, nb_dx, "x");
			GF_LSR_WRITE_INT(lsr, y, nb_dx, "x");

			nb_dx = nb_dy = 0;
			for (i=1; i<count; i++) {
				SVG_Point *pt = gf_list_get(pts, i);
				dx = lsr_translate_coords(lsr, pt->x); dx -= x;
				k = gf_get_bit_size(dx); if (k>nb_dx) nb_dx = k;
				dy = lsr_translate_coords(lsr, pt->y); dy -= y;
				k = gf_get_bit_size(dx); if (k>nb_dy) nb_dy = k;
				x += dx;
				y += dy;
			}
			GF_LSR_WRITE_INT(lsr, nb_dx, 5, "bitsx");
			GF_LSR_WRITE_INT(lsr, nb_dy, 5, "bitsy");
			x = lsr_translate_coords(lsr, pt->x);
			y = lsr_translate_coords(lsr, pt->y);
			for (i=1; i<count; i++) {
				SVG_Point *pt = gf_list_get(pts, i);
				dx = lsr_translate_coords(lsr, pt->x); dx -= x;
				GF_LSR_WRITE_INT(lsr, dx, nb_dx, "dx");
				dy = lsr_translate_coords(lsr, pt->y); dy -= y;
				GF_LSR_WRITE_INT(lsr, dy, nb_dy, "dy");
				x += dx;
				y += dy;
			}
        }
	}
	/*TODO golomb coding*/
}
static void lsr_write_path_type(GF_LASeRCodec *lsr, SVG_PathData *path, const char *name)
{
	u32 i, count;
	lsr_write_point_sequence(lsr, path->points, "seq");
	count = gf_list_count(path->commands);
    lsr_write_vluimsbf5(lsr, count, "nbOfTypes");
    for (i=0; i<count; i++) {
        u8 type = *(u8 *) gf_list_get(path->commands, i);
		GF_LSR_WRITE_INT(lsr, type, 8, name);
    }
}

static void lsr_write_rotate_type(GF_LASeRCodec *lsr, SVG_Rotate rotate, const char *name)
{
	if ((rotate.type == SVG_NUMBER_AUTO) || (rotate.type == SVG_NUMBER_AUTO_REVERSE)) {
		GF_LSR_WRITE_INT(lsr, 1, 1, name);
		GF_LSR_WRITE_INT(lsr, 1, 1, "choice");
		GF_LSR_WRITE_INT(lsr, (rotate.type == SVG_NUMBER_AUTO) ? 0 : 1, 1, "rotate");
	} else {
		GF_LSR_WRITE_INT(lsr, 0, 1, name);
	}
}
static void lsr_write_sync_behavior(GF_LASeRCodec *lsr, u8 sync, const char *name)
{
	if (sync==SMIL_SYNCBEHAVIOR_INHERIT) {
		GF_LSR_WRITE_INT(lsr, 0, 1, name);
	} else {
		GF_LSR_WRITE_INT(lsr, 1, 1, name);
		GF_LSR_WRITE_INT(lsr, sync-1, 2, name);
	}
}
static void lsr_write_sync_tolerance(GF_LASeRCodec *lsr, SMIL_SyncTolerance *sync, const char *name)
{
	if (sync->type==SMIL_SYNCTOLERANCE_INHERIT) {
		GF_LSR_WRITE_INT(lsr, 0, 1, name);
	} else {
		GF_LSR_WRITE_INT(lsr, 1, 1, name);
		if (sync->type==SMIL_SYNCTOLERANCE_DEFAULT) {
			GF_LSR_WRITE_INT(lsr, 1, 1, name);
		} else {
			GF_LSR_WRITE_INT(lsr, 0, 1, name);
		    lsr_write_vluimsbf5(lsr, (u32) (sync->value*lsr->time_resolution), "value");
		}
	}
}
static void lsr_write_coordinate(GF_LASeRCodec *lsr, Fixed val, Bool skipable, const char *name)
{
	if (!skipable && !val) {
		GF_LSR_WRITE_INT(lsr, 0, 1, name);
	} else {
		u32 res = lsr_translate_coords(lsr, val);
		if (skipable) GF_LSR_WRITE_INT(lsr, 1, 1, name);
		GF_LSR_WRITE_INT(lsr, res, lsr->coord_bits, name);
	}
}
static void lsr_write_transform_behavior(GF_LASeRCodec *lsr, u8 tr_type, const char *name)
{
	if (1) {
		GF_LSR_WRITE_INT(lsr, 0, 1, name);
	} else {
		GF_LSR_WRITE_INT(lsr, 1, 1, name);
		GF_LSR_WRITE_INT(lsr, 1, 4, name);
	}
}

static void lsr_write_content_type(GF_LASeRCodec *lsr, char *type, const char *name)
{
	if (type) {
		GF_LSR_WRITE_INT(lsr, 1, 1, "hasType");
		lsr_write_byte_align_string(lsr, type, "type");
	} else {
		GF_LSR_WRITE_INT(lsr, 0, 1, "hasType");
	}
}
static void lsr_write_value_with_units(GF_LASeRCodec *lsr, SVG_Number *n, const char *name)
{
#ifdef GPAC_FIXED_POINT
	s32 val = n->value >> 8;
#else
	s32 val = (s32) (n->value * (1<<8) );
#endif
	GF_LSR_WRITE_INT(lsr, val, 32, name);
    switch (n->type) {
	case SVG_NUMBER_IN: GF_LSR_WRITE_INT(lsr, 1, 3, "units"); break;
	case SVG_NUMBER_CM: GF_LSR_WRITE_INT(lsr, 2, 3, "units"); break;
	case SVG_NUMBER_MM: GF_LSR_WRITE_INT(lsr, 3, 3, "units"); break;
	case SVG_NUMBER_PT: GF_LSR_WRITE_INT(lsr, 4, 3, "units"); break;
	case SVG_NUMBER_PC: GF_LSR_WRITE_INT(lsr, 5, 3, "units"); break;
	case SVG_NUMBER_PERCENTAGE: GF_LSR_WRITE_INT(lsr, 6, 3, "units"); break;
	default: GF_LSR_WRITE_INT(lsr, 0, 3, "units"); break;
	}
}

static void lsr_write_event_type(GF_LASeRCodec *lsr, u32 evtType, char *evtName)
{
	if (evtName) {
		GF_LSR_WRITE_INT(lsr, 0, 1, "choice");
		lsr_write_byte_align_string(lsr, evtName, "evtString");
	} else {
		GF_LSR_WRITE_INT(lsr, 1, 1, "choice");
		/*enumeration abort{0} activate{1} begin{2} click{3} end{4} error{5} focusin{6} focusout{7} 
		keydown{8} keypress{9} keyup{10} load{11} longkeypress{12} mousedown{13} mouseout{14} 
		mouseover{15} mouseup{16} repeat{17} resize{18} scroll{19} textinput{20} unload{21} zoom{22} */
		switch (evtType) {
		case SVG_DOM_EVT_ABORT: GF_LSR_WRITE_INT(lsr, 0, 6, "event"); break;
		case SVG_DOM_EVT_ACTIVATE: GF_LSR_WRITE_INT(lsr, 1, 6, "event"); break;
		case SVG_DOM_EVT_BEGIN: GF_LSR_WRITE_INT(lsr, 2, 6, "event"); break;
		case SVG_DOM_EVT_CLICK: GF_LSR_WRITE_INT(lsr, 3, 6, "event"); break;
		case SVG_DOM_EVT_END: GF_LSR_WRITE_INT(lsr, 4, 6, "event"); break;
		case SVG_DOM_EVT_ERROR: GF_LSR_WRITE_INT(lsr, 5, 6, "event"); break;
		case SVG_DOM_EVT_FOCUSIN: GF_LSR_WRITE_INT(lsr, 6, 6, "event"); break;
		case SVG_DOM_EVT_FOCUSOUT: GF_LSR_WRITE_INT(lsr, 7, 6, "event"); break;
		case SVG_DOM_EVT_KEYDOWN: GF_LSR_WRITE_INT(lsr, 8, 6, "event"); break;
		case SVG_DOM_EVT_KEYPRESS: GF_LSR_WRITE_INT(lsr, 9, 6, "event"); break;
		case SVG_DOM_EVT_KEYUP: GF_LSR_WRITE_INT(lsr, 10, 6, "event"); break;
		case SVG_DOM_EVT_LOAD: GF_LSR_WRITE_INT(lsr, 11, 6, "event"); break;
		case SVG_DOM_EVT_LONGKEYPRESS: GF_LSR_WRITE_INT(lsr, 12, 6, "event"); break;
		case SVG_DOM_EVT_MOUSEDOWN: GF_LSR_WRITE_INT(lsr, 13, 6, "event"); break;
		case SVG_DOM_EVT_MOUSEOUT: GF_LSR_WRITE_INT(lsr, 14, 6, "event"); break;
		case SVG_DOM_EVT_MOUSEOVER: GF_LSR_WRITE_INT(lsr, 15, 6, "event"); break;
		case SVG_DOM_EVT_MOUSEUP: GF_LSR_WRITE_INT(lsr, 16, 6, "event"); break;
		case SVG_DOM_EVT_REPEAT: GF_LSR_WRITE_INT(lsr, 17, 6, "event"); break;
		case SVG_DOM_EVT_RESIZE: GF_LSR_WRITE_INT(lsr, 18, 6, "event"); break;
		case SVG_DOM_EVT_SCROLL: GF_LSR_WRITE_INT(lsr, 19, 6, "event"); break;
		case SVG_DOM_EVT_TEXTINPUT: GF_LSR_WRITE_INT(lsr, 20, 6, "event"); break;
		case SVG_DOM_EVT_UNLOAD: GF_LSR_WRITE_INT(lsr, 21, 6, "event"); break;
		case SVG_DOM_EVT_ZOOM: GF_LSR_WRITE_INT(lsr, 22, 6, "event"); break;
		default:
			fprintf(stdout, "Unsupported LASER event\n");
			break;
		}
	}
}


static void lsr_write_a(GF_LASeRCodec *lsr, SVGaElement *a)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)a) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, a->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) a);
	lsr_write_rare(lsr, (GF_Node *) a, (GF_Node *) clone);
	lsr_write_fill(lsr, (SVGElement *) a, clone);
	lsr_write_line_increment(lsr, (SVGElement *) a, clone);
	lsr_write_stroke(lsr, (SVGElement *) a, clone);
	GF_LSR_WRITE_INT(lsr, a->core->eRR, 1, "core->eRR");
	GF_LSR_WRITE_INT(lsr, (a->target!=NULL) ? 1 : 0, 1, "hasTarget");
	if (a->target) lsr_write_byte_align_string(lsr, a->target, "target");
	lsr_write_href(lsr, & a->xlink->href);

	lsr_write_any_attribute(lsr, (GF_Node *) a, clone);
	lsr_write_group_content(lsr, (SVGElement *) a);
	/*and destroy proto*/
	gf_node_unregister((GF_Node *)clone, NULL);
}

static void lsr_write_animate(GF_LASeRCodec *lsr, SVGanimateElement *animate)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)animate) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, animate->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) animate);
	lsr_write_rare(lsr, (GF_Node *) animate, (GF_Node *) clone);
	lsr_write_accumulate(lsr, animate->anim->accumulate);
	lsr_write_additive(lsr, animate->anim->additive);
	lsr_write_anim_value(lsr, &animate->anim->by, "_4_by");
	lsr_write_calc_mode(lsr, animate->anim->calcMode);
	lsr_write_anim_value(lsr, &animate->anim->from, "_4_from");
	lsr_write_fraction_12(lsr, animate->anim->keySplines, "_4_keySplines");
	lsr_write_fraction_12(lsr, animate->anim->keyTimes, "_4_keyTimes");
	lsr_write_anim_values(lsr, &animate->anim->values, "_4_values");
	lsr_write_animatable(lsr, &animate->anim->attributeName, (SVGElement *)animate, "_5_attributeName");
	lsr_write_time(lsr, animate->timing->begin, "_5_begin");
	lsr_write_duration(lsr, &animate->timing->dur, "_5_dur");
	/*TODO lsr:enabled not present in our code*/
	GF_LSR_WRITE_INT(lsr, 1/*animate->enabled*/, 1, "enabled");
	lsr_write_anim_fill(lsr, animate->timing->fill, "_5_fill");
	lsr_write_anim_repeat(lsr, &animate->timing->repeatCount, "repeatCount");
	lsr_write_duration(lsr, &animate->timing->repeatDur, "_5_repeatDur");
	lsr_write_anim_restart(lsr, animate->timing->restart, "_5_restart");
	lsr_write_anim_value(lsr, &animate->anim->to, "_5_to");

	lsr_write_href(lsr, & animate->xlink->href);
	lsr_write_any_attribute(lsr, (GF_Node *) animate, clone);
	lsr_write_group_content(lsr, (SVGElement *) animate);
	/*and destroy proto*/
	gf_node_unregister((GF_Node *)clone, NULL);
}


static void lsr_write_animateMotion(GF_LASeRCodec *lsr, SVGanimateMotionElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_accumulate(lsr, elt->anim->accumulate);
	lsr_write_additive(lsr, elt->anim->additive);
	lsr_write_anim_value(lsr, &elt->anim->by, "_4_by");
	lsr_write_calc_mode(lsr, elt->anim->calcMode);
	lsr_write_anim_value(lsr, &elt->anim->from, "_4_from");
	lsr_write_fraction_12(lsr, elt->anim->keySplines, "_4_keySplines");
	lsr_write_fraction_12(lsr, elt->anim->keyTimes, "_4_keyTimes");
	lsr_write_anim_values(lsr, &elt->anim->values, "_4_values");
//	lsr_write_animatable(lsr, &elt->anim->attributeName, (SVGElement *)elt, "_5_attributeName");
	lsr_write_time(lsr, elt->timing->begin, "_5_begin");
	lsr_write_duration(lsr, &elt->timing->dur, "_5_dur");
	/*TODO lsr:enabled not present in our code*/
	GF_LSR_WRITE_INT(lsr, 1/*elt->enabled*/, 1, "enabled");
	lsr_write_anim_fill(lsr, elt->timing->fill, "_5_fill");
	lsr_write_anim_repeat(lsr, &elt->timing->repeatCount, "_5_repeatCount");
	lsr_write_duration(lsr, &elt->timing->repeatDur, "_5_repeatDur");
	lsr_write_anim_restart(lsr, elt->timing->restart, "_5_restart");
	lsr_write_anim_value(lsr, &elt->anim->to, "_5_to");

	lsr_write_float_list(lsr, elt->keyPoints, "keyPoints");
	lsr_write_path_type(lsr, &elt->path, "path");
	lsr_write_rotate_type(lsr, elt->rotate, "rotate");

	lsr_write_href(lsr, & elt->xlink->href);
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	/*and destroy proto*/
	gf_node_unregister((GF_Node *)clone, NULL);
}

static void lsr_write_animateTransform(GF_LASeRCodec *lsr, SVGanimateTransformElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_accumulate(lsr, elt->anim->accumulate);
	lsr_write_additive(lsr, elt->anim->additive);
	lsr_write_anim_value(lsr, &elt->anim->by, "_4_by");
	lsr_write_calc_mode(lsr, elt->anim->calcMode);
	lsr_write_anim_value(lsr, &elt->anim->from, "_4_from");
	lsr_write_fraction_12(lsr, elt->anim->keySplines, "_4_keySplines");
	lsr_write_fraction_12(lsr, elt->anim->keyTimes, "_4_keyTimes");
	lsr_write_anim_values(lsr, &elt->anim->values, "_4_values");
	lsr_write_animatable(lsr, &elt->anim->attributeName, (SVGElement *)elt, "_5_attributeName");
	lsr_write_time(lsr, elt->timing->begin, "_5_begin");
	lsr_write_duration(lsr, &elt->timing->dur, "_5_dur");
	/*TODO lsr:enabled not present in our code*/
	GF_LSR_WRITE_INT(lsr, 1/*elt->enabled*/, 1, "enabled");
	lsr_write_anim_fill(lsr, elt->timing->fill, "_5_fill");
	lsr_write_anim_repeat(lsr, &elt->timing->repeatCount, "_5_repeatCount");
	lsr_write_duration(lsr, &elt->timing->repeatDur, "_5_repeatDur");
	lsr_write_anim_restart(lsr, elt->timing->restart, "_5_restart");
	lsr_write_anim_value(lsr, &elt->anim->to, "_5_to");

	/*enumeration rotate{0} scale{1} skewX{2} skewY{3} translate{4}*/
	switch (elt->anim->type) {
	case SVG_TRANSFORM_ROTATE: GF_LSR_WRITE_INT(lsr, 0, 3, "rotscatra"); break;
	case SVG_TRANSFORM_SCALE: GF_LSR_WRITE_INT(lsr, 1, 3, "rotscatra"); break;
	case SVG_TRANSFORM_SKEWX: GF_LSR_WRITE_INT(lsr, 2, 3, "rotscatra"); break;
	case SVG_TRANSFORM_SKEWY: GF_LSR_WRITE_INT(lsr, 3, 3, "rotscatra"); break;
	case SVG_TRANSFORM_TRANSLATE: GF_LSR_WRITE_INT(lsr, 4, 3, "rotscatra"); break;
	}

	lsr_write_href(lsr, & elt->xlink->href);
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	/*and destroy proto*/
	gf_node_unregister((GF_Node *)clone, NULL);
}

static void lsr_write_audio(GF_LASeRCodec *lsr, SVGaudioElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_time(lsr, elt->timing->begin, "_5_begin");
	lsr_write_duration(lsr, &elt->timing->dur, "_5_dur");
	GF_LSR_WRITE_INT(lsr, elt->core->eRR, 1, "core->eRR");
	lsr_write_anim_repeat(lsr, &elt->timing->repeatCount, "_5_repeatCount");
	lsr_write_duration(lsr, &elt->timing->repeatDur, "_5_repeatDur");
	lsr_write_sync_behavior(lsr, elt->sync->syncBehavior, "syncBehavior");
	lsr_write_sync_tolerance(lsr, &elt->sync->syncTolerance, "syncBehavior");
	lsr_write_content_type(lsr, elt->xlink->type, "type");
	lsr_write_href(lsr, & elt->xlink->href);

//	lsr_write_time(lsr, elt->clipBegin, "clipBegin");
	GF_LSR_WRITE_INT(lsr, 0, 1, "clipBegin");
//	lsr_write_time(lsr, elt->clipEnd, "clipEnd");
	GF_LSR_WRITE_INT(lsr, 0, 1, "clipEnd");
//	lsr_write_href(lsr, & elt->syncReference);
	GF_LSR_WRITE_INT(lsr, 0, 1, "hasSyncReference");

	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}
static void lsr_write_circle(GF_LASeRCodec *lsr, SVGcircleElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_fill(lsr, (SVGElement*)elt, clone);
	lsr_write_line_increment(lsr, (SVGElement*)elt, clone);
	lsr_write_stroke(lsr, (SVGElement*)elt, clone);
	lsr_write_coordinate(lsr, elt->cx.value, 1, "cx");
	lsr_write_coordinate(lsr, elt->cy.value, 1, "cy");
	lsr_write_coordinate(lsr, elt->r.value, 0, "r");
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}
static void lsr_write_cursor(GF_LASeRCodec *lsr, SVGElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, ((SVGcircleElement *)elt)->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_coordinate(lsr, /*elt->x*/ 0, 1, "x");
	lsr_write_coordinate(lsr, /*elt->x*/ 0, 1, "y");
	lsr_write_href(lsr, /*& elt->xlink->href*/ NULL);
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}

static void lsr_write_data(GF_LASeRCodec *lsr, SVGdescElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}

static void lsr_write_defs(GF_LASeRCodec *lsr, SVGdefsElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_fill(lsr, (SVGElement*)elt, clone);
	lsr_write_line_increment(lsr, (SVGElement*)elt, clone);
	lsr_write_stroke(lsr, (SVGElement*)elt, clone);
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}
static void lsr_write_ellipse(GF_LASeRCodec *lsr, SVGellipseElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_fill(lsr, (SVGElement*)elt, clone);
	lsr_write_line_increment(lsr, (SVGElement*)elt, clone);
	lsr_write_stroke(lsr, (SVGElement*)elt, clone);
	lsr_write_coordinate(lsr, elt->cx.value, 1, "cx");
	lsr_write_coordinate(lsr, elt->cy.value, 1, "cy");
	lsr_write_coordinate(lsr, elt->rx.value, 0, "rx");
	lsr_write_coordinate(lsr, elt->ry.value, 0, "ry");
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}
static void lsr_write_foreignObject(GF_LASeRCodec *lsr, SVGforeignObjectElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_fill(lsr, (SVGElement*)elt, clone);
	lsr_write_line_increment(lsr, (SVGElement*)elt, clone);
	lsr_write_stroke(lsr, (SVGElement*)elt, clone);
	GF_LSR_WRITE_INT(lsr, elt->core->eRR, 1, "core->eRR");
	lsr_write_coordinate(lsr, elt->height.value, 0, "height");
	lsr_write_coordinate(lsr, elt->width.value, 0, "width");
	lsr_write_coordinate(lsr, elt->x.value, 1, "x");
	lsr_write_coordinate(lsr, elt->y.value, 1, "y");

/*	TODO
	bit(1) opt_group;
	if(opt_group) {
		vluimsbf5 occ1;
		for(int t=0;t<occ1;t++) {
			privateElementContainer child0[[t]];
		}
	}
*/
	GF_LSR_WRITE_INT(lsr, 0, 1, "opt_group");
	gf_node_unregister((GF_Node *)clone, NULL);
}
static void lsr_write_g(GF_LASeRCodec *lsr, SVGgElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_fill(lsr, (SVGElement*)elt, clone);
	lsr_write_line_increment(lsr, (SVGElement*)elt, clone);
	lsr_write_stroke(lsr, (SVGElement*)elt, clone);
	/*TODO choice only ibn LASeR, not in SVG*/
	GF_LSR_WRITE_INT(lsr, 0, 1, "choice");
/*
class choiceClass {
		bit(1) choice;
		switch(choice) {
			case 0:
				bit(8) value;
				break;
			case 1:
					enumeration all{0} clip{1} delta{2} none{3} 								
					bit(2) choice;
				break;
			default:
				break;
			}
}

	*/
	GF_LSR_WRITE_INT(lsr, elt->core->eRR, 1, "core->eRR");
	/*TODO size only in LASeR, not in SVG*/
	GF_LSR_WRITE_INT(lsr, 0, 1, "size");

	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}
static void lsr_write_image(GF_LASeRCodec *lsr, SVGimageElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	GF_LSR_WRITE_INT(lsr, elt->core->eRR, 1, "core->eRR");
	lsr_write_coordinate(lsr, elt->height.value, 1, "height");
	GF_LSR_WRITE_INT(lsr, elt->properties->opacity.type ? 1 : 0, 1, "opacity");
	if (elt->properties->opacity.type) lsr_write_fixed_clamp(lsr, elt->properties->opacity.value, "opacity");
	lsr_write_transform_behavior(lsr, 0, "transformBehavior");
	lsr_write_content_type(lsr, elt->xlink->type, "type");
	lsr_write_coordinate(lsr, elt->width.value, 1, "width");
	lsr_write_coordinate(lsr, elt->x.value, 1, "x");
	lsr_write_coordinate(lsr, elt->y.value, 1, "y");
	lsr_write_href(lsr, &elt->xlink->href);
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}
static void lsr_write_line(GF_LASeRCodec *lsr, SVGlineElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_fill(lsr, (SVGElement *) elt, clone);
	lsr_write_line_increment(lsr, (SVGElement *) elt, clone);
	lsr_write_stroke(lsr, (SVGElement *) elt, clone);

	lsr_write_coordinate(lsr, elt->x1.value, 1, "x1");
	lsr_write_coordinate(lsr, elt->x2.value, 0, "x2");
	lsr_write_coordinate(lsr, elt->y1.value, 1, "y1");
	lsr_write_coordinate(lsr, elt->y2.value, 0, "y2");
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}
static void lsr_write_linearGradient(GF_LASeRCodec *lsr, SVGlinearGradientElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_fill(lsr, (SVGElement *) elt, clone);
	lsr_write_line_increment(lsr, (SVGElement *) elt, clone);
	lsr_write_stroke(lsr, (SVGElement *) elt, clone);
	/*enumeration objectBoundingBox{0} userSpaceOnUse{1}*/
	if (elt->gradientUnits == SVG_GRADIENTUNITS_USER) {
		GF_LSR_WRITE_INT(lsr, 1, 1, "hasGradientUnits");
		GF_LSR_WRITE_INT(lsr, 1, 1, "radientUnits");
	} else {
		GF_LSR_WRITE_INT(lsr, 0, 1, "hasGradientUnits");
	}
	lsr_write_coordinate(lsr, elt->x1.value, 1, "x1");
	lsr_write_coordinate(lsr, elt->x2.value, 1, "x2");
	lsr_write_coordinate(lsr, elt->y1.value, 1, "y1");
	lsr_write_coordinate(lsr, elt->y2.value, 1, "y2");
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}
static void lsr_write_mpath(GF_LASeRCodec *lsr, SVGmpathElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_href(lsr, &elt->xlink->href);
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}
static void lsr_write_path(GF_LASeRCodec *lsr, SVGpathElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_fill(lsr, (SVGElement *) elt, clone);
	lsr_write_line_increment(lsr, (SVGElement *) elt, clone);
	lsr_write_stroke(lsr, (SVGElement *) elt, clone);
	lsr_write_path_type(lsr, &elt->d, "d");
	if (elt->pathLength.value) {
		GF_LSR_WRITE_INT(lsr, 1, 1, "hasPathLength");
		lsr_write_fixed_16_8(lsr, elt->pathLength.value, "pathLength");
	} else {
		GF_LSR_WRITE_INT(lsr, 0, 1, "hasPathLength");
	}
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}
static void lsr_write_polygon(GF_LASeRCodec *lsr, SVGpolygonElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_fill(lsr, (SVGElement *) elt, clone);
	lsr_write_line_increment(lsr, (SVGElement *) elt, clone);
	lsr_write_stroke(lsr, (SVGElement *) elt, clone);
	lsr_write_point_sequence(lsr, elt->points, "points");
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}
static void lsr_write_radialGradient(GF_LASeRCodec *lsr, SVGradialGradientElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_fill(lsr, (SVGElement *) elt, clone);
	lsr_write_line_increment(lsr, (SVGElement *) elt, clone);
	lsr_write_stroke(lsr, (SVGElement *) elt, clone);
	lsr_write_coordinate(lsr, elt->cx.value, 1, "cx");
	lsr_write_coordinate(lsr, elt->cy.value, 1, "cy");

	/*enumeration objectBoundingBox{0} userSpaceOnUse{1}*/
	if (elt->gradientUnits == SVG_GRADIENTUNITS_USER) {
		GF_LSR_WRITE_INT(lsr, 1, 1, "hasGradientUnits");
		GF_LSR_WRITE_INT(lsr, 1, 1, "radientUnits");
	} else {
		GF_LSR_WRITE_INT(lsr, 0, 1, "hasGradientUnits");
	}
	lsr_write_coordinate(lsr, elt->r.value, 1, "r");
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}
static void lsr_write_rect(GF_LASeRCodec *lsr, SVGrectElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_fill(lsr, (SVGElement *) elt, clone);
	lsr_write_line_increment(lsr, (SVGElement *) elt, clone);
	lsr_write_stroke(lsr, (SVGElement *) elt, clone);
	lsr_write_coordinate(lsr, elt->height.value, 0, "height");
	lsr_write_coordinate(lsr, elt->rx.value, 1, "rx");
	lsr_write_coordinate(lsr, elt->ry.value, 1, "ry");
	lsr_write_coordinate(lsr, elt->width.value, 0, "width");
	lsr_write_coordinate(lsr, elt->x.value, 1, "x");
	lsr_write_coordinate(lsr, elt->y.value, 1, "y");
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}
static void lsr_write_script(GF_LASeRCodec *lsr, SVGscriptElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_single_time(lsr, NULL/*&elt->timing->begin*/, "begin");
	GF_LSR_WRITE_INT(lsr, 1/*elt->enabled*/, 1, "enabled");
	GF_LSR_WRITE_INT(lsr, elt->core->eRR, 1, "core->eRR");
	lsr_write_content_type(lsr, elt->xlink->type, "type");
	lsr_write_href(lsr, NULL /*&elt->xlink->href*/);
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_command_list(lsr, NULL, elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}
static void lsr_write_set(GF_LASeRCodec *lsr, SVGsetElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_animatable(lsr, &elt->anim->attributeName, (SVGElement *)elt, "_5_attributeName");
	lsr_write_time(lsr, elt->timing->begin, "_5_begin");
	lsr_write_duration(lsr, &elt->timing->dur, "_5_dur");
	/*TODO lsr:enabled not present in our code*/
	GF_LSR_WRITE_INT(lsr, 1/*elt->enabled*/, 1, "enabled");
	lsr_write_anim_fill(lsr, elt->timing->fill, "_5_fill");
	lsr_write_anim_repeat(lsr, &elt->timing->repeatCount, "_5_repeatCount");
	lsr_write_duration(lsr, &elt->timing->repeatDur, "_5_repeatDur");
	lsr_write_anim_restart(lsr, elt->timing->restart, "_5_restart");
	lsr_write_anim_value(lsr, &elt->anim->to, "_5_to");
	lsr_write_href(lsr, &elt->xlink->href);
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}
static void lsr_write_stop(GF_LASeRCodec *lsr, SVGstopElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_fill(lsr, (SVGElement *) elt, clone);
	lsr_write_line_increment(lsr, (SVGElement *) elt, clone);
	lsr_write_stroke(lsr, (SVGElement *) elt, clone);
	lsr_write_fixed_16_8(lsr, elt->offset.value, "offset");
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}
static void lsr_write_svg(GF_LASeRCodec *lsr, SVGsvgElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_fill(lsr, (SVGElement *) elt, clone);
	lsr_write_line_increment(lsr, (SVGElement *) elt, clone);
	lsr_write_stroke(lsr, (SVGElement *) elt, clone);
	lsr_write_string_attribute(lsr, elt->baseProfile, "baseProfile");
	lsr_write_string_attribute(lsr, elt->contentScriptType, "contentScriptType");
	GF_LSR_WRITE_INT(lsr, elt->core->eRR, 1, "core->eRR");
	lsr_write_value_with_units(lsr, &elt->height, "height");
	if (elt->playbackOrder==SVG_PLAYBACKORDER_FORWARDONLY) {
		GF_LSR_WRITE_INT(lsr, 1, 1, "hasPlaybackOrder");
		GF_LSR_WRITE_INT(lsr, 1, 1, "playbackOrder");
	} else {
		GF_LSR_WRITE_INT(lsr, 0, 1, "hasPlaybackOrder");
	}
	if (elt->preserveAspectRatio.align==SVG_PRESERVEASPECTRATIO_NONE) {
		GF_LSR_WRITE_INT(lsr, 0, 1, "hasPreserveAR");
	} else {
		GF_LSR_WRITE_INT(lsr, 1, 1, "hasPreserveAR");
		switch (elt->preserveAspectRatio.align) {
		case SVG_PRESERVEASPECTRATIO_XMAXYMAX: GF_LSR_WRITE_INT(lsr, (elt->preserveAspectRatio.meetOrSlice==SVG_MEETORSLICE_SLICE) ? 1 : 2, 5, "preserveAR"); break;
		case SVG_PRESERVEASPECTRATIO_XMAXYMID: GF_LSR_WRITE_INT(lsr, (elt->preserveAspectRatio.meetOrSlice==SVG_MEETORSLICE_SLICE) ? 3 : 4, 5, "preserveAR"); break;
		case SVG_PRESERVEASPECTRATIO_XMAXYMIN: GF_LSR_WRITE_INT(lsr, (elt->preserveAspectRatio.meetOrSlice==SVG_MEETORSLICE_SLICE) ? 5 : 6, 5, "preserveAR"); break;
		case SVG_PRESERVEASPECTRATIO_XMIDYMAX: GF_LSR_WRITE_INT(lsr, (elt->preserveAspectRatio.meetOrSlice==SVG_MEETORSLICE_SLICE) ? 7 : 8, 5, "preserveAR"); break;
		case SVG_PRESERVEASPECTRATIO_XMIDYMID: GF_LSR_WRITE_INT(lsr, (elt->preserveAspectRatio.meetOrSlice==SVG_MEETORSLICE_SLICE) ? 9 : 10, 5, "preserveAR"); break;
		case SVG_PRESERVEASPECTRATIO_XMIDYMIN: GF_LSR_WRITE_INT(lsr, (elt->preserveAspectRatio.meetOrSlice==SVG_MEETORSLICE_SLICE) ? 11 : 12, 5, "preserveAR"); break;
		case SVG_PRESERVEASPECTRATIO_XMINYMAX: GF_LSR_WRITE_INT(lsr, (elt->preserveAspectRatio.meetOrSlice==SVG_MEETORSLICE_SLICE) ? 13 : 14, 5, "preserveAR"); break;
		case SVG_PRESERVEASPECTRATIO_XMINYMID: GF_LSR_WRITE_INT(lsr, (elt->preserveAspectRatio.meetOrSlice==SVG_MEETORSLICE_SLICE) ? 15 : 16, 5, "preserveAR"); break;
		case SVG_PRESERVEASPECTRATIO_XMINYMIN: GF_LSR_WRITE_INT(lsr, (elt->preserveAspectRatio.meetOrSlice==SVG_MEETORSLICE_SLICE) ? 17 : 18, 5, "preserveAR"); break;
		default: GF_LSR_WRITE_INT(lsr, 0, 5, "preserveAR"); break;
		}
	}
	if (!elt->sync->syncBehaviorDefault) {
		GF_LSR_WRITE_INT(lsr, 0, 1, "hasSyncBehavior");
	} else {
		GF_LSR_WRITE_INT(lsr, 1, 1, "hasSyncBehavior");
		switch (elt->sync->syncBehaviorDefault) {
		case SMIL_SYNCBEHAVIOR_CANSLIP: GF_LSR_WRITE_INT(lsr, 0, 2, "syncBehavior"); break;
		case SMIL_SYNCBEHAVIOR_INDEPENDENT: GF_LSR_WRITE_INT(lsr, 1, 2, "syncBehavior"); break;
		case SMIL_SYNCBEHAVIOR_LOCKED: GF_LSR_WRITE_INT(lsr, 3, 2, "syncBehavior"); break;
		default: GF_LSR_WRITE_INT(lsr, 0, 2, "syncBehavior"); break;
		}
	}
	if (elt->sync->syncToleranceDefault.type != SMIL_SYNCTOLERANCE_VALUE) {
		GF_LSR_WRITE_INT(lsr, 0, 1, "hasSyncTolerance");
	} else {
		GF_LSR_WRITE_INT(lsr, 1, 1, "hasSyncTolerance");
		GF_LSR_WRITE_INT(lsr, 0, 1, "choice");
	    lsr_write_vluimsbf5(lsr, (u32) (elt->sync->syncToleranceDefault.value*lsr->time_resolution), "value");
	}
	if (elt->timelineBegin == SVG_TIMELINEBEGIN_ONSTART) {
		GF_LSR_WRITE_INT(lsr, 0, 1, "hasTimelineBegin");
	} else {
		GF_LSR_WRITE_INT(lsr, 1, 1, "hasTimelineBegin");
		GF_LSR_WRITE_INT(lsr, 1, 1, "timelineBegin");
	}
	lsr_write_string_attribute(lsr, elt->version, "version");
	if (!elt->viewBox.width && !elt->viewBox.height) {
		GF_LSR_WRITE_INT(lsr, 0, 1, "hasViewBox");
	} else {
		GF_LSR_WRITE_INT(lsr, 1, 1, "hasViewBox");
		lsr_write_fixed_16_8(lsr, elt->viewBox.x, "viewbox.x");
		lsr_write_fixed_16_8(lsr, elt->viewBox.y, "viewbox.y");
		lsr_write_fixed_16_8(lsr, elt->viewBox.width, "viewbox.width");
		lsr_write_fixed_16_8(lsr, elt->viewBox.height, "viewbox.height");
	}
	lsr_write_value_with_units(lsr, &elt->width, "width");
	/*zoom and pan must be encoded in our code...*/
	GF_LSR_WRITE_INT(lsr, 1, 1, "hasZoomAndPan");
	GF_LSR_WRITE_INT(lsr, (elt->zoomAndPan==SVG_ZOOMANDPAN_MAGNIFY) ? 1 : 0, 1, "zoomAndPan");	
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}

static void lsr_write_switch(GF_LASeRCodec *lsr, SVGswitchElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_fill(lsr, (SVGElement*)elt, clone);
	lsr_write_line_increment(lsr, (SVGElement*)elt, clone);
	lsr_write_stroke(lsr, (SVGElement*)elt, clone);
	GF_LSR_WRITE_INT(lsr, elt->core->eRR, 1, "core->eRR");
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}

static void lsr_write_text(GF_LASeRCodec *lsr, SVGtextElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_fill(lsr, (SVGElement*)elt, clone);
	lsr_write_line_increment(lsr, (SVGElement*)elt, clone);
	lsr_write_stroke(lsr, (SVGElement*)elt, clone);

	GF_LSR_WRITE_INT(lsr, elt->editable ? 1 : 0, 1, "editable");
	lsr_write_float_list(lsr, elt->rotate, "rotate");
//	lsr_write_coordinate(lsr, elt->x.value, 1, "x");
	GF_LSR_WRITE_INT(lsr, 0, 1, "hasX");
//	lsr_write_coordinate(lsr, elt->y.value, 1, "y");
	GF_LSR_WRITE_INT(lsr, 0, 1, "hasY");
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	/*TODO this won't work with our current implementation of text in SVG, we MUST move to tspan*/
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}

static void lsr_write_tspan(GF_LASeRCodec *lsr, SVGtspanElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_fill(lsr, (SVGElement*)elt, clone);
	lsr_write_line_increment(lsr, (SVGElement*)elt, clone);
	lsr_write_stroke(lsr, (SVGElement*)elt, clone);
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}

static void lsr_write_use(GF_LASeRCodec *lsr, SVGuseElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_fill(lsr, (SVGElement*)elt, clone);
	lsr_write_line_increment(lsr, (SVGElement*)elt, clone);
	lsr_write_stroke(lsr, (SVGElement*)elt, clone);
	GF_LSR_WRITE_INT(lsr, elt->core->eRR, 1, "core->eRR");
	/*TODO */
	GF_LSR_WRITE_INT(lsr, 0, 1, "hasOverflow");
	lsr_write_coordinate(lsr, elt->x.value, 1, "x");
	lsr_write_coordinate(lsr, elt->y.value, 1, "y");
	lsr_write_href(lsr, &elt->xlink->href);
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}

static void lsr_write_video(GF_LASeRCodec *lsr, SVGvideoElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);
	lsr_write_time(lsr, elt->timing->begin, "_5_begin");
	//lsr_write_duration(lsr, &elt->timing->dur, "_5_dur");
	GF_LSR_WRITE_INT(lsr, elt->core->eRR, 1, "core->eRR");
	lsr_write_coordinate(lsr, elt->height.value, 1, "height");
	/*TODO*/
	GF_LSR_WRITE_INT(lsr, 0, 1, "hasOverlay");
	lsr_write_anim_repeat(lsr, &elt->timing->repeatCount, "_5_repeatCount");
	lsr_write_duration(lsr, &elt->timing->repeatDur, "_5_repeatDur");
	lsr_write_sync_behavior(lsr, elt->sync->syncBehavior, "syncBehavior");
	lsr_write_sync_tolerance(lsr, &elt->sync->syncTolerance, "syncBehavior");
	lsr_write_transform_behavior(lsr, 0, "transformBehavior");
	lsr_write_content_type(lsr, elt->xlink->type, "type");
	lsr_write_coordinate(lsr, elt->width.value, 1, "width");
	lsr_write_coordinate(lsr, elt->x.value, 1, "x");
	lsr_write_coordinate(lsr, elt->y.value, 1, "y");
	lsr_write_href(lsr, & elt->xlink->href);
//	lsr_write_time(lsr, elt->clipBegin, "clipBegin");
	GF_LSR_WRITE_INT(lsr, 0, 1, "clipBegin");
//	lsr_write_time(lsr, elt->clipEnd, "clipEnd");
	GF_LSR_WRITE_INT(lsr, 0, 1, "clipEnd");
//	lsr_write_href(lsr, & elt->syncReference);
	GF_LSR_WRITE_INT(lsr, 0, 1, "hasSyncReference");
	
	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}

static void lsr_write_listener(GF_LASeRCodec *lsr, SVGlistenerElement *elt)
{
	SVGElement *clone;
	clone = gf_svg_new_node(lsr->sg, gf_node_get_tag((GF_Node *)elt) );
	gf_node_register((GF_Node *)clone, NULL);
	lsr_write_string_attribute(lsr, elt->core->_class, "class");
	lsr_write_id(lsr, (GF_Node *) elt);
	lsr_write_rare(lsr, (GF_Node *) elt, (GF_Node *) clone);

	GF_LSR_WRITE_INT(lsr, elt->defaultAction ? 1 : 0, 1, "hasDefaultAction");
	if (elt->defaultAction) GF_LSR_WRITE_INT(lsr, 1, 1, "defaultAction");
	GF_LSR_WRITE_INT(lsr, 1/*elt->endabled*/, 1, "enabled");
	if (elt->event != SVG_DOM_EVT_UNKNOWN) {
		GF_LSR_WRITE_INT(lsr, 1, 1, "hasEvent");
		lsr_write_event_type(lsr, elt->event, NULL);
	} else {
		GF_LSR_WRITE_INT(lsr, 0, 1, "hasEvent");
	}
	if (elt->handler.iri || elt->handler.target) {
		GF_LSR_WRITE_INT(lsr, 1, 1, "hasHandler");
		lsr_write_any_uri(lsr, &elt->handler, "handler");
	} else {
		GF_LSR_WRITE_INT(lsr, 1, 1, "hasHandler");
	}
	/*TODO double check spec here*/
	if (elt->observer.target) {
		GF_LSR_WRITE_INT(lsr, 1, 1, "hasObserver");
		lsr_write_codec_IDREF(lsr, &elt->observer, "observer");
	} else {
		GF_LSR_WRITE_INT(lsr, 0, 1, "hasObserver");
	}
	/*elt->phase is not written*/
	if (elt->propagate) {
		GF_LSR_WRITE_INT(lsr, 1, 1, "hasPropagate");
		GF_LSR_WRITE_INT(lsr, 1, 1, "propagate");
	} else {
		GF_LSR_WRITE_INT(lsr, 0, 1, "hasPropagate");
	}
	/*TODO double check spec here*/
	if (elt->target.target) {
		GF_LSR_WRITE_INT(lsr, 1, 1, "hasTarget");
		lsr_write_codec_IDREF(lsr, &elt->target, "target");
	} else {
		GF_LSR_WRITE_INT(lsr, 0, 1, "hasTarget");
	}
	/*TODO modify our SVG tree for LASeR*/
	GF_LSR_WRITE_INT(lsr, 0, 1, "hasDelay");
	/*TODO modify our SVG tree for LASeR*/
	GF_LSR_WRITE_INT(lsr, 0, 1, "hasTimeAttribute");

	lsr_write_any_attribute(lsr, (GF_Node *) elt, clone);
	lsr_write_group_content(lsr, (SVGElement *) elt);
	gf_node_unregister((GF_Node *)clone, NULL);
}

static void lsr_write_content_model_2(GF_LASeRCodec *lsr, void *node)
{
	u32 tag = gf_node_get_tag(node);
	switch(tag) {
	case TAG_SVG_a: GF_LSR_WRITE_INT(lsr, 0, 6, "ch4"); lsr_write_a(lsr, node); break;
	case TAG_SVG_animate: GF_LSR_WRITE_INT(lsr, 1, 6, "ch4"); lsr_write_animate(lsr, node); break;
	case TAG_SVG_animateColor: GF_LSR_WRITE_INT(lsr, 2, 6, "ch4"); lsr_write_animate(lsr, node); break;
	case TAG_SVG_animateMotion: GF_LSR_WRITE_INT(lsr, 3, 6, "ch4"); lsr_write_animateMotion(lsr, node); break;
	case TAG_SVG_animateTransform: GF_LSR_WRITE_INT(lsr, 4, 6, "ch4"); lsr_write_animateTransform(lsr, node); break;
	case TAG_SVG_audio: GF_LSR_WRITE_INT(lsr, 5, 6, "ch4"); lsr_write_audio(lsr, node); break;
	case TAG_SVG_circle: GF_LSR_WRITE_INT(lsr, 6, 6, "ch4"); lsr_write_circle(lsr, node); break;
#if TODO_LASER_EXTENSIONS	
	case TAG_SVG_cursor: GF_LSR_WRITE_INT(lsr, 7, 6, "ch4"); lsr_write_cursor(lsr, node); break;
#endif
	case TAG_SVG_defs: GF_LSR_WRITE_INT(lsr, 8, 6, "ch4"); lsr_write_defs(lsr, node); break;
	case TAG_SVG_desc: GF_LSR_WRITE_INT(lsr, 9, 6, "ch4"); lsr_write_data(lsr, node); break;
	case TAG_SVG_ellipse: GF_LSR_WRITE_INT(lsr, 10, 6, "ch4"); lsr_write_ellipse(lsr, node); break;
	case TAG_SVG_foreignObject: GF_LSR_WRITE_INT(lsr, 11, 6, "ch4"); lsr_write_foreignObject(lsr, node); break;
	case TAG_SVG_g: GF_LSR_WRITE_INT(lsr, 12, 6, "ch4"); lsr_write_g(lsr, node); break;
	case TAG_SVG_image: GF_LSR_WRITE_INT(lsr, 13, 6, "ch4"); lsr_write_image(lsr, node); break;
	case TAG_SVG_line: GF_LSR_WRITE_INT(lsr, 14, 6, "ch4"); lsr_write_line(lsr, node); break;
	case TAG_SVG_linearGradient: GF_LSR_WRITE_INT(lsr, 15, 6, "ch4"); lsr_write_linearGradient(lsr, node); break;
	case TAG_SVG_metadata: GF_LSR_WRITE_INT(lsr, 16, 6, "ch4"); lsr_write_data(lsr, node); break;
	case TAG_SVG_mpath: GF_LSR_WRITE_INT(lsr, 17, 6, "ch4"); lsr_write_mpath(lsr, node); break;
	case TAG_SVG_path: GF_LSR_WRITE_INT(lsr, 18, 6, "ch4"); lsr_write_path(lsr, node); break;
	case TAG_SVG_polygon: GF_LSR_WRITE_INT(lsr, 19, 6, "ch4"); lsr_write_polygon(lsr, node); break;
	case TAG_SVG_polyline: GF_LSR_WRITE_INT(lsr, 20, 6, "ch4"); lsr_write_polygon(lsr, node); break;
	case TAG_SVG_radialGradient: GF_LSR_WRITE_INT(lsr, 21, 6, "ch4"); lsr_write_radialGradient(lsr, node); break;
	case TAG_SVG_rect: GF_LSR_WRITE_INT(lsr, 22, 6, "ch4"); lsr_write_rect(lsr, node); break;
/*	case 23: samegType
	case 24: samelineType sameline;
	case 25: samepathType samepath;
	case 26: samepathfillType samepathfill;
	case 27: samepolygonType samepolygon;
	case 28: samepolygonfillType samepolygonfill;
	case 29: samepolygonstrokeType samepolygonstroke;
	case 30: samepolygonType samepolyline;
	case 31: samepolygonfillType samepolylinefill;
	case 32: samepolygonstrokeType samepolylinestroke;
	case 33: samerectType samerect;
	case 34: samerectfillType samerectfill;
	case 35: sametextType sametext;
	case 36: sametextfillType sametextfill;
	case 37: sameuseType sameuse;
*/
	case TAG_SVG_script: GF_LSR_WRITE_INT(lsr, 38, 6, "ch4"); lsr_write_script(lsr, node); break;
	case TAG_SVG_set: GF_LSR_WRITE_INT(lsr, 39, 6, "ch4"); lsr_write_set(lsr, node); break;
	case TAG_SVG_stop: GF_LSR_WRITE_INT(lsr, 40, 6, "ch4"); lsr_write_stop(lsr, node); break;
	case TAG_SVG_switch: GF_LSR_WRITE_INT(lsr, 41, 6, "ch4"); lsr_write_switch(lsr, node); break;
	case TAG_SVG_text: GF_LSR_WRITE_INT(lsr, 42, 6, "ch4"); lsr_write_text(lsr, node); break;
	case TAG_SVG_title: GF_LSR_WRITE_INT(lsr, 43, 6, "ch4"); lsr_write_data(lsr, node); break;
	case TAG_SVG_tspan: GF_LSR_WRITE_INT(lsr, 44, 6, "ch4"); lsr_write_tspan(lsr, node); break;
	case TAG_SVG_use: GF_LSR_WRITE_INT(lsr, 45, 6, "ch4"); lsr_write_use(lsr, node); break;
	case TAG_SVG_video: GF_LSR_WRITE_INT(lsr, 46, 6, "ch4"); lsr_write_video(lsr, node); break;
	case TAG_SVG_listener: GF_LSR_WRITE_INT(lsr, 47, 6, "ch4"); lsr_write_listener(lsr, node); break;
#if TODO_LASER_EXTENSIONS	
	case TAG_SVG_privateElement: 
		GF_LSR_WRITE_INT(lsr, 48, 6, "ch4"); 
		lsr_write_privateElement(lsr, node); 
		break;
	case TAG_SVG_textContent:
		GF_LSR_WRITE_INT(lsr, 49, 6, "ch4"); 
		lsr_write_byte_align_string();
		break;
	case TAG_SVG_extendElement: 
		GF_LSR_WRITE_INT(lsr, 50, 6, "ch4"); 
		lsr_write_extend_class(lsr, NULL, 0, "node"); 
		break;
#endif

	default:
		break;
	}
}

static void lsr_write_group_content(GF_LASeRCodec *lsr, SVGElement *elt)
{
	u32 i, count;
	lsr_write_object_content(lsr, elt);
	count = gf_list_count(elt->children);
	if (!count) {
		GF_LSR_WRITE_INT(lsr, 0, 1, "opt_group");
		return;
	}
	GF_LSR_WRITE_INT(lsr, 1, 1, "opt_group");
	lsr_write_vluimsbf5(lsr, count, "occ0");
	for (i=0; i<count; i++) {
		lsr_write_content_model_2(lsr, gf_list_get(elt->children, i));
	}
}

static GF_Err lsr_write_command_list(GF_LASeRCodec *lsr, GF_List *com_list, SVGscriptElement *script)
{
	u32 i, count = 0;
	if (com_list) count += gf_list_count(com_list);
	if (script && script->textContent) count += 1;

	if (script) {
		lsr_write_object_content(lsr, (SVGElement *) script);
		if (!count) {
			GF_LSR_WRITE_INT(lsr, 0, 1, "opt_group");
			return GF_OK;
		}
		GF_LSR_WRITE_INT(lsr, 1, 1, "opt_group");
	}
	lsr_write_vluimsbf5(lsr, count, "occ0");

	if (script && script->textContent) {
		GF_LSR_WRITE_INT(lsr, 10, 4, "ch4");
		lsr_write_byte_align_string(lsr, script->textContent, "textContent");
	}
	if (!com_list) return GF_OK;
	count = gf_list_count(com_list);
	for (i=0; i<count; i++) {
		GF_Command *com = gf_list_get(com_list, i);
		switch (com->tag) {
		case GF_SG_LSR_NEW_SCENE:
			GF_LSR_WRITE_INT(lsr, 4, 4, "ch4");
			lsr_write_any_attribute(lsr, NULL, NULL);
			lsr_write_svg(lsr, (SVGsvgElement *) com->node);
			break;
		case GF_SG_LSR_ADD:
			break;
		case GF_SG_LSR_CLEAN:
			break;
		case GF_SG_LSR_REPLACE:
			break;
		case GF_SG_LSR_DELETE:
			break;
		case GF_SG_LSR_INSERT:
			break;
		case GF_SG_LSR_RESTORE:
			break;
		case GF_SG_LSR_SAVE:
			break;
		case GF_SG_LSR_SEND_EVENT:
			break;
		default:
			return GF_BAD_PARAM;
		}
	}
	return GF_OK;
}

static void lsr_add_color(GF_LASeRCodec *lsr, SVG_Color *color)
{
	lsr->col_table = realloc(lsr->col_table, sizeof(LSRCol)*(lsr->nb_cols+1));
	lsr->col_table[lsr->nb_cols].r = FIX2INT(color->red*lsr->color_scale);
	lsr->col_table[lsr->nb_cols].g = FIX2INT(color->green*lsr->color_scale);
	lsr->col_table[lsr->nb_cols].b = FIX2INT(color->blue*lsr->color_scale);
	lsr->nb_cols++;
}

static void lsr_check_col_index(GF_LASeRCodec *lsr, SVG_Color *color, SVG_Paint *paint)
{
	s32 idx;
	if (color) {
		idx = lsr_get_col_index(lsr, color);
		if (idx==-2) lsr_add_color(lsr, color);
	}
	else if (paint && (paint->type==SVG_PAINT_COLOR) ) {
		idx = lsr_get_col_index(lsr, paint->color);
		if (idx==-2) lsr_add_color(lsr, paint->color);
	}
}

static void lsr_check_font_and_color(GF_LASeRCodec *lsr, SVGElement *elt)
{
	u32 i, count;
	lsr_check_col_index(lsr, NULL, &elt->properties->color);
	lsr_check_col_index(lsr, NULL, &elt->properties->fill);
	lsr_check_col_index(lsr, NULL, &elt->properties->stroke);
	lsr_check_col_index(lsr, NULL, &elt->properties->solid_color);
	lsr_check_col_index(lsr, NULL, &elt->properties->stop_color);
	lsr_check_col_index(lsr, NULL, &elt->properties->viewport_fill);

	if ((elt->properties->font_family.type == SVG_FONTFAMILY_VALUE) && elt->properties->font_family.value) {
		Bool found = 0;
		char *val = elt->properties->font_family.value;
		count = gf_list_count(lsr->font_table);
		for (i=0; i<count; i++) {
			char *ff = gf_list_get(lsr->font_table, i);
			if (!strcmp(ff, val)) {
				found = 1;
				break;
			}
		}
		if (!found) gf_list_add(lsr->font_table, strdup(val));
	}
	count = gf_list_count(elt->children);
	for (i=0; i<count; i++) {
		SVGElement *c = gf_list_get(elt->children, i);
		lsr_check_font_and_color(lsr, c);
	}
}

static GF_Err lsr_write_laser_unit(GF_LASeRCodec *lsr, GF_List *com_list, Bool reset_encoding_context)
{
	u32 i, count, prev_col_count, prev_font_count;

	/*laser unit header*/
	if (!com_list) {
		if (gf_sg_get_root_node(lsr->sg) == NULL) return GF_BAD_PARAM;
		/*RAP generation, force reset encoding context*/
		GF_LSR_WRITE_INT(lsr, 1, 1, "resetEncodingContext");
	} else {
		GF_LSR_WRITE_INT(lsr, reset_encoding_context ? 1 : 0, 1, "resetEncodingContext");
	}
	GF_LSR_WRITE_INT(lsr, 0, 1, "opt_group");
	/*if (opt_group)  codec_extension ext; */

	/*codecInitialisations*/

	/*clean all tables*/
	if (reset_encoding_context) {
		lsr->nb_cols = 0;
		if (lsr->col_table) free(lsr->col_table);
		lsr->col_table = NULL;
		while (gf_list_count(lsr->font_table)) {
			char *ft = gf_list_last(lsr->font_table);
			free(ft);
			gf_list_rem_last(lsr->font_table);
		}
	}

	prev_col_count = lsr->nb_cols;
	prev_font_count = gf_list_count(lsr->font_table);
	/*RAP generation, send all fonts and colors*/
	if (!com_list) prev_col_count = prev_font_count = 0;
	else {
		/*process all colors and fonts*/
		count = gf_list_count(com_list);
		for (i=0; i<count; i++) {
			GF_Command *com = gf_list_get(com_list, i);
			if (gf_list_count(com->command_fields)) {
			} else if (com->node && (com->tag!=GF_SG_LSR_DELETE) ) {
				lsr_check_font_and_color(lsr, (SVGElement *)com->node);
			}
		}
	}
	/*codec initialization*/
	GF_LSR_WRITE_INT(lsr, 0, 1, "anyXMLInitialisation");
	if (prev_col_count == lsr->nb_cols) {
		GF_LSR_WRITE_INT(lsr, 0, 1, "colorInitialisation");
	} else {
		GF_LSR_WRITE_INT(lsr, 1, 1, "colorInitialisation");
		lsr_write_vluimsbf5(lsr, lsr->nb_cols - prev_col_count, "count");
		for (i=prev_col_count; i<lsr->nb_cols; i++) {
			GF_LSR_WRITE_INT(lsr, lsr->col_table[i].r, lsr->info->cfg.colorComponentBits, "red");
			GF_LSR_WRITE_INT(lsr, lsr->col_table[i].g, lsr->info->cfg.colorComponentBits, "green");
			GF_LSR_WRITE_INT(lsr, lsr->col_table[i].b, lsr->info->cfg.colorComponentBits, "blue");
		}
	}
	lsr->colorIndexBits = gf_get_bit_size(lsr->nb_cols);
	GF_LSR_WRITE_INT(lsr, 0, 1, "extendedInitialisation");
	count = gf_list_count(lsr->font_table);
	if (prev_font_count == count) {
		GF_LSR_WRITE_INT(lsr, 0, 1, "fontInitialisation");
	} else {
		GF_LSR_WRITE_INT(lsr, 1, 1, "fontInitialisation");
		lsr_write_vluimsbf5(lsr, count - prev_font_count, "count");
		for (i=prev_font_count; i<count; i++) {
			char *ft = gf_list_get(lsr->font_table, i);
			lsr_write_byte_align_string(lsr, ft, "font");
		}
	}
	lsr->fontIndexBits = gf_get_bit_size(count);
	GF_LSR_WRITE_INT(lsr, 0, 1, "privateDataIdentifierInitialisation");

	/*RAP generation, encode NewScene with root node*/
	if (!com_list) {
		lsr_write_vluimsbf5(lsr, 1, "occ0");
		GF_LSR_WRITE_INT(lsr, 4, 4, "ch4");
		lsr_write_any_attribute(lsr, NULL, NULL);
		lsr_write_svg(lsr, (SVGsvgElement *) gf_sg_get_root_node(lsr->sg) );
		return GF_OK;
	}
	return lsr_write_command_list(lsr, com_list, NULL);
}


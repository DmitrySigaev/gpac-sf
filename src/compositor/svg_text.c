/*
 *			GPAC - Multimedia Framework C SDK
 *
 *			Copyright (c) Cyril Concolato 2004
 *					All rights reserved
 *
 *  This file is part of GPAC / Scene Compositor sub-project
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

#include <gpac/utf.h>

#ifndef GPAC_DISABLE_SVG

#include "visual_manager.h"
#include "nodes_stacks.h"

typedef struct 
{
	Drawable *drawable;
	Fixed prev_size;
	u32 prev_flags;
	u32 prev_anchor;
	GF_List *spans;
	GF_Rect bounds;
} SVG_TextStack;

static void svg_reset_text_stack(SVG_TextStack *st)
{
	while (gf_list_count(st->spans)) {
		GF_TextSpan *span = gf_list_get(st->spans, 0);
		gf_list_rem(st->spans, 0);
		gf_font_manager_delete_span(NULL, span);
	}
}

static void svg_finalize_sort(DrawableContext *ctx, SVG_TextStack *st, GF_TraverseState * tr_state)
{
#ifndef GPAC_DISABLE_3D
	if (tr_state->visual->type_3d) {
		gf_font_spans_draw_3d(st->spans, tr_state, &ctx->aspect, 0, 0);

		drawable_check_focus_highlight(ctx->drawable->node, tr_state, &st->bounds);
		ctx->drawable = NULL;
		return;
	} 
#endif
	/*if text selection mode, we must force redraw of the entire text span because we don't
	if glyphs have been (un)selected*/
	if (!tr_state->direct_draw && 
		/*text selection on*/
		(tr_state->visual->compositor->text_selection 
		/*text sel release*/
		|| (tr_state->visual->compositor->store_text_state==GF_SC_TSEL_RELEASED)) 
	) {
		GF_TextSpan *span;
		u32 i = 0;
		Bool unselect = (tr_state->visual->compositor->store_text_state==GF_SC_TSEL_RELEASED) ? 1 : 0;
		while ((span = gf_list_enum(st->spans, &i))) {
			if (span->flags & GF_TEXT_SPAN_SELECTED) {
				if (unselect) span->flags &= ~GF_TEXT_SPAN_SELECTED;
				ctx->flags |= CTX_APP_DIRTY;
			}
		}
	}
	drawable_finalize_sort(ctx, tr_state, &st->bounds);
}

/*@styles indicates font styles (PLAIN, BOLD, ITALIC, BOLDITALIC and UNDERLINED, STRIKEOUT)*/
static u32 svg_get_font_styles(GF_TraverseState * tr_state)
{
	u32 styles = 0;
	switch(*tr_state->svg_props->font_style) {
	case SVG_FONTSTYLE_ITALIC:
		styles = GF_FONT_ITALIC;
		break;
	case SVG_FONTSTYLE_OBLIQUE:
		styles = GF_FONT_OBLIQUE;
		break;
	}
	if (*tr_state->svg_props->font_variant==SVG_FONTVARIANT_SMALLCAPS) 
		styles |= GF_FONT_SMALLCAPS;

	switch(*tr_state->svg_props->font_weight) {
	case SVG_FONTWEIGHT_100: styles |= GF_FONT_WEIGHT_100; break;
	case SVG_FONTWEIGHT_LIGHTER: styles |= GF_FONT_WEIGHT_LIGHTER; break;
	case SVG_FONTWEIGHT_200: styles |= GF_FONT_WEIGHT_200; break;
	case SVG_FONTWEIGHT_300: styles |= GF_FONT_WEIGHT_300; break;
	case SVG_FONTWEIGHT_400: styles |= GF_FONT_WEIGHT_400; break;
	case SVG_FONTWEIGHT_NORMAL: styles |= GF_FONT_WEIGHT_NORMAL; break;
	case SVG_FONTWEIGHT_500: styles |= GF_FONT_WEIGHT_500; break;
	case SVG_FONTWEIGHT_600: styles |= GF_FONT_WEIGHT_600; break;
	case SVG_FONTWEIGHT_700: styles |= GF_FONT_WEIGHT_700; break;
	case SVG_FONTWEIGHT_BOLD: styles |= GF_FONT_WEIGHT_BOLD; break;
	case SVG_FONTWEIGHT_800: styles |= GF_FONT_WEIGHT_800; break;
	case SVG_FONTWEIGHT_900: styles |= GF_FONT_WEIGHT_900; break;
	case SVG_FONTWEIGHT_BOLDER: styles |= GF_FONT_WEIGHT_BOLDER; break;
	}

	return styles;
}

static GF_Font *svg_set_font(GF_TraverseState * tr_state, GF_FontManager *fm)
{
	GF_Font *font = NULL;
	char *a_font;
	char *fonts[50];
	u32 nb_fonts = 0;

	u32 styles = svg_get_font_styles(tr_state);

	a_font = tr_state->svg_props->font_family->value;
	while (a_font && !font) {
		char *sep;
		while (strchr("\t\r\n ", a_font[0])) a_font++;

		sep = strchr(a_font, ',');
		if (sep) sep[0] = 0;

		if (a_font[0] == '\'') {
			char *sep_end = strchr(a_font+1, '\'');
			if (sep_end) sep_end[0] = 0;
			a_font++;
//			font = gf_font_manager_set_font(fm, &a_font, 1, styles);
			fonts[nb_fonts] = strdup(a_font);
			nb_fonts++;
			if (sep_end) sep_end[0] = '\'';
		} else {
			u32 skip, len = strlen(a_font)-1;
			skip = 0;
			while (a_font[len-skip] == ' ') skip++;
			if (skip) a_font[len-skip+1] = 0;
//			font = gf_font_manager_set_font(fm, &a_font, 1, styles);
			fonts[nb_fonts] = strdup(a_font);
			nb_fonts++;
			if (skip) a_font[len-skip] = ' ';
		}
		
		if (sep) {
			sep[0] = ',';
			a_font = sep+1;
		} else {
			a_font = NULL;
		}
		if (nb_fonts==50) break;
	}
	font = gf_font_manager_set_font(fm, fonts, nb_fonts, styles);
	while (nb_fonts) {
		free(fonts[nb_fonts-1]);
		nb_fonts--;
	}
	return font;
}

static void svg_apply_text_anchor(GF_TraverseState * tr_state, Fixed *width)
{
	if (!tr_state->svg_props->text_anchor) {
		*width = 0;
		return;
	}
	switch(*tr_state->svg_props->text_anchor) {
	case SVG_TEXTANCHOR_MIDDLE:
		*width = -(*width)/2;
		break;
	case SVG_TEXTANCHOR_END:
		*width = -(*width);
		break;
	case SVG_TEXTANCHOR_START:
	default:
		*width = 0;
		break;
	}
}

static GF_TextSpan *svg_get_text_span(GF_FontManager *fm, GF_Font *font, Fixed font_size, Bool x_offsets, Bool y_offsets, Bool preserve, char *textContent, const char *lang, GF_TraverseState *tr_state) 
{
	GF_TextSpan *span = NULL;
	char *dup_text;
	u32 i, j, len;
	char prev;

	len = strlen(textContent);
	dup_text = malloc(len+1);
	prev = tr_state->last_char_was_space ? ' ' : 0;
	for (i = 0, j = 0; i < len; i++) {
		if (textContent[i] == ' ') {
			if (prev == ' ' && !preserve) { 
				/* ignore space */
			} else {
				dup_text[j] = textContent[i];
				prev = dup_text[j];
				j++;
			}
		} else if ((textContent[i] == '\n') ||
				   (textContent[i] == '\r') ||
				   (textContent[i] == '\t')
		) {
			if (prev == ' ' && !preserve) { 
				/* ignore space */
			} else {
				dup_text[j] = ' ';
				prev = dup_text[j];
				j++;
			}
		} else if (
			(((u8) textContent[i] == 0xc2) && ((u8) textContent[i+1] == 0xa0)) 
		) {
			if (prev == ' ' && !preserve) { 
				/* ignore space */
			} else {
				dup_text[j] = ' ';
				prev = dup_text[j];
				j++;
			}
			i++;
		} else {
			dup_text[j] = textContent[i];
			prev = dup_text[j];
			j++;
		}
	}
	dup_text[j] = 0;
	tr_state->last_char_was_space = (j && (dup_text[j-1]==' ')) ? 1 : 0;
	/*SVG text is fliped by default (text y-axis is the inverse of SVG y-axis*/
	span = gf_font_manager_create_span(fm, font, dup_text, font_size, x_offsets, y_offsets, lang, 1, 0);
	free(dup_text);
	if (span) span->flags |= GF_TEXT_SPAN_HORIZONTAL;
	return span;
}



typedef struct
{
	GF_TextSpan *span;
	u32 first_glyph, last_glyph;
} textArea_state;

static void svg_text_area_reset_state(GF_TraverseState *tr_state)
{
	u32 i, count;
	count = gf_list_count(tr_state->x_anchors);
	for (i=0; i<count; i++) {
		textArea_state *st = gf_list_get(tr_state->x_anchors, i);
		free(st);
	}
	gf_list_reset(tr_state->x_anchors);
}

static void svg_text_area_queue_state(GF_TraverseState *tr_state, GF_TextSpan *span, u32 first_glyph, u32 last_glyph)
{
	textArea_state *st;
	u32 i, count;
	count = gf_list_count(tr_state->x_anchors);
	for (i=0; i<count; i++) {
		textArea_state *st = gf_list_get(tr_state->x_anchors, i);
		if (st->span==span) {
			st->last_glyph = last_glyph;
			return;
		}
	}	
	st = malloc(sizeof(textArea_state));
	st->first_glyph = first_glyph;
	st->last_glyph = last_glyph;
	st->span = span;
	gf_list_add(tr_state->x_anchors, st);
}

static void svg_text_area_apply_diff(GF_TraverseState *tr_state, Fixed diff)
{
	u32 i, count, j;
	count = gf_list_count(tr_state->x_anchors);
	for (i=0; i<count; i++) {
		textArea_state *st = gf_list_get(tr_state->x_anchors, i);

		for (j=st->first_glyph; j<st->last_glyph; j++) {
			st->span->dy[j] += diff;
		}
	}
}

static void svg_traverse_dom_text_area(GF_Node *node, SVGAllAttributes *atts, GF_TraverseState *tr_state, GF_List *spans)
{
	GF_DOMText *dom_text = (GF_DOMText *)node;
	u32 word_start, word_end;
	u32 i, j;
	Fixed line_spacing;
	GF_Font *font;
	GF_FontManager *fm;
	GF_TextSpan *span;

	if (!dom_text->textContent) return;

	fm = tr_state->visual->compositor->font_manager;
	if (!fm) return;

	font = svg_set_font(tr_state, fm);
	if (!font) return;

	span = svg_get_text_span(fm, font, tr_state->svg_props->font_size->value, 1, 1, 0, dom_text->textContent, atts->xml_lang ? *atts->xml_lang : NULL, tr_state);
	if (!span) return;

	/*first run*/
	if (!tr_state->line_spacing) {
		tr_state->line_spacing = gf_mulfix(span->font_size, FLT2FIX(1.0) );
		if (!tr_state->text_end_y) tr_state->text_end_y = tr_state->line_spacing;
	} 
	line_spacing = gf_mulfix(span->font_size, FLT2FIX(1.0) );

	word_start = word_end = 0;
	i = 0;
	/* boucle principale: mot par mot */
	while (i<span->nb_glyphs) {
		Fixed word_size, last_char_size, word_height, h, offset;
		u32 break_glyph = 0;

		word_start = i;
		word_height = word_size = last_char_size = h = 0;
		while (i<span->nb_glyphs) {
			Fixed glyph_size;
			if (span->glyphs[i]) {
				/*look for word boundaries*/
				if ( (span->glyphs[i]->utf_name==' ') || (span->glyphs[i]->utf_name=='-') ) {
					last_char_size = span->glyphs[i]->horiz_advance * span->font_scale;
					i++;
					break;
				}
				glyph_size = span->glyphs[i]->horiz_advance * span->font_scale;
				if (word_size + glyph_size> tr_state->max_length) {
					break_glyph = i;
					i++;
					break;
				}
				word_size += glyph_size;
				h = span->glyphs[i]->vert_advance * span->font_scale;
				if (h>word_height) word_height = h;
			}
			i++;
		}

		if (tr_state->text_end_x + word_size > tr_state->max_length) {
			/* if the word doesn fit on line, escape*/
			if (word_size > tr_state->max_length) {
				word_start=break_glyph;
				break;
			}

			tr_state->text_end_x = 0;
			tr_state->line_spacing = line_spacing;
			svg_text_area_reset_state(tr_state);

			tr_state->text_end_y += (tr_state->svg_props->line_increment->type == SVG_NUMBER_AUTO ? tr_state->line_spacing : tr_state->svg_props->line_increment->value);
			/* out of area, abort processing*/
			if (tr_state->text_end_y > tr_state->max_height) break;
		} else {
			/* first word is too high for the area*/
			if (tr_state->text_end_x == 0 && (tr_state->text_end_y+h > tr_state->max_height) )
				break;

			/* stay on current line*/
			if (line_spacing > tr_state->line_spacing) {
				svg_text_area_apply_diff(tr_state, line_spacing - tr_state->line_spacing);
				tr_state->text_end_y -= tr_state->line_spacing;
				tr_state->text_end_y += line_spacing;
				tr_state->line_spacing = line_spacing;
			}

		}
		word_size += last_char_size;

		offset = tr_state->base_x + tr_state->text_end_x;
		for (j=word_start; j<i; j++) {
			span->dx[j] = offset;
			span->dy[j] = tr_state->base_y + tr_state->text_end_y;
			offset += (span->glyphs[j] ? span->glyphs[j]->horiz_advance : font->max_advance_h) * span->font_scale;
		}
		tr_state->text_end_x += word_size;
//		if (tr_state->y_step < word_height) tr_state->y_step = word_height;

		svg_text_area_queue_state(tr_state, span, word_start, i);
		word_start = i;
	}
	span->nb_glyphs = word_start;
	/*add span path to list of spans*/
	gf_list_add(spans, span);
}

static void get_domtext_width(GF_Node *node, SVGAllAttributes *atts, GF_TraverseState *tr_state)
{
	u32 i;
	GF_Font *font;
	Fixed block_width, *entry;
	GF_FontManager *fm;
	GF_TextSpan *span;
	GF_DOMText *dom_text = (GF_DOMText *)node;

	if (!dom_text->textContent) return;

	fm = tr_state->visual->compositor->font_manager;
	if (!fm) return;

	font = svg_set_font(tr_state, fm);
	if (!font) return;

	span = svg_get_text_span(fm, font, tr_state->svg_props->font_size->value, (tr_state->count_x>1), (tr_state->count_y>1), 0, dom_text->textContent, atts->xml_lang ? *atts->xml_lang : NULL, tr_state);
	if (!span) return;

	i=0;
	//count_x, _y: number of x- (y-) position of characters to come in the text flow
	while ( (i<span->nb_glyphs)
		&& ( (tr_state->count_x>1) || (tr_state->count_y>1) )
	) {
		block_width = (span->glyphs[i] ? span->glyphs[i]->horiz_advance : font->max_advance_h) * span->font_scale;

		//store width in tr_state->x_anchors
		entry = (Fixed*)malloc(sizeof(Fixed));
		*entry = block_width;
		gf_list_add(tr_state->x_anchors, entry);

		if (tr_state->count_x>0) tr_state->count_x--;
		if (tr_state->count_y>0) tr_state->count_y--;
		i++;
	}

	//chars are taken one by one while there are indicated positions, then remaining chars are treated as a block
	if (i<span->nb_glyphs) {
		block_width = 0;
		while (i<span->nb_glyphs) {
			block_width += (span->glyphs[i] ? span->glyphs[i]->horiz_advance : font->max_advance_h) * span->font_scale;
			i++;
		}
		//if last indicated position, create a new item
		if ((tr_state->count_x==1)||(tr_state->count_y==1)
			|| !gf_list_count(tr_state->x_anchors) ) {
			entry = (Fixed*)malloc(sizeof(Fixed));
			*entry = block_width;
			gf_list_add(tr_state->x_anchors, entry);
		} else { // (count_x == 0 && count_y == 0) otherwise increment last one
			Fixed *prec_lw=gf_list_last(tr_state->x_anchors);
			(*prec_lw) += block_width;
		}
		//force counters to 0 for next spans/DOM texts
		if (tr_state->count_x==1) tr_state->count_x = 0;
		if (tr_state->count_y==1) tr_state->count_y = 0;
	}
	gf_font_manager_delete_span(fm, span);
}

static void get_tspan_width(GF_Node *node, void *rs)
{
	SVGPropertiesPointers backup_props;
	u32 backup_flags;
	GF_TraverseState *tr_state = (GF_TraverseState *)rs;
	SVG_Element *tspan = (SVG_Element *)node;
	SVGAllAttributes atts;
	GF_ChildNodeItem *child;

	gf_svg_flatten_attributes(tspan, &atts);
	if (!compositor_svg_traverse_base(node, &atts, tr_state, &backup_props, &backup_flags))
		return;

	child = ((GF_ParentNode *) tspan)->children;
	while (child) {
		switch  (gf_node_get_tag(child->node)) {
		case TAG_DOMText:
			get_domtext_width(child->node, &atts, tr_state); 
			break;
		case TAG_SVG_tspan:
			get_tspan_width(child->node, tr_state); 
			break;
		default:
			break;
		}
		child=child->next;
	}

	memcpy(tr_state->svg_props, &backup_props, sizeof(SVGPropertiesPointers));
	tr_state->svg_flags = backup_flags;
}

void svg_traverse_domtext(GF_Node *node, SVGAllAttributes *atts, GF_TraverseState *tr_state, GF_List *spans, GF_Node *anchor_node)
{
	GF_DOMText *dom_text = (GF_DOMText *)node;
	Fixed x, y;
	u32 i;
	Fixed x_anchor, *ptr;
	GF_Font *font;
	Fixed block_width;
	GF_FontManager *fm;
	GF_TextSpan *span;

	if (!dom_text->textContent) return;

	if (tr_state->in_svg_text_area) {
		svg_traverse_dom_text_area(node, atts, tr_state, spans);
		return;
	}

	fm = tr_state->visual->compositor->font_manager;
	if (!fm) return;

	font = svg_set_font(tr_state, fm);
	if (!font) return;

	span = svg_get_text_span(fm, font, tr_state->svg_props->font_size->value, (tr_state->count_x>1), (tr_state->count_y>1), 0, dom_text->textContent, atts->xml_lang ? *atts->xml_lang : NULL, tr_state);
	if (!span) return;

	i=0;
	/*
	if character position is given in (x, y) attributes, use it. 
	Otherwise add text at tr_state->text_end_x.
	*/		
	while ((i<span->nb_glyphs)
		&& ( (tr_state->count_x>1) || (tr_state->count_y>1) )
	) {
		//get x and y positions
		if (tr_state->count_x==0) {
			x = tr_state->text_end_x;
		} else {
			SVG_Coordinate *xc = (SVG_Coordinate *) gf_list_get(*tr_state->text_x, tr_state->chunk_index);
			x = xc->value;
			(tr_state->count_x)--;
		}
		if (tr_state->count_y==0) {
			y = tr_state->text_end_y;
		} else {
			SVG_Coordinate *yc = (SVG_Coordinate *) gf_list_get(*tr_state->text_y, tr_state->chunk_index);
			y = yc->value;
			(tr_state->count_y)--;
		}
		

		/*apply x-anchor*/
		ptr = (Fixed *)gf_list_get(tr_state->x_anchors, tr_state->chunk_index);
		x_anchor = ptr ? *ptr : 0;
		if (span->dx) span->dx[i] = x_anchor + x;
		else if (!i) span->off_x = x_anchor + x;
		if (span->dy) span->dy[i] = y;
		else span->off_y = y;

		/*update last glyph position*/
		block_width = (span->glyphs[i] ? span->glyphs[i]->horiz_advance : font->max_advance_h) * span->font_scale;
		tr_state->text_end_x = x+block_width;
		tr_state->text_end_y = y;
		(tr_state->chunk_index)++;
		i++;
	}

	/* no more positions, add remaining glyphs as a block*/
	if (i<span->nb_glyphs) {
		Fixed offset;
		if ((tr_state->count_x==1) && tr_state->text_x) {
			SVG_Coordinate *xc = (SVG_Coordinate *) gf_list_get(*tr_state->text_x, tr_state->chunk_index);
			tr_state->text_end_x = xc->value;
			(tr_state->count_x)--;
		}
		if ((tr_state->count_y==1) && tr_state->text_y) {
			SVG_Coordinate *yc = (SVG_Coordinate *) gf_list_get(*tr_state->text_y, tr_state->chunk_index);
			tr_state->text_end_y = yc->value;
			(tr_state->count_y)--;
		}
		x = tr_state->text_end_x;
		y = tr_state->text_end_y;

		/*apply x anchor*/
		ptr = (Fixed *)gf_list_get(tr_state->x_anchors, tr_state->chunk_index);
		x_anchor = ptr ? *ptr : 0;

		offset = x_anchor + x - (span->dx ? span->dx[i] : span->off_x);

		if (!span->dx) span->off_x = x_anchor + x;
		if (!span->dy) span->off_y = y;

		block_width = 0;
		while (i<span->nb_glyphs) {
			if (span->dx) span->dx[i] = offset + block_width;
			if (span->dy) span->dy[i] = y;
			block_width += (span->glyphs[i] ? span->glyphs[i]->horiz_advance : font->max_advance_h) * span->font_scale;

			i++;
		}
		tr_state->text_end_x += block_width;
	}

	/*add span path to list of spans*/
	gf_list_add(spans, span);
	span->anchor = anchor_node;
}


static void svg_compute_text_width(GF_Node *node, SVGAllAttributes *atts, GF_TraverseState *tr_state )
{
	GF_ChildNodeItem *child;
	Bool is_switch = 0;
	/*compute length of all text blocks*/
	switch  (gf_node_get_tag(node)) {
	case TAG_DOMText:
		get_domtext_width(node, atts, tr_state); 
		break;
	case TAG_SVG_tspan:
		get_tspan_width(node, tr_state); 
		break;
	case TAG_SVG_switch:
		is_switch = 1;
	case TAG_SVG_a:
		child = ((GF_ParentNode *)node)->children;
		while (child) {
			if (is_switch) {
				SVGAllAttributes a_atts;
				gf_svg_flatten_attributes((SVG_Element*)child->node, &a_atts);
				if (compositor_svg_evaluate_conditional(tr_state->visual->compositor, &a_atts)) {
					svg_compute_text_width(child->node, atts, tr_state);
					break;
				}
			} else {
				svg_compute_text_width(child->node, atts, tr_state);
			}
			child = child->next;
		}
		break;
	default:
		break;
	}
}

static void svg_traverse_text_block(GF_Node *node, SVGAllAttributes *atts, GF_TraverseState *tr_state, GF_List *spans)
{
	GF_ChildNodeItem *child;
	Bool is_switch = 0;
	switch  (gf_node_get_tag(node)) {
	case TAG_DOMText:
		svg_traverse_domtext(node, atts, tr_state, spans, NULL); 
		break;
	case TAG_SVG_tspan:
		/*mark tspan as dirty to force rebuild*/
		gf_node_dirty_set(node, 0, 0);
		gf_node_traverse(node, tr_state); 
		break;
	case TAG_SVG_switch:
		is_switch = 1;
	case TAG_SVG_a:
		child = ((GF_ParentNode *)node)->children;
		while (child) {
			if (is_switch) {
				SVGAllAttributes a_atts;
				gf_svg_flatten_attributes((SVG_Element*)child->node, &a_atts);
				if (compositor_svg_evaluate_conditional(tr_state->visual->compositor, &a_atts)) {
					svg_traverse_text_block(child->node, atts, tr_state, spans);
					break;
				}
			} else if (gf_node_get_tag(child->node)==TAG_DOMText) {
				svg_traverse_domtext(child->node, atts, tr_state, spans, node); 
			}
			child = child->next;
		}
		break;
	default:
		break;
	}
}

static void svg_text_draw_2d(SVG_TextStack *st, GF_TraverseState *tr_state)
{
	gf_font_spans_draw_2d(st->spans, tr_state, 0, 0, &st->bounds);
}

static void svg_update_bounds(SVG_TextStack *st)
{
	u32 i=0;
	GF_TextSpan *span;
	/*finally compute text bounds*/
	st->bounds.width = st->bounds.height = 0;
	st->bounds.x = st->bounds.y = 0;
	while ( (span = gf_list_enum(st->spans, &i)) ) {
		gf_font_manager_refresh_span_bounds(span);
		gf_rect_union(&st->bounds, &span->bounds);
	}
}


static void svg_traverse_text(GF_Node *node, void *rs, Bool is_destroy)
{
	SVGPropertiesPointers backup_props;
	u32 backup_flags;
	GF_Matrix2D backup_matrix;
	GF_Matrix mx3d;
	GF_ChildNodeItem *child;
	DrawableContext *ctx;
	SVG_TextStack *st = (SVG_TextStack *)gf_node_get_private(node);
	GF_TraverseState *tr_state = (GF_TraverseState *)rs;
	SVG_Element *text = (SVG_Element *)node;
	SVGAllAttributes atts;
	u32 i,imax;
	Fixed * lw;

	if (is_destroy) {
		drawable_del(st->drawable);
		svg_reset_text_stack(st);
		gf_list_del(st->spans);
		free(st);
		return;
	}

	if (tr_state->traversing_mode==TRAVERSE_DRAW_2D) {
		svg_text_draw_2d(st, tr_state);
		return;
	}
	else if (tr_state->traversing_mode==TRAVERSE_GET_TEXT) {
		tr_state->text_parent = node;
		gf_font_spans_get_selection(node, st->spans, tr_state);
		/*and browse children*/
		child = ((GF_ParentNode *) text)->children;
		while (child) {
			switch  (gf_node_get_tag(child->node)) {
			case TAG_SVG_tspan:
				gf_node_traverse(child->node, tr_state); 
				break;
			}
			child = child->next;
		}
		tr_state->text_parent = NULL;
		return;
	}

	gf_svg_flatten_attributes(text, &atts);
	if (!compositor_svg_traverse_base(node, &atts, tr_state, &backup_props, &backup_flags))
		return;

	tr_state->in_svg_text++;
	tr_state->text_parent = node;

	if (tr_state->traversing_mode==TRAVERSE_PICK) {
		if (*tr_state->svg_props->pointer_events!=SVG_POINTEREVENTS_NONE) 
			gf_font_spans_pick(node, st->spans, tr_state, &st->bounds, 1, st->drawable);

		/*and browse children*/
		child = ((GF_ParentNode *) text)->children;
		while (child) {
			switch  (gf_node_get_tag(child->node)) {
			case TAG_SVG_tspan:
				gf_node_traverse(child->node, tr_state); 
				break;
			}
			child = child->next;
		}
		memcpy(tr_state->svg_props, &backup_props, sizeof(SVGPropertiesPointers));
		tr_state->svg_flags = backup_flags;
		tr_state->text_parent = NULL;
		tr_state->in_svg_text--;
		return;
	}
	else if (tr_state->traversing_mode==TRAVERSE_GET_TEXT) {
		gf_font_spans_get_selection(node, st->spans, tr_state);
		memcpy(tr_state->svg_props, &backup_props, sizeof(SVGPropertiesPointers));
		tr_state->svg_flags = backup_flags;
		tr_state->text_parent = NULL;
		tr_state->in_svg_text--;
		return;
	}

	compositor_svg_apply_local_transformation(tr_state, &atts, &backup_matrix, &mx3d);

	if ( (st->prev_size != tr_state->svg_props->font_size->value) || 
		 (st->prev_flags != *tr_state->svg_props->font_style) || 
		 (st->prev_anchor != *tr_state->svg_props->text_anchor) ||
		 (gf_node_dirty_get(node) & (GF_SG_SVG_GEOMETRY_DIRTY | GF_SG_CHILD_DIRTY) ) 
		 || tr_state->visual->compositor->reset_fonts
	) {
		u32 mode;
		child = ((GF_ParentNode *) text)->children;

		svg_reset_text_stack(st);
		tr_state->text_end_x = 0;
		tr_state->text_end_y = 0;

		/*initialize x and y counters - stored at the traverse level for handling tspan & co*/
		if (atts.text_x) tr_state->count_x = gf_list_count(*atts.text_x);
		else tr_state->count_x=0;
		if (atts.text_y) tr_state->count_y = gf_list_count(*atts.text_y);
		else tr_state->count_y=0;

		/*horizontal justifiers container*/
		tr_state->x_anchors = gf_list_new();
		tr_state->last_char_was_space = 0;

		/*compute length of all text blocks*/
		while (child) {
			svg_compute_text_width(child->node, &atts, tr_state);
			child=child->next;
		}

		/*apply justification of all blocks*/
		imax=gf_list_count(tr_state->x_anchors);
		for (i=0;i<imax;i++){
			lw=gf_list_get(tr_state->x_anchors, i);
			svg_apply_text_anchor(tr_state, lw);
		}

		/*re-initialize x and y counters for final compute*/
		if (atts.text_x) tr_state->count_x = gf_list_count(*atts.text_x);
		else tr_state->count_x=0;
		if (atts.text_y) tr_state->count_y = gf_list_count(*atts.text_y);
		else tr_state->count_y=0;
		
		tr_state->chunk_index = 0;

		/*initialize current text position*/
		if (!tr_state->text_end_x){
			SVG_Coordinate *xc = (atts.text_x ? (SVG_Coordinate *) gf_list_get(*atts.text_x, 0) : NULL);
			tr_state->text_end_x = (xc ? xc->value : 0);
		}
		if (!tr_state->text_end_y){
			SVG_Coordinate *yc = (atts.text_y ? (SVG_Coordinate *) gf_list_get(*atts.text_y, 0) : NULL);
			tr_state->text_end_y = (yc ? yc->value : 0);
		}

		/*pass x and y to children*/
		tr_state->text_x = atts.text_x;
		tr_state->text_y = atts.text_y;
		
		drawable_reset_path(st->drawable);
		
		/*switch to bounds mode, and recompute children*/
		mode = tr_state->traversing_mode;
		tr_state->traversing_mode = TRAVERSE_GET_BOUNDS;
		tr_state->last_char_was_space = 0;

		child = ((GF_ParentNode *) text)->children;
		while (child) {
			svg_traverse_text_block(child->node, &atts, tr_state, st->spans);
			child = child->next;
		}
		tr_state->traversing_mode = mode;
		gf_node_dirty_clear(node, 0);
		drawable_mark_modified(st->drawable, tr_state);
		st->prev_size = tr_state->svg_props->font_size->value;
		st->prev_flags = *tr_state->svg_props->font_style;
		st->prev_anchor = *tr_state->svg_props->text_anchor;

		while (gf_list_count(tr_state->x_anchors)) {
			Fixed *f = gf_list_last(tr_state->x_anchors);
			gf_list_rem_last(tr_state->x_anchors);
			free(f);
		}
		gf_list_del(tr_state->x_anchors);
		tr_state->x_anchors = NULL;
	
		svg_update_bounds(st);
	} 

	if (tr_state->traversing_mode == TRAVERSE_GET_BOUNDS) {
		if (!compositor_svg_is_display_off(tr_state->svg_props))
			tr_state->bounds = st->bounds;

	} else if ((tr_state->traversing_mode == TRAVERSE_SORT) 
		&& !compositor_svg_is_display_off(tr_state->svg_props) 
		&& (*(tr_state->svg_props->visibility) != SVG_VISIBILITY_HIDDEN) 
		) {
		ctx = drawable_init_context_svg(st->drawable, tr_state);
		if (ctx) svg_finalize_sort(ctx, st, tr_state);

		/*and browse children*/
		child = ((GF_ParentNode *) text)->children;
		while (child) {
			switch  (gf_node_get_tag(child->node)) {
			case TAG_SVG_tspan:
				gf_node_traverse(child->node, tr_state); 
				break;
			case TAG_SVG_switch:
				gf_node_traverse(child->node, tr_state); 
				break;
			}
			child = child->next;
		}
	}
	tr_state->in_svg_text--;
	tr_state->text_parent = NULL;

	compositor_svg_restore_parent_transformation(tr_state, &backup_matrix, &mx3d);
	memcpy(tr_state->svg_props, &backup_props, sizeof(SVGPropertiesPointers));
	tr_state->svg_flags = backup_flags;
}


void compositor_init_svg_text(GF_Compositor *compositor, GF_Node *node)
{
	SVG_TextStack *stack;
	GF_SAFEALLOC(stack, SVG_TextStack);
	stack->drawable = drawable_new();
	stack->drawable->node = node;
	stack->drawable->flags = DRAWABLE_USE_TRAVERSE_DRAW;
	stack->spans = gf_list_new();
	gf_node_set_private(node, stack);
	gf_node_set_callback_function(node, svg_traverse_text);
}


static void svg_traverse_tspan(GF_Node *node, void *rs, Bool is_destroy)
{	
	SVGPropertiesPointers backup_props;
	u32 backup_flags;
	GF_Matrix2D backup_matrix;
	GF_Matrix mx3d;
	DrawableContext *ctx;
	SVG_TextStack *st = (SVG_TextStack *)gf_node_get_private(node);
	GF_TraverseState *tr_state = (GF_TraverseState *)rs;
	SVG_Element *tspan = (SVG_Element *)node;
	SVGAllAttributes atts;
	GF_ChildNodeItem *child;

	if (is_destroy) {
		drawable_del(st->drawable);
		svg_reset_text_stack(st);
		gf_list_del(st->spans);
		free(st);
		return;
	}
	if (tr_state->traversing_mode==TRAVERSE_DRAW_2D) {
		svg_text_draw_2d(st, tr_state);
		return;
	}
	else if (tr_state->traversing_mode==TRAVERSE_GET_TEXT) {
		gf_font_spans_get_selection(node, st->spans, tr_state);
		return;
	}

	if (!tr_state->in_svg_text && !tr_state->in_svg_text_area) return;

	gf_svg_flatten_attributes(tspan, &atts);
	if (!compositor_svg_traverse_base(node, &atts, tr_state, &backup_props, &backup_flags))
		return;

	if (tr_state->traversing_mode==TRAVERSE_PICK) {
		if (*tr_state->svg_props->pointer_events!=SVG_POINTEREVENTS_NONE) 
			gf_font_spans_pick(node, st->spans, tr_state, &st->bounds, 1, st->drawable);

		memcpy(tr_state->svg_props, &backup_props, sizeof(SVGPropertiesPointers));
		tr_state->svg_flags = backup_flags;
		return;
	}
	
	compositor_svg_apply_local_transformation(tr_state, &atts, &backup_matrix, &mx3d);

	if ( (st->prev_size != tr_state->svg_props->font_size->value) || 
		 (st->prev_flags != *tr_state->svg_props->font_style) || 
		 (st->prev_anchor != *tr_state->svg_props->text_anchor) ||
		 (gf_node_dirty_get(node) & (GF_SG_SVG_GEOMETRY_DIRTY | GF_SG_CHILD_DIRTY) ) 
	) {
		/*switch to bounds mode, and recompute children*/
		u32 mode = tr_state->traversing_mode;
		tr_state->traversing_mode = TRAVERSE_GET_BOUNDS;

		svg_reset_text_stack(st);
		child = ((GF_ParentNode *) tspan)->children;

		while (child) {
			switch  (gf_node_get_tag(child->node)) {
			case TAG_DOMText:
				svg_traverse_domtext(child->node, &atts, tr_state, st->spans, NULL); 
				break;
			case TAG_SVG_tspan:
			case TAG_SVG_switch:
			case TAG_SVG_a:
				gf_node_traverse(child->node, tr_state); 
				break;
			case TAG_SVG_tbreak:
				if (tr_state->in_svg_text_area) {
					tr_state->text_end_y += (tr_state->svg_props->line_increment->type == SVG_NUMBER_AUTO ? tr_state->line_spacing : tr_state->svg_props->line_increment->value);
					tr_state->text_end_x = 0;
				}
				break;
			default:
				break;
			}
			child = child->next;
		}
		tr_state->traversing_mode = mode;
		gf_node_dirty_clear(node, 0);
		drawable_mark_modified(st->drawable, tr_state);
		st->prev_size = tr_state->svg_props->font_size->value;
		st->prev_flags = *tr_state->svg_props->font_style;
		st->prev_anchor = *tr_state->svg_props->text_anchor;

		svg_update_bounds(st);
	} 
	
	if (tr_state->traversing_mode == TRAVERSE_GET_BOUNDS) {
		if (!compositor_svg_is_display_off(tr_state->svg_props))
			tr_state->bounds = st->bounds;

	} 
	else if (
		(tr_state->traversing_mode == TRAVERSE_SORT) 
		&& !compositor_svg_is_display_off(tr_state->svg_props) 
		&& ( *(tr_state->svg_props->visibility) != SVG_VISIBILITY_HIDDEN) 
	) {
		child = ((GF_ParentNode *) tspan)->children;
		
		ctx = drawable_init_context_svg(st->drawable, tr_state);
		if (ctx) svg_finalize_sort(ctx, st, tr_state);

		while (child) {
			switch  (gf_node_get_tag(child->node)) {
			case TAG_SVG_tspan:
			case TAG_SVG_switch:
			case TAG_SVG_a:
				gf_node_traverse(child->node, tr_state); 
				break;
			default:
				break;
			}
			child = child->next;
		}
	}

	compositor_svg_restore_parent_transformation(tr_state, &backup_matrix, &mx3d);
	memcpy(tr_state->svg_props, &backup_props, sizeof(SVGPropertiesPointers));
	tr_state->svg_flags = backup_flags;
}

void compositor_init_svg_tspan(GF_Compositor *compositor, GF_Node *node)
{
	SVG_TextStack *stack;
	GF_SAFEALLOC(stack, SVG_TextStack);
	stack->drawable = drawable_new();
	stack->drawable->node = node;
	stack->drawable->flags = DRAWABLE_USE_TRAVERSE_DRAW;
	stack->spans = gf_list_new();
	gf_node_set_private(node, stack);
	gf_node_set_callback_function(node, svg_traverse_tspan);
}


static void svg_traverse_textArea(GF_Node *node, void *rs, Bool is_destroy)
{	
	SVGPropertiesPointers backup_props;
	u32 backup_flags;
	GF_Matrix mx3d;
	GF_Matrix2D backup_matrix;
	DrawableContext *ctx;
	GF_ChildNodeItem *child;
	SVG_TextStack *st = (SVG_TextStack *)gf_node_get_private(node);
	GF_TraverseState *tr_state = (GF_TraverseState *)rs;
	SVG_Element *text = (SVG_Element *)node;
	SVGAllAttributes atts;

	if (is_destroy) {
		drawable_del(st->drawable);
		svg_reset_text_stack(st);
		gf_list_del(st->spans);
		free(st);
		return;
	}

	if (tr_state->traversing_mode==TRAVERSE_DRAW_2D) {
		svg_text_draw_2d(st, tr_state);
		return;
	}
	else if (tr_state->traversing_mode==TRAVERSE_GET_TEXT) {
		gf_font_spans_get_selection(node, st->spans, tr_state);
		return;
	}


	gf_svg_flatten_attributes(text, &atts);
	if (!compositor_svg_traverse_base(node, &atts, tr_state, &backup_props, &backup_flags))
		return;

	tr_state->text_parent = node;

	if (tr_state->traversing_mode==TRAVERSE_PICK) {
		if (*tr_state->svg_props->pointer_events!=SVG_POINTEREVENTS_NONE) 
			gf_font_spans_pick(node, st->spans, tr_state, &st->bounds, 1, st->drawable);

		memcpy(tr_state->svg_props, &backup_props, sizeof(SVGPropertiesPointers));
		tr_state->svg_flags = backup_flags;
		tr_state->text_parent = NULL;
		return;
	}
	
	compositor_svg_apply_local_transformation(tr_state, &atts, &backup_matrix, &mx3d);
	tr_state->in_svg_text_area++;

	if ( (st->prev_size != tr_state->svg_props->font_size->value) || 
		 (st->prev_flags != *tr_state->svg_props->font_style) || 
		 (st->prev_anchor != *tr_state->svg_props->text_anchor) ||
		 (gf_node_dirty_get(node) & (GF_SG_SVG_GEOMETRY_DIRTY | GF_SG_CHILD_DIRTY) ) 
		 || tr_state->visual->compositor->reset_fonts
	) {
		u32 mode;

		child = ((GF_ParentNode *) text)->children;

		svg_reset_text_stack(st);
		drawable_reset_path(st->drawable);
		tr_state->max_length = (atts.width ? (atts.width->type == SVG_NUMBER_AUTO ? FIX_MAX : atts.width->value) : FIX_MAX);
		tr_state->max_height = (atts.height ? (atts.height->type == SVG_NUMBER_AUTO ? FIX_MAX : atts.height->value) : FIX_MAX);
		tr_state->base_x = (atts.x ? atts.x->value : 0);
		tr_state->base_y = (atts.y ? atts.y->value : 0);
		/*let it initialize from first font*/
		tr_state->line_spacing = 0;
		tr_state->text_end_x = 0;
		tr_state->text_end_y = (tr_state->svg_props->line_increment->type == SVG_NUMBER_AUTO ? 0 : tr_state->svg_props->line_increment->value);

		tr_state->x_anchors = gf_list_new();

		/*switch to bounds mode, and recompute children*/
		mode = tr_state->traversing_mode;
		tr_state->traversing_mode = TRAVERSE_GET_BOUNDS;
		tr_state->last_char_was_space = 0;

		child = ((GF_ParentNode *) text)->children;
		while (child) {
			switch  (gf_node_get_tag(child->node)) {
			case TAG_DOMText:
				svg_traverse_dom_text_area(child->node, &atts, tr_state, st->spans); 
				break;
			case TAG_SVG_tspan:
			case TAG_SVG_switch:
			case TAG_SVG_a:
				gf_node_traverse(child->node, tr_state); 
				break;
			case TAG_SVG_tbreak:
				svg_text_area_reset_state(tr_state);
				tr_state->text_end_y += (tr_state->svg_props->line_increment->type == SVG_NUMBER_AUTO ? tr_state->line_spacing : tr_state->svg_props->line_increment->value);
				tr_state->text_end_x = 0;
				/*reset line spacing*/
				tr_state->line_spacing = 0;
				break;
			default:
				break;
			}
			child=child->next;
		}

		//effacement m�moire, mise � jour des donn�es-test de changement
		gf_node_dirty_clear(node, 0);
		drawable_mark_modified(st->drawable, tr_state);
		tr_state->traversing_mode = mode;
		st->prev_size = tr_state->svg_props->font_size->value;
		st->prev_flags = *tr_state->svg_props->font_style;
		st->prev_anchor = *tr_state->svg_props->text_anchor;

		svg_text_area_reset_state(tr_state);
		gf_list_del(tr_state->x_anchors);

		svg_update_bounds(st);

	} 
	
	if (tr_state->traversing_mode == TRAVERSE_GET_BOUNDS) {
		if (!compositor_svg_is_display_off(tr_state->svg_props))
			tr_state->bounds = st->bounds;
	} else if ( (tr_state->traversing_mode == TRAVERSE_SORT) 
			&& !compositor_svg_is_display_off(tr_state->svg_props) 
			&& (*(tr_state->svg_props->visibility) != SVG_VISIBILITY_HIDDEN) 
		) {

		ctx = drawable_init_context_svg(st->drawable, tr_state);
		if (ctx) svg_finalize_sort(ctx, st, tr_state);
		
		child = ((GF_ParentNode *) text)->children;
		while (child) {
			switch  (gf_node_get_tag(child->node)) {
			case TAG_DOMText:
				break;
			case TAG_SVG_tspan:
			case TAG_SVG_switch:
			case TAG_SVG_a:
				gf_node_traverse(child->node, tr_state); 
				break;
			default:
				break;
			}
			child = child->next;
		}
	}
	tr_state->in_svg_text_area--;
	tr_state->text_parent = NULL;


	compositor_svg_restore_parent_transformation(tr_state, &backup_matrix, &mx3d);
	memcpy(tr_state->svg_props, &backup_props, sizeof(SVGPropertiesPointers));
	tr_state->svg_flags = backup_flags;
}

void compositor_init_svg_textarea(GF_Compositor *compositor, GF_Node *node)
{
	SVG_TextStack *stack;
	GF_SAFEALLOC(stack, SVG_TextStack);
	stack->drawable = drawable_new();
	stack->drawable->node = node;
	stack->drawable->flags = DRAWABLE_USE_TRAVERSE_DRAW;
	stack->spans = gf_list_new();
	gf_node_set_private(node, stack);
	gf_node_set_callback_function(node, svg_traverse_textArea);
}



#endif /*GPAC_DISABLE_SVG*/

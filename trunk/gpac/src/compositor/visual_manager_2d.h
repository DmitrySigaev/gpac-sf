/*
 *			GPAC - Multimedia Framework C SDK
 *
 *			Copyright (c) Jean Le Feuvre 2000-2005
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

#ifndef _VISUAL_MANAGER_2D_
#define _VISUAL_MANAGER_2D_

Bool gf_irect_overlaps(GF_IRect *rc1, GF_IRect *rc2);
void gf_irect_intersect(GF_IRect *rc1, GF_IRect *rc2);
GF_Rect gf_rect_ft(GF_IRect *rc);

/*@rc1 equales @rc2*/
#define gf_rect_equal(rc1, rc2) ((rc1.width == rc2.width) && (rc1.height == rc2.height) && (rc1.x == rc2.x)  && (rc1.y == rc2.y)) 


//#define TRACK_OPAQUE_REGIONS

/*ra_: rectangle array macros to speed dirty rects*/
#define RA_DEFAULT_STEP	10

typedef struct
{	
	GF_IRect *list;
	u32 count, alloc;
#ifdef TRACK_OPAQUE_REGIONS
	/*list of nodes covering (no transparency) each rect, or 0 otherwise.*/
	u32 *opaque_node_index;
#endif
} GF_RectArray;

#ifdef TRACK_OPAQUE_REGIONS
/*inits structure - called as a constructor*/
#define ra_init(ra) { (ra)->count = 0; (ra)->alloc = 1; (ra)->list = (GF_IRect*)malloc(sizeof(GF_IRect)); (ra)->opaque_node_index = NULL;}
/*deletes structure - called as a destructor*/
#define ra_del(ra) { free((ra)->list); if ((ra)->opaque_node_index) free((ra)->opaque_node_index); }
#else
#define ra_init(ra) { (ra)->count = 0; (ra)->alloc = 1; (ra)->list = (GF_IRect*)malloc(sizeof(GF_IRect));}
/*deletes structure - called as a destructor*/
#define ra_del(ra) { free((ra)->list); }
#endif

/*adds rect to list - expand if needed*/
#define ra_add(ra, rc) {	\
	if ((ra)->count==(ra)->alloc) { (ra)->alloc += RA_DEFAULT_STEP; (ra)->list = (GF_IRect*)realloc((ra)->list, sizeof(GF_IRect) * (ra)->alloc); }	\
	(ra)->list[(ra)->count] = *rc; (ra)->count++;	}


struct _drawable_store
{
	struct _drawable *drawable;
	struct _drawable_store *next;
};

/*
 *	Visual 2D functions
 */
Bool visual_2d_draw_frame(GF_VisualManager *visual, GF_Node *root, GF_TraverseState *tr_state, Bool is_root_visual);

Bool visual_2d_node_cull(GF_TraverseState *tr_state, GF_Rect *bounds);

void visual_2d_pick_node(GF_VisualManager *visual, GF_TraverseState *tr_state, GF_Event *ev, GF_ChildNodeItem *children);

/*gets a drawable context on this visual*/
DrawableContext *visual_2d_get_drawable_context(GF_VisualManager *visual);
/*remove last drawable context*/
void visual_2d_remove_last_context(GF_VisualManager *visual);
/*signal the given drawable is being deleted*/
void visual_2d_drawable_delete(GF_VisualManager *visual, Drawable *node);

/*inits raster surface handler for subsequent draw*/
GF_Err visual_2d_init_raster(GF_VisualManager *visual);
/*releases raster surface handler */
void visual_2d_release_raster(GF_VisualManager *visual);

/*clear given rect or all visual if no rect specified - clear color depends on visual's type:
	BackColor for background nodes
	0x00000000 for composite, 
	compositor clear color otherwise
*/
void visual_2d_clear(GF_VisualManager *visual, GF_IRect *clear, u32 BackColor);
/*texture the path with the given context info*/
void visual_2d_texture_path(GF_VisualManager *visual, GF_Path *path, DrawableContext *ctx);
/*draw the path (fill and strike) - if brushes are NULL they are created if needed based on the context aspect
DrawPath shall always be called after TexturePath*/
void visual_2d_draw_path(GF_VisualManager *visual, GF_Path *path, DrawableContext *ctx, GF_STENCIL brush, GF_STENCIL pen);
/*special texturing extension for text, using a given path (text rectangle) and texture*/
void visual_2d_texture_path_text(GF_VisualManager *visual, DrawableContext *txt_ctx, GF_Path *path, GF_Rect *object_bounds, GF_TextureHandler *txh);
/*fill given rect with given color with given ctx transform and clipper (used for text hilighting only)
if rc is NULL, fills object bounds*/
void visual_2d_fill_rect(GF_VisualManager *visual, DrawableContext *ctx, GF_Rect *rc, u32 color, u32 strike_color);


void visual_2d_texture_path_extended(GF_VisualManager *visual, GF_Path *path, GF_TextureHandler *txh, struct _drawable_context *ctx, GF_Rect *orig_bounds, GF_Matrix2D *ext_mx);


#endif	/*_VISUAL_MANAGER_2D_*/


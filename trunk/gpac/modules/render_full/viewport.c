/*
 *			GPAC - Multimedia Framework C SDK
 *
 *			Copyright (c) Jean Le Feuvre 2000-2005
 *					All rights reserved
 *
 *  This file is part of GPAC / 2D+3D rendering module
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

#include "node_stacks.h"
#include "visual_manager.h"
/*for default scene view*/
#include <gpac/internal/terminal_dev.h>



GF_Err render_get_viewpoint(GF_VisualRenderer *vr, u32 viewpoint_idx, const char **outName, Bool *is_bound)
{
	u32 count;
	GF_Node *n;
	Render *sr = (Render *) vr->user_priv;
	if (!sr->visual) return GF_BAD_PARAM;
	count = gf_list_count(sr->visual->view_stack);
	if (!viewpoint_idx) return GF_BAD_PARAM;
	if (viewpoint_idx>count) return GF_EOS;

	n = (GF_Node*)gf_list_get(sr->visual->view_stack, viewpoint_idx-1);
	switch (gf_node_get_tag(n)) {
	case TAG_MPEG4_Viewport: *outName = ((M_Viewport*)n)->description.buffer; *is_bound = ((M_Viewport*)n)->isBound;return GF_OK;
	case TAG_MPEG4_Viewpoint: case TAG_X3D_Viewpoint: *outName = ((M_Viewpoint*)n)->description.buffer; *is_bound = ((M_Viewpoint*)n)->isBound; return GF_OK;
	default: *outName = NULL; return GF_OK;
	}
}

GF_Err render_set_viewpoint(GF_VisualRenderer *vr, u32 viewpoint_idx, const char *viewpoint_name)
{
	u32 count, i;
	GF_Node *n;
	Render *sr = (Render *) vr->user_priv;
	if (!sr->visual) return GF_BAD_PARAM;
	count = gf_list_count(sr->visual->view_stack);
	if (viewpoint_idx>count) return GF_BAD_PARAM;
	if (!viewpoint_idx && !viewpoint_name) return GF_BAD_PARAM;

	if (viewpoint_idx) {
		Bool bind;
		n = (GF_Node*)gf_list_get(sr->visual->view_stack, viewpoint_idx-1);
		bind = Bindable_GetIsBound(n);
		Bindable_SetSetBind(n, !bind);
		return GF_OK;
	}
	for (i=0; i<count;i++) {
		char *name = NULL;
		n = (GF_Node*)gf_list_get(sr->visual->view_stack, viewpoint_idx-1);
		switch (gf_node_get_tag(n)) {
		case TAG_MPEG4_Viewport: name = ((M_Viewport*)n)->description.buffer; break;
		case TAG_MPEG4_Viewpoint: case TAG_X3D_Viewpoint: name = ((M_Viewpoint*)n)->description.buffer; break;
		default: break;
		}
		if (name && !stricmp(name, viewpoint_name)) {
			Bool bind = Bindable_GetIsBound(n);
			Bindable_SetSetBind(n, !bind);
			return GF_OK;
		}
	}
	return GF_BAD_PARAM;
}

#define VPCHANGED(__rend) { GF_Event evt; evt.type = GF_EVENT_VIEWPOINTS; GF_USER_SENDEVENT(__rend->user, &evt); }


static void DestroyViewStack(GF_Node *node)
{
	ViewStack *st = (ViewStack *) gf_node_get_private(node);
	PreDestroyBindable(node, st->reg_stacks);
	gf_list_del(st->reg_stacks);
	VPCHANGED(gf_sr_get_renderer(node));
	free(st);
}

static void viewport_set_bind(GF_Node *node)
{
	GF_Renderer *rend = gf_sr_get_renderer(node);
	ViewStack *st = (ViewStack *) gf_node_get_private(node);
	Bindable_OnSetBind(node, st->reg_stacks);

	gf_sr_invalidate(rend, NULL);
	/*notify change of vp stack*/
	VPCHANGED(rend);
	/*and dirty ourselves to force frustrum update*/
	gf_node_dirty_set(node, 0, 0);
}


static void RenderViewport(GF_Node *node, void *rs, Bool is_destroy)
{
	Fixed ar, sx, sy, w, h, tx, ty;
#ifndef GPAC_DISABLE_3D
	GF_Matrix mx;
#endif
	GF_Matrix2D mat;
	GF_Rect rc, rc_bckup;
	Bool is_layer;
	ViewStack *st = (ViewStack *) gf_node_get_private(node);
	M_Viewport *vp = (M_Viewport *) node;
	GF_TraverseState *tr_state = (GF_TraverseState *)rs;
	
	if (is_destroy) {
		DestroyViewStack(node);
		return;
	}

#ifndef GPAC_DISABLE_3D
	if (tr_state->visual->type_3d>1) return;
#endif

	/*first traverse, bound if needed*/
	if (gf_list_find(tr_state->viewpoints, node) < 0) {
		gf_list_add(tr_state->viewpoints, node);
		assert(gf_list_find(st->reg_stacks, tr_state->viewpoints)==-1);
		gf_list_add(st->reg_stacks, tr_state->viewpoints);

		if (gf_list_get(tr_state->viewpoints, 0) == vp) {
			if (!vp->isBound) Bindable_SetIsBound(node, 1);
		} else {
			if (gf_is_default_scene_viewpoint(node)) Bindable_SetSetBind(node, 1);
		}
		VPCHANGED(tr_state->visual->render->compositor);
		/*in any case don't draw the first time (since the viewport could have been declared last)*/
		gf_sr_invalidate(tr_state->visual->render->compositor, NULL);
		return;
	}

	if (tr_state->traversing_mode != TRAVERSE_RENDER_BINDABLE) return;
	if (!vp->isBound) return;

	w = tr_state->bounds.width;
	h = tr_state->bounds.height;
	if (!w || !h) return;


	is_layer = (tr_state->viewpoints == tr_state->visual->view_stack) ? 0 : 1;
	/*if no parent this is the main viewport, don't update if not changed*/
	if (!is_layer && !gf_node_dirty_get(node)) return;

	gf_node_dirty_clear(node, 0);

	gf_mx2d_init(mat);
	gf_mx2d_add_translation(&mat, vp->position.x, vp->position.y);
	gf_mx2d_add_rotation(&mat, 0, 0, vp->orientation);

	//compute scaling ratio
	rc = gf_rect_center(vp->size.x, vp->size.y);
	ar = gf_divfix(h, w);
	rc_bckup = rc;

	switch (vp->fit) {
	/*covers all area and respect aspect ratio*/
	case 2:
		if (gf_divfix(rc.width, w) > gf_divfix(rc.height, h)) {
			rc.width = gf_muldiv(rc.width, h, rc.height);
			rc.height = h;
		} else {
			rc.height = gf_muldiv(rc.height , w, rc.width);
			rc.width = w;
		}
		break;
	/*fits inside the area and respect AR*/
	case 1:
		if (gf_divfix(rc.width, w)> gf_divfix(rc.height, h)) {
			rc.height = gf_muldiv(rc.height, w, rc.width);
			rc.width = w;
		} else {
			rc.width = gf_muldiv(rc.width, h, rc.height);
			rc.height = h;
		}
		break;
	/*fit entirely: nothing to change*/
	case 0:
		rc.width = w;
		rc.height = h;
		break;
	default:
		return;
	}
	sx = gf_divfix(rc.width, rc_bckup.width);
	sy = gf_divfix(rc.height, rc_bckup.height);

	rc.x = - rc.width/2;
	rc.y = rc.height/2;

	tx = ty = 0;
	if (vp->fit && vp->alignment.count) {
		/*left alignment*/
		if (vp->alignment.vals[0] == -1) tx = rc.width/2 - w/2;
		else if (vp->alignment.vals[0] == 1) tx = w/2 - rc.width/2;

		if (vp->alignment.count>1) {
			/*top-alignment*/
			if (vp->alignment.vals[1]==-1) ty = rc.height/2 - h/2;
			else if (vp->alignment.vals[1]==1) ty = h/2 - rc.height/2;
		}
	}
	
	gf_mx2d_init(mat);
	gf_mx2d_add_scale(&mat, sx, sy);
	gf_mx2d_add_translation(&mat, tx, ty);

	gf_mx2d_add_translation(&mat, -vp->position.x*sx, -vp->position.y*sy);
	gf_mx2d_add_rotation(&mat, 0, 0, vp->orientation);

	tr_state->bounds = rc;
	tr_state->bounds.x += tx;
	tr_state->bounds.y += ty;

#ifndef GPAC_DISABLE_3D
	if (tr_state->visual->type_3d) {
		/*in layers directly modify the model matrix*/
		if (is_layer) {
			gf_mx_from_mx2d(&mx, &mat);
			gf_mx_add_matrix(&tr_state->model_matrix, &mx);
		} 
		/*otherwise add to camera viewport matrix*/
		else {
			gf_mx_from_mx2d(&tr_state->camera->viewport, &mat);
			tr_state->camera->flags = (CAM_HAS_VIEWPORT | CAM_IS_DIRTY);
		}
	} else
#endif
		gf_mx2d_pre_multiply(&tr_state->transform, &mat);
}

void render_init_viewport(Render *sr, GF_Node *node)
{
	ViewStack *ptr;
	GF_SAFEALLOC(ptr, ViewStack);

	ptr->reg_stacks = gf_list_new();

	gf_node_set_private(node, ptr);
	gf_node_set_callback_function(node, RenderViewport);
	((M_Viewport*)node)->on_set_bind = viewport_set_bind;
}


#ifndef GPAC_DISABLE_3D

static void viewpoint_set_bind(GF_Node *node)
{
	GF_Renderer *rend = gf_sr_get_renderer(node);
	ViewStack *st = (ViewStack *) gf_node_get_private(node);

	if (!((M_Viewpoint*)node)->isBound ) 
		st->prev_was_bound = 0;
	Bindable_OnSetBind(node, st->reg_stacks);
	gf_sr_invalidate(rend, NULL);
	/*notify change of vp stack*/
	VPCHANGED(rend);
	/*and dirty ourselves to force frustrum update*/
	gf_node_dirty_set(node, 0, 0);
}

static void RenderViewpoint(GF_Node *node, void *rs, Bool is_destroy)
{
	SFVec3f pos, v1, v2;
	SFRotation ori;
	GF_Matrix mx;
	GF_TraverseState *tr_state = (GF_TraverseState *)rs;
	M_Viewpoint *vp = (M_Viewpoint*) node;
	ViewStack *st = (ViewStack *) gf_node_get_private(node);

	if (is_destroy) {
		DestroyViewStack(node);
		return;
	}

	assert(tr_state->viewpoints);
//	if (!tr_state->camera->is_3D) return;

	/*first traverse, bound if needed*/
	if (gf_list_find(tr_state->viewpoints, node) < 0) {
		gf_list_add(tr_state->viewpoints, node);
		assert(gf_list_find(st->reg_stacks, tr_state->viewpoints)==-1);
		gf_list_add(st->reg_stacks, tr_state->viewpoints);

		if (gf_list_get(tr_state->viewpoints, 0) == vp) {
			if (!vp->isBound) Bindable_SetIsBound(node, 1);
		} else {
			if (gf_is_default_scene_viewpoint(node)) Bindable_SetSetBind(node, 1);
		}
		VPCHANGED(tr_state->visual->render->compositor);
		/*in any case don't draw the first time (since the viewport could have been declared last)*/
		if (tr_state->layer3d) gf_node_dirty_set(tr_state->layer3d, GF_SG_VRML_BINDABLE_DIRTY, 0);
		gf_sr_invalidate(tr_state->visual->render->compositor, NULL);
	}
	/*not rendering vp, return*/
	if (tr_state->traversing_mode != TRAVERSE_RENDER_BINDABLE) {
		/*store model matrix if changed - NOTE: we always have a 1-frame delay between VP used and real world...
		we could remove this by pre-rendering the scene before applying vp, but that would mean 2 scene 
		traversals*/
		if ((tr_state->traversing_mode==TRAVERSE_RENDER) || (tr_state->traversing_mode==TRAVERSE_GET_BOUNDS) ) {
			if (!gf_mx_equal(&st->world_view_mx, &tr_state->model_matrix)) {
				gf_mx_copy(st->world_view_mx, tr_state->model_matrix);
				gf_node_dirty_set(node, 0, 0);
			}
		}
		tr_state->trav_flags |= TF_DONT_CULL;
		return;
	}

	/*not bound or in 2D visual*/
	if (!vp->isBound || !tr_state->navigations) return;

	if (!gf_node_dirty_get(node)) return;
	gf_node_dirty_clear(node, 0);

	/*move to local system*/
	gf_mx_copy(mx, st->world_view_mx);
	gf_mx_add_translation(&mx, vp->position.x, vp->position.y, vp->position.z);
	gf_mx_add_rotation(&mx, vp->orientation.q, vp->orientation.x, vp->orientation.y, vp->orientation.z);
	gf_mx_decompose(&mx, &pos, &v1, &ori, &v2);
	/*get center*/
	v1.x = v1.y = v1.z = 0;
	/*X3D specifies examine center*/
	if (gf_node_get_tag(node)==TAG_X3D_Viewpoint) v1 = ((X_Viewpoint *)node)->centerOfRotation;
	gf_mx_apply_vec(&st->world_view_mx, &v1);
	/*set frustrum param - animate only if not bound last frame and jump false*/
	visual_3d_viewpoint_change(tr_state, node, (!st->prev_was_bound && !vp->jump) ? 1 : 0, vp->fieldOfView, pos, ori, v1);
	st->prev_was_bound = 1;
}

void render_init_viewpoint(Render *sr, GF_Node *node)
{
	ViewStack *st;
	GF_SAFEALLOC(st, ViewStack);

	st->reg_stacks = gf_list_new();
	gf_mx_init(st->world_view_mx);
	gf_node_set_private(node, st);
	gf_node_set_callback_function(node, RenderViewpoint);
	((M_Viewpoint*)node)->on_set_bind = viewpoint_set_bind;
}

#endif

static void navinfo_set_bind(GF_Node *node)
{
	ViewStack *st = (ViewStack *) gf_node_get_private(node);
	Bindable_OnSetBind(node, st->reg_stacks);
	gf_sr_invalidate( gf_sr_get_renderer(node), NULL);
}

static void RenderNavigationInfo(GF_Node *node, void *rs, Bool is_destroy)
{
	u32 i;
#ifndef GPAC_DISABLE_3D
	SFVec3f start, end;
	Fixed scale;
#endif
	GF_TraverseState *tr_state = (GF_TraverseState *)rs;
	M_NavigationInfo *ni = (M_NavigationInfo *) node;
	ViewStack *st = (ViewStack *) gf_node_get_private(node);

	if (is_destroy) {
		DestroyViewStack(node);
		return;
	}
#ifdef GPAC_DISABLE_3D

	/*FIXME, we only deal with one node, no bind stack for the current time*/
	for (i=0; i<ni->type.count; i++) {
		if (ni->type.vals[i] && !stricmp(ni->type.vals[i], "NONE")) {
			tr_state->visual->render->navigation_disabled = 1;
		}
	}
#else

	if (!tr_state->navigations) return;

	/*first traverse, bound if needed*/
	if (gf_list_find(tr_state->navigations, node) < 0) {
		gf_list_add(tr_state->navigations, node);
		if (gf_list_get(tr_state->navigations, 0) == ni) {
			if (!ni->isBound) Bindable_SetIsBound(node, 1);
		}
		assert(gf_list_find(st->reg_stacks, tr_state->navigations)==-1);
		gf_list_add(st->reg_stacks, tr_state->navigations);
		gf_mx_copy(st->world_view_mx, tr_state->model_matrix);
		/*in any case don't draw the first time*/
		gf_sr_invalidate(tr_state->visual->render->compositor, NULL);
		return;
	}
	/*not bound*/
	if (!ni->isBound) return;
	/*not rendering, return*/
	if (tr_state->traversing_mode != TRAVERSE_RENDER_BINDABLE) {
		if ((tr_state->traversing_mode==TRAVERSE_RENDER) || (tr_state->traversing_mode==TRAVERSE_GET_BOUNDS) ) {
			if (!gf_mx_equal(&st->world_view_mx, &tr_state->model_matrix)) {
				gf_mx_copy(st->world_view_mx, tr_state->model_matrix);
				gf_node_dirty_set(node, 0, 0);
			}
		}
		return;
	}

	if (!gf_node_dirty_get(node)) return;
	gf_node_dirty_clear(node, 0);

	tr_state->camera->navigation_flags = 0;
	tr_state->camera->navigate_mode = 0;
	for (i=0; i<ni->type.count; i++) {
		if (ni->type.vals[i] && !stricmp(ni->type.vals[i], "ANY")) tr_state->camera->navigation_flags |= NAV_ANY;
		if (!tr_state->camera->navigate_mode) {
			if (ni->type.vals[i] && !stricmp(ni->type.vals[i], "NONE")) tr_state->camera->navigate_mode = GF_NAVIGATE_NONE;
			else if (ni->type.vals[i] && !stricmp(ni->type.vals[i], "WALK")) tr_state->camera->navigate_mode = GF_NAVIGATE_WALK;
			else if (ni->type.vals[i] && !stricmp(ni->type.vals[i], "EXAMINE")) tr_state->camera->navigate_mode = GF_NAVIGATE_EXAMINE;
			else if (ni->type.vals[i] && !stricmp(ni->type.vals[i], "FLY")) tr_state->camera->navigate_mode = GF_NAVIGATE_FLY;
			else if (ni->type.vals[i] && !stricmp(ni->type.vals[i], "QTVR")) tr_state->camera->navigate_mode = GF_NAVIGATE_VR;
		}
	}
	if (ni->headlight) tr_state->camera->navigation_flags |= NAV_HEADLIGHT;

	start.x = start.y = start.z = 0;
	end.x = end.y = 0;
	end.z = FIX_ONE;
	gf_mx_apply_vec(&st->world_view_mx, &start);
	gf_mx_apply_vec(&st->world_view_mx, &end);
	gf_vec_diff(end, end, start);
	scale = gf_vec_len(end);

	tr_state->camera->speed = gf_mulfix(scale, ni->speed);
    tr_state->camera->visibility = gf_mulfix(scale, ni->visibilityLimit);
	if (ni->avatarSize.count) tr_state->camera->avatar_size.x = gf_mulfix(scale, ni->avatarSize.vals[0]);
	if (ni->avatarSize.count>1) tr_state->camera->avatar_size.y = gf_mulfix(scale, ni->avatarSize.vals[1]);
	if (ni->avatarSize.count>2) tr_state->camera->avatar_size.z = gf_mulfix(scale, ni->avatarSize.vals[2]);

	if (0 && tr_state->is_pixel_metrics) {
		u32 s = MAX(tr_state->visual->width, tr_state->visual->height);
		s /= 2;
//		tr_state->camera->speed = ni->speed;
	    tr_state->camera->visibility *= s;
		tr_state->camera->avatar_size.x *= s;
		tr_state->camera->avatar_size.y *= s;
		tr_state->camera->avatar_size.z *= s;
	}
#endif

}

void render_init_navigation_info(Render *sr, GF_Node *node)
{
	ViewStack *st;
	GF_SAFEALLOC(st, ViewStack);

	st->reg_stacks = gf_list_new();
	gf_node_set_private(node, st);
	gf_node_set_callback_function(node, RenderNavigationInfo);
	((M_NavigationInfo*)node)->on_set_bind = navinfo_set_bind;
}


#ifndef GPAC_DISABLE_3D

static void fog_set_bind(GF_Node *node)
{
	ViewStack *st = (ViewStack *) gf_node_get_private(node);
	Bindable_OnSetBind(node, st->reg_stacks);
	gf_sr_invalidate(gf_sr_get_renderer(node), NULL);
}

static void RenderFog(GF_Node *node, void *rs, Bool is_destroy)
{
	Fixed density, vrange;
	SFVec3f start, end;
	ViewStack *vp_st;
	M_Viewpoint *vp;
	GF_TraverseState *tr_state = (GF_TraverseState *)rs;
	M_Fog *fog = (M_Fog *) node;
	ViewStack *st = (ViewStack *) gf_node_get_private(node);

	if (is_destroy) {
		DestroyViewStack(node);
		return;
	}

	if (!tr_state->fogs) return;

	/*first traverse, bound if needed*/
	if (gf_list_find(tr_state->fogs, node) < 0) {
		gf_list_add(tr_state->fogs, node);
		if (gf_list_get(tr_state->fogs, 0) == fog) {
			if (!fog->isBound) Bindable_SetIsBound(node, 1);
		}
		assert(gf_list_find(st->reg_stacks, tr_state->fogs)==-1);
		gf_list_add(st->reg_stacks, tr_state->fogs);

		gf_mx_copy(st->world_view_mx, tr_state->model_matrix);
		/*in any case don't draw the first time*/
		gf_sr_invalidate(tr_state->visual->render->compositor, NULL);
		return;
	}
	/*not rendering, return*/
	if (tr_state->traversing_mode != TRAVERSE_RENDER_BINDABLE) {
		if ((tr_state->traversing_mode==TRAVERSE_RENDER) || (tr_state->traversing_mode==TRAVERSE_GET_BOUNDS) ) 
			gf_mx_copy(st->world_view_mx, tr_state->model_matrix);
		return;
	}
	/*not bound*/
	if (!fog->isBound || !fog->visibilityRange) return;

	/*fog visibility is expressed in current bound VP so get its matrix*/
	vp = (M_Viewpoint*)gf_list_get(tr_state->viewpoints, 0);
	vp_st = NULL;
	if (vp && vp->isBound) vp_st = (ViewStack *) gf_node_get_private((GF_Node *)vp);

	start.x = start.y = start.z = 0;
	end.x = end.y = 0; end.z = fog->visibilityRange;
	if (vp_st) {
		gf_mx_apply_vec(&vp_st->world_view_mx, &start);
		gf_mx_apply_vec(&vp_st->world_view_mx, &end);
	}
	gf_mx_apply_vec(&st->world_view_mx, &start);
	gf_mx_apply_vec(&st->world_view_mx, &end);
	gf_vec_diff(end, end, start);
	vrange = gf_vec_len(end);

	density = gf_invfix(vrange);
	visual_3d_set_fog(tr_state->visual, fog->fogType.buffer, fog->color, density, vrange);
}

void render_init_fog(Render *sr, GF_Node *node)
{
	ViewStack *st;
	GF_SAFEALLOC(st, ViewStack);

	st->reg_stacks = gf_list_new();
	gf_node_set_private(node, st);
	gf_node_set_callback_function(node, RenderFog);
	((M_Fog*)node)->on_set_bind = fog_set_bind;
}

#endif

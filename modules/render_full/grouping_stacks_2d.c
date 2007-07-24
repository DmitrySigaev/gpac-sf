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
#include "grouping.h"
#include "visual_manager.h"
/*for anchor processing, which needs to be filtered at the inline scene level*/
#include <gpac/internal/terminal_dev.h>

typedef struct
{
	s32 last_switch;
} SwitchStack;

static void RenderSwitch(GF_Node *node, void *rs, Bool is_destroy)
{
	GF_ChildNodeItem *l;
	u32 i, count;
	Bool prev_switch;
	GF_ChildNodeItem *children;
	s32 whichChoice;
	GF_Node *child;
	SwitchStack *st = (SwitchStack *)gf_node_get_private(node);
	GF_TraverseState *tr_state; 
	tr_state = (GF_TraverseState *)rs;

	if (is_destroy) {
		free(st);
		return;
	}
	

	if (gf_node_get_name(node)) {
		node = node;
	}
	/*WARNING: X3D/MPEG4 NOT COMPATIBLE*/
	if (gf_node_get_tag(node)==TAG_MPEG4_Switch) {
		children = ((M_Switch *)node)->choice;
		whichChoice = ((M_Switch *)node)->whichChoice;
	} else {
		children = ((X_Switch *)node)->children;
		whichChoice = ((X_Switch *)node)->whichChoice;
	}
	count = gf_node_list_get_count(children);

	prev_switch = tr_state->trav_flags;
	/*check changes in choice field*/
	if ((gf_node_dirty_get(node) & GF_SG_NODE_DIRTY) || (st->last_switch != whichChoice) ) {
		tr_state->trav_flags |= GF_SR_TRAV_SWITCHED_OFF;
		i=0;
		l = children;
		while (l) {
//			if ((s32) i!=whichChoice) gf_node_render(l->node, tr_state);
			if ((s32) i == st->last_switch) gf_node_render(l->node, tr_state);
			l = l->next;
			i++;
		}
		tr_state->trav_flags &= ~GF_SR_TRAV_SWITCHED_OFF;
		st->last_switch = whichChoice;
	}

	gf_node_dirty_clear(node, 0);

	/*no need to check for sensors since a sensor is active for the whole parent group, that is for switch itself
	CSQ: switch cannot be used to switch sensors, too bad...*/
	tr_state->trav_flags = prev_switch;

	if (whichChoice>=0) {
		child = (GF_Node*)gf_node_list_get_child(children, whichChoice);
		gf_node_render(child, tr_state);
	}
}

void render_init_switch(Render *sr, GF_Node *node)
{
	SwitchStack *st = (SwitchStack *)malloc(sizeof(SwitchStack));
	st->last_switch = -1;
	gf_node_set_private(node, st);
	gf_node_set_callback_function(node, RenderSwitch);
}


/*transform2D*/
typedef struct
{
	GROUPING_NODE_STACK_2D
	GF_Matrix2D mat;
	Bool is_identity;
} Transform2DStack;

static void traverse_transform(GF_Node *node, Transform2DStack *stack, GF_TraverseState *tr_state)
{
	/*note we don't clear dirty flag, this is done in traversing*/
	if (stack->is_identity) {
		group_2d_traverse(node, (GroupingNode2D *)stack, tr_state);
	} 
#ifndef GPAC_DISABLE_3D
	else if (tr_state->visual->type_3d) {
		GF_Matrix mx_bckup;
		gf_mx_copy(mx_bckup, tr_state->model_matrix);

		gf_mx_add_matrix_2d(&tr_state->model_matrix, &stack->mat);

		if (tr_state->traversing_mode == TRAVERSE_RENDER) {
			GF_Matrix tmp;
			gf_mx_from_mx2d(&tmp, &stack->mat);
			visual_3d_matrix_push(tr_state->visual);
			visual_3d_matrix_add(tr_state->visual, tmp.m);
			group_2d_traverse(node, (GroupingNode2D *)stack, tr_state);
			visual_3d_matrix_pop(tr_state->visual);
		} else {
			group_2d_traverse(node, (GroupingNode2D *)stack, tr_state);
		}

		gf_mx_copy(tr_state->model_matrix, mx_bckup);
	} 
#endif
	else {
		GF_Matrix2D bckup;
		gf_mx2d_copy(bckup, tr_state->transform);
		gf_mx2d_pre_multiply(&tr_state->transform, &stack->mat);
		
		group_2d_traverse(node, (GroupingNode2D *)stack, tr_state);

		gf_mx2d_copy(tr_state->transform, bckup);
	}

	if (tr_state->traversing_mode == TRAVERSE_GET_BOUNDS) {
		gf_mx2d_apply_rect(&stack->mat, &tr_state->bounds);
	}
}


static void RenderTransform2D(GF_Node *node, void *rs, Bool is_destroy)
{
	M_Transform2D *tr = (M_Transform2D *)node;
	Transform2DStack *ptr = (Transform2DStack *)gf_node_get_private(node);
	GF_TraverseState *tr_state;
	
	if (is_destroy) {
		free(ptr);
		return;
	}

	tr_state = (GF_TraverseState *) rs;

	if (gf_node_dirty_get(node) & GF_SG_NODE_DIRTY) {
		gf_mx2d_init(ptr->mat);
		ptr->is_identity = 1;
		if ((tr->scale.x != FIX_ONE) || (tr->scale.y != FIX_ONE)) {
			gf_mx2d_add_scale_at(&ptr->mat, tr->scale.x, tr->scale.y, 0, 0, tr->scaleOrientation);
			ptr->is_identity = 0;
		}
		if (tr->rotationAngle) {
			gf_mx2d_add_rotation(&ptr->mat, tr->center.x, tr->center.y, tr->rotationAngle);
			ptr->is_identity = 0;
		}
		if (tr->translation.x || tr->translation.y) {
			ptr->is_identity = 0;
			gf_mx2d_add_translation(&ptr->mat, tr->translation.x, tr->translation.y);
		}
	}
	traverse_transform(node, ptr, tr_state);
}

void render_init_transform2d(Render *sr, GF_Node *node)
{
	Transform2DStack *stack;
	GF_SAFEALLOC(stack, Transform2DStack);

	gf_mx2d_init(stack->mat);
	stack->is_identity = 1;
	gf_node_set_private(node, stack);
	gf_node_set_callback_function(node, RenderTransform2D);
}

void tr_mx2d_get_matrix(GF_Node *n, GF_Matrix2D *mat)
{
	M_TransformMatrix2D *tr = (M_TransformMatrix2D*)n;
	gf_mx2d_init(*mat);
	mat->m[0] = tr->mxx;
	mat->m[1] = tr->mxy;
	mat->m[2] = tr->tx;
	mat->m[3] = tr->myx;
	mat->m[4] = tr->myy;
	mat->m[5] = tr->ty;
}


/*TransformMatrix2D*/
static void RenderTransformMatrix2D(GF_Node *node, void *rs, Bool is_destroy)
{
	Transform2DStack *ptr = (Transform2DStack *) gf_node_get_private(node);
	GF_TraverseState *tr_state = (GF_TraverseState *)rs;

	if (is_destroy) {
		free(ptr);
		return;
	}

	if (gf_node_dirty_get(node) & GF_SG_NODE_DIRTY) {
		M_TransformMatrix2D *tr = (M_TransformMatrix2D*)node;
		tr_mx2d_get_matrix(node, &ptr->mat);
		if ((tr->mxx==FIX_ONE) && (tr->mxy==0) && (tr->tx==0)
			&& (tr->myx==0) && (tr->myy==FIX_ONE) && (tr->ty==0) )
			ptr->is_identity = 1;
		else
			ptr->is_identity = 0;
	}
	traverse_transform(node, ptr, tr_state);
}


void render_init_transformmatrix2d(Render *sr, GF_Node *node)
{
	Transform2DStack *stack;
	GF_SAFEALLOC(stack, Transform2DStack);

	gf_mx2d_init(stack->mat);
	gf_node_set_private(node, stack);
	gf_node_set_callback_function(node, RenderTransformMatrix2D);
}


typedef struct
{
	GROUPING_NODE_STACK_2D
	GF_ColorMatrix cmat;
} ColorTransformStack;

/*ColorTransform*/
static void RenderColorTransform(GF_Node *node, void *rs, Bool is_destroy)
{
	Bool c_changed;
	M_ColorTransform *tr = (M_ColorTransform *)node;
	ColorTransformStack *ptr = (ColorTransformStack  *)gf_node_get_private(node);
	GF_TraverseState *tr_state;
	tr_state = (GF_TraverseState *) rs;

	if (is_destroy) {
		free(ptr);
		return;
	}

	c_changed = 0;
	if (gf_node_dirty_get(node) & GF_SG_NODE_DIRTY) {
		gf_cmx_set(&ptr->cmat, 
			tr->mrr , tr->mrg, tr->mrb, tr->mra, tr->tr, 
			tr->mgr , tr->mgg, tr->mgb, tr->mga, tr->tg, 
			tr->mbr, tr->mbg, tr->mbb, tr->mba, tr->tb, 
			tr->mar, tr->mag, tr->mab, tr->maa, tr->ta); 
		c_changed = 1;
	}
	/*note we don't clear dirty flag, this is done in traversing*/
	if (ptr->cmat.identity) {
		group_2d_traverse(node, (GroupingNode2D *) ptr, tr_state);
	} else {
		GF_ColorMatrix gf_cmx_bck;
		Bool prev_inv = tr_state->invalidate_all;
		/*if modified redraw all nodes*/
		if (c_changed) tr_state->invalidate_all = 1;
		gf_cmx_copy(&gf_cmx_bck, &tr_state->color_mat);
		gf_cmx_multiply(&tr_state->color_mat, &ptr->cmat);
		group_2d_traverse(node, (GroupingNode2D *) ptr, tr_state);
		/*restore traversing state*/
		gf_cmx_copy(&tr_state->color_mat, &gf_cmx_bck);
		tr_state->invalidate_all = prev_inv;
	}
}

void render_init_colortransform(Render *sr, GF_Node *node)
{
	ColorTransformStack *stack;
	GF_SAFEALLOC(stack, ColorTransformStack);

	gf_cmx_init(&stack->cmat);
	gf_node_set_private(node, stack);
	gf_node_set_callback_function(node, RenderColorTransform);
}


struct og_pos
{
	Fixed priority;
	u32 position;
};
typedef struct
{
	GROUPING_NODE_STACK_2D
	u32 *positions;
} OrderedGroupStack;


static s32 compare_priority(const void* elem1, const void* elem2)
{
	struct og_pos *p1, *p2;
	p1 = (struct og_pos *)elem1;
	p2 = (struct og_pos *)elem2;
	if (p1->priority < p2->priority) return -1;
	if (p1->priority > p2->priority) return 1;
	return 0;
}


static void RenderOrderedGroup(GF_Node *node, void *rs, Bool is_destroy)
{
	u32 i, count;
	struct og_pos *priorities;
	Bool invalidate_backup;
	OrderedGroupStack *stack = (OrderedGroupStack *) gf_node_get_private(node);
	M_OrderedGroup *og = (M_OrderedGroup *) node;
	GF_TraverseState *tr_state = (GF_TraverseState *)rs;

	if (is_destroy) {
		if (stack->positions) free(stack->positions);
		free(stack);
		return;
	}

	if (!og->order.count) {
		group_2d_traverse(node, (GroupingNode2D*)stack, tr_state);
		return;
	}

	invalidate_backup = tr_state->invalidate_all;
	/*check whether the OrderedGroup node has changed*/
	if (gf_node_dirty_get(node) & GF_SG_NODE_DIRTY) {
		if (stack->positions) free(stack->positions);
		count = gf_node_list_get_count(og->children);
		priorities = (struct og_pos*)malloc(sizeof(struct og_pos)*count);
		for (i=0; i<count; i++) {
			priorities[i].position = i;
			priorities[i].priority = (i<og->order.count) ? og->order.vals[i] : 0;
		}
		qsort(priorities, count, sizeof(struct og_pos), compare_priority);

		stack->positions = (u32*)malloc(sizeof(u32) * count);
		for (i=0; i<count; i++) stack->positions[i] = priorities[i].position;
		free(priorities);
		
		tr_state->invalidate_all = 1;
	}
	group_2d_traverse_with_order(node, (GroupingNode2D*)stack, tr_state, stack->positions);
	tr_state->invalidate_all = invalidate_backup;
}

void render_init_orderedgroup(Render *sr, GF_Node *node)
{
	OrderedGroupStack *ptr;
	GF_SAFEALLOC(ptr, OrderedGroupStack);	
	gf_node_set_private(node, ptr);
	gf_node_set_callback_function(node, RenderOrderedGroup);
}

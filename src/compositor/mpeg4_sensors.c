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



#include "nodes_stacks.h"
#include "visual_manager.h"
/*for anchor*/
#include "mpeg4_grouping.h"
/*for anchor processing, which needs to be filtered at the inline scene level*/
#include <gpac/internal/terminal_dev.h>


static void mpeg4_sensor_deleted(GF_Node *node, GF_SensorHandler *hdl)
{
	GF_Compositor *compositor = gf_sc_get_compositor(node);
	if (compositor) {
		gf_list_del_item(compositor->previous_sensors, hdl);
		if (compositor->interaction_sensors) compositor->interaction_sensors--;
	}
}


typedef struct
{
	GROUPING_NODE_STACK_2D

	Bool enabled, active, over;
	GF_SensorHandler hdl;

} AnchorStack;

static void TraverseAnchor(GF_Node *node, void *rs, Bool is_destroy)
{
	AnchorStack *st = (AnchorStack *) gf_node_get_private(node);
	GF_TraverseState *tr_state = (GF_TraverseState *)rs;

	if (is_destroy) {
		mpeg4_sensor_deleted(node, &st->hdl);
		gf_sc_check_focus_upon_destroy(node);
		free(st);
		return;
	}

	if (gf_node_dirty_get(node) & GF_SG_NODE_DIRTY) {
		MFURL *url;
		if (gf_node_get_tag(node)==TAG_MPEG4_Anchor) {
			url = & ((M_Anchor *)node)->url;
		} else {
			url = & ((X_Anchor *)node)->url;
		}
		st->enabled = 0;
		if (url->count && url->vals[0].url && strlen(url->vals[0].url) )
			st->enabled = 1;

		if (!tr_state->visual->compositor->user->EventProc) {
			st->enabled = 0;
		}
		gf_node_dirty_clear(node, GF_SG_NODE_DIRTY);
	}

	group_2d_traverse(node, (GroupingNode2D*)st, tr_state);
}

static void OnAnchor(GF_SensorHandler *sh, Bool is_over, GF_Event *ev, GF_Compositor *compositor)
{
	GF_Event evt;
	MFURL *url;
	AnchorStack *st = (AnchorStack *) gf_node_get_private(sh->sensor);

	if ((ev->type==GF_EVENT_MOUSEDOWN) && (ev->mouse.button==GF_MOUSE_LEFT)) st->active = 1;
	else if ((ev->type==GF_EVENT_KEYDOWN) && (ev->key.key_code==GF_KEY_ENTER)) st->active = 1;
	else if (st->active &&
		(/*mouse*/(ev->type==GF_EVENT_MOUSEUP) && (ev->mouse.button==GF_MOUSE_LEFT) 
		|| /*mouse*/(ev->type==GF_EVENT_KEYUP) && (ev->key.key_code==GF_KEY_ENTER) )
	) {
		u32 i;
		if (gf_node_get_tag(sh->sensor)==TAG_MPEG4_Anchor) {
			url = & ((M_Anchor *)sh->sensor)->url;
			evt.navigate.param_count = ((M_Anchor *)sh->sensor)->parameter.count;
			evt.navigate.parameters = (const char **) ((M_Anchor *)sh->sensor)->parameter.vals;
		} else {
			url = & ((X_Anchor *)sh->sensor)->url;
			evt.navigate.param_count = ((X_Anchor *)sh->sensor)->parameter.count;
			evt.navigate.parameters = (const char **) ((X_Anchor *)sh->sensor)->parameter.vals;
		}
		evt.type = GF_EVENT_NAVIGATE;
		i=0;
		while (i<url->count) {
			evt.navigate.to_url = url->vals[i].url;
			if (!evt.navigate.to_url) break;
			/*current scene navigation*/
			if (evt.navigate.to_url[0] == '#') {
				GF_Node *bindable;
				evt.navigate.to_url++;
				bindable = gf_sg_find_node_by_name(gf_node_get_graph(sh->sensor), (char *) evt.navigate.to_url);
				if (bindable) {
					Bindable_SetSetBind(bindable, 1);
					break;
				}
			} else if (compositor->term) {
				if (gf_inline_process_anchor(sh->sensor, &evt))
					break;
			} else if (compositor->user->EventProc) {
				if (compositor->user->EventProc(compositor->user->opaque, &evt))
					break;
			}
			i++;
		}
	} else if (is_over && !st->over) {
		st->over = 1;
		if (compositor->user->EventProc) {
			evt.type = GF_EVENT_NAVIGATE_INFO;
			if (gf_node_get_tag(sh->sensor)==TAG_MPEG4_Anchor) {
				evt.navigate.to_url = ((M_Anchor *)sh->sensor)->description.buffer;
				url = & ((M_Anchor *)sh->sensor)->url;
			} else {
				evt.navigate.to_url = ((X_Anchor *)sh->sensor)->description.buffer;
				url = & ((X_Anchor *)sh->sensor)->url;
			}
			if (!evt.navigate.to_url || !strlen(evt.navigate.to_url)) evt.navigate.to_url = url->vals[0].url;
			compositor->user->EventProc(compositor->user->opaque, &evt);
		}
	} else if (!is_over) {
		st->over = 0;
	}
}

static Bool anchor_is_enabled(GF_Node *node)
{
	AnchorStack *st = (AnchorStack *) gf_node_get_private(node);
	return st->enabled;
}

static void on_activate_anchor(GF_Node *node)
{
	GF_Event ev;
	AnchorStack *st = (AnchorStack *) gf_node_get_private(node);
	if (!((M_Anchor *)node)->on_activate) return;

	ev.type = GF_EVENT_MOUSEUP;
	ev.mouse.x = ev.mouse.y = 0;
	ev.mouse.button = GF_MOUSE_LEFT;
	OnAnchor(&st->hdl, 0, &ev, NULL);
}

GF_SensorHandler *gf_sc_anchor_get_handler(GF_Node *n)
{
	AnchorStack *st = (AnchorStack *) gf_node_get_private(n);
	return &st->hdl;
}


void compositor_init_anchor(GF_Compositor *compositor, GF_Node *node)
{
	AnchorStack *stack;
	GF_SAFEALLOC(stack, AnchorStack);

	stack->hdl.IsEnabled = anchor_is_enabled;
	stack->hdl.OnUserEvent = OnAnchor;
	stack->hdl.sensor = node;
	if (gf_node_get_tag(node)==TAG_MPEG4_Anchor) {
		((M_Anchor *)node)->on_activate = on_activate_anchor;
	}
	compositor->interaction_sensors++;
	gf_node_set_private(node, stack);
	gf_node_set_callback_function(node, TraverseAnchor);
}


typedef struct 
{
	GF_SensorHandler hdl;
	GF_Compositor *compositor;
	Fixed start_angle;
	GF_Matrix initial_matrix;
} DiscSensorStack;

static void DestroyDiscSensor(GF_Node *node, void *rs, Bool is_destroy)
{
	if (is_destroy) {
		DiscSensorStack *st = (DiscSensorStack *) gf_node_get_private(node);
		mpeg4_sensor_deleted(node, &st->hdl);
		free(st);
	}
}

static Bool ds_is_enabled(GF_Node *n)
{
	M_DiscSensor *ds = (M_DiscSensor *)n;
	return (ds->enabled || ds->isActive);
}


static void OnDiscSensor(GF_SensorHandler *sh, Bool is_over, GF_Event *ev, GF_Compositor *compositor)
{
	Bool is_mouse = (ev->type<=GF_EVENT_MOUSEWHEEL) ? 1 : 0;
	M_DiscSensor *ds = (M_DiscSensor *)sh->sensor;
	DiscSensorStack *stack = (DiscSensorStack *) gf_node_get_private(sh->sensor);
	
	if (ds->isActive && 
		(!ds->enabled 
		|| /*mouse*/((ev->type==GF_EVENT_MOUSEUP) && (ev->mouse.button==GF_MOUSE_LEFT)) 
		|| /*keyboar*/(!is_mouse && (!is_over|| ((ev->type==GF_EVENT_KEYDOWN) && (ev->key.key_code==GF_KEY_ENTER))) )
	) ) {
		if (ds->autoOffset) {
			ds->offset = ds->rotation_changed;
			/*that's an exposedField*/
			gf_node_event_out_str(sh->sensor, "offset");
		}
		ds->isActive = 0;
		gf_node_event_out_str(sh->sensor, "isActive");
		compositor->grabbed_sensor = 0;
	} else if (is_mouse) {
		if (!ds->isActive && (ev->type==GF_EVENT_MOUSEDOWN) && (ev->mouse.button==GF_MOUSE_LEFT)) {
			/*store inverse matrix*/
			gf_mx_copy(stack->initial_matrix, compositor->hit_local_to_world);
			stack->start_angle = gf_atan2(compositor->hit_local_point.y, compositor->hit_local_point.x);
			ds->isActive = 1;
			gf_node_event_out_str(sh->sensor, "isActive");
			compositor->grabbed_sensor = 1;
		}
		else if (ds->isActive) {
			GF_Ray loc_ray;
			Fixed rot;
			SFVec3f res;
			loc_ray = compositor->hit_world_ray;
			gf_mx_apply_ray(&stack->initial_matrix, &loc_ray);
			compositor_get_2d_plane_intersection(&loc_ray, &res);
		
			rot = gf_atan2(res.y, res.x) - stack->start_angle + ds->offset;
			if (ds->minAngle < ds->maxAngle) {
				/*FIXME this doesn't work properly*/
				if (rot < ds->minAngle) rot = ds->minAngle;
				if (rot > ds->maxAngle) rot = ds->maxAngle;
			}
			ds->rotation_changed = rot;
			gf_node_event_out_str(sh->sensor, "rotation_changed");
	   		ds->trackPoint_changed.x = res.x;
	   		ds->trackPoint_changed.y = res.y;
			gf_node_event_out_str(sh->sensor, "trackPoint_changed");
		}
	} else {
		if (!ds->isActive && is_over && (ev->type==GF_EVENT_KEYDOWN) && (ev->key.key_code==GF_KEY_ENTER)) {
			ds->isActive = 1;
			stack->start_angle = ds->offset;
			gf_node_event_out_str(sh->sensor, "isActive");
		}
		else if (ds->isActive && (ev->type==GF_EVENT_KEYDOWN)) {
			Fixed res;
			Fixed diff = (ev->key.flags & GF_KEY_MOD_SHIFT) ? GF_PI/8 : GF_PI/64;
			res = stack->start_angle;
			switch (ev->key.key_code) {
			case GF_KEY_LEFT: 
			case GF_KEY_UP: 
				res += -diff; 
				break;
			case GF_KEY_RIGHT: 
			case GF_KEY_DOWN: 
				res += diff;
				break;
			case GF_KEY_HOME:
				res = ds->offset;
				break;
			default: return;
			}
			if (ds->minAngle < ds->maxAngle) {
				/*FIXME this doesn't work properly*/
				if (res < ds->minAngle) res = ds->minAngle;
				if (res > ds->maxAngle) res = ds->maxAngle;
			}
			stack->start_angle = res;
			ds->rotation_changed = res;
			gf_node_event_out_str(sh->sensor, "rotation_changed");
		}
	}
}

static GF_SensorHandler *disc_sensor_get_handler(GF_Node *n)
{
	DiscSensorStack *st = (DiscSensorStack *)gf_node_get_private(n);
	return &st->hdl;
}

void compositor_init_disc_sensor(GF_Compositor *compositor, GF_Node *node)
{
	DiscSensorStack *st;
	GF_SAFEALLOC(st, DiscSensorStack);

	st->hdl.IsEnabled = ds_is_enabled;
	st->hdl.OnUserEvent = OnDiscSensor;
	st->hdl.sensor = node;
	st->compositor = compositor;
	compositor->interaction_sensors++;
	gf_node_set_private(node, st);
	gf_node_set_callback_function(node, DestroyDiscSensor);
}


typedef struct 
{
	SFVec2f start_drag;
	GF_Matrix initial_matrix;
	GF_Compositor *compositor;
	GF_SensorHandler hdl;
} PS2DStack;

static void DestroyPlaneSensor2D(GF_Node *node, void *rs, Bool is_destroy)
{
	if (is_destroy) {
		PS2DStack *st = (PS2DStack *) gf_node_get_private(node);
		mpeg4_sensor_deleted(node, &st->hdl);
		free(st);
	}
}

static Bool ps2D_is_enabled(GF_Node *n)
{
	M_PlaneSensor2D *ps2d = (M_PlaneSensor2D *)n;
	return (ps2d->enabled || ps2d->isActive);
}

static void OnPlaneSensor2D(GF_SensorHandler *sh, Bool is_over, GF_Event *ev, GF_Compositor *compositor)
{
	Bool is_mouse = (ev->type<=GF_EVENT_MOUSEWHEEL) ? 1 : 0;
	M_PlaneSensor2D *ps = (M_PlaneSensor2D *)sh->sensor;
	PS2DStack *stack = (PS2DStack *) gf_node_get_private(sh->sensor);


	if (ps->isActive && 
		(!ps->enabled
		|| /*mouse*/((ev->type==GF_EVENT_MOUSEUP) && (ev->mouse.button==GF_MOUSE_LEFT)) 
		|| /*keyboar*/(!is_mouse && (!is_over|| ((ev->type==GF_EVENT_KEYDOWN) && (ev->key.key_code==GF_KEY_ENTER))) )
	) ) {
		if (ps->autoOffset) {
			ps->offset = ps->translation_changed;
			gf_node_event_out_str(sh->sensor, "offset");
		}
		ps->isActive = 0;
		gf_node_event_out_str(sh->sensor, "isActive");
		compositor->grabbed_sensor = 0;
	} else if (is_mouse) {
		if (!ps->isActive && (ev->type==GF_EVENT_MOUSEDOWN) && (ev->mouse.button==GF_MOUSE_LEFT)) {
			gf_mx_copy(stack->initial_matrix, compositor->hit_local_to_world);
			stack->start_drag.x = compositor->hit_local_point.x - ps->offset.x;
			stack->start_drag.y = compositor->hit_local_point.y - ps->offset.y;
			ps->isActive = 1;
			gf_node_event_out_str(sh->sensor, "isActive");
			compositor->grabbed_sensor = 1;
		} else if (ps->isActive) {
			GF_Ray loc_ray;
			SFVec3f res;
			loc_ray = compositor->hit_world_ray;
			gf_mx_apply_ray(&stack->initial_matrix, &loc_ray);

			compositor_get_2d_plane_intersection(&loc_ray, &res);
			ps->trackPoint_changed.x = res.x;
			ps->trackPoint_changed.y = res.y;
			gf_node_event_out_str(sh->sensor, "trackPoint_changed");

			res.x -= stack->start_drag.x;
			res.y -= stack->start_drag.y;
			/*clip*/
			if (ps->minPosition.x <= ps->maxPosition.x) {
				if (res.x < ps->minPosition.x) res.x = ps->minPosition.x;
				if (res.x > ps->maxPosition.x) res.x = ps->maxPosition.x;
			}
			if (ps->minPosition.y <= ps->maxPosition.y) {
				if (res.y < ps->minPosition.y) res.y = ps->minPosition.y;
				if (res.y > ps->maxPosition.y) res.y = ps->maxPosition.y;
			}
			ps->translation_changed.x = res.x;
			ps->translation_changed.y = res.y;
			gf_node_event_out_str(sh->sensor, "translation_changed");
		}
	} else {
		if (!ps->isActive && is_over && (ev->type==GF_EVENT_KEYDOWN) && (ev->key.key_code==GF_KEY_ENTER)) {
			ps->isActive = 1;
			stack->start_drag = ps->offset;
			gf_node_event_out_str(sh->sensor, "isActive");
		}
		else if (ps->isActive && (ev->type==GF_EVENT_KEYDOWN)) {
			SFVec2f res;
			Fixed diff = (ev->key.flags & GF_KEY_MOD_SHIFT) ? 5*FIX_ONE : FIX_ONE;
			if (!gf_sg_use_pixel_metrics(gf_node_get_graph(sh->sensor)))
				diff = gf_divfix(diff, compositor->vp_width/2);
			res = stack->start_drag;
			switch (ev->key.key_code) {
			case GF_KEY_LEFT: res.x += -diff; break;
			case GF_KEY_RIGHT: res.x += diff; break;
			case GF_KEY_UP: res.y += diff; break;
			case GF_KEY_DOWN: res.y += -diff; break;
			case GF_KEY_HOME: res = ps->offset; break;
			default: return;
			}
			/*clip*/
			if (ps->minPosition.x <= ps->maxPosition.x) {
				if (res.x < ps->minPosition.x) res.x = ps->minPosition.x;
				if (res.x > ps->maxPosition.x) res.x = ps->maxPosition.x;
			}
			if (ps->minPosition.y <= ps->maxPosition.y) {
				if (res.y < ps->minPosition.y) res.y = ps->minPosition.y;
				if (res.y > ps->maxPosition.y) res.y = ps->maxPosition.y;
			}
			stack->start_drag = res;
			ps->translation_changed = res;
			gf_node_event_out_str(sh->sensor, "translation_changed");
		}
	}
}

static GF_SensorHandler *plane_sensor2d_get_handler(GF_Node *n)
{
	PS2DStack *st = (PS2DStack *)gf_node_get_private(n);
	return &st->hdl;
}

void compositor_init_plane_sensor2d(GF_Compositor *compositor, GF_Node *node)
{
	PS2DStack *st;
	GF_SAFEALLOC(st, PS2DStack);

	st->hdl.IsEnabled = ps2D_is_enabled;
	st->hdl.OnUserEvent = OnPlaneSensor2D;
	st->hdl.sensor = node;
	st->compositor = compositor;
	st->compositor->interaction_sensors++;
	gf_node_set_private(node, st);
	gf_node_set_callback_function(node, DestroyPlaneSensor2D);
}


typedef struct 
{
	Double last_time;
	GF_Compositor *compositor;
	GF_SensorHandler hdl;
} Prox2DStack;

static void DestroyProximitySensor2D(GF_Node *node, void *rs, Bool is_destroy)
{
	if (is_destroy) {
		Prox2DStack *st = (Prox2DStack *) gf_node_get_private(node);
		mpeg4_sensor_deleted(node, &st->hdl);
		free(st);
	}
}

static Bool prox2D_is_enabled(GF_Node *n)
{
	return ((M_ProximitySensor2D *) n)->enabled;
}

static Bool prox2D_is_in_sensor(Prox2DStack *st, M_ProximitySensor2D *ps, Fixed X, Fixed Y)
{
	if (X < ps->center.x - ps->size.x/2) return 0;
	if (X > ps->center.x + ps->size.x/2) return 0;
	if (Y < ps->center.y - ps->size.y/2) return 0;
	if (Y > ps->center.y + ps->size.y/2) return 0;
	return 1;
}

static void OnProximitySensor2D(GF_SensorHandler *sh, Bool is_over, GF_Event *ev, GF_Compositor *compositor)
{
	M_ProximitySensor2D *ps = (M_ProximitySensor2D *)sh->sensor;
	Prox2DStack *stack = (Prox2DStack *) gf_node_get_private(sh->sensor);
	
	assert(ps->enabled);
	
	if (is_over) {
		stack->last_time = gf_node_get_scene_time(sh->sensor);
		if (prox2D_is_in_sensor(stack, ps, compositor->hit_local_point.x, compositor->hit_local_point.y)) {
			ps->position_changed.x = compositor->hit_local_point.x;
			ps->position_changed.y = compositor->hit_local_point.y;
			gf_node_event_out_str(sh->sensor, "position_changed");

			if (!ps->isActive) {
				ps->isActive = 1;
				gf_node_event_out_str(sh->sensor, "isActive");
				ps->enterTime = stack->last_time;
				gf_node_event_out_str(sh->sensor, "enterTime");
			}
			return;
		}
	} 
	/*either we're not over the shape or we're not in sensor*/
	if (ps->isActive) {
		ps->exitTime = stack->last_time;
		gf_node_event_out_str(sh->sensor, "exitTime");
		ps->isActive = 0;
		gf_node_event_out_str(sh->sensor, "isActive");
	}
}

static GF_SensorHandler *proximity_sensor2d_get_handler(GF_Node *n)
{
	Prox2DStack *st = (Prox2DStack *)gf_node_get_private(n);
	return &st->hdl;
}


void compositor_init_proximity_sensor2d(GF_Compositor *compositor, GF_Node *node)
{
	Prox2DStack *st;
	GF_SAFEALLOC(st, Prox2DStack);

	st->hdl.IsEnabled = prox2D_is_enabled;
	st->hdl.OnUserEvent = OnProximitySensor2D;
	st->hdl.sensor = node;
	st->compositor = compositor;
	st->compositor->interaction_sensors++;
	gf_node_set_private(node, st);
	gf_node_set_callback_function(node, DestroyProximitySensor2D);
}

typedef struct 
{
	GF_SensorHandler hdl;
	Bool mouse_down;
	GF_Compositor *compositor;
} TouchSensorStack;

static void DestroyTouchSensor(GF_Node *node, void *rs, Bool is_destroy)
{
	if (is_destroy) {
		TouchSensorStack *st = (TouchSensorStack *) gf_node_get_private(node);
		mpeg4_sensor_deleted(node, &st->hdl);
		free(st);
	}
}

static Bool ts_is_enabled(GF_Node *n)
{
	return ((M_TouchSensor *) n)->enabled;
}

static void OnTouchSensor(GF_SensorHandler *sh, Bool is_over, GF_Event *ev, GF_Compositor *compositor)
{
	Bool is_mouse = (ev->type<=GF_EVENT_MOUSEWHEEL);
	M_TouchSensor *ts = (M_TouchSensor *)sh->sensor;
	
	/*this is not specified in VRML, however we consider that a de-enabled sensor will not sent deactivation events*/
	if (!ts->enabled) {
		if (ts->isActive) compositor->grabbed_sensor = 0;
		return;
	}

	/*isActive becomes false, send touch time*/
	if (ts->isActive) {
		if (
			/*mouse*/ ((ev->type==GF_EVENT_MOUSEUP) && (ev->mouse.button==GF_MOUSE_LEFT) ) 
		|| /*keyboard*/ ((ev->type==GF_EVENT_KEYUP) && (ev->key.key_code==GF_KEY_ENTER) ) 
		) {
			ts->touchTime = gf_node_get_scene_time(sh->sensor);
			gf_node_event_out_str(sh->sensor, "touchTime");
			ts->isActive = 0;
			gf_node_event_out_str(sh->sensor, "isActive");
			compositor->grabbed_sensor = 0;
		}
	}
	if (is_over != ts->isOver) {
		ts->isOver = is_over;
		gf_node_event_out_str(sh->sensor, "isOver");
	}
	if (!ts->isActive && is_over) {
		if (/*mouse*/ ((ev->type==GF_EVENT_MOUSEDOWN) && (ev->mouse.button==GF_MOUSE_LEFT)) 
			|| /*keyboard*/ ((ev->type==GF_EVENT_KEYDOWN) && (ev->key.key_code==GF_KEY_ENTER)) 
		) {
			ts->isActive = 1;
			gf_node_event_out_str(sh->sensor, "isActive");
			compositor->grabbed_sensor = 1;
		}
	}
	if (is_over && is_mouse) {
		/*THIS IS NOT CONFORMANT, the hitpoint should be in the touchsensor coordinate system, eg we 
		should store the matrix from TS -> shape and apply that ...*/
		ts->hitPoint_changed = compositor->hit_local_point;
		gf_node_event_out_str(sh->sensor, "hitPoint_changed");
		ts->hitNormal_changed = compositor->hit_normal;
		gf_node_event_out_str(sh->sensor, "hitNormal_changed");
		ts->hitTexCoord_changed = compositor->hit_texcoords;
		gf_node_event_out_str(sh->sensor, "hitTexCoord_changed");
	}
}

static GF_SensorHandler *touch_sensor_get_handler(GF_Node *n)
{
	TouchSensorStack *ts = (TouchSensorStack *)gf_node_get_private(n);
	return &ts->hdl;
}


void compositor_init_touch_sensor(GF_Compositor *compositor, GF_Node *node)
{
	TouchSensorStack *st;
	GF_SAFEALLOC(st, TouchSensorStack);

	st->hdl.IsEnabled = ts_is_enabled;
	st->hdl.OnUserEvent = OnTouchSensor;
	st->hdl.sensor = node;
	st->compositor = compositor;
	st->compositor->interaction_sensors++;
	gf_node_set_private(node, st);
	gf_node_set_callback_function(node, DestroyTouchSensor);
}

#ifndef GPAC_DISABLE_3D

void TraverseProximitySensor(GF_Node *node, void *rs, Bool is_destroy)
{
	SFVec3f user_pos, dist, up;
	SFRotation ori;
	GF_Matrix mx;
	GF_TraverseState *tr_state = (GF_TraverseState *)rs;
	M_ProximitySensor *ps = (M_ProximitySensor *)node;
	if (is_destroy) return;

	if (tr_state->traversing_mode==TRAVERSE_GET_BOUNDS) {
		/*work with twice bigger bbox to get sure we're notify when culled out*/
		gf_vec_add(tr_state->bbox.max_edge, ps->center, ps->size);
		gf_vec_diff(tr_state->bbox.min_edge, ps->center, ps->size);
		gf_bbox_refresh(&tr_state->bbox);
		return;
	} else if (!ps->enabled || (tr_state->traversing_mode != TRAVERSE_SORT) ) return;

	/*TODO FIXME - find a way to cache inverted matrix*/
	gf_mx_copy(mx, tr_state->model_matrix);
	gf_mx_inverse(&mx);
	/*get use pos in local coord system*/
	user_pos = tr_state->camera->position;
	gf_mx_apply_vec(&mx, &user_pos);
	gf_vec_diff(dist, user_pos, ps->center);

	if (dist.x<0) dist.x *= -1;
	if (dist.y<0) dist.y *= -1;
	if (dist.z<0) dist.z *= -1;

	if ((2*dist.x <= ps->size.x) 
		&& (2*dist.y <= ps->size.y)
		&& (2*dist.z <= ps->size.z) ) {

		if (!ps->isActive) {
			ps->isActive = 1;
			gf_node_event_out_str(node, "isActive");
			ps->enterTime = gf_node_get_scene_time(node);
			gf_node_event_out_str(node, "enterTime");
		}
		if ((ps->position_changed.x != user_pos.x)
			|| (ps->position_changed.y != user_pos.y)
			|| (ps->position_changed.z != user_pos.z) )
		{
			ps->position_changed = user_pos;
			gf_node_event_out_str(node, "position_changed");
		}
		dist = tr_state->camera->target;
		gf_mx_apply_vec(&mx, &dist);
		up = tr_state->camera->up;
		gf_mx_apply_vec(&mx, &up);
		ori = camera_get_orientation(user_pos, dist, tr_state->camera->up);
		if ((ori.q != ps->orientation_changed.q)
			|| (ori.x != ps->orientation_changed.x)
			|| (ori.y != ps->orientation_changed.y)
			|| (ori.z != ps->orientation_changed.z) ) {
			ps->orientation_changed = ori;
			gf_node_event_out_str(node, "orientation_changed");
		}
	} else if (ps->isActive) {
		ps->isActive = 0;
		gf_node_event_out_str(node, "isActive");
		ps->exitTime = gf_node_get_scene_time(node);
		gf_node_event_out_str(node, "exitTime");
	}
}

void compositor_init_proximity_sensor(GF_Compositor *compositor, GF_Node *node)
{
	gf_node_set_callback_function(node, TraverseProximitySensor);
}


typedef struct 
{
	SFVec3f start_drag;
	GF_Plane tracker;
	GF_Matrix initial_matrix;
	GF_Compositor *compositor;
	GF_SensorHandler hdl;
} PSStack;

static void DestroyPlaneSensor(GF_Node *node, void *rs, Bool is_destroy)
{
	if (is_destroy) {
		PSStack *st = (PSStack *) gf_node_get_private(node);
		mpeg4_sensor_deleted(node, &st->hdl);
		free(st);
	}
}

static Bool ps_is_enabled(GF_Node *n)
{
	M_PlaneSensor *ps = (M_PlaneSensor *)n;
	return (ps->enabled || ps->isActive);
}

static void OnPlaneSensor(GF_SensorHandler *sh, Bool is_over, GF_Event *ev, GF_Compositor *compositor)
{
	Bool is_mouse = (ev->type<=GF_EVENT_MOUSEWHEEL) ? 1 : 0;
	M_PlaneSensor *ps = (M_PlaneSensor *)sh->sensor;
	PSStack *stack = (PSStack *) gf_node_get_private(sh->sensor);

	
	if (ps->isActive && 
		( /*mouse*/((ev->type==GF_EVENT_MOUSEUP) && (ev->mouse.button==GF_MOUSE_LEFT)) 
		|| /*keyboar*/(!is_mouse && (!is_over|| ((ev->type==GF_EVENT_KEYDOWN) && (ev->key.key_code==GF_KEY_ENTER))) )
	) ) {
		if (ps->autoOffset) {
			ps->offset = ps->translation_changed;
			gf_node_event_out_str(sh->sensor, "offset");
		}
		ps->isActive = 0;
		gf_node_event_out_str(sh->sensor, "isActive");
		compositor->grabbed_sensor = 0;
	}
	/*mouse*/
	else if (is_mouse) {
		if (!ps->isActive && (ev->type==GF_EVENT_MOUSEDOWN) && (ev->mouse.button==GF_MOUSE_LEFT) ) {
			gf_mx_copy(stack->initial_matrix, compositor->hit_local_to_world);
			gf_vec_diff(stack->start_drag, compositor->hit_local_point, ps->offset);
			stack->tracker.normal.x = stack->tracker.normal.y = 0; stack->tracker.normal.z = FIX_ONE;
			stack->tracker.d = - gf_vec_dot(stack->start_drag, stack->tracker.normal);
			ps->isActive = 1;
			gf_node_event_out_str(sh->sensor, "isActive");
			compositor->grabbed_sensor = 1;
		}
		else if (ps->isActive) {
			GF_Ray loc_ray;
			SFVec3f res;
			loc_ray = compositor->hit_world_ray;
			gf_mx_apply_ray(&stack->initial_matrix, &loc_ray);
			gf_plane_intersect_line(&stack->tracker, &loc_ray.orig, &loc_ray.dir, &res);
			ps->trackPoint_changed = res;
			gf_node_event_out_str(sh->sensor, "trackPoint_changed");

			gf_vec_diff(res, res, stack->start_drag);
			/*clip*/
			if (ps->minPosition.x <= ps->maxPosition.x) {
				if (res.x < ps->minPosition.x) res.x = ps->minPosition.x;
				if (res.x > ps->maxPosition.x) res.x = ps->maxPosition.x;
			}
			if (ps->minPosition.y <= ps->maxPosition.y) {
				if (res.y < ps->minPosition.y) res.y = ps->minPosition.y;
				if (res.y > ps->maxPosition.y) res.y = ps->maxPosition.y;
			}
			ps->translation_changed = res;
			gf_node_event_out_str(sh->sensor, "translation_changed");
		}
	} else {
		if (!ps->isActive && is_over && (ev->type==GF_EVENT_KEYDOWN) && (ev->key.key_code==GF_KEY_ENTER)) {
			ps->isActive = 1;
			stack->start_drag = ps->offset;
			gf_node_event_out_str(sh->sensor, "isActive");
		}
		else if (ps->isActive && (ev->type==GF_EVENT_KEYDOWN)) {
			SFVec3f res;
			Fixed diff = (ev->key.flags & GF_KEY_MOD_SHIFT) ? 5*FIX_ONE : FIX_ONE;
			if (!gf_sg_use_pixel_metrics(gf_node_get_graph(sh->sensor)))
				diff = gf_divfix(diff, compositor->vp_width/2);

			res = stack->start_drag;
			switch (ev->key.key_code) {
			case GF_KEY_LEFT: res.x -= diff; break;
			case GF_KEY_RIGHT: res.x += diff; break;
			case GF_KEY_UP: res.y += diff; break;
			case GF_KEY_DOWN: res.y -= diff; break;
			case GF_KEY_HOME: res = ps->offset; break;
			default: return;
			}
			/*clip*/
			if (ps->minPosition.x <= ps->maxPosition.x) {
				if (res.x < ps->minPosition.x) res.x = ps->minPosition.x;
				if (res.x > ps->maxPosition.x) res.x = ps->maxPosition.x;
			}
			if (ps->minPosition.y <= ps->maxPosition.y) {
				if (res.y < ps->minPosition.y) res.y = ps->minPosition.y;
				if (res.y > ps->maxPosition.y) res.y = ps->maxPosition.y;
			}
			stack->start_drag = res;
			ps->translation_changed = res;
			gf_node_event_out_str(sh->sensor, "translation_changed");
		}
	}
}

static GF_SensorHandler *plane_sensor_get_handler(GF_Node *n)
{
	PSStack *st = (PSStack *)gf_node_get_private(n);
	return &st->hdl;
}

void compositor_init_plane_sensor(GF_Compositor *compositor, GF_Node *node)
{
	PSStack *st;
	GF_SAFEALLOC(st, PSStack);

	st->hdl.IsEnabled = ps_is_enabled;
	st->hdl.OnUserEvent = OnPlaneSensor;
	st->hdl.sensor = node;
	st->compositor = compositor;
	st->compositor->interaction_sensors++;
	gf_node_set_private(node, st);
	gf_node_set_callback_function(node, DestroyPlaneSensor);
}

typedef struct 
{
	GF_SensorHandler hdl;
	GF_Compositor *compositor;
	GF_Matrix init_matrix;
	Bool disk_mode;
	SFVec3f grab_start;
	GF_Plane yplane, zplane, xplane;
} CylinderSensorStack;

static void DestroyCylinderSensor(GF_Node *node, void *rs, Bool is_destroy)
{
	if (is_destroy) {
		CylinderSensorStack *st = (CylinderSensorStack *) gf_node_get_private(node);
		mpeg4_sensor_deleted(node, &st->hdl);
		free(st);
	}
}

static Bool cs_is_enabled(GF_Node *n)
{
	M_CylinderSensor *cs = (M_CylinderSensor *)n;
	return (cs->enabled || cs->isActive);
}

static void OnCylinderSensor(GF_SensorHandler *sh, Bool is_over, GF_Event *ev, GF_Compositor *compositor)
{
	Bool is_mouse = (ev->type<=GF_EVENT_MOUSEWHEEL) ? 1 : 0;
	M_CylinderSensor *cs = (M_CylinderSensor *)sh->sensor;
	CylinderSensorStack *st = (CylinderSensorStack *) gf_node_get_private(sh->sensor);

	if (cs->isActive && (!cs->enabled 
		|| /*mouse*/((ev->type==GF_EVENT_MOUSEUP) && (ev->mouse.button==GF_MOUSE_LEFT)) 
		|| /*keyboar*/(!is_mouse && (!is_over|| ((ev->type==GF_EVENT_KEYDOWN) && (ev->key.key_code==GF_KEY_ENTER))))
	) ) {
		if (cs->autoOffset) {
			cs->offset = cs->rotation_changed.q;
			gf_node_event_out_str(sh->sensor, "offset");
		}
		cs->isActive = 0;
		gf_node_event_out_str(sh->sensor, "isActive");
		compositor->grabbed_sensor = 0;
	}
	else if (is_mouse) {
		if (!cs->isActive && (ev->type==GF_EVENT_MOUSEDOWN) && (ev->mouse.button==GF_MOUSE_LEFT)) {
			GF_Ray r;
			SFVec3f yaxis;
			Fixed acute, reva;
			SFVec3f bearing;

			gf_mx_copy(st->init_matrix, compositor->hit_world_to_local);
			/*get initial angle & check disk mode*/
			r = compositor->hit_world_ray;
			gf_vec_add(r.dir, r.orig, r.dir);
			gf_mx_apply_vec(&compositor->hit_world_to_local, &r.orig);
			gf_mx_apply_vec(&compositor->hit_world_to_local, &r.dir);
			gf_vec_diff(bearing, r.orig, r.dir);
			gf_vec_norm(&bearing);
			yaxis.x = yaxis.z = 0;
			yaxis.y = FIX_ONE;
			acute = gf_vec_dot(bearing, yaxis);
			if (acute < -FIX_ONE) acute = -FIX_ONE; 
			else if (acute > FIX_ONE) acute = FIX_ONE;
			acute = gf_acos(acute);
			reva = ABS(GF_PI - acute);
			if (reva<acute) acute = reva;
			st->disk_mode = (acute < cs->diskAngle) ? 1 : 0;

			st->grab_start = compositor->hit_local_point;
			/*cos we're lazy*/
			st->yplane.d = 0; st->yplane.normal.x = st->yplane.normal.z = st->yplane.normal.y = 0;
			st->zplane = st->xplane = st->yplane;
			st->xplane.normal.x = FIX_ONE;
			st->yplane.normal.y = FIX_ONE;
			st->zplane.normal.z = FIX_ONE;

			cs->rotation_changed.x = 0;
			cs->rotation_changed.y = FIX_ONE;
			cs->rotation_changed.z = 0;

			cs->isActive = 1;
			gf_node_event_out_str(sh->sensor, "isActive");
			compositor->grabbed_sensor = 1;
		}
		else if (cs->isActive) {
			GF_Ray r;
			Fixed radius, rot;
			SFVec3f dir1, dir2, cx;

			if (is_over) {
				cs->trackPoint_changed = compositor->hit_local_point;
				gf_node_event_out_str(sh->sensor, "trackPoint_changed");
			} else {
				GF_Plane project_to;
				r = compositor->hit_world_ray;
				gf_mx_apply_ray(&st->init_matrix, &r);

				/*no intersection, use intersection with "main" fronting plane*/
				if ( ABS(r.dir.z) > ABS(r.dir.y)) {
					if (ABS(r.dir.x) > ABS(r.dir.x)) project_to = st->xplane;
					else project_to = st->zplane;
				} else project_to = st->yplane;
				if (!gf_plane_intersect_line(&project_to, &r.orig, &r.dir, &compositor->hit_local_point)) return;
			}

  			dir1.x = compositor->hit_local_point.x; dir1.y = 0; dir1.z = compositor->hit_local_point.z;
			if (st->disk_mode) {
				radius = FIX_ONE;
			} else {
				radius = gf_vec_len(dir1);
			}
			gf_vec_norm(&dir1);
       		dir2.x = st->grab_start.x; dir2.y = 0; dir2.z = st->grab_start.z;
			gf_vec_norm(&dir2);
			cx = gf_vec_cross(dir2, dir1);
			gf_vec_norm(&cx);
			if (gf_vec_len(cx)<FIX_EPSILON) return;
			rot = gf_mulfix(radius, gf_acos(gf_vec_dot(dir2, dir1)) );
			if (fabs(cx.y + FIX_ONE) < FIX_EPSILON) rot = -rot;
			if (cs->autoOffset) rot += cs->offset;

			if (cs->minAngle < cs->maxAngle) {
				if (rot < cs->minAngle) rot = cs->minAngle;
				else if (rot > cs->maxAngle) rot = cs->maxAngle;
			}
			cs->rotation_changed.q = rot;
			gf_node_event_out_str(sh->sensor, "rotation_changed");
		} 
	} else {
		if (!cs->isActive && is_over && (ev->type==GF_EVENT_KEYDOWN) && (ev->key.key_code==GF_KEY_ENTER)) {
			cs->isActive = 1;
			cs->rotation_changed.q = cs->offset;
			cs->rotation_changed.x = cs->rotation_changed.z = 0;
			cs->rotation_changed.y = FIX_ONE;
			gf_node_event_out_str(sh->sensor, "isActive");
		}
		else if (cs->isActive && (ev->type==GF_EVENT_KEYDOWN)) {
			SFFloat res;
			Fixed diff = (ev->key.flags & GF_KEY_MOD_SHIFT) ? GF_PI/8 : GF_PI/64;

			res = cs->rotation_changed.q;
			switch (ev->key.key_code) {
			case GF_KEY_LEFT: res -= diff; break;
			case GF_KEY_RIGHT: res += diff; break;
			case GF_KEY_HOME: res = cs->offset; break;
			default: return;
			}
			/*clip*/
			if (cs->minAngle <= cs->maxAngle) {
				if (res < cs->minAngle) res = cs->minAngle;
				if (res > cs->maxAngle) res = cs->maxAngle;
			}
			cs->rotation_changed.q = res;
			gf_node_event_out_str(sh->sensor, "rotation_changed");
		}
	}
}

static GF_SensorHandler *cylinder_sensor_get_handler(GF_Node *n)
{
	CylinderSensorStack *st = (CylinderSensorStack  *)gf_node_get_private(n);
	return &st->hdl;
}

void compositor_init_cylinder_sensor(GF_Compositor *compositor, GF_Node *node)
{
	CylinderSensorStack *st;
	GF_SAFEALLOC(st, CylinderSensorStack);

	st->hdl.IsEnabled = cs_is_enabled;
	st->hdl.OnUserEvent = OnCylinderSensor;
	st->hdl.sensor = node;
	st->compositor = compositor;
	st->compositor->interaction_sensors++;
	gf_node_set_private(node, st);
	gf_node_set_callback_function(node, DestroyCylinderSensor);
}


typedef struct 
{
	GF_SensorHandler hdl;
	GF_Compositor *compositor;
	Fixed radius;
	/*center in world coords */
	SFVec3f grab_vec, center;
} SphereSensorStack;

static void DestroySphereSensor(GF_Node *node, void *rs, Bool is_destroy)
{
	if (is_destroy) {
		SphereSensorStack *st = (SphereSensorStack *) gf_node_get_private(node);
		mpeg4_sensor_deleted(node, &st->hdl);
		free(st);
	}
}

static Bool sphere_is_enabled(GF_Node *n)
{
	M_SphereSensor *ss = (M_SphereSensor *)n;
	return (ss->enabled || ss->isActive);
}

static void OnSphereSensor(GF_SensorHandler *sh, Bool is_over, GF_Event *ev, GF_Compositor *compositor)
{
	Bool is_mouse = (ev->type<=GF_EVENT_MOUSEWHEEL) ? 1 : 0;
	M_SphereSensor *sphere = (M_SphereSensor *)sh->sensor;
	SphereSensorStack *st = (SphereSensorStack *) gf_node_get_private(sh->sensor);


	if (sphere->isActive && (!sphere->enabled 
		|| /*mouse*/((ev->type==GF_EVENT_MOUSEUP) && (ev->mouse.button==GF_MOUSE_LEFT)) 
		|| /*keyboar*/(!is_mouse && (!is_over|| ((ev->type==GF_EVENT_KEYDOWN) && (ev->key.key_code==GF_KEY_ENTER))))
	) ) {
		if (sphere->autoOffset) {
			sphere->offset = sphere->rotation_changed;
			gf_node_event_out_str(sh->sensor, "offset");
		}
		sphere->isActive = 0;
		gf_node_event_out_str(sh->sensor, "isActive");
		compositor->grabbed_sensor = 0;
	}
	else if (is_mouse) {
		if (!sphere->isActive && (ev->type==GF_EVENT_MOUSEDOWN) && (ev->mouse.button==GF_MOUSE_LEFT)) {
			st->center.x = st->center.y = st->center.z = 0;
			gf_mx_apply_vec(&compositor->hit_local_to_world, &st->center);
			st->radius = gf_vec_len(compositor->hit_local_point);
			if (!st->radius) st->radius = FIX_ONE;
			st->grab_vec = gf_vec_scale(compositor->hit_local_point, gf_invfix(st->radius));

			sphere->isActive = 1;
			gf_node_event_out_str(sh->sensor, "isActive");
			compositor->grabbed_sensor = 1;
		}
		else if (sphere->isActive) {
			SFVec3f vec, axis;
			SFVec4f q1, q2;
			SFRotation r;
			Fixed cl;
			if (is_over) {
				sphere->trackPoint_changed = compositor->hit_local_point;
				gf_node_event_out_str(sh->sensor, "trackPoint_changed");
			} else {
				GF_Ray r;
				r = compositor->hit_world_ray;
				gf_mx_apply_ray(&compositor->hit_world_to_local, &r);
				if (!gf_ray_hit_sphere(&r, NULL, st->radius, &compositor->hit_local_point)) {
					vec.x = vec.y = vec.z = 0;
					/*doesn't work properly...*/
					compositor->hit_local_point = gf_closest_point_to_line(r.orig, r.dir, vec);
				}
			}

			vec = gf_vec_scale(compositor->hit_local_point, gf_invfix(st->radius));
			axis = gf_vec_cross(st->grab_vec, vec);
			cl = gf_vec_len(axis);

			if (cl < -FIX_ONE) cl = -FIX_ONE;
			else if (cl > FIX_ONE) cl = FIX_ONE;
			r.q = gf_asin(cl);
			if (gf_vec_dot(st->grab_vec, vec) < 0) r.q += GF_PI / 2;

			gf_vec_norm(&axis);
			r.x = axis.x; r.y = axis.y; r.z = axis.z;
			q1 = gf_quat_from_rotation(r);
			if (sphere->autoOffset) {
				q2 = gf_quat_from_rotation(sphere->offset);
				q1 = gf_quat_multiply(&q1, &q2);
			}
			sphere->rotation_changed = gf_quat_to_rotation(&q1);
			gf_node_event_out_str(sh->sensor, "rotation_changed");
		} 
	} else {
		if (!sphere->isActive && is_over && (ev->type==GF_EVENT_KEYDOWN) && (ev->key.key_code==GF_KEY_ENTER)) {
			sphere->isActive = 1;
			sphere->rotation_changed = sphere->offset;
			gf_node_event_out_str(sh->sensor, "isActive");
		}
		else if (sphere->isActive && (ev->type==GF_EVENT_KEYDOWN)) {
			SFVec4f res, rot;
			Fixed diff = GF_PI/64;

			res = sphere->rotation_changed;
			switch (ev->key.key_code) {
			case GF_KEY_LEFT: 
				diff = -diff;
			case GF_KEY_RIGHT: 
				rot.x = 0; rot.y = FIX_ONE; rot.z = 0; rot.q = diff;
				res = gf_quat_from_rotation(res);
				rot = gf_quat_from_rotation(rot);
				rot = gf_quat_multiply(&rot, &res);
				res = gf_quat_to_rotation(&rot);
				break;
			case GF_KEY_DOWN:
				diff = -diff;
			case GF_KEY_UP:
				if (ev->key.flags & GF_KEY_MOD_SHIFT) {
					rot.x = 0; rot.z = FIX_ONE; 
				} else {
					rot.x = FIX_ONE; rot.z = 0; 
				}
				rot.y = 0; rot.q = diff;
				res = gf_quat_from_rotation(res);
				rot = gf_quat_from_rotation(rot);
				rot = gf_quat_multiply(&rot, &res);
				res = gf_quat_to_rotation(&rot);
				break;
			case GF_KEY_HOME: res = sphere->offset; break;
			default: return;
			}
			sphere->rotation_changed = res;
			gf_node_event_out_str(sh->sensor, "rotation_changed");
		}
	}

}

static GF_SensorHandler *sphere_get_handler(GF_Node *n)
{
	SphereSensorStack *st = (SphereSensorStack *)gf_node_get_private(n);
	return &st->hdl;
}

void compositor_init_sphere_sensor(GF_Compositor *compositor, GF_Node *node)
{
	SphereSensorStack *st;
	GF_SAFEALLOC(st, SphereSensorStack);

	st->hdl.IsEnabled = sphere_is_enabled;
	st->hdl.OnUserEvent = OnSphereSensor;
	st->hdl.sensor = node;
	st->compositor = compositor;
	st->compositor->interaction_sensors++;
	gf_node_set_private(node, st);
	gf_node_set_callback_function(node, DestroySphereSensor);
}

void TraverseVisibilitySensor(GF_Node *node, void *rs, Bool is_destroy)
{
	GF_TraverseState *tr_state = (GF_TraverseState *)rs;
	M_VisibilitySensor *vs = (M_VisibilitySensor *)node;
	
	if (is_destroy || !vs->enabled) return;

	if (tr_state->traversing_mode==TRAVERSE_GET_BOUNDS) {
		/*work with twice bigger bbox to get sure we're notify when culled out*/
		gf_vec_add(tr_state->bbox.max_edge, vs->center, vs->size);
		gf_vec_diff(tr_state->bbox.min_edge, vs->center, vs->size);
		gf_bbox_refresh(&tr_state->bbox);

	} else if (tr_state->traversing_mode==TRAVERSE_SORT) {
		Bool visible;
		u32 cull_flag;
		GF_BBox bbox;
		SFVec3f s;
		s = gf_vec_scale(vs->size, FIX_ONE/2);
		/*cull with normal bbox*/
		gf_vec_add(bbox.max_edge, vs->center, s);
		gf_vec_diff(bbox.min_edge, vs->center, s);
		gf_bbox_refresh(&bbox);
		cull_flag = tr_state->cull_flag;
		tr_state->cull_flag = CULL_INTERSECTS;
		visible = visual_3d_node_cull(tr_state, &bbox, 0);
		tr_state->cull_flag = cull_flag;

		if (visible && !vs->isActive) {
			vs->isActive = 1;
			gf_node_event_out_str(node, "isActive");
			vs->enterTime = gf_node_get_scene_time(node);
			gf_node_event_out_str(node, "enterTime");
		}
		else if (!visible && vs->isActive) {
			vs->isActive = 0;
			gf_node_event_out_str(node, "isActive");
			vs->exitTime = gf_node_get_scene_time(node);
			gf_node_event_out_str(node, "exitTime");
		}
	}
}

void compositor_init_visibility_sensor(GF_Compositor *compositor, GF_Node *node)
{
	gf_node_set_callback_function(node, TraverseVisibilitySensor);
}

#endif



Bool compositor_mpeg4_is_sensor_node(GF_Node *node)
{
	switch (gf_node_get_tag(node)) {
	case TAG_MPEG4_DiscSensor: 
	case TAG_MPEG4_PlaneSensor2D: 
	case TAG_MPEG4_ProximitySensor2D:
	case TAG_MPEG4_TouchSensor:
	case TAG_X3D_TouchSensor:
#ifndef GPAC_DISABLE_3D
	case TAG_MPEG4_CylinderSensor: 
	case TAG_X3D_CylinderSensor: 
	case TAG_MPEG4_PlaneSensor: 
	case TAG_X3D_PlaneSensor: 
	case TAG_MPEG4_ProximitySensor: 
	case TAG_X3D_ProximitySensor: 
	case TAG_MPEG4_SphereSensor: 
	case TAG_X3D_SphereSensor: 
	case TAG_MPEG4_VisibilitySensor: 
	case TAG_X3D_VisibilitySensor: 
#endif
		return 1;
	/*NOTE: anchor is not considered as a child sensor node when picking sensors*/
	default:
		return 0;
	}
}

GF_SensorHandler *compositor_mpeg4_get_sensor_handler(GF_Node *n)
{
	GF_SensorHandler *hs;

	switch (gf_node_get_tag(n)) {
	/*anchor is not considered as a child sensor node when picking sensors*/
	case TAG_MPEG4_Anchor: 
	case TAG_X3D_Anchor: 
		hs = gf_sc_anchor_get_handler(n); 
		break;
	case TAG_MPEG4_DiscSensor: 
		hs = disc_sensor_get_handler(n); 
		break;
	case TAG_MPEG4_PlaneSensor2D: 
		hs = plane_sensor2d_get_handler(n); 
		break;
	case TAG_MPEG4_ProximitySensor2D:
		hs = proximity_sensor2d_get_handler(n);
		break;
	case TAG_MPEG4_TouchSensor:
	case TAG_X3D_TouchSensor:
		hs = touch_sensor_get_handler(n);
		break;
#ifndef GPAC_DISABLE_3D
	case TAG_MPEG4_CylinderSensor: 
	case TAG_X3D_CylinderSensor: 
		hs = cylinder_sensor_get_handler(n);
		break;
	case TAG_MPEG4_PlaneSensor: 
	case TAG_X3D_PlaneSensor: 
		hs = plane_sensor_get_handler(n);
		break;
	case TAG_MPEG4_SphereSensor: 
	case TAG_X3D_SphereSensor: 
		hs = sphere_get_handler(n);
		break;
#endif
	default: return NULL;
	}
	if (hs && hs->IsEnabled(n)) return hs;
	return NULL;
}

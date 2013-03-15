/*
* Copyright (c) 2011 Samsung Electronics Co., Ltd All Rights Reserved
*
* Licensed under the Apache License, Version 2.0 (the "License");
* you may not use this file except in compliance with the License.
* You may obtain a copy of the License at
*
* http://www.apache.org/licenses/LICENSE-2.0
*
* Unless required by applicable law or agreed to in writing, software
* distributed under the License is distributed on an "AS IS" BASIS,
* WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
* See the License for the specific language governing permissions and
* limitations under the License.
*/

#include <location/location.h>
#include <location/location-types.h>
#include <location/location-map-service.h>

#include "route.h"
#include "route_service.h"
#include "route_private.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Route module
 */
int route_clone(route_h * cloned_route, route_h origin)
{
	ROUTE_NULL_ARG_CHECK(cloned_route);
	ROUTE_NULL_ARG_CHECK(origin);

	route_s *handle = (route_s *) origin;
	if (NULL == handle->route) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_INVALID_PARAMETER);
	}

	route_s *cloned = (route_s *) malloc(sizeof(route_s));
	if (cloned == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_OUT_OF_MEMORY);
	}

	cloned->route = location_route_copy(handle->route);
	if (cloned->route == NULL) {
		free(cloned);
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_OUT_OF_MEMORY);
	}
	cloned->request_id = handle->request_id;

	*cloned_route = (route_h) cloned;

	return ROUTE_ERROR_NONE;
}

int route_destroy(route_h route)
{
	ROUTE_NULL_ARG_CHECK(route);

	route_s *handle = (route_s *) route;
	location_route_free(handle->route);
	handle->request_id = 0;
	free(handle);
	handle = NULL;

	return ROUTE_ERROR_NONE;
}

int route_get_request_id(route_h route, int *id)
{
	ROUTE_NULL_ARG_CHECK(route);
	ROUTE_NULL_ARG_CHECK(id);

	route_s *handle = (route_s *) route;
	*id = handle->request_id;

	return ROUTE_ERROR_NONE;
}

int route_get_origin(route_h route, location_coords_s * origin)
{
	ROUTE_NULL_ARG_CHECK(route);
	ROUTE_NULL_ARG_CHECK(origin);

	route_s *handle = (route_s *) route;
	LocationPosition *start = location_route_get_origin(handle->route);
	if (start == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_RESULT_NOT_FOUND);
	}

	origin->latitude = start->latitude;
	origin->longitude = start->longitude;

	return ROUTE_ERROR_NONE;
}

int route_get_destination(route_h route, location_coords_s * destination)
{
	ROUTE_NULL_ARG_CHECK(route);
	ROUTE_NULL_ARG_CHECK(destination);

	route_s *handle = (route_s *) route;
	LocationPosition *end = location_route_get_destination(handle->route);
	if (end == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_RESULT_NOT_FOUND);
	}

	destination->latitude = end->latitude;
	destination->longitude = end->longitude;

	return ROUTE_ERROR_NONE;
}

int route_get_geometry_bounding_box(route_h route, location_coords_s * top_left, location_coords_s * bottom_right)
{
	ROUTE_NULL_ARG_CHECK(route);
	ROUTE_NULL_ARG_CHECK(top_left);
	ROUTE_NULL_ARG_CHECK(bottom_right);

	route_s *handle = (route_s *) route;
	LocationBoundary *bbox = location_route_get_bounding_box(handle->route);
	if (bbox == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_RESULT_NOT_FOUND);
	}

	top_left->latitude = bbox->rect.left_top->latitude;
	top_left->longitude = bbox->rect.left_top->longitude;
	bottom_right->latitude = bbox->rect.right_bottom->latitude;
	bottom_right->longitude = bbox->rect.right_bottom->longitude;

	return ROUTE_ERROR_NONE;
}

int route_get_distance_unit(route_h route, route_distance_unit_e * unit)
{
	ROUTE_NULL_ARG_CHECK(route);
	ROUTE_NULL_ARG_CHECK(unit);

	char *M = "M";
	char *KM = "KM";
	char *FT = "FT";
	char *YD = "YD";
	char *MI = "MI";

	route_s *handle = (route_s *) route;
	char *dist_unit = (char *)location_route_get_distance_unit(handle->route);
	if (dist_unit == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_SERVICE_NOT_AVAILABLE);
	}

	if (strcmp(dist_unit, M) == 0) {
		*unit = ROUTE_DISTANCE_UNIT_M;
	} else if (strcmp(dist_unit, KM) == 0) {
		*unit = ROUTE_DISTANCE_UNIT_KM;
	} else if (strcmp(dist_unit, FT) == 0) {
		*unit = ROUTE_DISTANCE_UNIT_FT;
	} else if (strcmp(dist_unit, YD) == 0) {
		*unit = ROUTE_DISTANCE_UNIT_YD;
	} else if (strcmp(dist_unit, MI) == 0) {
		*unit = ROUTE_DISTANCE_UNIT_MI;
	}

	return ROUTE_ERROR_NONE;
}

int route_get_total_distance(route_h route, double *distance)
{
	ROUTE_NULL_ARG_CHECK(route);
	ROUTE_NULL_ARG_CHECK(distance);

	route_s *handle = (route_s *) route;
	double dist = (double)location_route_get_total_distance(handle->route);

	*distance = dist;

	return ROUTE_ERROR_NONE;
}

int route_get_total_duration(route_h route, long *duration)
{
	ROUTE_NULL_ARG_CHECK(route);
	ROUTE_NULL_ARG_CHECK(duration);

	route_s *handle = (route_s *) route;
	long dur = (long)location_route_get_total_duration(handle->route);

	*duration = dur;

	return ROUTE_ERROR_NONE;
}

int route_foreach_properties(route_h route, route_property_cb callback, void *user_data)
{
	ROUTE_NULL_ARG_CHECK(route);
	ROUTE_NULL_ARG_CHECK(callback);

	route_s *handle = (route_s *) route;
	GList *key_list = location_route_get_property_key(handle->route);

	while (key_list) {
		char *key = key_list->data;
		char *value = NULL;
		if (key != NULL && (value = (char *)location_route_get_property(handle->route, key)) != NULL) {
			if (callback(key, value, user_data) == false) {
				break;
			}
		}
		key_list = key_list->next;
	}

	return ROUTE_ERROR_NONE;
}

int route_foreach_segments(route_h route, route_segment_cb callback, void *user_data)
{
	ROUTE_NULL_ARG_CHECK(route);
	ROUTE_NULL_ARG_CHECK(callback);

	route_s *handle = (route_s *) route;
	GList *seg_list = location_route_get_route_segment(handle->route);

	while (seg_list) {
		route_segment_s *segment = (route_segment_s *) malloc(sizeof(route_segment_s));
		segment->segment = seg_list->data;

		if (callback(segment, user_data) == false) {
			free(segment);
			break;
		}
		seg_list = seg_list->next;
		free(segment);
	}

	return ROUTE_ERROR_NONE;
}

/*
 * Route segment module
 */
int route_segment_clone(route_segment_h * cloned_segment, route_segment_h origin)
{
	ROUTE_NULL_ARG_CHECK(cloned_segment);
	ROUTE_NULL_ARG_CHECK(origin);

	route_segment_s *handle = (route_segment_s *) origin;
	if (NULL == handle->segment) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_INVALID_PARAMETER);
	}

	route_segment_s *cloned = (route_segment_s *) malloc(sizeof(route_segment_s));
	if (cloned == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_OUT_OF_MEMORY);
	}

	cloned->segment = location_route_segment_copy(handle->segment);
	if (cloned->segment == NULL) {
		free(cloned);
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_OUT_OF_MEMORY);
	}

	*cloned_segment = (route_segment_h) cloned;

	return ROUTE_ERROR_NONE;
}

int route_segment_destroy(route_segment_h segment)
{
	ROUTE_NULL_ARG_CHECK(segment);

	route_segment_s *handle = (route_segment_s *) segment;
	location_route_segment_free(handle->segment);
	free(handle);
	handle = NULL;

	return ROUTE_ERROR_NONE;
}

int route_segment_get_origin(route_segment_h segment, location_coords_s * origin)
{
	ROUTE_NULL_ARG_CHECK(segment);
	ROUTE_NULL_ARG_CHECK(origin);

	route_segment_s *handle = (route_segment_s *) segment;
	LocationPosition *start = location_route_segment_get_start_point(handle->segment);
	if (start == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_RESULT_NOT_FOUND);
	}

	origin->latitude = start->latitude;
	origin->longitude = start->longitude;

	return ROUTE_ERROR_NONE;
}

int route_segment_get_destination(route_segment_h segment, location_coords_s * destination)
{
	ROUTE_NULL_ARG_CHECK(segment);
	ROUTE_NULL_ARG_CHECK(destination);

	route_segment_s *handle = (route_segment_s *) segment;
	LocationPosition *end = location_route_segment_get_end_point(handle->segment);
	if (end == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_RESULT_NOT_FOUND);
	}

	destination->latitude = end->latitude;
	destination->longitude = end->longitude;

	return ROUTE_ERROR_NONE;
}

int route_segment_get_geometry_bounding_box(route_segment_h segment,
					    location_coords_s * top_left, location_coords_s * bottom_right)
{
	ROUTE_NULL_ARG_CHECK(segment);
	ROUTE_NULL_ARG_CHECK(top_left);
	ROUTE_NULL_ARG_CHECK(bottom_right);

	route_segment_s *handle = (route_segment_s *) segment;
	LocationBoundary *bbox = location_route_segment_get_bounding_box(handle->segment);
	if (bbox == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_RESULT_NOT_FOUND);
	}

	top_left->latitude = bbox->rect.left_top->latitude;
	top_left->longitude = bbox->rect.left_top->longitude;
	bottom_right->latitude = bbox->rect.right_bottom->latitude;
	bottom_right->longitude = bbox->rect.right_bottom->longitude;

	return ROUTE_ERROR_NONE;
}

int route_segment_get_distance(route_segment_h segment, double *distance)
{
	ROUTE_NULL_ARG_CHECK(segment);
	ROUTE_NULL_ARG_CHECK(distance);

	route_segment_s *handle = (route_segment_s *) segment;
	double dist = (double)location_route_segment_get_distance(handle->segment);

	*distance = dist;

	return ROUTE_ERROR_NONE;
}

int route_segment_get_duration(route_segment_h segment, long *duration)
{
	ROUTE_NULL_ARG_CHECK(segment);
	ROUTE_NULL_ARG_CHECK(duration);

	route_segment_s *handle = (route_segment_s *) segment;
	long dur = (long)location_route_segment_get_duration(handle->segment);

	*duration = dur;

	return ROUTE_ERROR_NONE;
}

int route_segment_foreach_properties(route_segment_h segment, route_segment_property_cb callback, void *user_data)
{
	ROUTE_NULL_ARG_CHECK(segment);
	ROUTE_NULL_ARG_CHECK(callback);

	route_segment_s *handle = (route_segment_s *) segment;
	GList *key_list = location_route_segment_get_property_key(handle->segment);

	while (key_list) {
		char *key = key_list->data;
		char *value = NULL;
		if (key != NULL && (value = (char *)location_route_segment_get_property(handle->segment, key)) != NULL) {
			if (callback(key, value, user_data) == false) {
				break;
			}
		}
		key_list = key_list->next;
	}

	return ROUTE_ERROR_NONE;
}

int route_segment_foreach_steps(route_segment_h segment, route_segment_step_cb callback, void *user_data)
{
	ROUTE_NULL_ARG_CHECK(segment);
	ROUTE_NULL_ARG_CHECK(callback);

	route_segment_s *handle = (route_segment_s *) segment;
	GList *step_list = location_route_segment_get_route_step(handle->segment);

	while (step_list) {
		route_step_s *step = (route_step_s *) malloc(sizeof(route_step_s));
		step->step = step_list->data;

		if (callback(step, user_data) == false) {
			free(step);
			break;
		}
		step_list = step_list->next;
		free(step);
	}

	return ROUTE_ERROR_NONE;
}

/*
 * Route step module
 */
int route_step_clone(route_step_h * cloned_step, route_step_h origin)
{
	ROUTE_NULL_ARG_CHECK(cloned_step);
	ROUTE_NULL_ARG_CHECK(origin);

	route_step_s *handle = (route_step_s *) origin;
	if (NULL == handle->step) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_INVALID_PARAMETER);
	}

	route_step_s *cloned = (route_step_s *) malloc(sizeof(route_step_s));
	if (cloned == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_OUT_OF_MEMORY);
	}

	cloned->step = location_route_step_copy(handle->step);
	if (cloned->step == NULL) {
		free(cloned);
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_OUT_OF_MEMORY);
	}

	*cloned_step = (route_step_h) cloned;

	return ROUTE_ERROR_NONE;
}

int route_step_destroy(route_step_h step)
{
	ROUTE_NULL_ARG_CHECK(step);

	route_step_s *handle = (route_step_s *) step;
	location_route_step_free(handle->step);
	free(handle);
	handle = NULL;

	return ROUTE_ERROR_NONE;

}

int route_step_get_origin(route_step_h step, location_coords_s * origin)
{
	ROUTE_NULL_ARG_CHECK(step);
	ROUTE_NULL_ARG_CHECK(origin);

	route_step_s *handle = (route_step_s *) step;
	LocationPosition *start = location_route_step_get_start_point(handle->step);
	if (start == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_RESULT_NOT_FOUND);
	}

	origin->latitude = start->latitude;
	origin->longitude = start->longitude;

	return ROUTE_ERROR_NONE;
}

int route_step_get_destination(route_step_h step, location_coords_s * destination)
{
	ROUTE_NULL_ARG_CHECK(step);
	ROUTE_NULL_ARG_CHECK(destination);

	route_step_s *handle = (route_step_s *) step;
	LocationPosition *end = location_route_step_get_end_point(handle->step);
	if (end == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_RESULT_NOT_FOUND);
	}

	destination->latitude = end->latitude;
	destination->longitude = end->longitude;

	return ROUTE_ERROR_NONE;
}

int route_step_get_geometry_bounding_box(route_step_h step, location_coords_s * top_left, location_coords_s * bottom_right)
{
	ROUTE_NULL_ARG_CHECK(step);
	ROUTE_NULL_ARG_CHECK(top_left);
	ROUTE_NULL_ARG_CHECK(bottom_right);

	route_step_s *handle = (route_step_s *) step;
	LocationBoundary *bbox = location_route_step_get_bounding_box(handle->step);
	if (bbox == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_RESULT_NOT_FOUND);
	}

	top_left->latitude = bbox->rect.left_top->latitude;
	top_left->longitude = bbox->rect.left_top->longitude;
	bottom_right->latitude = bbox->rect.right_bottom->latitude;
	bottom_right->longitude = bbox->rect.right_bottom->longitude;

	return ROUTE_ERROR_NONE;
}

int route_step_get_distance(route_step_h step, double *distance)
{
	ROUTE_NULL_ARG_CHECK(step);
	ROUTE_NULL_ARG_CHECK(distance);

	route_step_s *handle = (route_step_s *) step;
	double dist = (double)location_route_step_get_distance(handle->step);

	*distance = dist;

	return ROUTE_ERROR_NONE;
}

int route_step_get_duration(route_step_h step, long *duration)
{
	ROUTE_NULL_ARG_CHECK(step);
	ROUTE_NULL_ARG_CHECK(duration);

	route_step_s *handle = (route_step_s *) step;
	long dur = (long)location_route_step_get_duration(handle->step);

	*duration = dur;

	return ROUTE_ERROR_NONE;
}

int route_step_get_transport_mode(route_step_h step, char** mode)
{
	ROUTE_NULL_ARG_CHECK(step);
	ROUTE_NULL_ARG_CHECK(mode);

	route_step_s *handle = (route_step_s *) step;
	char *transport = (char *)location_route_step_get_transport_mode(handle->step);

	if (transport == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_RESULT_NOT_FOUND);
	}

	*mode = strdup(transport);
	if (*mode == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_OUT_OF_MEMORY);
	}

	return ROUTE_ERROR_NONE;
}

int route_step_get_instruction(route_step_h step, char **instruction)
{
	ROUTE_NULL_ARG_CHECK(step);
	ROUTE_NULL_ARG_CHECK(instruction);

	route_step_s *handle = (route_step_s *) step;
	char *inst = (char *)location_route_step_get_instruction(handle->step);

	if (inst == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_RESULT_NOT_FOUND);
	}

	*instruction = strdup(inst);
	if (*instruction == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_OUT_OF_MEMORY);
	}

	return ROUTE_ERROR_NONE;
}

int route_step_foreach_geometries(route_step_h step, route_step_geometry_cb callback, void *user_data)
{
	ROUTE_NULL_ARG_CHECK(step);
	ROUTE_NULL_ARG_CHECK(callback);

	route_step_s *handle = (route_step_s *) step;
	GList *geometry_list = location_route_step_get_geometry(handle->step);

	while (geometry_list) {
		location_coords_s *geometry = (location_coords_s *) malloc(sizeof(location_coords_s));;
		LocationPosition *pos;
		pos = geometry_list->data;
		geometry->latitude = pos->latitude;
		geometry->longitude = pos->longitude;

		if (callback(geometry, user_data) == false) {
			free(geometry);
			break;
		}
		geometry_list = geometry_list->next;
		free(geometry);
	}

	return ROUTE_ERROR_NONE;
}

int route_step_foreach_properties(route_step_h step, route_step_property_cb callback, void *user_data)
{
	ROUTE_NULL_ARG_CHECK(step);
	ROUTE_NULL_ARG_CHECK(callback);

	route_step_s *handle = (route_step_s *) step;
	GList *key_list = location_route_step_get_property_key(handle->step);

	while (key_list) {
		char *key = key_list->data;
		char *value = NULL;
		if (key != NULL && (value = (char *)location_route_step_get_property(handle->step, key)) != NULL) {
			if (callback(key, value, user_data) == false) {
				break;
			}
		}
		key_list = key_list->next;
	}

	return ROUTE_ERROR_NONE;
}

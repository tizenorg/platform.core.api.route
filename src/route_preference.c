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

#include "route_private.h"
#include "route_preference.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
 * Internal implementation
 */
static int _convert_error_code(int code)
{
	int ret;
	char *msg = "ROUTE_ERROR_NONE";
	switch (code) {
	case LOCATION_ERROR_NONE:
		ret = ROUTE_ERROR_NONE;
		msg = "ROUTE_ERROR_NONE";
		break;
	case LOCATION_ERROR_PARAMETER:
		ret = ROUTE_ERROR_INVALID_PARAMETER;
		msg = "ROUTE_ERROR_INVALID_PARAMETER";
		break;
	case LOCATION_ERROR_NETWORK_FAILED:
	case LOCATION_ERROR_NETWORK_NOT_CONNECTED:
		ret = ROUTE_ERROR_NETWORK_FAILED;
		msg = "ROUTE_ERROR_NETWORK_FAILED";
		break;
	case LOCATION_ERROR_NOT_FOUND:
		ret = ROUTE_ERROR_RESULT_NOT_FOUND;
		msg = "ROUTE_ERROR_RESULT_NOT_FOUND";
		break;
	case LOCATION_ERROR_NOT_SUPPORTED:
		ret = ROUTE_ERROR_SERVICE_NOT_SUPPORTED;
		msg = "ROUTE_ERROR_SERVICE_NOT_SUPPORTED";
		break;
	case LOCATION_ERROR_NOT_ALLOWED:
	case LOCATION_ERROR_NOT_AVAILABLE:
	case LOCATION_ERROR_CONFIGURATION:
	case LOCATION_ERROR_UNKNOWN:
	default:
		msg = "ROUTE_ERROR_SERVICE_NOT_AVAILABLE";
		ret = ROUTE_ERROR_SERVICE_NOT_AVAILABLE;
	}
	ROUTE_LOGE("%s(0x%08x) : core fw error(0x%x)", msg, ret, code);
	return ret;
}

/*
 * Route preference
 */
int route_preference_create(route_preference_h * preference)
{
	ROUTE_NULL_ARG_CHECK(preference);

	route_preference_s *handle = (route_preference_s *) malloc(sizeof(route_preference_s));
	if (handle == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_OUT_OF_MEMORY);
	}
	memset(handle, 0, sizeof(route_preference_s));

	handle->preference = location_route_pref_new();

	if (handle->preference == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_SERVICE_NOT_AVAILABLE);
	}

	*preference = (route_preference_h) handle;

	return ROUTE_ERROR_NONE;
}

int route_preference_destroy(route_preference_h preference)
{
	ROUTE_NULL_ARG_CHECK(preference);

	route_preference_s *handle = (route_preference_s *) preference;

	if (handle->preference) {
		location_route_pref_free(handle->preference);
	}
	free(handle);
	handle = NULL;

	return ROUTE_ERROR_NONE;
}

int route_preference_foreach_addresses_to_avoid(route_preference_h preference, route_preference_address_to_avoid_cb callback,
						void *user_data)
{
	ROUTE_NULL_ARG_CHECK(preference);
	ROUTE_NULL_ARG_CHECK(callback);

	route_preference_s *handle = (route_preference_s *) preference;
	GList *addr_list = location_route_pref_get_freeformed_addr_to_avoid(handle->preference);

	while (addr_list) {
		gchar *address = addr_list->data;
		if (address != NULL && !callback(address, user_data)) {
			break;
		}
		addr_list = addr_list->next;
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_foreach_areas_to_avoid(route_preference_h preference, route_preference_area_to_avoid_cb callback,
					    void *user_data)
{
	ROUTE_NULL_ARG_CHECK(preference);
	ROUTE_NULL_ARG_CHECK(callback);

	route_preference_s *handle = (route_preference_s *) preference;
	GList *area_list = location_route_pref_get_area_to_avoid(handle->preference);
	LocationBoundary *area;

	while (area_list) {
		area = area_list->data;
		if (area != NULL && !callback((location_bounds_h) area, user_data)) {
			break;
		}
		area_list = area_list->next;
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_foreach_constraints(route_preference_h preference, route_preference_constraint_cb callback,
					 void *user_data)
{
	ROUTE_NULL_ARG_CHECK(preference);
	ROUTE_NULL_ARG_CHECK(callback);

	route_preference_s *handle = (route_preference_s *) preference;
	GList *constraint_list = location_route_pref_get_feature_to_avoid(handle->preference);

	while (constraint_list) {
		char *constraint = (char *)constraint_list->data;
		if (constraint != NULL && !callback(constraint, user_data)) {
			break;
		}
		constraint_list = constraint_list->next;
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_foreach_properties(route_preference_h preference, route_preference_property_cb callback, void *user_data)
{
	ROUTE_NULL_ARG_CHECK(preference);
	ROUTE_NULL_ARG_CHECK(callback);

	route_preference_s *handle = (route_preference_s *) preference;
	GList *key_list = location_route_pref_get_property_key(handle->preference);

	while (key_list) {
		char *key = key_list->data;
		char *value = NULL;
		if (key != NULL && (value = (char *)location_route_pref_get_property(handle->preference, key)) != NULL) {
			if (callback(key, value, user_data) == false) {
				break;
			}
		}
		key_list = key_list->next;
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_get_geometry_bounding_box(route_preference_h preference, location_coords_s * top_left,
					       location_coords_s * bottom_right)
{
	ROUTE_NULL_ARG_CHECK(preference);
	ROUTE_NULL_ARG_CHECK(top_left);
	ROUTE_NULL_ARG_CHECK(bottom_right);

	route_preference_s *handle = (route_preference_s *) preference;
	LocationBoundary *bbox = location_route_pref_get_bounding_box(handle->preference);

	if (bbox == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_RESULT_NOT_FOUND);
	}

	top_left->latitude = bbox->rect.left_top->latitude;
	top_left->longitude = bbox->rect.left_top->longitude;
	bottom_right->latitude = bbox->rect.right_bottom->latitude;
	bottom_right->longitude = bbox->rect.right_bottom->longitude;

	return ROUTE_ERROR_NONE;
}

int route_preference_get_max_results(route_preference_h preference, int *max_results)
{
	ROUTE_NULL_ARG_CHECK(preference);
	ROUTE_NULL_ARG_CHECK(max_results);

	route_preference_s *handle = (route_preference_s *) preference;
	int result = (int)location_route_pref_get_max_result(handle->preference);

	*max_results = result;

	return ROUTE_ERROR_NONE;
}

int route_preference_get_goal(route_preference_h preference, char **goal)
{
	ROUTE_NULL_ARG_CHECK(preference);
	ROUTE_NULL_ARG_CHECK(goal);

	route_preference_s *handle = (route_preference_s *) preference;
	char *route_type = (char *)location_route_pref_get_route_type(handle->preference);

	if (route_type == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_RESULT_NOT_FOUND);
	}

	*goal = strdup(route_type);
	if (*goal == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_OUT_OF_MEMORY);
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_get_transport_mode(route_preference_h preference, char **mode)
{
	ROUTE_NULL_ARG_CHECK(preference);
	ROUTE_NULL_ARG_CHECK(mode);

	route_preference_s *handle = (route_preference_s *) preference;
	char *transport = (char *)location_route_pref_get_transport_mode(handle->preference);

	if (transport == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_RESULT_NOT_FOUND);
	}

	*mode = strdup(transport);
	if (*mode == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_OUT_OF_MEMORY);
	}

	return ROUTE_ERROR_NONE;
}

bool route_preference_is_geometry_used(route_preference_h preference)
{
	ROUTE_NULL_ARG_CHECK_RETURN_FALSE(preference);

	route_preference_s *handle = (route_preference_s *) preference;
	bool ret = (bool) location_route_pref_get_geometry_used(handle->preference);

	return ret;
}

bool route_preference_is_instruction_bounding_box_used(route_preference_h preference)
{
	ROUTE_NULL_ARG_CHECK_RETURN_FALSE(preference);

	route_preference_s *handle = (route_preference_s *) preference;
	bool ret = (bool) location_route_pref_get_instruction_bounding_box_used(handle->preference);

	return ret;
}

bool route_preference_is_instruction_geometry_used(route_preference_h preference)
{
	ROUTE_NULL_ARG_CHECK_RETURN_FALSE(preference);

	route_preference_s *handle = (route_preference_s *) preference;
	bool ret = (bool) location_route_pref_get_instruction_geometry_used(handle->preference);

	return ret;
}

bool route_preference_is_instruction_used(route_preference_h preference)
{
	ROUTE_NULL_ARG_CHECK_RETURN_FALSE(preference);

	route_preference_s *handle = (route_preference_s *) preference;
	bool ret = (bool) location_route_pref_get_instruction_used(handle->preference);

	return ret;
}

bool route_preference_is_traffic_data_used(route_preference_h preference)
{
	ROUTE_NULL_ARG_CHECK_RETURN_FALSE(preference);

	route_preference_s *handle = (route_preference_s *) preference;
	bool ret = (bool) location_route_pref_get_traffic_data_used(handle->preference);

	return ret;
}

int route_preference_get(route_preference_h preference, const char *key, char **value)
{
	ROUTE_NULL_ARG_CHECK(preference);
	ROUTE_NULL_ARG_CHECK(key);
	ROUTE_NULL_ARG_CHECK(value);

	route_preference_s *handle = (route_preference_s *) preference;
	char *val = (char *)location_route_pref_get_property(handle->preference, (gconstpointer) key);
	if (val == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_SERVICE_NOT_AVAILABLE);
	}
	*value = strdup(val);

	return ROUTE_ERROR_NONE;
}

int route_preference_set(route_preference_h preference, const char *key, const char *value)
{
	ROUTE_NULL_ARG_CHECK(preference);
	ROUTE_NULL_ARG_CHECK(key);
	ROUTE_NULL_ARG_CHECK(value);

	route_preference_s *handle = (route_preference_s *) preference;
	bool ret = (bool) location_route_pref_set_property(handle->preference, (gconstpointer) key,
							   (gconstpointer) value);
	if (!ret) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_SERVICE_NOT_AVAILABLE);
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_add_address_to_avoid(route_preference_h preference, const char *address)
{
	ROUTE_NULL_ARG_CHECK(preference);
	ROUTE_NULL_ARG_CHECK(address);

	route_preference_s *handle = (route_preference_s *) preference;
	GList *addr_list = location_route_pref_get_freeformed_addr_to_avoid(handle->preference);
	addr_list = g_list_append(addr_list, (gpointer) address);

	bool ret = (bool) location_route_pref_set_freeformed_addr_to_avoid(handle->preference, addr_list);
	if (!ret) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_SERVICE_NOT_AVAILABLE);
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_clear_addresses_to_avoid(route_preference_h preference)
{
	ROUTE_NULL_ARG_CHECK(preference);

	route_preference_s *handle = (route_preference_s *) preference;
	GList *addr_list = NULL;

	bool ret = (bool) location_route_pref_set_freeformed_addr_to_avoid(handle->preference, addr_list);
	if (!ret) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_SERVICE_NOT_AVAILABLE);
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_add_area_to_avoid(route_preference_h preference, location_bounds_h area)
{
	ROUTE_NULL_ARG_CHECK(preference);
	ROUTE_NULL_ARG_CHECK(area);

	route_preference_s *handle = (route_preference_s *) preference;
	GList *area_list = location_route_pref_get_area_to_avoid(handle->preference);
	area_list = g_list_append(area_list, (gpointer) area);

	bool ret = (bool) location_route_pref_set_area_to_avoid(handle->preference, area_list);
	if (!ret) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_SERVICE_NOT_AVAILABLE);
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_clear_areas_to_avoid(route_preference_h preference)
{
	ROUTE_NULL_ARG_CHECK(preference);

	route_preference_s *handle = (route_preference_s *) preference;
	GList *area_list = NULL;

	bool ret = (bool) location_route_pref_set_area_to_avoid(handle->preference, area_list);
	if (!ret) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_SERVICE_NOT_AVAILABLE);
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_add_constraint(route_preference_h preference, const char *constraint)
{
	ROUTE_NULL_ARG_CHECK(preference);
	ROUTE_NULL_ARG_CHECK(constraint);

	route_preference_s *handle = (route_preference_s *) preference;
	GList *constraint_list = location_route_pref_get_feature_to_avoid(handle->preference);
	constraint_list = g_list_append(constraint_list, (gpointer) constraint);

	bool ret = (bool) location_route_pref_set_feature_to_avoid(handle->preference, constraint_list);
	if (!ret) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_SERVICE_NOT_AVAILABLE);
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_clear_constraints(route_preference_h preference)
{
	ROUTE_NULL_ARG_CHECK(preference);

	route_preference_s *handle = (route_preference_s *) preference;
	GList *constraint_list = NULL;

	bool ret = (bool) location_route_pref_set_feature_to_avoid(handle->preference, constraint_list);
	if (!ret) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_SERVICE_NOT_AVAILABLE);
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_set_geometry_bounding_box(route_preference_h preference, location_coords_s top_left,
					       location_coords_s bottom_right)
{
	ROUTE_NULL_ARG_CHECK(preference);
	ROUTE_CHECK_CONDITION(top_left.latitude>=-90 && top_left.latitude<=90 ,ROUTE_ERROR_INVALID_PARAMETER,"latitude should be -90 <= latitude <= 90");
	ROUTE_CHECK_CONDITION(top_left.longitude>=-180 && top_left.longitude<=180,ROUTE_ERROR_INVALID_PARAMETER,"longitude should be -180 <= latitude <= 180");
	ROUTE_CHECK_CONDITION(bottom_right.latitude>=-90 && bottom_right.latitude<=90 ,ROUTE_ERROR_INVALID_PARAMETER,"latitude should be -90 <= latitude <= 90");
	ROUTE_CHECK_CONDITION(bottom_right.longitude>=-180 && bottom_right.longitude<=180,ROUTE_ERROR_INVALID_PARAMETER,"longitude should be -180 <= latitude <= 180");

	route_preference_s *handle = (route_preference_s *) preference;
	LocationPosition *tl = location_position_new(0, top_left.latitude, top_left.longitude, 0, LOCATION_STATUS_2D_FIX);
	if (tl == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_SERVICE_NOT_AVAILABLE);
	}
	LocationPosition *br =
	    location_position_new(0, bottom_right.latitude, bottom_right.longitude, 0, LOCATION_STATUS_2D_FIX);
	if (br == NULL) {
		location_position_free(tl);
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_SERVICE_NOT_AVAILABLE);
	}

	LocationBoundary *bbox = location_boundary_new_for_rect(tl, br);

	bool ret = (bool) location_route_pref_set_bounding_box(handle->preference, bbox);
	if (!ret) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_SERVICE_NOT_AVAILABLE);
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_set_max_results(route_preference_h preference, int max_results)
{
	ROUTE_NULL_ARG_CHECK(preference);

	route_preference_s *handle = (route_preference_s *) preference;
	bool ret = (bool) location_route_pref_set_max_result(handle->preference, (guint) max_results);
	if (!ret) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_SERVICE_NOT_AVAILABLE);
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_set_goal(route_preference_h preference, const char *goal)
{
	ROUTE_NULL_ARG_CHECK(preference);
	ROUTE_NULL_ARG_CHECK(goal);

	route_preference_s *handle = (route_preference_s *) preference;
	bool ret = (bool) location_route_pref_set_route_type(handle->preference, (gchar *) goal);
	if (!ret) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_SERVICE_NOT_AVAILABLE);
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_set_transport_mode(route_preference_h preference, const char *mode)
{
	ROUTE_NULL_ARG_CHECK(preference);
	ROUTE_NULL_ARG_CHECK(mode);

	route_preference_s *handle = (route_preference_s *) preference;
	bool ret = (bool) location_route_pref_set_transport_mode(handle->preference, (gchar *) mode);
	if (!ret) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_SERVICE_NOT_AVAILABLE);
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_set_geometry_used(route_preference_h preference, bool used)
{
	ROUTE_NULL_ARG_CHECK(preference);

	route_preference_s *handle = (route_preference_s *) preference;
	bool ret = (bool) location_route_pref_set_geometry_used(handle->preference, (gboolean) used);
	if (!ret) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_SERVICE_NOT_AVAILABLE);
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_set_instruction_bounding_box_used(route_preference_h preference, bool used)
{
	ROUTE_NULL_ARG_CHECK(preference);

	route_preference_s *handle = (route_preference_s *) preference;
	bool ret = (bool) location_route_pref_set_instruction_bounding_box_used(handle->preference,
										(gboolean) used);
	if (!ret) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_SERVICE_NOT_AVAILABLE);
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_set_instruction_geometry_used(route_preference_h preference, bool used)
{
	ROUTE_NULL_ARG_CHECK(preference);

	route_preference_s *handle = (route_preference_s *) preference;
	bool ret = (bool) location_route_pref_set_instruction_geometry_used(handle->preference,
									    (gboolean) used);
	if (!ret) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_SERVICE_NOT_AVAILABLE);
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_set_instruction_used(route_preference_h preference, bool used)
{
	ROUTE_NULL_ARG_CHECK(preference);

	route_preference_s *handle = (route_preference_s *) preference;
	bool ret = (bool) location_route_pref_set_instruction_used(handle->preference, (gboolean) used);
	if (!ret) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_SERVICE_NOT_AVAILABLE);
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_set_traffic_data_used(route_preference_h preference, bool used)
{
	ROUTE_NULL_ARG_CHECK(preference);

	route_preference_s *handle = (route_preference_s *) preference;
	bool ret = (bool) location_route_pref_set_traffic_data_used(handle->preference, (gboolean) used);
	if (!ret) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_SERVICE_NOT_AVAILABLE);
	}

	return ROUTE_ERROR_NONE;
}

bool route_preference_is_area_to_avoid_supported(route_service_h service, location_bounds_type_e type)
{
	ROUTE_NULL_ARG_CHECK_RETURN_FALSE(service);

	route_service_s *handle = (route_service_s *) service;
	bool ret = false;
	switch (type) {
	case LOCATION_BOUNDS_RECT:
		ret =
		    (bool) location_map_is_supported_provider_capability(handle->object,
									 MAP_SERVICE_ROUTE_REQUEST_RECT_AREA_TO_AVOID);
		break;
	case LOCATION_BOUNDS_CIRCLE:
		ret =
		    (bool) location_map_is_supported_provider_capability(handle->object,
									 MAP_SERVICE_ROUTE_REQUEST_CIRCLE_AREA_TO_AVOID);
		break;
	case LOCATION_BOUNDS_POLYGON:
		ret =
		    (bool) location_map_is_supported_provider_capability(handle->object,
									 MAP_SERVICE_ROUTE_REQUEST_POLYGON_AREA_TO_AVOID);
		break;
	default:
		ROUTE_LOGE("Unknown location_bounds_type_e : %d", type);
		break;
	}

	return ret;
}

bool route_preference_is_address_to_avoid_supported(route_service_h service)
{
	ROUTE_NULL_ARG_CHECK_RETURN_FALSE(service);

	route_service_s *handle = (route_service_s *) service;
	bool ret = (bool) location_map_is_supported_provider_capability(handle->object,
									MAP_SERVICE_ROUTE_REQUEST_FREEFORM_ADDR_TO_AVOID);

	return ret;
}

bool route_preference_is_geometry_bounding_box_supported(route_service_h service)
{
	ROUTE_NULL_ARG_CHECK_RETURN_FALSE(service);

	route_service_s *handle = (route_service_s *) service;
	bool ret =
	    (bool) location_map_is_supported_provider_capability(handle->object, MAP_SERVICE_ROUTE_PREF_GEOMETRY_BOUNDING_BOX);

	return ret;
}

bool route_preference_is_geometry_supported(route_service_h service)
{
	ROUTE_NULL_ARG_CHECK_RETURN_FALSE(service);

	route_service_s *handle = (route_service_s *) service;
	bool ret =
	    (bool) location_map_is_supported_provider_capability(handle->object, MAP_SERVICE_ROUTE_PREF_GEOMETRY_RETRIEVAL);

	return ret;
}

bool route_preference_is_instruction_geometry_supported(route_service_h service)
{
	ROUTE_NULL_ARG_CHECK_RETURN_FALSE(service);

	route_service_s *handle = (route_service_s *) service;
	bool ret =
	    (bool) location_map_is_supported_provider_capability(handle->object, MAP_SERVICE_ROUTE_PREF_INSTRUCTION_GEOMETRY);

	return ret;
}

bool route_preference_is_instruction_bounding_box_supported(route_service_h service)
{
	ROUTE_NULL_ARG_CHECK_RETURN_FALSE(service);

	route_service_s *handle = (route_service_s *) service;
	bool ret = (bool) location_map_is_supported_provider_capability(handle->object,
									MAP_SERVICE_ROUTE_PREF_INSTRUCTION_BOUNDING_BOX);

	return ret;
}

bool route_preference_is_instruction_supported(route_service_h service)
{
	ROUTE_NULL_ARG_CHECK_RETURN_FALSE(service);

	route_service_s *handle = (route_service_s *) service;
	bool ret =
	    (bool) location_map_is_supported_provider_capability(handle->object, MAP_SERVICE_ROUTE_PREF_INSTRUCTION_RETRIEVAL);

	return ret;
}

bool route_preference_is_traffic_data_supported(route_service_h service)
{
	ROUTE_NULL_ARG_CHECK_RETURN_FALSE(service);

	route_service_s *handle = (route_service_s *) service;
	bool ret =
	    (bool) location_map_is_supported_provider_capability(handle->object, MAP_SERVICE_ROUTE_PREF_REALTIME_TRAFFIC);

	return ret;
}

int route_preference_foreach_available_constraints(route_service_h service, route_preference_available_constraint_cb callback,
						   void *user_data)
{
	ROUTE_NULL_ARG_CHECK(service);
	ROUTE_NULL_ARG_CHECK(callback);

	route_service_s *handle = (route_service_s *) service;
	LocationMapServiceType type = MAP_SERVICE_ROUTE_REQUEST_FEATURE_TO_AVOID;
	GList *constraint_list = NULL;
	int ret = location_map_get_provider_capability_key(handle->object, type, &constraint_list);
	if (ret) {
		return _convert_error_code(ret);
	}

	while (constraint_list) {
		char *constraint = (char *)constraint_list->data;
		if (constraint != NULL && !callback(constraint, user_data)) {
			break;
		}
		constraint_list = constraint_list->next;
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_foreach_available_goals(route_service_h service, route_preference_available_goal_cb callback,
					     void *user_data)
{
	ROUTE_NULL_ARG_CHECK(service);
	ROUTE_NULL_ARG_CHECK(callback);

	route_service_s *handle = (route_service_s *) service;
	LocationMapServiceType type = MAP_SERVICE_ROUTE_PREF_TYPE;
	GList *goal_list = NULL;
	int ret = location_map_get_provider_capability_key(handle->object, type, &goal_list);
	if (ret) {
		return _convert_error_code(ret);
	}

	while (goal_list) {
		char *goal = (char *)goal_list->data;
		if (goal != NULL && !callback(goal, user_data)) {
			break;
		}
		goal_list = goal_list->next;
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_foreach_available_transport_modes(route_service_h service,
						       route_preference_available_transport_mode_cb callback, void *user_data)
{
	ROUTE_NULL_ARG_CHECK(service);
	ROUTE_NULL_ARG_CHECK(callback);

	route_service_s *handle = (route_service_s *) service;
	LocationMapServiceType type = MAP_SERVICE_ROUTE_PREF_TRANSPORT_MODE;
	GList *mode_list = NULL;
	int ret = location_map_get_provider_capability_key(handle->object, type, &mode_list);
	if (ret) {
		return _convert_error_code(ret);
	}

	while (mode_list) {
		char *mode = (char *)mode_list->data;
		if (mode != NULL && !callback(mode, user_data)) {
			break;
		}
		mode_list = mode_list->next;
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_foreach_available_property_keys(route_service_h service,
						     route_preference_available_property_key_cb callback, void *user_data)
{
	ROUTE_NULL_ARG_CHECK(service);
	ROUTE_NULL_ARG_CHECK(callback);

	route_service_s *handle = (route_service_s *) service;
	LocationMapServiceType type = MAP_SERVICE_ROUTE_PREF_PROPERTY;
	GList *key_list = NULL;
	int ret = location_map_get_provider_capability_key(handle->object, type, &key_list);
	if (ret) {
		return _convert_error_code(ret);
	}

	while (key_list) {
		char *key = (char *)key_list->data;
		if (key != NULL && !callback(key, user_data)) {
			break;
		}
		key_list = key_list->next;
	}

	return ROUTE_ERROR_NONE;
}

int route_preference_foreach_available_property_values(route_service_h service, const char *key,
						       route_preference_available_property_value_cb callback, void *user_data)
{
	ROUTE_NULL_ARG_CHECK(service);
	ROUTE_NULL_ARG_CHECK(key);
	ROUTE_NULL_ARG_CHECK(callback);

	route_service_s *handle = (route_service_s *) service;
	LocationMapServiceType type = MAP_SERVICE_ROUTE_PREF_PROPERTY;
	GList *key_list = NULL;
	int ret = location_map_get_provider_capability_key(handle->object, type, &key_list);
	if (ret) {
		return _convert_error_code(ret);
	}

	while (key_list) {
		char *key = (char *)key_list->data;
		char *value = (char *)location_route_pref_get_property(handle->route_preference, (gconstpointer) key);
		if (key != NULL && value != NULL && !callback(value, user_data)) {
			break;
		}
		key_list = key_list->next;
	}

	return ROUTE_ERROR_NONE;
}

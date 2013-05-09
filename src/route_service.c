/*
 * Copyright (c) 2011-2013 Samsung Electronics Co., Ltd All Rights Reserved
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

#include "route_service.h"
#include "route_preference.h"
#include "route_private.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
	void *data;
	route_service_found_cb callback;
} __callback_data;

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

static void __free_waypoint(gpointer data)
{
	LocationPosition *pos = (LocationPosition *) data;
	if (pos) {
		location_position_free(pos);
	}
}

/*
 * Route service
 */
static void __LocationRouteCB(LocationError error, guint req_id, GList * route_list, gchar * error_code, gchar * error_msg,
			      gpointer userdata)
{
	__callback_data *calldata = (__callback_data *) userdata;
	if (calldata == NULL || calldata->callback == NULL) {
		return;
	}

	int ret = _convert_error_code(error);
	GList *routes_list = route_list;
	int index = 0;
	int total = 0;

	if (routes_list == NULL || ret != 0) {
		calldata->callback(ret, index, total, NULL, calldata->data);
		free(calldata);
		return;
	}

	total = g_list_length(routes_list);
	while (routes_list) {
		route_s *route = (route_s *) malloc(sizeof(route_s));
		if (route == NULL) {
			break;
		}
		route->route = routes_list->data;
		route->request_id = req_id;
		if (calldata->callback(ret, index++, total, route, calldata->data) == false) {
			free(route);
			break;
		}
		routes_list = routes_list->next;
		free(route);
	}
	free(calldata);
}

EXPORT_API int route_service_create(route_service_h * service)
{
	ROUTE_NULL_ARG_CHECK(service);

	int ret = location_init();
	if (ret != LOCATION_ERROR_NONE) {
		ROUTE_LOGE("Fail to location_init");
		return _convert_error_code(ret);
	}

	route_service_s *handle = (route_service_s *) malloc(sizeof(route_service_s));
	if (handle == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_OUT_OF_MEMORY);
	}
	memset(handle, 0, sizeof(route_service_s));

	if (ROUTE_ERROR_NONE != route_preference_create(&handle->route_preference)) {
		free(handle);
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_OUT_OF_MEMORY);
	}

	handle->object = location_map_new(NULL);
	if (handle->object == NULL) {
		free(handle);
		ROUTE_LOGE("Fail to location_map_new");
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_SERVICE_NOT_AVAILABLE);
	}

	*service = (route_service_h) handle;

	return ROUTE_ERROR_NONE;
}

EXPORT_API int route_service_destroy(route_service_h service)
{
	ROUTE_NULL_ARG_CHECK(service);

	route_service_s *handle = (route_service_s *) service;

	if (handle->route_preference) {
		route_preference_destroy(handle->route_preference);
	}

	int ret = location_map_free(handle->object);
	if (ret != LOCATION_ERROR_NONE) {
		return _convert_error_code(ret);
	}
	free(handle);
	handle = NULL;

	return ROUTE_ERROR_NONE;
}

EXPORT_API int route_service_get_preference(route_service_h service, route_preference_h * preference)
{
	ROUTE_NULL_ARG_CHECK(service);
	ROUTE_NULL_ARG_CHECK(preference);

	route_service_s *handle = (route_service_s *) service;

	if (handle->route_preference == NULL) {
		route_preference_create(&handle->route_preference);
	}
	*preference = handle->route_preference;

	return ROUTE_ERROR_NONE;
}

EXPORT_API int route_service_set_preference(route_service_h service, route_preference_h preference)
{
	ROUTE_NULL_ARG_CHECK(service);
	ROUTE_NULL_ARG_CHECK(preference);

	route_service_s *handle = (route_service_s *) service;

	if (handle->route_preference) {
		route_preference_destroy(handle->route_preference);
		handle->route_preference = preference;
	}

	return ROUTE_ERROR_NONE;
}

EXPORT_API int route_service_find(route_service_h service, location_coords_s origin, location_coords_s destination,
		       location_coords_s * waypoint_list, int waypoint_num, route_service_found_cb callback, void *user_data,
		       int *request_id)
{
	ROUTE_NULL_ARG_CHECK(service);
	ROUTE_NULL_ARG_CHECK(callback);
	ROUTE_CHECK_CONDITION(origin.latitude>=-90 && origin.latitude<=90 ,ROUTE_ERROR_INVALID_PARAMETER,"latitude should be -90 <= latitude <= 90");
	ROUTE_CHECK_CONDITION(origin.longitude>=-180 && origin.longitude<=180,ROUTE_ERROR_INVALID_PARAMETER,"longitude should be -180 <= latitude <= 180");
	ROUTE_CHECK_CONDITION(destination.latitude>=-90 && destination.latitude<=90 ,ROUTE_ERROR_INVALID_PARAMETER,"latitude should be -90 <= latitude <= 90");
	ROUTE_CHECK_CONDITION(destination.longitude>=-180 && destination.longitude<=180,ROUTE_ERROR_INVALID_PARAMETER,"longitude should be -180 <= latitude <= 180");

	LocationPosition start;
	LocationPosition end;
	unsigned int reqid;
	int ret;
	int i;

	route_service_s *handle = (route_service_s *) service;
	route_preference_s *pref = (route_preference_s *) handle->route_preference;

	start.latitude = origin.latitude;
	start.longitude = origin.longitude;
	start.altitude = 0;
	start.status = LOCATION_STATUS_2D_FIX;

	end.latitude = destination.latitude;
	end.longitude = destination.longitude;
	end.altitude = 0;
	end.status = LOCATION_STATUS_2D_FIX;

	GList *waypoint = NULL;
	LocationPosition *via_pos = NULL;

	for (i = 0; i < waypoint_num; i++) {
		via_pos =
		    location_position_new(0, waypoint_list->latitude, waypoint_list->longitude, 0, LOCATION_STATUS_2D_FIX);
		if (via_pos == NULL) {
			ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_RESULT_NOT_FOUND);
		} else {
			waypoint_list++;
			waypoint = g_list_append(waypoint, (gpointer) via_pos);
		}
		location_position_free(via_pos);
	}

	__callback_data *calldata = (__callback_data *) malloc(sizeof(__callback_data));
	if (calldata == NULL) {
		ROUTE_PRINT_ERROR_CODE_RETURN(ROUTE_ERROR_OUT_OF_MEMORY);
	}

	calldata->callback = callback;
	calldata->data = user_data;

	ret = location_map_request_route(handle->object, &start, &end, waypoint, pref->preference, __LocationRouteCB, calldata,
				   &reqid);
	if (ret != LOCATION_ERROR_NONE) {
		free(calldata);
		g_list_free_full(waypoint, __free_waypoint);
		return _convert_error_code(ret);
	}

	if (request_id) {
		*request_id = reqid;
	}

	return ROUTE_ERROR_NONE;
}

EXPORT_API int route_service_cancel(route_service_h service, int request_id)
{
	ROUTE_NULL_ARG_CHECK(service);
	ROUTE_CHECK_CONDITION(request_id>0,ROUTE_ERROR_INVALID_PARAMETER,"request id should be > 0");

	int ret;

	route_service_s *handle = (route_service_s *) service;

	ret = location_map_cancel_route_request(handle->object, request_id);

	if (ret != LOCATION_ERROR_NONE) {
		return _convert_error_code(ret);
	}

	return ROUTE_ERROR_NONE;
}

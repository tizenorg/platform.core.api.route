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

#include <tet_api.h>

#include <route_service.h>
#include <route_preference.h>
#include <route.h>
#include <glib.h>

enum {
	POSITIVE_TC_IDX = 0x01,
	NEGATIVE_TC_IDX,
};

static void startup(void);
static void cleanup(void);

void (*tet_startup) (void) = startup;
void (*tet_cleanup) (void) = cleanup;

static void utc_location_route_clone_p(void);
static void utc_location_route_clone_n(void);
static void utc_location_route_destroy_p(void);
static void utc_location_route_destroy_n(void);
static void utc_location_route_get_request_id_p(void);
static void utc_location_route_get_request_id_n(void);
static void utc_location_route_get_request_id_n_02(void);
static void utc_location_route_get_origin_p(void);
static void utc_location_route_get_origin_n(void);
static void utc_location_route_get_origin_n_02(void);
static void utc_location_route_get_destination_p(void);
static void utc_location_route_get_destination_n(void);
static void utc_location_route_get_destination_n_02(void);
static void utc_location_route_get_geometry_bounding_box_p(void);
static void utc_location_route_get_geometry_bounding_box_n(void);
static void utc_location_route_get_geometry_bounding_box_n_02(void);
static void utc_location_route_get_geometry_bounding_box_n_03(void);
static void utc_location_route_get_distance_unit_p(void);
static void utc_location_route_get_distance_unit_n(void);
static void utc_location_route_get_distance_unit_n_02(void);
static void utc_location_route_get_total_distance_p(void);
static void utc_location_route_get_total_distance_n(void);
static void utc_location_route_get_total_distance_n_02(void);
static void utc_location_route_get_total_duration_p(void);
static void utc_location_route_get_total_duration_n(void);
static void utc_location_route_get_total_duration_n_02(void);
static void utc_location_route_foreach_properties_p(void);
static void utc_location_route_foreach_properties_n(void);
static void utc_location_route_foreach_properties_n_02(void);
static void utc_location_route_foreach_segments_p(void);
static void utc_location_route_foreach_segments_n(void);
static void utc_location_route_foreach_segments_n_02(void);
static void utc_location_route_segment_clone_p(void);
static void utc_location_route_segment_clone_n(void);
static void utc_location_route_segment_destroy_p(void);
static void utc_location_route_segment_destroy_n(void);
static void utc_location_route_segment_get_origin_p(void);
static void utc_location_route_segment_get_origin_n(void);
static void utc_location_route_segment_get_origin_n_02(void);
static void utc_location_route_segment_get_destination_p(void);
static void utc_location_route_segment_get_destination_n(void);
static void utc_location_route_segment_get_destination_n_02(void);
static void utc_location_route_segment_get_geometry_bounding_box_p(void);
static void utc_location_route_segment_get_geometry_bounding_box_n(void);
static void utc_location_route_segment_get_geometry_bounding_box_n_02(void);
static void utc_location_route_segment_get_geometry_bounding_box_n_03(void);
static void utc_location_route_segment_get_distance_p(void);
static void utc_location_route_segment_get_distance_n(void);
static void utc_location_route_segment_get_distance_n_02(void);
static void utc_location_route_segment_get_duration_p(void);
static void utc_location_route_segment_get_duration_n(void);
static void utc_location_route_segment_get_duration_n_02(void);
static void utc_location_route_segment_foreach_properties_p(void);
static void utc_location_route_segment_foreach_properties_n(void);
static void utc_location_route_segment_foreach_properties_n_02(void);
static void utc_location_route_segment_foreach_steps_p(void);
static void utc_location_route_segment_foreach_steps_n(void);
static void utc_location_route_segment_foreach_steps_n_02(void);
static void utc_location_route_step_clone_p(void);
static void utc_location_route_step_clone_n(void);
static void utc_location_route_step_destroy_p(void);
static void utc_location_route_step_destroy_n(void);
static void utc_location_route_step_get_origin_p(void);
static void utc_location_route_step_get_origin_n(void);
static void utc_location_route_step_get_origin_n_02(void);
static void utc_location_route_step_get_destination_p(void);
static void utc_location_route_step_get_destination_n(void);
static void utc_location_route_step_get_destination_n_02(void);
static void utc_location_route_step_get_geometry_bounding_box_p(void);
static void utc_location_route_step_get_geometry_bounding_box_n(void);
static void utc_location_route_step_get_geometry_bounding_box_n_02(void);
static void utc_location_route_step_get_geometry_bounding_box_n_03(void);
static void utc_location_route_step_get_distance_p(void);
static void utc_location_route_step_get_distance_n(void);
static void utc_location_route_step_get_distance_n_02(void);
static void utc_location_route_step_get_duration_p(void);
static void utc_location_route_step_get_duration_n(void);
static void utc_location_route_step_get_duration_n_02(void);
static void utc_location_route_step_get_transport_mode_p(void);
static void utc_location_route_step_get_transport_mode_n(void);
static void utc_location_route_step_get_transport_mode_n_02(void);
static void utc_location_route_step_get_instruction_p(void);
static void utc_location_route_step_get_instruction_n(void);
static void utc_location_route_step_get_instruction_n_02(void);
static void utc_location_route_step_foreach_geometries_p(void);
static void utc_location_route_step_foreach_geometries_n(void);
static void utc_location_route_step_foreach_geometries_n_02(void);
static void utc_location_route_step_foreach_properties_p(void);
static void utc_location_route_step_foreach_properties_n(void);
static void utc_location_route_step_foreach_properties_n_02(void);

struct tet_testlist tet_testlist[] = {
	{utc_location_route_clone_p, POSITIVE_TC_IDX},
	{utc_location_route_clone_n, NEGATIVE_TC_IDX},
	{utc_location_route_destroy_p, POSITIVE_TC_IDX},
	{utc_location_route_destroy_n, NEGATIVE_TC_IDX},
	{utc_location_route_get_request_id_p, POSITIVE_TC_IDX},
	{utc_location_route_get_request_id_n, NEGATIVE_TC_IDX},
	{utc_location_route_get_request_id_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_get_origin_p, POSITIVE_TC_IDX},
	{utc_location_route_get_origin_n, NEGATIVE_TC_IDX},
	{utc_location_route_get_origin_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_get_destination_p, POSITIVE_TC_IDX},
	{utc_location_route_get_destination_n, NEGATIVE_TC_IDX},
	{utc_location_route_get_destination_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_get_geometry_bounding_box_p, POSITIVE_TC_IDX},
	{utc_location_route_get_geometry_bounding_box_n, NEGATIVE_TC_IDX},
	{utc_location_route_get_geometry_bounding_box_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_get_geometry_bounding_box_n_03, NEGATIVE_TC_IDX},
	{utc_location_route_get_distance_unit_p, POSITIVE_TC_IDX},
	{utc_location_route_get_distance_unit_n, NEGATIVE_TC_IDX},
	{utc_location_route_get_distance_unit_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_get_total_distance_p, POSITIVE_TC_IDX},
	{utc_location_route_get_total_distance_n, NEGATIVE_TC_IDX},
	{utc_location_route_get_total_distance_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_get_total_duration_p, POSITIVE_TC_IDX},
	{utc_location_route_get_total_duration_n, NEGATIVE_TC_IDX},
	{utc_location_route_get_total_duration_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_foreach_properties_p, POSITIVE_TC_IDX},
	{utc_location_route_foreach_properties_n, NEGATIVE_TC_IDX},
	{utc_location_route_foreach_properties_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_foreach_segments_p, POSITIVE_TC_IDX},
	{utc_location_route_foreach_segments_n, NEGATIVE_TC_IDX},
	{utc_location_route_foreach_segments_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_segment_clone_p, POSITIVE_TC_IDX},
	{utc_location_route_segment_clone_n, NEGATIVE_TC_IDX},
	{utc_location_route_segment_destroy_p, POSITIVE_TC_IDX},
	{utc_location_route_segment_destroy_n, NEGATIVE_TC_IDX},
	{utc_location_route_segment_get_origin_p, POSITIVE_TC_IDX},
	{utc_location_route_segment_get_origin_n, NEGATIVE_TC_IDX},
	{utc_location_route_segment_get_origin_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_segment_get_destination_p, POSITIVE_TC_IDX},
	{utc_location_route_segment_get_destination_n, NEGATIVE_TC_IDX},
	{utc_location_route_segment_get_destination_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_segment_get_geometry_bounding_box_p, POSITIVE_TC_IDX},
	{utc_location_route_segment_get_geometry_bounding_box_n, NEGATIVE_TC_IDX},
	{utc_location_route_segment_get_geometry_bounding_box_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_segment_get_geometry_bounding_box_n_03, NEGATIVE_TC_IDX},
	{utc_location_route_segment_get_distance_p, POSITIVE_TC_IDX},
	{utc_location_route_segment_get_distance_n, NEGATIVE_TC_IDX},
	{utc_location_route_segment_get_distance_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_segment_get_duration_p, POSITIVE_TC_IDX},
	{utc_location_route_segment_get_duration_n, NEGATIVE_TC_IDX},
	{utc_location_route_segment_get_duration_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_segment_foreach_properties_p, POSITIVE_TC_IDX},
	{utc_location_route_segment_foreach_properties_n, NEGATIVE_TC_IDX},
	{utc_location_route_segment_foreach_properties_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_segment_foreach_steps_p, POSITIVE_TC_IDX},
	{utc_location_route_segment_foreach_steps_n, NEGATIVE_TC_IDX},
	{utc_location_route_segment_foreach_steps_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_step_clone_p, POSITIVE_TC_IDX},
	{utc_location_route_step_clone_n, NEGATIVE_TC_IDX},
	{utc_location_route_step_destroy_p, POSITIVE_TC_IDX},
	{utc_location_route_step_destroy_n, NEGATIVE_TC_IDX},
	{utc_location_route_step_get_origin_p, POSITIVE_TC_IDX},
	{utc_location_route_step_get_origin_n, NEGATIVE_TC_IDX},
	{utc_location_route_step_get_origin_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_step_get_destination_p, POSITIVE_TC_IDX},
	{utc_location_route_step_get_destination_n, NEGATIVE_TC_IDX},
	{utc_location_route_step_get_destination_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_step_get_geometry_bounding_box_p, POSITIVE_TC_IDX},
	{utc_location_route_step_get_geometry_bounding_box_n, NEGATIVE_TC_IDX},
	{utc_location_route_step_get_geometry_bounding_box_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_step_get_geometry_bounding_box_n_03, NEGATIVE_TC_IDX},
	{utc_location_route_step_get_distance_p, POSITIVE_TC_IDX},
	{utc_location_route_step_get_distance_n, NEGATIVE_TC_IDX},
	{utc_location_route_step_get_distance_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_step_get_duration_p, POSITIVE_TC_IDX},
	{utc_location_route_step_get_duration_n, NEGATIVE_TC_IDX},
	{utc_location_route_step_get_duration_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_step_get_transport_mode_p, POSITIVE_TC_IDX},
	{utc_location_route_step_get_transport_mode_n, NEGATIVE_TC_IDX},
	{utc_location_route_step_get_transport_mode_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_step_get_instruction_p, POSITIVE_TC_IDX},
	{utc_location_route_step_get_instruction_n, NEGATIVE_TC_IDX},
	{utc_location_route_step_get_instruction_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_step_foreach_geometries_p, POSITIVE_TC_IDX},
	{utc_location_route_step_foreach_geometries_n, NEGATIVE_TC_IDX},
	{utc_location_route_step_foreach_geometries_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_step_foreach_properties_p, POSITIVE_TC_IDX},
	{utc_location_route_step_foreach_properties_n, NEGATIVE_TC_IDX},
	{utc_location_route_step_foreach_properties_n_02, NEGATIVE_TC_IDX},

	{NULL, 0},
};

static bool service_enabled = FALSE;

static GMainLoop *g_mainloop = NULL;
static GThread *event_thread;

gpointer GmainThread(gpointer data)
{
	g_mainloop = g_main_loop_new(NULL, 0);
	g_main_loop_run(g_mainloop);

	return NULL;
}

static void validate_and_next(char *api_name, int act_ret, int ext_ret, char *fail_msg)
{
	dts_message(api_name, "Actual Result : %d, Expected Result : %d", act_ret, ext_ret);
	if (act_ret != ext_ret) {
		dts_message(api_name, "Fail Message: %s", fail_msg);
		dts_fail(api_name);
	}
}

static void validate_eq(char *api_name, int act_ret, int ext_ret)
{
	dts_message(api_name, "Actual Result : %d, Expected Result : %d", act_ret, ext_ret);
	if (act_ret == ext_ret) {
		dts_pass(api_name);
	} else {
		dts_fail(api_name);
	}
}

static void wait_for_service(char *api_name)
{
	int timeout = 0;
	for (timeout; timeout < 180; timeout++) {
		if (service_enabled) {
			dts_message(api_name, "Find Routes!!!!");
			break;
		} else {
			dts_message(api_name, "Did not find Routes!!!!");
			sleep(1);
		}
	}
}

static route_service_h g_service;
static route_h g_route;
static route_segment_h g_segment;
static route_step_h g_step;

static bool route_segment_step_callback(route_step_h step, void *user_data)
{
	if (step == NULL) {
		return FALSE;
	}

	int ret = route_step_clone(&g_step, step);
	validate_and_next(__func__, ret, ROUTE_ERROR_NONE, "route_step_clone() is failed");
	return TRUE;
}

static bool route_segment_callback(route_segment_h segment, void *user_data)
{
	if (segment == NULL) {
		return FALSE;
	}

	int ret = route_segment_clone(&g_segment, segment);
	validate_and_next(__func__, ret, ROUTE_ERROR_NONE, "route_segment_clone() is failed");
	ret = route_segment_foreach_steps(segment, route_segment_step_callback, NULL);
	validate_and_next(__func__, ret, ROUTE_ERROR_NONE, "route_segment_foreach_steps() is failed");
	return TRUE;
}

static bool route_service_found_callback(route_error_e error, int index, int total, route_h route, void *user_data)
{
	if (error != ROUTE_ERROR_NONE) {
		return FALSE;
	}

	service_enabled = TRUE;

	int ret = route_clone(&g_route, route);
	validate_and_next(__func__, ret, ROUTE_ERROR_NONE, "route_clone() is failed");
	ret = route_foreach_segments(route, route_segment_callback, NULL);
	validate_and_next(__func__, ret, ROUTE_ERROR_NONE, "route_foreach_segments() is failed");
	return TRUE;
}

void request_route_service_start()
{
	int ret, request_id;
	location_coords_s origin, destination;

	ret = route_service_create(&g_service);
	validate_and_next(__func__, ret, ROUTE_ERROR_NONE, "route_service_create() is failed");

	origin.latitude = 37.564263;
	origin.longitude = 126.974676;
	destination.latitude = 37.55712;
	destination.longitude = 126.99241;

	ret = route_service_find(g_service, origin, destination, NULL, 0, route_service_found_callback, NULL, &request_id);
	validate_and_next(__func__, ret, ROUTE_ERROR_NONE, "route_service_find() is failed");
}

void request_route_service_stop()
{
	if (g_service) {
		route_service_destroy(g_service);
	}

	if (g_route) {
		route_destroy(g_route);
	}

	if (g_segment) {
		route_segment_destroy(g_segment);
	}

	if (g_step) {
		route_step_destroy(g_step);
	}
}

static void startup(void)
{
	g_setenv("PKG_NAME", "com.samsung.capi-location-route-test", 1);
	g_setenv("LOCATION_TEST_ENABLE", "1", 1);

#if !GLIB_CHECK_VERSION (2, 31, 0)
	if (!g_thread_supported()) {
		g_thread_init(NULL);
	}
#endif

	event_thread = g_thread_create(GmainThread, NULL, 1, NULL);

	request_route_service_start();
	wait_for_service(__func__);
}

static void cleanup(void)
{
	request_route_service_stop();
	g_main_loop_quit(g_mainloop);
	g_thread_join(event_thread);
}

static bool capi_route_foreach_property_cb(const char *key, const char *value, void *user_data)
{
	return TRUE;
}

static bool capi_route_foreach_segment_cb(route_segment_h segment, void *user_data)
{
	return TRUE;
}

static bool capi_segment_foreach_property_cb(const char *key, const char *value, void *user_data)
{
	return TRUE;
}

static bool capi_segment_foreach_step_cb(route_step_h step, void *user_data)
{
	return TRUE;
}

static bool capi_step_foreach_geometry_cb(location_coords_s * geometry, void *user_data)
{
	return TRUE;
}

static bool capi_step_foreach_property_cb(const char *key, const char *value, void *user_datea)
{
	return TRUE;
}

static void utc_location_route_clone_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	route_h cloned;

	ret = route_clone(&cloned, g_route);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_clone_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_clone(NULL, g_route);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_destroy_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	route_h cloned;

	ret = route_clone(&cloned, g_route);
	validate_and_next(__func__, ret, ROUTE_ERROR_NONE, "route_clone() is failed");

	ret = route_destroy(cloned);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_destroy_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_destroy(NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_get_request_id_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	int id = 0;

	ret = route_get_request_id(g_route, &id);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_get_request_id_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	int id = 0;

	ret = route_get_request_id(NULL, &id);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_get_request_id_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_get_request_id(g_route, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_get_origin_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s origin;

	ret = route_get_origin(g_route, &origin);
	if (ret == ROUTE_ERROR_RESULT_NOT_FOUND) {
		validate_eq(__func__, ret, ROUTE_ERROR_RESULT_NOT_FOUND);
	} else {
		validate_eq(__func__, ret, ROUTE_ERROR_NONE);
	}
}

static void utc_location_route_get_origin_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s origin;

	ret = route_get_origin(NULL, &origin);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_get_origin_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_get_origin(g_route, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_get_destination_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s destination;

	ret = route_get_destination(g_route, &destination);
	if (ret == ROUTE_ERROR_RESULT_NOT_FOUND) {
		validate_eq(__func__, ret, ROUTE_ERROR_RESULT_NOT_FOUND);
	} else {
		validate_eq(__func__, ret, ROUTE_ERROR_NONE);
	}
}

static void utc_location_route_get_destination_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s destination;

	ret = route_get_destination(NULL, &destination);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_get_destination_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_get_destination(g_route, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_get_geometry_bounding_box_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s top_left;
	location_coords_s bottom_right;

	ret = route_get_geometry_bounding_box(g_route, &top_left, &bottom_right);
	if (ret == ROUTE_ERROR_RESULT_NOT_FOUND) {
		validate_eq(__func__, ret, ROUTE_ERROR_RESULT_NOT_FOUND);
	} else {
		validate_eq(__func__, ret, ROUTE_ERROR_NONE);
	}
}

static void utc_location_route_get_geometry_bounding_box_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s top_left;
	location_coords_s bottom_right;

	ret = route_get_geometry_bounding_box(NULL, &top_left, &bottom_right);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_get_geometry_bounding_box_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s bottom_right;

	ret = route_get_geometry_bounding_box(g_route, NULL, &bottom_right);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_get_geometry_bounding_box_n_03(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s top_left;

	ret = route_get_geometry_bounding_box(g_route, &top_left, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_get_distance_unit_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	route_distance_unit_e unit = ROUTE_DISTANCE_UNIT_M;

	ret = route_get_distance_unit(g_route, &unit);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_get_distance_unit_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	route_distance_unit_e unit = ROUTE_DISTANCE_UNIT_M;

	ret = route_get_distance_unit(NULL, &unit);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_get_distance_unit_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_get_distance_unit(g_route, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_get_total_distance_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	double distance;

	ret = route_get_total_distance(g_route, &distance);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_get_total_distance_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	double distance;

	ret = route_get_total_distance(NULL, &distance);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_get_total_distance_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_get_total_distance(g_route, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_get_total_duration_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	long duration;

	ret = route_get_total_duration(g_route, &duration);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_get_total_duration_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	long duration;

	ret = route_get_total_duration(NULL, &duration);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_get_total_duration_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_get_total_duration(g_route, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_foreach_properties_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_foreach_properties(g_route, capi_route_foreach_property_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_foreach_properties_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_foreach_properties(NULL, capi_route_foreach_property_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_foreach_properties_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_foreach_properties(g_route, NULL, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_foreach_segments_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_foreach_segments(g_route, capi_route_foreach_segment_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_foreach_segments_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_foreach_segments(NULL, capi_route_foreach_segment_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_foreach_segments_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_foreach_segments(g_route, NULL, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_segment_clone_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	route_segment_h cloned;

	ret = route_segment_clone(&cloned, g_segment);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_segment_clone_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_segment_clone(NULL, g_segment);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_segment_destroy_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	route_segment_h cloned;

	ret = route_segment_clone(&cloned, g_segment);
	validate_and_next(__func__, ret, ROUTE_ERROR_NONE, "route_segment_clone() is failed");

	ret = route_segment_destroy(cloned);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_segment_destroy_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_segment_destroy(NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_segment_get_origin_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s origin;

	ret = route_segment_get_origin(g_segment, &origin);
	if (ret == ROUTE_ERROR_RESULT_NOT_FOUND) {
		validate_eq(__func__, ret, ROUTE_ERROR_RESULT_NOT_FOUND);
	} else {
		validate_eq(__func__, ret, ROUTE_ERROR_NONE);
	}
}

static void utc_location_route_segment_get_origin_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s origin;

	ret = route_segment_get_origin(NULL, &origin);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_segment_get_origin_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_segment_get_origin(g_segment, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_segment_get_destination_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s destination;

	ret = route_segment_get_destination(g_segment, &destination);
	if (ret == ROUTE_ERROR_RESULT_NOT_FOUND) {
		validate_eq(__func__, ret, ROUTE_ERROR_RESULT_NOT_FOUND);
	} else {
		validate_eq(__func__, ret, ROUTE_ERROR_NONE);
	}
}

static void utc_location_route_segment_get_destination_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s destination;

	ret = route_segment_get_destination(NULL, &destination);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_segment_get_destination_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_segment_get_destination(g_segment, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_segment_get_geometry_bounding_box_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s top_left;
	location_coords_s bottom_right;

	ret = route_segment_get_geometry_bounding_box(g_segment, &top_left, &bottom_right);
	if (ret == ROUTE_ERROR_RESULT_NOT_FOUND) {
		validate_eq(__func__, ret, ROUTE_ERROR_RESULT_NOT_FOUND);
	} else {
		validate_eq(__func__, ret, ROUTE_ERROR_NONE);
	}
}

static void utc_location_route_segment_get_geometry_bounding_box_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s top_left;
	location_coords_s bottom_right;

	ret = route_segment_get_geometry_bounding_box(NULL, &top_left, &bottom_right);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_segment_get_geometry_bounding_box_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s top_left;

	ret = route_segment_get_geometry_bounding_box(g_segment, &top_left, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_segment_get_geometry_bounding_box_n_03(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s bottom_right;

	ret = route_segment_get_geometry_bounding_box(g_segment, NULL, &bottom_right);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_segment_get_distance_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	double distance;

	ret = route_segment_get_distance(g_segment, &distance);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_segment_get_distance_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	double distance;

	ret = route_segment_get_distance(NULL, &distance);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_segment_get_distance_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_segment_get_distance(g_segment, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_segment_get_duration_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	long duration;

	ret = route_segment_get_duration(g_segment, &duration);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_segment_get_duration_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	long duration;

	ret = route_segment_get_duration(NULL, &duration);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_segment_get_duration_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_segment_get_duration(g_segment, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_segment_foreach_properties_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_segment_foreach_properties(g_segment, capi_segment_foreach_property_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_segment_foreach_properties_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_segment_foreach_properties(NULL, capi_segment_foreach_property_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_segment_foreach_properties_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_segment_foreach_properties(g_segment, NULL, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_segment_foreach_steps_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_segment_foreach_steps(g_segment, capi_segment_foreach_step_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_segment_foreach_steps_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_segment_foreach_steps(NULL, capi_segment_foreach_step_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_segment_foreach_steps_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_segment_foreach_steps(g_segment, NULL, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_step_clone_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	route_step_h cloned;

	ret = route_step_clone(&cloned, g_step);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_step_clone_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_step_clone(NULL, g_step);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_step_destroy_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	route_step_h cloned;

	ret = route_step_clone(&cloned, g_step);
	validate_and_next(__func__, ret, ROUTE_ERROR_NONE, "route_step_clone() is failed");

	ret = route_step_destroy(cloned);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_step_destroy_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_step_destroy(NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_step_get_origin_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s origin;

	ret = route_step_get_origin(g_step, &origin);
	if (ret == ROUTE_ERROR_RESULT_NOT_FOUND) {
		validate_eq(__func__, ret, ROUTE_ERROR_RESULT_NOT_FOUND);
	} else {
		validate_eq(__func__, ret, ROUTE_ERROR_NONE);
	}
}

static void utc_location_route_step_get_origin_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s origin;

	ret = route_step_get_origin(NULL, &origin);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_step_get_origin_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_step_get_origin(g_step, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_step_get_destination_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s destination;

	ret = route_step_get_destination(g_step, &destination);
	if (ret == ROUTE_ERROR_RESULT_NOT_FOUND) {
		validate_eq(__func__, ret, ROUTE_ERROR_RESULT_NOT_FOUND);
	} else {
		validate_eq(__func__, ret, ROUTE_ERROR_NONE);
	}
}

static void utc_location_route_step_get_destination_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s destination;

	ret = route_step_get_destination(NULL, &destination);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_step_get_destination_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_step_get_destination(g_step, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_step_get_geometry_bounding_box_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s top_left;
	location_coords_s bottom_right;

	ret = route_step_get_geometry_bounding_box(g_step, &top_left, &bottom_right);
	if (ret == ROUTE_ERROR_RESULT_NOT_FOUND) {
		validate_eq(__func__, ret, ROUTE_ERROR_RESULT_NOT_FOUND);
	} else {
		validate_eq(__func__, ret, ROUTE_ERROR_NONE);
	}
}

static void utc_location_route_step_get_geometry_bounding_box_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s top_left;
	location_coords_s bottom_right;

	ret = route_step_get_geometry_bounding_box(NULL, &top_left, &bottom_right);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_step_get_geometry_bounding_box_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s top_left;

	ret = route_step_get_geometry_bounding_box(g_step, &top_left, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_step_get_geometry_bounding_box_n_03(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s bottom_right;

	ret = route_step_get_geometry_bounding_box(g_step, NULL, &bottom_right);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_step_get_distance_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	double distance;

	ret = route_step_get_distance(g_step, &distance);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_step_get_distance_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	double distance;

	ret = route_step_get_distance(NULL, &distance);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_step_get_distance_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_step_get_distance(g_step, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_step_get_duration_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	long duration;

	ret = route_step_get_duration(g_step, &duration);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_step_get_duration_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	long duration;

	ret = route_step_get_duration(NULL, &duration);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_step_get_duration_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_step_get_duration(g_step, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_step_get_transport_mode_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	char *mode = NULL;

	ret = route_step_get_transport_mode(g_step, &mode);
	if (mode != NULL) {
		free(mode);
	}

	if (ret == ROUTE_ERROR_RESULT_NOT_FOUND) {
		validate_eq(__func__, ret, ROUTE_ERROR_RESULT_NOT_FOUND);
	} else {
		validate_eq(__func__, ret, ROUTE_ERROR_NONE);
	}
}

static void utc_location_route_step_get_transport_mode_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	char *mode = NULL;

	ret = route_step_get_transport_mode(NULL, &mode);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_step_get_transport_mode_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_step_get_transport_mode(g_step, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_step_get_instruction_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	char *instruction = NULL;

	ret = route_step_get_instruction(g_step, &instruction);
	if (instruction != NULL) {
		free(instruction);
	}

	if (ret == ROUTE_ERROR_RESULT_NOT_FOUND) {
		validate_eq(__func__, ret, ROUTE_ERROR_RESULT_NOT_FOUND);
	} else {
		validate_eq(__func__, ret, ROUTE_ERROR_NONE);
	}
}

static void utc_location_route_step_get_instruction_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	char *instruction = NULL;

	ret = route_step_get_instruction(NULL, &instruction);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_step_get_instruction_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_step_get_instruction(g_step, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_step_foreach_geometries_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_step_foreach_geometries(g_step, capi_step_foreach_geometry_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_step_foreach_geometries_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_step_foreach_geometries(NULL, capi_step_foreach_geometry_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_step_foreach_geometries_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_step_foreach_geometries(g_step, NULL, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_step_foreach_properties_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_step_foreach_properties(g_step, capi_step_foreach_property_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_step_foreach_properties_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_step_foreach_properties(NULL, capi_step_foreach_property_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_step_foreach_properties_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_step_foreach_properties(g_step, NULL, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

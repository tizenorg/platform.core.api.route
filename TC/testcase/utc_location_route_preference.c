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

/*
 * This testcase is only for decarta.
 */
#include <tet_api.h>

#include <route_service.h>
#include <route_preference.h>
#include <glib.h>

enum {
	POSITIVE_TC_IDX = 0x01,
	NEGATIVE_TC_IDX,
};

static void startup(void);
static void cleanup(void);

void (*tet_startup) (void) = startup;
void (*tet_cleanup) (void) = cleanup;

static void utc_location_route_preference_create_p(void);
static void utc_location_route_preference_create_n(void);
static void utc_location_route_preference_foreach_addresses_to_avoid_p(void);
static void utc_location_route_preference_foreach_addresses_to_avoid_n(void);
static void utc_location_route_preference_foreach_addresses_to_avoid_n_02(void);
static void utc_location_route_preference_foreach_areas_to_avoid_p(void);
static void utc_location_route_preference_foreach_areas_to_avoid_n(void);
static void utc_location_route_preference_foreach_areas_to_avoid_n_02(void);
static void utc_location_route_preference_foreach_constraints_p(void);
static void utc_location_route_preference_foreach_constraints_n(void);
static void utc_location_route_preference_foreach_constraints_n_02(void);
static void utc_location_route_preference_foreach_properties_p(void);
static void utc_location_route_preference_foreach_properties_n(void);
static void utc_location_route_preference_foreach_properties_n_02(void);
static void utc_location_route_preference_get_geometry_bounding_box_p(void);
static void utc_location_route_preference_get_geometry_bounding_box_n(void);
static void utc_location_route_preference_get_geometry_bounding_box_n_02(void);
static void utc_location_route_preference_get_geometry_bounding_box_n_03(void);
static void utc_location_route_preference_get_max_results_p(void);
static void utc_location_route_preference_get_max_results_n(void);
static void utc_location_route_preference_get_max_results_n_02(void);
static void utc_location_route_preference_get_goal_p(void);
static void utc_location_route_preference_get_goal_n(void);
static void utc_location_route_preference_get_goal_n_02(void);
static void utc_location_route_preference_get_transport_mode_p(void);
static void utc_location_route_preference_get_transport_mode_n(void);
static void utc_location_route_preference_get_transport_mode_n_02(void);
static void utc_location_route_preference_is_geometry_used_p(void);
static void utc_location_route_preference_is_geometry_used_n(void);
static void utc_location_route_preference_is_instruction_bounding_box_used_p(void);
static void utc_location_route_preference_is_instruction_bounding_box_used_n(void);
static void utc_location_route_preference_is_instruction_geometry_used_p(void);
static void utc_location_route_preference_is_instruction_geometry_used_n(void);
static void utc_location_route_preference_is_instruction_used_p(void);
static void utc_location_route_preference_is_instruction_used_n(void);
static void utc_location_route_preference_is_traffic_data_used_p(void);
static void utc_location_route_preference_is_traffic_data_used_n(void);
static void utc_location_route_preference_get_p(void);
static void utc_location_route_preference_get_n(void);
static void utc_location_route_preference_get_n_02(void);
static void utc_location_route_preference_get_n_03(void);
static void utc_location_route_preference_set_p(void);
static void utc_location_route_preference_set_n(void);
static void utc_location_route_preference_set_n_02(void);
static void utc_location_route_preference_set_n_03(void);
static void utc_location_route_preference_add_address_to_avoid_p(void);
static void utc_location_route_preference_add_address_to_avoid_n(void);
static void utc_location_route_preference_add_address_to_avoid_n_02(void);
static void utc_location_route_preference_clear_addresses_to_avoid_p(void);
static void utc_location_route_preference_clear_addresses_to_avoid_n(void);
static void utc_location_route_preference_add_area_to_avoid_p(void);
static void utc_location_route_preference_add_area_to_avoid_n(void);
static void utc_location_route_preference_add_area_to_avoid_n_02(void);
static void utc_location_route_preference_clear_areas_to_avoid_p(void);
static void utc_location_route_preference_clear_areas_to_avoid_n(void);
static void utc_location_route_preference_add_constraint_p(void);
static void utc_location_route_preference_add_constraint_n(void);
static void utc_location_route_preference_add_constraint_n_02(void);
static void utc_location_route_preference_clear_constraints_p(void);
static void utc_location_route_preference_clear_constraints_n(void);
static void utc_location_route_preference_set_geometry_bounding_box_p(void);
static void utc_location_route_preference_set_geometry_bounding_box_n(void);
static void utc_location_route_preference_set_max_results_p(void);
static void utc_location_route_preference_set_max_results_n(void);
static void utc_location_route_preference_set_goal_p(void);
static void utc_location_route_preference_set_goal_n(void);
static void utc_location_route_preference_set_goal_n_02(void);
static void utc_location_route_preference_set_transport_mode_p(void);
static void utc_location_route_preference_set_transport_mode_n(void);
static void utc_location_route_preference_set_transport_mode_n_02(void);
static void utc_location_route_preference_set_geometry_used_p(void);
static void utc_location_route_preference_set_geometry_used_p_02(void);
static void utc_location_route_preference_set_geometry_used_n(void);
static void utc_location_route_preference_set_instruction_bounding_box_used_p(void);
static void utc_location_route_preference_set_instruction_bounding_box_used_p_02(void);
static void utc_location_route_preference_set_instruction_bounding_box_used_n(void);
static void utc_location_route_preference_set_instruction_geometry_used_p(void);
static void utc_location_route_preference_set_instruction_geometry_used_p_02(void);
static void utc_location_route_preference_set_instruction_geometry_used_n(void);
static void utc_location_route_preference_set_instruction_used_p(void);
static void utc_location_route_preference_set_instruction_used_p_02(void);
static void utc_location_route_preference_set_instruction_used_n(void);
static void utc_location_route_preference_set_traffic_data_used_p(void);
static void utc_location_route_preference_set_traffic_data_used_p_02(void);
static void utc_location_route_preference_set_traffic_data_used_n(void);
static void utc_location_route_preference_is_area_to_avoid_supported_p(void);
static void utc_location_route_preference_is_area_to_avoid_supported_p_02(void);
static void utc_location_route_preference_is_area_to_avoid_supported_p_03(void);
static void utc_location_route_preference_is_area_to_avoid_supported_n(void);
static void utc_location_route_preference_is_address_to_avoid_supported_p(void);
static void utc_location_route_preference_is_address_to_avoid_supported_n(void);
static void utc_location_route_preference_is_geometry_bounding_box_supported_p(void);
static void utc_location_route_preference_is_geometry_bounding_box_supported_n(void);
static void utc_location_route_preference_is_geometry_supported_p(void);
static void utc_location_route_preference_is_geometry_supported_n(void);
static void utc_location_route_preference_is_instruction_geometry_supported_p(void);
static void utc_location_route_preference_is_instruction_geometry_supported_n(void);
static void utc_location_route_preference_is_instruction_bounding_box_supported_p(void);
static void utc_location_route_preference_is_instruction_bounding_box_supported_n(void);
static void utc_location_route_preference_is_instruction_supported_p(void);
static void utc_location_route_preference_is_instruction_supported_n(void);
static void utc_location_route_preference_is_traffic_data_supported_p(void);
static void utc_location_route_preference_is_traffic_data_supported_n(void);
static void utc_location_route_preference_foreach_available_constraints_p(void);
static void utc_location_route_preference_foreach_available_constraints_n(void);
static void utc_location_route_preference_foreach_available_constraints_n_02(void);
static void utc_location_route_preference_foreach_available_goals_p(void);
static void utc_location_route_preference_foreach_available_goals_n(void);
static void utc_location_route_preference_foreach_available_goals_n_02(void);
static void utc_location_route_preference_foreach_available_transport_modes_p(void);
static void utc_location_route_preference_foreach_available_transport_modes_n(void);
static void utc_location_route_preference_foreach_available_transport_modes_n_02(void);
static void utc_location_route_preference_foreach_available_property_keys_p(void);
static void utc_location_route_preference_foreach_available_property_keys_n(void);
static void utc_location_route_preference_foreach_available_property_keys_n_02(void);
static void utc_location_route_preference_foreach_available_property_values_p(void);
static void utc_location_route_preference_foreach_available_property_values_n(void);
static void utc_location_route_preference_foreach_available_property_values_n_02(void);
static void utc_location_route_preference_foreach_available_property_values_n_03(void);
static void utc_location_route_preference_destroy_p(void);
static void utc_location_route_preference_destroy_n(void);

struct tet_testlist tet_testlist[] = {
	{utc_location_route_preference_create_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_create_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_foreach_addresses_to_avoid_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_foreach_addresses_to_avoid_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_foreach_addresses_to_avoid_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_preference_foreach_areas_to_avoid_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_foreach_areas_to_avoid_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_foreach_areas_to_avoid_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_preference_foreach_constraints_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_foreach_constraints_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_foreach_constraints_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_preference_foreach_properties_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_foreach_properties_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_foreach_properties_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_preference_get_geometry_bounding_box_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_get_geometry_bounding_box_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_get_geometry_bounding_box_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_preference_get_geometry_bounding_box_n_03, NEGATIVE_TC_IDX},
	{utc_location_route_preference_get_max_results_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_get_max_results_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_get_max_results_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_preference_get_goal_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_get_goal_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_get_goal_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_preference_get_transport_mode_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_get_transport_mode_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_get_transport_mode_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_preference_is_geometry_used_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_is_geometry_used_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_is_instruction_bounding_box_used_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_is_instruction_bounding_box_used_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_is_instruction_geometry_used_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_is_instruction_geometry_used_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_is_instruction_used_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_is_instruction_used_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_is_traffic_data_used_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_is_traffic_data_used_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_get_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_get_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_get_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_preference_get_n_03, NEGATIVE_TC_IDX},
	{utc_location_route_preference_set_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_set_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_set_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_preference_set_n_03, NEGATIVE_TC_IDX},
	{utc_location_route_preference_add_address_to_avoid_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_add_address_to_avoid_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_add_address_to_avoid_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_preference_clear_addresses_to_avoid_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_clear_addresses_to_avoid_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_add_area_to_avoid_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_add_area_to_avoid_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_add_area_to_avoid_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_preference_clear_areas_to_avoid_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_clear_areas_to_avoid_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_add_constraint_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_add_constraint_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_add_constraint_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_preference_clear_constraints_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_clear_constraints_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_set_geometry_bounding_box_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_set_geometry_bounding_box_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_set_max_results_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_set_max_results_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_set_goal_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_set_goal_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_set_goal_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_preference_set_transport_mode_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_set_transport_mode_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_set_transport_mode_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_preference_set_geometry_used_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_set_geometry_used_p_02, POSITIVE_TC_IDX},
	{utc_location_route_preference_set_geometry_used_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_set_instruction_bounding_box_used_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_set_instruction_bounding_box_used_p_02, POSITIVE_TC_IDX},
	{utc_location_route_preference_set_instruction_bounding_box_used_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_set_instruction_geometry_used_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_set_instruction_geometry_used_p_02, POSITIVE_TC_IDX},
	{utc_location_route_preference_set_instruction_geometry_used_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_set_instruction_used_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_set_instruction_used_p_02, POSITIVE_TC_IDX},
	{utc_location_route_preference_set_instruction_used_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_set_traffic_data_used_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_set_traffic_data_used_p_02, POSITIVE_TC_IDX},
	{utc_location_route_preference_set_traffic_data_used_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_is_area_to_avoid_supported_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_is_area_to_avoid_supported_p_02, POSITIVE_TC_IDX},
	{utc_location_route_preference_is_area_to_avoid_supported_p_03, POSITIVE_TC_IDX},
	{utc_location_route_preference_is_area_to_avoid_supported_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_is_address_to_avoid_supported_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_is_address_to_avoid_supported_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_is_geometry_bounding_box_supported_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_is_geometry_bounding_box_supported_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_is_geometry_supported_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_is_geometry_supported_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_is_instruction_geometry_supported_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_is_instruction_geometry_supported_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_is_instruction_bounding_box_supported_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_is_instruction_bounding_box_supported_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_is_instruction_supported_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_is_instruction_supported_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_is_traffic_data_supported_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_is_traffic_data_supported_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_foreach_available_constraints_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_foreach_available_constraints_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_foreach_available_constraints_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_preference_foreach_available_goals_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_foreach_available_goals_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_foreach_available_goals_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_preference_foreach_available_transport_modes_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_foreach_available_transport_modes_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_foreach_available_transport_modes_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_preference_foreach_available_property_keys_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_foreach_available_property_keys_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_foreach_available_property_keys_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_preference_foreach_available_property_values_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_foreach_available_property_values_n, NEGATIVE_TC_IDX},
	{utc_location_route_preference_foreach_available_property_values_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_preference_foreach_available_property_values_n_03, NEGATIVE_TC_IDX},
	{utc_location_route_preference_destroy_p, POSITIVE_TC_IDX},
	{utc_location_route_preference_destroy_n, NEGATIVE_TC_IDX},

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

static void validate_eq_bool(char *api_name, bool act_ret, bool ext_ret)
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
static route_preference_h g_pref;

static bool route_service_found_callback(route_error_e error, int index, int total, route_h route, void *user_data)
{
	if (error != ROUTE_ERROR_NONE) {
		return FALSE;
	}

	service_enabled = TRUE;
	return TRUE;
}

void request_route_service_start()
{
	int ret, request_id;
	location_coords_s origin, destination;

	ret = route_service_create(&g_service);
	validate_and_next(__func__, ret, ROUTE_ERROR_NONE, "route_service_create() is failed");

	ret = route_preference_create(&g_pref);
	validate_and_next(__func__, ret, ROUTE_ERROR_NONE, "route_preference_create() is failed");

	ret = route_service_set_preference(g_service, g_pref);

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

	if (g_pref) {
		route_preference_destroy(g_pref);
	}
}

static void startup(void)
{
	g_setenv("PKG_NAME", "com.samsung.capi-location-route-preference-test", 1);
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

static void utc_location_route_preference_create_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	route_preference_h preference;

	ret = route_preference_create(&preference);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_preference_create_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_create(NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static bool capi_route_preference_address_to_avoid_cb(const char *address, void *user_data)
{
	return true;
}

static void utc_location_route_preference_foreach_addresses_to_avoid_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_foreach_addresses_to_avoid(g_pref, capi_route_preference_address_to_avoid_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_preference_foreach_addresses_to_avoid_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_foreach_addresses_to_avoid(g_pref, NULL, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_foreach_addresses_to_avoid_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_foreach_addresses_to_avoid(NULL, capi_route_preference_address_to_avoid_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static bool capi_route_preference_area_to_avoid_cb(location_bounds_h area, void *user_data)
{
	return true;
}

static void utc_location_route_preference_foreach_areas_to_avoid_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_foreach_areas_to_avoid(g_pref, capi_route_preference_area_to_avoid_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_preference_foreach_areas_to_avoid_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_foreach_areas_to_avoid(g_pref, NULL, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_foreach_areas_to_avoid_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_foreach_areas_to_avoid(NULL, capi_route_preference_area_to_avoid_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static bool capi_route_preference_constraint_cb(const char *constraint, void *user_data)
{
	return true;
}

static void utc_location_route_preference_foreach_constraints_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_foreach_constraints(g_pref, capi_route_preference_constraint_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_preference_foreach_constraints_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_foreach_constraints(g_pref, NULL, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);

}

static void utc_location_route_preference_foreach_constraints_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_foreach_constraints(NULL, capi_route_preference_constraint_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);

}

static bool capi_route_preference_property_cb(const char *key, const char *value, void *user_data)
{
	return true;
}

static void utc_location_route_preference_foreach_properties_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_foreach_properties(g_pref, capi_route_preference_property_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_preference_foreach_properties_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_foreach_properties(g_pref, NULL, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);

}

static void utc_location_route_preference_foreach_properties_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_foreach_properties(NULL, capi_route_preference_property_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);

}

static void utc_location_route_preference_get_geometry_bounding_box_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s top_left;
	location_coords_s bottom_right;

	ret = route_preference_get_geometry_bounding_box(g_pref, &top_left, &bottom_right);
	if (ret == ROUTE_ERROR_RESULT_NOT_FOUND) {
		validate_eq(__func__, ret, ROUTE_ERROR_RESULT_NOT_FOUND);
	} else {
		validate_eq(__func__, ret, ROUTE_ERROR_NONE);
	}
}

static void utc_location_route_preference_get_geometry_bounding_box_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s top_left;
	location_coords_s bottom_right;

	ret = route_preference_get_geometry_bounding_box(NULL, &top_left, &bottom_right);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_get_geometry_bounding_box_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s bottom_right;

	ret = route_preference_get_geometry_bounding_box(g_pref, NULL, &bottom_right);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_get_geometry_bounding_box_n_03(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s top_left;

	ret = route_preference_get_geometry_bounding_box(g_pref, &top_left, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_get_max_results_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	int max_results;

	ret = route_preference_get_max_results(g_pref, &max_results);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_preference_get_max_results_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	int max_results;
	ret = route_preference_get_max_results(NULL, &max_results);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_get_max_results_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_get_max_results(g_pref, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_get_goal_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	char *goal = NULL;

	ret = route_preference_get_goal(g_pref, &goal);
	if (goal != NULL) {
		free(goal);
	}

	if (ret == ROUTE_ERROR_RESULT_NOT_FOUND) {
		validate_eq(__func__, ret, ROUTE_ERROR_RESULT_NOT_FOUND);
	} else {
		validate_eq(__func__, ret, ROUTE_ERROR_NONE);
	}
}

static void utc_location_route_preference_get_goal_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	char *goal = NULL;

	ret = route_preference_get_goal(NULL, &goal);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_get_goal_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_get_goal(g_pref, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_get_transport_mode_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	char *mode = NULL;

	ret = route_preference_get_transport_mode(g_pref, &mode);
	if (mode != NULL) {
		free(mode);
	}

	if (ret == ROUTE_ERROR_RESULT_NOT_FOUND) {
		validate_eq(__func__, ret, ROUTE_ERROR_RESULT_NOT_FOUND);
	} else {
		validate_eq(__func__, ret, ROUTE_ERROR_NONE);
	}
}

static void utc_location_route_preference_get_transport_mode_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	char *mode = NULL;

	ret = route_preference_get_transport_mode(NULL, &mode);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_get_transport_mode_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_get_transport_mode(g_pref, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_is_geometry_used_p(void)
{
	bool ret = true;

	ret = route_preference_is_geometry_used(g_pref);
	validate_eq_bool(__func__, ret, false);
}

static void utc_location_route_preference_is_geometry_used_n(void)
{
	bool ret = true;

	ret = route_preference_is_geometry_used(NULL);
	validate_eq_bool(__func__, ret, false);
}

static void utc_location_route_preference_is_instruction_bounding_box_used_p(void)
{
	bool ret = true;

	ret = route_preference_is_instruction_bounding_box_used(g_pref);
	validate_eq_bool(__func__, ret, false);
}

static void utc_location_route_preference_is_instruction_bounding_box_used_n(void)
{
	bool ret = true;

	ret = route_preference_is_instruction_bounding_box_used(NULL);
	validate_eq_bool(__func__, ret, false);
}

static void utc_location_route_preference_is_instruction_geometry_used_p(void)
{
	bool ret = true;

	ret = route_preference_is_instruction_geometry_used(g_pref);
	validate_eq_bool(__func__, ret, false);
}

static void utc_location_route_preference_is_instruction_geometry_used_n(void)
{
	bool ret = true;

	ret = route_preference_is_instruction_geometry_used(NULL);
	validate_eq_bool(__func__, ret, false);
}

static void utc_location_route_preference_is_instruction_used_p(void)
{
	bool ret = true;

	ret = route_preference_is_instruction_used(g_pref);
	validate_eq_bool(__func__, ret, false);
}

static void utc_location_route_preference_is_instruction_used_n(void)
{
	bool ret = true;

	ret = route_preference_is_instruction_used(NULL);
	validate_eq_bool(__func__, ret, false);
}

static void utc_location_route_preference_is_traffic_data_used_p(void)
{
	bool ret = true;

	ret = route_preference_is_traffic_data_used(g_pref);
	validate_eq_bool(__func__, ret, false);
}

static void utc_location_route_preference_is_traffic_data_used_n(void)
{
	bool ret = true;

	ret = route_preference_is_traffic_data_used(NULL);
	validate_eq_bool(__func__, ret, false);
}

static void utc_location_route_preference_get_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	char *value = NULL;

	route_preference_set(g_pref, "LandmarkType", "hotel");

	ret = route_preference_get(g_pref, "LandmarkType", &value);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_preference_get_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	char *value = NULL;

	ret = route_preference_get(NULL, "LandmarkType", &value);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_get_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;
	char *value = NULL;

	ret = route_preference_get(g_pref, NULL, &value);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_get_n_03(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_get(g_pref, "LandmarkType", NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_set_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set(g_pref, "LandmarkType", "hotel");
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);

}

static void utc_location_route_preference_set_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set(NULL, "LandmarkType", "hotel");
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_set_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set(g_pref, NULL, "hotel");
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_set_n_03(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set(g_pref, "LandmarkType", NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_add_address_to_avoid_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_add_address_to_avoid(g_pref, "Grand Central Pky");
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);

}

static void utc_location_route_preference_add_address_to_avoid_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_add_address_to_avoid(NULL, "Grand Central Pky");
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_add_address_to_avoid_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_add_address_to_avoid(g_pref, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_clear_addresses_to_avoid_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_clear_addresses_to_avoid(g_pref);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);

}

static void utc_location_route_preference_clear_addresses_to_avoid_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_clear_addresses_to_avoid(NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_add_area_to_avoid_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	location_bounds_h area;
	location_coords_s top_left = { 30, 30 };
	location_coords_s bottom_right = { 10, 50 };
	location_bounds_create_rect(top_left, bottom_right, &area);

	ret = route_preference_add_area_to_avoid(g_pref, area);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);

}

static void utc_location_route_preference_add_area_to_avoid_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	location_bounds_h area;
	location_coords_s top_left = { 30, 30 };
	location_coords_s bottom_right = { 10, 50 };
	location_bounds_create_rect(top_left, bottom_right, &area);

	ret = route_preference_add_area_to_avoid(NULL, area);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_add_area_to_avoid_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_add_area_to_avoid(g_pref, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_clear_areas_to_avoid_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_clear_areas_to_avoid(g_pref);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_preference_clear_areas_to_avoid_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_clear_areas_to_avoid(NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_add_constraint_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_add_constraint(g_pref, "BRIDGES");
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_preference_add_constraint_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_add_constraint(NULL, "BRIDGES");
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_add_constraint_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_add_constraint(g_pref, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_clear_constraints_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_clear_constraints(g_pref);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_preference_clear_constraints_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_clear_constraints(NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_set_geometry_bounding_box_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s top_left = { 30, 30 };
	location_coords_s bottom_right = { 10, 50 };

	ret = route_preference_set_geometry_bounding_box(g_pref, top_left, bottom_right);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_preference_set_geometry_bounding_box_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s top_left = { 30, 30 };
	location_coords_s bottom_right = { 10, 50 };

	ret = route_preference_set_geometry_bounding_box(NULL, top_left, bottom_right);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_set_max_results_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set_max_results(g_pref, 5);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_preference_set_max_results_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set_max_results(NULL, 5);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_set_goal_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set_goal(g_pref, "FASTEST");
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);

}

static void utc_location_route_preference_set_goal_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set_goal(NULL, "FASTEST");
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_set_goal_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set_goal(g_pref, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_set_transport_mode_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set_transport_mode(g_pref, "Vehicle");
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_preference_set_transport_mode_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set_transport_mode(NULL, "CAR");
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);

}

static void utc_location_route_preference_set_transport_mode_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set_transport_mode(g_pref, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);

}

static void utc_location_route_preference_set_geometry_used_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set_geometry_used(g_pref, false);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);

}

static void utc_location_route_preference_set_geometry_used_p_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set_geometry_used(g_pref, true);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_preference_set_geometry_used_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set_geometry_used(NULL, true);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);

}

static void utc_location_route_preference_set_instruction_bounding_box_used_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set_instruction_bounding_box_used(g_pref, false);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);

}

static void utc_location_route_preference_set_instruction_bounding_box_used_p_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set_instruction_bounding_box_used(g_pref, true);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);

}

static void utc_location_route_preference_set_instruction_bounding_box_used_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set_instruction_bounding_box_used(NULL, true);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_set_instruction_geometry_used_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set_instruction_geometry_used(g_pref, false);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_preference_set_instruction_geometry_used_p_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set_instruction_geometry_used(g_pref, true);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_preference_set_instruction_geometry_used_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set_instruction_geometry_used(NULL, true);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_set_instruction_used_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set_instruction_used(g_pref, false);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_preference_set_instruction_used_p_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set_instruction_used(g_pref, true);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_preference_set_instruction_used_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set_instruction_used(NULL, true);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_set_traffic_data_used_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set_traffic_data_used(g_pref, false);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_preference_set_traffic_data_used_p_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set_traffic_data_used(g_pref, true);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_preference_set_traffic_data_used_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_set_traffic_data_used(NULL, true);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_is_area_to_avoid_supported_p(void)
{
	bool ret = true;

	ret = route_preference_is_area_to_avoid_supported(g_service, LOCATION_BOUNDS_RECT);
	validate_eq_bool(__func__, ret, false);
}

static void utc_location_route_preference_is_area_to_avoid_supported_p_02(void)
{
	bool ret = true;

	ret = route_preference_is_area_to_avoid_supported(g_service, LOCATION_BOUNDS_CIRCLE);
	validate_eq_bool(__func__, ret, true);
}

static void utc_location_route_preference_is_area_to_avoid_supported_p_03(void)
{
	bool ret = true;

	ret = route_preference_is_area_to_avoid_supported(g_service, LOCATION_BOUNDS_POLYGON);
	validate_eq_bool(__func__, ret, false);
}

static void utc_location_route_preference_is_area_to_avoid_supported_n(void)
{
	bool ret = true;

	ret = route_preference_is_area_to_avoid_supported(NULL, LOCATION_BOUNDS_CIRCLE);
	validate_eq_bool(__func__, ret, false);
}

static void utc_location_route_preference_is_address_to_avoid_supported_p(void)
{
	bool ret = true;

	ret = route_preference_is_address_to_avoid_supported(g_service);
	validate_eq_bool(__func__, ret, true);
}

static void utc_location_route_preference_is_address_to_avoid_supported_n(void)
{
	bool ret = true;

	ret = route_preference_is_address_to_avoid_supported(NULL);
	validate_eq_bool(__func__, ret, false);
}

static void utc_location_route_preference_is_geometry_bounding_box_supported_p(void)
{
	bool ret = true;

	ret = route_preference_is_geometry_bounding_box_supported(g_service);
	validate_eq_bool(__func__, ret, true);
}

static void utc_location_route_preference_is_geometry_bounding_box_supported_n(void)
{
	bool ret = true;

	ret = route_preference_is_geometry_bounding_box_supported(NULL);
	validate_eq_bool(__func__, ret, false);
}

static void utc_location_route_preference_is_geometry_supported_p(void)
{
	bool ret = true;

	ret = route_preference_is_geometry_supported(g_service);
	validate_eq_bool(__func__, ret, true);
}

static void utc_location_route_preference_is_geometry_supported_n(void)
{
	bool ret = true;

	ret = route_preference_is_geometry_supported(NULL);
	validate_eq_bool(__func__, ret, false);
}

static void utc_location_route_preference_is_instruction_geometry_supported_p(void)
{
	bool ret = true;

	ret = route_preference_is_instruction_geometry_supported(g_service);
	validate_eq_bool(__func__, ret, true);
}

static void utc_location_route_preference_is_instruction_geometry_supported_n(void)
{
	bool ret = true;

	ret = route_preference_is_instruction_geometry_supported(NULL);
	validate_eq_bool(__func__, ret, false);
}

static void utc_location_route_preference_is_instruction_bounding_box_supported_p(void)
{
	bool ret = true;

	ret = route_preference_is_instruction_bounding_box_supported(g_service);
	validate_eq_bool(__func__, ret, true);
}

static void utc_location_route_preference_is_instruction_bounding_box_supported_n(void)
{
	bool ret = true;

	ret = route_preference_is_instruction_bounding_box_supported(NULL);
	validate_eq_bool(__func__, ret, false);
}

static void utc_location_route_preference_is_instruction_supported_p(void)
{
	bool ret = true;

	ret = route_preference_is_instruction_supported(g_service);
	validate_eq_bool(__func__, ret, true);
}

static void utc_location_route_preference_is_instruction_supported_n(void)
{
	bool ret = true;

	ret = route_preference_is_instruction_supported(NULL);
	validate_eq_bool(__func__, ret, false);
}

static void utc_location_route_preference_is_traffic_data_supported_p(void)
{
	bool ret = true;

	ret = route_preference_is_traffic_data_supported(g_service);
	validate_eq_bool(__func__, ret, true);
}

static void utc_location_route_preference_is_traffic_data_supported_n(void)
{
	bool ret = true;

	ret = route_preference_is_traffic_data_supported(NULL);
	validate_eq_bool(__func__, ret, false);
}

static bool capi_route_preference_available_constraint_cb(const char *constraint, void *user_data)
{
	return true;
}

static void utc_location_route_preference_foreach_available_constraints_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_foreach_available_constraints(g_service, capi_route_preference_available_constraint_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_preference_foreach_available_constraints_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_foreach_available_constraints(NULL, capi_route_preference_available_constraint_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_foreach_available_constraints_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_foreach_available_constraints(g_service, NULL, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static bool capi_route_preference_available_goal_cb(const char *goal, void *user_data)
{
	return true;
}

static void utc_location_route_preference_foreach_available_goals_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_foreach_available_goals(g_service, capi_route_preference_available_goal_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_preference_foreach_available_goals_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_foreach_available_goals(NULL, capi_route_preference_available_goal_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_foreach_available_goals_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_foreach_available_goals(g_service, NULL, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static bool capi_route_preference_available_transport_mode_cb(const char *mode, void *user_data)
{
	return true;
}

static void utc_location_route_preference_foreach_available_transport_modes_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret =
	    route_preference_foreach_available_transport_modes(g_service, capi_route_preference_available_transport_mode_cb,
							       NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);

}

static void utc_location_route_preference_foreach_available_transport_modes_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_foreach_available_transport_modes(NULL, capi_route_preference_available_transport_mode_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_foreach_available_transport_modes_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_foreach_available_transport_modes(g_service, NULL, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static bool capi_route_preference_available_property_key_cb(const char *key, void *user_data)
{
	return true;
}

static void utc_location_route_preference_foreach_available_property_keys_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret =
	    route_preference_foreach_available_property_keys(g_service, capi_route_preference_available_property_key_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);

}

static void utc_location_route_preference_foreach_available_property_keys_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_foreach_available_property_keys(NULL, capi_route_preference_available_property_key_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_foreach_available_property_keys_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_foreach_available_property_keys(g_service, NULL, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static bool capi_route_preference_available_property_value_cb(const char *value, void *user_data)
{
	return true;
}

static void utc_location_route_preference_foreach_available_property_values_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret =
	    route_preference_foreach_available_property_values(g_service, "LandmarkType",
							       capi_route_preference_available_property_value_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);

}

static void utc_location_route_preference_foreach_available_property_values_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret =
	    route_preference_foreach_available_property_values(NULL, "LandmarkType",
							       capi_route_preference_available_property_value_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_foreach_available_property_values_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret =
	    route_preference_foreach_available_property_values(g_service, NULL,
							       capi_route_preference_available_property_value_cb, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_foreach_available_property_values_n_03(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_foreach_available_property_values(g_service, "LandmarkType", NULL, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_preference_destroy_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_destroy(g_pref);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_preference_destroy_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_preference_destroy(NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

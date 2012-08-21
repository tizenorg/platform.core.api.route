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
#include <glib.h>

enum {
	POSITIVE_TC_IDX = 0x01,
	NEGATIVE_TC_IDX,
};

static void startup(void);
static void cleanup(void);

void (*tet_startup) (void) = startup;
void (*tet_cleanup) (void) = cleanup;

static void utc_location_route_service_create_p(void);
static void utc_location_route_service_create_n(void);
static void utc_location_route_service_get_preference_p(void);
static void utc_location_route_service_get_preference_n(void);
static void utc_location_route_service_get_preference_n_02(void);
static void utc_location_route_service_set_preference_p(void);
static void utc_location_route_service_set_preference_n(void);
static void utc_location_route_service_set_preference_n_02(void);
static void utc_location_route_service_find_p(void);
static void utc_location_route_service_find_n(void);
static void utc_location_route_service_find_n_02(void);
static void utc_location_route_service_cancel_p(void);
static void utc_location_route_service_cancel_n(void);
static void utc_location_route_service_destroy_p(void);
static void utc_location_route_service_destroy_n(void);

struct tet_testlist tet_testlist[] = {
	{utc_location_route_service_create_p, POSITIVE_TC_IDX},
	{utc_location_route_service_create_n, NEGATIVE_TC_IDX},
	{utc_location_route_service_get_preference_p, POSITIVE_TC_IDX},
	{utc_location_route_service_get_preference_n, NEGATIVE_TC_IDX},
	{utc_location_route_service_get_preference_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_service_set_preference_p, POSITIVE_TC_IDX},
	{utc_location_route_service_set_preference_n, NEGATIVE_TC_IDX},
	{utc_location_route_service_set_preference_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_service_find_p, POSITIVE_TC_IDX},
	{utc_location_route_service_find_n, NEGATIVE_TC_IDX},
	{utc_location_route_service_find_n_02, NEGATIVE_TC_IDX},
	{utc_location_route_service_cancel_p, POSITIVE_TC_IDX},
	{utc_location_route_service_cancel_n, NEGATIVE_TC_IDX},
	{utc_location_route_service_destroy_p, POSITIVE_TC_IDX},
	{utc_location_route_service_destroy_n, NEGATIVE_TC_IDX},

	{NULL, 0},
};

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

static void startup(void)
{
	g_setenv("PKG_NAME", "com.samsung.capi-location-route-service-test", 1);
	g_setenv("LOCATION_TEST_ENABLE", "1", 1);

#if !GLIB_CHECK_VERSION (2, 31, 0)
	if (!g_thread_supported()) {
		g_thread_init(NULL);
	}
#endif
	event_thread = g_thread_create(GmainThread, NULL, 1, NULL);
}

static void cleanup(void)
{
	g_main_loop_quit(g_mainloop);
	g_thread_join(event_thread);
}

static route_service_h g_service;
int g_request_id;
static bool service_enabled = FALSE;

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

static void utc_location_route_service_create_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_service_create(&g_service);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_service_create_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_service_create(NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_service_get_preference_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	route_preference_h pref = NULL;
	ret = route_preference_create(&pref);
	validate_and_next(__func__, ret, ROUTE_ERROR_NONE, "route_preference_create() is failed");

	ret = route_service_get_preference(g_service, &pref);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_service_get_preference_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_service_get_preference(g_service, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_service_get_preference_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	route_preference_h pref;
	ret = route_preference_create(&pref);
	validate_and_next(__func__, ret, ROUTE_ERROR_NONE, "route_preference_create() is failed");

	ret = route_service_get_preference(NULL, pref);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_service_set_preference_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	route_preference_h pref = NULL;
	ret = route_preference_create(&pref);
	validate_and_next(__func__, ret, ROUTE_ERROR_NONE, "route_preference_create() is failed");

	ret = route_service_set_preference(g_service, pref);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_service_set_preference_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	route_preference_h pref;
	ret = route_preference_create(&pref);
	validate_and_next(__func__, ret, ROUTE_ERROR_NONE, "route_preference_create() is failed");

	ret = route_service_set_preference(g_service, NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_service_set_preference_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;

	route_preference_h pref;
	ret = route_preference_create(&pref);
	validate_and_next(__func__, ret, ROUTE_ERROR_NONE, "route_preference_create() is failed");

	ret = route_service_set_preference(NULL, pref);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static bool capi_route_service_found_cb(route_error_e error, int index, int total, route_h route, void *user_data)
{
	if (error != ROUTE_ERROR_NONE) {
		return FALSE;
	}

	service_enabled = TRUE;
	return TRUE;
}

static void utc_location_route_service_find_p(void)
{
	int ret = ROUTE_ERROR_NONE;
	location_coords_s origin = { 37.564263, 126.974676 };
	location_coords_s destination = { 37.557120, 126.992410 };

	ret = route_service_find(g_service, origin, destination, NULL, 0, capi_route_service_found_cb, NULL, &g_request_id);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
	wait_for_service("route_service_find");
}

static void utc_location_route_service_find_n(void)
{
	int ret = ROUTE_ERROR_NONE;
	int request_id;
	location_coords_s origin = { 37.564263, 126.974676 };
	location_coords_s destination = { 37.557120, 126.992410 };

	ret = route_service_find(NULL, origin, destination, NULL, 0, capi_route_service_found_cb, NULL, &request_id);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_service_find_n_02(void)
{
	int ret = ROUTE_ERROR_NONE;
	int request_id;
	location_coords_s origin = { 37.564263, 126.974676 };
	location_coords_s destination = { 37.557120, 126.992410 };

	ret = route_service_find(g_service, origin, destination, NULL, 0, NULL, NULL, &request_id);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

static void utc_location_route_service_cancel_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_service_cancel(g_service, g_request_id);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_service_cancel_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_service_cancel(NULL, g_request_id);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);

}

static void utc_location_route_service_destroy_p(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_service_destroy(g_service);
	validate_eq(__func__, ret, ROUTE_ERROR_NONE);
}

static void utc_location_route_service_destroy_n(void)
{
	int ret = ROUTE_ERROR_NONE;

	ret = route_service_destroy(NULL);
	validate_eq(__func__, ret, ROUTE_ERROR_INVALID_PARAMETER);
}

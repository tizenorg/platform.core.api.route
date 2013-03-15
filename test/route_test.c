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

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <glib.h>

#include <location_bounds.h>
#include <route_service.h>
#include <route_preference.h>
#include <route.h>

route_service_h service;

#define ROUTE_TEST_PRINT_RETURN(api, ret)	\
	if (ret == 0) { } else	\
        { printf("Error [%s] return (0x%08x)\n", api, ret); };	\


#define ROUTE_TEST_PRINT_BOOL(api, bret)	\
	if (bret)	\
	{ printf("[TRUE ] %s\n", api); } else	\
        { printf("[FASLE] %s\n", api); };	\

static bool route_preference_available_property_value_callback(const char *value, void *user_data)
{
	printf("===== route_preference_available_property_value_callback ======\n");

	if (value == NULL) {
		printf("value is NULL\n");
		return FALSE;
	}

	printf("value : %s\n", value);
	return TRUE;
}

static bool route_preference_available_property_key_callback(const char *key, void *user_data)
{
	printf("===== route_preference_available_property_key_callback ======\n");

	if (key == NULL) {
		printf("key is NULL\n");
		return FALSE;
	}

	printf("key : %s\n", key);

	int ret =
	    route_preference_foreach_available_property_values(service, key, route_preference_available_property_value_callback,
							       NULL);
	ROUTE_TEST_PRINT_RETURN("route_preference_foreach_available_property_values", ret);
	return TRUE;
}

static bool route_preference_available_constraint_callback(const char *constraint, void *user_data)
{
	printf("===== route_preference_available_constraint_callback ======\n");

	if (constraint == NULL) {
		printf("constraint is NULL\n");
		return FALSE;
	}

	printf("constraint : %s\n", constraint);
	return TRUE;

}

static bool route_preference_available_goal_callback(const char *goal, void *user_data)
{
	printf("===== route_preference_available_goal_callback ======\n");

	if (goal == NULL) {
		printf("goal is NULL\n");
		return FALSE;
	}

	printf("goal : %s\n", goal);
	return TRUE;
}

static bool route_preference_available_transport_mode_callback(const char *mode, void *user_data)
{
	printf("===== route_preference_available_transport_mode_callback ======\n");

	if (mode == NULL) {
		printf("mode is NULL\n");
		return FALSE;
	}

	printf("mode : %s\n", mode);
	return TRUE;

}

static bool route_preference_property_callback(const char *key, const char *value, void *user_data)
{
	printf("===== route_preference_property_callback ======\n");

	if (key == NULL) {
		printf("key is NULL\n");
		return FALSE;
	}

	printf("key : %s value : %s\n", key, value);
	return TRUE;
}

static bool route_preference_address_to_avoid_callback(const char *address, void *user_data)
{
	printf("===== route_preference_address_to_avoid_callback ======\n");

	if (address == NULL) {
		printf("address is NULL\n");
		return FALSE;
	}

	printf("address : %s\n", address);
	return TRUE;
}

static bool route_preference_area_to_avoid_callback(location_bounds_h area, void *user_data)
{
	printf("===== route_preference_area_to_avoid_callback ======\n");

	if (area == NULL) {
		printf("arer is NULL\n");
		return FALSE;
	}

	location_bounds_type_e type;
	location_bounds_get_type(area, &type);

	if (type == LOCATION_BOUNDS_CIRCLE) {
		location_coords_s center;
		double radius;
		location_bounds_get_circle_coords(area, &center, &radius);
		printf("center : %lf, %lf radius : %lf\n", center.latitude, center.longitude, radius);
	} else if (type == LOCATION_BOUNDS_RECT) {
		location_coords_s top_left;
		location_coords_s bottom_right;
		location_bounds_get_rect_coords(area, &top_left, &bottom_right);
		printf("top_left : %lf, %lf bottom_right : %lf, %lf\n", top_left.latitude, top_left.longitude,
		       bottom_right.latitude, bottom_right.longitude);
	} else if (type == LOCATION_BOUNDS_POLYGON) {
		printf("LOCATION_BOUNDS_POLYGON type\n");
	}

	return TRUE;
}

static bool route_preference_constraint_callback(const char *constraint, void *user_data)
{
	printf("===== route_preference_constraint_callback ======\n");

	if (constraint == NULL) {
		printf("constraint is NULL\n");
		return FALSE;
	}

	printf("constraint : %s\n", constraint);
	return TRUE;
}

void route_preference_test(route_preference_h pref)
{
	int ret;
	bool bret;

	ret = route_preference_create(&pref);
	ROUTE_TEST_PRINT_RETURN("route_preference_create", ret);

	// capability
	location_bounds_type_e type = LOCATION_BOUNDS_RECT;
	bret = route_preference_is_area_to_avoid_supported(service, type);
	ROUTE_TEST_PRINT_BOOL("route_preference_is_area_to_avoid_supported [RECT]", bret);

	type = LOCATION_BOUNDS_CIRCLE;
	bret = route_preference_is_area_to_avoid_supported(service, type);
	ROUTE_TEST_PRINT_BOOL("route_preference_is_area_to_avoid_supported [CIRCLE]", bret);

	type = LOCATION_BOUNDS_POLYGON;
	bret = route_preference_is_area_to_avoid_supported(service, type);
	ROUTE_TEST_PRINT_BOOL("route_preference_is_area_to_avoid_supported [POLYGON]", bret);

	bret = route_preference_is_address_to_avoid_supported(service);
	ROUTE_TEST_PRINT_BOOL("route_preference_is_address_to_avoid_supported", bret);

	bret = route_preference_is_geometry_bounding_box_supported(service);
	ROUTE_TEST_PRINT_BOOL("route_preference_is_geometry_bounding_box_supported", bret);

	bret = route_preference_is_geometry_supported(service);
	ROUTE_TEST_PRINT_BOOL("route_preference_is_geometry_supported", bret);

	bret = route_preference_is_instruction_geometry_supported(service);
	ROUTE_TEST_PRINT_BOOL("route_preference_is_instruction_geometry_supported", bret);

	bret = route_preference_is_instruction_bounding_box_supported(service);
	ROUTE_TEST_PRINT_BOOL("route_preference_is_instruction_bounding_box_supported", bret);

	bret = route_preference_is_instruction_supported(service);
	ROUTE_TEST_PRINT_BOOL("route_preference_is_instruction_supported", bret);

	bret = route_preference_is_traffic_data_supported(service);
	ROUTE_TEST_PRINT_BOOL("route_preference_is_traffic_data_supported", bret);

	ret = route_preference_foreach_available_constraints(service, route_preference_available_constraint_callback, NULL);
	ROUTE_TEST_PRINT_RETURN("route_preference_foreach_available_constraints", ret);

	ret = route_preference_foreach_available_goals(service, route_preference_available_goal_callback, NULL);
	ROUTE_TEST_PRINT_RETURN("route_preference_foreach_available_goals", ret);

	ret =
	    route_preference_foreach_available_transport_modes(service, route_preference_available_transport_mode_callback,
							       NULL);
	ROUTE_TEST_PRINT_RETURN("route_preference_foreach_available_transport_modes", ret);

	ret = route_preference_foreach_available_property_keys(service, route_preference_available_property_key_callback, NULL);
	ROUTE_TEST_PRINT_RETURN("route_preference_foreach_available_property_keys", ret);

	// set preference
	char *address = "39 Namdaemunno Jung-Gu, Seoul, 100-794, Korea";
	ret = route_preference_add_address_to_avoid(pref, address);
	ROUTE_TEST_PRINT_RETURN("route_preference_add_address_to_avoid", ret);

	location_coords_s tl;
	tl.latitude = 37.562;
	tl.longitude = 126.980661;
	location_coords_s br;
	br.latitude = 37.561;
	br.longitude = 126.990;
	location_bounds_h area;
	ret = location_bounds_create_rect(tl, br, &area);
	ROUTE_TEST_PRINT_RETURN("location_bounds_create_rect", ret);
	ret = route_preference_add_area_to_avoid(pref, area);
	ROUTE_TEST_PRINT_RETURN("route_preference_add_area_to_avoid", ret);

	char *constraint = "BRIDGES";
	ret = route_preference_add_constraint(pref, constraint);
	ROUTE_TEST_PRINT_RETURN("route_preference_add_constraint", ret);

	ret = route_preference_set_geometry_bounding_box(pref, tl, br);
	ROUTE_TEST_PRINT_RETURN("route_preference_add_constraint", ret);

	int max_results = 10;
	ret = route_preference_set_max_results(pref, max_results);
	ROUTE_TEST_PRINT_RETURN("route_preference_set_max_results", ret);

	char *goal = "FASTEST";
	ret = route_preference_set_goal(pref, goal);
	ROUTE_TEST_PRINT_RETURN("route_preference_set_goal", ret);

	char *mode = "Vehicle";
	ret = route_preference_set_transport_mode(pref, mode);
	ROUTE_TEST_PRINT_RETURN("route_preference_set_transport_mode", ret);

	bool used = TRUE;
	ret = route_preference_set_geometry_used(pref, used);
	ROUTE_TEST_PRINT_RETURN("route_preference_set_geometry_used", ret);

	ret = route_preference_set_instruction_bounding_box_used(pref, used);
	ROUTE_TEST_PRINT_RETURN("route_preference_set_instruction_bounding_box_used", ret);

	ret = route_preference_set_instruction_geometry_used(pref, used);
	ROUTE_TEST_PRINT_RETURN("route_preference_set_instruction_geometry_used", ret);

	ret = route_preference_set_instruction_used(pref, used);
	ROUTE_TEST_PRINT_RETURN("route_preference_set_instruction_used", ret);

	ret = route_preference_set_traffic_data_used(pref, used);
	ROUTE_TEST_PRINT_RETURN("route_preference_set_instruction_used", ret);

	// get preference
	ret = route_preference_foreach_addresses_to_avoid(pref, route_preference_address_to_avoid_callback, NULL);
	ROUTE_TEST_PRINT_RETURN("route_preference_foreach_addresses_to_avoid", ret);

	ret = route_preference_foreach_areas_to_avoid(pref, route_preference_area_to_avoid_callback, NULL);
	ROUTE_TEST_PRINT_RETURN("route_preference_foreach_areas_to_avoid", ret);

	ret = route_preference_foreach_constraints(pref, route_preference_constraint_callback, NULL);
	ROUTE_TEST_PRINT_RETURN("route_preference_foreach_constraints", ret);

	ret = route_preference_foreach_properties(pref, route_preference_property_callback, NULL);
	ROUTE_TEST_PRINT_RETURN("route_preference_foreach_properties", ret);

	memset(&tl, 0, sizeof(location_coords_s));
	memset(&br, 0, sizeof(location_coords_s));
	ret = route_preference_get_geometry_bounding_box(pref, &tl, &br);
	ROUTE_TEST_PRINT_RETURN("route_preference_foreach_properties", ret);
	printf("geometry tl lat : %f long : %f\n", tl.latitude, tl.longitude);
	printf("geometry br lat : %f long : %f\n", br.latitude, br.longitude);

	max_results = 0;
	ret = route_preference_get_max_results(pref, &max_results);
	ROUTE_TEST_PRINT_RETURN("route_preference_get_max_results", ret);
	printf("max_results : %d\n", max_results);

	char *get_goal;
	ret = route_preference_get_goal(pref, &get_goal);
	ROUTE_TEST_PRINT_RETURN("route_preference_get_goal", ret);
	printf("get goal : %s\n", get_goal);

	char *get_mode;
	ret = route_preference_get_transport_mode(pref, &get_mode);
	ROUTE_TEST_PRINT_RETURN("route_preference_get_transport_mode", ret);
	printf("get mode : %s\n", get_mode);

	// clear preference
	ret = route_preference_clear_addresses_to_avoid(pref);
	ROUTE_TEST_PRINT_RETURN("route_preference_clear_addresses_to_avoid", ret);

	ret = route_preference_clear_areas_to_avoid(pref);
	ROUTE_TEST_PRINT_RETURN("route_preference_clear_areas_to_avoid", ret);

	ret = route_preference_clear_constraints(pref);
	ROUTE_TEST_PRINT_RETURN("route_preference_clear_constraints", ret);

	ret = route_preference_destroy(pref);
	//ROUTE_TEST_PRINT_RETURN("route_preference_destroy", ret);
}

void route_set_preference(route_service_h pref)
{
	int ret;

	char *goal = "FASTEST";
	ret = route_preference_set_goal(pref, goal);
	ROUTE_TEST_PRINT_RETURN("route_preference_set_goal", ret);
}

static bool route_step_geometry_callback(location_coords_s * geometry, void *user_data)
{
	printf("===== route_step_geometry_callback ======\n");

	if (geometry == NULL) {
		printf("geometry is NULL\n");
		return FALSE;
	}

	printf("geometry lat : %f long : %f\n", geometry->latitude, geometry->longitude);
	return TRUE;
}

static bool route_step_property_callback(const char *key, const char *value, void *user_data)
{
	printf("===== route_step_property_callback ======\n");

	if (key == NULL) {
		printf("key is NULL\n");
		return FALSE;
	}

	printf("key : %s value : %s\n", key, value);
	return TRUE;
}

void route_step_information(route_step_h step)
{
	int ret;
	location_coords_s origin, destination;
	location_coords_s tl, br;
	double distance;
	long duration;
	char *instruction;

	ret = route_step_get_origin(step, &origin);
	ROUTE_TEST_PRINT_RETURN("route_step_get_origin", ret);
	printf("origin lat : %f long : %f\n", origin.latitude, origin.longitude);

	ret = route_step_get_destination(step, &destination);
	ROUTE_TEST_PRINT_RETURN("route_step_get_destination", ret);
	printf("destination lat : %f long : %f\n", destination.latitude, destination.longitude);

	ret = route_step_get_geometry_bounding_box(step, &tl, &br);
	ROUTE_TEST_PRINT_RETURN("route_step_get_geometry_bounding_box", ret);
	printf("bbox tl lat : %f long : %f\n", tl.latitude, tl.longitude);
	printf("bbox br lat : %f long : %f\n", br.latitude, br.longitude);

	ret = route_step_get_distance(step, &distance);
	ROUTE_TEST_PRINT_RETURN("route_step_get_distance", ret);
	printf("distance : %f\n", distance);

	ret = route_step_get_duration(step, &duration);
	ROUTE_TEST_PRINT_RETURN("route_step_get_duration", ret);
	printf("duration : %ld\n", duration);

	ret = route_step_get_instruction(step, &instruction);
	ROUTE_TEST_PRINT_RETURN("route_step_get_instruction", ret);
	printf("instruction : %s\n", instruction);

	ret = route_step_foreach_geometries(step, route_step_geometry_callback, NULL);
	ROUTE_TEST_PRINT_RETURN("oute_step_foreach_geometries", ret);

	ret = route_step_foreach_properties(step, route_step_property_callback, NULL);
	ROUTE_TEST_PRINT_RETURN("route_step_foreach_properties", ret);
}

static bool route_segment_property_callback(const char *key, const char *value, void *user_data)
{
	printf("===== route_segment_property_callback ======\n");

	if (key == NULL) {
		printf("key is NULL\n");
		return FALSE;
	}

	printf("key : %s value : %s\n", key, value);
	return TRUE;
}

static bool route_segment_step_callback(route_step_h step, void *user_data)
{
	printf("===== route_segment_step_callback ======\n");

	if (step == NULL) {
		printf("step is NULL\n");
		return FALSE;
	}

	int ret;
	route_step_h cloned_step;

	ret = route_step_clone(&cloned_step, step);
	ROUTE_TEST_PRINT_RETURN("route_step_clone", ret);

	route_step_information(cloned_step);

	ret = route_step_destroy(cloned_step);
	ROUTE_TEST_PRINT_RETURN("route_step_destroy", ret);

	return TRUE;
}

void route_segment_information(route_segment_h segment)
{
	int ret;
	location_coords_s origin, destination;
	location_coords_s tl, br;
	double distance;
	long duration;

	ret = route_segment_get_origin(segment, &origin);
	ROUTE_TEST_PRINT_RETURN("route_segment_get_origin", ret);
	printf("origin lat : %f long : %f\n", origin.latitude, origin.longitude);

	ret = route_segment_get_destination(segment, &destination);
	ROUTE_TEST_PRINT_RETURN("route_segment_get_destination", ret);
	printf("destination lat : %f long : %f\n", destination.latitude, destination.longitude);

	ret = route_segment_get_geometry_bounding_box(segment, &tl, &br);
	ROUTE_TEST_PRINT_RETURN("route_segment_get_geometry_bounding_box", ret);
	printf("bbox tl lat : %f long : %f\n", tl.latitude, tl.longitude);
	printf("bbox br lat : %f long : %f\n", br.latitude, br.longitude);

	ret = route_segment_get_distance(segment, &distance);
	ROUTE_TEST_PRINT_RETURN("route_segment_get_distance", ret);
	printf("distance : %f\n", distance);

	ret = route_segment_get_duration(segment, &duration);
	ROUTE_TEST_PRINT_RETURN("route_segment_get_duration", ret);
	printf("duration : %ld\n", duration);

	ret = route_segment_foreach_properties(segment, route_segment_property_callback, NULL);
	ROUTE_TEST_PRINT_RETURN("route_segment_foreach_properties", ret);

	ret = route_segment_foreach_steps(segment, route_segment_step_callback, NULL);
	ROUTE_TEST_PRINT_RETURN("route_segment_foreach_steps", ret);
}

static bool route_property_callback(const char *key, const char *value, void *user_data)
{
	printf("===== route_property_callback ======\n");

	if (key == NULL) {
		printf("key is NULL\n");
		return FALSE;
	}

	printf("key : %s value : %s\n", key, value);
	return TRUE;
}

static bool route_segment_callback(route_segment_h segment, void *user_data)
{
	printf("===== route_segment_callback ======\n");

	if (segment == NULL) {
		printf("segment is NULL\n");
		return FALSE;
	}

	int ret;
	route_segment_h cloned_segment;

	ret = route_segment_clone(&cloned_segment, segment);
	ROUTE_TEST_PRINT_RETURN("route_segment_clone", ret);

	route_segment_information(cloned_segment);

	ret = route_segment_destroy(cloned_segment);
	ROUTE_TEST_PRINT_RETURN("route_segment_destroy", ret);

	return TRUE;
}

void route_information(route_h route)
{
	int ret;
	int request_id;
	location_coords_s origin, destination;
	location_coords_s tl, br;
	route_distance_unit_e unit;
	double distance;
	long duration;

	ret = route_get_request_id(route, &request_id);
	ROUTE_TEST_PRINT_RETURN("route_get_request_id", ret);
	printf("request_id : %d\n", request_id);

	ret = route_get_origin(route, &origin);
	ROUTE_TEST_PRINT_RETURN("route_get_origin", ret);
	printf("origin lat : %f long : %f\n", origin.latitude, origin.longitude);

	ret = route_get_destination(route, &destination);
	ROUTE_TEST_PRINT_RETURN("route_get_destination", ret);
	printf("destination lat : %f long : %f\n", destination.latitude, destination.longitude);

	ret = route_get_geometry_bounding_box(route, &tl, &br);
	ROUTE_TEST_PRINT_RETURN("route_get_geometry_bounding_box", ret);
	printf("bbox.tl lat : %f long : %f\n", tl.latitude, tl.longitude);
	printf("bbox.br lat : %f long : %f\n", br.latitude, br.longitude);

	ret = route_get_distance_unit(route, &unit);
	ROUTE_TEST_PRINT_RETURN("route_get_distance_unit", ret);
	printf("distance unit : %d\n", unit);

	ret = route_get_total_distance(route, &distance);
	ROUTE_TEST_PRINT_RETURN("route_get_total_distance", ret);
	printf("distance : %f\n", distance);

	ret = route_get_total_duration(route, &duration);
	ROUTE_TEST_PRINT_RETURN("route_get_total_duration", ret);
	printf("duration : %ld\n", duration);

	ret = route_foreach_properties(route, route_property_callback, NULL);
	ROUTE_TEST_PRINT_RETURN("route_foreach_properties", ret);

	ret = route_foreach_segments(route, route_segment_callback, NULL);
	ROUTE_TEST_PRINT_RETURN("route_foreach_segments", ret);

}

static bool route_service_found_callback(route_error_e error, int index, int total, route_h route, void *user_data)
{
	printf("===== route_service_found_callback ======\n");
	if (error != ROUTE_ERROR_NONE) {
		printf("Failed : %d\n", error);
		return FALSE;
	}

	int ret;
	int req_id;
	route_h cloned_route;

	ret = route_clone(&cloned_route, route);
	ROUTE_TEST_PRINT_RETURN("route_clone", ret);

	printf("index[%d]/total[%d]\n", index, total);

	route_information(cloned_route);

	ret = route_destroy(cloned_route);
	ROUTE_TEST_PRINT_RETURN("route_destroy", ret);

	ret = route_get_request_id(route, &req_id);
	ROUTE_TEST_PRINT_RETURN("route_get_request_id", ret);

	ret = route_service_cancel(service, req_id);
	ROUTE_TEST_PRINT_RETURN("route_service_cancel", ret);

	return TRUE;
}

void route_service_test()
{
	int ret;
	location_coords_s origin, destination;
	int request_id;
	route_preference_h service_pref;

	ret = route_service_create(&service);
	ROUTE_TEST_PRINT_RETURN("route_service_create", ret);

	route_preference_create(&service_pref);
	ROUTE_TEST_PRINT_RETURN("route_preference_create", ret);

	route_set_preference(service_pref);

	origin.latitude = 37.564263;
	origin.longitude = 126.974676;
	destination.latitude = 37.55712;
	destination.longitude = 126.99241;

	//ret = route_service_get_preference(service, &service_pref);
	//ROUTE_TEST_PRINT_RETURN("route_service_get_preference", ret);

	ret = route_service_set_preference(service, service_pref);
	ROUTE_TEST_PRINT_RETURN("route_service_set_preference", ret);

	ret = route_service_find(service, origin, destination, NULL, 0, route_service_found_callback, NULL, &request_id);
	ROUTE_TEST_PRINT_RETURN("route_service_find", ret);

	route_preference_test(service_pref);

	if (service_pref) {
		route_preference_destroy(service_pref);
	}
}

static GMainLoop *g_mainloop = NULL;

static gboolean exit_program(gpointer data)
{
	if (service == NULL) {
		printf("service == NULL\n");
	} else {
		int ret = route_service_destroy(service);
		ROUTE_TEST_PRINT_RETURN("route_service_destroy", ret);
	}
	g_main_loop_quit(g_mainloop);
	return FALSE;
}

int main(int argc, char **argv)
{
	g_setenv("PKG_NAME", "com.samsung.location-test", 1);
	g_mainloop = g_main_loop_new(NULL, 0);
	route_service_test();
	g_timeout_add_seconds(1800, exit_program, NULL);
	g_main_loop_run(g_mainloop);
	return 0;
}

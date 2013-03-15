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

#ifndef __TIZEN_LOCATION_ROUTE_PREFERENCE_H__
#define __TIZEN_LOCATION_ROUTE_PREFERENCE_H__

#include <location_bounds.h>

#include "route_handle.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @addtogroup CAPI_LOCATION_ROUTE_PREF_MODULE
 * @{
 */

/**
 * @brief  Called repeatedly when you get the properties.
 * @remarks  @a key and @a value are valid only in this function.
 * @param[in]  key  The property key of route preference
 * @param[in]  value  The property value of route preference
 * @param[in]  user_data  The user data passed from foreach function
 * @return  @c true to continue with the next iteration of the loop, \n @c false to break out of the loop
 * @see	location_preference_foreach_available_properties()
 */
typedef bool(*route_preference_property_cb)(const char* key, const char* value, void* user_data);

/**
 * @brief  Called repeatedly when you get the addresses to avoid.
 * @remarks  @a address is valid only in this function.
 * @param[in]  address	 The address to avoid
 * @param[in]  user_data The user data passed from foreach function
 * @return  @c true to continue with the next iteration of the loop, \n @c false to break out of the loop
 * @see	route_preference_foreach_addresses_to_avoid()
 */
typedef bool(*route_preference_address_to_avoid_cb)(const char* address, void* user_data);

/**
 * @brief  Called repeatedly when you get the areas to avoid.
 * @remarks  @a area is valid only in this function.
 * @param[in]  area  The area to avoid
 * @param[in]  user_data  The user data passed from foreach function
 * @return  @c true to continue with the next iteration of the loop, \n @c false to break out of the loop
 * @see	route_preference_foreach_areas_to_avoid()
 */
typedef bool(*route_preference_area_to_avoid_cb)(location_bounds_h area, void* user_data);

/**
 * @brief  Called repeatedly when you get the constraints.
 * @remarks  @a constraint is valid only in this function.
 * @param[in]  constraint  The contraint
 * @param[in]  user_data  The user data passed from foreach function
 * @return  @c true to continue with the next iteration of the loop, \n @c false to break out of the loop
 * @see	route_preference_foreach_constraints()
 */
typedef bool(*route_preference_constraint_cb)(const char* constraint, void* user_data);

/**
 * @}
 */

/**
 * @addtogroup CAPI_LOCATION_ROUTE_PREF_CAPABILITY_MODULE
 * @{
 */

/**
 * @brief  Called repeatedly when you get the available property keys.
 * @remarks  @a key is valid only in this function.
 * @param[in]  key  The available property key of route preference
 * @param[in]  user_data  The user data passed from foreach function
 * @return  @c true to continue with the next iteration of the loop, \n @c false to break out of the loop
 * @see	route_preference_foreach_available_property_keys()
 */
typedef bool(*route_preference_available_property_key_cb)(const char* key, void* user_data);

/**
 * @brief  Called repeatedly when you get the available property values.
 * @remarks  @a value is valid only in this function.
 * @param[in]  value  The available property value of route preference
 * @param[in]  user_data  The user data passed from foreach function
 * @return  @c true to continue with the next iteration of the loop, \n @c false to break out of the loop
 * @see	route_preference_foreach_available_property_values()
 */
typedef bool(*route_preference_available_property_value_cb)(const char* value, void* user_data);

/**
  * @brief  Called repeatedly when you get the available constraints.
  * @remarks  @a constraint is valid only in this function.
  * @param[in]  constraint  The available constraint of route preference
  * @param[in]  user_data  The user data passed from foreach function
  * @return  @c true to continue with the next iteration of the loop, \n @c false to break out of the loop
  * @see route_preference_foreach_available_constraints()
  */
typedef bool(*route_preference_available_constraint_cb)(const char* constraint, void* user_data);

/**
  * @brief  Called repeatedly when you get the available route goals.
  * @remarks  @a goal is valid only in this function.
  * @param[in]  goal  The available route goal
  * @param[in]  user_data The user data passed from foreach function
  * @return  @c true to continue with the next iteration of the loop, \n @c false to break out of the loop
  * @see route_preference_foreach_available_goals()
  */
typedef bool(*route_preference_available_goal_cb)(const char* goal, void* user_data);

/**
  * @brief  Called repeatedly when you get the available transport modes.
  * @remarks  @a mode is valid only in this function.
  * @param[in]  mode  The available transport mode
  * @param[in]  user_data  The user data passed from foreach function
  * @return  @c true to continue with the next iteration of the loop, \n @c false to break out of the loop
  * @see route_preference_foreach_available_transport_modes()
  */
typedef bool(*route_preference_available_transport_mode_cb)(const char* mode, void* user_data);

/**
 * @}
 */

/**
 * @addtogroup CAPI_LOCATION_ROUTE_PREF_MODULE
 * @{
 */

/**
 * @brief  Creates a handle of route preference.
 * @remarks  The @a preference must be released route_preference_destroy() by you.
 * @param[out]  route  A handle of a new route preference handle on success
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_OUT_OF_MEMORY  Out of memory
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_destroy()
 */
int route_preference_create(route_preference_h* preference);

/**
 * @brief	 Destroys the handle of route preference and releases all its resources.
 * @param[in]  preference  The route preference handle to destroy
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_create()
 */
int route_preference_destroy(route_preference_h preference);

/**
 * @brief  Gets the list of addresses to avoid.
 * @param[in]  preference  The handle of route preference
 * @param[in]  callback  The callback function to invoke
 * @param[in]  user_data  The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_address_to_avoid_cb()
 * @see  route_preference_is_address_to_avoid_supported()
 * @see  route_preference_add_address_to_avoid()
 */
int route_preference_foreach_addresses_to_avoid(route_preference_h preference, route_preference_address_to_avoid_cb callback, void* user_data);

/**
 * @brief  Gets the list of areas to avoid.
 * @param[in]  preference  The handle of route preference
 * @param[in]  callback  The callback function to invoke
 * @param[in]  user_data  The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_area_to_avoid_cb()
 */
int route_preference_foreach_areas_to_avoid(route_preference_h preference, route_preference_area_to_avoid_cb callback, void* user_data);

/**
 * @brief  Gets the list of constraints.
 * @param[in]  preference  The handle of route preference
 * @param[in]  callback  The callback function to invoke
 * @param[in]  user_data  The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_constraint_cb()
 */
int route_preference_foreach_constraints(route_preference_h preference, route_preference_constraint_cb callback, void* user_data);

/**
 * @brief  Gets the list of a pair of key and value in route preference.
 * @param[in]  preference  The handle of route preference
 * @param[in]  callback  The callback function to invoke
 * @param[in]  user_data  The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see route_preference_property_cb()
 */
int route_preference_foreach_properties(route_preference_h preference, route_preference_property_cb callback, void* user_data);

/**
 * @brief	 Gets the bounding box of route geometry.
 * @param[in]  preference  The handle of route preference
 * @param[out]  top_left  The coords of top left
 * @param[out]  bottom_right  The coords of bottom right
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_set_geometry_bounding_box()
 * @see  route_preference_is_geometry_bounding_box_supported()
 */
int route_preference_get_geometry_bounding_box(route_preference_h preference, location_coords_s* top_left, location_coords_s* bottom_right);

/**
 * @brief	 Gets the max results to be returned.
 * @param[in]  preference  The handle of route preference
 * @param[out]  max_results  The max results to be returned
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_set_max_results()
 */
int route_preference_get_max_results(route_preference_h preference, int* max_results);

/**
 * @brief	 Gets the route goal.
 * @remarks @a goal must be released with @c free() by you.
 * @param[in]  preference  The handle of route preference
 * @param[out]  goal  The route goal
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_set_goal()
 * @see  route_preference_foreach_available_goals()
 */
int route_preference_get_goal(route_preference_h preference, char** goal);

/**
 * @brief	 Gets the transport mode.
 * @remarks @a mode must be released with @c free() by you.
 * @param[in]  preference  The handle of route preference
 * @param[out]  mode  The transport mode
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_set_transport_mode()
 * @see  route_preference_foreach_available_transport_modes()
 */
int route_preference_get_transport_mode(route_preference_h preference, char** mode);

/**
 * @brief  Gets the preference for providing the route geometry.
 * @param[in]  preference  The handle of route preference
 * @return  @a true if geomtry is used, otherwise @a false.
 * @see	route_preference_set_geometry_used()
 * @see  route_preference_is_geometry_supported()
 */
bool route_preference_is_geometry_used(route_preference_h preference);

/**
 * @brief	 Gets the preference for providing the instruction bounding box.
 * @param[in]  preference  The handle of route preference
 * @return  @a true if instruction bounding box is used, otherwise @a false.
 * @see	route_preference_set_instruction_bounding_box_used()
 * @see  route_preference_is_instruction_bounding_box_supported()
 */
bool route_preference_is_instruction_bounding_box_used(route_preference_h preference);

/**
 * @brief	 Gets the preference for providing the instruction geometry.
 * @param[in]  preference  The handle of route preference
 * @return  @a true if instruction geometry is used, otherwise @a false.
 * @see	route_preference_set_instruction_geometry_used()
 * @see  route_preference_is_instruction_geometry_supported()
 */
bool route_preference_is_instruction_geometry_used(route_preference_h preference);

/**
 * @brief	 Gets the preference for providing the instruction.
 * @param[in]  preference  The handle of route preference
 * @return  @a true if instruction is used, otherwise @a false.
 * @see	route_preference_set_instruction_used()
 * @see  route_preference_is_instruction_supported()
 */
bool route_preference_is_instruction_used(route_preference_h preference);

/**
 * @brief  Gets the preference for using traffic data.
 * @param[in]  preference  The handle of route preference
 * @return  @a true if traffic data is used, otherwise @a false.
 * @see	route_preference_set_traffic_data_used()
 * @see  route_preference_is_traffic_data_supported()
 */
bool route_preference_is_traffic_data_used(route_preference_h preference);

/**
 * @brief	 Gets the value of route preference.
 * @param[in]  preference  The handle of route preference
 * @param[in]  key  The property key
 * @param[out]  value  The property value
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_set()
 * @see  route_preference_foreach_available_property_keys()
 */
int route_preference_get(route_preference_h preference, const char* key, char** value);

/**
 * @brief	 Sets the value of route preference.
 * @param[in]  preference  The handle of route preference
 * @param[in]  key  The property key
 * @param[out]  value  The property value
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_get()
 * @see  route_preference_foreach_available_property_keys()
 * @see  route_preference_foreach_available_property_values()
 */
int route_preference_set(route_preference_h preference, const char* key, const char* value);

/**
 * @brief  Adds the address to avoid.
 * @param[in]  preference  The handle of route preference
 * @param[in]  address  The addresses to avoid
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see  route_preference_is_address_to_avoid_supported()
 * @see  route_preference_foreach_addresses_to_avoid()
 */
int route_preference_add_address_to_avoid(route_preference_h preference, const char* address);

/**
 * @brief  Clears the addresses to avoid.
 * @param[in]  preference  The handle of route preference
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see  route_preference_is_address_to_avoid_supported()
 * @see  route_preference_foreach_addresses_to_avoid()
 */
int route_preference_clear_addresses_to_avoid(route_preference_h preference);

/**
 * @brief	 Adds the area to avoid.
 * @param[in]  preference  The handle of route preference
 * @param[in]  area  The area to avoid
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_foreach_areas_to_avoid()
 * @see  route_preference_is_area_to_avoid_supported()
 */
int route_preference_add_area_to_avoid(route_preference_h preference, location_bounds_h area);

/**
 * @brief	 Clears the area to avoid.
 * @param[in]  preference  The handle of route preference
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_foreach_areas_to_avoid()
 * @see  route_preference_is_area_to_avoid_supported()
 */
int route_preference_clear_areas_to_avoid(route_preference_h preference);

/**
 * @brief  Adds the constraints.
 * @param[in]  preference  The handle of route preference
 * @param[in]  constraint_list  The constraint
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_get_constraints()
 * @see	route_preference_foreach_available_constraints()
 */
int route_preference_add_constraint(route_preference_h preference, const char* constraint);

/**
 * @brief  Clears the constraints.
 * @param[in]  preference  The handle of route preference
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_get_constraints()
 * @see	route_preference_foreach_available_constraints()
 */
int route_preference_clear_constraints(route_preference_h preference);

/**
 * @brief	 Sets the bounding box of route geometry.
 * @param[in]  preference  The handle of route preference
 * @param[in]  top_left  The coords of top left
 * @param[in]  bottom_right  The list of bottom right
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_get_geometry_bounding_box()
 * @see  route_preference_is_geometry_bounding_box_supported()
 */
int route_preference_set_geometry_bounding_box(route_preference_h preference, location_coords_s top_left, location_coords_s bottom_right);

/**
 * @brief	 Sets the max results to be returned.
 * @param[in]  preference  The handle of route preference
 * @param[in]  max_results  The max results to be returned
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_get_max_results()
 */
int route_preference_set_max_results(route_preference_h preference, int max_results);

/**
 * @brief	 Sets the route goal.
 * @param[in]  preference  The handle of route preference
 * @param[in]  goal  The route goal
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_get_goal()
 * @see  route_preference_foreach_available_goals()
 */
int route_preference_set_goal(route_preference_h preference, const char* goal);

/**
 * @brief	 Sets the transport mode.
 * @param[in]  preference  The handle of route preference
 * @param[in]  mode  The transport mode
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_get_transport_mode()
 * @see  route_preference_foreach_available_transport_modes()
 */
int route_preference_set_transport_mode(route_preference_h preference, const char* mode);

/**
 * @brief	 Sets the preference for providing the route geometry.
 * @param[in]  preference  The handle of route preference
 * @param[in]  used  @a true if used, otherwise @a false
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_is_geometry_used()
 * @see	route_preference_is_geometry_supported()
 */
int route_preference_set_geometry_used(route_preference_h preference, bool used);

/**
 * @brief	 Sets the preference for providing the instruction bounding box.
 * @param[in]  preference  The handle of route preference
 * @param[in]  used  @a true if used, otherwise @a false
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_is_instruction_bounding_box_used()
 * @see	route_preference_is_instruction_bounding_box_supported()
 */
int route_preference_set_instruction_bounding_box_used(route_preference_h preference, bool used);

/**
 * @brief	 Sets the preference for providing the instruction geometry.
 * @param[in]  preference  The handle of route preference
 * @param[in]  used  @a true if used, otherwise @a false
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_is_instruction_geometry_used()
 * @see	route_preference_is_instruction_geometry_supported()
 */
int route_preference_set_instruction_geometry_used(route_preference_h preference, bool used);

/**
 * @brief	 Sets the preference for providing the instruction.
 * @param[in]  preference  The handle of route preference
 * @param[in]  used  @a true if used, otherwise @a false
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_is_instruction_used()
 * @see	route_preference_is_instruction_supported()
 */
int route_preference_set_instruction_used(route_preference_h preference, bool used);

/**
 * @brief	 Sets the preference for using the traffic data.
 * @param[in]  preference  The handle of route preference
 * @param[in]  used  @a true if used, otherwise @a false
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_is_traffic_data_used()
 * @see	route_preference_is_traffic_data_supported()
 */
int route_preference_set_traffic_data_used(route_preference_h preference, bool used);

/**
 * @}
 */

/**
 * @addtogroup CAPI_LOCATION_ROUTE_PREF_CAPABILITY_MODULE
 * @{
 */

/**
 * @brief	 Checks whether the given bound type is supported as area to avoid.
 * @param[in]  service  The handle of route service
 * @param[in]  type  The type of location bound
 * @return  @a true if area to avoid is supported, otherwise @a false.
 * @see	route_preference_add_area_to_avoid()
 * @see	route_preference_foreach_areas_to_avoid()
 */
bool route_preference_is_area_to_avoid_supported(route_service_h service, location_bounds_type_e type);

/**
 * @brief	 Checks whether the address to avoid is supported.
 * @param[in]  service  The handle of route service
 * @return  @a true if address to avoid is supported, otherwise @a false.
 * @see  route_preference_foreach_addresses_to_avoid()
 * @see  route_preference_add_address_to_avoid()
 */
bool route_preference_is_address_to_avoid_supported(route_service_h service);

/**
 * @brief	 Checks whether the bounding box of route geometry is supported.
 * @param[in]  service  The handle of route service
 * @return  @a true if geometry bounding box is supported, otherwise @a false.
 * @see	route_preference_set_geometry_bounding_box()
 * @see	route_preference_get_geometry_bounding_box()
 */
bool route_preference_is_geometry_bounding_box_supported(route_service_h service);

/**
 * @brief	 Checks whether the route geometry is supported.
 * @param[in]  service  The handle of route service
 * @return  @a true if geometry is supported, otherwise @a false.
 * @see	route_preference_set_geometry_used()
 * @see	route_preference_is_geometry_used()
 */
bool route_preference_is_geometry_supported(route_service_h service);

/**
 * @brief	 Checks whether the instruction geometry is supported.
 * @param[in]  service  The handle of route service
 * @return  @a true if instruction geometry is supported, otherwise @a false.
 * @see	route_preference_is_instruction_geometry_used()
 * @see	route_preference_set_instruction_geometry_used()
 */
bool route_preference_is_instruction_geometry_supported(route_service_h service);

/**
 * @brief	 Checks whether the instruction bounding box is supported.
 * @param[in]  service  The handle of route service
 * @return  @a true if instruction bounding box is supported, otherwise @a false.
 * @see	route_preference_set_instruction_bounding_box_used()
 * @see	route_preference_is_instruction_bounding_box_used()
 */
bool route_preference_is_instruction_bounding_box_supported(route_service_h service);

/**
 * @brief	 Checks whether the instruction is supported.
 * @param[in]  service  The handle of route service
 * @return  @a true if instruction is supported, otherwise @a false.
 * @see	route_preference_set_instruction_used()
 * @see	route_preference_is_instruction_used()
 */
bool route_preference_is_instruction_supported(route_service_h service);

/**
 * @brief	 Checks whether the traffic data is supported.
 * @param[in]  service  The handle of route service
 * @return  @a true if traffic data is supported, otherwise @a false.
 * @see	route_preference_set_traffic_data_used()
 * @see	route_preference_is_traffic_data_used()
 */
bool route_preference_is_traffic_data_supported(route_service_h service);

/**
 * @brief  Gets the list of available constraints.
 * @param[in]  service  The handle of route service
 * @param[in]  callback  The callback function to invoke
 * @param[in]  user_data  The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_add_constraint()
 * @see	route_preference_foreach_constraints()
 */
int route_preference_foreach_available_constraints(route_service_h service, route_preference_available_constraint_cb callback, void* user_data);

/**
 * @brief  Gets the list of available route goals.
 * @param[in]  service  The handle of route service
 * @param[in]  callback  The callback function to invoke
 * @param[in]  user_data  The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_get_goal()
 * @see	route_preference_set_goal()
 */
int route_preference_foreach_available_goals(route_service_h service, route_preference_available_goal_cb callback, void* user_data);

/**
 * @brief  Gets the list of available transport mode.
 * @param[in]  service  The handle of route service
 * @param[in]  callback  The callback function to invoke
 * @param[in]  user_data  The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_set_transport_mode()
 * @see	route_preference_get_transport_mode()
 */
int route_preference_foreach_available_transport_modes(route_service_h service, route_preference_available_transport_mode_cb callback, void* user_data);

/**
 * @brief	 Gets the list of available keys in route preference.
 * @param[in]  service  The handle of route service
 * @param[in]  callback  The callback function to invoke
 * @param[in]  user_data  The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_set()
 * @see	route_preference_get()
 * @see	route_preference_foreach_available_property_values()
 */
int route_preference_foreach_available_property_keys(route_service_h service, route_preference_available_property_key_cb callback, void* user_data);

/**
 * @brief	 Gets the list of available values in route preference.
 * @param[in]  service  The handle of route service
 * @param[in]  callback  The callback function to invoke
 * @param[in]  user_data  The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_preference_foreach_properties()
 * @see	route_preference_foreach_available_property_keys()
 * @see	route_preference_set()
 */
int route_preference_foreach_available_property_values(route_service_h service, const char* key, route_preference_available_property_value_cb callback, void* user_data);

/**
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_LOCATION_ROUTE_PREFERENCE_H__ */

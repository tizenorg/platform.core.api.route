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

#ifndef __TIZEN_LOCATION_ROUTE_H__
#define __TIZEN_LOCATION_ROUTE_H__

#include <location_bounds.h>

#include "route_handle.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * @addtogroup CAPI_LOCATION_ROUTE_MODULE
 * @{
 */

/**
 * @brief  Called repeatedly when you get the list of a pair of key and value in properties.
 * @remarks  @a key and @a value are valid only in this function.
 * @param[in]  key  The property key of route
 * @param[in]  value  The property value of route
 * @param[in]  user_data  The user data passed from foreach function
 * @return  @c true to continue with the next iteration of the loop, \n @c false to break out of the loop
 * @see	route_foreach_properties()
 */
typedef bool(*route_property_cb)(const char *key, const char *value, void *user_data);

/**
 * @brief  Called repeatedly when you get the list of segments.
 * @remarks  @a segment is valid only in this function.
 * @param[in]  segment  The segment of route
 * @param[in]  user_data  The user data passed from foreach function
 * @return  @c true to continue with the next iteration of the loop, \n @c false to break out of the loop
 * @see	route_foreach_segments()
 */
typedef bool(*route_segment_cb)(route_segment_h segment, void *user_data);

/**
 * @brief Enumerations of distance unit
 */
typedef enum
{
    ROUTE_DISTANCE_UNIT_M = 0,  /**< Meter */
    ROUTE_DISTANCE_UNIT_KM = 1,  /**< Kilometer */
    ROUTE_DISTANCE_UNIT_FT = 2,  /**< Feet */
    ROUTE_DISTANCE_UNIT_YD = 3,  /**< Yard */
    ROUTE_DISTANCE_UNIT_MI = 4,  /**< Mile */
} route_distance_unit_e;

/**
 * @}
 */

/**
 * @addtogroup CAPI_LOCATION_ROUTE_SEGMENT_MODULE
 * @{
 */

/**
 * @brief  Called repeatedly when you get the list of a pair of key and value in properties.
 * @remarks  @a key and @a value are valid only in this function.
 * @param[in]  key  The property key of route segment
 * @param[in]  value  The property value of route segment
 * @param[in]  user_data  The user data passed from foreach function
 * @return  @c true to continue with the next iteration of the loop, \n @c false to break out of the loop
 * @see	route_segment_foreach_properties()
 */
typedef bool(*route_segment_property_cb)(const char *key, const char *value, void *user_data);

/**
 * @brief  Called repeatedly when you get the list of steps.
 * @remarks  @a step is valid only in this function.
 * @param[in]  step  The step of route segment
 * @param[in]  user_data  The user data passed from foreach function
 * @return  @c true to continue with the next iteration of the loop, \n @c false to break out of the loop
 * @see	route_segment_foreach_steps()
 */
typedef bool(*route_segment_step_cb)(route_step_h step, void *user_data);

/**
 * @}
 */

/**
 * @addtogroup CAPI_LOCATION_ROUTE_STEP_MODULE
 * @{
 */

/**
 * @brief  Called repeatedly when you get the list of geometries in route step.
 * @remarks  @a geometry is valid only in this function.
 * @param[in]  geometry  The geometry of route step
 * @param[in]  user_data  The user data passed from foreach function
 * @return  @c true to continue with the next iteration of the loop, \n @c false to break out of the loop
 * @see	route_step_foreach_geometries()
 */
typedef bool(*route_step_geometry_cb)(location_coords_s* geometry, void *user_data);

/**
 * @brief  Called repeatedly when you get the list of a pair of key and value in properties.
 * @remarks  @a key and @a value are valid only in this function.
 * @param[in]  key  The property key of route step
 * @param[in]  value  The property value of route step
 * @param[in]  user_data  The user data passed from foreach function
 * @return  @c true to continue with the next iteration of the loop, \n @c false to break out of the loop
 * @see	route_step_foreach_properties()
 */
typedef bool(*route_step_property_cb)(const char *key, const char *value, void *user_data);

/**
 * @}
 */

/**
 * @addtogroup CAPI_LOCATION_ROUTE_MODULE
 * @{
 */

/**
 * @brief  Clones the handle of route.
 * @remarks  The @a cloned_route must be released route_destroy() by you.
 * @param[out]  cloned_route  A cloned route handle
 * @param[in]  origin  The original route handle
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval  #ROUTE_ERROR_OUT_OF_MEMORY  Out of memory
 * @see	route_destroy()
 */
int route_clone(route_h* cloned_route, route_h origin);

/**
 * @brief  Destroys the handle of route.
 * @param[in]  route  The route handle
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_clone()
 */
int route_destroy(route_h route);

/**
 * @brief  Gets the request ID.
 * @param[in]  route  The route handle
 * @param[out]  request_id  The request ID of route handle
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_service_find()
 */
int route_get_request_id(route_h route, int* id);

/**
 * @brief  Gets the origin of route.
 * @param[in]  route  The route handle
 * @param[out]  origin  The origin of route
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_get_destination()
 */
int route_get_origin(route_h route, location_coords_s* origin);

/**
 * @brief  Gets the destination.
 * @param[in]  route  The route handle
 * @param[out]  destination  The destination of route
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_get_origin()
 */
int route_get_destination(route_h route, location_coords_s* destination);

/**
 * @brief  Gets the bounding box of route geometry.
 * @param[in]  route  The route handle
 * @param[out]  top_left  The top left coords of bounding box
 * @param[out]  bottom_right  The bottom right coords of bounding box
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 */
int route_get_geometry_bounding_box(route_h route, location_coords_s* top_left, location_coords_s* bottom_right);

/**
 * @brief  Gets the distance unit of route.
 * @param[in]  route  The route handle
 * @param[out]  unit  The distance unit used in route
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_get_total_duration()
 */
int route_get_distance_unit(route_h route, route_distance_unit_e* unit);

/**
 * @brief  Gets the distance of route.
 * @param[in]  route  The route handle
 * @param[out]  distance  The distance of route. You can get the distance unit by route_get_distance_unit().
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_get_total_duration()
 */
int route_get_total_distance(route_h route, double* distance);

/**
 * @brief  Gets the duration unit of route.
 * @param[in]  route  The route handle
 * @param[out]  duration  The duration
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_get_total_distance()
 */
int route_get_total_duration(route_h route, long* duration);

/**
 * @brief  Gets the list of a pair of key and value in properties.
 * @param[in]  route  The route handle
 * @param[in]  callback  The callback function to invoke
 * @param[in]  user_data  The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see  route_property_cb()
 */
int route_foreach_properties(route_h route, route_property_cb callback, void* user_data);

/**
 * @brief Gets the list of segments.
 * @param[in]  route  The route handle
 * @param[in]  callback  The callback function to invoke
 * @param[in]  user_data  The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see  route_segment_cb()
 */
int route_foreach_segments(route_h route, route_segment_cb callback, void* user_data);

/**
 * @}
 */

/**
 * @addtogroup CAPI_LOCATION_ROUTE_SEGMENT_MODULE
 * @{
 */

/**
 * @brief  Clones the handle of route segment.
 * @remarks  The @a cloned_segment must be released route_segment_destroy() by you.
 * @param[out]  cloned_segment  A cloned handle of route segment
 * @param[in]  origin  The original handle of route segment
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval  #ROUTE_ERROR_OUT_OF_MEMORY  Out of memory
 * @see	route_segment_destroy()
 */
int route_segment_clone(route_segment_h* cloned_segment, route_segment_h origin);

/**
 * @brief  Destroys the handle of route segment.
 * @param[in]  segment  The handle of route segment
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_segment_clone()
 */
int route_segment_destroy(route_segment_h segment);

/**
 * @brief  Gets the origin.
 * @param[in]  segment  The handle of route segment
 * @param[out]  origin  The origin of route segment
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_segment_get_destination()
 */
int route_segment_get_origin(route_segment_h segment, location_coords_s* origin);

/**
 * @brief  Gets the destination.
 * @param[in]  segment  The handle of route segment
 * @param[out]  destination  The destination of route segment
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_segment_get_origin()
 */
int route_segment_get_destination(route_segment_h segment, location_coords_s* destination);

/**
 * @brief  Gets the bounding box of route segment geometry.
 * @param[in]  segment  The handle of route segment
 * @param[out]  top_left  The top left coords of bounding box
 * @param[out]  bottom_right  The bottom right coords of bounding box
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 */
int route_segment_get_geometry_bounding_box(route_segment_h segment, location_coords_s* top_left, location_coords_s* bottom_right);

/**
 * @brief  Gets the distance of route segment.
 * @param[in]  segment  The handle of route segment
 * @param[out]  distance  The distance of route. You can get the distance unit by route_get_distance_unit().
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_segment_get_duration()
 */
int route_segment_get_distance(route_segment_h segment, double* distance);

/**
 * @brief  Gets the duration unit of route.
 * @param[in]  segment  The handle of route segment
 * @param[out]  duration  The duration
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_segment_get_distance()
 */
int route_segment_get_duration(route_segment_h segment, long* duration);

/**
 * @brief  Gets the list of a pair of key and value in properties.
 * @param[in]  segment  The handle of route segment
 * @param[in]  callback  The callback function to invoke
 * @param[in]  user_data  The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see  route_segment_property_cb()
 */
int route_segment_foreach_properties(route_segment_h segment, route_segment_property_cb callback, void* user_data);

/**
 * @brief Gets the list of segments.
 * @param[in]  segment  The handle of route segment
 * @param[in]  callback  The callback function to invoke
 * @param[in]  user_data  The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see  route_segment_step_cb()
 */
int route_segment_foreach_steps(route_segment_h segment, route_segment_step_cb callback, void* user_data);

/**
 * @}
 */

/**
 * @addtogroup CAPI_LOCATION_ROUTE_STEP_MODULE
 * @{
 */

/**
 * @brief  Clones the handle of route step.
 * @remarks  The @a cloned_step must be released route_step_destroy() by you.
 * @param[out]  cloned_step  A cloned handle of route step
 * @param[in]  origin  The original handle route step
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval  #ROUTE_ERROR_OUT_OF_MEMORY  Out of memory
 * @see	route_step_destroy()
 */
int route_step_clone(route_step_h* cloned_step, route_step_h origin);

/**
 * @brief  Destroys the handle of route step.
 * @param[in]  step  The handle of route step
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_step_clone()
 */
int route_step_destroy(route_step_h step);

/**
 * @brief  Gets the origin.
 * @param[in]  step  The handle of route step
 * @param[out]  origin  The origin of route step
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_step_get_destination()
 */
int route_step_get_origin(route_step_h step, location_coords_s* origin);

/**
 * @brief  Gets the destination.
 * @param[in]  step  The handle of route step
 * @param[out]  destination  The destination of route step
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_segment_get_origin()
 */
int route_step_get_destination(route_step_h step, location_coords_s* destination);

/**
 * @brief  Gets the bounding box of route step geometry.
 * @param[in]  step  The handle of route step
 * @param[out]  top_left  The top left coords of bounding box
 * @param[out]  bottom_right  The bottom right coords of bounding box
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 */
int route_step_get_geometry_bounding_box(route_step_h step, location_coords_s* top_left, location_coords_s* bottom_right);

/**
 * @brief  Gets the distance of route step.
 * @param[in]  step  The handle of route step
 * @param[out]  distance  The distance of route. You can get the distance unit by route_get_distance_unit().
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_step_get_duration()
 */
int route_step_get_distance(route_step_h step, double* distance);

/**
 * @brief  Gets the duration unit of route.
 * @param[in]  step  The handle of route step
 * @param[out]  duration  The duration
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_step_get_distance()
 */
int route_step_get_duration(route_step_h step, long* duration);

/**
 * @brief	 Gets the transport mode.
 * @remarks @a mode must be released with @c free() by you.
 * @param[in]  step  The handle of route step
 * @param[out]  mode  The transport mode
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see  route_preference_foreach_available_transport_modes()
 */
int route_step_get_transport_mode(route_step_h step, char** mode);

/**
 * @brief  Gets the instruction of route step.
 * @remarks @a instruction must be released with @c free() by you.
 * @param[in]  step  The handle of route step
 * @param[out]  instruction  The instruction of step
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 */
int route_step_get_instruction(route_step_h step, char** instruction);

/**
 * @brief  Gets the list of geometries in route step.
 * @param[in]  step  The handle of route step
 * @param[in]  callback  The callback function to invoke
 * @param[in]  user_data  The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see  route_step_geometry_cb()
 */
int route_step_foreach_geometries(route_step_h step, route_step_geometry_cb callback, void* user_data);

/**
 * @brief  Gets the list of a pair of key and value in properties.
 * @param[in]  step  The handle of route step
 * @param[in]  callback  The callback function to invoke
 * @param[in]  user_data  The user data to be passed to the callback function
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see  route_step_property_cb()
 */
int route_step_foreach_properties(route_step_h step, route_step_property_cb callback, void* user_data);

/**
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_LOCATION_ROUTE_H__ */

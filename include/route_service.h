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

#ifndef __TIZEN_LOCATION_ROUTE_SERVICE_H__
#define __TIZEN_LOCATION_ROUTE_SERVICE_H__

#include <location_bounds.h>

#include "route_handle.h"

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup CAPI_LOCATION_ROUTE_SERVICE_MODULE
 * @{
 */

/**
 * @brief	 Called when the requested routes are found by route_service_find().
 * @remarks  @a route is valid only in this function. In order to use the route outside this function, you must copy the route with route_clone(). \n
 * If route_service_find() failed, this callback function is called only once with 0 total and NULL route.
 * @param[in]  route_error_e  The reuslt of request
 * @param[in]  request_id  The identification of request
 * @param[in]  total  The total number of result
 * @param[in]  route  The route data
 * @param[in]  user_data  The user data passed from the request function
 * @return  @c true to continue with the next iteration of the loop, \n @c false to break out of the loop
 * @pre  route_service_find() will invoke this callback.
 * @see  route_service_find()
 */
typedef bool(*route_service_found_cb)(route_error_e error, int index, int total, route_h route, void* user_data);

/**
 * @brief  Creates a new handle of route service.
 * @remarks  The @a service must be released route_service_destroy() by you.
 * @param[out]  service  A handle of a new route service on success
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_OUT_OF_MEMORY  Out of memory
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval  #ROUTE_ERROR_SERVICE_NOT_AVAILABLE  Service not available
 * @see	route_service_destroy()
 */
int route_service_create(route_service_h* service);

/**
 * @brief	 Destroys the handle of route service and releases all its resources.
 * @param[in]  service  The route service handle to destroy
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_service_create()
 */
int route_service_destroy(route_service_h service);

/**
 * @brief	 Gets the route preference.
 * @param[in]  service  The handle of route service
 * @param[out]  preference  The handle of route preference
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_service_set_preference()
 */
int route_service_get_preference(route_service_h service, route_preference_h* preference);

/**
 * @brief	 Sets the route preference.
 * @param[in]  service  The handle of route service
 * @param[in]  preference  The handle of route preference
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_service_get_preference()
 */
int route_service_set_preference(route_service_h service, route_preference_h preference);

/**
 * @brief	 Requests to find the route, asynchronously.
 * @param[in]  service  The handle of route service
 * @param[in]  origin  The starting point
 * @param[in]  destination  The destination
 * @param[in]  waypoint_list  The list of waypoints to go through
 * @param[in]  waypoint_num  The number of waypoints to go through
 * @param[in]  callback  The result callback
 * @param[in]  user_data  The user data to be passed to the callback function
 * @param[out]  request_id  The request ID
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_OUT_OF_MEMORY  Out of memory
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @retval  #ROUTE_ERROR_SERVICE_UNAVILABLE  Service unavailabe
 * @see	route_service_cancel()
 * @see  route_service_found_cb()
 */
int route_service_find(route_service_h service, location_coords_s origin, location_coords_s destination, location_coords_s* waypoint_list, int waypoint_num, route_service_found_cb callback, void* user_data, int* request_id);

/**
 * @brief	 Cancels the request.
 * @param[in]  service  The handle of route service
 * @param[out]  request_id  The request ID which is got from route_service_find()
 * @return  0 on success, otherwise a negative error value.
 * @retval  #ROUTE_ERROR_NONE  Successful
 * @retval  #ROUTE_ERROR_INVALID_PARAMETER  Invalid parameter
 * @see	route_service_find()
 */
int route_service_cancel(route_service_h service, int request_id);

/**
 * @}
 */


#ifdef __cplusplus
}
#endif

#endif /* __TIZEN_LOCATION_ROUTE_SERVICE_H__ */

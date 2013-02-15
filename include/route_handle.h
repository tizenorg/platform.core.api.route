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

#ifndef __TIZEN_LOCATION_ROUTE_HANDLE_H__
#define	__TIZEN_LOCATION_ROUTE_HANDLE_H__

#include <tizen_type.h>
#include <tizen_error.h>

#ifdef __cplusplus
extern "C" {
#endif

/**
 * @addtogroup CAPI_LOCATION_ROUTE_SERVICE_MODULE
 * @{
 */

typedef enum
{
	ROUTE_ERROR_NONE = TIZEN_ERROR_NONE,  /**< Successful */
	ROUTE_ERROR_OUT_OF_MEMORY = TIZEN_ERROR_OUT_OF_MEMORY,  /**< Out of memory */
	ROUTE_ERROR_INVALID_PARAMETER = TIZEN_ERROR_INVALID_PARAMETER,  /**< Invalid parameter */
	ROUTE_ERROR_NETWORK_FAILED = TIZEN_ERROR_LOCATION_CLASS | 0x0111,  /**< Network unavailable*/
	ROUTE_ERROR_SERVICE_NOT_AVAILABLE = TIZEN_ERROR_LOCATION_CLASS | 0x0112,  /**< Service unavailable */
	ROUTE_ERROR_SERVICE_NOT_SUPPORTED = TIZEN_ERROR_LOCATION_CLASS | 0x0113,  /**< Not supproted */
	ROUTE_ERROR_RESULT_NOT_FOUND = TIZEN_ERROR_LOCATION_CLASS | 0x0114,  /**< Result not found */
} route_error_e;

/**
 * @brief The handle of route service
 */
typedef void* route_service_h;

/**
 * @brief  The handle of route preference
 */
typedef void* route_preference_h;

/**
 * @brief The handle of route
 */
typedef void* route_h;

/**
 * @}
 */

/**
 * @addtogroup CAPI_LOCATION_ROUTE_MODULE
 * @{
 */

/**
 * @brief The handle of route segment
 */
typedef void* route_segment_h;

/**
 * @}
 */

/**
 * @addtogroup CAPI_LOCATION_ROUTE_SEGMENT_MODULE
 * @{
 */

/**
 * @brief The handle of route step
 */
typedef void* route_step_h;

/**
 * @}
 */

#ifdef __cplusplus
}
#endif

#endif //__TIZEN_LOCATION_ROUTE_HANDLE_H__


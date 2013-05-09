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

#ifndef __TIZEN_LOCATION_ROUTE_PRIVATE_H__
#define	__TIZEN_LOCATION_ROUTE_PRIVATE_H__

#include <location.h>
#include <location-map-service.h>

#include "route_preference.h"
#include <dlog.h>

#ifdef LOG_TAG
#undef LOG_TAG
#endif
#define LOG_TAG "CAPI_LOCATION_ROUTE"

/*
 * Internal macros
 */

#define ROUTE_LOGD(fmt,args...)  LOGD(fmt, ##args)
#define ROUTE_LOGW(fmt,args...)  LOGW(fmt, ##args)
#define ROUTE_LOGI(fmt,args...)  LOGI(fmt, ##args)
#define ROUTE_LOGE(fmt,args...)  LOGE(fmt, ##args)

#define ROUTE_CHECK_CONDITION(condition, error, msg)	\
	do { \
		if( !(condition) ){	\
			ROUTE_LOGE("%s(0x%08x)", msg, error); \
			return error;	\
		} \
	} while (0)

#define ROUTE_PRINT_ERROR_CODE_RETURN(code) \
	do{ \
		ROUTE_LOGE("%s(0x%08x)", #code, code); \
		return code;	\
	} while (0)

#define ROUTE_NULL_ARG_CHECK_RETURN_FALSE(arg)\
	do { \
		if(arg != NULL) { \
		} else	{ \
			ROUTE_LOGE("ROUTE_ERROR_INVALID_PARAMETER");  \
			return false; };	\
	} while (0)

#define ROUTE_NULL_ARG_CHECK(arg)\
	ROUTE_CHECK_CONDITION( (arg != NULL), ROUTE_ERROR_INVALID_PARAMETER, "ROUTE_ERROR_INVALID_PARAMETER")


#ifdef __cplusplus
extern "C" {
#endif


typedef struct _route_service_s{
    LocationMapObject* object;
    route_preference_h route_preference;
} route_service_s;

typedef struct _route_preference_s{
    LocationRoutePreference* preference;
} route_preference_s;

typedef struct _route_s{
    LocationRoute* route;
    int request_id;
} route_s;

typedef struct _route_segment_s{
    LocationRouteSegment* segment;
} route_segment_s;

typedef struct _route_step_s{
    LocationRouteStep* step;
} route_step_s;

#ifdef __cplusplus
}
#endif

#endif //__TIZEN_LOCATION_ROUTE_PRIVATE_H__


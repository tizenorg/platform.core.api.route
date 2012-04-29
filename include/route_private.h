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

#ifndef __TIZEN_LOCATION_ROUTE_PRIVATE_H__
#define	__TIZEN_LOCATION_ROUTE_PRIVATE_H__

#include <location.h>

#include "route_preference.h"

#ifdef __cplusplus
extern "C" {
#endif


typedef struct _route_service_s{
    LocationObject* object;
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


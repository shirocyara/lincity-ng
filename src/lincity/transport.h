/* ---------------------------------------------------------------------- *
 * transport.h
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * ---------------------------------------------------------------------- */

#ifndef TRANSPORT_H
#define TRANSPORT_H

#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || _MSC_VER > 1000
#pragma once
#endif

#include "engglobs.h"

#define XY_IS_TRANSPORT(x,y) \
((MP_GROUP(x,y) == GROUP_TRACK) || \
 (MP_GROUP(x,y) == GROUP_ROAD) || \
 (MP_GROUP(x,y) == GROUP_RAIL) || \
 (MP_GROUP(x,y) == GROUP_TRACK_BRIDGE) || \
 (MP_GROUP(x,y) == GROUP_ROAD_BRIDGE) || \
 (MP_GROUP(x,y) == GROUP_RAIL_BRIDGE))
#endif

void general_transport(int x, int y, int max_waste);
void connect_transport(int originx, int originy, int w, int h);

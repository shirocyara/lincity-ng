/* ---------------------------------------------------------------------- *
 * modules.h
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * (c) Corey Keasling, 2004
 * ---------------------------------------------------------------------- */
#ifndef modules_h
#define modules_h

#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || _MSC_VER > 1000
#pragma once
#endif

#include "../lctypes.h"
#include "tinygettext/gettext.hpp"
#include "../engglobs.h"
#include "../engine.h"
#include "../stats.h"
#include "gui_interface/mps.h"
#include "../lclib.h"

#include "market.h"
#include "../power.h"

// for real_time
//#include "cliglobs.h"

#endif /* __modules_h__ */

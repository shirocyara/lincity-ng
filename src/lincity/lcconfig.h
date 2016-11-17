/* ---------------------------------------------------------------------- *
 * lcconfig.h
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * ---------------------------------------------------------------------- */
#ifndef lcconfig_h
#define lcconfig_h

#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || _MSC_VER > 1000
#pragma once
#endif

#if defined (WIN32)
#include "confw32.h"
#else
#include <config.h>
#endif

#ifndef _MSC_VER
//#warning deprecated header
#else
#pragma message(__FILE__ ": deprecated header")
#endif

#endif /* __lcconfig_h__ */

/* ---------------------------------------------------------------------- *
 * lcstring.h
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * ---------------------------------------------------------------------- */
#ifndef lcstring_h
#define lcstring_h

#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || _MSC_VER > 1000
#pragma once
#endif

#include <string.h>
#ifndef _WIN32
#include <unistd.h>
#endif

#ifndef _MSC_VER
//#warning deprecated header
#else
#pragma message(__FILE__ ": deprecated header")
#endif

#endif /* __lcstring_h__ */

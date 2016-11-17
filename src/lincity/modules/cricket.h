/* ---------------------------------------------------------------------- *
 * cricket.h
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * (c) Corey Keasling, 2004
 * ---------------------------------------------------------------------- */

#ifndef cricket_h
#define cricket_h

#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || _MSC_VER > 1000
#pragma once
#endif

void do_cricket(int x, int y);
void do_cricket_cover(int x, int y);
void mps_cricket(int x, int y);

#endif /* __cricket_h__ */

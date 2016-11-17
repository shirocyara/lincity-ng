/* ---------------------------------------------------------------------- *
 * shanty.h
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * (c) Corey Keasling, 2004
 * ---------------------------------------------------------------------- */

#ifndef shanty_h
#define shanty_h

#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || _MSC_VER > 1000
#pragma once
#endif

void add_a_shanty(void);
void remove_a_shanty(int x, int y);
void update_shanty(void);
void do_shanty(int x, int y);

#endif /* __shanty_h__ */

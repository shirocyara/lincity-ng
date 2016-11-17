/* ---------------------------------------------------------------------- *
 * substation.h
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * (c) Corey Keasling, 2004
 * ---------------------------------------------------------------------- */

#ifndef substation_h
#define substation_h

#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || _MSC_VER > 1000
#pragma once
#endif

void do_power_substation(int x, int y);
int add_a_substation(int x, int y);
void remove_a_substation(int x, int y);
void shuffle_substations(void);

void mps_substation(int x, int y);

#endif /* __substation_h__ */

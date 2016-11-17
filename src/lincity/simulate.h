/* ---------------------------------------------------------------------- *
 * simulate.h
 * This file is part of lincity.
 * Lincity is copyright (c) I J Peters 1995-1997, (c) Greg Sharp 1997-2001.
 * ---------------------------------------------------------------------- */
#ifndef simulate_h
#define simulate_h

#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || _MSC_VER > 1000
#pragma once
#endif

void do_time_step(void);
int count_groups(int gr);
void count_all_groups(int *group_count);
void set_mappoint(int x, int y, short selected_type);
void do_rand_ecology(int x, int y);

extern void connect_rivers(void);

#endif /* __simulate_h__ */

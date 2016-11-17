/* ----------------------------------------------------------------------
 * init_game.h
 * This file is part of lincity-ng
 * see COPYING for license, and CREDITS for authors
 * ----------------------------------------------------------------------
 */
#ifndef init_game_h
#define init_game_h

#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || _MSC_VER > 1000
#pragma once
#endif

void clear_game(void);
void setup_land(void);
void new_city(int *originx, int *originy, int random_village);

#endif /* __init_game_h__ */

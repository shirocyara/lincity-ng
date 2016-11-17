/* ---------------------------------------------------------------------- *
 * loadsave.h
 * This file is part of lincity-NG
 * ---------------------------------------------------------------------- */

/* This is the loading/saving facility */

#ifndef loadsave_h
#define loadsave_h

#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || _MSC_VER > 1000
#pragma once
#endif

#define LC_SAVE_DIR "lincity-ng"
#define LINCITYRC_FILENAME "lincity-NGrc"

#define RESULTS_FILENAME "results.txt"


/* New load/save format */
#define WATERWELL_V2 1322


//void load_saved_city(char *s);
void save_city(char *);
void save_city_2(char *);
void load_city_2(char *);

extern void load_city_old(char *);

#endif /* __loadsave_h__ */

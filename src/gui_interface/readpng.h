/* ---------------------------------------------------------------------- *
 * readpng.c
 * This file is part of lincity (see COPYRIGHT for copyright information).
 * ---------------------------------------------------------------------- */
#ifndef readpng_h
#define readpng_h

#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || _MSC_VER > 1000
#pragma once
#endif

int load_png_graphics (char *txt_filename, char *png_filename);

#endif /* __readpng_h__ */

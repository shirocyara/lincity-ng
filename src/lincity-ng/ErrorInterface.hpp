#ifndef ErrorInterface_h
#define ErrorInterface_h

#if __GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4) || _MSC_VER > 1000
#pragma once
#endif

void do_error (const char *s);
void HandleError (const char *s, int i);
#endif

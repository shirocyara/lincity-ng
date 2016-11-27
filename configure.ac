#                                               -*- Autoconf -*-
# Process this file with autoconf to produce a configure script.

AC_PREREQ([2.69])
AC_INIT([lincity-ngW], [2.0.1], [shirocyara@yahoo.co.jp],,https://github.com/shirocyara/lincity-ng)
AC_CONFIG_AUX_DIR([mk/autoconf])
AC_CONFIG_MACRO_DIR([mk/macro])
AM_INIT_AUTOMAKE(subdir-objects)

#AC_USE_SYSTEM_EXTENSIONS
#AM_GNU_GETTEXT([external])
#AM_GNU_GETTEXT_VERSION(0.19.7)
#AM_GNU_GETTEXT_INTL_SUBDIR

AC_CANONICAL_BUILD
AC_CANONICAL_HOST

AC_CONFIG_SRCDIR([src/lincity-ng/main.cpp])
AC_CONFIG_HEADERS([config.h])

#----------------------------------------------------------------------------
# Check for build variant (debug, profile, optimize)
#----------------------------------------------------------------------------
VARIANT=optimize
AC_ARG_ENABLE([optimize], [AS_HELP_STRING([--enable-optimize],
    [build with optimizations enabled (default YES)])],
    [test "$enableval" = "yes" && VARIANT=optimize])

AC_ARG_ENABLE([debug], [AS_HELP_STRING([--enable-debug],
    [build with debugging information (default NO)])],
    [test "$enableval" = "yes" && VARIANT=debug])

AC_ARG_ENABLE([profile], [AS_HELP_STRING([--enable-profile],
    [build with profiling information (default NO)])],
    [test "$enableval" = "yes" && VARIANT=profile])
AC_SUBST([VARIANT])

#----------------------------------------------------------------------------
# Checks for programs.
#----------------------------------------------------------------------------
AM_PROG_AR
AC_PROG_CXX
AC_PROG_INSTALL
AC_PROG_RANLIB
AC_CHECK_PROGS([XGETTEXT], xgettext)
AC_CHECK_PROGS([XSLTPROC], xsltproc)

# check if our c++ compiler is gcc3.2 or newer
AC_MSG_CHECKING([whether g++ is new enough])
AC_LANG_PUSH([C++])
AC_COMPILE_IFELSE([AC_LANG_PROGRAM([], [
#ifndef __GNUC__
#error no gcc compiler found (__GNUC__ not defined)
#endif
#if __GNUC__ < 3 || (__GNUC__ == 3 && __GNUC__ < 2)
#error gcc compiler too old. Need at least version 3.2.0
#endif
])],[AC_MSG_RESULT(yes)], [
	AC_MSG_RESULT(no)
	AC_MSG_ERROR([
Error: Your gcc version is too old. Lincity-ng needs at least gcc 3.2.0.
])])
AC_LANG_POP([C++])

#----------------------------------------------------------------------------
# Checks for libraries.
#----------------------------------------------------------------------------

AX_BINRELOC

AX_CHECK_ZLIB

AM_PATH_XML2(2.6.11)

AX_CHECK_GL

dnl Check for SDL
SDL_VERSION=1.2.5
AM_PATH_SDL($SDL_VERSION, :, AC_MSG_ERROR([*** SDL version $SDL_VERSION not found!]))
AX_PATH_SDL_XXX([mixer], [1.2.2], :, AC_MSG_ERROR([*** SDL_mixer version over 1.2.2 not found!]))
AX_PATH_SDL_XXX([image], [1.2.1], :, AC_MSG_ERROR([*** SDL_image version over 1.2.1 not found!]))
AX_PATH_SDL_XXX([ttf],   [2.0.8], :, AC_MSG_ERROR([*** SDL_ttf version over 2.0.8 not found!]))
AX_PATH_SDL_XXX([gfx],   [2.0.13],:, AC_MSG_ERROR([*** SDL_gfx version over 2.0.13 not found!]))
AC_CHECK_LIB([physfs], [PHYSFS_init], AC_SUBST([PHYSFS_LIBS], [-lphysfs]), AC_MSG_ERROR([Please install physfs >= 1.0]))

#----------------------------------------------------------------------------
# Checks for header files.
#----------------------------------------------------------------------------
AC_HEADER_DIRENT
AC_HEADER_STDC
AC_HEADER_TIME

AC_CHECK_HEADERS([fcntl.h limits.h stddef.h stdint.h unistd.h])

AC_CHECK_HEADERS([physfs.h], ,
  AC_MSG_ERROR([ *** PhysFS library found but cannot find headers (http://icculus.org/physfs/)]))

# compiler characteristics
AC_C_CONST
AC_C_INLINE
AC_CHECK_FUNCS(gettimeofday mkdir popen)

AM_ICONV
AC_SUBST([ICONV_LIBS], [$LIBICONV])

#----------------------------------------------------------------------------
# Checks for typedefs, structures, and compiler characteristics.
#----------------------------------------------------------------------------
AC_CHECK_HEADER_STDBOOL
AC_C_INLINE
AC_TYPE_INT16_T
AC_TYPE_INT32_T
AC_TYPE_INT64_T
AC_TYPE_INT8_T
AC_TYPE_SIZE_T
AC_TYPE_SSIZE_T
AC_TYPE_UINT16_T
AC_TYPE_UINT32_T
AC_TYPE_UINT64_T
AC_TYPE_UINT8_T

#----------------------------------------------------------------------------
# Checks for library functions.
#----------------------------------------------------------------------------
AC_FUNC_CHOWN
AC_FUNC_MALLOC
AC_FUNC_REALLOC
AC_CHECK_FUNCS([floor getcwd memset mkdir pow setlocale sqrt strcasecmp strchr strdup strerror strrchr strstr])

case "${VARIANT}" in
  "optimize" )
    CXXFLAGS="-O3 -g -Wall"
#    CXXFLAGS="$CXXFLAGS -march=native"
    LIBS="-g $LIBS"
    ;;
  "debug" )
    CXXFLAGS="-Wall -W -O0 -g3 -DDEBUG -Werror"
    LIBS="-g3 $LIBS"
    ;;
  "profile" )
    CXXFLAGS="-O3 -g3 -pg"
    LIBS="-g3 -pg $LIBS"
    ;;
  * ) AC_MSG_ERROR([Invalid variant ${VARIANT} selected]) ;;
esac

RES_FILE=""
AS_CASE([$host_os],[mingw*], [
  CXXFLAGS+=" -static-libgcc -static-libstdc++"
  RES_FILE="${ac_pwd}/contrib/win32/lincity-ng.res"
#  LIBS="$LIBS -lws2_32 -lpsapi -liphlpapi -lshell32 -luserenv -luser32"
])
AC_SUBST([RES_FILE])

AC_CONFIG_FILES([Makefile
                 src/Makefile
                 src/gui/Makefile
                 src/PhysfsStream/Makefile
                 src/tinygettext/Makefile
                 src/lincity/Makefile
                 src/lincity-ng/Makefile])
#AC_CONFIG_FILES([Makefile po/Makefile.in])
AC_OUTPUT

AC_MSG_NOTICE([-------------------------------------------------------------------
 Configuration results
host  : $host
build : $build
PACKAGE_NAME    : $PACKAGE_NAME
PACKAGE_VERSION : $PACKAGE_VERSION
------------------------------------------------------------------------------
BINRELOC_LIBS   : $BINRELOC_LIBS
BINRELOC_CFLAGS : $BINRELOC_CFLAGS
ZLIB_LIBS       : $ZLIB_LIBS
XML_LIBS        : $XML_LIBS
XML_CPPFLAGS    : $XML_CPPFLAGS
GL_LIBS         : $GL_LIBS
GL_CFLAGS       : $GL_CFLAGS
SDL_LIBS        : $SDL_LIBS
SDL_CFLAGS      : $SDL_CFLAGS
SDL_LIBS_mixer  : $SDL_LIBS_mixer
SDL_LIBS_ttf    : $SDL_LIBS_ttf
SDL_LIBS_image  : $SDL_LIBS_image
SDL_LIBS_gfx    : $SDL_LIBS_gfx
ICONV_LIBS      : $ICONV_LIBS
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
LIBS            : $LIBS
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
CXXFLAGS        : $CXXFLAGS
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
CPPFLAGS        : $CPPFLAGS
 - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - - -
LDFLAGS         : $LDFLAGS
------------------------------------------------------------------------------])

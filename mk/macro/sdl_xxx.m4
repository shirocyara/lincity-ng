dnl AM_PATH_SDL_XXX(XXX, [MINIMUM-VERSION, [ACTION-IF-FOUND [, ACTION-IF-NOT-FOUND]]])
dnl Test for SDL_XXX
dnl
AC_DEFUN([AX_PATH_SDL_XXX],
[
  if test $1 = "mixer" ; then
    libm=mixer
    defm1=SDL_MIXER_MAJOR_VERSION
    defm2=SDL_MIXER_MINOR_VERSION
    defm3=SDL_MIXER_PATCHLEVEL
  elif test $1 = "image" ; then
    libm=image
    defm1=SDL_IMAGE_MAJOR_VERSION
    defm2=SDL_IMAGE_MINOR_VERSION
    defm3=SDL_IMAGE_PATCHLEVEL
  elif test $1 = "ttf" ; then
    libm=ttf
    defm1=SDL_TTF_MAJOR_VERSION
    defm2=SDL_TTF_MINOR_VERSION
    defm3=SDL_TTF_PATCHLEVEL
  elif test $1 = "gfx" ; then
    libm=gfxPrimitives
    defm1=SDL_GFXPRIMITIVES_MAJOR
    defm2=SDL_GFXPRIMITIVES_MINOR
    defm3=SDL_GFXPRIMITIVES_MICRO
  fi
  
  min_sdl_xxx_version=ifelse([$2], ,0.0.0, $2)
  AC_MSG_CHECKING(for SDL_$1 - version >= $min_sdl_xxx_version)
  no_sdl_xxx=""
  if test "$SDL_CONFIG" != "no" ; then
    sdl_xxx_major_version=`echo $min_sdl_xxx_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\1/'`
    sdl_xxx_minor_version=`echo $min_sdl_xxx_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\2/'`
    sdl_xxx_micro_version=`echo $min_sdl_xxx_version | sed 's/\([[0-9]]*\).\([[0-9]]*\).\([[0-9]]*\)/\3/'`
    if test "x$enable_sdltest" = "xyes" ; then
      ac_save_CFLAGS="$CFLAGS"
      ac_save_CXXFLAGS="$CXXFLAGS"
      ac_save_LIBS="$LIBS"
      CFLAGS="$CFLAGS $SDL_CFLAGS"
      CXXFLAGS="$CXXFLAGS $SDL_CFLAGS"
      LIBS="$LIBS $SDL_LIBS -lSDL_$1"
      AC_LANG_PUSH([C])
      AC_RUN_IFELSE(
        [AC_LANG_SOURCE([[
#include <SDL/SDL_${libm}.h>
int main (int argc, char *argv[])
{
	int major, minor, micro;
	major = ${defm1};
	minor = ${defm2};
	micro = ${defm3};

	if ((major > $sdl_xxx_major_version) ||
	   ((major == $sdl_xxx_major_version) && (minor > $sdl_xxx_minor_version)) ||
	   ((major == $sdl_xxx_major_version) && (minor == $sdl_xxx_minor_version) && (micro >= $sdl_xxx_micro_version)))
	{
		return 0;
	} else {
		return 1;
	}
}
]])], , no_sdl_xxx=yes,[echo $ac_n "cross compiling; assumed OK... $ac_c"])
      AC_LANG_POP([C])
      CFLAGS="$ac_save_CFLAGS"
      CXXFLAGS="$ac_save_CXXFLAGS"
      LIBS="$ac_save_LIBS"
    fi
  fi
  
  if test "x$no_sdl_xxx" = x ; then
    AC_MSG_RESULT(yes)
    SDL_LIBS_$1="-lSDL_$1"
    AC_SUBST([SDL_LIBS_$1])
    ifelse([$3], , :, [$3])
  else
    AC_MSG_RESULT(no)
    if test "$SDL_CONFIG" = "no" ; then
      echo "*** The sdl-config script installed by SDL could not be found"
      echo "*** If SDL was installed in PREFIX, make sure PREFIX/bin is in"
      echo "*** your path, or set the SDL_CONFIG environment variable to the"
      echo "*** full path to sdl-config."
    fi
    ifelse([$4], , :, [$4])
  fi
])

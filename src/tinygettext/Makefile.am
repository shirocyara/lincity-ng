#
#  Makefile.am for src/tinygettext
#
noinst_LIBRARIES = libtinygettext.a
AM_CPPFLAGS = -I../ ${SDL_CFLAGS}
LIBS+= ${SDL_LIBS}
libtinygettext_a_SOURCES = \
  findlocale.cpp tinygettext.cpp findlocale.hpp gettext.hpp tinygettext.hpp

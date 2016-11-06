#
#  Makefile.am for src/lincity-ng
#
bin_PROGRAMS = lincity-ng
AM_CPPFLAGS = -I../ ${XML_CPPFLAGS} ${SDL_CFLAGS} ${GL_CFLAGS} -DDEFAULT_LIBDIR="${appdatadir}"
LIBS+= ${XML_LIBS} ${SDL_LIBS} ${SDL_LIBS_image} ${SDL_LIBS_mixer} ${SDL_LIBS_ttf} ${SDL_LIBS_gfx} ${PHYSFS_LIBS} ${GL_LIBS} ${ICONV_LIBS} ${ZLIB_LIBS} ${BINRELOC_LIBS}
lincity_ng_SOURCES = \
  ButtonInterface.cpp ButtonPanel.cpp CheckButton.cpp Config.cpp Debug.cpp Dialog.cpp EconomyGraph.cpp ErrorInterface.cpp Game.cpp GameView.cpp HelpWindow.cpp main.cpp MainLincity.cpp MainMenu.cpp MapEdit.cpp MiniMap.cpp Mps.cpp MpsInterface.cpp PBar.cpp PbarInterface.cpp readdir.cpp ReadPngInterface.cpp ScreenInterface.cpp Sound.cpp TimerInterface.cpp Util.cpp \
  ButtonPanel.hpp CheckButton.hpp Config.hpp Debug.hpp Dialog.hpp EconomyGraph.hpp ErrorInterface.hpp Game.hpp GameView.hpp HelpWindow.hpp main.hpp MainLincity.hpp MainMenu.hpp MapEdit.hpp MapPoint.hpp MiniMap.hpp Mps.hpp PBar.hpp readdir.hpp ScreenInterface.hpp Sound.hpp TimerInterface.hpp Util.hpp \
  binreloc.c \
  binreloc.h

lincity_ng_LDADD = \
  ../gui/liblincity_gui.a ../lincity/liblincity_lib.a ../tinygettext/libtinygettext.a ../PhysfsStream/libphysfsstream.a ${RES_FILE}

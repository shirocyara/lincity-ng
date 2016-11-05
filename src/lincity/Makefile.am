#
#  Makefile.am for src/lincity
#
noinst_LIBRARIES = liblincity_lib.a
AM_CPPFLAGS = -I../ -DDEFAULT_LIBDIR="${appdatadir}"
LIBS+= ${ICONV_LIBS} ${ZLIB_LIBS}
liblincity_lib_a_SOURCES = \
  engglobs.cpp engine.cpp fileutil.cpp init_game.cpp lc_locale.cpp lclib.cpp lintypes.cpp loadsave.cpp old_ldsvguts.cpp power.cpp simulate.cpp stats.cpp transport.cpp \
  confw32.h engglobs.h engine.h fileutil.h init_game.h lc_locale.h lcconfig.h lclib.h lcstring.h lctypes.h lin-city.h lintypes.h loadsave.h old_ldsvguts.h power.h simulate.h stats.h transport.h \
  modules/blacksmith.cpp modules/coal_power.cpp modules/coalmine.cpp modules/commune.cpp modules/cricket.cpp modules/fire.cpp modules/firestation.cpp modules/health_centre.cpp modules/heavy_industry.cpp modules/light_industry.cpp modules/market.cpp modules/mill.cpp modules/monument.cpp modules/oremine.cpp modules/organic_farm.cpp modules/parkland.cpp modules/port.cpp modules/pottery.cpp modules/power_line.cpp modules/rail.cpp modules/recycle.cpp modules/residence.cpp modules/road.cpp modules/rocket_pad.cpp modules/school.cpp modules/shanty.cpp modules/solar_power.cpp modules/substation.cpp modules/tip.cpp modules/track.cpp modules/university.cpp modules/water.cpp modules/waterwell.cpp modules/windmill.cpp \
  modules/all_modules.h modules/blacksmith.h modules/coal_power.h modules/coalmine.h modules/commune.h modules/cricket.h modules/fire.h modules/firestation.h modules/health_centre.h modules/heavy_industry.h modules/light_industry.h modules/market.h modules/mill.h modules/modules.h modules/monument.h modules/oremine.h modules/organic_farm.h modules/parkland.h modules/port.h modules/pottery.h modules/power_line.h modules/rail.h modules/recycle.h modules/residence.h modules/road.h modules/rocket_pad.h modules/school.h modules/shanty.h modules/solar_power.h modules/substation.h modules/tip.h modules/track.h modules/university.h modules/water.h modules/waterwell.h modules/windmill.h \
  ../gui_interface/dialbox_interface.h ../gui_interface/mps.h ../gui_interface/pbar_interface.h ../gui_interface/readpng.h ../gui_interface/screen_interface.h ../gui_interface/shared_globals.h

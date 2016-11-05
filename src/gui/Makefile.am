#
#  Makefile.am for src/gui
#
noinst_LIBRARIES = liblincity_gui.a
AM_CPPFLAGS = -I../ ${SDL_CFLAGS} ${XML_CPPFLAGS} ${GL_CFLAGS}
LIBS+= ${XML_LIBS} ${SDL_LIBS} ${SDL_LIBS_image} ${PHYSFS_LIBS} ${GL_LIBS} ${ICONV_LIBS}
liblincity_gui_a_SOURCES = \
  Button.cpp Child.cpp Color.cpp Component.cpp ComponentFactory.cpp ComponentLoader.cpp Desktop.cpp \
  Document.cpp DocumentImage.cpp Event.cpp FilledRectangle.cpp Filter.cpp FontManager.cpp \
  Gradient.cpp Image.cpp Panel.cpp Paragraph.cpp Rect2D.cpp ScrollBar.cpp ScrollView.cpp \
  Style.cpp SwitchComponent.cpp TableLayout.cpp TextureManager.cpp TooltipManager.cpp \
  Window.cpp XmlReader.cpp \
  Button.hpp Child.hpp Color.hpp Component.hpp ComponentFactory.hpp ComponentLoader.hpp Desktop.hpp \
  Document.hpp DocumentElement.hpp DocumentImage.hpp Event.hpp FilledRectangle.hpp Filter.hpp FontManager.hpp \
  Gradient.hpp Image.hpp Painter.hpp Panel.hpp Paragraph.hpp Rect2D.hpp ScrollBar.hpp ScrollView.hpp \
  Style.hpp SwitchComponent.hpp TableLayout.hpp Texture.hpp TextureManager.hpp TooltipManager.hpp \
  Vector2.hpp Window.hpp XmlReader.hpp \
  callback/Callback.hpp callback/CallbackBase.hpp callback/Signal.hpp \
  PainterGL/PainterGL.cpp PainterGL/TextureGL.cpp PainterGL/TextureManagerGL.cpp \
  PainterGL/PainterGL.hpp PainterGL/TextureGL.hpp PainterGL/TextureManagerGL.hpp \
  PainterSDL/PainterSDL.cpp PainterSDL/TextureManagerSDL.cpp PainterSDL/TextureSDL.cpp \
  PainterSDL/PainterSDL.hpp PainterSDL/TextureManagerSDL.hpp PainterSDL/TextureSDL.hpp

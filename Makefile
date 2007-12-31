SDL_PATH = ../SDL-1.2.11
SDL_INCLUDE = $(SDL_PATH)/include
SDL_LIB = $(SDL_PATH)/lib

GLEW_PATH = ../glew
GLEW_INCLUDE = $(GLEW_PATH)/include

BOOST_PATH = ../vge/SDK/win32/boost_1_34_0
BOOST_INCLUDE = $(BOOST_PATH)/include/boost-1_34
BOOST_LIB = -L$(BOOST_PATH)/lib -lboost_filesystem-mgw34-1_34

SDL_IMAGE_PATH = ../SDL_image-1.2.6
SDL_IMAGE_INCLUDE = $(SDL_IMAGE_PATH)/include
SDL_IMAGE_LIB = $(SDL_IMAGE_PATH)/lib

SDL_MIXER_PATH = ../SDL_mixer-1.2.8
SDL_MIXER_INCLUDE = $(SDL_MIXER_PATH)/include
SDL_MIXER_LIB = $(SDL_MIXER_PATH)/lib

CPPFLAGS += -I$(SDL_INCLUDE) \
	-I$(BOOST_INCLUDE) \
	-I$(GLEW_INCLUDE) \
	-I$(SDL_IMAGE_INCLUDE) \
	-I$(SDL_MIXER_INCLUDE) \
	-I. \
	-D_GNU_SOURCE=1 -Dmain=SDL_main -DWINDOWS

LINKFLAGS += -mwindows -lmingw32 -lopengl32 -lglu32 \
	-L$(SDL_LIB) -lSDLmain -lSDL_ttf -lSDL.dll \
	-L$(SDL_IMAGE_LIB) -lSDL_image \
	-L$(SDL_MIXER_LIB) -lSDL_mixer \
	$(BOOST_LIB)

GLUI_SOURCES = slak/glui/app.cpp \
	slak/glui/hiscore_screen.cpp \
	slak/glui/hiscore_table.cpp \
	slak/glui/label.cpp \
	slak/glui/orthomode.cpp \
	slak/glui/pulse.cpp \
	slak/glui/rgbpic.cpp \
	slak/glui/screen.cpp

TETRIS_SOURCES = slak/tetris/field.cpp \
	slak/tetris/main.cpp \
	slak/tetris/renderer.cpp \
	slak/tetris/root_menu.cpp \
	slak/tetris/soundm.cpp \
	slak/tetris/tetrad.cpp \
	slak/tetris/tetris.cpp \
	slak/tetris/tetris_app.cpp \
	slak/tetris/tetris_screen.cpp

GLUI_OBJS := $(subst .cpp,.o,$(GLUI_SOURCES))
GLUI_OBJS := $(subst slak/glui/,,$(GLUI_OBJS))

TETRIS_OBJS := $(subst .cpp,.o,$(TETRIS_SOURCES))
TETRIS_OBJS := $(subst slak/tetris/,,$(TETRIS_OBJS))


VPATH = slak/glui:slak/tetris

all: tetris.exe

tetris.exe: $(GLUI_OBJS) $(TETRIS_OBJS)
	g++ -o tetris.exe $(TETRIS_OBJS) $(GLUI_OBJS) $(LINKFLAGS)

tidy:
	rm -f *.o
	rm -f `find . -name "*~"`

BOOST_LIB = -lboost_filesystem-gcc41-1_34_1

CPPFLAGS += -I. $(shell sdl-config --cflags)
LINKFLAGS += $(shell sdl-config --libs) -lSDL_ttf -lSDL_image -lSDL_mixer \
             $(BOOST_LIB) -lGL

GLUI_SOURCES = $(wildcard slak/glui/*.cpp)
TETRIS_SOURCES = $(wildcard slak/tetris/*.cpp)

GLUI_OBJS := $(subst .cpp,.o,$(GLUI_SOURCES))
GLUI_OBJS := $(subst slak/glui/,,$(GLUI_OBJS))

TETRIS_OBJS := $(subst .cpp,.o,$(TETRIS_SOURCES))
TETRIS_OBJS := $(subst slak/tetris/,,$(TETRIS_OBJS))

VPATH = slak/glui:slak/tetris

all: tetris

tetris: $(GLUI_OBJS) $(TETRIS_OBJS)
	g++ -o $@ $^ $(LINKFLAGS)

tidy:
	rm -f *.o
	rm -f `find . -name "*~"`

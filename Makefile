# slak-games: simple SDL+OpenGL based games
# Copyright (C) 2006-2008 Artem Baguinski <femistofel@gmail.com>
#
# This program is free software; you can redistribute it and/or
# modify it under the terms of the GNU General Public License
# as published by the Free Software Foundation; either version 2
# of the License, or (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with this program; if not, write to the Free Software
# Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.

PROJECT_NAME = slak-games
prefix = /usr
bin_prefix = $(prefix)/bin
data_prefix = $(prefix)/share/$(PROJECT_NAME)

BOOST_LIB = -lboost_filesystem-gcc41-1_34_1

CPPFLAGS += -I. $(shell sdl-config --cflags)
LINK=g++
LINKFLAGS += $(shell sdl-config --libs) -lSDL_ttf -lSDL_image -lSDL_mixer \
             $(BOOST_LIB) -lGL

GLUI_SOURCES = $(wildcard slak/glui/*.cpp)
TETRIS_SOURCES = $(wildcard slak/tetris/*.cpp)

GLUI_OBJS := $(notdir $(GLUI_SOURCES:.cpp=.o))
TETRIS_OBJS := $(notdir $(TETRIS_SOURCES:.cpp=.o))

VPATH = slak/glui:slak/tetris

all: tetris

DEPS = $(GLUI_OBJS:.o=.P) $(TETRIS_OBJS:.o=.P)
-include $(DEPS)

$(GLUI_OBJS) $(TETRIS_OBJS): Makefile

#
# Combining dependency generation with compilation We ask g++ to
# generate deps to .d file then filter it into .P file to avoid "No
# rule to make target..." errors.
#
# see: http://make.paulandlesley.org/autodep.html
#
%.o : %.cpp
	$(CXX) $(CPPFLAGS) $(CXXFLAGS) -MD -c -o $@ $<
	@cp $*.d $*.P; \
	sed -e 's/#.*//' -e 's/^[^:]*: *//' -e 's/ *\\$$//' \
	    -e '/^$$/ d' -e 's/$$/ :/' < $*.d >> $*.P; \
	rm -f $*.d

tetris: $(GLUI_OBJS) $(TETRIS_OBJS)
	$(LINK) -o $@ $^ $(LINKFLAGS)

tidy:
	rm -f *.o
	rm -f `find . -name "*~"`

clean: tidy
	rm -f tetris

install: tetris
	install -d $(DESTDIR)$(bin_prefix)
	install tetris $(DESTDIR)$(bin_prefix)
	install -d $(DESTDIR)$(data_prefix)/bitmaps
	install -m 644 media/bitmaps/*.bmp media/bitmaps/*.png $(DESTDIR)$(data_prefix)/bitmaps
	install -d $(DESTDIR)$(data_prefix)/fonts
	install -m 644 media/fonts/TouristTrap.ttf $(DESTDIR)$(data_prefix)/fonts
	install -d $(DESTDIR)$(data_prefix)/sound
	install -m 644 media/sound/*.wav $(DESTDIR)$(data_prefix)/sound


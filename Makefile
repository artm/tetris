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


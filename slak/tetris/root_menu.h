/*
 * slak-games: simple SDL+OpenGL based games
 * Copyright (C) 2006-2008 Artem Baguinski <femistofel@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

#ifndef slak_tetris_root_menu_h
#define slak_tetris_root_menu_h

#include <vector>
#include "slak/glui/screen.h"
#include "slak/glui/label.h"

namespace slak {
	namespace tetris {
		struct RootMenu : slak::glui::Screen {
		        // compose the menu screen
			RootMenu();
			// overloads of Screen's methods
			virtual bool handle(SDL_Event& ev);
			virtual void draw();
		};
	}
}

#endif

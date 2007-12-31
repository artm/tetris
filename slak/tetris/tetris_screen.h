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

#ifndef slak_tetris_screen_h
#define slak_tetris_screen_h

#include "tetris.h"
#include "renderer.h"
#include "slak/glui/screen.h"
#include "slak/glui/toggle.h"

namespace slak {
	namespace tetris {
		struct GameScreenPriv;

		// GameScreen keeps pointers to other bits of the application
		// it needs to know about. Otherwise it's just a slak::glui::Screen
		struct GameScreen : slak::glui::Screen {
		        // the game logic
			Game * game;
			// tetris renderer
			Renderer renderer;
			// private data - the true private fields and methods are invisible
			// through the .h files. Not that C++ makes life easy with such a
			// design, but sometimes principles are more important then convenience
			GameScreenPriv * priv;
			// The "game over" overlay sits in a switch-on-and-off-able toggle
			slak::glui::Toggle gameover_toggle;

			GameScreen(Game * game);
			virtual ~GameScreen();

			// overloads of Screen methods
			virtual bool handle(SDL_Event& ev);
			virtual void draw();
		};
	}
}

#endif

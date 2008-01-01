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

#ifndef slak_tetris_app_h
#define slak_tetris_app_h

#include "boost/filesystem/convenience.hpp"

#include <string>
#include "slak/glui/app.h"
#include "tetris.h"
#include "soundm.h"
#include "tetris_screen.h"
#include "slak/glui/hiscore_screen.h"
#include "root_menu.h"

namespace slak {
	namespace tetris {
		struct TetrisApp : slak::glui::App {
			// Game logic
			Game tetris;
			// sound manager
			SoundManager soundm;

			// game screens
			GameScreen game_screen;
			slak::glui::HiScoreScreen hiscore_screen;
			RootMenu root;

			// custom events
			static const int
				GOTO_HISCORES	= USER_APP_EV_BASE,
				STATE_CHANGED	= USER_APP_EV_BASE + 1,
				NEW_GAME	= USER_APP_EV_BASE + 2,
				GOTO_ROOT	= USER_APP_EV_BASE + 3,
				RESUME		= USER_APP_EV_BASE + 4,
				TICK		= USER_APP_EV_BASE + 5;
			TetrisApp(int w, int h);
			// overloaded event handler
			virtual bool handle(SDL_Event& ev);

                        static boost::filesystem::path data_dir;
			static std::string data_file(std::string rel_path) {
				return (data_dir / boost::filesystem::path(rel_path)).file_string();
			}
                        static std::string fontname;
                        static boost::filesystem::path find_data_dir();
		};
	}
}

#endif

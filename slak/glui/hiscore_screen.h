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

#ifndef slak_glui_hiscore_screen_h
#define slak_glui_hiscore_screen_h

#include "hiscore_table.h"
#include "screen.h"
#include "label.h"
#include "pulse.h"

namespace slak {
	namespace glui {
		struct HiScoreScreen : Screen {
			static const int cursor_delay = 400; // ms

			HiScoreTable * table;
			unsigned int leave_message;
			Pulse cursor_pulse;

			std::vector<Label*> nameLabels, scoreLabels;

			HiScoreScreen(HiScoreTable * t, unsigned int leave_message, std::string fontname);
			virtual bool handle(SDL_Event& ev);
			virtual void draw();
		};
	}
}

#endif


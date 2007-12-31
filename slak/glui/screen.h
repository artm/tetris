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

#ifndef slak_glui_screen_h
#define slak_glui_screen_h

#include <vector>
#include "overlay.h"
#include "drawmode.h"

namespace slak {
	namespace glui {
		struct Screen {
		  // Screen events base
			static const int SCREEN_EV_BASE = 1000;
		  // Rendering request event ID
			static const int DRAW_FRAME = SCREEN_EV_BASE;

		  // a list of overlays - things drawn on top of the screen
			std::vector<Overlay*> overlays;
		  // a list of draw modes (OpenGL state changing objects)
			std::vector<DrawMode*> modes;

		  // handle event
			virtual bool handle(SDL_Event& ev);
		  // draw yourself
			virtual void draw();
		};

	}
}

#endif

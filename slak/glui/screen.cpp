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

#include <algorithm>
#include <functional>
#include <SDL.h>
#include <assert.h>
#include "screen.h"

using namespace slak::glui;

// default event handler only handles draw requests
bool Screen::handle(SDL_Event& ev)
{
	switch(ev.type) {
	case SDL_USEREVENT:
		switch(ev.user.code) {
		case DRAW_FRAME:
			draw();
			return true;
		}
		break;
	}
	return false;
}

// default draw function only draws installed overlays
void Screen::draw()
{
        // init draw modes
	std::for_each(modes.begin(),
		      modes.end(),
		      std::mem_fun(&DrawMode::drawPre));

	// draw overlays
	std::for_each(overlays.begin(),
		      overlays.end(),
		      std::mem_fun(&Overlay::draw));

	// clear draw modes
	std::for_each(modes.rbegin(),
		      modes.rend(),
		      std::mem_fun(&DrawMode::drawPost));

}


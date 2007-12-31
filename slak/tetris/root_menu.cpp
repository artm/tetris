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

#include <SDL.h>
#include <SDL_ttf.h>
#include "slak/glui/gl-include.h"
#include "root_menu.h"
#include "tetris_app.h"
#include "slak/glui/orthomode.h"
#include "slak/glui/rgbpic.h"

using namespace slak::tetris;
using namespace slak::glui;

RootMenu::RootMenu()
{
  // just setup a background
	overlays.push_back(new RGBPic("media/bitmaps/tetris-menu.bmp"));
  // and ortho projection
	modes.push_back(new OrthoMode);
}

bool RootMenu::handle(SDL_Event& ev)
{
  // handle menu keys
	switch(ev.type) {
	case SDL_KEYDOWN:
		switch(ev.key.keysym.sym) {
		case SDLK_F1:
			App::push(TetrisApp::NEW_GAME);
			return true;
		case SDLK_F2:
			App::push(TetrisApp::RESUME);
			return true;
		case SDLK_F3:
			App::push(TetrisApp::GOTO_HISCORES);
			return true;
		case SDLK_F10:
			App::push(TetrisApp::QUIT);
			return true;
		}
	}
  // or pass event to the parent class
	return Screen::handle(ev);
}

void RootMenu::draw()
{
	Screen::draw();
	// for greater flexibility default draw() doesn't swap buffers - do it here
	SDL_GL_SwapBuffers();
}

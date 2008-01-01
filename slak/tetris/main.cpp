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

#include <cstdlib>
#include <cstdio>
#include <ctime>
#include <string>
#include <sstream>
#include <iostream>

#include <SDL.h>
#include <SDL_ttf.h>

#include "tetris_app.h"

using namespace slak::tetris;

extern "C"
int main(int argc,char* argv[])
{
  // init libraries
	if (SDL_Init(SDL_INIT_VIDEO|
		     SDL_INIT_TIMER) < 0) {
		std::cerr << "SDL initialization error: "
			<< SDL_GetError() << "\n";
		exit(1);
	}
	atexit(SDL_Quit);

	if (TTF_Init() < 0) {
		std::cerr << "SDL_ttf initialization error: "
			<< SDL_GetError() << "\n";
		exit(1);
	}

	// tetris friendly keyboard settings
	SDL_EnableKeyRepeat(250, 50);

	// start tetris
	try {
		slak::tetris::TetrisApp app(1024, 768);
		app.run();
	} catch (std::string& s) {
		std::cout << "Exception: " << s << std::endl;
		exit(1);
	}

	exit(0);
}


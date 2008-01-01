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
#include <string>
#include <SDL.h>
#include "tetris_app.h"
#include "slak/glui/rgbpic.h"

using namespace slak::tetris;
using namespace slak::glui;

namespace fs = boost::filesystem;

fs::path TetrisApp::data_dir = TetrisApp::find_data_dir();
std::string TetrisApp::fontname = TetrisApp::data_file("fonts/TouristTrap.ttf");

fs::path TetrisApp::find_data_dir()
{
	fs::path data_dir;
	fs::file_status bmp_dir_stat, snd_dir_stat, fnt_dir_stat;

	char * data_dir_candidates[] = { "media", "/usr/share/slak-games", NULL };
	char ** data_dir_cand = data_dir_candidates;

	while(*data_dir_cand) {
		data_dir = fs::path(*data_dir_cand);
		data_dir_cand++;

		if (!fs::exists(fs::status(data_dir))) continue;
		if (!fs::exists(fs::status(data_dir / "bitmaps"))) continue;
		if (!fs::exists(fs::status(data_dir / "sound"))) continue;
		if (!fs::exists(fs::status(data_dir / "fonts"))) continue;

		goto found_data_dir;
	};
	throw std::string("Coudn't find data dir");

found_data_dir:
	std::cout << "Found data dir: " << data_dir << std::endl;
	return data_dir;
}

TetrisApp::TetrisApp(int w,int h)
	: tetris(), soundm(), game_screen(&tetris),
	root(), slak::glui::App(w,h,&root)
{
	// Platform dependent place for high scores file
	fs::path conf_dir;

#ifdef __APPLE__
	conf_dir = fs::path(getenv("HOME")) / fs::path("Library/Slak/Tetris/",
						       fs::portable_posix_name);
#else
#  ifdef WINDOWS
	// on windows $APPDATA/Slak/Tetris
	conf_dir = fs::path(getenv("APPDATA")) / fs::path("Slak/Tetris/",
							  fs::windows_name);
#  else

	// on posix make ~/.slak/tetris
	conf_dir = fs::path(getenv("HOME")) / fs::path(".slak/tetris/",
						       fs::portable_posix_name);
#  endif

#endif
	fs::create_directories(conf_dir);

	hiscore_screen.init(&tetris.hi_scores, GOTO_ROOT,
			    fontname);

	// initialize the game logic
	tetris.hi_scores.load(conf_dir / "hiscores");
	tetris.setSoundManager(&soundm);
	tetris.newGame();

	// load sounds
	char* map[][2] = {
		{"click", "sound/tetris-click.wav" },
		{"woosh", "sound/tetris-woosh.wav" },
		{"snap",  "sound/tetris-snap.wav" },
		{"tada",  "sound/tetris-tada.wav" },
	};
	int n = sizeof(map)/sizeof(char*[2]);

	for(int i=0; i<n; i++) {
		std::string sample_file = data_file(map[i][1]);
		Mix_Chunk* sample = Mix_LoadWAV(sample_file.c_str());
		if (sample)
			soundm.samples[map[i][0]] = sample;
		else {
			std::cerr << "Can't open sample " <<
				sample_file << ": " <<
				SDL_GetError() << "\n";
		}
	}

	// we use generic hiscore_screen, but add a tetris specific
	// background to it
	hiscore_screen.overlays
	  .insert(hiscore_screen.overlays.begin(),
		  new slak::glui::RGBPic(data_file("bitmaps/tetris-hiscore.bmp")));

	// request TICK event to drive the game with tick_delay
	loop(TICK,NULL,NULL,Game::tick_delay);
}

bool TetrisApp::handle(SDL_Event& ev)
{
  // handle our own events
	switch(ev.type) {
	case SDL_USEREVENT:
		switch(ev.user.code) {
		case GOTO_HISCORES:
			setScreen(&hiscore_screen);
			return true;
		case NEW_GAME:
			tetris.newGame();
			// fall through to resume
		case RESUME:
			if (tetris.state != GAME_OVER_STATE)
				setScreen(&game_screen);
			return true;
		case GOTO_ROOT:
			setScreen(&root);
			return true;
		}
	}

	// ... if got here - pass to generic handler
	return slak::glui::App::handle(ev);
}


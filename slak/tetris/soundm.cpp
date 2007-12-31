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

#include <SDL_mixer.h>
#include <iostream>

#include "soundm.h"

using namespace slak::tetris;

SoundManager::SoundManager()
{
  // init audio device
	if (Mix_OpenAudio(44100, AUDIO_S16, 1, 4096) < 0) {
		std::cerr << "SDL_mixer error: " << SDL_GetError() << "\n";
		exit(1);
	}

  // load samples, this is tetris specific, the class is intended to be
  // made generic and initialized from outside later.
	char* map[][2] = {
		{"click", "media/sound/tetris-click.wav"},
		{"woosh", "media/sound/tetris-woosh.wav"},
		{"snap",  "media/sound/tetris-snap.wav"},
		{"tada",  "media/sound/tetris-tada.wav"},
	};
	int n = sizeof(map)/sizeof(char*[2]);

	for(int i=0; i<n; i++) {
		Mix_Chunk* sample = Mix_LoadWAV(map[i][1]);
		if (sample)
			samples[map[i][0]] = sample;
		else {
			std::cerr << "Can't open sample " <<
				map[i][1] << ":" <<
				SDL_GetError() << "\n";
		}
	}
}

void SoundManager::play(std::string tag)
{
  // don't crash when called with non existent tag
	if(samples.find(tag) != samples.end()) {
		Mix_PlayChannel(-1,samples[tag],0);
	} else
		std::cerr << "Unknown sound tag: " << tag << "\n";
}

SoundManager::~SoundManager()
{
	Mix_CloseAudio();
}

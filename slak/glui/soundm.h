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

#ifndef slak_soundm_h
#define slak_soundm_h

#include <string>
#include <map>
#include <SDL_mixer.h>

namespace slak {
	namespace glui {

                // SDL_mixer based sound manager
		struct SoundManager {
                        // tagged samples map
			std::map<std::string, Mix_Chunk*> samples;

			SoundManager();
			~SoundManager();

                        // play sample by tag (channel will be autoallocated)
			void play(std::string tag);
		};

	}
}

#endif

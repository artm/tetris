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

#ifndef slak_glui_app_h
#define slak_glui_app_h

#include <map>
#include <string>
#include <assert.h>
#include <SDL.h>

namespace slak {
	namespace glui {
		struct Screen;


		struct App {

		  // Base event ID for application class specific events
			static const int APP_EV_BASE = 100;
		  // Quit request
			static const int QUIT = APP_EV_BASE;
		  // Base event ID for derived application specific events
			static const int USER_APP_EV_BASE = 500;
		  // Base event ID for automatically allocated event IDs
			static const int AUTO_ALLOC_EV_BASE = 50000;

		  // singleton
			static App * theApp;

		  // SDL screen or window
			SDL_Surface * sdl_screen;

			Screen * cur_screen;
		  // screenshot counter
			int printed;
		  // when false - main loop will exit
			bool go_on;

		  // names of user defined events
			static std::map<std::string, int> user_event_dict;
		  // id of the next user event
			static int free_event_id;

			App(int width, int height,
				slak::glui::Screen * start_screen);
		  // switch screen
			void setScreen(Screen * s);
		  // run the game
			void run();
		  // take a screen shot
			void printScreen();

		  // handle event (to be overloaded)
		  // return true if handled (and should be discarded)
			virtual bool handle(SDL_Event& ev);

		  // get event id by name
			static int eventId(std::string name);

		  // push (queue) an event by code. data1/2 are event
		  // dependent pointers, if delay > 0 event will fire
		  // in the future
			static SDL_TimerID push(int code, void*data1=NULL,
						void*data2=NULL,
						unsigned int delay = 0);
		  // same as above but event is designated by name
			static SDL_TimerID push(std::string event_name,
						void*data1=NULL,
						void*data2=NULL,
						unsigned int delay = 0);
		  // post a periodic event that will fire every delay ms
			static SDL_TimerID loop(int code, void*data1,
						void*data2,
						unsigned int delay);

			static int getScreenWidth() {
				assert(theApp);
				assert(theApp->sdl_screen);
				return theApp->sdl_screen->w;
			}
			static int getScreenHeight() {
				assert(theApp);
				assert(theApp->sdl_screen);
				return theApp->sdl_screen->h;
			}
		};
	}
}


#endif


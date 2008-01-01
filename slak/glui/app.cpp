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

#include <assert.h>
#include <iostream>
#include <sstream>
#include <SDL.h>
#include "app.h"
#include "screen.h"

using namespace slak::glui;

static Uint32 postEventAndReschedule(Uint32 ival, void * data)
{
	SDL_Event * ev = (SDL_Event*)data;
	SDL_PushEvent(ev);
	return ival;
}

static Uint32 postEventAndDelete(Uint32 ival, void * data)
{
	SDL_Event * ev = (SDL_Event*)data;
	SDL_PushEvent(ev);
	delete ev;
	return 0;
}

App* App::theApp = NULL;
std::map<std::string, int> App::user_event_dict;
int App::free_event_id = AUTO_ALLOC_EV_BASE;


App::App(int width, int height, Screen * start_screen)
	: cur_screen(start_screen), printed(0), go_on(true)
{
	assert(!theApp);
	theApp = this;

	// initialize the game window
	SDL_GL_SetAttribute( SDL_GL_RED_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_GREEN_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_BLUE_SIZE, 8 );
	SDL_GL_SetAttribute( SDL_GL_DOUBLEBUFFER, 1 );


	sdl_screen = SDL_SetVideoMode(width, height, 32,
				      SDL_OPENGL|SDL_FULLSCREEN);
	if (sdl_screen == NULL) {
		std::cerr << "Error setting video mode: " << SDL_GetError();
		exit(1);
	}

	// Add custom event
	user_event_dict["quit"] = QUIT;
}

int App::eventId(std::string name)
{
	if (user_event_dict.count(name)==0) {
		user_event_dict[name] = free_event_id++;
	}
	return user_event_dict[name];
}

SDL_TimerID App::push(std::string event_name,
		      void*data1,
		      void*data2,
		      unsigned int delay)
{
	return push(eventId(event_name), data1, data2, delay);
}

void App::run()
{
	while(go_on) {
		SDL_Event ev;
		while(SDL_PollEvent(&ev)) {
			assert(cur_screen);
			if (!handle(ev))
				cur_screen->handle(ev);
		}
		push(Screen::DRAW_FRAME);

		// give other programs / threads a chance to live
		SDL_Delay(10);
	}
}

// common events handler (will be overloaded)
bool App::handle(SDL_Event& ev)
{
	switch(ev.type) {
	case SDL_KEYDOWN:
	        switch(ev.key.keysym.sym) {
        // ctrl+p saves a numbered screenshot
		case 'p':
		case 'P':
			if (ev.key.keysym.mod & KMOD_CTRL) {
				printScreen();
				return true;
			}
			break;
		}
		break;
	case SDL_USEREVENT:
		switch(ev.user.code) {
	 // if quit's requested - remember that
		case QUIT:
			go_on = false;
			return true;
		}
	}
	return false;
}

void App::setScreen(Screen * s)
{
	assert(s);
	cur_screen = s;
}

SDL_TimerID App::push(int code, void*data1, void*data2, unsigned int delay)
{
  // allocate event structure (SDL will copy it from us)
	SDL_Event ev;
	ev.type = SDL_USEREVENT;
	ev.user.code = code;
	ev.user.data1 = data1;
	ev.user.data2 = data2;
	if (!delay) {
	  // fire right away
		SDL_PushEvent(&ev);
		return NULL;
	} else {
	  // schedule to fire later
		SDL_Event * heap_ev = new SDL_Event;
		*heap_ev = ev;
		return SDL_AddTimer(delay, &postEventAndDelete, heap_ev);
	}
}


SDL_TimerID App::loop(int code, void*data1, void*data2, unsigned int delay)
{
	SDL_Event * ev = new SDL_Event;
	ev->type = SDL_USEREVENT;
	ev->user.code = code;
	ev->user.data1 = data1;
	ev->user.data2 = data2;
	return SDL_AddTimer(delay, &postEventAndReschedule, ev);
}


void App::printScreen()
{
	std::ostringstream os;
	os.width(3);
	os.fill('0');
	os << "screenshot" << printed << ".bmp";
	printed++;
	SDL_SaveBMP(sdl_screen, os.str().c_str());
}

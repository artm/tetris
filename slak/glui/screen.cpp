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


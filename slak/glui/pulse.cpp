#include "pulse.h"

using namespace slak::glui;

Pulse::Pulse(int delay, bool initial_state)
	: delay(delay), state(initial_state), stopwatch(SDL_GetTicks())
{ }

bool Pulse::getState() 
{
	Uint32 now = SDL_GetTicks();
	if ((now - stopwatch) >= delay) {
		stopwatch = now;
		state = ! state;
	}
	return state;
}


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
	slak::tetris::TetrisApp app(1024, 768);
	app.run();
	
	exit(0);
}


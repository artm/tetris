#ifndef slak_tetris_screen_h
#define slak_tetris_screen_h

#include "tetris.h"
#include "renderer.h"
#include "slak/glui/screen.h"
#include "slak/glui/toggle.h"

namespace slak {
	namespace tetris {
		struct GameScreenPriv;

		// GameScreen keeps pointers to other bits of the application
		// it needs to know about. Otherwise it's just a slak::glui::Screen
		struct GameScreen : slak::glui::Screen {
		        // the game logic
			Game * game;
			// tetris renderer
			Renderer renderer;
			// private data - the true private fields and methods are invisible 
			// through the .h files. Not that C++ makes life easy with such a 
			// design, but sometimes principles are more important then convenience
			GameScreenPriv * priv;
			// The "game over" overlay sits in a switch-on-and-off-able toggle
			slak::glui::Toggle gameover_toggle;

			GameScreen(Game * game);
			virtual ~GameScreen();
			
			// overloads of Screen methods
			virtual bool handle(SDL_Event& ev);
			virtual void draw();
		};
	}
}

#endif

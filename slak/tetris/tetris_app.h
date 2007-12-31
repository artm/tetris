#ifndef slak_tetris_app_h
#define slak_tetris_app_h

#include <string>
#include "slak/glui/app.h"
#include "tetris.h"
#include "soundm.h"
#include "tetris_screen.h"
#include "slak/glui/hiscore_screen.h"
#include "root_menu.h"

namespace slak {
	namespace tetris {
		struct TetrisApp : slak::glui::App {
		  // Game logic
			Game tetris;
			// sound manager
			SoundManager soundm;

			// game screens
			GameScreen game_screen;
			slak::glui::HiScoreScreen hiscore_screen;
			RootMenu root;

			// custom events
			static const int 
				GOTO_HISCORES	= USER_APP_EV_BASE,
				STATE_CHANGED	= USER_APP_EV_BASE + 1,
				NEW_GAME	= USER_APP_EV_BASE + 2,
				GOTO_ROOT	= USER_APP_EV_BASE + 3,
				RESUME		= USER_APP_EV_BASE + 4,
				TICK		= USER_APP_EV_BASE + 5;
			TetrisApp(int w, int h);
			// overloaded event handler
			virtual bool handle(SDL_Event& ev);
			
			static const std::string fontname;
		};
	}
}

#endif

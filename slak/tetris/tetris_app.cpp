#include "boost/filesystem/convenience.hpp" 
namespace fs = boost::filesystem;

#include <cstdlib>
#include <string>
#include <SDL.h>
#include "tetris_app.h"
#include "slak/glui/rgbpic.h"

using namespace slak::tetris;
using namespace slak::glui;

const std::string TetrisApp::fontname = "media/fonts/TouristTrap.ttf";

TetrisApp::TetrisApp(int w,int h)
	: tetris(), soundm(), game_screen(&tetris), 
	hiscore_screen(&tetris.hi_scores, GOTO_ROOT,fontname),
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

	// initialize the game logic
	tetris.hi_scores.load(conf_dir / "hiscores");
	tetris.setSoundManager(&soundm);
	tetris.newGame();

	// we use generic hiscore_screen, but add a tetris specific 
	// background to it
	hiscore_screen.overlays
	  .insert(hiscore_screen.overlays.begin(), 
		  new slak::glui::RGBPic("media/bitmaps/tetris-hiscore.bmp"));

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


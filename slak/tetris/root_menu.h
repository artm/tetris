#ifndef slak_tetris_root_menu_h
#define slak_tetris_root_menu_h

#include <vector>
#include "slak/glui/screen.h"
#include "slak/glui/label.h"

namespace slak {
	namespace tetris {
		struct RootMenu : slak::glui::Screen {
		        // compose the menu screen
			RootMenu();
			// overloads of Screen's methods
			virtual bool handle(SDL_Event& ev);
			virtual void draw();
		};
	}
}

#endif

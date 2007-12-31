#ifndef slak_glui_screen_h
#define slak_glui_screen_h

#include <vector>
#include "overlay.h"
#include "drawmode.h"

namespace slak {
	namespace glui {
		struct Screen {
		  // Screen events base
			static const int SCREEN_EV_BASE = 1000;
		  // Rendering request event ID
			static const int DRAW_FRAME = SCREEN_EV_BASE;

		  // a list of overlays - things drawn on top of the screen
			std::vector<Overlay*> overlays;
		  // a list of draw modes (OpenGL state changing objects)
			std::vector<DrawMode*> modes;

		  // handle event
			virtual bool handle(SDL_Event& ev); 
		  // draw yourself
			virtual void draw();
		};

	}
}

#endif

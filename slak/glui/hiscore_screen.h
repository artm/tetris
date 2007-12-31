#ifndef slak_glui_hiscore_screen_h
#define slak_glui_hiscore_screen_h

#include "hiscore_table.h"
#include "screen.h"
#include "label.h"
#include "pulse.h"

namespace slak {
	namespace glui {
		struct HiScoreScreen : Screen {
			static const int cursor_delay = 400; // ms

			HiScoreTable * table;
			unsigned int leave_message;
			Pulse cursor_pulse;

			std::vector<Label*> nameLabels, scoreLabels;

			HiScoreScreen(HiScoreTable * t, unsigned int leave_message, std::string fontname); 
			virtual bool handle(SDL_Event& ev); 
			virtual void draw();
		};
	}
}

#endif


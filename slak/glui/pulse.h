#ifndef slak_glui_pulse_h
#define slak_glui_pulse_h

#include <SDL.h>


namespace slak {
	namespace glui {

		struct Pulse {
		protected:
			bool state;
		public:
			int delay;
			Uint32 stopwatch;

			Pulse(int delay, bool initial_state = false);
			bool getState();
		};
	}
}


#endif

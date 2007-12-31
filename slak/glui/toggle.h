#ifndef slak_glui_toggle_h
#define slak_glui_toggle_h

#include "overlay.h"

namespace slak {
	namespace glui {
		struct Toggle : Overlay {
			bool on;
			Overlay * kid;
			Toggle(): on(true), kid(NULL) {}
			virtual void draw() { if (on && kid) kid->draw(); }
		};
	}
}

#endif

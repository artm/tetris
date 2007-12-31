#ifndef slak_glui_orthomode_h
#define slak_glui_orthomode_h

#include "drawmode.h"

namespace slak {
	namespace glui {
		struct OrthoMode : DrawMode {
			virtual void drawPre();
			virtual void drawPost();
		};
	}
}

#endif


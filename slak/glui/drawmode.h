#ifndef slak_glui_drawmode_h
#define slak_glui_drawmode_h

namespace slak {
	namespace glui {
		struct DrawMode {
			virtual void drawPre() = 0;
			virtual void drawPost() = 0;
		};
	}
}

#endif


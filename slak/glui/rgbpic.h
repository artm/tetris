#ifndef slak_glui_rgbpic_h
#define slak_glui_rgbpic_h

#include <string>
#include "overlay.h"

struct SDL_Surface;

namespace slak {
	namespace glui {
		struct RGBPic : Overlay {
			SDL_Surface * pic;
			int x,y;
			unsigned int texID;
			bool inited_gfx, use_texture;
			int texw, texh;
			float maxs,maxt;

			RGBPic(std::string fname);
			virtual void draw();
		};
		void sdl2glPixelParams(SDL_PixelFormat * sdlfmt, 
				       unsigned int& format, 
				       unsigned int& type);
	}
}

#endif

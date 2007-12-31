#ifndef slak_glui_label_h
#define slak_glui_label_h

#include <string>
#include "overlay.h"

struct _TTF_Font;
typedef struct _TTF_Font TTF_Font;
struct SDL_Surface;

namespace slak {
	namespace glui {

		struct Label : Overlay {
			enum {
				ALIGN_LEFT,
				ALIGN_RIGHT,
				ALIGN_CENTER,
			};

			TTF_Font * fnt;
			SDL_Surface * bitmap;
			std::string text;
			int x,y;
			int align;

			Label(std::string fontname, int fontsize, int fontstyle=0, int align = ALIGN_LEFT);
			~Label();
			void setText(std::string newtext);
			virtual void draw();
		};

	}
}

#endif

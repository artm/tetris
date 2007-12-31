/*
 * slak-games: simple SDL+OpenGL based games
 * Copyright (C) 2006-2008 Artem Baguinski <femistofel@gmail.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301, USA.
 */

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

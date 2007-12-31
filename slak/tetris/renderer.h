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

#ifndef slak_tetris_renderer_h
#define slak_tetris_renderer_h

#include <string>
#include "tetrad.h"
#include "slak/glui/label.h"
#include "slak/glui/overlay.h"

namespace slak {
	namespace tetris {

		struct Game;

		// the overlay that renders the tetris field and
		// other game related elements (score, level, ...)
		struct Renderer : slak::glui::Overlay {
		        // the block size is variable
			static const int block_size = 32;

			// texture objects for square colours
			unsigned int texture_ids[N_STATES];
			// position of the field on screen
			int field_x0;
			int field_x1;
			int field_y0;
			int field_y1;

			// the game logic
			Game * g;
			// text overlays
			slak::glui::Label score_lbl, level_lbl;

			Renderer(Game * g);
			~Renderer();

			// load textures from files
			void loadTextures();

			// the overloaded draw...
			void draw();
			// ... and its subprocedures:
			// field borders
			void drawField();
			// squares of each colour are drawn by a separate pass
			// ... i did overoptimize this too much, habit
			void drawBlocksPass(square_state st,
					   float x0 = -1, float y0 = -1);
			// calls all the passes in a loop
			void drawBlocks();
			// draw score label
			void drawScore();
			// draw level label
			void drawLevel();
			// draw the hint
			void drawNextTetrad();
			// find pixel coordinates from Row x Column.
			// if not specified x0 and y0 default to the
			// field corner
			void blockXY(int i, int j, float& x, float& y,
				    float x0 = -1, float y0 = -1);
		};

	}
}

#endif

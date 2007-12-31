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

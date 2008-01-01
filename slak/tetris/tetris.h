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

#ifndef slak_tetris_h
#define slak_tetris_h

#include "slak/glui/soundm.h"
#include "slak/glui/hiscore_table.h"

#include "field.h"

namespace slak {

	namespace tetris {

	  // constants for state machine
		enum game_state {
			INIT_STATE,
			NORMAL_STATE,
			FAST_FALL_STATE,
			STROBE_FX_STATE,
			GAME_OVER_STATE,
		};

		struct Game {
		  // the game is driven by ticks - events are handled
		  // and scheduled with a minimum granularity of a tick
		  // the size of a tick is chosen so I could match score /
		  // speed relationships of the classical arcade
		  // implementation
			static const int tick_delay = 17; // ~60Hz

		  // score bonus depending of number of cleared lines
		        static const int score_for_clear[];

		  // various time parameters (in ticks, see above)
		  // current fall delay
  		        int fall_ticks;
		  // what to set fall_ticks to depending on state
			int ticks_per_normal_fall;
			int ticks_per_fast_fall;
		      // blinking effect delay
			int ticks_per_strobe_fx;

		  // game play stats. number of cleared lines is used
		  // to set level.
			int score, level, cleared;

		  // state machine state
			game_state state;

		  // playing field
			Field field;
		  // next tetris block to fall (to display a hint)
			Tetrad nextTetrad;

		  // obvious...
                        slak::glui::SoundManager * sm;
		  // hi scores (data structure)
			slak::glui::HiScoreTable hi_scores;

		  // when false block can't be fast-dropped, e.g.
		  // during the drop
			bool can_fast_fall;

		  // initialization
			Game();

		  // start a new game (reuses this object)
			void newGame();
		  // selects one of the following three depending on
		  // the current state. this function is called every
		  // tick.
			void tick();
			void normalTick();
			void fastFallTick();
			void strobeTick();

		  // inster next block into the field
		        void dropNextTetrad();
		  // enter particular game state
			void enter(game_state st);
		  // set current level and calculate speed from it
			void setLevel(int i);

		  // move the block. whenever the block has moved it
		  // is allowed to be fast-dropped again.
			void right() {
				field.moveFalling(1,0);
				can_fast_fall = true;
			}
			void left() {
				field.moveFalling(-1,0);
				can_fast_fall = true;
			}
			void rotate() {
				field.rotateFalling();
				can_fast_fall = true;
			}

			void setSoundManager(slak::glui::SoundManager*sm) {
				this->sm = sm;
			}
		};
	}
}

#endif

#ifndef slak_tetris_field_h
#define slak_tetris_field_h

#include "tetrad.h" 

namespace slak {

	namespace tetris {
	
		struct Field : public Tetrad {
			Tetrad falling;
			int x,y;

			Field(int w, int h);

			// clears the field and current tetrad
			virtual void clear();

			// attempt to insert a new tetrad into the 
			// field. returns true if it was possible.
			bool drop(const Tetrad& f);
			// render the current falling tetrad onto the
			// field (after it has fallen). this has nothing
			// to do with rendering on screen (which is called
			// drawing in the code).
			void renderFalling();
			// attempt to move the falling block, return true 
			// if it was possible.
			bool moveFalling(int dx, int dy);
			// attempt to rotate the block, return true if it 
			// was possible. 
			bool rotateFalling();

			// return the "state" of the square (which is a 
			// colour of the block or none for empty). this 
			// overrides tetrad's method to account for the 
			// falling tetrad on top of the field
			virtual square_state  sq(int i, int j) const;
		};

	}
}

#endif


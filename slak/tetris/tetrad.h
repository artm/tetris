#ifndef slak_tetris_tetrad_h
#define slak_tetris_tetrad_h

#include <cstddef>

namespace slak {

	namespace tetris {

	  // classical shapes (names from DOS tetris)
		enum shape {
			RANDOM_SHAPE = -1,
			O = 0,
			I,
			L,
			J,
			Z,
			S,
			T,

			N_SHAPES,
		};

	  // possible square states - empty or coloured
	  // colours based on DOS tetris
		enum square_state {
			EMPTY = 0,
			RED,
			BLACK,
			MAGENTA,
			BLUE,
			GREEN,
			BROWN,
			CYAN,

			N_STATES,
		};

		// the tetris block mask
		struct Tetrad {
		  // mask size
			int width, height;
		  // what is considered center? 
		  // this is used to place rotated block
		  // in the field 
			int cx,cy;
		  // actual mask
			square_state * mask;

		  // empty tetrad constructor
		        Tetrad(); 
		  // initialize the tetrad and mask array
			Tetrad(int w, int h, int cx=-1, int cy=-1);
		  // copy constructor
			Tetrad(const Tetrad& other);
			Tetrad& operator=(const Tetrad& other);
			virtual ~Tetrad();
		  // clear (overriden by the field)
			virtual void clear();
		  // square colour
			virtual square_state& sq(int i, int j);
		  // this one is overriden by the field
			virtual square_state  sq(int i, int j) const;

		  // rotate the tetrad
			Tetrad rotate() const;
		  // collision detection
			bool collides(int x, int y,const Tetrad& other);
		  // comparison
			bool operator==(const Tetrad& other) const;
			bool operator!=(const Tetrad& other) const;
		  // is tetrad empty?
			bool empty() const { return mask==NULL; }
		  // is the line j complete? 
			bool lineComplete(int j) const;
		  // delete a line
			void delLine(int j);
		  // .. or all complete lines
			int delAllComplete();
		  // count complete lines (for score)
			int countComplete();

		  // tetrad factory
		  // non-random shape creation was used by the test suite
			static Tetrad make(shape s = RANDOM_SHAPE, 
					   int n_rot = -1);
		};

	}
}

#endif

#ifndef slak_soundm_h
#define slak_soundm_h

#include <string>
#include <map>
#include <SDL_mixer.h>

namespace slak {
	namespace tetris {

	  // SDL_mixer based sound manager
		struct SoundManager {
		  // tagged samples map
			std::map<std::string, Mix_Chunk*> samples;

			SoundManager();
			~SoundManager();
		  // play sample by tag (channel will be autoallocated)
			void play(std::string tag);
		};

	}
}

#endif

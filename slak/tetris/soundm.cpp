#include <SDL_mixer.h>
#include <iostream>

#include "soundm.h"

using namespace slak::tetris;

SoundManager::SoundManager()
{
  // init audio device
	if (Mix_OpenAudio(44100, AUDIO_S16, 1, 4096) < 0) {
		std::cerr << "SDL_mixer error: " << SDL_GetError() << "\n";
		exit(1);
	}

  // load samples, this is tetris specific, the class is intended to be 
  // made generic and initialized from outside later.
	char* map[][2] = {
		{"click", "media/sound/tetris-click.wav"},
		{"woosh", "media/sound/tetris-woosh.wav"},
		{"snap",  "media/sound/tetris-snap.wav"},
		{"tada",  "media/sound/tetris-tada.wav"},
	};
	int n = sizeof(map)/sizeof(char*[2]);

	for(int i=0; i<n; i++) {
		Mix_Chunk* sample = Mix_LoadWAV(map[i][1]);
		if (sample)
			samples[map[i][0]] = sample;
		else {
			std::cerr << "Can't open sample " <<
				map[i][1] << ":" <<
				SDL_GetError() << "\n";
		}
	}
}

void SoundManager::play(std::string tag)
{
  // don't crash when called with non existent tag
	if(samples.find(tag) != samples.end()) {
		Mix_PlayChannel(-1,samples[tag],0);
	} else 
		std::cerr << "Unknown sound tag: " << tag << "\n";
}

SoundManager::~SoundManager()
{
	Mix_CloseAudio();
}

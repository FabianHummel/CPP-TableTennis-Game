#include "soundmanager.h"
#include <SDL_mixer.h>

namespace SoundManager
{
	std::unordered_map<const char *, Mix_Chunk *> sounds = {};

	void addSound(const char *path, const char *name)
	{
		printf("Loading Sound %s\n", path);
		Mix_Chunk *sound = Mix_LoadWAV(path);
		if (!sound)
		{
			printf("Error loading sound!\n"
			       "SDL_mixer_Error: %s\n",
			       Mix_GetError());
			exit(EXIT_FAILURE);
		}

		sounds[name] = sound;
	}

	void playSound(const char *name, int volume)
	{
		auto sound = sounds[name];
		sound->volume = volume / 128.0f * 100.0f;
		Mix_PlayChannel(-1, sound, 0);
	}

	void playSound(const char *name)
	{
		playSound(name, MIX_MAX_VOLUME);
	}

	void playSounds(const std::vector<const char *> &names, int volume)
	{
		for (auto name : names)
		{
			playSound(name, volume);
		}
	}

	void playSounds(const std::vector<const char *> &names)
	{
		playSounds(names, MIX_MAX_VOLUME);
	}

	void playRndSound(const std::vector<const char *> &names, int volume)
	{
		int rnd = rand() % names.size();
		playSound(names[rnd], volume);
	}

	void playRndSound(const std::vector<const char *> &names)
	{
		playRndSound(names, MIX_MAX_VOLUME);
	}
}
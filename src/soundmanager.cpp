#include "soundmanager.h"
#include <SDL3_mixer/SDL_mixer.h>

namespace SoundManager
{
	SDL_AudioSpec spec = { .format = SDL_AUDIO_S16, .channels = 2, .freq = 44100 };
	MIX_Mixer *mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec);
	std::unordered_map<const char *, MIX_Audio *> sounds = {};

	void addSound(const char *path, const char *name)
	{
		printf("Loading Sound %s\n", path);
		MIX_Audio *sound = MIX_LoadAudio(nullptr, path, false);
		if (!sound)
		{
			printf("Error loading sound!\nSDL Error: %s\n", SDL_GetError());
			exit(EXIT_FAILURE);
		}

		sounds[name] = sound;
	}

	void playSound(const char *name, float volume)
	{
		auto sound = sounds[name];
		MIX_SetMixerGain(mixer, volume);
		MIX_PlayAudio(mixer, sound);
	}

	void playSound(const char *name)
	{
		playSound(name, 1.0f);
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
		playSounds(names, 1.0);
	}

	void playRndSound(const std::vector<const char *> &names, int volume)
	{
		int rnd = rand() % names.size();
		playSound(names[rnd], volume);
	}

	void playRndSound(const std::vector<const char *> &names)
	{
		playRndSound(names, 1.0);
	}
}
//
// Created by Fabian Hummel on 17.06.22.
//

#pragma once

#include <SDL3_mixer/SDL_mixer.h>
#include <unordered_map>
#include <vector>

namespace SoundManager
{
	extern MIX_Mixer *mixer;
	extern std::unordered_map<const char *, MIX_Audio *> sounds;

	void addSound(const char *path, const char *name);
	void playSound(const char *name, int volume);
	void playSound(const char *name);

	void playSounds(const std::vector<const char *> &names, int volume);
	void playSounds(const std::vector<const char *> &names);

	void playRndSound(const std::vector<const char *> &names, int volume);
	void playRndSound(const std::vector<const char *> &names);
};
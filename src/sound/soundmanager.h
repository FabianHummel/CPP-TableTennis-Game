//
// Created by Fabian Hummel on 17.06.22.
//

#pragma once

#include <SDL_mixer.h>
#include <unordered_map>
#include <vector>

namespace SoundManager
{
	extern std::unordered_map<const char *, Mix_Chunk *> sounds;

	void addSound(const char *path, const char *name);
	void playSound(const char *name, int volume);
	void playSound(const char *name);

	void playSounds(const std::vector<const char *> &names, int volume);
	void playSounds(const std::vector<const char *> &names);

	void playRndSound(const std::vector<const char *> &names, int volume);
	void playRndSound(const std::vector<const char *> &names);
};
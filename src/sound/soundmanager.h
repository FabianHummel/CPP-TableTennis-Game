//
// Created by Fabian Hummel on 17.06.22.
//

#pragma once

#include <SDL_mixer.h>
#include <unordered_map>
#include <vector>

class SoundManager
{
  private:
	static std::unordered_map<const char *, Mix_Chunk *> sounds;

  public:
	static void addSound(const char *path, const char *name);
	static void playSound(const char *name, int volume);
	static void playSound(const char *name);

	static void playSounds(const std::vector<const char *> &names, int volume);
	static void playSounds(const std::vector<const char *> &names);

	static void playRndSound(const std::vector<const char *> &names, int volume);
	static void playRndSound(const std::vector<const char *> &names);
};
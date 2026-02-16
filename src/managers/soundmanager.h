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

    void add_sound(const char *path, const char *name);
    void play_sound(MIX_Track *track, const char *name, float gain);
    void play_sound_random(MIX_Track *track, const std::vector<const char *> &names, float gain);
    void play_sounds(MIX_Track *track, const std::vector<const char *> &names, float gain);
} // namespace SoundManager
#include "soundmanager.h"
#include <SDL3_mixer/SDL_mixer.h>

namespace SoundManager
{
    SDL_AudioSpec spec = {.format = SDL_AUDIO_S16, .channels = 2, .freq = 44100};
    MIX_Mixer *mixer = MIX_CreateMixerDevice(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &spec);
    std::unordered_map<const char *, MIX_Audio *> sounds = {};
}

void SoundManager::add_sound(const char *path, const char *name)
{
    printf("Loading Sound %s\n", path);
    MIX_Audio *sound = MIX_LoadAudio(mixer, path, false);
    if (!sound)
    {
        SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Error loading sound: %s\n", SDL_GetError());
        exit(EXIT_FAILURE);
    }

    sounds[name] = sound;
}

void SoundManager::play_sound(MIX_Track *track, const char *name, const float gain)
{
    MIX_SetTrackAudio(track, sounds[name]);
    MIX_SetTrackGain(track, gain);
    MIX_PlayTrack(track, 0);
}

void SoundManager::play_sound_random(MIX_Track *track, const std::vector<const char *> &names, const float gain)
{
    const int rnd = SDL_rand((int)names.size());
    play_sound(track, names[rnd], gain);
}

void SoundManager::play_sounds(MIX_Track *track, const std::vector<const char *> &names, const float gain)
{
    for (const auto name : names)
    {
        play_sound(track, name, gain);
    }
}
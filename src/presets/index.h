#pragma once

#include "../components/componentsystem.h"
#include "SDL3/SDL_render.h"
#include <functional>

namespace Presets
{
    extern Preset button(SDL_Renderer* renderer, const char* text, int pt_size, const std::function<void()>& on_click);
    extern Preset text_input(SDL_Renderer* renderer, char* text, size_t max_length, const char* placeholder, int pt_size);
    extern Preset readonly_text_input(SDL_Renderer* renderer, const char* text, int pt_size);
    extern Preset error(SDL_Renderer* renderer, const char* text, int pt_size);
}
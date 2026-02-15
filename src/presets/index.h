#pragma once

#include <functional>
#include "../componentsystem.h"
#include "SDL3/SDL_render.h"

namespace Presets
{
	extern Preset button(SDL_Renderer *renderer, const char *text, int ptSize, const std::function<void()> &onClick);
	extern Preset textinput(SDL_Renderer *renderer, char* text, size_t max_length, const char* placeholder, int ptSize);
	extern Preset readonlyTextinput(SDL_Renderer *renderer, const char* text, int ptSize);
	extern Preset error(SDL_Renderer *renderer, const char* text, int ptSize);
}

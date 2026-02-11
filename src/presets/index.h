#pragma once

#include <functional>
#include "../componentsystem.h"
#include "SDL3/SDL_render.h"

namespace Presets
{
	extern Preset button(SDL_Renderer *renderer, const char *text, int ptSize, const std::function<void()> &onClick);
	extern Preset textinput(SDL_Renderer *renderer, char* text, int ptSize, size_t max_length);
}

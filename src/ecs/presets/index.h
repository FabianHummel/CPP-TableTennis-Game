#pragma once

#include "../ecs.h"
#include "../components/index.h"

namespace Presets
{
	extern Preset button(SDL_Renderer *renderer, const char *text, const std::function<void()> &onClick);
	extern Preset textinput(SDL_Renderer *renderer, char* text, size_t max_length);
}
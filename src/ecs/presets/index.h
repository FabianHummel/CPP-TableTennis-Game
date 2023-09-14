#pragma once

#include "../ecs.h"
#include "../components/index.h"

namespace Presets
{
	extern Preset button(SDL_Renderer *renderer, const std::function<void()> &onClick);
}
#pragma once

#include <SDL3/SDL_render.h>

#include "transform.h"

class Debugger : public Component
{
  private:
	Transform *transform{};
	SDL_Renderer *renderer;
	bool extendedDebugInfo;

  public:
	explicit Debugger(SDL_Renderer *renderer);
	explicit Debugger(SDL_Renderer *renderer, bool extendedDebugInfo);
	void onInitialize() override;
	void onUpdate(double deltaTime) override;
	void onEvent(const SDL_Event *event) override;
};

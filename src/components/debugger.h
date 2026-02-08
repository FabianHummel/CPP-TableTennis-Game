#pragma once

#include <SDL_render.h>

#include "transform.h"

class Debugger : public Component
{
  private:
	Transform *transform{};
	SDL_Renderer *renderer;

  public:
	explicit Debugger(SDL_Renderer *renderer);
	void onInitialize() override;
	void onUpdate(double deltaTime) override;
	void onEvent(SDL_Event event) override;
};

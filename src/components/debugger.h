#pragma once

#include "../ecs/ecs.h"
#include <SDL.h>
#include <SDL_render.h>

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

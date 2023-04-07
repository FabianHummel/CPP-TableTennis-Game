#pragma once

#include "component.h"
#include "transform.h"
#include <SDL.h>
#include <SDL_render.h>

class Debugger : public Component
{
  private:
	Transform *transform;
	SDL_Renderer *renderer;

  public:
	Debugger(SDL_Renderer *renderer);
	void onInitialize() override;
	void onUpdate(double deltaTime) override;
	void onEvent(SDL_Event event) override;
};

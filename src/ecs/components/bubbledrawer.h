#pragma once

#include "../ecs.h"
#include <SDL.h>
#include <SDL_render.h>

class BubbleDrawer : public Component
{
  private:
	SDL_Renderer *renderer;
	Transform *transform;
	SDL_Texture *texture;
	double time;

	SDL_Color fromColor = {181, 193, 255, 255};
	SDL_Color toColor = {203, 211, 235, 255};

	constexpr static double ROTATION = 3.5;
	constexpr static double SPEED = 20;

  public:
	BubbleDrawer(SDL_Renderer *renderer);
	void onInitialize() override;
	void onUpdate(double deltaTime) override;
};

#pragma once

#include "../componentsystem.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

class BubbleDrawer : public Component
{
  private:
	Transform *transform{nullptr};
	SDL_Renderer *renderer;
	SDL_Texture *texture;
	double time{0};

	SDL_Color fromColor = {181, 193, 255, 255};
	SDL_Color toColor = {203, 211, 235, 255};

	constexpr static double ROTATION = 3.5;
	constexpr static double SPEED = 20;

  public:
	BubbleDrawer(SDL_Renderer *renderer);
	void onInitialize() override;
	void onUpdate(double deltaTime) override;
};

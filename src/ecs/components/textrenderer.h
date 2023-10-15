#pragma once

#include "../ecs.h"
#include "../../fontmanager.h"
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_pixels.h>
#include <SDL_render.h>
#include <SDL_ttf.h>

class TextRenderer : public Component
{
  private:
	SDL_Texture *texture{};
	SDL_Renderer *renderer;
	Transform *transform{};
	const char *text;
	SDL_Color color{};
	TTF_Font *font;

	void updateTexture();

  public:
	bool visible = true;
	int ptSize = 42;

	TextRenderer(SDL_Renderer *renderer, const char *text, int ptSize, SDL_Color color);

	void onInitialize() override;
	void onUpdate(double deltaTime) override;

	void setText(const char *text);
	void setColor(SDL_Color color);
};

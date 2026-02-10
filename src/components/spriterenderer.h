#pragma once

#include "../componentsystem.h"

class SpriteRenderer : public Component
{
  private:
	SDL_Texture *texture{};
	SDL_Renderer *renderer;
	Transform *transform{};
	const char *img;
	SDL_FRect *srcrect = nullptr;

  public:
	bool visible = true;

	SpriteRenderer(const char *img, SDL_Renderer *renderer);

	void onInitialize() override;
	void onStart() override;
	void onUpdate(double deltaTime) override;
	void onDelete() override;

	void setSrcrect(SDL_FRect rect);
	void setImage(const char *img);
};

#pragma once

#include "../componentsystem.h"

class SpriteRenderer : public Component
{
  private:
	SDL_Texture *texture{};
	SDL_Renderer *renderer;
	Transform *transform{};
	const char *img;
	SDL_Rect *srcrect = nullptr;

  public:
	bool visible = true;

	SpriteRenderer(const char *img, SDL_Renderer *renderer);

	void onInitialize() override;
	void onStart() override;
	void onUpdate(double deltaTime) override;
	void onDelete() override;

	void setSrcrect(SDL_Rect rect);
	void setImage(const char *img);
};

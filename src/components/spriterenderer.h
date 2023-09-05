#pragma once

#include "../ecs/ecs.h"
#include <SDL_events.h>
#include <SDL_render.h>

class SpriteRenderer : public Component
{
  private:
	SDL_Texture *texture{};
	SDL_Renderer *renderer;
	Transform *transform{};
	const char *img;
	bool visible = true;
	int opacity = 255;
	SDL_Rect *srcrect = nullptr;

  public:
	SpriteRenderer(const char *img, SDL_Renderer *renderer);

	void onInitialize() override;
	void onStart() override;
	void onUpdate(double deltaTime) override;

	void setImage(const char *img);
	void setOpacity(int v);
	void setSrcrect(SDL_Rect rect);

	void setVisible(bool v);
	bool isVisible() const;
};

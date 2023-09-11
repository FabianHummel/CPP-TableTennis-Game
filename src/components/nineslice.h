#pragma once

#include "../ecs/ecs.h"

struct Positions
{
	int top, right, bottom, left;
};

class NineSlice : public Component
{
  private:
	SDL_Texture *texture{};
	SDL_Renderer *renderer;
	Transform *transform{};
	Positions positions{};
	const char *img;
	bool visible = true;
	int opacity = 255;

  public:
	NineSlice(const char *img, Positions positions, SDL_Renderer *renderer);

	void onInitialize() override;
	void onStart() override;
	void onUpdate(double deltaTime) override;
	void onDelete() override;

	void setImage(const char *img, Positions positions);
	void setOpacity(int v);

	void setVisible(bool v);
	bool isVisible() const;
};
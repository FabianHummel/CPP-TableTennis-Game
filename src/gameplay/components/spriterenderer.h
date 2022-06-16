#pragma once

#include "../component.h"
#include "transform.h"
#include "../../entity/entity.h"
#include <SDL_render.h>

class SpriteRenderer : public Component {
private:
	SDL_Texture *texture;
	SDL_Renderer *renderer;
    const char *img;

	bool visible = true;

	Transform *transform;
	int opacity = 255;

	SDL_Rect *srcrect = nullptr;

public:
	SpriteRenderer(const char *img, SDL_Renderer *renderer);

    void onInitialize() override;
    void onStart() override;
    void onUpdate() override;

	void setImage(const char *img);
	void setOpacity(int v);
	void setSrcrect(SDL_Rect rect);

	void setVisible(bool v);
	bool isVisible() const;
};

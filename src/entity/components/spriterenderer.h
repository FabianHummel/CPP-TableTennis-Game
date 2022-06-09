#pragma once

#include "../component.h"
#include <SDL_render.h>

class SpriteRenderer : public Component {
private:
	SDL_Texture *texture;
	SDL_Renderer *renderer;
    const char *img;
    int x, y, w, h;

public:
	SpriteRenderer(const char *img, SDL_Renderer *renderer, int x, int y, int w, int h);

    void onInitialize() override;
    void onStart() override;
    void onUpdate() override;
};

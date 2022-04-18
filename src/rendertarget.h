//
// Created by Fabian Hummel on 18.04.22.
//

#pragma once

#include "SDL.h"
#include "SDL_image.h"

class RenderTarget {
private:
    SDL_Texture *texture;
    int *posX;
    int *posY;
    int width;
    int height;

public:
    RenderTarget(SDL_Texture *texture, int *posX, int *posY, int width, int height);
    ~RenderTarget();

    void render(SDL_Renderer *renderer);
};
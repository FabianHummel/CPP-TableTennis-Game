//
// Created by Fabian Hummel on 18.04.22.
//

#include "rendertarget.h"
#include <iostream>

RenderTarget::RenderTarget(SDL_Texture *texture, int *posX, int *posY, int width, int height) :
    texture(texture), posX(posX), posY(posY), width(width), height(height) {
}

RenderTarget::~RenderTarget() {

}

void RenderTarget::render(SDL_Renderer *renderer) {
    SDL_Rect rect;
    if (!posX)
        rect.x = 0;
    else
        rect.x = *posX;

    if (!posY)
        rect.y = 0;
    else
        rect.y = *posY;

    rect.w = width;
    rect.h = height;

    SDL_RenderCopy(renderer, texture, nullptr, &rect);
}
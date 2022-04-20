//
// Created by Fabian Hummel on 16.04.22.
//

#pragma once

#include "vector"
#include "../entitybase.h"
#include "rendertarget.h"

class RenderWindow {
public:
    SDL_Window *window;
    SDL_Renderer *renderer;

    RenderWindow(int width, int height, const char *title);
    ~RenderWindow();

    void drawBG(SDL_Color color);
    void clear();
    void destroy();

    RenderTarget *createTarget(const char *file, int *posX, int *posY, int width, int height) const;
    RenderTarget *createTarget(const char *file, EntityBase *entity, int width, int height) const;
};
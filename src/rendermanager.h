//
// Created by Fabian Hummel on 17.04.22.
//

#pragma once

#include "vector"
#include "rendertarget.h"

class RenderManager {
private:
    SDL_Renderer *renderer;
    std::vector<RenderTarget> targets;

public:
    explicit RenderManager(SDL_Renderer *renderer);
    ~RenderManager();

    void move(int oldIndex, int newIndex);
    void addTarget(RenderTarget *target);
    void renderAll();
};
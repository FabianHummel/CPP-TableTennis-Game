//
// Created by Fabian Hummel on 17.04.22.
//

#pragma once

#include "vector"
#include "rendertarget.h"

class RenderManager {
private:
    static std::vector<RenderTarget*> targets;

public:
    static void move(int oldIndex, int newIndex);
    static void addTarget(RenderTarget *target);
    static void renderAll(SDL_Renderer *renderer);
	static int indexFromTarget(RenderTarget *target);
};
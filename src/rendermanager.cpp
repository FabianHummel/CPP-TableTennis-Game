//
// Created by Fabian Hummel on 17.04.22.
//

#include "rendermanager.h"

RenderManager::RenderManager(SDL_Renderer *renderer) {
    this->renderer = renderer;
}

RenderManager::~RenderManager() {

}

void RenderManager::move(int oldIndex, int newIndex) {
    if (oldIndex > newIndex)
        std::rotate(targets.rend() - oldIndex - 1, targets.rend() - oldIndex, targets.rend() - newIndex);
    else
        std::rotate(targets.begin() + oldIndex, targets.begin() + oldIndex + 1, targets.begin() + newIndex + 1);
}

void RenderManager::addTarget(RenderTarget *target) {
    targets.push_back(*target);
}

void RenderManager::renderAll() {
    for (auto target : targets) {
        target.render(
            renderer
        );
    }
}
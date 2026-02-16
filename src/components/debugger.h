#pragma once

#include <SDL3/SDL_render.h>

#include "transform.h"

class Debugger : public Component
{
  private:
    Transform *transform{};
    SDL_Renderer *renderer;
    bool extended_debug_info;

  public:
    explicit Debugger(SDL_Renderer *renderer);
    explicit Debugger(SDL_Renderer *renderer, bool extended_debug_info);

    void on_initialize() override;
    void on_update(double deltaTime) override;
};
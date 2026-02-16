#pragma once

#include "componentsystem.h"
#include <SDL3/SDL.h>
#include <SDL3/SDL_render.h>

class BubbleDrawer : public Component
{
  private:
    Transform *transform{nullptr};
    SDL_Renderer *renderer;
    SDL_Texture *texture;
    double time{0};

    constexpr static double ROTATION = 3.5;
    constexpr static double SPEED = 20;

  public:
    explicit BubbleDrawer(SDL_Renderer *renderer);
    void on_initialize() override;
    void on_update(double delta_time) override;
};
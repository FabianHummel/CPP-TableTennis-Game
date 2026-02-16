#pragma once

#include "SDL3/SDL_render.h"

class Pane
{
  protected:
    SDL_Renderer *renderer;

  public:
    explicit Pane(SDL_Renderer *renderer);
    virtual ~Pane();

    /**
     * @brief Called once when the game starts.
     */
    virtual void on_start() {};

    /**
     * @brief Called every frame.
     */
    virtual void on_gui(double delta_time) {};

    /**
     * @brief Called when an event fires.
     */
    virtual void on_event(const SDL_Event *event) {};
};
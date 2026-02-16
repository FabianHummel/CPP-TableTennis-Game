#pragma once

#include "../components/componentsystem.h"
#include "pane.h"

class GamePane : public Pane
{
  protected:
    Entity *table;
    Entity *net;
    Entity *shadow;
    Entity *ball;
    Entity *indicator;
    Entity *power_bar;
    Entity *power_box;
    Entity *prediction_segments;
    Entity *back_button;

    void back() const;

  public:
    explicit GamePane(SDL_Renderer *renderer);
    ~GamePane() override;

    void on_event(const SDL_Event *event) override;
};
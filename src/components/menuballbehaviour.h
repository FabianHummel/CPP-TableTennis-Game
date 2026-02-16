#pragma once

#include "componentsystem.h"

class MenuBallBehaviour : public Component
{
  private:
    double initial_position{0.0};

    constexpr static float SPEED = 5.0f;
    constexpr static int HEIGHT = 50;
    Transform *transform{};
    double time{};

  public:
    MenuBallBehaviour();

    void on_initialize() override;
    void on_update(double delta_time) override;
};
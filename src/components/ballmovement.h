#pragma once

#include <SDL3_mixer/SDL_mixer.h>

#include "../game/tableside.h"
#include "../utility/vector3.h"
#include "componentsystem.h"

class BallMovement : public Component
{
  private:
    Transform *transform = nullptr;

    double idle_time = 0;
    MIX_Track *ball_track = nullptr;

  public:
    BallMovement();

    constexpr static double IDLE_TIME = 1.0;
    constexpr static double GRAVITY = 0.2;
    constexpr static double FRICTION = 5.0;

    bool fellOff = false;
    bool idle = false;
    Vector3 velocity = {0.0f, 0.0f, 0.0f};

    void on_initialize() override;
    void on_start() override;
    void on_update(double delta_time) override;

    void apply_gravity(double delta_time);
    void apply_friction(double delta_time);
    void apply_velocity(double delta_time) const;
    void apply_z_index() const;

    void check_ground();
    void check_net(double delta_time);
    void check_idle(double delta_time);
    void check_fell_off() const;

    TableSideX get_side_x() const;
    TableSideY get_side_y() const;
};
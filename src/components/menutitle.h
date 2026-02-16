#pragma once

#include "componentsystem.h"

class MenuTitle : public Component
{
private:
    constexpr static float SPEED = 1.0f;
    Transform* transform{nullptr};
    double initial_position{0};
    double time{0};

public:
    MenuTitle();
    MenuTitle(double time_offset);

    void on_initialize() override;
    void on_update(double delta_time) override;
};
#pragma once

#include "componentsystem.h"

class ShadowTransformer : public Component
{
private:
    Transform* ball{};
    Transform* transform{};
    Entity* target;

public:
    explicit ShadowTransformer(Entity* shadow);

    void on_initialize() override;
    void on_update(double delta_time) override;
};
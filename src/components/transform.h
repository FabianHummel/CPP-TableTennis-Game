#pragma once

#include "../utility/vector2.h"
#include "../utility/vector3.h"
#include "componentsystem.h"
#include <SDL3/SDL_rect.h>

class Transform : public Component
{
public:
    Transform* animation{nullptr};
    Vector3 position = {0, 0, 0};
    Vector2 scale = {0, 0};
    float rotation = 0.0f;
    int z_index = 0;
    SDL_FPoint anchor = {0, 0};

    Transform();

    void on_delete() override;

    Vector3 get_calculated_pos() const;
    Vector2 get_calculated_scale() const;
    float get_calculated_rotation() const;
    int get_calculated_z_index() const;

    Entity* apply(const Vector3& pos, const Vector2& scl, const SDL_FPoint& anchor, float rot, int z_index);

    bool in_table_bounds() const;
    bool in_transform_bounds(float target_x, float target_y) const;

    SDL_FRect get_calculated_rect() const;
};
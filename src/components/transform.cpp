#include "transform.h"
#include <SDL3/SDL_rect.h>

Transform::Transform()
{
    this->name = "Transform";
}

void Transform::on_delete()
{
    delete animation;
}

Vector3 Transform::get_calculated_pos() const
{
    Vector3 pos = position;
    if (parent && parent->parent)
        pos += parent->parent->transform->get_calculated_pos();
    if (animation)
        pos += animation->get_calculated_pos();
    return pos;
}

Vector2 Transform::get_calculated_scale() const
{
    Vector2 scl = scale;
    if (animation)
        scl += animation->get_calculated_scale();
    return scl;
}

float Transform::get_calculated_rotation() const
{
    float rot = rotation;
    if (parent && parent->parent)
        rot += parent->parent->transform->get_calculated_rotation();
    if (animation)
        rot += animation->get_calculated_rotation();
    return rot;
}

int Transform::get_calculated_z_index() const
{
    int i = z_index;
    if (parent && parent->parent)
        i += parent->parent->transform->get_calculated_z_index();
    if (animation)
        i += animation->get_calculated_z_index();
    return i;
}

Entity *Transform::apply(const Vector3 &pos, const Vector2 &scl, const SDL_FPoint &anchor, const float rot,
                         const int z_index)
{
    this->position = pos;
    this->scale = scl;
    this->anchor = anchor;
    this->rotation = rot;
    this->z_index = z_index;
    return parent;
}

bool Transform::in_table_bounds() const
{
    const Vector3 pos = get_calculated_pos();
    return pos.x > 35 && pos.x < 665 && pos.z > 72 && pos.z < 938;
}

bool Transform::in_transform_bounds(const float target_x, const float target_y) const
{
    const auto [x, y, w, h] = get_calculated_rect();
    return target_x >= x && target_x <= x + w && target_y >= y && target_y <= y + h;
}

SDL_FRect Transform::get_calculated_rect() const
{
    const Vector3 pos = get_calculated_pos();
    const Vector2 scl = get_calculated_scale();

    SDL_FRect ret;
    ret.x = (float)(pos.x - scl.x * anchor.x);
    ret.y = (float)(pos.z - scl.y * anchor.y - pos.y);
    ret.w = (float)scl.x;
    ret.h = (float)scl.y;
    return ret;
}
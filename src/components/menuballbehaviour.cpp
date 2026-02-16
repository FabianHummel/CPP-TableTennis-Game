#include "menuballbehaviour.h"
#include <cmath>

MenuBallBehaviour::MenuBallBehaviour()
{
    this->name = "Menu Ball Behaviour";
}

void MenuBallBehaviour::on_initialize()
{
    this->transform = this->parent->transform;
    this->initial_position = transform->position.z;
}

double height(const double x)
{
    return (x - 2) * (x - 2) + 4;
}

void MenuBallBehaviour::on_update(const double delta_time)
{
    time += delta_time;
    this->transform->position.z = initial_position + HEIGHT * height(fmod(time * SPEED, 4));
}
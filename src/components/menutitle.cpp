#include "menutitle.h"

MenuTitle::MenuTitle() : MenuTitle(0.0)
{
}

MenuTitle::MenuTitle(const double time_offset)
{
    this->name = "Menu Title";
    this->time = time_offset;
}

void MenuTitle::on_initialize()
{
    transform = parent->transform;
    initial_position = transform->position.z;
}

void MenuTitle::on_update(const double delta_time)
{
    time += delta_time;
    transform->position.z = initial_position + 15 * sin(time * SPEED);
}
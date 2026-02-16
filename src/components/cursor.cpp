//
// Created by Fabian Hummel on 08.02.26.
//

#include "cursor.h"

#include "../managers/fontmanager.h"

Cursor::Cursor(const int ptSize)
{
    this->name = "Cursor";
    this->pt_size = ptSize;
    this->time = 0;
}

void Cursor::on_initialize()
{
    this->text_input = parent->parent->get_component<TextInput>();
    this->sprite_renderer = parent->get_component<SpriteRenderer>();
    this->transform = parent->transform;
}

void Cursor::on_update(const double deltaTime)
{
    time = std::fmod(time + deltaTime, 1);

    this->sprite_renderer->visible = text_input->is_focused && time < 0.5;

    int w;
    TTF_SetFontSize(FontManager::main, pt_size);
    TTF_GetStringSize(FontManager::main, this->text_input->text, 0, &w, nullptr);
    transform->position.x = w - parent->parent->transform->scale.x / 2.0 + 35;
}
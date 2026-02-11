//
// Created by Fabian Hummel on 08.02.26.
//

#include "cursor.h"

#include "../fontmanager.h"

Cursor::Cursor(int ptSize)
{
    this->name = "Cursor";
    this->ptSize = ptSize;
    this->time = 0;
}

void Cursor::onInitialize()
{
    this->textInput = parent->parent->getComponent<TextInput>();
    this->spriteRenderer = parent->getComponent<SpriteRenderer>();
    this->transform = parent->transform;
}

void Cursor::onUpdate(const double deltaTime)
{
    time = std::fmod(time + deltaTime, 1);

    this->spriteRenderer->visible = textInput->isFocused && time < 0.5;

    int w;
    TTF_SetFontSize(FontManager::main, ptSize);
    TTF_GetStringSize(FontManager::main, this->textInput->text, 0, &w, nullptr);
    transform->position.x = w - parent->parent->transform->scale.x / 2.0 + 35;
}

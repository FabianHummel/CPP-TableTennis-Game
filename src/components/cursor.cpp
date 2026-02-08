//
// Created by Fabian Hummel on 08.02.26.
//

#include "cursor.h"

#include "../fontmanager.h"

Cursor::Cursor(int ptSize) {
    this->ptSize = ptSize;
    this->time = 0;
}

void Cursor::onInitialize() {
    this->textInput = parent->parent->getComponent<TextInput>();
    this->spriteRenderer = parent->getComponent<SpriteRenderer>();
    this->transform = parent->transform;
}

void Cursor::onUpdate(const double deltaTime) {
    time = std::fmod(time + deltaTime, 1);

    this->spriteRenderer->visible = textInput->isFocused && time < 0.5;

    int w;
    TTF_SetFontSize(FontManager::main, ptSize);
    TTF_SizeText(FontManager::main, this->textInput->text, &w, nullptr);
    transform->setX(w - parent->parent->transform->getScaleX() / 2.0 + 35);
}

void Cursor::onEvent(SDL_Event event) {

}

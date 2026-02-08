#pragma once

#include "spriterenderer.h"
#include "textinput.h"

class Cursor : public Component
{
private:
    Transform *transform{};
    TextInput *textInput{};
    SpriteRenderer *spriteRenderer{};
    double time;
    int ptSize;

public:
    Cursor(int ptSize);
    void onInitialize() override;
    void onUpdate(double deltaTime) override;
    void onEvent(SDL_Event event) override;
};

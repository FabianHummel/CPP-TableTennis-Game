#pragma once

#include "spriterenderer.h"
#include "textinput.h"

class Cursor : public Component
{
private:
    Transform* transform{};
    TextInput* text_input{};
    SpriteRenderer* sprite_renderer{};
    double time;
    int pt_size;

public:
    Cursor(int ptSize);
    void on_initialize() override;
    void on_update(double deltaTime) override;
};
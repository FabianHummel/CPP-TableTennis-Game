#pragma once

#include "componentsystem.h"
#include "textrenderer.h"

class TextInput : public Component
{
private:
    Transform* transform{};
    std::function<void(char* text)> on_input_changed;
    size_t max_length;

public:
    char* text;
    bool is_focused{};

    TextInput(char* text, size_t max_length, const std::function<void(char* text)>& on_input_changed);

    void on_initialize() override;
    void on_update(double delta_time) override;
    void on_event(const SDL_Event* event) override;
};
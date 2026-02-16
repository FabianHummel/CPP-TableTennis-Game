#pragma once

#include "componentsystem.h"
#include <functional>

class Button : public Component
{
  private:
    Transform *transform{nullptr};
    std::function<void()> on_mouse_down;
    std::function<void()> on_mouse_up;
    std::function<void()> on_mouse_over;
    std::function<void()> on_mouse_exit;

  public:
    struct EventHandlers
    {
        const std::function<void()> &on_mouse_down = nullptr;
        const std::function<void()> &on_mouse_up = nullptr;
        const std::function<void()> &on_mouse_over = nullptr;
        const std::function<void()> &on_mouse_exit = nullptr;
    };

    bool is_mouse_over{};

    explicit Button(const EventHandlers &event_handlers);
    explicit Button(const std::function<void()> &on_click);
    void on_initialize() override;
    void on_update(double deltaTime) override;
    void on_event(const SDL_Event *event) override;
};
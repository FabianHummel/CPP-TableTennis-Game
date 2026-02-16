#include "button.h"
#include "../managers/cursormanager.h"
#include "button.h"
#include <SDL3/SDL_events.h>
#include <SDL3/SDL_mouse.h>

Button::Button(const EventHandlers &event_handlers)
{
    this->name = "Button";
    this->on_mouse_down = event_handlers.on_mouse_down;
    this->on_mouse_up = event_handlers.on_mouse_up;
    this->on_mouse_over = event_handlers.on_mouse_over;
    this->on_mouse_exit = event_handlers.on_mouse_exit;
}

Button::Button(const std::function<void()> &on_click)
    : Button(EventHandlers{
          .on_mouse_up = on_click,
      })
{
}

void Button::on_initialize()
{
    this->transform = parent->transform;
}

void Button::on_update(double deltaTime)
{
    if (!parent->is_visible())
        return;

    float x, y;
    SDL_GetMouseState(&x, &y);
    x *= 2;
    y *= 2;

    CursorManager::request_cursor(transform->in_transform_bounds(x, y) ? CursorManager::hand_cursor
                                                                      : CursorManager::arrow_cursor);
}

void Button::on_event(const SDL_Event *event)
{
    if (!parent->is_visible())
        return;

    float x, y;
    SDL_GetMouseState(&x, &y);
    x *= 2;
    y *= 2;

    switch (event->type)
    {
    case SDL_EVENT_MOUSE_MOTION:
        if (transform->in_transform_bounds(x, y) && !is_mouse_over)
        {
            is_mouse_over = true;
            if (on_mouse_over)
                on_mouse_over();
        }
        else if (!transform->in_transform_bounds(x, y) && is_mouse_over)
        {
            is_mouse_over = false;
            if (on_mouse_exit)
                on_mouse_exit();
        }
        break;
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        if (on_mouse_down && transform->in_transform_bounds(x, y))
            on_mouse_down();
        break;

    case SDL_EVENT_MOUSE_BUTTON_UP:
        if (on_mouse_up && transform->in_transform_bounds(x, y))
            on_mouse_up();
        break;
    default:
        break;
    }
}
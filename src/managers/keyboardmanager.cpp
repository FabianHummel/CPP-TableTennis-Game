//
// Created by Fabian Hummel on 08.02.26.
//

#include "../managers/keyboardmanager.h"

#include <SDL3/SDL_keyboard.h>

namespace KeyboardManager
{
    bool is_text_input_requested = false;
}

void KeyboardManager::pre_event(const SDL_Event *event)
{
    switch (event->type)
    {
    case SDL_EVENT_MOUSE_BUTTON_DOWN:
        is_text_input_requested = false;
        break;
    default:;
    }
}

void KeyboardManager::post_event(SDL_Window *window)
{
    if (is_text_input_requested)
    {
        SDL_StartTextInput(window);
    }
    else
    {
        SDL_StopTextInput(window);
    }
}
//
// Created by Fabian Hummel on 08.02.26.
//

#include "keyboardmanager.h"

#include <SDL3/SDL_keyboard.h>

#include "utility/renderwindow.h"

namespace KeyboardManager
{
    bool isTextInputRequested = false;

    void preEvent(const SDL_Event *event)
    {
        switch (event->type)
        {
            case SDL_EVENT_MOUSE_BUTTON_DOWN:
                isTextInputRequested = false;
                break;
            default: ;
        }
    }

    void postEvent()
    {
        if (isTextInputRequested)
        {
            SDL_StartTextInput(nullptr);
        }
        else
        {
            SDL_StopTextInput(nullptr);
        }
    }
}

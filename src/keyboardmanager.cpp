//
// Created by Fabian Hummel on 08.02.26.
//

#include "keyboardmanager.h"

#include <SDL_keyboard.h>

namespace KeyboardManager
{
    bool isTextInputRequested = false;

    void preEvent(const SDL_Event &event)
    {
        switch (event.type)
        {
            case SDL_MOUSEBUTTONDOWN:
                isTextInputRequested = false;
                break;
            default: ;
        }
    }

    void postEvent()
    {
        if (isTextInputRequested)
        {
            SDL_StartTextInput();
        }
        else
        {
            SDL_StopTextInput();
        }
    }
}

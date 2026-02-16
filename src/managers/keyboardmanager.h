//
// Created by Fabian Hummel on 08.02.26.
//

#ifndef TABLETENNIS_KEYBOARDMANAGER_H
#define TABLETENNIS_KEYBOARDMANAGER_H
#include <SDL3/SDL_events.h>


namespace KeyboardManager
{
    extern bool is_text_input_requested;

    void pre_event(const SDL_Event* event);
    void post_event(SDL_Window * window);
};


#endif //TABLETENNIS_KEYBOARDMANAGER_H
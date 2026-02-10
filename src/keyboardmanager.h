//
// Created by Fabian Hummel on 08.02.26.
//

#ifndef TABLETENNIS_KEYBOARDMANAGER_H
#define TABLETENNIS_KEYBOARDMANAGER_H
#include <SDL3/SDL_events.h>


namespace KeyboardManager {

    extern bool isTextInputRequested;

    void preEvent(const SDL_Event *event);
    void postEvent();
};


#endif //TABLETENNIS_KEYBOARDMANAGER_H
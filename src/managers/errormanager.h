//
// Created by Fabian Hummel on 15.02.26.
//

#ifndef TABLETENNIS_ERRORMANAGER_H
#define TABLETENNIS_ERRORMANAGER_H

#include <SDL3/SDL.h>
#include <vector>

class ErrorManager
{
private:
    static std::vector<const char*> errors;

public:
    static void queue_error(const char* error);
    static void show_errors(SDL_Renderer* renderer);
};


#endif //TABLETENNIS_ERRORMANAGER_H
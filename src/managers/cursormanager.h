#pragma once

#include <SDL3/SDL_mouse.h>

namespace CursorManager
{
    extern SDL_Cursor* arrow_cursor;
    extern SDL_Cursor* input_cursor;
    extern SDL_Cursor* hand_cursor;

    void load_cursors();
    void request_cursor(SDL_Cursor * cursor);
    void force_set_cursor(SDL_Cursor * cursor);
    void update();
}
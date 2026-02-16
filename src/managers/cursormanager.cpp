#include "cursormanager.h"
#include "map"

namespace CursorManager
{
    SDL_Cursor* arrow_cursor{};
    SDL_Cursor* hand_cursor{};
    SDL_Cursor* input_cursor{};

    SDL_Cursor* active{};
    std::map<SDL_Cursor*, uint> priority;

    void load_cursors()
    {
        arrow_cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
        priority[arrow_cursor] = 0;

        input_cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_TEXT);
        priority[input_cursor] = 1;

        hand_cursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_POINTER);
        priority[hand_cursor] = 2;
    }

    void request_cursor(SDL_Cursor* cursor)
    {
        const uint current_priority = priority[active];

        if (const uint new_priority = priority[cursor]; new_priority > current_priority)
        {
            active = cursor;
        }
    }

    void force_set_cursor(SDL_Cursor* cursor)
    {
        active = cursor;
    }

    void update()
    {
        SDL_SetCursor(active);
    }
}
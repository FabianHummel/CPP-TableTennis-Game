#include "fontmanager.h"
#include <SDL3_ttf/SDL_ttf.h>
#include <cstdio>

namespace FontManager
{
    TTF_Font* main = {};
    TTF_Font* mono = {};

    void init()
    {
        main = TTF_OpenFont("res/fonts/Quicksand-Bold.ttf", 42);
        mono = TTF_OpenFont("res/fonts/RobotoMono-Regular.ttf", 42);

        TTF_SetFontStyle(main, TTF_STYLE_NORMAL);
    }

    void close()
    {
        TTF_CloseFont(main);
        TTF_CloseFont(mono);
    }
}
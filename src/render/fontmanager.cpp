#include "fontmanager.h"
#include <SDL_ttf.h>
#include <cstdio>

namespace FontManager
{
	void init()
	{
		TTF_Font *mainFont = TTF_OpenFont("res/fonts/Quicksand-Bold.ttf", 42);
		printf("Initialized!\n%s\n", TTF_GetError());
		TTF_SetFontStyle(mainFont, TTF_STYLE_NORMAL);
		FontManager::main = mainFont;
	}

	void close()
	{
		TTF_CloseFont(FontManager::main);
	}
}

#pragma once

#include <SDL2/SDL_mouse.h>

namespace CursorManager
{
	extern SDL_Cursor *arrowCursor;
	extern SDL_Cursor *inputCursor;
	extern SDL_Cursor *handCursor;

	void loadCursors();
	void requestCursor(SDL_Cursor *cursor);
	void forceSetCursor(SDL_Cursor *cursor);
	void update();
}
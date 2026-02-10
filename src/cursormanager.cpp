#include "cursormanager.h"
#include "map"

namespace CursorManager
{
	SDL_Cursor *arrowCursor{};
	SDL_Cursor *handCursor{};
	SDL_Cursor *inputCursor{};

	SDL_Cursor *active{};
	std::map<SDL_Cursor*, uint> priority;

	void loadCursors()
	{
		arrowCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_DEFAULT);
		priority[arrowCursor] = 0;

		inputCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_TEXT);
		priority[inputCursor] = 1;

		handCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_POINTER);
		priority[handCursor] = 2;
	}

	void requestCursor(SDL_Cursor *cursor)
	{
		uint currentPriority = priority[active];
		uint newPriority = priority[cursor];

		if (newPriority > currentPriority)
		{
			active = cursor;
		}
	}

	void forceSetCursor(SDL_Cursor *cursor)
	{
		active = cursor;
	}

	void update()
	{
		SDL_SetCursor(active);
	}
}
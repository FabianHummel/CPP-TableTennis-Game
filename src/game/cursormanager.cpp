#include "cursormanager.h"
#include "map"

namespace CursorManager
{
	SDL_Cursor *arrowCursor{};
	SDL_Cursor *handCursor{};

	SDL_Cursor *active{};
	std::map<SDL_Cursor*, uint> priority;

	void loadCursors()
	{
		arrowCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_ARROW);
		priority[arrowCursor] = 0;

		handCursor = SDL_CreateSystemCursor(SDL_SYSTEM_CURSOR_HAND);
		priority[handCursor] = 1;
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
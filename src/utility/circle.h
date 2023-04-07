#pragma once

#include "SDL.h"
#include "SDL_render.h"

class CircleDrawer
{
  public:
	static void DrawCircle(int x, int y, int radius, SDL_Color color, SDL_Renderer *renderer);
};

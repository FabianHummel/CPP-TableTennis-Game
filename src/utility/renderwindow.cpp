//
// Created by Fabian Hummel on 16.04.22.
//

#include "renderwindow.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_hints.h>
#include <SDL2/SDL_video.h>

RenderWindow::RenderWindow(int width, int height, const char *title)
{
	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
		return;
	}

	SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
	window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width / 2, height / 2,
	                          SDL_WINDOW_ALLOW_HIGHDPI + SDL_WINDOW_OPENGL);

	if (!window)
	{
		printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
		return;
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED + SDL_RENDERER_PRESENTVSYNC);
	if (!renderer)
	{
		printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
		return;
	}
}

RenderWindow::~RenderWindow()
{
	this->destroy();
}

void RenderWindow::drawBG(const SDL_Color color) const
{
	SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void RenderWindow::clear() const
{
	SDL_RenderClear(renderer);
}

void RenderWindow::destroy() const
{
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

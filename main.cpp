#define ENET_IMPLEMENTATION
#define SDL_MAIN_USE_CALLBACKS 1

#include "src/animationmanager.h"
#include "src/cursormanager.h"
#include "src/keyboardmanager.h"
#include "src/ecsmanager.h"
#include "src/fontmanager.h"
#include "src/gamemanager.h"
#include "src/netmanager.h"
#include "src/panes/home.h"
#include "src/utility/renderwindow.h"
#include "src/shared/enet.h"
#include <SDL3/SDL.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <SDL3_ttf/SDL_ttf.h>
#include <cstdio>

SDL_Window *window;
SDL_Renderer *renderer;
bool running = true;
uint64_t currentTick = SDL_GetPerformanceCounter();
uint64_t lastTick = 0;

SDL_AppResult SDL_AppInit(void **appstate, int argc, char *argv[])
{
	if (!SDL_CreateWindowAndRenderer("Table Tennis", RenderWindow::SCREEN_WIDTH / 2, RenderWindow::SCREEN_HEIGHT / 2,
		SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_OPENGL | SDL_WINDOWPOS_CENTERED, &window, &renderer))
	{
		SDL_LogError(SDL_LOG_CATEGORY_RENDER, "Couldn't create window and renderer: %s\n", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Couldn't initialize SDL: %s\n", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!MIX_Init())
	{
		SDL_LogError(SDL_LOG_CATEGORY_AUDIO, "Couldn't initialize Mixer: %s\n", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!TTF_Init())
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't initialize TTF: %s\n", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (enet_initialize() < 0)
	{
		fprintf(stderr, "Couldn't initialize ENet.\n");
		exit(EXIT_FAILURE);
	}

	CursorManager::loadCursors();
	FontManager::init();
	GameManager::switchScene(nullptr, new HomePane(renderer));

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, const SDL_Event *event)
{
	switch (event->type)
	{
		case SDL_EVENT_QUIT: {
			return SDL_APP_SUCCESS;
		}

		default:
			KeyboardManager::preEvent(event);
			GameManager::currentPane->onEvent(event);
			EcsManager::event(event);
			KeyboardManager::postEvent();
	}

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
	lastTick = currentTick;
	currentTick = SDL_GetPerformanceCounter();
	double deltaTime = (double)(currentTick - lastTick) / (double)SDL_GetPerformanceFrequency();

	EcsManager::sort();
	CursorManager::forceSetCursor(CursorManager::arrowCursor);

	SDL_SetRenderDrawColor(renderer, 203, 211, 235, 255);
	SDL_RenderClear(renderer);

	NetManager::update(deltaTime);
	EcsManager::update(deltaTime);
	GameManager::currentPane->onGui(deltaTime);
	AnimationManager::update(deltaTime);
	CursorManager::update();

	SDL_RenderPresent(renderer);

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
	FontManager::close();

	SDL_Quit();
	MIX_Quit();
	TTF_Quit();
	enet_deinitialize();
}
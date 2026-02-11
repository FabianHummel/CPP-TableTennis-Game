#define ENET_IMPLEMENTATION
#define SDL_MAIN_USE_CALLBACKS

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
#include <SDL3/SDL_main.h>
#include <SDL3/SDL_init.h>
#include <SDL3_mixer/SDL_mixer.h>
#include <cstdio>

struct AppState
{
	SDL_Window *window{nullptr};
	SDL_Renderer *renderer{nullptr};
	bool running{true};
	uint64_t currentTick{0};
	uint64_t lastTick{0};
};

SDL_AppResult SDL_AppInit(void **appstate, int argc, char **argv)
{
	*appstate = new AppState;
	AppState& state = *static_cast<AppState*>(*appstate);

	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO))
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't initialize SDL: %s\n", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	if (!SDL_CreateWindowAndRenderer("Table Tennis", RenderWindow::SCREEN_WIDTH / 2, RenderWindow::SCREEN_HEIGHT / 2,
		SDL_WINDOW_HIGH_PIXEL_DENSITY | SDL_WINDOW_OPENGL, &state.window, &state.renderer))
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't create window and renderer: %s\n", SDL_GetError());
		return SDL_APP_FAILURE;
	}

	SDL_SetWindowPosition(state.window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

	if (!MIX_Init())
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "Couldn't initialize Mixer: %s\n", SDL_GetError());
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
	GameManager::switchScene(nullptr, new HomePane(state.renderer));

	state.currentTick = SDL_GetPerformanceCounter();

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppEvent(void *appstate, SDL_Event *event)
{
	AppState& state = *static_cast<AppState*>(appstate);

	switch (event->type)
	{
		case SDL_EVENT_QUIT: {
			return SDL_APP_SUCCESS;
		}

		default:
			KeyboardManager::preEvent(event);
			GameManager::currentPane->onEvent(event);
			EcsManager::event(event);
			KeyboardManager::postEvent(state.window);
	}

	return SDL_APP_CONTINUE;
}

SDL_AppResult SDL_AppIterate(void *appstate)
{
	AppState& state = *static_cast<AppState*>(appstate);

	state.lastTick = state.currentTick;
	state.currentTick = SDL_GetPerformanceCounter();
	double deltaTime = (double)(state.currentTick - state.lastTick) / (double)SDL_GetPerformanceFrequency();

	if (SDL_GetWindowFlags(state.window) & SDL_WINDOW_OCCLUDED)
	{
		SDL_Delay(100);
	}

	EcsManager::sort();
	CursorManager::forceSetCursor(CursorManager::arrowCursor);

	SDL_SetRenderDrawColor(state.renderer, 203, 211, 235, 255);
	SDL_RenderClear(state.renderer);

	NetManager::update(deltaTime);
	EcsManager::update(deltaTime);
	GameManager::currentPane->onGui(deltaTime);
	AnimationManager::update(deltaTime);
	CursorManager::update();

	SDL_RenderPresent(state.renderer);

	return SDL_APP_CONTINUE;
}

void SDL_AppQuit(void *appstate, SDL_AppResult result)
{
	AppState* state = static_cast<AppState*>(appstate);
	delete state;

	FontManager::close();

	SDL_Quit();
	MIX_Quit();
	TTF_Quit();
	enet_deinitialize();
}
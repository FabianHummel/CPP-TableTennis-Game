#include "src/animationmanager.h"
#include "src/cursormanager.h"
#include "src/ecsmanager.h"
#include "src/fontmanager.h"
#include "src/gamemanager.h"
#include "src/netmanager.h"
#include "src/panes/home.h"
#include "src/utility/renderwindow.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <enet/enet.h>
#include <cstdio>

const SDL_Color BG = {203, 211, 235, 255};

uint64_t currentTick = 0;
uint64_t lastTick = 0;
double deltaTime = 0;

int main(int argc, char **argv)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		fprintf(stderr, "SDL could not be initialized!\n SDL_Error: %s\n", SDL_GetError());
		return EXIT_FAILURE;
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		fprintf(stderr, "SDL_mixer could not initialize!\n SDL_mixer_Error: %s\n", Mix_GetError());
		return EXIT_FAILURE;
	}

	if (TTF_Init() < 0)
	{
		fprintf(stderr, "SDL_ttf could not initialize!\n SDL_ttf_Error: %s\n", TTF_GetError());
		return EXIT_FAILURE;
	}

	if (enet_initialize() < 0)
	{
		fprintf(stderr, "An error occurred while initializing ENet.\n");
		return EXIT_FAILURE;
	}


	RenderWindow *window = new RenderWindow(RenderWindow::SCREEN_WIDTH, RenderWindow::SCREEN_HEIGHT, "Table Tennis");
	CursorManager::loadCursors();
	FontManager::init();
	GameManager::switchScene(nullptr, new HomePane(window));
	currentTick = SDL_GetPerformanceCounter();
	GameManager::currentPane->onStart();

	bool running = true;
	while (running)
	{
		lastTick = currentTick;
		currentTick = SDL_GetPerformanceCounter();
		deltaTime = (currentTick - lastTick) / (double)SDL_GetPerformanceFrequency();

		EcsManager::sort();
		CursorManager::forceSetCursor(CursorManager::arrowCursor);

		SDL_Event event;
		while (SDL_PollEvent(&event))
		{
			switch (event.type)
			{
			case SDL_QUIT: {
				running = false;
			}

			default:
				GameManager::currentPane->onEvent(event);
				EcsManager::event(event);
			}
		}

		window->drawBG(BG);
		window->clear();

		NetManager::update();
		EcsManager::update(deltaTime);
		GameManager::currentPane->onGui(deltaTime);
		AnimationManager::update(deltaTime);
		CursorManager::update();

		SDL_RenderPresent(window->renderer);
	}

	delete GameManager::currentPane;
	FontManager::close();
	EcsManager::clear();

	SDL_Quit();
	Mix_Quit();
	TTF_Quit();

	return 0;
}

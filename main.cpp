#include "src/ecs/ecsmanager.h"
#include "src/game/gamemanager.h"
#include "src/game/cursormanager.h"
#include "src/animations/animationmanager.h"
#include "src/render/fontmanager.h"
#include "src/render/renderwindow.h"
#include "src/panes/game.h"
#include "src/panes/home.h"
#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <cstdio>

const SDL_Color BG = {203, 211, 235, 255};

uint64_t currentTick = 0;
uint64_t lastTick = 0;
double deltaTime = 0;

int main(int argc, char **argv)
{
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
	{
		printf("SDL could not be initialized!\n SDL_Error: %s\n", SDL_GetError());
		exit(EXIT_FAILURE);
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
	{
		printf("SDL_mixer could not initialize!\n SDL_mixer_Error: %s\n", Mix_GetError());
		exit(EXIT_FAILURE);
	}

	if (TTF_Init() < 0)
	{
		printf("SDL_ttf could not initialize!\n SDL_ttf_Error: %s\n", TTF_GetError());
		exit(EXIT_FAILURE);
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

		EcsManager::update(deltaTime);
		GameManager::currentPane->onGui(deltaTime);
		AnimationManager::update(deltaTime);
		CursorManager::update();

		SDL_RenderPresent(window->renderer);
	}

	GameManager::currentPane->dispose();
	FontManager::close();
	EcsManager::clear();

	SDL_Quit();
	Mix_Quit();
	TTF_Quit();

	return 0;
}

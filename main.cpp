#include <SDL.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <cstdio>
#include "src/menu/pane.h"
#include "src/panes/game.h"
#include "src/panes/home.h"
#include "src/render/renderwindow.h"
#include "src/render/fontmanager.h"
#include "src/entity/entitymanager.h"

const SDL_Color BG = {203, 211, 235, 255};

uint64_t currentTick = 0;
uint64_t lastTick = 0;
double deltaTime = 0;

Pane *currentPane;

int main(int argc, char** argv) {
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("SDL could not be initialized!\n" "SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_mixer could not initialize!\n" "SDL_mixer_Error: %s\n", Mix_GetError());
		exit(1);
	}

	if (TTF_Init() < 0) {
		printf("SDL_ttf could not initialize!\n" "SDL_ttf_Error: %s\n", TTF_GetError());
		exit(1);
	}

	RenderWindow *window = new RenderWindow(
		RenderWindow::SCREEN_WIDTH, RenderWindow::SCREEN_HEIGHT, "Table Tennis");
	FontManager::init();

	currentPane = new HomePane(window);
	currentTick = SDL_GetPerformanceCounter();

	currentPane->onStart();

	bool running = true;
	while (running) {
		lastTick = currentTick;
		currentTick = SDL_GetPerformanceCounter();
		deltaTime = (double) ((currentTick - lastTick) * 1 / (double) SDL_GetPerformanceFrequency());

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT: {
					running = false;
				}

				default:
					EntityManager::event(event);
			}
		}

		window->drawBG(BG);
		window->clear();

		currentPane->onGui(deltaTime);

		SDL_RenderPresent(window->renderer);
	}

	currentPane->dispose();
	FontManager::close();

	SDL_Quit();
	Mix_Quit();
	TTF_Quit();

	return 0;
}

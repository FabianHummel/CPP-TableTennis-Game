#include <SDL.h>
#include "src/render/renderwindow.h"
#include "src/entity/entity.h"
#include "src/gameplay/components/spriterenderer.h"
#include "src/gameplay/components/ballmovement.h"
#include "src/entity/entitymanager.h"
#include "src/gameplay/components/shadowtransformer.h"
#include "src/gameplay/components/gamemanager.h"
#include "src/gameplay/components/clickmanager.h"
#include "src/gameplay/components/powerbar.h"
#include "src/sound/soundmanager.h"

const SDL_Color BG = {203, 211, 235, 255};

Uint64 currentTick = 0;
Uint64 lastTick = 0;
double deltaTime = 0;

int main(int argc, char** argv) {
	if(SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
		printf("SDL could not be initialized!\n" "SDL_Error: %s\n", SDL_GetError());
		exit(1);
	}

	if (Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
		printf("SDL_mixer could not initialize!\n" "SDL_mixer_Error: %s\n", Mix_GetError());
		exit(1);
	}

	RenderWindow *window = new RenderWindow(
		RenderWindow::SCREEN_WIDTH, RenderWindow::SCREEN_HEIGHT, "Table Tennis"
	);

	Entity *global = ( new Entity("Global") )
		->addComponent(new Transform(
			{ 0, 0, 0 }, { 0, 0 }, 0.0f)
		)
		->addComponent(new GameManager())
		->addComponent(new ClickManager());

	Entity *table = ( new Entity("Table") )
		->addComponent(new Transform(
			{ RenderWindow::SCREEN_CENTER_X, 0, RenderWindow::SCREEN_CENTER_Y },
			{ RenderWindow::SCREEN_WIDTH, RenderWindow::SCREEN_HEIGHT }, 0.0f
		) )
		->addComponent(new SpriteRenderer(
			"res/table.png", window->renderer
		) );

	Entity *net = ( new Entity("Net") )
		->addComponent(new Transform(
			{ RenderWindow::SCREEN_CENTER_X, 0, RenderWindow::SCREEN_CENTER_Y },
			{ RenderWindow::SCREEN_WIDTH, RenderWindow::SCREEN_HEIGHT }, 0.0f
		) )
		->addComponent(new SpriteRenderer(
			"res/net.png", window->renderer
		) );

	Entity *shadow = ( new Entity("Shadow") )
		->addComponent(new Transform(
			{ RenderWindow::SCREEN_CENTER_X, 0, RenderWindow::SCREEN_CENTER_Y },
			{ 40, 40 }, 0.0f
		) )
		->addComponent(new SpriteRenderer(
			"res/shadow.png", window->renderer
		) )
		->addComponent(new ShadowTransformer());

	Entity *ball = ( new Entity("Ball") )
		->addComponent(new Transform(
			{ RenderWindow::SCREEN_CENTER_X, 0, RenderWindow::SCREEN_CENTER_Y },
			{ 40, 40 }, 0.0f
		) )
		->addComponent(new SpriteRenderer(
			"res/ball.png", window->renderer
		) )
		->addComponent(new BallMovement());

	Entity *indicator = ( new Entity("Indicator") )
		->addComponent(new Transform(
			{ 0, 0, 0 }, { 70, 70 }, 0.0f
		) )
		->addComponent(new SpriteRenderer(
			"res/indicator.png", window->renderer
		) );

	Entity *powerbar = ( new Entity("Powerbar") )
		->addComponent(new Transform(
			{ 0, 0, 0 }, { 70, 70 }, 0.0f
		) )
		->addComponent(new SpriteRenderer(
			"res/powerbar.png", window->renderer
		) )
		->addComponent(new Powerbar());

	Entity *powerbox = ( new Entity("Powerbox") )
		->addComponent(new Transform(
			{ 0, 0, 0 }, { 70, 70 }, 0.0f
		) )
		->addComponent(new SpriteRenderer(
			"res/powerbox.png", window->renderer
		) );

	EntityManager::initialize();
	EntityManager::start();

	ClickManager *clickManager = global->getComponent<ClickManager>();

	currentTick = SDL_GetPerformanceCounter();

	bool running = true;
	while (running) {
		lastTick = currentTick;
		currentTick = SDL_GetPerformanceCounter();
		deltaTime = (double) ((currentTick - lastTick) * 1000 / (double) SDL_GetPerformanceFrequency());

		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT: {
					running = false;
					break;
				}

				case SDL_MOUSEBUTTONDOWN: {
					int x, y;
					SDL_GetMouseState(&x, &y);
					clickManager->onClick(x * 2, y * 2);
					break;
				}

				case SDL_MOUSEBUTTONUP: {
					clickManager->onRelease();
					break;
				}

				case SDL_MOUSEMOTION: {
					int x, y;
					SDL_GetMouseState(&x, &y);
					clickManager->onDrag(x * 2, y * 2);
					break;
				}

				default:
					break;
			}
		}

		window->drawBG(BG);
		window->clear();

		EntityManager::update(deltaTime * 0.1);

		SDL_RenderPresent(
			window->renderer
		);
	}

	delete table;
	delete net;
	delete shadow;
	delete ball;
	delete indicator;
	delete powerbox;
	delete powerbar;
	delete global;

	delete window;

	SDL_Quit();
	return 0;
}
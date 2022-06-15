#include <SDL.h>
#include "src/render/renderwindow.h"
#include "src/entity/entity.h"
#include "src/gameplay/clickmanager.h"
#include "src/gameplay/components/spriterenderer.h"
#include "src/gameplay/components/ballmovement.h"
#include "src/entity/entitymanager.h"
#include "src/gameplay/components/shadowtransformer.h"
#include "src/gameplay/components/gamemanager.h"

const SDL_Color BG = {203, 211, 235, 255};

int main(int argc, char** argv) {
	RenderWindow *window = new RenderWindow(
		RenderWindow::SCREEN_WIDTH, RenderWindow::SCREEN_HEIGHT, "Table Tennis"
	);

	Entity *global = ( new Entity("Global") )
		->addComponent(new GameManager());

	Entity *table = ( new Entity("Table") )
		->addComponent(new Transform(
			{ 0, 0, 0 }, { RenderWindow::SCREEN_WIDTH, RenderWindow::SCREEN_HEIGHT }
		) )
		->addComponent(new SpriteRenderer(
			"../res/table.png", window->renderer
		) );

	Entity *net = ( new Entity("Net") )
		->addComponent(new Transform(
			{ 0, 0, 0 }, { RenderWindow::SCREEN_WIDTH, RenderWindow::SCREEN_HEIGHT }
		) )
		->addComponent(new SpriteRenderer(
			"../res/net.png", window->renderer
		) );

	Entity *shadow = ( new Entity("Shadow") )
		->addComponent(new Transform(
			{ 0, 0, 0 }, { 40, 40 }
		) )
		->addComponent(new SpriteRenderer(
			"../res/shadow.png", window->renderer
		) )
		->addComponent(new ShadowTransformer());

	Entity *ball = ( new Entity("Ball") )
		->addComponent(new Transform(
			{ (float) RenderWindow::trueCenterX(40), 0, (float) RenderWindow::trueCenterY(40) }, { 40, 40 }
		) )
		->addComponent(new SpriteRenderer(
			"../res/ball.png", window->renderer
		) )
		->addComponent(new BallMovement());

	EntityManager::initialize();
	EntityManager::start();

	bool running = true;
	while (running) {
		SDL_Event event;
		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_QUIT:
					running = false;
					break;

				case SDL_MOUSEBUTTONDOWN:
					int x, y;
					SDL_GetMouseState(&x, &y);
					ClickManager::onClick(x, y);
					break;

				default:
					break;
			}
		}

		window->drawBG(BG);
		window->clear();

		EntityManager::update();

		SDL_RenderPresent(
			window->renderer
		);
	}

	delete table;
	delete net;
	delete shadow;
	delete ball;
	delete global;

	delete window;
	return 0;
}
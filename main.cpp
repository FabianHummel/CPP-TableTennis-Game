#include <SDL.h>
#include "src/render/renderwindow.h"
#include "src/entity/entity.h"
#include "src/gameplay/clickmanager.h"
#include "vector"
#include "src/entity/components/spriterenderer.h"

const SDL_Color BG = {203, 211, 235, 255};

int main(int argc, char** argv) {
	RenderWindow *window = new RenderWindow(
		RenderWindow::SCREEN_WIDTH, RenderWindow::SCREEN_HEIGHT, "Table Tennis"
	);

	Entity ball = ( new Entity("Ball") )
		->addComponent<SpriteRenderer>(new SpriteRenderer(
			"../res/ball.png", window->renderer, 20, 20, 40, 40)
		);

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

		SDL_RenderPresent(
			window->renderer
		);
	}

	delete window;
	return 0;
}
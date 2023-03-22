#pragma once

#include "../menu/pane.h"
#include "../entity/entity.h"
#include <SDL_events.h>

class GamePane : public Pane
{
	private:
		Entity *global;
		Entity *table;
		Entity *net;
		Entity *shadow;
		Entity *ball;
		Entity *indicator;
		Entity *powerbar;
		Entity *powerbox;

	public:
		GamePane(RenderWindow *window);
		void onStart() override;
		void onGui(double deltaTime) override;
		void dispose() override;
};

#pragma once

#include "pane.h"
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
	Entity *prediction;

  public:
	explicit GamePane(RenderWindow *window);
	void dispose() override;
};

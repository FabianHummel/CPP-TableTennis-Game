#pragma once

#include "pane.h"
#include "../componentsystem.h"

class GamePane : public Pane
{
  private:
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
	~GamePane();
};

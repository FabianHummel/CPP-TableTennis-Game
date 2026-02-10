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

	void back();

  public:
	explicit GamePane(SDL_Renderer *renderer);
	~GamePane();

	void onEvent(const SDL_Event *event) override;
};

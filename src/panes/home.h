#pragma once

#include "pane.h"
#include "../game/gamemode.h"

class HomePane : public Pane
{
  private:
	GameMode currentGameMode{};
	TextRenderer *gamemodeText{};
	Entity *title;
	Entity *background;
	Entity *gamemode;
	Entity *previous;
	Entity *next;
	Entity *ball;
	Entity *menuline;
	Entity *settings;
	Entity *start;

  public:
	explicit HomePane(RenderWindow *window);
	~HomePane();

	void onStart() override;
	void onEvent(SDL_Event event) override;

	void changeGameMode();
	void previousGameMode();
	void nextGameMode();
	void startGame();
};

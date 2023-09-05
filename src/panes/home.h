#pragma once

#include "pane.h"
#include "../gameplay/gamemode.h"

class HomePane : public Pane
{
  private:
	Entity *title;
	Entity *background;
	Entity *gamemode;
	Entity *previous;
	Entity *next;

	GameMode currentGameMode;
	TextRenderer *gamemodeText;

  public:
	HomePane(RenderWindow *window);
	void onStart() override;
	void onEvent(SDL_Event event) override;
	void dispose() override;

	void previousGameMode();
	void nextGameMode();
	void startGame();
};

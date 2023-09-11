#pragma once

#include "pane.h"
#include "../game/gamemode.h"

class HomePane : public Pane
{
  private:
	GameMode currentGameMode{};
	TextRenderer *gamemodeText{};

  public:
	HomePane(RenderWindow *window);
	void onStart() override;
	void onEvent(SDL_Event event) override;
	void dispose() override;

	void previousGameMode();
	void nextGameMode();
	void startGame();
};

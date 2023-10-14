#pragma once

#include "pane.h"
#include "../game/gamemode.h"

class HomePane : public Pane
{
  private:
	char matchCode[6] = { 0 };
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
	Entity *matchCodeInput;

  public:
	explicit HomePane(RenderWindow *window);
	~HomePane();

	void onStart() override;
	void onEvent(SDL_Event event) override;

	void changeGameMode();
	void previousGameMode();
	void nextGameMode();
	void startServer();
	void joinServer();
	void startSinglePlayer();
};

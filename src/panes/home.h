#pragma once

#include "pane.h"
#include "../componentsystem.h"
#include "../game/gamemode.h"
#include "../components/textrenderer.h"

class HomePane : public Pane
{
  private:
	char matchCode[6] = {};
	char playerName[6] = {};
	GameMode currentGameMode{};
	TextRenderer *gamemodeText{};

	Entity *title;
	Entity *background;
	Entity *gamemode;
	Entity *previous;
	Entity *next;
	Entity *ball;
	Entity *menuline;
	Entity *start;
	Entity *matchCodeInput;
	Entity *playerNameInput;

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
	void startOrJoinServer();
};

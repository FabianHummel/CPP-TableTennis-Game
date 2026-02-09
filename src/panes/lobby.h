#pragma once

#include "pane.h"
#include "../componentsystem.h"
#include <enet/enet.h>

class LobbyPane : public Pane
{
  protected:
	Entity *versus;
	Entity *background;
	Entity *backButton;
	Entity *matchCodeButton;

	ENetPeer *enemy;

	std::string matchCode;
	std::string playerName;
	std::string enemyName;

	void back();

  public:
	explicit LobbyPane(RenderWindow *window, const std::string &match_code, const std::string &player_name);
	~LobbyPane();

	void onEvent(SDL_Event event) override;
};
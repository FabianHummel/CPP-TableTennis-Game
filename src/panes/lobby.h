#pragma once

#include "pane.h"
#include "../componentsystem.h"
#include <enet/enet.h>

class LobbyPane : public Pane
{
  private:
	Entity *versus;
	Entity *background;
	Entity *backButton;
	Entity *matchCodeButton;

	ENetPeer *enemy;

	const char *playerName;

	void back();

  public:
	explicit LobbyPane(RenderWindow *window, const char *match_code, const char *player_name);
	explicit LobbyPane(RenderWindow *window, const char *match_code, const char *player_name, ENetPeer *enemy);
	~LobbyPane();

	void onEvent(SDL_Event event) override;
};
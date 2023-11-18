#pragma once

#include "pane.h"
#include <enet/enet.h>

class LobbyPane : public Pane
{
  private:
	Entity *versus;
	Entity *background;
	Entity *backButton;
	Entity *matchCodeButton;

	ENetPeer *enemy;

	void back();

  public:
	explicit LobbyPane(RenderWindow *window, const char *match_code);
	explicit LobbyPane(RenderWindow *window, const char *match_code, ENetPeer *enemy);
	~LobbyPane();

	void onEvent(SDL_Event event) override;
};
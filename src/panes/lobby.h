#pragma once

#include "pane.h"
#include "../componentsystem.h"
#include "../shared/enet.h"

class LobbyPane : public Pane
{
  private:
	const char READY_TEXT[12] = "Ready!     ";
	const char NOT_READY_TEXT[10] = "Not ready";

  protected:
	Entity *versusTitle;
	Entity *versusEnemyName;
	Entity *background;
	Entity *backButton;
	Entity *matchCodeButton;
	Entity *readyButton;

	ENetPeer *enemy;

	std::string matchCode;
	std::string playerName;
	std::string enemyName;
	bool isReady;
	bool isEnemyReady;

	void back() const;

  public:
	explicit LobbyPane(SDL_Renderer *renderer, const std::string &match_code, const std::string &player_name);
	~LobbyPane();

	void onStart() override;
	void onEvent(const SDL_Event *event) override;
	void onGui(double deltaTime) override;
};
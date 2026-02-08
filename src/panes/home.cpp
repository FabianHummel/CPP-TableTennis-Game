#include "home.h"
#include "../animationmanager.h"
#include "../presets/index.h"
#include "../ecsmanager.h"
#include "../gamemanager.h"
#include "../netmanager.h"
#include "../fontmanager.h"
#include "../utility/renderindexes.h"
#include "game.h"
#include "lobby.h"
#include <functional>

HomePane::HomePane(RenderWindow *window) : Pane(window)
{
	title = EcsManager::addEntity(new Entity("Title"))
		->addComponent(new SpriteRenderer("res/title.png", window->renderer))
		->addComponent(new MenuTitle())
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 0}, {RenderWindow::SCREEN_WIDTH, 425}, {0.5f, 0.0f}, 0.0f, RenderIndexes::Menu::TITLE);

	background = EcsManager::addEntity(new Entity("Background"))
		->addComponent(new BubbleDrawer(window->renderer))
		->transform
		->apply({RenderWindow::SCREEN_HEIGHT, 0, 0}, {RenderWindow::SCREEN_WIDTH, RenderWindow::SCREEN_HEIGHT}, {0.5f, 0.5f}, -3.8, RenderIndexes::Menu::BACKGROUND);

	gamemode = EcsManager::addEntity(new Entity("Gamemode"))
		->addComponent(new TextRenderer(window->renderer, magic_enum::enum_name(GameMode::SINGLEPLAYER).data(), FontManager::DEFAULT, {40, 40, 40}))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 700}, {300, 100}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI);

	previous = EcsManager::addEntity(new Entity("Previous"))
		->addComponent(new Button(nullptr, [this] { previousGameMode(); }))
		->addComponent(new SpriteRenderer("res/menuarrow.png", window->renderer))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X - 200, 0, 700}, {40, 40}, {0.5f, 0.5f}, 180.0f, RenderIndexes::Menu::UI);

	next = EcsManager::addEntity(new Entity("Next"))
		->addComponent(new Button(nullptr, [this] { nextGameMode(); }))
		->addComponent(new SpriteRenderer("res/menuarrow.png", window->renderer))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X + 200, 0, 700}, {40, 40}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI);

	ball = EcsManager::addEntity(new Entity("Ball"))
		->addComponent(new SpriteRenderer("res/ball.png", window->renderer))
		->addComponent(new MenuBallBehaviour())
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 220}, {40, 40}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::BALL);

	menuline = EcsManager::addEntity(new Entity("Menuline"))
		->addComponent(new SpriteRenderer("res/menuline.png", window->renderer))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 650}, {300, 6}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI);

	start = EcsManager::addEntity(new Entity("Play-Button"))
		->usePreset(Presets::button(window->renderer, "Play", FontManager::DEFAULT, [this] { startSinglePlayer(); }))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 1000}, {300, 100}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI);

	playerNameInput = EcsManager::addEntity(new Entity("Player-Name-Input"))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 870}, {300, 120}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI)
		->apply(false)
		->usePreset(Presets::textinput(window->renderer, playerName, FontManager::DEFAULT, sizeof(playerName)-1));

	matchCodeInput = EcsManager::addEntity(new Entity("Match-Code-Input"))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 1000}, {300, 120}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI)
		->apply(false)
		->usePreset(Presets::textinput(window->renderer, matchCode, FontManager::DEFAULT, sizeof(matchCode)-1))
		->addChild((new Entity("Continue"))
			->addComponent(new Button(nullptr, [this] { startOrJoinServer(); }))
			->addComponent(new SpriteRenderer("res/menuarrow.png", window->renderer))
			->transform
			->apply({110, 0, -10}, {40, 40}, {0.5f, 0.5f}, 0.0f, 0));
}

HomePane::~HomePane()
{
	delete gamemodeText;
	delete title;
	delete background;
	delete gamemode;
	delete previous;
	delete next;
	delete ball;
	delete menuline;
	delete start;
	delete playerNameInput;
	delete matchCodeInput;
}

void HomePane::onStart()
{
	this->gamemodeText = gamemode->getComponent<TextRenderer>();
}

void HomePane::onEvent(SDL_Event event)
{
	switch (event.type)
	{
	case SDL_KEYDOWN:
		switch (event.key.keysym.sym)
		{
		case SDLK_LEFT:
			previousGameMode();
			break;
		case SDLK_RIGHT:
			nextGameMode();
			break;
		case SDLK_RETURN:
			if (this->currentGameMode == GameMode::SINGLEPLAYER)
			{
				startSinglePlayer();
			}
			else if (this->currentGameMode == GameMode::MULTIPLAYER)
			{
				startOrJoinServer();
			}
			break;
		}
	}
}

void HomePane::changeGameMode()
{
	auto text = magic_enum::enum_name(currentGameMode).data();
	this->gamemodeText->setText(text);

	if (this->currentGameMode == GameMode::SINGLEPLAYER)
	{
		AnimationManager::play(Animations::swipeIn(start, false), Easings::easeOut, 0.4);
		AnimationManager::play(Animations::fadeIn(start), Easings::linear, 0.2);

		AnimationManager::play(Animations::swipeOut(playerNameInput, true), Easings::easeOut, 0.4);
		AnimationManager::play(Animations::fadeOut(playerNameInput), Easings::easeOut, 0.2);

		AnimationManager::play(Animations::swipeOut(matchCodeInput, true), Easings::easeOut, 0.4);
		AnimationManager::play(Animations::fadeOut(matchCodeInput), Easings::easeOut, 0.2);
	}

	if (this->currentGameMode == GameMode::MULTIPLAYER)
	{
		AnimationManager::play(Animations::swipeOut(start, false), Easings::easeOut, 0.4);
		AnimationManager::play(Animations::fadeOut(start), Easings::easeOut, 0.2);

		AnimationManager::play(Animations::swipeIn(playerNameInput, true), Easings::easeOut, 0.4);
		AnimationManager::play(Animations::fadeIn(playerNameInput), Easings::linear, 0.2);

		AnimationManager::play(Animations::swipeIn(matchCodeInput, true), Easings::easeOut, 0.4);
		AnimationManager::play(Animations::fadeIn(matchCodeInput), Easings::linear, 0.2);
	}
}

void HomePane::previousGameMode()
{
	this->currentGameMode--;
	this->changeGameMode();
}

void HomePane::nextGameMode()
{
	this->currentGameMode++;
	this->changeGameMode();
}

void HomePane::startServer()
{
	NetManager::on_match_found = [this](const char *matchCode) {
		printf("Match found: %s\n", matchCode);
		EcsManager::clear();
		Pane *lobby = new LobbyPane(window, matchCode, playerName);
		GameManager::switchScene(this, lobby);
	};
	NetManager::on_match_not_found = [] {
		fprintf(stderr, "Match not found\n");
	};
	NetManager::init_matchmaking();
}

void HomePane::joinServer()
{
	NetManager::on_match_not_found = [] {
		fprintf(stderr, "Match not found\n");
	};
	NetManager::on_match_full = [] {
		fprintf(stderr, "Match full\n");
	};
	NetManager::on_punch_fail = [] {
		fprintf(stderr, "Punch failed\n");
	};
	NetManager::on_punched = [this](ENetPeer *enemy) {
		printf("Connected to %u:%u\n", enemy->address.host, enemy->address.port);
		EcsManager::clear();
		const auto matchCode = static_cast<char*>(malloc(6));
		strcpy(matchCode, this->matchCode);
		Pane *lobby = new LobbyPane(window, matchCode, playerName, enemy);
		GameManager::switchScene(this, lobby);
	};
	NetManager::on_peer_ping = [this](double rtt) {
//		printf("Round trip time: %f\n", rtt);
	};
	NetManager::join_match(matchCode);
}

void HomePane::startSinglePlayer()
{
	EcsManager::clear();
	Pane *pane = new GamePane(window);
	GameManager::switchScene(this, pane);
}

void HomePane::startOrJoinServer()
{
	if (this->matchCode[0] == '\0')
	{
		startServer();
	}
	else
	{
		joinServer();
	}
}
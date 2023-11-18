#include "home.h"
#include "../animationmanager.h"
#include "../ecs/presets/index.h"
#include "../ecsmanager.h"
#include "../gamemanager.h"
#include "../netmanager.h"
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
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 200}, {RenderWindow::SCREEN_WIDTH, 425}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::TITLE);

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

	settings = EcsManager::addEntity(new Entity("Start-Server-Button"))
	    ->apply(false)
	    ->usePreset(Presets::button(window->renderer, "Start server", FontManager::DEFAULT, [this] { startServer(); }))
	    ->transform
	    ->apply({RenderWindow::SCREEN_CENTER_X, 0, 1000}, {300, 100}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI);

	start = EcsManager::addEntity(new Entity("Play-Button"))
		->usePreset(Presets::button(window->renderer, "Play", FontManager::DEFAULT, [this] { startSinglePlayer(); }))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 1000}, {300, 100}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI);

	matchCodeInput = EcsManager::addEntity(new Entity("Match-Code-Input"))
		->apply(false)
		->usePreset(Presets::textinput(window->renderer, matchCode, FontManager::DEFAULT, sizeof(matchCode)-1))
	 	->getChild("Textinput.Text")
		->transform
	    ->apply({-120, 0, -10}, {0, 0}, {0.0f, 0.5f}, 0.0f, 0)
		->parent
		->addChild((new Entity("Textinput.Continue"))
			->addComponent(new Button(nullptr, [this] { joinServer(); }))
			->addComponent(new SpriteRenderer("res/menuarrow.png", window->renderer))
			->transform
			->apply({120, 0, -10}, {-300+40, -120+40}, {1.0f, 0.5f}, 0.0f, 0))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 870}, {300, 120}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI);
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
	delete settings;
	delete start;
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
				if (this->matchCode[0] == '\0')
				{
					startServer();
				}
				else
				{
					joinServer();
				}
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
		AnimationManager::play(Animations::swipeOut(settings, true), Easings::easeOut, 0.4);
		AnimationManager::play(Animations::fadeOut(settings), Easings::easeOut, 0.2);

		AnimationManager::play(Animations::swipeIn(start, false), Easings::easeOut, 0.4);
		AnimationManager::play(Animations::fadeIn(start), Easings::linear, 0.2);

		AnimationManager::play(Animations::swipeOut(matchCodeInput, true), Easings::easeOut, 0.4);
		AnimationManager::play(Animations::fadeOut(matchCodeInput), Easings::easeOut, 0.2);
	}

	if (this->currentGameMode == GameMode::MULTIPLAYER)
	{
		AnimationManager::play(Animations::swipeIn(settings, true), Easings::easeOut, 0.4);
		AnimationManager::play(Animations::fadeIn(settings), Easings::linear, 0.2);

		AnimationManager::play(Animations::swipeOut(start, false), Easings::easeOut, 0.4);
		AnimationManager::play(Animations::fadeOut(start), Easings::easeOut, 0.2);

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
	NetManager::on_match_found = [this](const char *match_code) {
		printf("Match found: %s\n", match_code);
		EcsManager::clear();
		Pane *pane = new LobbyPane(window, match_code);
		GameManager::switchScene(this, pane);
	};
	NetManager::on_match_not_found = [this]() {
		fprintf(stderr, "Match not found\n");
	};
	NetManager::init_matchmaking();
}

void HomePane::joinServer()
{
	NetManager::on_match_not_found = [this]() {
		fprintf(stderr, "Match not found\n");
	};
	NetManager::on_match_full = [this]() {
		fprintf(stderr, "Match full\n");
	};
	NetManager::on_punch_fail = [this]() {
		fprintf(stderr, "Punch failed\n");
	};
	NetManager::on_punched = [this](ENetPeer *enemy) {
		// TODO: Send client data (name, level, etc...)
		Buffer b;
		b.Write(Packet::PEER_ENEMY_DATA);
		ENetPacket *packet = enet_packet_create(b.GetBuffer(), b.GetSize(), ENET_PACKET_FLAG_RELIABLE);
		enet_peer_send(enemy, 0, packet);

		printf("Connected to %u:%u\n", enemy->address.host, enemy->address.port);
		EcsManager::clear();
		char* matchCode = (char*) malloc(6);
		strcpy(matchCode, this->matchCode);
		Pane *pane = new LobbyPane(window, matchCode);
		GameManager::switchScene(this, pane);
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
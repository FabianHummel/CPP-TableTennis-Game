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

#include "../components/bubbledrawer.h"
#include "../components/button.h"
#include "../components/menuballbehaviour.h"
#include "../components/menutitle.h"
#include "../components/spriterenderer.h"
#include "../utility/renderwindow.h"

HomePane::HomePane(SDL_Renderer *renderer) : Pane(renderer)
{
	title = EcsManager::addEntity(new Entity("Title"))
		->addComponent(new SpriteRenderer("res/title.png", renderer))
		->addComponent(new MenuTitle())
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 0}, {RenderWindow::SCREEN_WIDTH, 425}, {0.5f, 0.0f}, 0.0f, RenderIndexes::Menu::TITLE);

	background = EcsManager::addEntity(new Entity("Background"))
		->addComponent(new BubbleDrawer(renderer))
		->transform
		->apply({RenderWindow::SCREEN_HEIGHT, 0, 0}, {RenderWindow::SCREEN_WIDTH, RenderWindow::SCREEN_HEIGHT}, {0.5f, 0.5f}, -3.8, RenderIndexes::Menu::BACKGROUND);

	gamemode = EcsManager::addEntity(new Entity("Gamemode"))
		->addComponent(new TextRenderer(renderer, magic_enum::enum_name(GameMode::SINGLEPLAYER).data(), FontManager::DEFAULT, {40, 40, 40}))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 700}, {300, 100}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI);

	previous = EcsManager::addEntity(new Entity("Previous"))
		->addComponent(new Button(nullptr, [this] { previousGameMode(); }))
		->addComponent(new SpriteRenderer("res/menuarrow.png", renderer))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X - 200, 0, 700}, {40, 40}, {0.5f, 0.5f}, 180.0f, RenderIndexes::Menu::UI);

	next = EcsManager::addEntity(new Entity("Next"))
		->addComponent(new Button(nullptr, [this] { nextGameMode(); }))
		->addComponent(new SpriteRenderer("res/menuarrow.png", renderer))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X + 200, 0, 700}, {40, 40}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI);

	ball = EcsManager::addEntity(new Entity("Ball"))
		->addComponent(new SpriteRenderer("res/ball.png", renderer))
		->addComponent(new MenuBallBehaviour())
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 220}, {40, 40}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::BALL);

	menuline = EcsManager::addEntity(new Entity("Menuline"))
		->addComponent(new SpriteRenderer("res/menuline.png", renderer))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 650}, {300, 6}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI);

	start = EcsManager::addEntity(new Entity("Play-Button"))
		->usePreset(Presets::button(renderer, "Play", FontManager::DEFAULT, [this] { startSinglePlayer(); }))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 1000}, {300, 100}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI);

	playerNameInput = EcsManager::addEntity(new Entity("Player-Name-Input"))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 870}, {300, 120}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI)
		->apply(false)
		->usePreset(Presets::textinput(renderer, playerName, FontManager::DEFAULT, sizeof(playerName)-1));

	matchCodeInput = EcsManager::addEntity(new Entity("Match-Code-Input"))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 1000}, {300, 120}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI)
		->apply(false)
		->usePreset(Presets::textinput(renderer, matchCode, FontManager::DEFAULT, sizeof(matchCode)-1))
		->addChild((new Entity("Continue"))
			->addComponent(new Button(nullptr, [this] { startOrJoinServer(); }))
			->addComponent(new SpriteRenderer("res/menuarrow.png", renderer))
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

void HomePane::onEvent(const SDL_Event *event)
{
	switch (event->type)
	{
	case SDL_EVENT_KEY_DOWN:
		switch (event->key.key)
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
		SDL_LogInfo(SDL_LOG_CATEGORY_APPLICATION, "Match found: %s\n", matchCode);
		EcsManager::clear();
		Pane *lobby = new LobbyPane(renderer, matchCode, playerName);
		GameManager::switchScene(this, lobby);
	};
	NetManager::on_match_not_found = [] {
		SDL_LogWarn(SDL_LOG_CATEGORY_APPLICATION, "Match not found\n");
	};
	NetManager::init_matchmaking();
}

void HomePane::joinServer()
{
	EcsManager::clear();
	Pane *lobby = new LobbyPane(renderer, this->matchCode, this->playerName);
	NetManager::join_match(this->matchCode);
	GameManager::switchScene(this, lobby);
}

void HomePane::startSinglePlayer()
{
	EcsManager::clear();
	Pane *pane = new GamePane(renderer);
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
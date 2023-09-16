#include "home.h"
#include "../ecs/ecsmanager.h"
#include "../ecs/presets/index.h"
#include "../game/gamemanager.h"
#include "../render/renderindexes.h"
#include "../animations/animationmanager.h"
#include "game.h"
#include <functional>

Entity *title;
Entity *background;
Entity *gamemode;
Entity *previous;
Entity *next;
Entity *ball;
Entity *menuline;
Entity *settings;
Entity *start;

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
//	    ->addComponent(new Button(nullptr, [this] { startGame(); }))
		->addComponent(new TextRenderer(window->renderer, magic_enum::enum_name(GameMode::SINGLEPLAYER).data(), {40, 40, 40}))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 800}, {300, 100}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI);

	previous = EcsManager::addEntity(new Entity("Previous"))
		->addComponent(new Button(nullptr, [this] { previousGameMode(); }))
		->addComponent(new SpriteRenderer("res/menuarrow.png", window->renderer))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X - 200, 0, 800}, {40, 40}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI);

	next = EcsManager::addEntity(new Entity("Next"))
		->addComponent(new Button(nullptr, [this] { nextGameMode(); }))
		->addComponent(new SpriteRenderer("res/menuarrow.png", window->renderer))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X + 200, 0, 800}, {40, 40}, {0.5f, 0.5f}, 180.0f, RenderIndexes::Menu::UI);

	ball = EcsManager::addEntity(new Entity("Ball"))
		->addComponent(new SpriteRenderer("res/ball.png", window->renderer))
		->addComponent(new MenuBallBehaviour())
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 320}, {40, 40}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::BALL);

	menuline = EcsManager::addEntity(new Entity("Menuline"))
		->addComponent(new SpriteRenderer("res/menuline.png", window->renderer))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 750}, {300, 6}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI);

	settings = EcsManager::addEntity(new Entity("Start-Server-Button"))
	    ->apply(false)
	    ->usePreset(Presets::button(window->renderer, "Start server", [] { printf("Starting server...\n"); }))
	    ->transform
	    ->apply({RenderWindow::SCREEN_CENTER_X, 0, 1000}, {300, 100}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI);

	start = EcsManager::addEntity(new Entity("Play-Button"))
		->usePreset(Presets::button(window->renderer, "Play", [this] { startGame(); }))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, 1000}, {200, 100}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Menu::UI);
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
			startGame();
			break;
		}
	}
}

void HomePane::dispose()
{
	delete title;
	delete background;
	delete gamemode;
	delete previous;
	delete next;
	delete ball;
	delete menuline;
	delete settings;
	delete start;
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
	}

	if (this->currentGameMode == GameMode::MULTIPLAYER)
	{
		AnimationManager::play(Animations::swipeIn(settings, true), Easings::easeOut, 0.4);
		AnimationManager::play(Animations::fadeIn(settings), Easings::linear, 0.2);

		AnimationManager::play(Animations::swipeOut(start, false), Easings::easeOut, 0.4);
		AnimationManager::play(Animations::fadeOut(start), Easings::easeOut, 0.2);
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

void HomePane::startGame()
{
	EcsManager::clear();
	Pane *pane;
	switch (currentGameMode)
	{
	case GameMode::SINGLEPLAYER:
		pane = new GamePane(window);
		break;
	case GameMode::MULTIPLAYER:
		pane = new GamePane(window);
		break;
	}

	GameManager::switchScene(this, pane);
}

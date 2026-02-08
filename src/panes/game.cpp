#include "game.h"
#include "../ecsmanager.h"
#include "../utility/renderindexes.h"
#include "../components/index.h"

GamePane::GamePane(RenderWindow *window) : Pane(window)
{
	table = EcsManager::addEntity(new Entity("Table"))
		->transform
		->apply({0, 0, 0}, {RenderWindow::SCREEN_WIDTH, RenderWindow::SCREEN_HEIGHT}, {0.0f, 0.0f}, 0.0f, RenderIndexes::Game::TABLE)
		->addComponent(new SpriteRenderer("res/table.png", window->renderer));

	net = EcsManager::addEntity(new Entity("Net"))
		->transform
		->apply({RenderWindow::SCREEN_CENTER_X, 0, RenderWindow::SCREEN_CENTER_Y - 100}, {RenderWindow::SCREEN_WIDTH, 129}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Game::NET)
		->addComponent(new SpriteRenderer("res/net.png", window->renderer));

	shadow = EcsManager::addEntity(new Entity("Shadow"))
		->transform
		->apply({0, 0, 0}, {40, 40}, {0.5f, 0.0f}, 0.0f, RenderIndexes::Game::DEFAULT)
		->addComponent(new SpriteRenderer("res/shadow.png", window->renderer));

	ball = EcsManager::addEntity(new Entity("Ball"))
		->transform
		->apply({0, 0, 0}, {40, 40}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Game::DEFAULT)
		->addComponent(new SpriteRenderer("res/ball.png", window->renderer))
		->addComponent(new BallMovement())
		->addComponent(new ShadowTransformer(shadow));

	indicator = EcsManager::addEntity(new Entity("Indicator"))
		->transform
		->apply({0, 0, 0}, {112, 112}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Game::UI + 1)
		->addComponent(new SpriteRenderer("res/indicator.png", window->renderer));

	powerbar = EcsManager::addEntity(new Entity("Powerbar"))
		->transform
		->apply({0, 0, 0}, {70, 70}, {0.5f, 1.0f}, 0.0f, RenderIndexes::Game::UI + 0)
		->addComponent(new SpriteRenderer("res/powerbar.png", window->renderer))
		->addComponent(new Powerbar());

	powerbox = EcsManager::addEntity(new Entity("Powerbox"))
		->transform
		->apply({0, 0, 0}, {70, 70}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Game::UI + 1)
		->addComponent(new SpriteRenderer("res/powerbox.png", window->renderer));

	prediction = EcsManager::addEntity(new Entity("Prediction"))
		->transform
		->apply({0, 0, 0}, {RenderWindow::SCREEN_WIDTH, RenderWindow::SCREEN_HEIGHT}, {0.0f, 0.0f}, 0.0f, RenderIndexes::Game::PREDICTION)
		->addComponent(new Prediction("res/predictionsegment.png", window->renderer));
}

GamePane::~GamePane()
{
	delete table;
	delete net;
	delete ball;
	delete shadow;
	delete indicator;
	delete powerbar;
	delete powerbox;
	delete prediction;
}

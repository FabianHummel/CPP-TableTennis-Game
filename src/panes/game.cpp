#include "game.h"
#include "../ecs/ecsmanager.h"
#include "../render/renderindexes.h"

GamePane::GamePane(RenderWindow *window) : Pane(window)
{
	table = (new Entity("Table"))
	  ->addComponent(new SpriteRenderer("res/table.png", window->renderer))
	  ->getTransform()
	  ->apply({0, 0, 0}, {RenderWindow::SCREEN_WIDTH, RenderWindow::SCREEN_HEIGHT}, {0.0f, 0.0f}, 0.0f, RenderIndexes::Game::TABLE);

	net = (new Entity("Net"))
		->addComponent(new SpriteRenderer("res/net.png", window->renderer))
		->getTransform()
		->apply({RenderWindow::SCREEN_CENTER_X, 0, RenderWindow::SCREEN_CENTER_Y - 100},
		        {RenderWindow::SCREEN_WIDTH, 129}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Game::NET);

	shadow = (new Entity("Shadow"))
	  ->getTransform()
		->apply({0, 0, 0}, {40, 40}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Game::DEFAULT)
  	->addComponent(new SpriteRenderer("res/shadow.png", window->renderer));

	ball = (new Entity("Ball"))
		->getTransform()
		->apply({0, 0, 0}, {40, 40}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Game::DEFAULT)
		->addComponent(new SpriteRenderer("res/ball.png", window->renderer))
		->addComponent(new BallMovement())
		->addComponent(new ShadowTransformer(shadow));

	indicator = (new Entity("Indicator"))
		->getTransform()
		->apply({0, 0, 0}, {112, 112}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Game::UI + 1)
		->addComponent(new SpriteRenderer("res/indicator.png", window->renderer));

	powerbar = (new Entity("Powerbar"))
		->getTransform()
		->apply({0, 0, 0}, {70, 70}, {0.5f, 1.0f}, 0.0f, RenderIndexes::Game::UI + 0)
		->addComponent(new SpriteRenderer("res/powerbar.png", window->renderer))
		->addComponent(new Powerbar());

	powerbox = (new Entity("Powerbox"))
		->getTransform()
		->apply({0, 0, 0}, {70, 70}, {0.5f, 0.5f}, 0.0f, RenderIndexes::Game::UI + 1)
		->addComponent(new SpriteRenderer("res/powerbox.png", window->renderer));

	prediction = (new Entity("Prediction"))
		->addComponent(new Prediction("res/predictionsegment.png", window->renderer))
		->getTransform()
		->apply({0, 0, 0}, {RenderWindow::SCREEN_WIDTH, RenderWindow::SCREEN_HEIGHT}, {0.0f, 0.0f}, 0.0f, RenderIndexes::Game::PREDICTION);
}

void GamePane::dispose()
{
	delete global;
	delete table;
	delete net;
	delete ball;
	delete shadow;
	delete indicator;
	delete powerbar;
	delete powerbox;
	delete prediction;
}

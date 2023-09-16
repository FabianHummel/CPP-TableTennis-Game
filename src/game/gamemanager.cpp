#include "gamemanager.h"
#include "../ecs/ecsmanager.h"
#include <cstdlib>

namespace GameManager
{
	Pane *currentPane = {};

	void nextRound()
	{
		Entity *ball = EcsManager::findEntity("Ball");
		Transform *transform = ball->getComponent<Transform>();
		transform->setPosition({RenderWindow::SCREEN_CENTER_X, 10, 650});

		BallMovement *ballMovement = ball->getComponent<BallMovement>();
		ballMovement->idle = true;
		ballMovement->setForce({0, 8, 0});
	}

	void switchScene(Pane *from, Pane *to)
	{

		if (from != nullptr)
		{
			from->dispose();
			delete from;
		}

		if (to == nullptr)
		{
			exit(EXIT_FAILURE);
		}

		currentPane = to;
		EcsManager::initialize();
		EcsManager::start();
	}
}

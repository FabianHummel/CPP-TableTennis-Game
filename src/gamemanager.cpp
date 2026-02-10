#include "gamemanager.h"
#include "ecsmanager.h"
#include <cstdlib>

#include "components/index.h"
#include "utility/renderwindow.h"

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
		delete from;

		if (to == nullptr)
		{
			exit(EXIT_FAILURE);
		}

		currentPane = to;
		EcsManager::initialize();
		GameManager::currentPane->onStart();
		EcsManager::start();
	}
}

#include "gamemanager.h"
#include "ecsmanager.h"
#include "components/ballmovement.h"
#include "components/transform.h"
#include "utility/renderwindow.h"

namespace GameManager
{
	Pane *currentPane = {};

	void nextRound()
	{
		Entity *ball = EcsManager::findEntity("Ball");
		Transform *transform = ball->getComponent<Transform>();
		transform->position = {RenderWindow::SCREEN_CENTER_X, 10, 650};

		BallMovement *ballMovement = ball->getComponent<BallMovement>();
		ballMovement->idle = true;
		ballMovement->velocity = {0, 8, 0};
	}

	void switchScene(const Pane *from, Pane *to)
	{
		delete from;

		currentPane = to;
		EcsManager::initialize();
		currentPane->onStart();
		EcsManager::start();
	}
}

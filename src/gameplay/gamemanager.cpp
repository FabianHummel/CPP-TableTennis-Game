//
// Created by Fabian Hummel on 14.06.22.
//

#include "gamemanager.h"
#include "../entity/entitymanager.h"
#include "../components/transform.h"
#include "../components/ballmovement.h"
#include "../render/renderwindow.h"

void GameManager::nextRound() {
	Entity *ball = EntityManager::findEntity("Ball");
	Transform *transform = ball->getComponent<Transform>();
	transform->setPosition({ RenderWindow::SCREEN_CENTER_X, 10, 650 });

	BallMovement *ballMovement = ball->getComponent<BallMovement>();
	ballMovement->setIdle();
	ballMovement->setForce({ 0, 8, 0 });
}

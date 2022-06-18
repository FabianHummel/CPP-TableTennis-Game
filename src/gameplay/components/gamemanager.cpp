//
// Created by Fabian Hummel on 14.06.22.
//

#include "gamemanager.h"
#include "../../entity/entitymanager.h"
#include "transform.h"
#include "ballmovement.h"
#include "../../render/renderwindow.h"

void GameManager::onInitialize() {
	printf("Initializing Game Manager on %s\n", parent->getName());
}

void GameManager::onStart() {}

void GameManager::onUpdate(double deltaTime) {}

void GameManager::nextRound(bool side) {
	Entity *ball = EntityManager::findEntity("Ball");

	auto transform = ball->getComponent<Transform>();
	transform->setPosition({ RenderWindow::SCREEN_CENTER_X, 10, 650 });

	auto ballMovement = ball->getComponent<BallMovement>();
	ballMovement->setIdle();
	ballMovement->setForce({ 0, 8, 0 });
}
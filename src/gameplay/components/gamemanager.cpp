//
// Created by Fabian Hummel on 14.06.22.
//

#include "gamemanager.h"
#include "../../entity/entitymanager.h"
#include "transform.h"
#include "ballmovement.h"
#include "../../render/renderwindow.h"

void GameManager::onInitialize() {}

void GameManager::onStart() {}

void GameManager::onUpdate() {}

void GameManager::nextRound(bool side) {
	Entity *ball = EntityManager::findEntity("Ball");

	auto transform = ball->getComponent<Transform>();
	transform->setPosition({ (float) RenderWindow::trueCenterX(transform->getScaleX()), 10, 650 });

	auto ballMovement = ball->getComponent<BallMovement>();
	ballMovement->setIdle();
	ballMovement->setForce({ 0, 8, 0 });
}
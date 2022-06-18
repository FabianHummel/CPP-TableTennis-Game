//
// Created by Fabian Hummel on 15.06.22.
//

#include "clickmanager.h"
#include "../../entity/entitymanager.h"
#include <cmath>
#include <SDL.h>

void ClickManager::onInitialize() {
	printf("Initializing Click Manager on %s\n", parent->getName());

	indicator = EntityManager::findEntity("Indicator")->getComponent<Transform>();
	indicatorSprite = EntityManager::findEntity("Indicator")->getComponent<SpriteRenderer>();
	ball = EntityManager::findEntity("Ball")->getComponent<BallMovement>();

	Entity *powerboxEntity = EntityManager::findEntity("Powerbox");
	powerbox = powerboxEntity->getComponent<Transform>();
	powerboxSprite = powerboxEntity->getComponent<SpriteRenderer>();

	Entity *powerbarEntity = EntityManager::findEntity("Powerbar");
	powerbar = powerbarEntity->getComponent<Transform>();
	powerbarSprite = powerbarEntity->getComponent<SpriteRenderer>();
	powerbarBehavior = powerbarEntity->getComponent<Powerbar>();
}

void ClickManager::onStart() {
	indicatorSprite->setVisible(false);
	powerboxSprite->setVisible(false);
	powerbarSprite->setVisible(false);

	indicator->setAnchor({
		 indicator->getScaleX() / 2, 0
	 });
}

void ClickManager::onUpdate(double deltaTime) {}

void ClickManager::onClick(int x, int y) {
	isDragging = true;
	startX = x;
	startY = y;
	// printf("began mouse drag at: %d, %d\n", startX, startY);

	indicator->setPosition({
		startX - indicator->getScaleX() / 2.0f, 0,
		(float) startY
	});
	powerbox->setPosition({
		startX - 140.0f, 0,
		startY - powerbox->getScaleY() / 2.0f
	});
	powerbar->setPosition({
		startX - 140.0f, 0,
		startY - powerbar->getScaleY() / 2.0f
	});
}

void ClickManager::onRelease() {
	indicatorSprite->setVisible(false);
	powerboxSprite->setVisible(false);
	powerbarSprite->setVisible(false);

	isDragging = false;
	// printf("ended mouse drag at: %d, %d, ", currentX, currentY);
	// printf("with a delta of: %d, %d ", deltaX, deltaY);
	// printf("and an angle of: %d°\n", angle);

	if (strength > 0.1f) {
		ball->setActive();
		ball->setForce({
			( float ) -deltaX / strength * 0.03f,
			ball->getForce().y * strength * 2.0f + 1.0f,
			( float ) -deltaY / strength * 0.03f
		});
	}

	strength = 0.0f;
}

void ClickManager::onDrag(int x, int y) {
	if (isDragging) {
		indicatorSprite->setVisible(true);
		powerboxSprite->setVisible(true);
		powerbarSprite->setVisible(true);

		currentX = x;
		currentY = y;

		deltaX = currentX - startX;
		deltaY = currentY - startY;

		angle = 180 - (int) ( atan2(deltaX, deltaY) * 180 / M_PI );
		indicator->setRotation(
			(float) angle
		);

		strength = std::clamp(
			(float) sqrt(deltaX * deltaX + deltaY * deltaY) / 200.0f, 0.0f, 1.0f
		);

		powerbarBehavior->setProgress(
			strength * 100.0f, startY
		);
	}
}
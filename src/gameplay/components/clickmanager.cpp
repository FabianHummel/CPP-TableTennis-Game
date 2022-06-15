//
// Created by Fabian Hummel on 15.06.22.
//

#include "clickmanager.h"
#include "../../entity/entitymanager.h"
#include <cmath>
#include <SDL.h>

void ClickManager::onInitialize() {
	indicator = EntityManager::findEntity("Indicator")->getComponent<Transform>();
	sprite = EntityManager::findEntity("Indicator")->getComponent<SpriteRenderer>();
	ball = EntityManager::findEntity("Ball")->getComponent<BallMovement>();
}

void ClickManager::onStart() {
	sprite->setVisible(false);
	indicator->setAnchor({
		 indicator->getScaleX() / 2, 0
	 });
}

void ClickManager::onUpdate() {
	indicator->setPosition({
	   startX - (float) indicator->getScaleX() / 2, 0, (float) startY
	});
}

void ClickManager::onClick(int x, int y) {
	isDragging = true;
	startX = x;
	startY = y;
	printf("began mouse drag at: %d, %d\n", startX, startY);
}

void ClickManager::onRelease() {
	sprite->setVisible(false);
	isDragging = false;
	printf("ended mouse drag at: %d, %d, ", currentX, currentY);
	printf("with a delta of: %d, %d ", deltaX, deltaY);
	printf("and an angle of: %d°\n", angle);

	ball->setActive();
	ball->setForce({
		( float ) -deltaX * 0.03f,
		ball->getForce().y,
		( float ) -deltaY * 0.03f
	});
}

void ClickManager::onDrag(int x, int y) {
	if (isDragging) {
		sprite->setVisible(true);
		currentX = x;
		currentY = y;

		deltaX = currentX - startX;
		deltaY = currentY - startY;

		angle = 180 - (int) ( atan2(deltaX, deltaY) * 180 / M_PI );
		indicator->setRotation(
			(float) angle
		);
	}
}
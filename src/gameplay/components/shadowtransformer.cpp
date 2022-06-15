//
// Created by Fabian Hummel on 12.06.22.
//

#include "shadowtransformer.h"
#include "../../entity/entitymanager.h"

void ShadowTransformer::onInitialize() {
	Entity *ballEntity = EntityManager::findEntity("Ball");
	this->ball = ballEntity->getComponent<Transform>();
	this->ballMovement = ballEntity->getComponent<BallMovement>();

	this->shadow = parent->getComponent<Transform>();
	this->sprite = parent->getComponent<SpriteRenderer>();
}

void ShadowTransformer::onStart() {

}

void ShadowTransformer::onUpdate() {
	shadow->setX(ball->getX() + ball->getY());
	shadow->setY((float) -shadow->getScaleX() / 2);
	shadow->setZ(ball->getZ());

	if (ballMovement->inTableBounds()) {
		sprite->setOpacity(SDL_ALPHA_OPAQUE);
	} else {
		sprite->setOpacity(SDL_ALPHA_TRANSPARENT);
	}
}
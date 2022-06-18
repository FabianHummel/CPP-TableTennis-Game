//
// Created by Fabian Hummel on 12.06.22.
//

#include "shadowtransformer.h"
#include "../../entity/entitymanager.h"

void ShadowTransformer::onInitialize() {
	printf("Initializing Shadow Transformer on %s\n", parent->getName());
	Entity *ballEntity = EntityManager::findEntity("Ball");
	this->ball = ballEntity->getComponent<Transform>();

	this->shadow = parent->getComponent<Transform>();
	this->sprite = parent->getComponent<SpriteRenderer>();
}

void ShadowTransformer::onStart() {}

void ShadowTransformer::onUpdate(double deltaTime) {
	//TODO: Push new values instead of pulling them! (Prevent lag behind)
	shadow->setX(ball->getX() + ball->getY());
	shadow->setY((float) -shadow->getScaleX() / 2);
	shadow->setZ(ball->getZ());

	if (shadow->inTableBounds()) {
		sprite->setOpacity(SDL_ALPHA_OPAQUE);
	} else {
		sprite->setOpacity(SDL_ALPHA_TRANSPARENT);
	}
}
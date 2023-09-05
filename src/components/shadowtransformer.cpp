//
// Created by Fabian Hummel on 12.06.22.
//

#include "shadowtransformer.h"
#include "spriterenderer.h"

ShadowTransformer::ShadowTransformer(Entity *shadow)
{
	this->target = shadow;
}

void ShadowTransformer::onInitialize()
{
	printf("Initializing Shadow Transformer on %s\n", parent->getName());
	this->ball = parent->getComponent<Transform>();
	this->transform = target->getComponent<Transform>();
	this->sprite = target->getComponent<SpriteRenderer>();
}

void ShadowTransformer::onUpdate(double deltaTime)
{
	// TODO: Push new values instead of pulling them! (Prevent lag behind)
	transform->setX(ball->getX() + ball->getY());
	transform->setY((float)-transform->getScaleY() / 2);
	transform->setZ(ball->getZ());
	transform->setI(ball->getI() - 1);

	if (transform->inTableBounds())
	{
		sprite->setOpacity(SDL_ALPHA_OPAQUE);
	}
	else
	{
		sprite->setOpacity(SDL_ALPHA_TRANSPARENT);
	}
}

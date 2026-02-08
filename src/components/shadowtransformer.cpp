#include "shadowtransformer.h"
#include "spriterenderer.h"

ShadowTransformer::ShadowTransformer(Entity *shadow)
{
	this->target = shadow;
}

void ShadowTransformer::onInitialize()
{
	printf("Initializing Shadow Transformer on %s\n", parent->name);
	this->ball = parent->getComponent<Transform>();
	this->transform = target->getComponent<Transform>();
}

void ShadowTransformer::onUpdate(double deltaTime)
{
	// TODO: Push new values instead of pulling them! (Prevent lag behind)
	transform->setX(ball->getX() + ball->getY());
	transform->setZ(ball->getZ());
	transform->setI(ball->getI() - 1);

	if (transform->inTableBounds())
	{
		target->opacity = SDL_ALPHA_OPAQUE;
	}
	else
	{
		target->opacity = SDL_ALPHA_TRANSPARENT;
	}
}

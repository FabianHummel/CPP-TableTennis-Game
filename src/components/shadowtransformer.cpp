#include "shadowtransformer.h"
#include "spriterenderer.h"

ShadowTransformer::ShadowTransformer(Entity *shadow)
{
	this->name = "Shadow Transformer";
	this->target = shadow;
}

void ShadowTransformer::onInitialize()
{
	this->ball = parent->getComponent<Transform>();
	this->transform = target->getComponent<Transform>();
}

void ShadowTransformer::onUpdate(double deltaTime)
{
	// TODO: Push new values instead of pulling them! (Prevent lag behind)
	transform->position.x = ball->position.x + ball->position.y;
	transform->position.z = ball->position.z;
	transform->zIndex = ball->zIndex - 1;

	if (transform->inTableBounds())
	{
		target->opacity = SDL_ALPHA_OPAQUE;
	}
	else
	{
		target->opacity = SDL_ALPHA_TRANSPARENT;
	}
}

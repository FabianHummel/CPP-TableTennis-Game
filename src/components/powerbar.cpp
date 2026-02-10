#include "powerbar.h"
#include "../ecsmanager.h"
#include "ballmovement.h"
#include "prediction.h"
#include "spriterenderer.h"
#include <cstdio>

void Powerbar::onInitialize()
{
	printf("Initializing Powerbar Behavior on %s\n", parent->name);

	indicator = EcsManager::findEntity("Indicator")->getComponent<Transform>();
	indicatorSprite = EcsManager::findEntity("Indicator")->getComponent<SpriteRenderer>();
	ball = EcsManager::findEntity("Ball")->getComponent<BallMovement>();

	Entity *powerboxEntity = EcsManager::findEntity("Powerbox");
	powerbox = powerboxEntity->getComponent<Transform>();
	powerboxSprite = powerboxEntity->getComponent<SpriteRenderer>();

	Entity *powerbarEntity = EcsManager::findEntity("Powerbar");
	powerbar = powerbarEntity->getComponent<Transform>();
	powerbarSprite = powerbarEntity->getComponent<SpriteRenderer>();

	Entity *predictionEntity = EcsManager::findEntity("Prediction");
	prediction = predictionEntity->getComponent<Prediction>();
}

void Powerbar::onEvent(const SDL_Event *event)
{
	switch (event->type)
	{
	case SDL_EVENT_MOUSE_BUTTON_DOWN: {
		float x, y;
		SDL_GetMouseState(&x, &y);
		onClick(x * 2, y * 2);
		break;
	}

	case SDL_EVENT_MOUSE_BUTTON_UP: {
		onRelease();
		break;
	}

	case SDL_EVENT_MOUSE_MOTION: {
		float x, y;
		SDL_GetMouseState(&x, &y);
		onDrag(x * 2, y * 2);
		break;
	}
	}
}

void Powerbar::setProgress(float v, float y)
{
	this->size = v;

	float progress = size / 100.0f * 250;
	powerbarSprite->setSrcrect({0, 250.0f - progress, 250, progress});

	powerbar->setScaleY(size / 100.0f * 70);
}

void Powerbar::onStart()
{
	indicatorSprite->visible = false;
	powerboxSprite->visible = false;
	powerbarSprite->visible = false;
}

void Powerbar::onUpdate(double deltaTime)
{
	if (isDragging)
	{
		Vector3 force = calcForce();
		prediction->onPredict(force);
	}
}

Vector3 Powerbar::calcForce()
{
	double length = sqrt(deltaX * deltaX + deltaY * deltaY);
	double forceX = -(double)deltaX / length * strength * 7.0;
	double forceY = -(double)deltaY / length * strength * 7.0;
	return {(float)forceX, 8.f, (float)forceY};
}

void Powerbar::onClick(float x, float y)
{
	isDragging = true;
	startX = x;
	startY = y;
	// printf("began mouse drag at: %d, %d\n", startX, startY);

	indicator->setPosition({startX, 0.0f, startY});
	powerbox->setPosition({startX - 100.0f, 0.0f, startY});
	powerbar->setPosition({startX - 100.0f, 0.0f, startY + powerbox->getScaleY() / 2.0f});
}

void Powerbar::onRelease()
{
	indicatorSprite->visible = false;
	powerboxSprite->visible = false;
	powerbarSprite->visible = false;

	isDragging = false;
	// printf("ended mouse drag at: %d, %d, ", currentX, currentY);
	// printf("with a delta of: %d, %d ", deltaX, deltaY);
	// printf("and an angle of: %d°\n", angle);

	if (strength > 0.1f && ball->parent->transform->getY() > -10.0f)
	{
		ball->idle = false;

		Vector3 force = calcForce();
		ball->setForce(force);
	}

	strength = 0.0f;
}

void Powerbar::onDrag(float x, float y)
{
	if (isDragging)
	{
		indicatorSprite->visible = true;
		powerboxSprite->visible = true;
		powerbarSprite->visible = true;

		float currentX = x;
		float currentY = y;

		deltaX = currentX - startX;
		deltaY = currentY - startY;

		float angle = 180.0f - atan2(deltaX, deltaY) * 180 / M_PI;
		indicator->setRotation(angle);

		strength = std::clamp(sqrt(deltaX * deltaX + deltaY * deltaY) / 200.0f, 0.0f, 1.0f);
		setProgress(strength * 100.0f, startY);
	}
}

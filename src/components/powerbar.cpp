#include "powerbar.h"
#include "../ecsmanager.h"
#include "ballmovement.h"
#include "prediction.h"
#include "spriterenderer.h"
#include <cstdio>

PowerBar::PowerBar()
{
	this->name = "Power Bar";
}

void PowerBar::onInitialize()
{
	indicator = EcsManager::findEntity("Indicator")->getComponent<Transform>();
	indicatorSprite = EcsManager::findEntity("Indicator")->getComponent<SpriteRenderer>();
	ball = EcsManager::findEntity("Ball")->getComponent<BallMovement>();

	Entity *powerboxEntity = EcsManager::findEntity("Powerbox");
	powerbox = powerboxEntity->getComponent<Transform>();
	powerboxSprite = powerboxEntity->getComponent<SpriteRenderer>();

	Entity *powerbarEntity = EcsManager::findEntity("PowerBar");
	powerbar = powerbarEntity->getComponent<Transform>();
	powerbarSprite = powerbarEntity->getComponent<SpriteRenderer>();

	Entity *predictionEntity = EcsManager::findEntity("Prediction");
	prediction = predictionEntity->getComponent<Prediction>();
}

void PowerBar::onEvent(const SDL_Event *event)
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

void PowerBar::setProgress(float v, float y)
{
	this->size = v;

	const float progress = size / 100.0f * 250;
	powerbarSprite->setSrcrect({0, 250.0f - progress, 250, progress});

	powerbar->scale.y = size / 100.0f * 70;
}

void PowerBar::onStart()
{
	indicatorSprite->visible = false;
	powerboxSprite->visible = false;
	powerbarSprite->visible = false;
}

void PowerBar::onUpdate(double deltaTime)
{
	if (isDragging)
	{
		const Vector3 force = calcForce();
		prediction->onPredict(force);
	}
}

Vector3 PowerBar::calcForce() const
{
	const double length = sqrt(deltaX * deltaX + deltaY * deltaY);
	const double forceX = -(double)deltaX / length * strength * 7.0;
	const double forceY = -(double)deltaY / length * strength * 7.0;
	return {(float)forceX, 8.f, (float)forceY};
}

void PowerBar::onClick(float x, float y)
{
	isDragging = true;
	startX = x;
	startY = y;
	// printf("began mouse drag at: %d, %d\n", startX, startY);

	indicator->position = {startX, 0.0f, startY};
	powerbox->position = {startX - 100.0f, 0.0f, startY};
	powerbar->position = {startX - 100.0f, 0.0f, startY + powerbox->scale.y / 2.0f};
}

void PowerBar::onRelease()
{
	indicatorSprite->visible = false;
	powerboxSprite->visible = false;
	powerbarSprite->visible = false;

	isDragging = false;
	// printf("ended mouse drag at: %d, %d, ", currentX, currentY);
	// printf("with a delta of: %d, %d ", deltaX, deltaY);
	// printf("and an angle of: %d°\n", angle);

	if (strength > 0.1f && ball->parent->transform->scale.y > -10.0f)
	{
		ball->idle = false;

		const Vector3 force = calcForce();
		ball->velocity = force;
	}

	strength = 0.0f;
}

void PowerBar::onDrag(float x, float y)
{
	if (isDragging)
	{
		indicatorSprite->visible = true;
		powerboxSprite->visible = true;
		powerbarSprite->visible = true;

		const float currentX = x;
		const float currentY = y;

		deltaX = currentX - startX;
		deltaY = currentY - startY;

		const float angle = 180.0f - atan2(deltaX, deltaY) * 180.0f / (float)M_PI;
		indicator->rotation = angle;

		strength = std::clamp(sqrt(deltaX * deltaX + deltaY * deltaY) / 200.0f, 0.0f, 1.0f);
		setProgress(strength * 100.0f, startY);
	}
}

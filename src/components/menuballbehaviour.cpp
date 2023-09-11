#include "menuballbehaviour.h"
#include <cmath>

float initialPosition;

void MenuBallBehaviour::onInitialize()
{
	this->transform = this->parent->getTransform();
	initialPosition = transform->getZ();
}

double f(double x)
{
	return (x-2)*(x-2)+4;
}

void MenuBallBehaviour::onUpdate(double deltaTime)
{
	time += deltaTime;
	this->transform->setZ(initialPosition + HEIGHT * (float)f(fmod(time * SPEED, 4)));
}
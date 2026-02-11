#include "menuballbehaviour.h"
#include <cmath>

double initialPosition;

MenuBallBehaviour::MenuBallBehaviour()
{
	this->name = "Menu Ball Behaviour";
}

void MenuBallBehaviour::onInitialize()
{
	this->transform = this->parent->transform;
	initialPosition = transform->position.z;
}

double height(const double x)
{
	return (x-2)*(x-2)+4;
}

void MenuBallBehaviour::onUpdate(const double deltaTime)
{
	time += deltaTime;
	this->transform->position.z = initialPosition + HEIGHT * height(fmod(time * SPEED, 4));
}
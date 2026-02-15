#include "menutitle.h"

MenuTitle::MenuTitle() : MenuTitle(0.0)
{
}

MenuTitle::MenuTitle(const double timeOffset)
{
	this->name = "Menu Title";
	this->time = timeOffset;
}

void MenuTitle::onInitialize()
{
	transform = parent->transform;
	initialPosition = transform->position.z;
}

void MenuTitle::onUpdate(double deltaTime)
{
	time += deltaTime;
	transform->position.z = initialPosition + 15 * sin(time * SPEED);
}

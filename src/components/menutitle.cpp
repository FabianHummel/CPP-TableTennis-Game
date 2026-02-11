#include "menutitle.h"

MenuTitle::MenuTitle()
{
	this->name = "Menu Title";
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

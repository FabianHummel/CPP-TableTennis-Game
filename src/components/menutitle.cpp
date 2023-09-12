#include "menutitle.h"

void MenuTitle::onInitialize()
{
	transform = parent->transform;
	initialPosition = transform->getZ();
}

void MenuTitle::onUpdate(double deltaTime)
{
	time += deltaTime;
	transform->setZ(initialPosition + 15 * sin(time * MenuTitle::SPEED));
}

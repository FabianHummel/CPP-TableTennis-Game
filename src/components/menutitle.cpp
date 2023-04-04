#include "menutitle.h"
#include <cstdio>
#include <ctime>

void MenuTitle::onInitialize() {
  transform = parent->getTransform();
  initialPosition = transform->getZ();
}

void MenuTitle::onUpdate(double deltaTime) {
  time += deltaTime;
  transform->setZ(initialPosition + 15 * sin(time * MenuTitle::SPEED));
}

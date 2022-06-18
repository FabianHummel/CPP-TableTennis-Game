//
// Created by Fabian Hummel on 16.06.22.
//

#include "powerbar.h"

void Powerbar::onInitialize() {
	sprite = parent->getComponent<SpriteRenderer>();
	bar = parent->getComponent<Transform>();
}

void Powerbar::onStart() {}

void Powerbar::onUpdate() {}

void Powerbar::setProgress(float v, float y) {
	this->size = v;

	int progress = size / 100.0f * 250;
	sprite->setSrcrect(
		{ 0, 250-progress, 250, progress }
	);

	bar->setScaleY(size / 100.0f * 70);
	bar->setZ(y - size / 100.0f * 70 / 2);
}
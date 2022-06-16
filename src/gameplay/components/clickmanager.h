//
// Created by Fabian Hummel on 15.06.22.
//

#pragma once

#include "../component.h"
#include "transform.h"
#include "spriterenderer.h"
#include "ballmovement.h"
#include "powerbar.h"

class ClickManager : public Component {
private:
	bool isDragging = false;
	int startX = 0, startY = 0;
	int currentX = 0, currentY = 0;
	int deltaX = 0, deltaY = 0;
	int angle = 0;

	float strength = 0;

	BallMovement *ball;

	Transform *indicator;
	SpriteRenderer *indicatorSprite;

	Transform *powerbox;
	SpriteRenderer *powerboxSprite;

	Transform *powerbar;
	SpriteRenderer *powerbarSprite;
	Powerbar *powerbarBehavior;

public:
	void onInitialize() override;
	void onStart() override;
	void onUpdate() override;

	void onClick(int x, int y);
	void onRelease();
	void onDrag(int x, int y);
};
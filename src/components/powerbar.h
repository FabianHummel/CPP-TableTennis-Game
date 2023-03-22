#pragma once

#include "component.h"
#include "spriterenderer.h"
#include "transform.h"
#include "ballmovement.h"

class Powerbar : public Component {
private:
	int size;
	bool isDragging;
	int startX, startY;
	int deltaX, deltaY;
	float strength;

	BallMovement *ball;
	Transform *indicator;
	SpriteRenderer *indicatorSprite;
	Transform *powerbox;
	SpriteRenderer *powerboxSprite;
	Transform *powerbar;
	SpriteRenderer *powerbarSprite;

	void onClick(int x, int y);
	void onRelease();
	void onDrag(int x, int y);

	void setProgress(float v, float y);

public:
	void onInitialize() override;
	void onStart() override;
	void onEvent(SDL_Event event) override;
};

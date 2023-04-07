#pragma once

#include "./ballmovement.h"
#include "./component.h"
#include "./prediction.h"
#include "./spriterenderer.h"
#include "./transform.h"

class Powerbar : public Component
{
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
	Prediction *prediction;

	void onClick(int x, int y);
	void onRelease();
	void onDrag(int x, int y);

	void setProgress(float v, float y);
	void report();

  public:
	void onInitialize() override;
	void onStart() override;
	void onEvent(SDL_Event event) override;
};

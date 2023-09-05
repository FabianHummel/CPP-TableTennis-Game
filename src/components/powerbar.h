#pragma once

#include "../ecs/ecs.h"
#include "ballmovement.h"
#include "prediction.h"

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
	Vector3 calcForce();

  public:
	void onInitialize() override;
	void onStart() override;
	void onUpdate(double deltaTime) override;
	void onEvent(SDL_Event event) override;
};

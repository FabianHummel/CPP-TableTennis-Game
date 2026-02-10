#pragma once

#include "../componentsystem.h"
#include "ballmovement.h"
#include "prediction.h"
#include "spriterenderer.h"

class Powerbar : public Component
{
  private:
	float size;
	bool isDragging;
	float startX, startY;
	float deltaX, deltaY;
	float strength;

	BallMovement *ball;
	Transform *indicator;
	SpriteRenderer *indicatorSprite;
	Transform *powerbox;
	SpriteRenderer *powerboxSprite;
	Transform *powerbar;
	SpriteRenderer *powerbarSprite;
	Prediction *prediction;

	void onClick(float x, float y);
	void onRelease();
	void onDrag(float x, float y);
	void setProgress(float v, float y);
	Vector3 calcForce();

  public:
	void onInitialize() override;
	void onStart() override;
	void onUpdate(double deltaTime) override;
	void onEvent(const SDL_Event *event) override;
};

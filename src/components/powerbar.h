#pragma once

#include "../componentsystem.h"
#include "ballmovement.h"
#include "prediction.h"
#include "spriterenderer.h"

class PowerBar : public Component
{
  private:
	float size{0};
	bool isDragging{0};
	float startX{0}, startY{0};
	float deltaX{0}, deltaY{0};
	float strength{0};

	BallMovement *ball{nullptr};
	Transform *indicator{nullptr};
	SpriteRenderer *indicatorSprite{nullptr};
	Transform *powerbox{nullptr};
	SpriteRenderer *powerboxSprite{nullptr};
	Transform *powerbar{nullptr};
	SpriteRenderer *powerbarSprite{nullptr};
	Prediction *prediction{nullptr};

	void onClick(float x, float y);
	void onRelease();
	void onDrag(float x, float y);
	void setProgress(float v, float y);
	Vector3 calcForce() const;

  public:
	PowerBar();

	void onInitialize() override;
	void onStart() override;
	void onUpdate(double deltaTime) override;
	void onEvent(const SDL_Event *event) override;
};

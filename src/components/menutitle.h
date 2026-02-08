#pragma once

#include "../componentsystem.h"

class MenuTitle : public Component
{
  private:
	constexpr static float SPEED = 1.0f;
	Transform *transform;
	float initialPosition;
	double time;

  public:
	void onInitialize() override;
	void onUpdate(double deltaTime) override;
};

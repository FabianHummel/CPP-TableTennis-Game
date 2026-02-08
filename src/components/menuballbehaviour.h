#pragma once

#include "../componentsystem.h"

class MenuBallBehaviour : public Component
{
  private:
	constexpr static float SPEED = 5.0f;
	constexpr static int HEIGHT = 50;
	Transform *transform{};
	double time{};

  protected:
	void onInitialize() override;
	void onUpdate(double deltaTime) override;
};
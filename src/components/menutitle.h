#pragma once

#include "../componentsystem.h"

class MenuTitle : public Component
{
  private:
	constexpr static float SPEED = 1.0f;
	Transform *transform{nullptr};
	double initialPosition{0};
	double time{0};

  public:
	MenuTitle();
	MenuTitle(double timeOffset);

	void onInitialize() override;
	void onUpdate(double deltaTime) override;
};

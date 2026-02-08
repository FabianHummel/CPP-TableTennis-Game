#pragma once

#include "../componentsystem.h"

class ShadowTransformer : public Component
{
  private:
	Transform *ball{};
	Transform *transform{};
	Entity *target;

  public:
	explicit ShadowTransformer(Entity *shadow);

	void onInitialize() override;
	void onUpdate(double deltaTime) override;
};

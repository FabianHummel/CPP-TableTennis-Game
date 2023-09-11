#pragma once

#include "../ecs/ecs.h"
#include <functional>

class Button : public Component
{
  private:
	Transform *transform{};
	std::function<void()> onMouseDown;
	std::function<void()> onMouseUp;

  public:
	Button(const std::function<void()> &onMouseDown, const std::function<void()> &onMouseUp);
	void onInitialize() override;
	void onUpdate(double deltaTime) override;
	void onEvent(SDL_Event event) override;
};

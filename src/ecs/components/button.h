#pragma once

#include "../ecs.h"
#include <functional>

class Button : public Component
{
  private:
	Transform *transform{};
	std::function<void()> onMouseDown;
	std::function<void()> onMouseUp;
	std::function<void()> onMouseOver;
	std::function<void()> onMouseExit;

  public:
	bool isMouseOver{};

	Button(
		const std::function<void()> &onMouseDown = nullptr,
		const std::function<void()> &onMouseUp = nullptr,
		const std::function<void()> &onMouseOver = nullptr,
		const std::function<void()> &onMouseExit = nullptr);
	void onInitialize() override;
	void onUpdate(double deltaTime) override;
	void onEvent(SDL_Event event) override;
};

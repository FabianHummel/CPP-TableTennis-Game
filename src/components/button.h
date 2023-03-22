#pragma once

#include "component.h"
#include "transform.h"
#include <SDL.h>
#include <SDL_events.h>
#include <functional>

class Button : public Component
{
	private:
		Transform *transform;
		std::function<void()> onMouseDown;
		std::function<void()> onMouseUp;

	public:
		Button(const std::function<void()> onMouseDown, const std::function<void()> onMouseUp);
		void onInitialize() override;
		void onEvent(SDL_Event event) override;
};

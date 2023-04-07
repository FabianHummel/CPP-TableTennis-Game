#include "button.h"
#include <SDL_events.h>
#include <SDL_mouse.h>
#include <cstdio>
#include <functional>

Button::Button(const std::function<void()> onMouseDown, const std::function<void()> onMouseUp)
{
	this->onMouseDown = onMouseDown;
	this->onMouseUp = onMouseUp;
}

void Button::onInitialize()
{
	this->transform = parent->getTransform();
}

void Button::onEvent(SDL_Event event)
{
	int x, y;
	SDL_GetMouseState(&x, &y);
	x *= 2;
	y *= 2;

	switch (event.type)
	{
	case SDL_MOUSEBUTTONDOWN:
		if (onMouseDown != nullptr && transform->inTransformBounds(x, y))
			onMouseDown();
		break;

	case SDL_MOUSEBUTTONUP:
		if (onMouseUp != nullptr && transform->inTransformBounds(x, y))
			onMouseUp();
		break;
	}
}

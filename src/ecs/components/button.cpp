#include "button.h"
#include "../../cursormanager.h"
#include <SDL_events.h>
#include <SDL_mouse.h>

Button::Button(
	const std::function<void()> &onMouseDown,
	const std::function<void()> &onMouseUp,
	const std::function<void()> &onMouseOver,
	const std::function<void()> &onMouseExit)
{
	this->onMouseDown = onMouseDown;
	this->onMouseUp = onMouseUp;
	this->onMouseOver = onMouseOver;
	this->onMouseExit = onMouseExit;
};

void Button::onInitialize()
{
	this->transform = parent->transform;
}

void Button::onUpdate(double deltaTime)
{
	if (!parent->isVisible()) return;

	int x, y;
	SDL_GetMouseState(&x, &y);
	x *= 2;
	y *= 2;

	if (transform->inTransformBounds(x, y))
		CursorManager::requestCursor(CursorManager::handCursor);
	else
		CursorManager::requestCursor(CursorManager::arrowCursor);
}

void Button::onEvent(SDL_Event event)
{
	if (!parent->isVisible()) return;

	int x, y;
	SDL_GetMouseState(&x, &y);
	x *= 2;
	y *= 2;

	switch (event.type)
	{
	case SDL_MOUSEMOTION:
		if (transform->inTransformBounds(x, y) && !isMouseOver)
		{
			isMouseOver = true;
			if (onMouseOver)
				onMouseOver();
		}
		else if (!transform->inTransformBounds(x, y) && isMouseOver)
		{
			isMouseOver = false;
			if (onMouseExit)
				onMouseExit();
		}
		break;
	case SDL_MOUSEBUTTONDOWN:
		if (onMouseDown && transform->inTransformBounds(x, y))
			onMouseDown();
		break;

	case SDL_MOUSEBUTTONUP:
		if (onMouseUp && transform->inTransformBounds(x, y))
			onMouseUp();
		break;
	}
}
#pragma once

#include <SDL_events.h>
#include <vector>
#include <SDL.h>
#include "../render/renderwindow.h"

class Pane
{
protected:
	RenderWindow *window;

public:
	Pane(RenderWindow *window);
	/**
	 * @brief Called once when the game starts.
	 */
	virtual void onStart() {};

	/**
	 * @brief Called every frame.
	 */
	virtual void onGui(double deltaTime) {};

	/**
	 * @brief Called when an event fires.
	 */
	virtual void onEvent(SDL_Event event) {};

	/**
	 * @brief Called when the window stops existing
	 */
	virtual void dispose() {};
};

#pragma once

#include "../render/renderwindow.h"
#include "../ecs/ecs.h"
#include "../components/index.h"
#include <SDL.h>
#include <SDL_events.h>
#include <vector>

class Pane
{
  protected:
	RenderWindow *window;

  public:
	explicit Pane(RenderWindow *window);
	/**
	 * @brief Called once when the game starts.
	 */
	virtual void onStart(){};

	/**
	 * @brief Called every frame.
	 */
	virtual void onGui(double deltaTime){};

	/**
	 * @brief Called when an event fires.
	 */
	virtual void onEvent(SDL_Event event){};

	/**
	 * @brief Called when the window stops existing
	 */
	virtual void dispose(){};
};

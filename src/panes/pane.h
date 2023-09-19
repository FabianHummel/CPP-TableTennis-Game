#pragma once

#include "../ecs/components/index.h"
#include "../ecs/ecs.h"
#include "../utility/renderwindow.h"
#include <SDL.h>
#include <SDL_events.h>
#include <vector>

class Pane
{
  protected:
	RenderWindow *window;

  public:
	explicit Pane(RenderWindow *window);
	~Pane();

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
};

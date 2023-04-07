#pragma once

#include <SDL_events.h>
#include <vector>

class Entity;

class Component
{
  public:
	Entity *parent;

	/**
	 * @brief Initializes the component. Only use to reference other components.
	 */
	virtual void onInitialize(){};

	/**
	 * @brief Called once when the game starts.
	 */
	virtual void onStart(){};

	/**
	 * @brief Called every frame.
	 */
	virtual void onUpdate(double deltaTime){};

	/**
	 * @brief Called on an event.
	 */
	virtual void onEvent(SDL_Event event){};
};

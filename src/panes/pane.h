#pragma once

#include "SDL3/SDL_render.h"

class Pane
{
  protected:
	SDL_Renderer *renderer;

  public:
	explicit Pane(SDL_Renderer *renderer);
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
	virtual void onEvent(const SDL_Event *event){};
};

#pragma once

#include <vector>

class Entity;

class Component {
public:
	Entity *parent;

	/**
	 * @brief Initializes the component. Only use to reference other components.
	 */
	virtual void onInitialize() = 0;

	/**
	 * @brief Called once when the game starts.
	 */
	virtual void onStart() = 0;

	/**
	 * @brief Called every frame.
	 */
	virtual void onUpdate(double deltaTime) = 0;
};

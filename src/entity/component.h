#pragma once

class Component {
  public:

	/**
	 * @brief Initializes the component. Only use to reference other components.
	 */
    virtual void onInitialize();

	/**
	 * @brief Called once when the game starts.
	 */
    virtual void onStart();

	/**
	 * @brief Called every frame.
	 */
	virtual void onUpdate();
};

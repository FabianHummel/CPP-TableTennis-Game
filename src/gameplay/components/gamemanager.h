//
// Created by Fabian Hummel on 14.06.22.
//

#pragma once

#include "../component.h"

class GameManager : public Component {
public:
	void onInitialize() override;
	void onStart() override;
	void onUpdate() override;

	/**
	 * Initiates the next round.\n
	 * This is called when the ball stops moving.
	 * @param side The side on the board the ball stopped moving on
	 */
	static void nextRound(bool side);
};
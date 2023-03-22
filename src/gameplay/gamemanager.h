#pragma once

#include "../components/ballmovement.h"

class GameManager
{
private:
	Entity *ball;
	BallMovement *ballMovement;

public:
	static void nextRound();
};

//
// Created by Fabian Hummel on 17.04.22.
//

#pragma once

#include "vector3.h"

namespace MathUtil
{
	float sign(float x);

	void moveTowards(float &current, float target, float maxDelta);
	void moveTowardsZero(float &current, float maxDelta);
	void moveTowards(Vector3 &current, const Vector3 &target, float maxDelta);
	void moveTowardsZero(Vector3 &current, float maxDelta);
	bool closeToPoint(float value, float threshold);
};

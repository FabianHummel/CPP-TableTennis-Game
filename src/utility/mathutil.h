//
// Created by Fabian Hummel on 17.04.22.
//

#pragma once

#include "vector3.h"

namespace MathUtil
{
	double sign(double x);
	void moveTowards(double &current, double target, double maxDelta);
	void moveTowardsZero(double &current, double maxDelta);
	void moveTowards(Vector3 &current, const Vector3 &target, double maxDelta);
	void moveTowardsZero(Vector3 &current, double maxDelta);
	bool closeToPoint(double value, double threshold);
};

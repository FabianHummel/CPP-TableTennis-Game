//
// Created by Fabian Hummel on 17.04.22.
//

#pragma once

#include "vector3.h"

class MathUtil
{
  private:
	static float sign(float x);

  public:
	static void moveTowards(float &current, float target, float maxDelta);
	static void moveTowardsZero(float &current, float maxDelta);
	static void moveTowards(Vector3 &current, const Vector3 &target, float maxDelta);
	static void moveTowardsZero(Vector3 &current, float maxDelta);
	static bool closeToPoint(float value, float threshold);
};

//
// Created by Fabian Hummel on 17.04.22.
//

#include "mathutil.h"
#include <algorithm>
#include <cmath>

namespace MathUtil
{
	void moveTowards(float &current, float target, float maxDelta)
	{
		if (abs(target - current) <= maxDelta)
		{
			current = target;
			return;
		}
		current = current + sign(target - current) * maxDelta;
	}

	void moveTowardsZero(float &current, float maxDelta)
	{
		return moveTowards(current, 0, maxDelta);
	}

	void moveTowards(Vector3 &current, const Vector3 &target, float maxDelta)
	{
		float deltaX = target.x - current.x;
		float deltaY = target.y - current.y;
		float deltaZ = target.z - current.z;

		float sqdist = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;
		if (sqdist == 0 || maxDelta >= 0 && sqdist <= maxDelta * maxDelta)
		{
			current = target;
			return;
		}

		float dist = sqrt(sqdist);
		float newX = current.x + deltaX / dist * maxDelta;
		float newY = current.y + deltaY / dist * maxDelta;
		float newZ = current.z + deltaZ / dist * maxDelta;
		current = {newX, newY, newZ};
	}

	void moveTowardsZero(Vector3 &current, float maxDelta)
	{
		return moveTowards(current, {0, 0, 0}, maxDelta);
	}

	float sign(float x)
	{
		return x < 0 ? -1 : 1;
	}

	bool closeToPoint(float value, float threshold)
	{
		return abs(value) <= threshold;
	}
}
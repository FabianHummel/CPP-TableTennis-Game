//
// Created by Fabian Hummel on 17.04.22.
//

#include "mathutil.h"
#include <algorithm>
#include <cmath>

namespace MathUtil
{
	void moveTowards(double &current, const double target, const double maxDelta)
	{
		if (abs(target - current) <= maxDelta)
		{
			current = target;
			return;
		}
		current = current + sign(target - current) * maxDelta;
	}

	void moveTowardsZero(double &current, const double maxDelta)
	{
		return moveTowards(current, 0, maxDelta);
	}

	void moveTowards(Vector3 &current, const Vector3 &target, const double maxDelta)
	{
		const double deltaX = target.x - current.x;
		const double deltaY = target.y - current.y;
		const double deltaZ = target.z - current.z;

		const double sqrdist = deltaX * deltaX + deltaY * deltaY + deltaZ * deltaZ;
		if (sqrdist == 0 || maxDelta >= 0 && sqrdist <= maxDelta * maxDelta)
		{
			current = target;
			return;
		}

		const double dist = sqrt(sqrdist);
		const double newX = current.x + deltaX / dist * maxDelta;
		const double newY = current.y + deltaY / dist * maxDelta;
		const double newZ = current.z + deltaZ / dist * maxDelta;
		current = {newX, newY, newZ};
	}

	void moveTowardsZero(Vector3 &current, const double maxDelta)
	{
		return moveTowards(current, {0, 0, 0}, maxDelta);
	}

	double sign(const double x)
	{
		return x < 0 ? -1 : 1;
	}

	bool closeToPoint(const double value, const double threshold)
	{
		return abs(value) <= threshold;
	}
}
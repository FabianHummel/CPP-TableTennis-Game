//
// Created by Fabian Hummel on 17.04.22.
//

#include "mathutil.h"
#include <algorithm>
#include <cmath>

namespace MathUtil
{
    void move_towards(double& current, const double target, const double max_delta)
    {
        if (abs(target - current) <= max_delta)
        {
            current = target;
            return;
        }
        current = current + sign(target - current) * max_delta;
    }

    void move_towards_zero(double& current, const double maxDelta)
    {
        return move_towards(current, 0, maxDelta);
    }

    void move_towards(Vector3& current, const Vector3& target, const double max_delta)
    {
        const double delta_x = target.x - current.x;
        const double delta_y = target.y - current.y;
        const double delta_z = target.z - current.z;

        const double sqrdist = delta_x * delta_x + delta_y * delta_y + delta_z * delta_z;
        if (sqrdist == 0 || max_delta >= 0 && sqrdist <= max_delta * max_delta)
        {
            current = target;
            return;
        }

        const double dist = sqrt(sqrdist);
        const double new_x = current.x + delta_x / dist * max_delta;
        const double new_y = current.y + delta_y / dist * max_delta;
        const double new_z = current.z + delta_z / dist * max_delta;
        current = {new_x, new_y, new_z};
    }

    void move_towards_zero(Vector3& current, const double max_delta)
    {
        return move_towards(current, {0, 0, 0}, max_delta);
    }

    double sign(const double x)
    {
        return x < 0 ? -1 : 1;
    }

    bool close_to_point(const double value, const double threshold)
    {
        return abs(value) <= threshold;
    }
}
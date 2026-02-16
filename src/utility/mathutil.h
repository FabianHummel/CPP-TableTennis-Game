//
// Created by Fabian Hummel on 17.04.22.
//

#pragma once

#include "vector3.h"

namespace MathUtil
{
    double sign(double x);
    void move_towards(double& current, double target, double max_delta);
    void move_towards_zero(double& current, double maxDelta);
    void move_towards(Vector3& current, const Vector3& target, double max_delta);
    void move_towards_zero(Vector3& current, double max_delta);
    bool close_to_point(double value, double threshold);
};
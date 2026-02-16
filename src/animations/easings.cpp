#include "../managers/animationmanager.h"

double Easings::linear(const double t)
{
    return t;
}

double Easings::ease_in(const double t)
{
    return t * t;
}

double Easings::ease_out(const double t)
{
    return t * (2 - t);
}

double Easings::ease(const double t)
{
    return t < 0.5 ? 2 * t * t : -1 + (4 - 2 * t) * t;
}

double Easings::ease_out_elastic(const double t)
{
    if (t == 0 || t == 1)
        return t;

    constexpr double p = 0.3;
    constexpr double s = p / 4;
    return pow(2, -10 * t) * sin((t - s) * (2 * M_PI) / p) + 1;
}
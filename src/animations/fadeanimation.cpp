#include "../managers/animationmanager.h"

Animation Animations::fade_in(Entity* target)
{
    return [=](const double t)
    {
        target->opacity = t * 255;
    };
}

Animation Animations::fade_out(Entity* target)
{
    return [=](const double t)
    {
        target->opacity = (1 - t) * 255;
    };
}
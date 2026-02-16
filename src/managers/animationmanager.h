#pragma once

#include "../components/componentsystem.h"
#include "functional"

typedef std::function<void(double)> Animation;

typedef std::function<double(double)> Easing;

typedef struct
{
    Animation animation;
    Easing easing;
    double duration;
    double progress;
} AnimationInstance;

namespace AnimationManager
{
    extern std::vector<AnimationInstance*> animations;

    AnimationInstance* play(const Animation& animation, const Easing& easing, double duration = 1.0);
    void update(double deltaTime);
}

namespace Animations
{
    extern Animation swipe_in(Entity* target, bool direction);
    extern Animation swipe_out(Entity* target, bool direction);

    extern Animation fade_in(Entity * target);
    extern Animation fade_out(Entity * target);
}

namespace Easings
{
    double linear(double t);
    double ease_in(double t);
    double ease_out(double t);
    double ease(double t);
    double ease_out_elastic(double t);
}
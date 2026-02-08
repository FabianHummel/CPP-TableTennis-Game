#pragma once

#include "componentsystem.h"
#include "functional"

typedef std::function<void(double)> Animation;

typedef std::function<double(double)> Easing;

typedef struct {
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
	extern Animation swipeIn(Entity *target, bool direction);
	extern Animation swipeOut(Entity *target, bool direction);

	extern Animation fadeIn(Entity *target);
	extern Animation fadeOut(Entity *target);
}

namespace Easings
{
	double linear(double t);
	double easeIn(double t);
	double easeOut(double t);
	double ease(double t);
	double easeOutElastic(double t);
}
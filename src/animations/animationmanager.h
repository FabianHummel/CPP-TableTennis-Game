#pragma once

#include "functional"
#include "../ecs/ecs.h"

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
	extern Easing linear;
	extern Easing easeIn;
	extern Easing easeOut;
	extern Easing ease;
	extern Easing easeOutElastic;
}
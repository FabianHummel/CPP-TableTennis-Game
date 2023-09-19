#include "../animationmanager.h"

Animation Animations::fadeIn(Entity *target)
{
	return [=](double t)
	{
		target->opacity = t * 255;
	};
}

Animation Animations::fadeOut(Entity *target)
{
	return [=](double t)
	{
		target->opacity = (1-t) * 255;
	};
}
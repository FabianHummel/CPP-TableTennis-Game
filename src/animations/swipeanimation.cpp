#include "animationmanager.h"

#include "../render/renderwindow.h"

Animation Animations::swipeIn(Entity *target, bool direction)
{
	return [=](double t)
	{
		if (!target) return;
		target->visible = true;
		int dir = direction ? -1 : 1;
		target->animation->setX(dir * (1.0-t) * RenderWindow::SCREEN_WIDTH);
	};
}

Animation Animations::swipeOut(Entity *target, bool direction)
{
	return [=](double t)
	{
		if (!target) return;
		int dir = direction ? -1 : 1;
		target->animation->setX(dir * t * RenderWindow::SCREEN_WIDTH);

		if (t >= 1.0)
		{
			target->visible = false;
		}
	};
}
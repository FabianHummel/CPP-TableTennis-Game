#include "../animationmanager.h"

#include "../utility/renderwindow.h"

Animation Animations::swipeIn(Entity *target, bool direction)
{
	return [=](double t)
	{
		target->visible = true;
		const int dir = direction ? -1 : 1;
		target->animation->position.x = dir * (1.0-t) * RenderWindow::SCREEN_WIDTH;
	};
}

Animation Animations::swipeOut(Entity *target, bool direction)
{
	return [=](double t)
	{
		const int dir = direction ? -1 : 1;
		target->animation->position.x = dir * t * RenderWindow::SCREEN_WIDTH;

		if (t >= 1.0)
		{
			target->visible = false;
		}
	};
}
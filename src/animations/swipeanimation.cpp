#include "../managers/animationmanager.h"

#include "../utility/renderwindow.h"

Animation Animations::swipe_in(Entity* target, const bool direction)
{
    return [=](const double t)
    {
        target->visible = true;
        const int dir = direction ? -1 : 1;
        target->animation->position.x = dir * (1.0 - t) * RenderWindow::SCREEN_WIDTH;
    };
}

Animation Animations::swipe_out(Entity* target, const bool direction)
{
    return [=](const double t)
    {
        const int dir = direction ? -1 : 1;
        target->animation->position.x = dir * t * RenderWindow::SCREEN_WIDTH;

        if (t >= 1.0)
        {
            target->visible = false;
        }
    };
}
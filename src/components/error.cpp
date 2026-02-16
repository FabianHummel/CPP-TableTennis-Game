//
// Created by Fabian Hummel on 15.02.26.
//

#include "error.h"

Error::Error(const double close_time)
{
    this->close_time = close_time;
}

void Error::on_start()
{
    AnimationManager::play(Animations::swipe_in(this->parent, true), Easings::ease_out, FADEIN_DURATION);
}

void Error::on_update(const double delta_time)
{
    this->elapsed_time += delta_time;

    if (fadeout == nullptr && this->elapsed_time > this->close_time - FADEOUT_DURATION)
    {
        fadeout = AnimationManager::play(Animations::swipe_out(this->parent, true), Easings::ease_out,
                                         FADEOUT_DURATION);
    }

    if (this->elapsed_time > this->close_time)
    {
        std::erase(AnimationManager::animations, fadeout);
        delete this->parent;
    }
}
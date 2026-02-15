//
// Created by Fabian Hummel on 15.02.26.
//

#include "error.h"

Error::Error(const double closeTime)
{
    this->closeTime = closeTime;
}

void Error::onStart()
{
    AnimationManager::play(Animations::swipeIn(this->parent, true), Easings::easeOut, FADEIN_DURATION);
}

void Error::onUpdate(const double deltaTime)
{
    this->elapsedTime += deltaTime;

    if (fadeout == nullptr && this->elapsedTime > this->closeTime - FADEOUT_DURATION)
    {
        fadeout = AnimationManager::play(Animations::swipeOut(this->parent, true), Easings::easeOut, FADEOUT_DURATION);
    }

    if (this->elapsedTime > this->closeTime)
    {
        std::erase(AnimationManager::animations, fadeout);
        delete this->parent;
    }
}
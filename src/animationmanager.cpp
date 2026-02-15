#include "animationmanager.h"

namespace AnimationManager
{
	std::vector<AnimationInstance*> animations;
}

AnimationInstance* AnimationManager::play(const Animation& animation, const Easing& easing, const double duration)
{
	const auto instance = new AnimationInstance {animation, easing, duration};
	animations.push_back(instance);
	return instance;
}

void AnimationManager::update(const double deltaTime)
{
	for (AnimationInstance* animation : animations)
	{
		animation->progress += deltaTime;
		if (animation->progress > animation->duration)
		{
			animation->progress = animation->duration;
			std::erase(animations, animation);
		}

		animation->animation(animation->easing(animation->progress / animation->duration));
	}
}
#include "animationmanager.h"

namespace AnimationManager
{
	std::vector<AnimationInstance*> animations;

	AnimationInstance* play(const Animation& animation, const Easing& easing, double duration)
	{
		AnimationInstance *instance = new AnimationInstance {animation, easing, duration};
		animations.push_back(instance);
		return instance;
	}

	void update(double deltaTime)
	{
		for (AnimationInstance* animation : animations)
		{
			animation->progress += deltaTime;
			if (animation->progress > animation->duration)
			{
				animation->progress = animation->duration;
				animations.erase(std::remove(animations.begin(), animations.end(), animation), animations.end());
			}

			animation->animation(animation->easing(animation->progress / animation->duration));
		}
	}
}
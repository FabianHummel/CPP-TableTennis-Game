#include "ecsmanager.h"
#include "../components/transform.h"
#include "ecs.h"
#include <SDL_events.h>

namespace EcsManager
{
	void addEntity(Entity *entity)
	{
		entities.push_back(entity);
	}

	void removeEntity(Entity *entity)
	{
		entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
	}

	Entity *findEntity(const char *name)
	{
		for (auto &entity : entities)
		{
			if (strcmp(entity->getName(), name) == 0)
			{
				return entity;
			}
		}
		return nullptr;
	}

	void forEachEntity(const std::function<void(Entity *)> &callback)
	{
		for (auto &entity : entities)
		{
			callback(entity);
		}
	}

	void forEachComponent(const std::function<void(Component *)> &callback)
	{
		forEachEntity([&](Entity *entity) { entity->forEachComponent(callback); });
	}

	void initialize()
	{
		forEachComponent([](Component *component) { component->onInitialize(); });
	}

	void start()
	{
		forEachComponent([](Component *component) { component->onStart(); });
	}

	void update(double deltaTime)
	{
		forEachComponent([deltaTime](Component *component) { component->onUpdate(deltaTime); });
	}

	void event(SDL_Event event)
	{
		forEachComponent([event](Component *component) { component->onEvent(event); });
	}

	void sort()
	{
		std::sort(entities.begin(), entities.end(), [](Entity *a, Entity *b) {
			Transform *trfA = a->getTransform();
			Transform *trfB = b->getTransform();
			/*return trfA->getY() > trfB->getY() &&
			         trfA->getZ() > trfB->getZ();*/
			if (trfA->getI() == trfB->getI())
			{
				return trfA->getZ() < trfB->getZ();
			}

			return trfA->getI() < trfB->getI();
		});
	}

	void clear()
	{
		entities.clear();
	}
}
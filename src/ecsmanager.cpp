#include "ecsmanager.h"
#include "components/transform.h"
#include "componentsystem.h"
#include <SDL_events.h>

namespace EcsManager
{
	std::vector<Entity*> entities;

	/// Returns the newly added entity
	Entity* addEntity(Entity *entity)
	{
		entities.push_back(entity);
		return entity;
	}

	/// Returns the removed entity
	Entity* removeEntity(Entity *entity)
	{
		entities.erase(std::remove(entities.begin(), entities.end(), entity), entities.end());
		return entity;
	}

	/// Finds an entity in the most outer scope
	Entity* findEntity(const char *name)
	{
		for (auto &entity : entities)
		{
			if (strcmp(entity->name, name) == 0)
			{
				return entity;
			}
		}
		return nullptr;
	}

	void callOnEachEntity(const std::function<void(Component *)> &callback)
	{
		for (auto &entity : entities)
		{
			entity->update(callback);
		}
	}

	void initialize()
	{
		callOnEachEntity([](Component *component) { component->onInitialize(); });
	}

	void start()
	{
		callOnEachEntity([](Component *component) { component->onStart(); });
	}

	void update(double deltaTime)
	{
		callOnEachEntity([deltaTime](Component *component) { component->onUpdate(deltaTime); });
	}

	void event(SDL_Event event)
	{
		callOnEachEntity([event](Component *component) { component->onEvent(event); });
	}

	void sort()
	{
		std::sort(entities.begin(), entities.end(), [](Entity *a, Entity *b) {
			Transform *trfA = a->transform;
			Transform *trfB = b->transform;

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
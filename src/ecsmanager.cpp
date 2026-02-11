#include "ecsmanager.h"
#include "components/transform.h"
#include "componentsystem.h"
#include <SDL3/SDL_events.h>

namespace EcsManager
{
	std::vector<Entity*> entities;
}

/// Returns the newly added entity
Entity* EcsManager::addEntity(Entity *entity)
{
	entities.push_back(entity);
	return entity;
}

/// Returns the removed entity
Entity* EcsManager::removeEntity(Entity *entity)
{
	std::erase(entities, entity);
	return entity;
}

/// Finds an entity in the most outer scope
Entity* EcsManager::findEntity(const char *name)
{
	for (const auto &entity : entities)
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
	for (const auto &entity : EcsManager::entities)
	{
		entity->update(callback);
	}
}

void EcsManager::initialize()
{
	callOnEachEntity([](Component *component)
	{
		SDL_LogTrace(SDL_LOG_CATEGORY_APPLICATION, "Initializing %s on %s\n", component->name, component->parent->name);

		component->onInitialize();
	});
}

void EcsManager::start()
{
	callOnEachEntity([](Component *component)
	{
		SDL_LogTrace(SDL_LOG_CATEGORY_APPLICATION, "Starting %s on %s\n", component->name, component->parent->name);

		component->onStart();
	});
}

void EcsManager::update(double deltaTime)
{
	callOnEachEntity([deltaTime](Component *component)
	{
		component->onUpdate(deltaTime);
	});
}

void EcsManager::event(const SDL_Event *event)
{
	callOnEachEntity([event](Component *component)
	{
		component->onEvent(event);
	});
}

void EcsManager::sort()
{
	std::ranges::sort(entities, [](const Entity *a, const Entity *b) {
		const Transform *trfA = a->transform;
		const Transform *trfB = b->transform;

		if (trfA->zIndex == trfB->zIndex)
		{
			return trfA->position.z < trfB->position.z;
		}

		return trfA->zIndex < trfB->zIndex;
	});
}

void EcsManager::clear()
{
	entities.clear();
}
#include "ecsmanager.h"
#include "components/transform.h"
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

void EcsManager::initialize()
{
	for (const auto &entity : entities)
	{
		entity->initialize();
	}
}

void EcsManager::start()
{
	for (const auto &entity : entities)
	{
		entity->start();
	}
}

void EcsManager::update(const double deltaTime)
{
	for (const auto &entity : entities)
	{
		entity->update(deltaTime);
	}
}

void EcsManager::event(const SDL_Event *event)
{
	for (const auto &entity : entities)
	{
		entity->event(event);
	}
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
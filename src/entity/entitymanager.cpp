//
// Created by Fabian Hummel on 12.06.22.
//

#include "entitymanager.h"
#include "entity.h"
#include <SDL_events.h>

std::vector<Entity*> EntityManager::entities;

void EntityManager::addEntity(Entity *entity)
{
	entities.push_back(entity);
}

void EntityManager::removeEntity(Entity *entity)
{
	entities.erase(
		std::remove(entities.begin(), entities.end(), entity), entities.end()
	);
}

Entity* EntityManager::findEntity(const char *name)
{
	for (auto &entity : entities) {
		if (strcmp(entity->getName(), name) == 0) {
			return entity;
		}
	}
	return nullptr;
}

void EntityManager::forEachEntity(const std::function<void(Entity *)>& callback)
{
	for (auto &entity : entities) {
		callback(entity);
	}
}

void EntityManager::forEachComponent(const std::function<void(Component *)> &callback)
{
	forEachEntity([&](Entity *entity) {
		entity->forEachComponent(callback);
	});
}

void EntityManager::initialize()
{
	forEachComponent([](Component *component) {
		component->onInitialize();
	});
}

void EntityManager::start()
{
	forEachComponent([](Component *component) {
		component->onStart();
	});
}

void EntityManager::update(double deltaTime)
{
	forEachComponent([deltaTime](Component *component) {
		component->onUpdate(deltaTime);
	});
}

void EntityManager::event(SDL_Event event)
{
	forEachComponent([event](Component *component) {
		component->onEvent(event);
	});
}

void EntityManager::sort()
{
	std::sort(entities.begin(), entities.end(), [](Entity *a, Entity *b) {
		Transform *trfA = a->getTransform();
		Transform *trfB = b->getTransform();
		/*return trfA->getY() > trfB->getY() &&
				 trfA->getZ() > trfB->getZ();*/
		if (trfA->getI() == trfB->getI()) {
			return trfA->getZ() < trfB->getZ();
		}

		return trfA->getI() < trfB->getI(); 
	});
}

void EntityManager::clear()
{
	entities.clear();
}

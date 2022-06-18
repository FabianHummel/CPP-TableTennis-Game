//
// Created by Fabian Hummel on 12.06.22.
//

#include "entitymanager.h"

std::vector<Entity*> EntityManager::entities;

void EntityManager::addEntity(Entity *entity) {
	entities.push_back(entity);
}

void EntityManager::removeEntity(Entity *entity) {
	entities.erase(
		std::remove(entities.begin(), entities.end(), entity), entities.end()
	);
}

Entity* EntityManager::findEntity(const char *name) {
	for (auto &entity : entities) {
		if (strcmp(entity->getName(), name) == 0) {
			return entity;
		}
	}
	return nullptr;
}

int EntityManager::findIndex(Entity *entity) {
	for (int i = 0; i < entities.size(); i++) {
		if (entities[i] == entity) {
			return i;
		}
	}
	return -1;
}

int EntityManager::findIndex(const char *name) {
	for (int i = 0; i < entities.size(); i++) {
		if (strcmp(entities[i]->getName(), name) == 0) {
			return i;
		}
	}
	return -1;
}

void EntityManager::forEachEntity(const std::function<void(Entity *)>& callback) {
	for (auto &entity : entities) {
		callback(entity);
	}
}

void EntityManager::forEachComponent(const std::function<void(Component *)> &callback) {
	forEachEntity([&](Entity *entity) {
		entity->forEachComponent(callback);
	});
}

void EntityManager::initialize() {
	forEachComponent([](Component *component) {
		component->onInitialize();
	});
}

void EntityManager::start() {
	forEachComponent([](Component *component) {
		component->onStart();
	});
}

void EntityManager::update(double deltaTime) {
	forEachComponent([deltaTime](Component *component) {
		component->onUpdate(deltaTime);
	});
}

// TODO: Short flashing when called
void EntityManager::renderAbove(Entity *movee, Entity *target) {
	// { global, ball, table, net } ->
	// { global, table, net } ->
	// { global, table, net, ball }
	entities.erase(
		std::find(entities.begin(), entities.end(), movee)
	);

	entities.insert(
		std::find(entities.begin(), entities.end(), target) + 1, movee
	);
}

void EntityManager::renderBelow(Entity *movee, Entity *target) {
	// { global, table, net, ball } ->
	// { global, table, net } ->
	// { global, ball, table, net }
	entities.erase(
		std::find(entities.begin(), entities.end(), movee)
	);

	entities.insert(
		std::find(entities.begin(), entities.end(), target), movee
	);
}
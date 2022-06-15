//
// Created by Fabian Hummel on 06.06.22.
//

#include "entity.h"
#include "entitymanager.h"

Entity::Entity(const char *name) {
	this->name = name;
	EntityManager::addEntity(this);
}

Entity::~Entity() {
	EntityManager::removeEntity(this);
}

void Entity::forEachComponent(const std::function<void(Component*)>& callback) {
	for (auto &component : components) {
		callback(component.second);
	}
}

const char *Entity::getName() const {
	return this->name;
}
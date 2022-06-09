//
// Created by Fabian Hummel on 06.06.22.
//

#include "entity.h"

Entity::Entity(const char *name) {
	this->name = name;
}

template<typename T> Entity Entity::addComponent(T *v) {
	this->components->push_back(v);
	return *this;
}

template<typename T> Entity Entity::removeComponent(T v) {
	for (auto it = this->components->begin(); it != this->components->end(); it++) {
		if (&(*it) == v) {
			this->components->erase(it);
			break;
		}
	}
	return *this;
}

template<typename T> T* Entity::getComponent() {
	for (auto &component : *this->components) {
		if (typeid(T) == typeid(component)) {
			return (T *) &component;
		}
	}
	return nullptr;
}
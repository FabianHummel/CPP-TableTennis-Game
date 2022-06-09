#pragma once

#include "vector"
#include "component.h"

class Entity {
private:
	const char *name;
	std::vector<Component> *components;

public:
	Entity(const char *name);
	template<typename T> Entity addComponent(T *component);
	template<typename T> Entity removeComponent(T component);
	template<typename T> T* getComponent();
};

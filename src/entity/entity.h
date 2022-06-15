#pragma once

#include <unordered_map>
#include "../gameplay/component.h"

class Entity {
private:
	const char *name;
	std::unordered_map<const char*, Component*> components;

public:
	Entity(const char *name);
	~Entity();

	template<class T> Entity* addComponent(T *component) {
		((Component*) component)->parent = this;
		this->components[typeid(*component).name()] = component;
		return this;
	};

	template<class T> T* getComponent() {
		return dynamic_cast<T*>(
			components[typeid(T).name()]
		);
	};

	template<class T> Entity* removeComponent() {
		components.erase(
			typeid(T).name()
		);
		return this;
	};

	void forEachComponent(const std::function<void(Component*)>& callback);

	const char* getName() const;
};
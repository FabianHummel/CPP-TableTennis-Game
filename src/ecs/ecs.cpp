#include "ecs.h"
#include "ecsmanager.h"

Entity::Entity(const char *name)
{
	this->name = name;
	this->addComponent(new Transform());
	this->transform = this->getComponent<Transform>();
	EcsManager::addEntity(this);
}

Entity::~Entity()
{
	EcsManager::removeEntity(this);
	this->forEachComponent([&](Component *component) {
		component->onDelete();
		delete component;
	});
	this->components.clear();
}

void Entity::forEachComponent(const std::function<void(Component *)> &callback)
{
	for (auto &[key, value] : this->components)
	{
		callback(value);
	}
}

const char *Entity::getName() const
{
	return this->name;
}

Transform *Entity::getTransform()
{
	return this->transform;
}
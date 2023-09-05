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
}

void Entity::forEachComponent(const std::function<void(Component *)> &callback)
{
	for (auto &component : components)
	{
		callback(component.second);
	}
}

const char *Entity::getName() const
{
	return this->name;
}

Transform *Entity::getTransform()
{
	return transform;
}
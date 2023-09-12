#include "ecs.h"
#include "ecsmanager.h"

Entity::Entity(const char *name)
{
	this->name = name;
	this->addComponent(new Transform());
	this->transform = this->getComponent<Transform>();
}

Entity::~Entity()
{
	EcsManager::removeEntity(this);
	for (auto &[name, component] : components)
	{
		component->onDelete();
		delete component;
	}

	this->components.clear();
}

void Entity::update(const std::function<void(Component *)> &callback)
{
	for (auto &[name, component] : this->components)
	{
		callback(component);
	}

	std::sort(children.begin(), children.end(), [](Entity *a, Entity *b) {
		Transform *trfA = a->transform;
		Transform *trfB = b->transform;

		if (trfA->getI() == trfB->getI())
		{
			return trfA->getZ() < trfB->getZ();
		}

		return trfA->getI() < trfB->getI();
	});

	for (auto &child : this->children)
	{
		child->update(callback);
	}
}

Entity* Entity::addChild(Entity *child)
{
	this->children.push_back(child);
	child->parent = this;
	return this;
}

Entity* Entity::getChild(const char *name)
{
	for (Entity *child : children)
	{
		if (child->name == name)
		{
			return child;
		}
	}
}


Entity* Entity::removeChild(Entity *child)
{
	this->children.erase(std::find(children.begin(), children.end(), child));
	return child;
}
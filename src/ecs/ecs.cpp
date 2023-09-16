#include "ecs.h"
#include "ecsmanager.h"

Entity::Entity(const char *name)
{
	this->name = name;

	Transform *transform = new Transform();
	this->addComponent(transform);
	transform->animation = new Transform();

	this->transform = transform;
	this->animation = transform->animation;
}

Entity::~Entity()
{
	EcsManager::removeEntity(this);
	for (auto &component : components)
	{
		component->onDelete();
		delete component;
	}

	this->components.clear();
}

int Entity::getOpacity() const
{
	if (this->parent != nullptr)
	{
		return this->opacity * this->parent->getOpacity() / 255;
	}

	return this->opacity;
}

bool Entity::isVisible() const
{
	if (this->parent != nullptr)
	{
		return this->visible && this->parent->isVisible();
	}

	return this->visible;
}

void Entity::update(const std::function<void(Component *)> &callback)
{
	for (auto &component : this->components)
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

	return nullptr;
}

Entity* Entity::removeChild(Entity *child)
{
	this->children.erase(std::find(children.begin(), children.end(), child));
	return child;
}

Entity* Entity::usePreset(const Preset &function)
{
	function(this);
	return this;
}

Entity* Entity::apply(bool visible, int opacity)
{
	this->opacity = opacity;
	this->visible = visible;
	return this;
}
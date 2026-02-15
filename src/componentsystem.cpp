#include "componentsystem.h"
#include "ecsmanager.h"

Entity::Entity(const char *name)
{
	this->name = name;

	const auto transform = new Transform();
	this->addComponent(transform);
	transform->animation = new Transform();

	this->transform = transform;
	this->animation = transform->animation;
}

Entity::~Entity()
{
	EcsManager::removeEntity(this);
	for (const auto &component : components)
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

void Entity::initialize()
{
	runOnComponents([](Component *component)
	{
		SDL_LogTrace(SDL_LOG_CATEGORY_APPLICATION, "Initializing %s on %s\n", component->name, component->parent->name);
		component->onInitialize();
	});
}

void Entity::start()
{
	runOnComponents([](Component *component)
	{
		SDL_LogTrace(SDL_LOG_CATEGORY_APPLICATION, "Starting %s on %s\n", component->name, component->parent->name);
		component->onStart();
	});
}

void Entity::update(const double deltaTime)
{
	runOnComponents([deltaTime](Component *component)
	{
		component->onUpdate(deltaTime);
	});
}

void Entity::event(const SDL_Event *event)
{
	runOnComponents([event](Component *component)
	{
		component->onEvent(event);
	});
}

void Entity::runOnComponents(const std::function<void(Component *)> &callback)
{
	for (const auto &component : this->components)
	{
		callback(component);
	}

	std::ranges::sort(children, [](const Entity *a, const Entity *b)
	{
		const Transform *trfA = a->transform;
		const Transform *trfB = b->transform;

		if (trfA->zIndex == trfB->zIndex)
		{
			return trfA->position.z < trfB->position.z;
		}

		return trfA->zIndex < trfB->zIndex;
	});

	for (const auto &child : this->children)
	{
		child->runOnComponents(callback);
	}
}

Entity* Entity::addChild(Entity *child)
{
	this->children.push_back(child);
	child->parent = this;
	return this;
}

Entity* Entity::getChild(const char *name) const
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
	std::erase(this->children, child);
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
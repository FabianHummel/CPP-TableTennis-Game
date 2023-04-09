#include "entity.h"
#include "entitymanager.h"

Entity::Entity(const char *name)
{
	this->name = name;
	this->addComponent(new Transform());
	this->transform = this->getComponent<Transform>();
	EntityManager::addEntity(this);
}

Entity::~Entity()
{
	EntityManager::removeEntity(this);
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
};

/*template<typename T> Entity* Entity::addComponent(T *component) {
    ((Component*) component)->parent = this;
    this->components[typeid(*component).name()] = component;
    return this;
};

template<class T> T* Entity::getComponent() {
    return dynamic_cast<T*>(
        components[typeid(T).name()]
    );
};

template<class T> Entity* Entity::removeComponent() {
    components.erase(
        typeid(T).name()
    );
    return this;
};*/

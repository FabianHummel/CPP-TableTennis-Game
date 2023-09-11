#ifndef ECS_H
#define ECS_H

#include <SDL_events.h>
#include <SDL_image.h>
#include "unordered_map"
#include "vector"
#include "functional"

class Entity;

class Component
{
  public:
	Entity *parent{};

	virtual void onInitialize(){};
	virtual void onStart(){};
	virtual void onUpdate(double deltaTime){};
	virtual void onEvent(SDL_Event event){};
	virtual void onDelete(){};
};

class Transform;

class Entity
{
  private:
	const char *name;
	std::unordered_map<const char *, Component *> components;
	Transform *transform;

  public:
	explicit Entity(const char *name);
	~Entity();

	void forEachComponent(const std::function<void(Component *)> &callback);
	const char *getName() const;
	Transform *getTransform();

	template <typename T> Entity *addComponent(T *component)
	{
		((Component *)component)->parent = this;
		this->components[typeid(*component).name()] = component;
		return this;
	};

	template <class T> T *getComponent()
	{
		return dynamic_cast<T*>(this->components[typeid(T).name()]);
	};

	template <class T> Entity *removeComponent()
	{
		this->components.erase(typeid(T).name());
		return this;
	};
};

#endif //ECS_H

#include "../components/transform.h"
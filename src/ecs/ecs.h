#ifndef ECS_H
#define ECS_H

#include <SDL_events.h>
#include "unordered_map"
#include "functional"

class Entity;

class Component
{
  public:
	Entity *parent{};

	/**
	 * @brief Initializes the component. Only use to reference other components.
	 */
	virtual void onInitialize(){};

	/**
	 * @brief Called once when the game starts.
	 */
	virtual void onStart(){};

	/**
	 * @brief Called every frame.
	 */
	virtual void onUpdate(double deltaTime){};

	/**
	 * @brief Called on an event.
	 */
	virtual void onEvent(SDL_Event event){};
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
		return dynamic_cast<T *>(components[typeid(T).name()]);
	};

	template <class T> Entity *removeComponent()
	{
		components.erase(typeid(T).name());
		return this;
	};
};

#endif //ECS_H

#include "../components/transform.h"
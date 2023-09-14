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

typedef std::function<void(Entity*)> Preset;

class Entity
{
  public:
	explicit Entity(const char *name);
	~Entity();

	const char *name;
	std::vector<Component*> components;
	std::vector<Entity*> children;
	Transform *transform;
	Entity *parent{};

	void update(const std::function<void(Component*)> &callback);

	Entity* addChild(Entity *child);
	Entity* getChild(const char *name);
	Entity* removeChild(Entity *child);

	Entity* usePreset(const Preset &function)
	{
		function(this);
		return this;
	}

	template <typename T> Entity* addComponent(T *component)
	{
		((Component *)component)->parent = this;
		this->components.push_back(component);
		return this;
	};

	template <class T> T* getComponent()
	{
		const std::vector<T*>& components = getComponents<T>();
		return components.empty() ? nullptr : components[0];
	};

	template <class T> std::vector<T*> getComponents()
	{
		std::vector<T*> result;
		for (Component *c : this->components)
		{
			T* derived = dynamic_cast<T*>(c);
			if (derived)
			{
				result.push_back(derived);
			}
		}

		return result;
	};

	Entity* removeComponent(Component *component)
	{
		this->components.erase(std::find(this->components.begin(), this->components.end(), component));
		return this;
	};

	template <class T> Entity* removeComponents()
	{
		std::erase_if(this->components.begin(), this->components.end(), [&](const auto &item) {
			return dynamic_cast<T*>(item);
		});
		return this;
	};
};

#endif //ECS_H

#include "components/transform.h"
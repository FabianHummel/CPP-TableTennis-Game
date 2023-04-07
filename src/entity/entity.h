#pragma once

#include "../components/component.h"
#include "../components/transform.h"
#include <unordered_map>

class Transform;

class Entity
{
  private:
	const char *name;
	std::unordered_map<const char *, Component *> components;
	Transform *transform;

  public:
	Entity(const char *name);
	~Entity();

	void forEachComponent(const std::function<void(Component *)> &callback);

	const char *getName() const;

	Transform *getTransform();

	/*template<typename T> Entity* addComponent(T *component);

	template<class T> T* getComponent();

	template<class T> Entity* removeComponent(); */

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

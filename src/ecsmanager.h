#pragma once

#include <SDL3/SDL_events.h>
#include <functional>
#include <vector>

class Entity;
class Component;

namespace EcsManager
{
  	extern std::vector<Entity*> entities;

	Entity* addEntity(Entity *entity);
	Entity* removeEntity(Entity *entity);
	Entity* findEntity(const char *name);

	void initialize();
	void start();
	void event(const SDL_Event *event);
	void update(double deltaTime);
	void sort();
	void clear();
};

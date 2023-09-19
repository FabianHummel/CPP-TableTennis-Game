#pragma once

#include <SDL_events.h>
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
	void update(double deltaTime);
	void event(SDL_Event event);
	void sort();
	void clear();
};

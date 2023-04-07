//
// Created by Fabian Hummel on 12.06.22.
//

#pragma once

#include "entity.h"
#include <SDL_events.h>
#include <vector>

class EntityManager
{
  private:
	static std::vector<Entity *> entities;
	static void forEachEntity(const std::function<void(Entity *)> &callback);
	static void forEachComponent(const std::function<void(Component *)> &callback);

  public:
	static void addEntity(Entity *entity);
	static void removeEntity(Entity *entity);
	static Entity *findEntity(const char *name);

	static void initialize();
	static void start();
	static void update(double deltaTime);
	static void event(SDL_Event event);
	static void sort();
	static void clear();
};

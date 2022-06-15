//
// Created by Fabian Hummel on 12.06.22.
//

#pragma once

#include <vector>
#include "entity.h"

class EntityManager {
private:
	static std::vector<Entity*> entities;
	static void forEachEntity(const std::function<void(Entity*)>& callback);
	static void forEachComponent(const std::function<void(Component*)>& callback);

public:
	static void addEntity(Entity *entity);
	static void removeEntity(Entity *entity);
	static Entity* findEntity(const char *name);
	static int findIndex(Entity *entity);
	static int findIndex(const char *name);

	static void renderAbove(Entity *movee, Entity *target);
	static void renderBelow(Entity *movee, Entity *target);

	static void initialize();
	static void start();
	static void update();
};

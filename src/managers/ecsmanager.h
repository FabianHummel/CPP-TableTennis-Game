#pragma once

#include <SDL3/SDL_events.h>
#include <vector>

class Entity;
class Component;

namespace EcsManager
{
    extern std::vector<Entity *> entities;

    Entity *add_entity(Entity *entity);
    Entity *remove_entity(Entity *entity);
    Entity *find_entity(const char *name);

    void initialize();
    void start();
    void event(const SDL_Event *event);
    void update(double delta_time);
    void sort();
    void clear();

    bool compare(const Entity *a, const Entity *b);
}; // namespace EcsManager

#define set_entity(target, entity) target = EcsManager::add_entity(entity)
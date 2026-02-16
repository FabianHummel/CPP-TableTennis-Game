#include "componentsystem.h"
#include "../managers/ecsmanager.h"

Entity::Entity(const char *name)
{
    this->name = name;
    this->transform = new Transform();
    this->add_component(this->transform);
    this->transform->animation = new Transform();
    this->animation = transform->animation;
}

Entity::~Entity()
{
    for (const auto &component : components)
    {
        component->on_delete();
        delete component;
    }

    this->components.clear();

    EcsManager::remove_entity(this);
}

int Entity::get_calculated_opacity() const
{
    if (this->parent != nullptr)
    {
        return this->opacity * this->parent->get_calculated_opacity() / 255;
    }

    return this->opacity;
}

bool Entity::is_visible() const
{
    if (this->parent != nullptr)
    {
        return this->visible && this->parent->is_visible();
    }

    return this->visible;
}

void Entity::initialize()
{
    run_on_components(&Component::on_initialize);
}

void Entity::start()
{
    run_on_components(&Component::on_start);
}

void Entity::update(const double deltaTime)
{
    run_on_components(
        [deltaTime](Component *component)
        {
            component->on_update(deltaTime);
        });
}

void Entity::event(const SDL_Event *event)
{
    run_on_components(
        [event](Component *component)
        {
            component->on_event(event);
        });
}

void Entity::run_on_components(const std::function<void(Component *)> &callback)
{
    for (const auto &component : this->components)
    {
        callback(component);
    }

    std::ranges::sort(children, EcsManager::compare);

    for (const auto &child : this->children)
    {
        child->run_on_components(callback);
    }
}

Entity *Entity::add_child(Entity *child)
{
    this->children.push_back(child);
    child->parent = this;
    return this;
}

Entity *Entity::get_child(const char *name) const
{
    for (Entity *child : children)
    {
        if (child->name == name)
        {
            return child;
        }
    }

    return nullptr;
}

Entity *Entity::remove_child(Entity *child)
{
    std::erase(this->children, child);
    return child;
}

Entity *Entity::use_preset(const Preset &function)
{
    function(this);
    return this;
}

Entity *Entity::apply(const bool visible, const int opacity)
{
    this->opacity = opacity;
    this->visible = visible;
    return this;
}
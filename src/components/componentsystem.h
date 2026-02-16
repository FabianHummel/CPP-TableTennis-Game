#ifndef ECS_H
#define ECS_H

#include "functional"
#include "unordered_map"
#include "vector"
#include <SDL3/SDL.h>

class Entity;

class Component
{
  public:
    const char *name{"Component"};

    Entity *parent{};

    virtual ~Component() = default;

    virtual void on_initialize()
    {
    }

    virtual void on_start()
    {
    }

    virtual void on_update(double deltaTime)
    {
    }

    virtual void on_event(const SDL_Event *event)
    {
    }

    virtual void on_delete()
    {
    }
};

class Transform;

typedef std::function<void(Entity *)> Preset;

class Entity
{
  private:
    void run_on_components(const std::function<void(Component *)> &callback);

  public:
    explicit Entity(const char *name);
    ~Entity();

    const char *name;
    std::vector<Component *> components;
    std::vector<Entity *> children;
    Transform *transform;
    Transform *animation;
    Entity *parent{};
    bool visible{true};
    int opacity{255};

    void initialize();
    void start();
    void update(double deltaTime);
    void event(const SDL_Event *event);

    [[nodiscard]] int get_calculated_opacity() const;
    [[nodiscard]] bool is_visible() const;

    Entity *add_child(Entity *child);
    Entity *get_child(const char *name) const;
    Entity *remove_child(Entity *child);
    Entity *use_preset(const Preset &function);
    Entity *apply(bool visible = true, int opacity = 255);

    template <typename T> Entity *add_component(T *component)
    {
        ((Component *)component)->parent = this;
        this->components.push_back(component);
        return this;
    }

    template <class T> T *get_component()
    {
        auto component_list = get_components<T>();
        return component_list.empty() ? nullptr : component_list.front();
    }

    template <class T> std::vector<T *> get_components()
    {
        std::vector<T *> result;
        for (Component *c : this->components)
        {
            if (T *derived = dynamic_cast<T *>(c))
            {
                result.push_back(derived);
            }
        }

        return result;
    }

    Entity *removeComponent(const Component *component)
    {
        std::erase(this->components, component);
        return this;
    }

    template <class T> Entity *removeComponents()
    {
        std::erase_if(this->components,
                      [&](const auto &item)
                      {
                          return dynamic_cast<T *>(item);
                      });
        return this;
    }
};

#endif // ECS_H

#include "transform.h"
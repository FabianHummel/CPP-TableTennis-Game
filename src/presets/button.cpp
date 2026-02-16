#include "../components/button.h"
#include "../components/nineslice.h"
#include "../components/textrenderer.h"
#include "../managers/animationmanager.h"
#include "index.h"

Preset Presets::button(SDL_Renderer *renderer, const char *text, const int pt_size,
                       const std::function<void()> &on_click)
{
    return [=](Entity *target)
    {
        const auto normal = new NineSlice("res/button.png", {32, 32, 48, 32}, renderer);
        const auto hover = new NineSlice("res/buttonhover.png", {32, 32, 40, 32}, renderer);
        hover->visible = false;

        const std::function on_mouse_enter = [=]
        {
            normal->visible = false;
            hover->visible = true;
            target->transform->position.z += 4;
            target->transform->scale.y += -8;
            const float random_rotation = SDL_randf() * 6 - 3;

            AnimationManager::play(
                [=](const double t)
                {
                    target->animation->rotation = (float)(t * random_rotation);
                    target->animation->scale.x = t * 15;
                    target->animation->scale.y = t * 20;
                },
                Easings::ease_out_elastic, 0.5);
        };

        const std::function on_mouse_exit = [=]
        {
            normal->visible = true;
            hover->visible = false;
            target->transform->position.z += -4;
            target->transform->scale.y += 8;
            const float initial_rotation = target->animation->rotation;

            AnimationManager::play(
                [=](const double t)
                {
                    target->animation->rotation = (float)((1 - t) * initial_rotation);
                    target->animation->scale.x = (1 - t) * 15;
                    target->animation->scale.y = (1 - t) * 20;
                },
                Easings::ease_out_elastic, 0.5);
        };

        target
            ->add_component(new Button(Button::EventHandlers{
                .on_mouse_up = on_click,
                .on_mouse_over = on_mouse_enter,
                .on_mouse_exit = on_mouse_exit,
            }))
            ->add_component(normal)
            ->add_component(hover)
            ->add_child((new Entity("Text"))
                            ->add_component(new TextRenderer(renderer, text, pt_size, {255, 255, 255}))
                            ->transform->apply({0, 0, -10}, {0, 0}, {0.5f, 0.5f}, 0.0f, 0));
    };
}
#include "../components/cursor.h"
#include "../components/nineslice.h"
#include "../components/onstart.h"
#include "../managers/fontmanager.h"
#include "index.h"

void set_placeholder(TextRenderer* text_renderer, const char* text, const char* placeholder)
{
    if (placeholder != nullptr && strlen(text) == 0)
    {
        text_renderer->set_text(placeholder);
        text_renderer->set_color({128, 138, 168});
    }
}

Preset Presets::text_input(SDL_Renderer* renderer, char* text, const size_t max_length, const char* placeholder,
                          const int pt_size)
{
    return [=](Entity* target)
    {
        const auto text_renderer = new TextRenderer(renderer, text, pt_size, {64, 64, 64});

        target->add_component(new TextInput(text, max_length, [=](const char* newText)
        {
            text_renderer->set_text(newText);
            text_renderer->set_color({64, 64, 64});
            set_placeholder(text_renderer, text, placeholder);
        }));

        target->add_component(new OnStart([=]
        {
            set_placeholder(text_renderer, text, placeholder);
        }));

        target->add_component(new NineSlice("res/textinput.png", {32, 32, 48, 32}, renderer));

        target->add_child((new Entity("Text"))
                         ->transform
                         ->apply({-120, 0, -10}, {0, 0}, {0.0f, 0.5f}, 0.0f, 0)
                         ->add_component(text_renderer));

        target->add_child((new Entity("Cursor"))
                         ->transform
                         ->apply({0, 0, -10}, {5, FontManager::DEFAULT}, {0.0f, 0.5f}, 0.0f, 0)
                         ->add_component(new Cursor(pt_size))
                         ->add_component(new SpriteRenderer("res/cursor.png", renderer)));
    };
}

Preset Presets::readonly_text_input(SDL_Renderer* renderer, const char* text, const int pt_size)
{
    return [=](Entity* target)
    {
        target
            ->add_component(new NineSlice("res/textinput.png", {32, 32, 48, 32}, renderer))

            ->add_child((new Entity("Text"))
                       ->transform
                       ->apply({-120, 0, -10}, {0, 0}, {0.0f, 0.5f}, 0.0f, 0)
                       ->add_component(new TextRenderer(renderer, text, pt_size, {64, 64, 64})));
    };
}
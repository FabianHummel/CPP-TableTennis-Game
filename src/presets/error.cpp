#include "index.h"
#include "../components/nineslice.h"
#include "../components/textrenderer.h"

Preset Presets::error(SDL_Renderer* renderer, const char* text, const int pt_size)
{
    return [=](Entity* target)
    {
        target
            ->add_component(new NineSlice("res/error.png", {32, 32, 48, 32}, renderer))

            ->add_child((new Entity("Text"))
                       ->transform
                       ->apply({20, 0, 20}, {0, 0}, {0.0, 0.0}, 0.0f, 0)
                       ->add_component(new TextRenderer(renderer, text, pt_size, {79, 26, 26})));
    };
}
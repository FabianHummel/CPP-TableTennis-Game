#include "index.h"
#include "../components/nineslice.h"
#include "../components/textrenderer.h"

Preset Presets::error(SDL_Renderer *renderer, const char* text, const int ptSize)
{
    return [=](Entity *target)
    {
        target
            ->addComponent(new NineSlice("res/error.png", { 32, 32, 48, 32 }, renderer))

            ->addChild((new Entity("Text"))
                ->transform
                ->apply({ 20, 0, 20 }, { 0, 0 }, { 0.0, 0.0 }, 0.0f, 0)
                ->addComponent(new TextRenderer(renderer, text, ptSize, { 79, 26, 26 })));
    };
}

//
// Created by Fabian Hummel on 15.02.26.
//

#include "errormanager.h"

#include "componentsystem.h"
#include "ecsmanager.h"
#include "fontmanager.h"
#include "components/error.h"
#include "presets/index.h"
#include "utility/renderindexes.h"

std::vector<const char*> ErrorManager::errors = std::vector<const char*>();

void ErrorManager::queueError(const char *error)
{
    errors.push_back(error);
}

void ErrorManager::showErrors(SDL_Renderer *renderer)
{
    for (const auto error : errors)
    {
        const auto entity = EcsManager::addEntity(new Entity("Error-Message"))
            ->usePreset(Presets::error(renderer, error, FontManager::SMALL))
            ->transform
            ->apply({ 20.0, 0.0, 20.0 }, { 600.0, 150.0 }, { 0.0, 0.0 }, 0.0f, RenderIndexes::ERROR)
            ->addComponent(new Error(5.0));

        entity->initialize();
        entity->start();
    }

    errors.clear();
}

#include "debugger.h"
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "../managers/fontmanager.h"

Debugger::Debugger(SDL_Renderer *renderer, const bool extended_debug_info)
{
    this->name = "Debugger";
    this->extended_debug_info = extended_debug_info;
    this->renderer = renderer;
}

Debugger::Debugger(SDL_Renderer *renderer) : Debugger(renderer, false)
{
    this->renderer = renderer;
}

void Debugger::on_initialize()
{
    this->transform = parent->transform;
}

void render_string(const char *param_name, const double value, const float pos, SDL_Renderer *renderer)
{
    char *str;
    asprintf(&str, "%s: %f", param_name, value);
    SDL_Surface *surface = TTF_RenderText_Blended(FontManager::mono, str, 0, {0, 0, 0, 255});
    const auto texture = SDL_CreateTextureFromSurface(renderer, surface);
    const auto dst_rect = SDL_FRect{0.0, pos * FontManager::DEFAULT, (float)surface->w, (float)surface->h};
    SDL_RenderTexture(renderer, texture, nullptr, &dst_rect);
}

void Debugger::on_update(double deltaTime)
{
    SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

    const auto [x, y, w, h] = transform->get_calculated_rect();

    SDL_FRect pos;
    pos.x = x - 5;
    pos.y = y - 5;
    pos.w = 10;
    pos.h = 10;
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
    SDL_RenderFillRect(renderer, &pos);

    SDL_FRect area;
    area.x = x;
    area.y = y;
    area.w = w;
    area.h = h;
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);
    SDL_RenderFillRect(renderer, &area);

    SDL_FRect anchor;
    anchor.x = x + w * transform->anchor.x - 5;
    anchor.y = y + h * transform->anchor.y - 5;
    anchor.w = 10;
    anchor.h = 10;
    SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
    SDL_RenderFillRect(renderer, &anchor);

    if (!extended_debug_info)
        return;

    render_string("X", transform->position.x, 0, renderer);
    render_string("Y", transform->position.y, 1, renderer);
    render_string("Z", transform->position.z, 2, renderer);
}
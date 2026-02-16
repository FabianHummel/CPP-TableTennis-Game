#pragma once

#include "componentsystem.h"
#include <SDL3/SDL_pixels.h>
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

class TextRenderer : public Component
{
private:
    SDL_Texture* texture{};
    SDL_Renderer* renderer;
    Transform* transform{};
    const char* text;
    SDL_Color color{};
    TTF_Font* font;
    int pt_size;

    void update_texture();

public:
    bool visible = true;

    TextRenderer(SDL_Renderer* renderer, const char* text, int pt_size, SDL_Color color);

    void on_initialize() override;
    void on_update(double delta_time) override;

    void set_text(const char* text);
    void set_color(SDL_Color color);
};
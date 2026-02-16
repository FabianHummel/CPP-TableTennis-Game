#pragma once

#include "componentsystem.h"

class SpriteRenderer : public Component
{
private:
    SDL_Texture* texture{};
    SDL_Renderer* renderer;
    Transform* transform{};
    const char* img;
    SDL_FRect* src_rect = nullptr;

public:
    bool visible = true;

    SpriteRenderer(const char* img, SDL_Renderer* renderer);
    //SpriteRenderer(const char *svgImg, SDL_Renderer *renderer, int width, int height);

    void on_initialize() override;
    void on_start() override;
    void on_update(double delta_time) override;
    void on_delete() override;

    void set_src_rect(SDL_FRect rect);
    void set_image(const char* img);
};
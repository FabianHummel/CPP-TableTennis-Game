#include "spriterenderer.h"

#include <SDL3_image/SDL_image.h>

SpriteRenderer::SpriteRenderer(const char *img, SDL_Renderer *renderer)
{
    this->name = "Sprite Renderer";
    this->renderer = renderer;
    this->img = img;
}

// SpriteRenderer::SpriteRenderer(const char *svgImg, SDL_Renderer *renderer, int width, int height)
// {
// 	this->name = "Sprite Renderer";
// 	this->renderer = renderer;
// 	this->svgImg = svgImg;
// 	this->width = width;
// 	this->height = height;
// }

void SpriteRenderer::on_initialize()
{
    this->transform = parent->transform;
}

void SpriteRenderer::on_start()
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Loading Texture %s\n", img);

    this->texture = IMG_LoadTexture(renderer, img);

    if (this->texture == nullptr)
    {
        SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load Texture %s: %s\n", img, SDL_GetError());
    }
}

void SpriteRenderer::on_update(double delta_time)
{
    if (!visible || !parent->is_visible())
        return;

    const SDL_FRect dst_rect = transform->get_calculated_rect();
    SDL_SetTextureAlphaMod(texture, parent->get_calculated_opacity());
    SDL_RenderTextureRotated(renderer, texture, src_rect, &dst_rect, transform->get_calculated_rotation(), nullptr,
                             SDL_FLIP_NONE);
}

void SpriteRenderer::on_delete()
{
    SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Unloading Texture %s\n", img);
    SDL_DestroyTexture(this->texture);
}

void SpriteRenderer::set_src_rect(const SDL_FRect rect)
{
    this->src_rect = new SDL_FRect(rect);
}

void SpriteRenderer::set_image(const char *img)
{
    this->img = img;
    this->on_delete();
    this->on_start();
}
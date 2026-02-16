#include "nineslice.h"

#include <SDL3_image/SDL_image.h>

NineSlice::NineSlice(const char* img, const Positions positions, SDL_Renderer* renderer)
{
    this->name = "Nine Slice";
    this->renderer = renderer;
    this->img = img;
    this->positions = positions;
}

void NineSlice::on_initialize()
{
    this->transform = parent->transform;
}

void NineSlice::on_start()
{
    SDL_Texture* old_render_target = SDL_GetRenderTarget(renderer);

    float top = (float)positions.top;
    float right = (float)positions.right;
    float bottom = (float)positions.bottom;
    float left = (float)positions.left;

    float w = (float)transform->scale.x;
    float h = (float)transform->scale.y;

    SDL_FPoint size;
    SDL_Texture* source = IMG_LoadTexture(renderer, img);
    SDL_GetTextureSize(source, &size.x, &size.y);

    texture = SDL_CreateTexture(
        renderer,
        SDL_PIXELFORMAT_RGBA4444,
        SDL_TEXTUREACCESS_TARGET,
        (int)w, (int)h);

    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
    SDL_SetRenderTarget(renderer, texture);

    {
        //top left
        SDL_FRect dst = {0, 0, left, top};
        SDL_FRect src = {0, 0, left, top};
        SDL_RenderTexture(renderer, source, &src, &dst);
    }
    {
        //top right
        SDL_FRect dst = {w - right, 0, right, top};
        SDL_FRect src = {size.x - right, 0, right, top};
        SDL_RenderTexture(renderer, source, &src, &dst);
    }
    {
        //bottom left
        SDL_FRect dst = {0, h - bottom, left, bottom};
        SDL_FRect src = {0, size.y - bottom, left, bottom};
        SDL_RenderTexture(renderer, source, &src, &dst);
    }
    {
        //bottom right
        SDL_FRect dst = {w - right, h - bottom, right, bottom};
        SDL_FRect src = {size.x - right, size.y - bottom, right, bottom};
        SDL_RenderTexture(renderer, source, &src, &dst);
    }
    {
        //top
        SDL_FRect dst = {left, 0, w - left - right, top};
        SDL_FRect src = {left, 0, size.x - left - right, top};
        SDL_RenderTexture(renderer, source, &src, &dst);
    }
    {
        //bottom
        SDL_FRect dst = {left, h - bottom, w - left - right, bottom};
        SDL_FRect src = {left, size.y - bottom, size.x - left - right, bottom};
        SDL_RenderTexture(renderer, source, &src, &dst);
    }
    {
        //left
        SDL_FRect dst = {0, top, left, h - top - bottom};
        SDL_FRect src = {0, top, left, size.y - top - bottom};
        SDL_RenderTexture(renderer, source, &src, &dst);
    }
    {
        //right
        SDL_FRect dst = {w - right, top, right, h - top - bottom};
        SDL_FRect src = {size.x - right, top, right, size.y - top - bottom};
        SDL_RenderTexture(renderer, source, &src, &dst);
    }
    {
        //center
        SDL_FRect dst = {left, top, w - left - right, h - top - bottom};
        SDL_FRect src = {left, top, size.x - left - right, size.y - top - bottom};
        SDL_RenderTexture(renderer, source, &src, &dst);
    }

    SDL_SetRenderTarget(renderer, old_render_target);
    SDL_DestroyTexture(source);
}

// based on https://github.com/cxong/sdl2-9-slice/blob/master/main.c
void NineSlice::on_update(double delta_time)
{
    if (!visible || !parent->is_visible()) return;

    const Vector2 scale = transform->get_calculated_scale();
    const SDL_FRect dst = transform->get_calculated_rect();

    const SDL_FPoint anchor = {
        .x = (float)(transform->anchor.x * scale.x),
        .y = (float)(transform->anchor.y * scale.y)
    };

    SDL_SetTextureAlphaMod(texture, parent->get_calculated_opacity());
    SDL_RenderTextureRotated(renderer, this->texture, nullptr, &dst, transform->get_calculated_rotation(), &anchor,
                             SDL_FLIP_NONE);
}

void NineSlice::on_delete()
{
    SDL_DestroyTexture(this->texture);
}

void NineSlice::setImage(const char* img, const Positions positions)
{
    this->img = img;
    this->positions = positions;
    this->on_delete();
    this->on_start();
}
#include "textrenderer.h"
#include "../managers/fontmanager.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>

TextRenderer::TextRenderer(SDL_Renderer* renderer, const char* text, const int pt_size, const SDL_Color color)
{
    this->name = "Text Renderer";
    this->pt_size = pt_size;
    this->renderer = renderer;
    this->text = text;
    this->color = color;
    this->font = FontManager::main;
}

void TextRenderer::on_initialize()
{
    this->transform = parent->transform;
    update_texture();
}

void TextRenderer::on_update(double delta_time)
{
    if (!visible || !parent->is_visible()) return;

    transform->scale = {(float)texture->w, (float)texture->h};

    const SDL_FRect dst_rect = transform->get_calculated_rect();
    SDL_SetTextureAlphaMod(texture, parent->get_calculated_opacity());
    SDL_RenderTextureRotated(renderer, texture, nullptr, &dst_rect, transform->get_calculated_rotation(), nullptr,
                             SDL_FLIP_NONE);
}

void TextRenderer::set_text(const char* text)
{
    this->text = text;
    update_texture();
}

void TextRenderer::set_color(const SDL_Color color)
{
    this->color = color;
    update_texture();
}

void TextRenderer::update_texture()
{
    SDL_DestroyTexture(texture);
    TTF_SetFontSize(FontManager::main, (float)pt_size);
    SDL_Surface* surface = TTF_RenderText_Blended_Wrapped(font, text, 0, color, 0);
    this->texture = SDL_CreateTextureFromSurface(renderer, surface);
    SDL_DestroySurface(surface);
}
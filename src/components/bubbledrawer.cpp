#include "bubbledrawer.h"
#include "../utility/renderwindow.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3_image/SDL_image.h>
#include <cmath>

BubbleDrawer::BubbleDrawer(SDL_Renderer *renderer)
{
    this->name = "Bubble Drawer";
    this->renderer = renderer;
    this->texture = IMG_LoadTexture(renderer, "res/background.png");
    SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

void BubbleDrawer::on_initialize()
{
    this->transform = parent->transform;
}

void BubbleDrawer::on_update(const double delta_time)
{
    time += delta_time;
    const double x_off = fmod(time * SPEED, 80.0);
    const double y_off = fmod(time * SPEED, 80.0) * 0.05;

    SDL_FRect dstrect;
    dstrect.x = -100.0 + x_off;
    dstrect.y = -180.0 + RenderWindow::SCREEN_HEIGHT - RenderWindow::SCREEN_WIDTH + y_off;
    dstrect.w = RenderWindow::SCREEN_WIDTH + 200.0;
    dstrect.h = RenderWindow::SCREEN_WIDTH + 200.0;

    SDL_RenderTextureRotated(renderer, texture, nullptr, &dstrect, 3.5, nullptr, SDL_FLIP_NONE);
}
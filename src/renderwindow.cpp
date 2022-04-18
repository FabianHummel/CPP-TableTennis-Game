//
// Created by Fabian Hummel on 16.04.22.
//

#include <SDL.h>
#include <SDL_image.h>
#include "renderwindow.h"
#include "string"

RenderWindow::RenderWindow(int width, int height, const char *title) {
    if(SDL_Init(SDL_INIT_VIDEO) < 0){
        printf("Error: SDL failed to initialize\nSDL Error: '%s'\n", SDL_GetError());
        return;
    }

    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
    window = SDL_CreateWindow(title,
      SDL_WINDOWPOS_UNDEFINED,
      SDL_WINDOWPOS_UNDEFINED,
      width / 2, height / 2, SDL_WINDOW_ALLOW_HIGHDPI + SDL_WINDOW_OPENGL
    );
    if(!window){
        printf("Error: Failed to open window\nSDL Error: '%s'\n", SDL_GetError());
        return;
    }

    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if(!renderer){
        printf("Error: Failed to create renderer\nSDL Error: '%s'\n", SDL_GetError());
        return;
    }
}

RenderWindow::~RenderWindow() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

void RenderWindow::drawBG(const SDL_Color color) {
    SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
}

void RenderWindow::clear() {
    SDL_RenderClear(renderer);
}

void RenderWindow::destroy() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
}

RenderTarget *RenderWindow::createTarget(const char *file, int *posX, int *posY, int width, int height) const {
    SDL_Texture *texture = IMG_LoadTexture(renderer, file);
    if (!texture) {
        throw std::runtime_error(
            "Error: Failed to load texture\nSDL Error: '%s'\n" + std::string(SDL_GetError())
        );
    }

    return new RenderTarget(texture, posX, posY, width, height);
}

RenderTarget *RenderWindow::createTarget(const char *file, EntityBase *entity, int width, int height) const {
    return createTarget(file, &entity->renderX, &entity->renderY, width, height);
}
#include <SDL_render.h>
#include <SDL_image.h>
#include "spriterenderer.h"


SpriteRenderer::SpriteRenderer(const char *img, SDL_Renderer *renderer, int x, int y, int w, int h) {
  this->renderer = renderer;
  this->img = img;
  this->x = x;
  this->y = y;
  this->w = w;
  this->h = h;
}

void SpriteRenderer::onInitialize() {

}

void SpriteRenderer::onStart() {
	texture = IMG_LoadTexture(renderer, img);
}

void SpriteRenderer::onUpdate() {
	SDL_Rect rect;
	rect.x = x;
	rect.y = y;
	rect.w = w;
	rect.h = h;

	SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

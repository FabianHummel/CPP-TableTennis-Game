#include <SDL_render.h>
#include <SDL_image.h>
#include "spriterenderer.h"

SpriteRenderer::SpriteRenderer(const char *img, SDL_Renderer *renderer) {
	this->renderer = renderer;
	this->img = img;
}

void SpriteRenderer::onInitialize() {
	printf("Initializing Sprite Renderer Script\n");
	transform = parent->getComponent<Transform>();
}

void SpriteRenderer::onStart() {
	printf("Loading Texture %s\n", img);
	texture = IMG_LoadTexture(renderer, img);
}

void SpriteRenderer::onUpdate() {
	SDL_Rect rect;
	rect.x = (int) transform->getX();
	rect.y = (int) ( -transform->getY() + transform->getZ() );
	rect.w = transform->getScaleX();
	rect.h = transform->getScaleY();

	SDL_SetTextureAlphaMod(texture, opacity);
	SDL_RenderCopy(renderer, texture, nullptr, &rect);
}

void SpriteRenderer::setImage(const char *v) {
	this->img = v;
}

void SpriteRenderer::setOpacity(int v) {
	this->opacity = v;
}

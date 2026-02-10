#include "spriterenderer.h"

#include <SDL3_image/SDL_image.h>

SpriteRenderer::SpriteRenderer(const char *img, SDL_Renderer *renderer)
{
	this->renderer = renderer;
	this->img = img;
}

void SpriteRenderer::onInitialize()
{
	printf("Initializing Sprite Renderer on %s\n", parent->name);
	this->transform = parent->transform;
}

void SpriteRenderer::onStart()
{
	printf("Loading Texture %s\n", img);
	this->texture = IMG_LoadTexture(renderer, img);
}

void SpriteRenderer::onUpdate(double deltaTime)
{
	if (!visible || !parent->isVisible()) return;

	SDL_FRect dstrect = transform->asRect();
	SDL_SetTextureAlphaMod(texture, parent->getOpacity());
	SDL_RenderTextureRotated(renderer, texture, srcrect, &dstrect, transform->getRotation(), nullptr, SDL_FLIP_NONE);
}

void SpriteRenderer::onDelete()
{
	printf("Unloading Texture %s\n", img);
	SDL_DestroyTexture(this->texture);
}

void SpriteRenderer::setSrcrect(SDL_FRect rect)
{
	this->srcrect = new SDL_FRect(rect);
}

void SpriteRenderer::setImage(const char *v)
{
	this->img = v;
	this->onDelete();
	this->onStart();
}
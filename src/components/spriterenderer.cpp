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

void SpriteRenderer::onInitialize()
{
	this->transform = parent->transform;
}

void SpriteRenderer::onStart()
{
	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Loading Texture %s\n", img);

	this->texture = IMG_LoadTexture(renderer, img);

	if (this->texture == nullptr) {
		SDL_LogError(SDL_LOG_CATEGORY_APPLICATION, "Failed to load Texture %s: %s\n", img, SDL_GetError());
	}
}

void SpriteRenderer::onUpdate(double deltaTime)
{
	if (!visible || !parent->isVisible()) return;

	SDL_FRect dstrect = transform->getCalculatedRect();
	SDL_SetTextureAlphaMod(texture, parent->getOpacity());
	SDL_RenderTextureRotated(renderer, texture, srcrect, &dstrect, transform->getCalculatedRotation(), nullptr, SDL_FLIP_NONE);
}

void SpriteRenderer::onDelete()
{
	SDL_LogDebug(SDL_LOG_CATEGORY_APPLICATION, "Unloading Texture %s\n", img);
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
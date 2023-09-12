#include "spriterenderer.h"

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
	if (!isVisible())
		return;

	SDL_FRect dstrect;
	dstrect.x = transform->getX() - transform->getScaleX() * transform->getAnchor().x;
	dstrect.y = -transform->getY() + transform->getZ() - transform->getScaleY() * transform->getAnchor().y;
	dstrect.w = transform->getScaleX();
	dstrect.h = transform->getScaleY();

	SDL_SetTextureAlphaMod(texture, opacity);
	SDL_RenderCopyExF(renderer, texture, srcrect, &dstrect, transform->getRotation(), nullptr, SDL_FLIP_NONE);
}

void SpriteRenderer::onDelete()
{
	printf("Unloading Texture %s\n", img);
	SDL_DestroyTexture(this->texture);
}

void SpriteRenderer::setImage(const char *v)
{
	this->img = v;
	this->onDelete();
	this->onStart();
}

void SpriteRenderer::setOpacity(int v)
{
	this->opacity = v;
}

void SpriteRenderer::setSrcrect(SDL_Rect rect)
{
	this->srcrect = new SDL_Rect(rect);
}

void SpriteRenderer::setVisible(bool v)
{
	this->visible = v;
}

bool SpriteRenderer::isVisible() const
{
	return this->visible;
}

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
	if (isVisible()) {
		SDL_Rect destrect;
		destrect.x = (int) transform->getX();
		destrect.y = (int) ( -transform->getY() + transform->getZ() );
		destrect.w = transform->getScaleX();
		destrect.h = transform->getScaleY();

		SDL_SetTextureAlphaMod(texture, opacity);

		SDL_RenderCopyEx(
			renderer, texture, srcrect, &destrect, transform->getRotation(), transform->getAnchor(), SDL_FLIP_NONE
		);
	}
}

void SpriteRenderer::setImage(const char *v) {
	this->img = v;
}

void SpriteRenderer::setOpacity(int v) {
	this->opacity = v;
}

void SpriteRenderer::setSrcrect(SDL_Rect rect) {
	this->srcrect = new SDL_Rect(rect);
}

void SpriteRenderer::setVisible(bool v) {
	this->visible = v;
}

bool SpriteRenderer::isVisible() const {
	return this->visible;
}

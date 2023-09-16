#include "nineslice.h"

NineSlice::NineSlice(const char *img, const Positions positions, SDL_Renderer *renderer)
{
	this->renderer = renderer;
	this->img = img;
	this->positions = positions;
}

void NineSlice::onInitialize()
{
	printf("Initializing 9-Slice on %s\n", parent->name);
	this->transform = parent->transform;
}

void NineSlice::onStart()
{
	printf("Loading 9-Slice %s\n", img);

	SDL_Texture *oldRenderTarget = SDL_GetRenderTarget(renderer);

	int top = positions.top;
	int right = positions.right;
	int bottom = positions.bottom;
	int left = positions.left;

	int w = transform->getScaleX();
	int h = transform->getScaleY();

	SDL_Point size;
	SDL_Texture *source = IMG_LoadTexture(renderer, img);
	SDL_QueryTexture(source, nullptr, nullptr, &size.x, &size.y);

	texture = SDL_CreateTexture(
		renderer,
		SDL_PixelFormatEnum::SDL_PIXELFORMAT_RGBA4444,
		SDL_TextureAccess::SDL_TEXTUREACCESS_TARGET,
		w, h);

	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
	SDL_SetRenderTarget(renderer, texture);

	{ //top left
		SDL_Rect dst = { 0, 0, left, top };
		SDL_Rect src = { 0, 0, left, top };
		SDL_RenderCopy(renderer, source, &src, &dst);
	}
	{ //top right
		SDL_Rect dst = { w - right, 0, right, top };
		SDL_Rect src = { size.x - right, 0, right, top };
		SDL_RenderCopy(renderer, source, &src, &dst);
	}
	{ //bottom left
		SDL_Rect dst = { 0, h - bottom, left, bottom };
		SDL_Rect src = { 0, size.y - bottom, left, bottom };
		SDL_RenderCopy(renderer, source, &src, &dst);
	}
	{ //bottom right
		SDL_Rect dst = { w - right, h - bottom, right, bottom };
		SDL_Rect src = { size.x - right, size.y - bottom, right, bottom };
		SDL_RenderCopy(renderer, source, &src, &dst);
	}
	{ //top
		SDL_Rect dst = { left, 0, w - left - right, top };
		SDL_Rect src = { left, 0, size.x - left - right, top };
		SDL_RenderCopy(renderer, source, &src, &dst);
	}
	{ //bottom
		SDL_Rect dst = { left, h - bottom, w - left - right, bottom };
		SDL_Rect src = { left, size.y - bottom, size.x - left - right, bottom };
		SDL_RenderCopy(renderer, source, &src, &dst);
	}
	{ //left
		SDL_Rect dst = { 0, top, left, h - top - bottom };
		SDL_Rect src = { 0, top, left, size.y - top - bottom };
		SDL_RenderCopy(renderer, source, &src, &dst);
	}
	{ //right
		SDL_Rect dst = { w - right, top, right, h - top - bottom };
		SDL_Rect src = { size.x - right, top, right, size.y - top - bottom };
		SDL_RenderCopy(renderer, source, &src, &dst);
	}
	{ //center
		SDL_Rect dst = { left, top, w - left - right, h - top - bottom };
		SDL_Rect src = { left, top, size.x - left - right, size.y - top - bottom };
		SDL_RenderCopy(renderer, source, &src, &dst);
	}

	SDL_SetRenderTarget(renderer, oldRenderTarget);
	SDL_DestroyTexture(source);
}

// based on https://github.com/cxong/sdl2-9-slice/blob/master/main.c
void NineSlice::onUpdate(double deltaTime)
{
	if (!visible || !parent->isVisible()) return;

	SDL_FRect dst;
	dst.x = transform->getX() - transform->getScaleX() * transform->getAnchor().x;
	dst.y = -transform->getY() + transform->getZ() - transform->getScaleY() * transform->getAnchor().y;
	dst.w = transform->getScaleX();
	dst.h = transform->getScaleY();

	SDL_FPoint anchor = {transform->getAnchor().x * transform->getScaleX(), transform->getAnchor().y * transform->getScaleY()};

	SDL_SetTextureAlphaMod(texture, parent->getOpacity());
	SDL_RenderCopyExF(renderer, this->texture, nullptr, &dst, transform->getRotation(), &anchor, SDL_FLIP_NONE);
}

void NineSlice::onDelete()
{
	printf("Unloading 9-Slice %s\n", img);
	SDL_DestroyTexture(this->texture);
}

void NineSlice::setImage(const char *v, Positions positions)
{
	this->img = v;
	this->positions = positions;
	this->onDelete();
	this->onStart();
}
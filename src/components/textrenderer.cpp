#include "../fontmanager.h"
#include "textrenderer.h"
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <SDL3/SDL_surface.h>
#include <SDL3_ttf/SDL_ttf.h>

TextRenderer::TextRenderer(SDL_Renderer *renderer, const char *text, int ptSize, SDL_Color color)
{
	this->name = "Text Renderer";
	this->ptSize = ptSize;
	this->renderer = renderer;
	this->text = text;
	this->color = color;
	this->font = FontManager::main;
}

void TextRenderer::onInitialize()
{
	this->transform = parent->transform;
	updateTexture();
}

void TextRenderer::onUpdate(double deltaTime)
{
	if (!visible || !parent->isVisible()) return;

	transform->scale = {(float)texture->w, (float)texture->h};

	SDL_FRect dstrect = transform->getCalculatedRect();
	SDL_SetTextureAlphaMod(texture, parent->getOpacity());
	SDL_RenderTextureRotated(renderer, texture, nullptr, &dstrect, transform->getCalculatedRotation(), nullptr, SDL_FLIP_NONE);
}

void TextRenderer::setText(const char *text)
{
	this->text = text;
	updateTexture();
}

void TextRenderer::setColor(const SDL_Color color)
{
	this->color = color;
	updateTexture();
}

void TextRenderer::updateTexture()
{
	SDL_DestroyTexture(texture);
	TTF_SetFontSize(FontManager::main, (float)ptSize);
	SDL_Surface *surface = TTF_RenderText_Blended_Wrapped(font, text, 0, color, 0);
	this->texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_DestroySurface(surface);
}

#include "../fontmanager.h"
#include "textrenderer.h"
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>

TextRenderer::TextRenderer(SDL_Renderer *renderer, const char *text, int ptSize, SDL_Color color)
{
	this->ptSize = ptSize;
	this->renderer = renderer;
	this->text = text;
	this->color = color;
	this->font = FontManager::main;
	updateTexture();
}

void TextRenderer::onInitialize()
{
	this->transform = parent->transform;
}

void TextRenderer::onUpdate(double deltaTime)
{
	if (!visible || !parent->isVisible()) return;

	int w, h;
	TTF_SetFontSize(FontManager::main, ptSize);
	TTF_SizeText(FontManager::main, text, &w, &h);
	transform->setScale({(float)w, (float)h});

	SDL_FRect dstrect = transform->asRect();
	SDL_SetTextureAlphaMod(texture, parent->getOpacity());
	SDL_RenderCopyExF(renderer, texture, nullptr, &dstrect, transform->getRotation(), nullptr, SDL_FLIP_NONE);
}

void TextRenderer::setText(const char *text)
{
	this->text = text;
	updateTexture();
}

void TextRenderer::setColor(SDL_Color color)
{
	this->color = color;
	updateTexture();
}

void TextRenderer::updateTexture()
{
	SDL_DestroyTexture(texture);
	TTF_SetFontSize(FontManager::main, ptSize);
	SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
	this->texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

#include <SDL.h>
#include <SDL_rect.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include <SDL_render.h>
#include <SDL_events.h>
#include <cstdlib>
#include <string>
#include "textrenderer.h"
#include "../render/fontmanager.h"

TextRenderer::TextRenderer(SDL_Renderer *renderer, const char *text, SDL_Color color)
{
	this->renderer = renderer;
	this->text = text;
	this->color = color;
	this->font = FontManager::main;
	updateTexture();
}

void TextRenderer::onInitialize()
{
	this->transform = parent->getTransform();
}

void TextRenderer::onUpdate(double deltaTime)
{
	int w, h;
	TTF_SizeText(FontManager::main, text, &w, &h);

	SDL_FRect dstrect;
	dstrect.x = transform->getX() - w * transform->getAnchor().x;
	dstrect.y = transform->getZ() - h * transform->getAnchor().y;
	dstrect.w = w;
	dstrect.h = h;
	
	SDL_FPoint anchor = transform->getAnchor();

	SDL_RenderCopyExF(
		renderer, texture, nullptr, &dstrect, transform->getRotation(), &anchor, SDL_FLIP_NONE);
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
	SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
	SDL_DestroyTexture(texture);
	this->texture = SDL_CreateTextureFromSurface(renderer, surface);
}

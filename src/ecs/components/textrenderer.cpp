#include "textrenderer.h"
#include "../../render/fontmanager.h"
#include <SDL.h>
#include <SDL_events.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <SDL_surface.h>
#include <SDL_ttf.h>
#include <cstdlib>
#include <string>

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
	this->transform = parent->transform;
}

void TextRenderer::onUpdate(double deltaTime)
{
	if (!visible || !parent->isVisible()) return;

	int w, h;
	TTF_SizeText(FontManager::main, text, &w, &h);

	SDL_FRect dstrect;
	dstrect.x = transform->getX() - w * transform->getAnchor().x;
	dstrect.y = transform->getZ() - h * transform->getAnchor().y;
	dstrect.w = w;
	dstrect.h = h;

	SDL_FPoint anchor = {transform->getAnchor().x * w, transform->getAnchor().y * h};

	SDL_SetTextureAlphaMod(texture, parent->getOpacity());
	SDL_RenderCopyExF(renderer, texture, nullptr, &dstrect, transform->getRotation(), &anchor, SDL_FLIP_NONE);
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
	SDL_Surface *surface = TTF_RenderText_Blended(font, text, color);
	this->texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FreeSurface(surface);
}

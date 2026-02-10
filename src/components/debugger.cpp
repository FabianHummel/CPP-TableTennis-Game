#include "debugger.h"
#include <SDL3/SDL_render.h>
#include <SDL3_ttf/SDL_ttf.h>

#include "../fontmanager.h"

Debugger::Debugger(SDL_Renderer *renderer, bool extendedDebugInfo)
{
	this->extendedDebugInfo = extendedDebugInfo;
	this->renderer = renderer;
}

Debugger::Debugger(SDL_Renderer *renderer) : Debugger(renderer, false)
{
	this->renderer = renderer;
}

void Debugger::onInitialize()
{
	this->transform = parent->transform;
}

void renderString(Transform *transform, const char* paramName, float value, float pos, SDL_Renderer *renderer)
{
	char *str; asprintf(&str, "%s: %f", paramName, value);
	SDL_Surface *surface = TTF_RenderText_Blended(FontManager::mono, str, 0, {0,0,0,255});
	const auto texture = SDL_CreateTextureFromSurface(renderer, surface);
	SDL_FRect dstRect = SDL_FRect {0.0, pos * FontManager::DEFAULT, (float)surface->w, (float)surface->h};
	SDL_RenderTexture(renderer, texture, nullptr, &dstRect);
}

void Debugger::onUpdate(double deltaTime)
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	SDL_FRect rec = transform->asRect();

	SDL_FRect pos;
	pos.x = rec.x - 5;
	pos.y = rec.y - 5;
	pos.w = 10;
	pos.h = 10;
	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
	SDL_RenderFillRect(renderer, &pos);

	SDL_FRect area;
	area.x = rec.x;
	area.y = rec.y;
	area.w = rec.w;
	area.h = rec.h;
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);
	SDL_RenderFillRect(renderer, &area);

	SDL_FRect anchor;
	anchor.x = rec.x + rec.w * transform->getAnchor().x - 5;
	anchor.y = rec.y + rec.h * transform->getAnchor().y - 5;
	anchor.w = 10;
	anchor.h = 10;
	SDL_SetRenderDrawColor(renderer, 0, 255, 0, 255);
	SDL_RenderFillRect(renderer, &anchor);

	if (!extendedDebugInfo) return;

	renderString(transform, "X", transform->getX(), 0, renderer);
	renderString(transform, "Y", transform->getY(), 1, renderer);
	renderString(transform, "Z", transform->getZ(), 2, renderer);
}

void Debugger::onEvent(const SDL_Event *event)
{
}

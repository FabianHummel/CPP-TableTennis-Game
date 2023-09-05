#include "debugger.h"
#include <SDL_render.h>

Debugger::Debugger(SDL_Renderer *renderer)
{
	this->renderer = renderer;
}

void Debugger::onInitialize()
{
	this->transform = parent->getTransform();
}

void Debugger::onUpdate(double deltaTime)
{
	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	SDL_Rect rec = transform->asRect();

	SDL_Rect pos;
	pos.x = rec.x - 5;
	pos.y = rec.y - 5;
	pos.w = 10;
	pos.h = 10;
	SDL_SetRenderDrawColor(renderer, 20, 60, 160, 255);
	SDL_RenderFillRect(renderer, &pos);

	rec.x -= rec.w * transform->getAnchor().x;
	rec.y -= rec.h * transform->getAnchor().y;
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 100);
	SDL_RenderFillRect(renderer, &rec);

	SDL_Rect anchor;
	anchor.x = rec.x - 5;
	anchor.y = rec.y - 5;
	anchor.w = 10;
	anchor.h = 10;
	SDL_SetRenderDrawColor(renderer, 55, 160, 20, 255);
	SDL_RenderFillRect(renderer, &anchor);
}

void Debugger::onEvent(SDL_Event event)
{
}

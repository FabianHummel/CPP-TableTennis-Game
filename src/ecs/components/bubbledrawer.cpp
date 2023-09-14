#include "bubbledrawer.h"
#include "../../render/renderwindow.h"
#include <SDL_image.h>
#include <SDL_rect.h>
#include <SDL_render.h>
#include <cmath>

BubbleDrawer::BubbleDrawer(SDL_Renderer *renderer)
{
	this->renderer = renderer;
	this->texture = IMG_LoadTexture(renderer, "res/background.png");
	SDL_SetTextureBlendMode(texture, SDL_BLENDMODE_BLEND);
}

void BubbleDrawer::onInitialize()
{
	this->transform = parent->transform;
}

void BubbleDrawer::onUpdate(double deltaTime)
{
	time += deltaTime;
	double xOff = fmod(time * BubbleDrawer::SPEED, 80.0);
	double yOff = fmod(time * BubbleDrawer::SPEED, 80.0) * 0.05;

	SDL_FRect dstrect;
	dstrect.x = -100.0 + xOff;
	dstrect.y = -180.0 + RenderWindow::SCREEN_HEIGHT - RenderWindow::SCREEN_WIDTH + yOff;
	dstrect.w = RenderWindow::SCREEN_WIDTH + 200.0;
	dstrect.h = RenderWindow::SCREEN_WIDTH + 200.0;

	SDL_RenderCopyExF(renderer, texture, nullptr, &dstrect, 3.5, nullptr, SDL_FLIP_NONE);
}

#pragma once

#include "../ecs.h"
#include "spriterenderer.h"
#include <SDL_events.h>

class ShadowTransformer : public Component
{
  private:
	Transform *ball{};
	Transform *transform{};
	SpriteRenderer *sprite{};
	Entity *target;

  public:
	explicit ShadowTransformer(Entity *shadow);

	void onInitialize() override;
	void onUpdate(double deltaTime) override;
};

//
// Created by Fabian Hummel on 12.06.22.
//

#pragma once

#include "component.h"
#include "../entity/entity.h"
#include "spriterenderer.h"
#include "ballmovement.h"
#include <SDL_events.h>

class ShadowTransformer : public Component {
private:
	Transform *ball;
	Transform *transform;
	SpriteRenderer *sprite;
	Entity *target;

public:
	ShadowTransformer(Entity *shadow);

	void onInitialize() override;
	void onUpdate(double deltaTime) override;
};

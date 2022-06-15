//
// Created by Fabian Hummel on 12.06.22.
//

#pragma once

#include "../component.h"
#include "../../entity/entity.h"
#include "spriterenderer.h"
#include "ballmovement.h"

class ShadowTransformer : public Component {
private:
	Transform *ball;
	BallMovement *ballMovement;

	Transform *shadow;
	SpriteRenderer *sprite;

public:
	void onInitialize() override;
	void onStart() override;
	void onUpdate() override;
};
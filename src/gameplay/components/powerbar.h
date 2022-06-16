//
// Created by Fabian Hummel on 16.06.22.
//

#pragma once

#include "../component.h"
#include "spriterenderer.h"

class Powerbar : public Component {
private:
	int size;
	SpriteRenderer *sprite;
	Transform *bar;

public:
	void onInitialize() override;
	void onStart() override;
	void onUpdate() override;

	void setProgress(float v, float y);
};
#pragma once

#include "../entity/entity.h"
#include "ballmovement.h"
#include "component.h"
#include "spriterenderer.h"
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

#pragma once

#include "component.h"
#include "transform.h"
#include <SDL_render.h>

class Prediction : public Component {
private:
  SDL_Renderer *renderer;
  Transform *ball;

public:
  Prediction(SDL_Renderer *renderer);

  void onInitialize() override;
  void onUpdate(double deltaTime) override;
  void onMotion(int x, int y, int dx, int dy, float strength);
};

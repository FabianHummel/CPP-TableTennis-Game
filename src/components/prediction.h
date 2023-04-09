#pragma once

#include "ballmovement.h"
#include "component.h"
#include "transform.h"
#include <SDL_render.h>

class Prediction : public Component
{
  private:
	SDL_Renderer *renderer;
	Transform *ball;
	double g = BallMovement::GRAVITY;

	double v(double t, double a, double b);
	double zcv(double a, double b);
	double f(double t, double a, double b, double c);
	double pzcf(double a, double b, double c);
	double pzc(double a, double b, double c);

  public:
	Prediction(SDL_Renderer *renderer);

	void onInitialize() override;
	void onPredict(Vector3 &force);
};

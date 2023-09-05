#pragma once

#include "../ecs/ecs.h"
#include "ballmovement.h"
#include <SDL_render.h>

class Prediction : public Component
{
  private:
	SDL_Renderer *renderer;
	Transform *ball{};
	double g = BallMovement::GRAVITY;
	const char *img;
	SDL_Texture *texture{};

	double v(double t, double a, double b);
	double zero_crossing_v(double a, double b);
	double f(double t, double a, double b, double c);
	double pos_zero_crossing_f(double a, double b, double c);
	double pos_zero_crossing(double a, double b, double c);
	double length(double x, double a, double b);
	double length_f(double x, double a, double b);
	double x_from_length_f(double l, double a, double b, double c);

  public:
	Prediction(const char *img, SDL_Renderer *renderer);

	void onInitialize() override;
	void onStart() override;
	void onPredict(Vector3 &force);
};

#include "prediction.h"
#include "../entity/entitymanager.h"
#include "transform.h"
#include <SDL_rect.h>
#include <SDL_render.h>
#include <cmath>
#include <cstdio>

Prediction::Prediction(SDL_Renderer *renderer)
{
	this->renderer = renderer;
}

void Prediction::onInitialize()
{
	this->ball = EntityManager::findEntity("Ball")->getComponent<Transform>();

	// uncomment this for unit-testing:
	// double x = pzcf(2, 7, 200);
	// printf("Zero crossing of f(t) at x=%f\n", x);
	// double x2 = f(x, 2, 7, 200);
	// printf("Value of f(%f)=%f\n", x, x2);
	// double x3 = zcv(2, 7);
	// printf("Zero crossing of v(t) at x=%f\n", x3);
	// double x4 = f(x3, 2, 7, 200);
	// printf("Highest value of f(t) at x=%f is y=%f\n", x3, x4);
}

void Prediction::onPredict(Vector3 &force)
{
	double px = pzcf(force.x, force.y, ball->getY());
	double pz = pzcf(force.z, force.y, ball->getY());

	SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255);
	for (int i = 0; i < 100; i++)
	{
		double x = px / 100 * i;
		double z = pz / 100 * i;
		SDL_Rect rect;
		if (force.x < 0.0)
			rect.x = -x + ball->getX() - 5;
		else
			rect.x = x + ball->getX() - 5;

		double h = f(x, force.x, force.y, ball->getY());
		if (force.z < 0.0)
			rect.y = -z + ball->getZ() - abs(h) - 5;
		else
			rect.y = z + ball->getZ() - abs(h) - 5;

		rect.w = 10;
		rect.h = 10;
		SDL_RenderFillRect(renderer, &rect);
	}
}

// v(t) = (vy-gt/vx)/vx
// Keep in mind that the velocity function depends on vx (velocity x-axis)
double Prediction::v(double t, double vx, double vy)
{
	return (vy - g * t / abs(vx)) / abs(vx);
}

// zero crossing of v(t)
double Prediction::zcv(double vx, double vy)
{
	return abs(vx) * vy / g;
}

// f(t) = ∫v(t)dt = (-gt^2/2vx+vyt)/vx+c
double Prediction::f(double t, double vx, double vy, double c)
{
	return (-g * t * t / (2 * abs(vx)) + vy * t) / abs(vx) + c;
}

// positive zero crossing of f(t)
double Prediction::pzcf(double vx, double vy, double py)
{
	double a = -g / (2 * vx * vx);
	double b = vy / abs(vx);
	double c = py;
	return pzc(a, b, c);
}

// positive zero crossing
// x1,2 = (-b±√(b^2-4ac)) / 2a
double Prediction::pzc(double a, double b, double c)
{
	// we use minus here because it's the positive crossing in this case.
	return (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
}

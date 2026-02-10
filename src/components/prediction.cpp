#include "prediction.h"
#include "../ecsmanager.h"
#include <SDL3_image/SDL_image.h>
#include <SDL3/SDL_rect.h>
#include <SDL3/SDL_render.h>
#include <cmath>

Prediction::Prediction(const char *img, SDL_Renderer *renderer)
{
	this->img = img;
	this->renderer = renderer;
}

void Prediction::onInitialize()
{
	this->ball = EcsManager::findEntity("Ball")->getComponent<Transform>();

	// uncomment this for unit-testing:
//	double x = pos_zero_crossing_f(2, 7, 200);
//	printf("Zero crossing of f(t) at x=%f\n", x);
//	double x2 = f(x, 2, 7, 200);
//	printf("Value of f(%f)=%f\n", x, x2);
//	double x3 = zero_crossing_v(2, 7);
//	printf("Zero crossing of v(t) at x=%f\n", x3);
//	double x4 = f(x3, 2, 7, 200);
//	printf("Highest value of f(t) at x=%f is y=%f\n", x3, x4);
//	double l = length_f(x, 2, 7);
//	printf("Length of arc: %f\n", l);
//	double x5 = x_from_length_f(l / 2.0, 2, 7, 200);
//	printf("X at function length %f = %f\n", l / 2.0, x5);
//	double l2 = length_f(x5, 2, 7);
//	printf("Length of arc at x=%f if %f\n", x5, l2);
}

void Prediction::onStart()
{
	printf("Loading Texture %s\n", img);
	this->texture = IMG_LoadTexture(renderer, img);
}

void Prediction::onPredict(Vector3 &force)
{
	double px = pos_zero_crossing_f(force.x, force.y, ball->getY());
	double pz = pos_zero_crossing_f(force.z, force.y, ball->getY());

	double total_length = length_f(px, force.x, force.y);
	constexpr double segment_length = 45.0;

	// double progress = 0.0;
	// while (progress < total_length)
	// {
	// 	SDL_FRect rect;
	// 	rect.w = 40.0;
	// 	rect.h = 40.0;
	//
	// 	double x = x_from_length_f(progress, force.x, force.y, ball->getY());
	// 	double z = x_from_length_f(progress, force.z, force.y, ball->getY());
	// 	double h = f(z, force.z, force.y, ball->getY());
	//
	// 	double tmp1 = ball->getX() - ball->getScaleX() * ball->getAnchor().x - 5;
	// 	double tmp2 = ball->getZ() - ball->getScaleY() * ball->getAnchor().y - abs(h) - 5;
	//
	// 	if (force.x < 0.0)
	// 		rect.x = -x + tmp1;
	// 	else
	// 		rect.x = x + tmp1;
	//
	// 	if (force.z < 0.0)
	// 		rect.y = -z + tmp2;
	// 	else
	// 		rect.y = z + tmp2;
	//
	// 	SDL_RenderCopyExF(renderer, texture, nullptr, &rect, 0.0, nullptr, SDL_RendererFlip::SDL_FLIP_NONE);
	// 	progress += segment_length;
	// }

	double amount = total_length / segment_length;

	for (int i = 0; i < amount; i++)
	{
		SDL_FRect rect;
		rect.w = 40.0;
		rect.h = 40.0;

		float x = (float)px / amount * i;
		float z = (float)pz / amount * i;
		if (force.x < 0.0)
		{
			rect.x = -x + ball->getX() - 20;
		}
		else
		{
			rect.x = x + ball->getX() - 20;
		}

		float h = f(z, force.z, force.y, ball->getY());
		if (force.z < 0.0)
		{
			rect.y = -z + ball->getZ() - abs(h) - 20;
		}
		else
		{
			rect.y = z + ball->getZ() - abs(h) - 20;
		}

		// double angleX = atan(v(x, force.x, force.y)) * 180.0 / 3.1415;
		// double angleZ = atan(v(z, force.z, force.y)) * 180.0 / 3.1415;
		// double angle = angleX;
		// if (force.x > 0.0)
		// 	angle *= -1.0;

		SDL_SetTextureAlphaMod(texture, 255);
		SDL_RenderTextureRotated(renderer, texture, nullptr, &rect, 0.0, nullptr, SDL_FLIP_NONE);
	}
}

// v(t) = (vy-gt/vx)/vx
// Keep in mind that the velocity function depends on vx (velocity x-axis)
double Prediction::v(double t, double vx, double vy)
{
	return (vy - g * t / abs(vx)) / abs(vx);
}

// zero crossing of v(t)
double Prediction::zero_crossing_v(double vx, double vy)
{
	return abs(vx) * vy / g;
}

// f(t) = ∫v(t)dt = (vyt-gt^2/2vx)/vx+c
double Prediction::f(double t, double vx, double vy, double c)
{
	return (-g * t * t / (2 * abs(vx)) + vy * t) / abs(vx) + c;
}

// positive zero crossing of f(t)
double Prediction::pos_zero_crossing_f(double vx, double vy, double py)
{
	double a = -g / (2 * vx * vx);
	double b = vy / abs(vx);
	double c = py;
	return pos_zero_crossing(a, b, c);
}

// positive zero crossing
// x1,2 = (-b±√(b^2-4ac)) / 2a
double Prediction::pos_zero_crossing(double a, double b, double c)
{
	// we use minus here because it's the positive crossing in this case.
	return (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
}

// length of quadratic function's arc
double Prediction::length(double x, double a, double b)
{
	double tmp1 = a * x + b;
	double tmp2 = sqrt(1 + tmp1 * tmp1);
	double tmp3 = sqrt(1 + b * b);

	// double [...] = a * 0 + b; // we can just use 'b' because the lower bound is always 0
	return ((log(abs(tmp2 + tmp1)) + tmp1 * tmp2) - (log(abs(tmp3 + b)) + b * tmp3)) / (2 * a);
}

// l = ∫[0,pzcf](√(1+v(t)^2))
double Prediction::length_f(double x, double vx, double vy)
{
	double a = -g / (vx * vx);
	double b = vy / abs(vx);
	return length(x, a, b);
}

// get the distance from 0 on the x axis where the function is 'l' long from 0
// too complicated to calculate, therefore an approximation
double Prediction::x_from_length_f(double l, double vx, double vy, double py)
{
	constexpr int ITERATIONS = 10;
	double zc = pos_zero_crossing_f(vx, vy, py);
	double x = zc / 2.0;
	for (int iter = 1; iter <= ITERATIONS; iter++)
	{
		double approx = length_f(x, vx, vy);
		if (approx < l)
		{
			x += zc / (4 * iter);
		}
		else if (approx > l)
		{
			x -= zc / (4 * iter);
		}
		else
		{
			return x;
		}
	}

	return x;
}

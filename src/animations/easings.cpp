#include "animationmanager.h"

Easing Easings::linear = [](double t) { return t; };

Easing Easings::easeIn = [](double t) { return t * t; };

Easing Easings::easeOut = [](double t) { return t * (2 - t); };

Easing Easings::ease = [](double t) { return t < 0.5 ? 2 * t * t : -1 + (4 - 2 * t) * t; };

Easing Easings::easeOutElastic = [](double t) {
	if (t == 0 || t == 1)
		return t;

	double p = 0.3;
	double s = p / 4;
	return pow(2, -10 * t) * sin((t - s) * (2 * M_PI) / p) + 1;
};
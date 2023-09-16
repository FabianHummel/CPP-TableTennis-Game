#include "animationmanager.h"

Easing Easings::linear = [](double t) { return t; };

Easing Easings::easeIn = [](double t) { return t * t; };

Easing Easings::easeOut = [](double t) { return t * (2 - t); };

Easing Easings::ease = [](double t) { return t < 0.5 ? 2 * t * t : -1 + (4 - 2 * t) * t; };
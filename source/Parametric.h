#ifndef PARAMETRIC_H
#define PARAMETRIC_H

#include <cmath>

static void parametric1(float &x, float &y, float t, float width, float height)
{
	x = width * cos(t);
	y = height * sin(t);
}

static void parametric2(float &x, float &y, float t, float width, float height)
{
	x = width * cos(3 * t);
	y = height * sin(5 * t);
}

static void parametric3(float &x, float &y, float t, float width, float height)
{
	float c = cos(t);
	float s = sin(t);

	x = width * c * c * s;
	y = height * s * s * c;
}

#endif

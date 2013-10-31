#ifndef MATH_UTILS_H
#define MATH_UTILS_H

#ifndef M_PI
#define M_PI 3.14159
#endif

#ifndef RADIANS_TO_DEGREES
#define RADIANS_TO_DEGREES 57.2957795131
#endif

static void lerp(double x0, double y0, double x1, double y1, double c, double* x, double* y)
{
	*x = (1 - c) * x0 + c * x1;
	*y = (1 - c) * y0 + c * y1;
}

static double cosInterpolate(double x0, double x1, double c)
{
	double c2 = (1 - cos(c * M_PI)) * 0.5;
	return x1 + c2 * (x1 - x0);
}

static double cubicInterpolate(double x0, double x1, double x2, double x3, double c)
{
	double a0 = -x0 + x1 - x2 + x3;
	double a1 = x0 - x1 - a0;
	double a2 = x2 - x0;
	double c2 = c * c;

	return a0 * c * c2 + a1 * c2 + a2 * c + x1;
}

#endif
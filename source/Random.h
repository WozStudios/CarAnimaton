#ifndef WRANDOM_H
#define WRANDOM_H

/* Helper function that returns a float between min and max) */
static double Random(double min, double max)
{
	return (double)rand() / ((double)RAND_MAX / (max - min)) + min;
}

/* Helper function that returns an int between min and max) */
static int Random(int min, int max)
{
	return rand() % max + min;
}

#endif
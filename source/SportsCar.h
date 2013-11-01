#ifndef SPORTS_CAR_H
#define SPORTS_CAR_H

#include "Car.h"

class SportsCar : public Car
{
public:
	SportsCar(Transform transform, vec3 direction, vec3 colour, vec3* cameraPosition, vec3* cameraDirection, Path* path) :
		Car(transform, direction, colour, cameraPosition, cameraDirection, path) { }

	void Draw(ModelviewStack* ms);

private:
	void DrawWheel(ModelviewStack* ms, int frontBack, int rightLeft);

};

#endif
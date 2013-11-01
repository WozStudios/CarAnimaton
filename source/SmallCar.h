#ifndef SMALL_CAR_H
#define SMALL_CAR_H

#include "Car.h"

class SmallCar : public Car
{
public:
	SmallCar(Transform transform, vec3 direction, vec3 colour, vec3* cameraPosition, vec3* cameraDirection, Path* path) :
		Car(transform, direction, colour, cameraPosition, cameraDirection, path) { }

	void Draw(ModelviewStack* ms);
	void Crash(float deltaTime);

private:
	void DrawWheel(ModelviewStack* ms, int frontBack, int rightLeft);
};

#endif

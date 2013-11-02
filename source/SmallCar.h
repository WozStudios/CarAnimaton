#ifndef SMALL_CAR_H
#define SMALL_CAR_H

#include "Car.h"

class SmallCar : public Car
{
private:
	vec3 _crashPosition;
	vec3 _crashVelocity;
	vec3 _crashAcceleration;

	float _timeSinceCrash;

public:
	SmallCar(Transform transform, vec3 direction, vec3 colour, vec3* cameraPosition, vec3* cameraDirection, Path* path) :
		Car(transform, direction, colour, cameraPosition, cameraDirection, path)
	{ _crashVelocity = vec3(-40.0f, 20.0f, 15.0f); _timeSinceCrash = 0; }

	void Draw(ModelviewStack* ms);
	void Crash(float deltaTime);

	void SetCrashPosition() { _crashPosition = _transform.position; }

private:
	void DrawWheel(ModelviewStack* ms, int frontBack, int rightLeft);
};

#endif

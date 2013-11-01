#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include "Camera.h"
#include "SmallCar.h"
#include "SportsCar.h"
#include "InputManager.h"

class AnimationManager
{
private:
	bool _isAnimating;
	float _animationStartTime;

	float _animationSpeed;

	Camera* _camera;
	SmallCar* _smallCar;
	SportsCar* _sportsCar;

	InputManager* _inputManager;

	vec3 _smallCarTrigger;

	bool _crashed;

public:
	void Init(Camera* camera, SmallCar* smallCar, SportsCar* sportsCar);
	void Update(float deltaTime);
};


#endif
#include "AnimationManager.h"

void AnimationManager::Init(Camera* camera, SmallCar* smallCar, SportsCar* sportsCar)
{
	_camera = camera;
	_smallCar = smallCar;
	_sportsCar = sportsCar;

	_animationSpeed = 2.0f;

	_isAnimating = false;
	_inputManager = InputManager::GetInstance();

	_smallCarTrigger = vec3(-15.0f, 0.0f, -110.0f);

	_crashed = false;
}

void AnimationManager::Update(float deltaTime)
{
	if (_inputManager->WasPPressed())
	{
		_isAnimating = !_isAnimating;

		_smallCar->SetCarSpeed(150.0f * _animationSpeed);
		_sportsCar->SetCarSpeed(600.0f * _animationSpeed);
		_smallCar->SetAnimating(_isAnimating);

		if (_isAnimating)
			std::cout << "Starting Animation\n";
		else
			std::cout << "Stopping Animation\n";
	}

	// Start sports car animation
	if (glm::length(_smallCar->GetPosition() - _smallCarTrigger) < 5.0f)
	{
		_sportsCar->SetAnimating(_isAnimating);
	}

	// Handle collision
	if (!_crashed && glm::length(_smallCar->GetPosition() - _sportsCar->GetPosition()) < 5.0f)
	{
		std::cout << "Crashed!\n";
		_crashed = true;
		_smallCar->SetAnimating(false);
	}

	if (_crashed)
	{
		_smallCar->Crash(deltaTime);
	}
}
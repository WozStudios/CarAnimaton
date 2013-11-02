#include "AnimationManager.h"

void AnimationManager::Init(Camera* camera, SmallCar* smallCar, SportsCar* sportsCar, TrafficLight* rightTL, TrafficLight* leftTL, ElectricalBox* electricalBox, sf::Music* soundtrack)
{
	_camera = camera;
	_smallCar = smallCar;
	_sportsCar = sportsCar;
	_rightTrafficLight = rightTL;
	_leftTrafficLight = leftTL;

	_electricalBox = electricalBox;

	_soundtrack = soundtrack;

	_animationSpeed = 4.0f;

	_isAnimating = false;
	_inputManager = InputManager::GetInstance();

	_smallCarTrigger = vec3(-44.0f, 0.0f, -211.0f);

	_crashed = false;
}

void AnimationManager::Update(float deltaTime)
{
	if (_inputManager->WasRightClicked())
	{
		vec3 position = _smallCar->GetPosition();
		std::cout << "SmallCar Position: (" << position.x << ", " << position.z << ")\n";
	}

	if (_inputManager->WasPPressed())
	{
		_isAnimating = !_isAnimating;

		_soundtrack->setVolume(50.0f);
		_soundtrack->play();

		_electricalBox->Explode();

		_smallCar->SetCarSpeed(75.0f * _animationSpeed);
		_sportsCar->SetCarSpeed(0.0f * _animationSpeed);
		_smallCar->SetAnimating(_isAnimating);

		if (_isAnimating)
			std::cout << "Starting Animation\n";
		else
			std::cout << "Stopping Animation\n";
	}

	// Start sports car animation
	if (glm::length(_smallCar->GetPosition() - _smallCarTrigger) < 5.0f)
	{
		_smallCar->SetAcceleration(65.0f * _animationSpeed);
		_sportsCar->SetAcceleration(250.0f * _animationSpeed);
		_sportsCar->SetAnimating(_isAnimating);
	}

	// Handle collision
	if (!_crashed && glm::length(_smallCar->GetPosition() - _sportsCar->GetPosition()) < 10.0f)
	{
		std::cout << "Crashed!\n";
		_crashed = true;
		_smallCar->SetAnimating(false);
		_smallCar->SetPosition(vec3(_smallCar->GetPosition().x, 0.01f, _smallCar->GetPosition().z));
		_smallCar->SetCrashPosition();
	}

	if (_crashed)
	{
		_smallCar->Crash(deltaTime);
	}
}
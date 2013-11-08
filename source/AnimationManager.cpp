#include "AnimationManager.h"
#include "MathUtils.h"
#include "drawScene.h"


void AnimationManager::Init(Camera* camera, SmallCar* smallCar, SportsCar* sportsCar, TrafficLight* rightTL, TrafficLight* leftTL, ElectricalBox* electricalBox, sf::Music* soundtrack, vector<Rat*> rats)
{
	_camera = camera;
	_smallCar = smallCar;
	_sportsCar = sportsCar;
	_rightTrafficLight = rightTL;
	_leftTrafficLight = leftTL;
	_electricalBox = electricalBox;
	_soundtrack = soundtrack;

	//for (vector<Rat*>::iterator i = rats->begin(); i != rats->end(); i++)
	//{
	//	_rats.push_back(*i);
	//}

	_rats = rats;

	_animationSpeed = 4.0f;

	_isAnimating = false;
	_inputManager = InputManager::GetInstance();

	_smallCarTrigger = vec3(-44.0f, 0.0f, -211.0f);

	_crashed = false;

	_saturation = 0.0f;
	_fade = 1.0f;

	_fadingIn = false;
	_fadingOut = false;

	_animatingDummyTarget = false;
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

		_fade = 0.0f;
		_fadingIn = true;

		_soundtrack->setVolume(100.0f);
		_soundtrack->play();

		_camera->ResetCounters();
		_camera->SetAcceleration(8.0f, 140.0f);
		_camera->SetIdealCounterX(-M_PI / 8.0f);
		_camera->SetRotationSpeedY(0.15f);
		_camera->SetRotationSpeedX(0.05f);
		_camera->SetAnimating(true);

		for (vector<Rat*>::iterator i = _rats.begin(); i != _rats.end(); i++)
			(*i)->SetAnimating(true);

		if (_isAnimating)
			std::cout << "Starting Animation\n";
		else
			std::cout << "Stopping Animation\n";
	}

	if (_fadingIn)
		FadeIn(deltaTime);

	if (_fadingOut)
		FadeOut(deltaTime);

	GLuint fadeLocation = glGetUniformLocation(gShaders.getActiveID(), "fade");
	if ((int)fadeLocation >= 0)
		glUniform1f(fadeLocation, _fade);

	if (glm::length(_camera->GetTargetPosition() - vec3(59.4f, 12.7f, -216.4f)) < 1.0f)
	{
		_camera->SetIdealCounterY(3.0f * M_PI / 2.0f, 1);
		_camera->SetIdealCounterX(M_PI / 4.0f);
	}

	// Slow down as approaching Electrical Box
	if (glm::length(_camera->GetTargetPosition() - vec3(9.4f, 17.7f, 3.2f)) < 1.0f)
	{
		_camera->SetAcceleration(-45.0f, 40.0f);
	}

	// Start Electrical Box Animation
	if (glm::length(_camera->GetTargetPosition() - _electricalBox->GetPosition()) < 10.0f)
	{
		_electricalBox->Explode();

		_camera->SetIdealCounterY(7.0f * M_PI / 4.0f, 1);
		_camera->SetIdealCounterX(-M_PI / 4.0f);
		_camera->SetRotationSpeedY(0.15f);
		_camera->SetRotationSpeedX(0.08f);

		_camera->SetAcceleration(60.0f, 60.0f);
	}

	//Start Traffic Lights Animation
	if (glm::length(_camera->GetTargetPosition() - vec3(5.7f, 11.7f, 14.6f)) < 1.0f)
	{
		_rightTrafficLight->SetAnimating(true);
		_leftTrafficLight->SetAnimating(true);
	}

	//Start turning towards small car
	if (glm::length(_camera->GetTargetPosition() - vec3(10.4f, 10.4f, 8.2f)) < 1.0f)
	{
		_camera->SetAcceleration(10.0f, 120.0f);
		_camera->SetIdealCounterY(0.5f, 1);
		_camera->SetIdealCounterX(1.2f);
		_camera->SetRotationSpeedX(0.15f);
	}

	//Start zooming out
	if (glm::length(_camera->GetTargetPosition() - vec3(-46.8f, 12.7f, -60.3f)) < 1.0f)
	{
		_camera->SetDistance(128);
	}

	// Start small car animation
	if (glm::length(_camera->GetTargetPosition() - vec3(-109.0f, 10.0f, -95.0f)) < 0.7f)
	{
		_smallCar->SetCarSpeed(40.0f * _animationSpeed);
		_smallCar->SetAnimating(_isAnimating);

		_camera->SetAnimating(false);
		_camera->SetTarget(_smallCar->GetPositionPointer());

		_camera->SetIdealCounterY(1.3f, 1);
		_camera->SetIdealCounterX(1.2f);
		_camera->SetRotationSpeedY(0.1f);
		_camera->SetRotationSpeedX(0.08f);
		_camera->SetDistance(70);
	}

	// Start speeding up and rotating back
	if (glm::length(_camera->GetTargetPosition() - vec3(-47.5f, 10.0f, -214.2f)) < 0.5f)
	{
		_smallCar->SetAcceleration(4.2f * _animationSpeed);
		
		_camera->SetIdealCounterY(5.0f, -1);
		_camera->SetIdealCounterX(-0.5f);
		_camera->SetRotationSpeedY(0.1f);
		_camera->SetDistance(50);
	}

	// Start sports car animation
	if (glm::length(_camera->GetTargetPosition() - vec3(-14.7f, 10.0f, -133.8f)) < 0.7f)
	{
		_sportsCar->SetCarSpeed(0.0f);
		_sportsCar->SetAcceleration(70.0f * _animationSpeed);
		_sportsCar->SetAnimating(_isAnimating);
	}

	// Handle collision
	if (!_crashed && glm::length(_smallCar->GetPosition() - _sportsCar->GetPosition()) < 20.0f)
	{
		std::cout << "Crashed!\n";
		_crashed = true;
		_smallCar->SetAnimating(false);
		_smallCar->SetPosition(vec3(_smallCar->GetPosition().x, 0.01f, _smallCar->GetPosition().z));
		_smallCar->SetCrashPosition();

		_camera->SetFollowing(false);

	}

	if (_crashed)
	{
		_smallCar->Crash(deltaTime);
	}

	// Start looking up
	if (glm::length(_smallCar->GetPosition() - vec3(336.0f, 10.0f, 171.8f)) < 0.2f)
	{
		_dummyTarget = _smallCar->GetPosition();
		_animatingDummyTarget = true;

		_camera->SetTarget(&_dummyTarget);
	}

	// Fade out after crash
	if (_smallCar->GetPosition().y < 0.0f)
	{
		_fadingIn = false;
		_fadingOut = true;
	}

	if (_animatingDummyTarget)
	{
		_dummyTarget.y += deltaTime * 10.0f;

	}
}

void AnimationManager::AnimateSaturation(float deltaTime)
{
	_saturation += deltaTime * 0.1f;

	if (_saturation > 1.0f)
		_saturation = 1.0f;
}

void AnimationManager::FadeIn(float deltaTime)
{
	_fade += deltaTime * 0.2f;

	if (_fade > 1.0f)
		_fade = 1.0f;
}

void AnimationManager::FadeOut(float deltaTime)
{
	_fade -= deltaTime * 0.2f;

	if (_fade < 0.0f)
		_fade = 0.0f;
}
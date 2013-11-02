#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include "Camera.h"
#include "SmallCar.h"
#include "SportsCar.h"
#include "TrafficLight.h"
#include "ElectricalBox.h"
#include "InputManager.h"
#include "SFML/Audio.hpp"

class AnimationManager
{
private:
	bool _isAnimating;
	float _animationStartTime;

	float _animationSpeed;

	Camera* _camera;
	SmallCar* _smallCar;
	SportsCar* _sportsCar;
	ElectricalBox* _electricalBox;
	TrafficLight* _rightTrafficLight;
	TrafficLight* _leftTrafficLight;


	sf::Music* _soundtrack;

	InputManager* _inputManager;

	vec3 _smallCarTrigger;

	bool _crashed;

public:
	void Init(Camera* camera, SmallCar* smallCar, SportsCar* sportsCar, TrafficLight* right, TrafficLight* left, ElectricalBox* electricalBox, sf::Music* soundtrack);
	void Update(float deltaTime);
};

#endif
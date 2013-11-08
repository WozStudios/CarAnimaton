#ifndef ANIMATION_MANAGER_H
#define ANIMATION_MANAGER_H

#include "Camera.h"
#include "SmallCar.h"
#include "SportsCar.h"
#include "TrafficLight.h"
#include "ElectricalBox.h"
#include "InputManager.h"
#include "SFML/Audio.hpp"
#include "Rat.h"

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
	vector<Rat*> _rats;

	InputManager* _inputManager;

	vec3 _smallCarTrigger;

	bool _crashed;

	float _saturation;
	float _fade;

	bool _fadingIn;
	bool _fadingOut;

	vec3 _dummyTarget;
	bool _animatingDummyTarget;

public:
	void Init(Camera* camera, SmallCar* smallCar, SportsCar* sportsCar, TrafficLight* right, TrafficLight* left, ElectricalBox* electricalBox, sf::Music* soundtrack, vector<Rat*> rats);
	void Update(float deltaTime);

private:

	void AnimateSaturation(float deltaTime);
	void FadeIn(float deltaTime);
	void FadeOut(float deltaTime);
};

#endif
#include "Camera.h"
#include "InputManager.h"
#include "drawScene.h"

Camera::Camera(double distance)
{
	_distance = distance;
	_position = vec3(_distance, _distance, 0);
	_target = vec3(0, 0, 0);
	_upVector = vec3(0, 1, 0);
	
	_heightSpeed = 10.0;
	_zoomSpeed = 10.0;
	_rotationSpeed = 1.0;

	_angle = 0.0;

	_isRotating = false;
}

void Camera::Update(float deltaTime)
{
	InputManager* inputManager = InputManager::GetInstance();
	
	if (inputManager->IsRightClicked())
		_distance += deltaTime * inputManager->GetMouseDY() * _zoomSpeed;

	double heightFactor = 1.0;
	if (inputManager->IsLeftClicked())
		_position.y += deltaTime * inputManager->GetMouseDY() * _heightSpeed;

	if (inputManager->IsSpacePressed())
	{
		inputManager->SetSpacePressed(false);
		_isRotating = !_isRotating;
	}
	
	if (_isRotating)
	{
		_angle += deltaTime;

		if (_angle > 360.0)
			_angle -=360.0;
	}
	
	_position = vec3(_distance * cos(_angle) * _rotationSpeed,
					 _position.y,
					 _distance  * sin(_angle) * _rotationSpeed);
}
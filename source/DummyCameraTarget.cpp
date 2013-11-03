#include "DummyCameraTarget.h"
#include "opengl.h"
#include "drawScene.h"

#include <iostream>

DummyCameraTarget::DummyCameraTarget(vec3 position)
{
	_transform.position = position;
	//_camera = camera;
	_targetPosition = NULL;

	_inputManager = InputManager::GetInstance();
	_movementSpeed =75.0f;
}

void DummyCameraTarget::Update(float deltaTime)
{
	if (_targetPosition != NULL)
		_transform.position = *_targetPosition;
	else
	{
		_movementVector = vec3();
		vec3 direction = glm::normalize(_transform.position - _cameraPosition);
		vec3 left = glm::normalize(glm::cross(vec3(0.0, 1.0, 0.0), direction));
		vec3 up = glm::normalize(glm::cross(direction, left));

		if (_inputManager->IsKeyPressed(GLFW_KEY_W))
		{
			_movementVector += direction;
		}

		if (_inputManager->IsKeyPressed(GLFW_KEY_S))
		{
			_movementVector -= direction;
		}

		if (_inputManager->IsKeyPressed(GLFW_KEY_A))
		{
			_movementVector += left;
		}

		if (_inputManager->IsKeyPressed(GLFW_KEY_D))
		{
			_movementVector -= left;
		}

		if (_inputManager->IsKeyPressed(GLFW_KEY_E))
		{
			_movementVector += up;
		}

		if (_inputManager->IsKeyPressed(GLFW_KEY_Q))
		{
			_movementVector -= up;
		}

		float currentSpeed;
		if (_inputManager->IsKeyPressed(GLFW_KEY_SPACE))
			currentSpeed = 2 * _movementSpeed;
		else
			currentSpeed = _movementSpeed;

		if (_movementVector != vec3())
			_transform.position += glm::normalize(_movementVector) * currentSpeed * deltaTime;
	}
}

void DummyCameraTarget::Draw(ModelviewStack* ms)
{
	useTexture(0);
	setColour(1.0, 1.0, 1.0);
	ms->Push();
	{
		ms->Translate(_transform.position);
		drawSphere(*ms);
	}
	ms->Pop();
}
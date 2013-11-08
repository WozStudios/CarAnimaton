#include "DummyCameraTarget.h"
#include "opengl.h"
#include "drawScene.h"

#include <iostream>
#include "Node.h"
#include "MathUtils.h"

#include "Debug.h"

#define MAX_SPEED 180.0f
#define MIN_SPEED 15.0f

void DummyCameraTarget::Init(vec3 position)
{
	_transform.position = position;
	//_camera = camera;
	_targetPosition = NULL;

	_inputManager = InputManager::GetInstance();
	_movementSpeed = 75.0f;

	_isAnimating = false;
	_acceleration = 0.0;
	_currentNode = 0;
	_currentC = 0.0f;

	SetupPath();
}

void DummyCameraTarget::Destroy()
{
	_path.Destroy();
}

void DummyCameraTarget::Update(float deltaTime)
{
	if (_isAnimating)
	{
		_movementSpeed += _acceleration * deltaTime;

		//// Clamp speed
		//if (_movementSpeed > MAX_SPEED)
		//	_movementSpeed = MAX_SPEED;
		//if (_movementSpeed < MIN_SPEED)
		//	_movementSpeed = MIN_SPEED;

		if (_acceleration > 0.0f)
		{
			if (_movementSpeed > _targetSpeed)
				_movementSpeed = _targetSpeed;
		}
		else
		{
			if (_movementSpeed < _targetSpeed)
				_movementSpeed = _targetSpeed;
		}

		_currentC += deltaTime * _movementSpeed;

		while (_currentC > 1.0)
		{
			_currentNode++;
			_currentC -= 1.0;
		}

		vector<vec3> points = _path.GetPoints();
		
		if (_currentNode < points.size() - 2)
		{
			_transform.position.x = (float)lerp(points[_currentNode].x, points[_currentNode + 1].x, _currentC);
			_transform.position.y = (float)lerp(points[_currentNode].y, points[_currentNode + 1].y, _currentC);
			_transform.position.z = (float)lerp(points[_currentNode].z, points[_currentNode + 1].z, _currentC);
		}
	}

	else
	{
		if (_targetPosition != NULL)
		{
			_transform.position.x = _targetPosition->x;
			_transform.position.z = _targetPosition->z;
		}
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

	if (_inputManager->WasRightClicked())
	{
		std::cout << "DummyCameraTarget Position: (" << _transform.position.x << ", "
			<< _transform.position.y << ", "
			<< _transform.position.z << ")\n";

		std::cout << "DummyCameraTarget Speed: " << _movementSpeed << "\n";
	}
}

void DummyCameraTarget::Draw(ModelviewStack* ms)
{
	_path.DrawDebugSpheres(ms);

	useTexture(0);
	setColour(1.0, 1.0, 1.0);
	ms->Push();
	{
		ms->Translate(_transform.position);
		drawSphere(*ms);
	}
	ms->Pop();
}

void DummyCameraTarget::SetupPath()
{
	_path.AddNode(new Node(vec3(130.0f, 12.0f, -214.7f)));
	_path.AddNode(new Node(vec3(120.0f, 12.0f, -214.7f)));
	//_path.AddNode(new Node(vec3(75.0f, 12.0f, -214.7f)));
	_path.AddNode(new Node(vec3(75.0f, 12.0f, -214.7f)));
	_path.AddNode(new Node(vec3(33.1f, 15.4f, -201.0f)));
	_path.AddNode(new Node(vec3(28.8f, 17.3f, -80.7f)));
	_path.AddNode(new Node(vec3(0.8f, 17.3f, 28.6f)));
	_path.AddNode(new Node(vec3(-2.4f, 15.0f, 28.3f)));
	_path.AddNode(new Node(vec3(0.9f, 8.8f, -20.5f)));
	_path.AddNode(new Node(vec3(-79.2, 14.5f, -79.0f)));
	_path.AddNode(new Node(vec3(-109.0f, 10.0f, -95.0f)));
	_path.AddNode(new Node(vec3(-109.9f, 10.0f, -95.5f)));
	_path.AddNode(new Node(vec3(-109.95f, 10.0f, -95.6f)));
	_path.CalculatePath();

}
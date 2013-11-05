#include "DummyCameraTarget.h"
#include "opengl.h"
#include "drawScene.h"

#include <iostream>
#include "Node.h"
#include "MathUtils.h"

#define MAX_SPEED 200.0f
#define MIN_SPEED 10.0f

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

		// Clamp speed
		if (_movementSpeed > MAX_SPEED)
			_movementSpeed = MAX_SPEED;
		if (_movementSpeed < MIN_SPEED)
			_movementSpeed = MIN_SPEED;

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

			//double c = _currentC;
			//unsigned int node = _currentNode;
			//vec3 heading;
			//
			//vec3 nextPosition = vec3();
			//for (int i = 0; i < 10; i++)
			//{
			//	c += 1.0;
			//
			//	while (c > 1.0)
			//	{
			//		node++;
			//		c -= 1.0;
			//	}
			//
			//	if (node < points.size() - 2)
			//	{
			//		lerp(points[_currentNode].x, 
			//			points[_currentNode].z, 
			//			points[node + 1].x, 
			//			points[node + 1].z,
			//			c,
			//			&x, &z);
			//
			//		nextPosition.x += (float)x;
			//		nextPosition.z += (float)z;
			//	}
			//}
			//nextPosition.x /= 10.0f;
			//nextPosition.z /= 10.0f;
			//
			//if (_transform.position != nextPosition)
			//{
			//	vec3 heading = glm::normalize(nextPosition - _transform.position);
			//	_carAngle = acos(glm::dot(_carDirection, heading));
			//
			//	vec3 crossProduct = glm::cross(_carDirection, heading);
			//	if (crossProduct.y > 0)
			//		_carAngle *= -1.0f;
			//}
			//
			//_rotationCounter = _carAngle / (float) M_PI;
			//
			//if (_rotationCounter > 2.0f)
			//	_rotationCounter -= 2.0f;
			//if (_rotationCounter < 0.0f)
			//	_rotationCounter += 2.0f;
		}
	}

	else
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

	if (_inputManager->WasRightClicked())
	{
		std::cout << "DummyCameraTarget Position: (" << _transform.position.x << ", "
			<< _transform.position.y << ", "
			<< _transform.position.z << ")\n";
	}
}

void DummyCameraTarget::Draw(ModelviewStack* ms)
{
	//_path.DrawDebugSpheres(ms);

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
	_path.AddNode(new Node(vec3(75.1f, 12.0f, -214.7f)));
	//_path.AddNode(new Node(vec3(75.0f, 12.0f, -214.7f)));
	_path.AddNode(new Node(vec3(75.0f, 12.0f, -214.7f)));
	_path.AddNode(new Node(vec3(33.1f, 15.4f, -201.0f)));
	_path.AddNode(new Node(vec3(28.8f, 17.3f, -80.7f)));
	_path.AddNode(new Node(vec3(0.8f, 17.3f, 28.6f)));
	_path.AddNode(new Node(vec3(-2.4f, 15.0f, 28.3f)));
	_path.AddNode(new Node(vec3(0.9f, 8.8f, 3.5f)));
	_path.AddNode(new Node(vec3(-79.2, 14.5f, -79.0f)));
	_path.AddNode(new Node(vec3(-105.8f, 4.9f, -91.7f)));
	_path.AddNode(new Node(vec3(-107.7f, 4.2f, -93.2f)));
	_path.CalculatePath();

}
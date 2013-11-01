#include "Car.h"
#include "drawScene.h"
#include "MathUtils.h"
#include "Utility.h"
#include "InputManager.h"
#include "Node.h"

Car::Car(Transform transform, vec3 direction, vec3 colour, vec3* cameraPosition, vec3* cameraDirection, Path* path)
{
	_transform = transform;
	_lastPosition = _transform.position;

	_colour = colour;

	_carSpeed = 75.0f;

	_carDirection = vec3(0.0f, 0.0f, -1.0f);
	_carAngle = 180.0f;
	_rotationCounter = 0.0f;

	_tireRadius = 2.0f;
	_wheelAngle = 0.0f;

	_cameraPosition = cameraPosition;
	_cameraDirection = cameraDirection;

	if (path != NULL)
	{
		_path = path;
		_points = path->GetPoints();
	}
	_currentNode = 1;
	_currentC = 0.0;

	_isAnimating = false;
}

void Car::Update(float deltaTime)
{
	if (_isAnimating && _points.size() > 0)
	{
		double x;
		double z;

		_currentC += deltaTime * _carSpeed;

		while (_currentC > 1.0)
		{
			_currentNode++;
			_currentC -= 1.0;
		}

		if (_currentNode < _points.size() - 2)
		{
			lerp(_points[_currentNode].x, 
				_points[_currentNode].z, 
				_points[_currentNode + 1].x, 
				_points[_currentNode + 1].z,
				_currentC,
				&x, &z);

			_transform.position.x = (float)x;
			_transform.position.z = (float)z;
		
			double c = _currentC;
			unsigned int node = _currentNode;
			vec3 heading;

			vec3 nextPosition = vec3();
			for (int i = 0; i < 10; i++)
			{
				c += 1.0;

				while (c > 1.0)
				{
					node++;
					c -= 1.0;
				}

				if (node < _points.size() - 2)
				{
					lerp(_points[_currentNode].x, 
						_points[_currentNode].z, 
						_points[node + 1].x, 
						_points[node + 1].z,
						c,
						&x, &z);

					nextPosition.x += (float)x;
					nextPosition.z += (float)z;
				}
			}
			nextPosition.x /= 10.0f;
			nextPosition.z /= 10.0f;
		
			if (_transform.position != nextPosition)
			{
				vec3 heading = glm::normalize(nextPosition - _transform.position);
				_carAngle = acos(glm::dot(_carDirection, heading));

				vec3 crossProduct = glm::cross(_carDirection, heading);
				if (crossProduct.y > 0)
					_carAngle *= -1.0f;
			}

			_rotationCounter = _carAngle / (float) M_PI;

			if (_rotationCounter > 2.0f)
				_rotationCounter -= 2.0f;
			if (_rotationCounter < 0.0f)
				_rotationCounter += 2.0f;
		}
	}

	quat carDirection1 = quat(vec3(0.0f, M_PI, 0.0f));
	quat carDirection2 = quat(vec3(0.0f, 0.0, 0.0f));
	_heading = mix(carDirection1, carDirection2, _rotationCounter);
	
	// Calculate wheel spin
	float distanceTravelled = glm::length(_transform.position - _lastPosition);
	_wheelAngle += (distanceTravelled / _tireRadius) *  (float)RADIANS_TO_DEGREES;
	_lastPosition = _transform.position;
}

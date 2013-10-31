#include "Car.h"
#include "drawScene.h"
#include "MathUtils.h"
#include "Utility.h"
#include "InputManager.h"
#include "Node.h"

Car::Car(vec3* cameraPosition, vec3* cameraDirection)
{
	_transform.position = vec3(-109.0f, 0.0f, -95.0f);
	_transform.rotation = vec3(0.0f, 1.0f, 0.0f);
	_transform.scale = vec3(8.0f, 4.0f, 20.0f);

	_lastPosition = _transform.position;

	_velocity = vec3(0.0f, 0.0f, 0.0f);
	_acceleration = 0.3f;
	_carSpeed = 50.0f;

	_carDirection = vec3(0.0f, 0.0f, -1.0f);
	_carAngle = 180.0f;
	_rotationCounter = 0.0f;

	_tireRadius = 2.0f;
	_wheelAngle = 0.0f;
	_wheelSpeed = _velocity.z * 180.0f / 4.0f;

	_cameraPosition = cameraPosition;
	_cameraDirection = cameraDirection;

	_path.AddNode(new Node(vec3(-109.0f, 0.0f, -60.0f)));
	_path.AddNode(new Node(vec3(_transform.position.x, 0.0f, _transform.position.z)));
	//_path.AddNode(new Node(vec3(-120.0f, 5.0f, -120.0f)));
	_path.AddNode(new Node(vec3(-115.0f, 0.0f, -160.0f)));
	//_path.AddNode(new Node(vec3(-138.0f, 5.0f, -190.0f)));
	_path.AddNode(new Node(vec3(-82.0f, 0.0f, -210.0f)));
	_path.AddNode(new Node(vec3(-22.0f, 0.0f, -168.0f)));
	//_path.AddNode(new Node(vec3(-28.0f, 5.0f, -193.0f)));
	//_path.AddNode(new Node(vec3(-16.0f, 5.0f, -143.0f)));
	//_path.AddNode(new Node(vec3(-22.0f, 5.0f, -85.0f)));
	//_path.AddNode(new Node(vec3(-12.0f, 5.0f, -45.0f)));
	_path.AddNode(new Node(vec3(-8.0f, 0.0f, -10.0f)));
	//_path.AddNode(new Node(vec3(9.0f, 5.0f, 4.0f)));
	_path.AddNode(new Node(vec3(90.0f, 0.0f, 16.0f)));
	_path.AddNode(new Node(vec3(150.0f, 0.0f, 16.0f)));

	_path.CalculatePath();
	_points = _path.GetPoints();

	_currentNode = 1;
	_currentC = 0.0;
}

void Car::Update(float deltaTime)
{
	if (_currentNode < _points.size() - 2)
	{
		double x;
		double z;

		_currentC += deltaTime * _carSpeed;

		while (_currentC > 1.0)
		{
			_currentNode++;
			_currentC -= 1.0;
		}

		lerp(_points[_currentNode].x, 
			_points[_currentNode].z, 
			_points[_currentNode + 1].x, 
			_points[_currentNode + 1].z,
			_currentC,
			&x, &z);

		_transform.position.x = x;
		_transform.position.z = z;
		
		double c = _currentC;
		int node = _currentNode;
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

			lerp(_points[_currentNode].x, 
				_points[_currentNode].z, 
				_points[node + 1].x, 
				_points[node + 1].z,
				c,
				&x, &z);

			nextPosition.x += x;
			nextPosition.z += z;
		}
		nextPosition.x /= 10.0f;
		nextPosition.z /= 10.0f;
		
		if (_transform.position != nextPosition)
		{
			vec3 heading = glm::normalize(nextPosition - _transform.position);
			_carAngle = acos(glm::dot(_carDirection, heading));

			//std::cout << "Car Angle: " << _carAngle << "\n";

			vec3 crossProduct = glm::cross(_carDirection, heading);
			if (crossProduct.y > 0)
				_carAngle *= -1.0f;

			//vec3 crossProduct = glm::cross(_carDirection, heading);
			//if (crossProduct.y > 0)
			//	_carAngle = acos(glm::dot(_carDirection, heading)) * RADIANS_TO_DEGREES;
			//else
			//	_carAngle = 360.0 - acos(glm::dot(_carDirection, heading)) * RADIANS_TO_DEGREES;
		}


		// Animation test
		//_rotationCounter += deltaTime * 0.5f;

		_rotationCounter = _carAngle / M_PI;

		if (_rotationCounter > 2.0f)
			_rotationCounter -= 2.0f;
		if (_rotationCounter < 0.0f)
			_rotationCounter += 2.0f;

		quat carDirection1 = quat(vec3(0.0f, M_PI, 0.0f));
		quat carDirection2 = quat(vec3(0.0f, 0.0, 0.0f));
		//vec3 heading = vec3(_points[_currentNode + 2].x - _transform.position.x, 0.0f,
		//							_points[_currentNode + 2].z - _transform.position.z);
		_heading = mix(carDirection1, carDirection2, _rotationCounter);
	}
	
	// Calculate wheel spin
	double distanceTravelled = glm::length(_transform.position - _lastPosition);
	int spinDirection = 1; //_velocity.z < 0 ? 1 : -1;
	_wheelAngle += spinDirection * (distanceTravelled / _tireRadius) * RADIANS_TO_DEGREES;
	_lastPosition = _transform.position;
}

void Car::Draw(ModelviewStack* ms)
{
	//_path.DrawDebugSpheres(ms);

	if (!Utility::isVisible(_transform.position, *_cameraPosition, *_cameraDirection))
		return;

	setColour(0.25f, 0.4f, 0.3f);
	ms->Push();
	{
		ms->Translate(_transform.position);
		//ms->Rotate(_carAngle * RADIANS_TO_DEGREES + 180.0, _transform.rotation);
		ms->Mult(mat4_cast(_heading));
		// Draw main body
		ms->Push();
		{
			ms->Translate(vec3(0.0f, _transform.scale.y * 0.3f + _tireRadius, 0.0f));

			ms->Scale(vec3(_transform.scale.x * 0.5f,
						   _transform.scale.y * 0.3f,
						   _transform.scale.z * 0.5f));
			drawCube(*ms);
		}
		ms->Pop();

		//Draw Top
		ms->Push();
		{
			ms->Translate(vec3(0.0f, _transform.scale.y * 0.77f + _tireRadius, -3.0f));

			ms->Scale(vec3(_transform.scale.x * 0.47f,
				_transform.scale.y * 0.17f,
				_transform.scale.z * 0.2f));
			drawCube(*ms);
		}
		ms->Pop();

		//Draw Roof
		ms->Push();
		{
			ms->Translate(vec3(0.0f, _transform.scale.y * 1.06f + _tireRadius, -2.0f));

			ms->Scale(vec3(_transform.scale.x * 0.47f,
				_transform.scale.y * 0.12f,
				_transform.scale.z * 0.25f));
			drawCube(*ms);
		}
		ms->Pop();

		setColour(0.0f, 0.0f, 0.0f);
		//Draw front windows
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 
				_transform.scale.y * 0.77f + _tireRadius,
				-3.0f + _transform.scale.z * 0.235f));

			ms->Scale(vec3(_transform.scale.x * 0.471f,
				_transform.scale.y * 0.3f,
				_transform.scale.z * 0.07f));

			drawCube(*ms);
		}
		ms->Pop();
		// Draw windshield
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 
				_transform.scale.y * 0.66f + _tireRadius,
				-3.0f + _transform.scale.z * 0.34f));

			ms->Rotate(45.0f, vec3(1.0f, 0.0f, 0.0f));

			ms->Scale(vec3(_transform.scale.x * 0.469f,
				_transform.scale.y * 0.17f,
				_transform.scale.z * 0.1f));
			drawCube(*ms);
		}
		ms->Pop();

		//Draw middle windows
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 
				_transform.scale.y * 0.77f + _tireRadius,
				-3.0f)); // + _transform.scale.z * 0.25f));

			ms->Scale(vec3(_transform.scale.x * 0.471f,
				_transform.scale.y * 0.3f,
				_transform.scale.z * 0.1f));

			drawCube(*ms);
		}
		ms->Pop();

		// Draw back window
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 
				_transform.scale.y * 0.655f + _tireRadius,
				-3.0f - _transform.scale.z * 0.23f));

			ms->Rotate(-45.0f, vec3(1.0f, 0.0f, 0.0f));

			ms->Scale(vec3(_transform.scale.x * 0.469f,
				_transform.scale.y * 0.18f,
				_transform.scale.z * 0.1f));
			drawCube(*ms);
		}
		ms->Pop();

		setColour(1.0f, 1.0f, 1.0f);

		// Draw headlights
		ms->Push();
		{
			ms->Translate(vec3(-_transform.scale.x / 4.0f, 
				_transform.scale.y * 0.3f + _tireRadius,
				_transform.scale.z * 0.5f));

			ms->Scale(vec3(_transform.scale.x * 0.06f, _transform.scale.x * 0.06f, 0.01f));
			drawCube(*ms);
		}
		ms->Pop();
		ms->Push();
		{
			ms->Translate(vec3(_transform.scale.x / 4.0f, 
				_transform.scale.y * 0.3f + _tireRadius,
				_transform.scale.z * 0.5f));

			ms->Scale(vec3(_transform.scale.x * 0.06f, _transform.scale.x * 0.06f, 0.01f));
			drawCube(*ms);
		}
		ms->Pop();

		setColour(0.4f, 0.0f, 0.0f);
		// Draw brake lights
		ms->Push();
		{
			ms->Translate(vec3(-_transform.scale.x / 4.0f, 
				_transform.scale.y * 0.3f + _tireRadius,
				-_transform.scale.z * 0.5f));

			ms->Scale(vec3(_transform.scale.x * 0.06f, _transform.scale.x * 0.06f, 0.01f));
			drawCube(*ms);
		}
		ms->Pop();
		ms->Push();
		{
			ms->Translate(vec3(_transform.scale.x / 4.0f, 
				_transform.scale.y * 0.3f + _tireRadius,
				-_transform.scale.z * 0.5f));

			ms->Scale(vec3(_transform.scale.x * 0.06f, _transform.scale.x * 0.06f, 0.01f));
			drawCube(*ms);
		}
		ms->Pop();
		
		// Draw wheels
		DrawWheel(ms, 1, -1);
		DrawWheel(ms, -1, 1);
		DrawWheel(ms, -1, -1);
		DrawWheel(ms, 1, 1);

	}
	ms->Pop();
}

void Car::DrawWheel(ModelviewStack* ms, int frontBack, int rightLeft)
{
	setColour(0.1f, 0.1f, 0.1f);
	ms->Push();
	{
		ms->Translate(vec3(rightLeft * _transform.scale.x / 2.0f,
						   _tireRadius,
						   frontBack * -_transform.scale.z / 4.0f));

		ms->Rotate(_wheelAngle, vec3(1.0f, 0.0f, 0.0f));

		// Draw tire
		ms->Push();
		{
			ms->Scale(vec3(_tireRadius, _tireRadius * 2.0, _tireRadius * 2.0));
			ms->Rotate(90.0, vec3(0.0f, 1.0f, 0.0f));
			drawCylinder(*ms);
		}
		ms->Pop();

		// Draw hub cap
		ms->Push();
		{
			ms->Translate(vec3(rightLeft * _tireRadius / 2.0f, 0.0f, 0.0f));
			ms->Scale(vec3(0.05f, _tireRadius, _tireRadius));
			//ms->Rotate(90.0, vec3(0.0f, 1.0f, 0.0f));
			drawSphere(*ms);
				
			setColour(0.5f, 0.5f, 0.5f);
			ms->Scale(vec3(1.5f, 0.5f, 0.5f));
			drawSphere(*ms);

		}
		ms->Pop();

		setColour(0.1f, 0.1f, 0.1f);
		// Draw bolts
		for (int i = 0; i < 6; i++)
		{
			ms->Push();
			{
				ms->Translate(vec3(rightLeft * _tireRadius / 2.0f, std::sin(i) * 0.5f, std::cos(i) * 0.5f));
				ms->Scale(vec3(0.1f, 0.1f, 0.1f));
				//ms->Rotate(90.0, vec3(0.0f, 1.0f, 0.0f));
				drawSphere(*ms);

			}
			ms->Pop();
		}
	}
	ms->Pop();
}
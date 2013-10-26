#include "Bird.h"
#include "drawScene.h"
#include "MathUtils.h"
#include "Parametric.h"
#include "Random.h"

Bird::Bird(Transform transform, float flightSpeed, int pathFunction)
{
	_transform = transform;
	_transform.rotation = vec3(0.0, 1.0, 0.0);

	_wingAngle = 45.0f;
	_wingCounter = 0.0f;
	_wingFlapSpeed = 2.0f;
	_flightSpeed = flightSpeed;
	_pathCounter = Random(0.0f, 2 * M_PI);
	_rotationAngle = 0.0f;
	_front = vec3(0.0f, 0.0f, 1.0f);
	_lastPosition = _transform.position;

	SetPathFunction(pathFunction);
}

void Bird::Update(float deltaTime)
{
	//_transform.position.z += _flightSpeed * deltaTime;
	// Fly along path

	_pathCounter += deltaTime * _flightSpeed;
	(*PathFunction)(_transform.position.x, _transform.position.z, _pathCounter, 128.0f, 128.0f);

	// Rotate to get proper heading
	vec3 heading = glm::normalize(_transform.position - _lastPosition);
	vec3 crossProduct = glm::cross(_front, heading);
	if (crossProduct.y > 0)
		_rotationAngle = acos(glm::dot(_front, heading)) * RADIANS_TO_DEGREES;
	else
		_rotationAngle = 360.0 - acos(glm::dot(_front, heading)) * RADIANS_TO_DEGREES;

	_lastPosition = _transform.position;

	// Flap wings
	_wingCounter += deltaTime * _wingFlapSpeed;
	if (_wingCounter > 2 * M_PI);
		_wingCounter -= 2 * M_PI;
	_wingAngle = sin(_wingCounter) * 45.0f;
}

void Bird::Draw(ModelviewStack* ms)
{
	setColour(1.0f, 1.0f, 1.0f);
	ms->Push();
	{
		ms->Translate(_transform.position);
		ms->Rotate(_rotationAngle, _transform.rotation);
		
		ms->Push();
		{
			ms->Scale(vec3(_transform.scale.x / 2.0f, 
				 			_transform.scale.y / 2.0f, 
							_transform.scale.z / 2.0f));
			ms->Translate(vec3(0.0f, 1.0f, 0.0f));
			drawSphere(*ms);
		}
		ms->Pop();
		
		DrawWing(ms, 1);
		DrawWing(ms, -1);
	}
	ms->Pop();
}

void Bird::DrawWing(ModelviewStack* ms, int rightLeft)
{
	ms->Push();
	{
		ms->Rotate(_wingAngle * rightLeft, vec3(0.0f, 0.0f, 1.0f));
		ms->Translate(vec3(0.0f, _transform.scale.y / 4.0f, 0.0f));
		ms->Scale(vec3(_transform.scale.x * 1.7f, _transform.scale.y / 8.0f, _transform.scale.z / 6.0f));
		ms->Translate(vec3(rightLeft, 1.0f, 0.0f));
		drawCube(*ms);
	}
	ms->Pop();
}

void Bird::SetPathFunction(int pathFunction)
{
	switch (pathFunction)
	{
	case 1:
		PathFunction = &parametric1;
		break;

	case 2:
		PathFunction = &parametric2;
		break;

	case 3:
		PathFunction = &parametric2;
		break;
	}
}
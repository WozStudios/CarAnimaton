#include "Bird.h"
#include "drawScene.h"
#include "MathUtils.h"
#include "Parametric.h"
#include "Random.h"
#include "Utility.h"

Bird::Bird(Transform transform, float flightSpeed, int pathFunction, float pathWidth, vec3* cameraPosition, vec3* cameraDirection)
{
	_transform = transform;
	_transform.rotation = vec3(0.0, 1.0, 0.0);

	_wingAngle = 45.0f;
	_wingCounter = 0.0f;
	_wingFlapSpeed = 2.0f;
	_flightSpeed = flightSpeed;
	_pathWidth = pathWidth;
	_pathCounter = (float)Random(0.0, 2.0 * M_PI);
	_rotationAngle = 0.0f;
	_front = vec3(0.0f, 0.0f, 1.0f);
	_lastPosition = _transform.position;
	_cameraPosition = cameraPosition;
	_cameraDirection = cameraDirection;
	_visible = true;

	SetPathFunction(pathFunction);
}

void Bird::Update(float deltaTime)
{
	if (!Utility::isVisible(_transform.position, *_cameraPosition, *_cameraDirection))
	{
		_visible = false;
		return;
	}
	else
		_visible = true;

	// Fly along path
	_pathCounter += deltaTime * _flightSpeed;
	(*PathFunction)(_transform.position.x, _transform.position.z, _pathCounter, _pathWidth, _pathWidth);

	// Rotate to get proper heading
	vec3 heading = glm::normalize(_transform.position - _lastPosition);
	vec3 crossProduct = glm::cross(_front, heading);
	if (crossProduct.y > 0)
		_rotationAngle =  (float)(acos(glm::dot(_front, heading)) * RADIANS_TO_DEGREES);
	else
		_rotationAngle =  (float)(360.0 - acos(glm::dot(_front, heading)) * RADIANS_TO_DEGREES);

	_lastPosition = _transform.position;

	// Flap wings
	_wingCounter += deltaTime * _wingFlapSpeed;
	_wingAngle = sin(_wingCounter) * 45.0f;
}

void Bird::Draw(ModelviewStack* ms)
{
	if (!_visible)
		return;

	useTexture(0);
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
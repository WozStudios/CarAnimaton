#include "Rat.h"
#include "drawScene.h"
#include "Utility.h"
#include "Parametric.h"
#include "Random.h"

Rat::Rat(vec3* cameraPosition, vec3* cameraDirection)
{
	_transform.scale = vec3(0.95f, 0.95f, 3.0f);
	_transform.position = vec3(Random(45.0f, 75.0f), _transform.scale.y * 0.5f, Random(-250.0f, -190.0f));
	_transform.rotation = vec3(0.0f, 1.0f, 0.0f);

	_cameraPosition = cameraPosition;
	_cameraDirection = cameraDirection;

	_tailCounter = 0.0f;
	_tailAngle = 0.0f;

	_movementSpeed = Random(12.0f, 17.0f);
	_pathCounter = 0.1f;
	_pathWidth = 20.0f;
	_rotationAngle = 0.0f;
	_front = vec3(0.0f, 0.0f, 1.0f);
	_lastPosition = _transform.position;
	_isVisible = true;
	_isAnimating = false;
}

void Rat::Update(float deltaTime)
{
	if (!Utility::isVisible(_transform.position, *_cameraPosition, *_cameraDirection))
	{
		_isVisible = false;
		return;
	}
	else
		_isVisible = true;

	if (_isAnimating)
	{
		// Move along path
		_pathCounter += deltaTime * _movementSpeed;
		//parametric3(_transform.position.x, _transform.position.z, _pathCounter, _pathWidth, _pathWidth);

		_transform.position.x += deltaTime * _movementSpeed;
		_transform.position.z += std::sin(_pathCounter) * 0.1f;

		// Rotate to get proper heading
		vec3 heading = glm::normalize(_transform.position - _lastPosition);
		vec3 crossProduct = glm::cross(_front, heading);
		if (crossProduct.y > 0)
			_rotationAngle =  (float)(acos(glm::dot(_front, heading)) * RADIANS_TO_DEGREES);
		else
			_rotationAngle =  (float)(360.0 - acos(glm::dot(_front, heading)) * RADIANS_TO_DEGREES);

		_lastPosition = _transform.position;

		// Wag tail
		_tailCounter += deltaTime * 10.0f;
		_tailAngle = std::sin(_tailCounter) * 20.0f;
	}
}

void Rat::Draw(ModelviewStack* ms)
{
	if (!_isVisible)
		return;
	
	useTexture(0);
	setColour(0.1f, 0.06f, 0.0f);
	
	ms->Push();
	{
		ms->Translate(_transform.position);
		ms->Rotate(_rotationAngle, _transform.rotation);

		// Draw body
		ms->Push();
		{
			//ms->Translate(vec3(0.0f, 0.0f, 0.0f));
			ms->Scale(0.5f * _transform.scale);
			drawSphere(*ms);
		}
		ms->Pop();

		// Draw head
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 0.4f, 0.5f * _transform.scale.z));
			ms->Rotate(10.0f, vec3(1.0f, 0.0f, 0.0f));
			ms->Scale(0.2f * _transform.scale);
			drawSphere(*ms);
		}
		ms->Pop();

		setColour(0.14f, 0.09f, 0.0f);

		// Draw tail
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 0.1f, -0.45f * _transform.scale.z));
			ms->Rotate(_tailAngle, _transform.rotation);
			ms->Translate(vec3(0.0f, 0.0f, -0.5f * _transform.scale.z));
			//ms->Rotate(10.0f, _transform.rotation);
			ms->Scale(vec3(0.05f * _transform.scale.x, 0.05f * _transform.scale.y, _transform.scale.z));
			drawCylinder(*ms);
		}
		ms->Pop();
	}
	ms->Pop();
}
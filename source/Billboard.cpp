#include "Billboard.h"
#include "drawScene.h"
#include "MathUtils.h"
#include "Utility.h"

Billboard::Billboard(Transform transform, vec3* cameraPosition, vec3* cameraDirection, int textureID)
{
	_transform = transform;
	_cameraPosition = cameraPosition;
	_cameraDirection = cameraDirection;
	_textureID = textureID;

	_normal = vec3(0.0, 0.0, 1.0);

	_rotationAngle = 0;
}

void Billboard::Update(float time)
{
	vec3 idealNormal = *_cameraPosition - _transform.position;
	idealNormal.y = _transform.position.y;
	
	idealNormal = glm::normalize(idealNormal);
	
	vec3 crossProduct = glm::cross(_normal, idealNormal);
	if (crossProduct.y > 0)
		_rotationAngle = acos(glm::dot(_normal, idealNormal)) * RADIANS_TO_DEGREES;
	else 
		_rotationAngle = 360.0 - acos(glm::dot(_normal, idealNormal)) * RADIANS_TO_DEGREES;

	_distanceFromCamera = glm::length(_transform.position - *_cameraPosition);
}

void Billboard::Draw(ModelviewStack* ms)
{
	if (!Utility::isVisible(_transform.position, *_cameraPosition, *_cameraDirection))
		return;

	useTexture(_textureID);
	setColour(1.0, 1.0, 1.0);

	useLighting(0);

	ms->Push();
	{
		float height =  _transform.position.y + _transform.scale.y / 4;
		ms->Translate(vec3(_transform.position.x,
						   height,
						   _transform.position.z));

		ms->Rotate(_rotationAngle, vec3(0.0, 1.0, 0.0));
		ms->Scale(vec3(_transform.scale.x / 2, _transform.scale.y / 2, 1.0));

		//ms->Rotate(-90.0, vec3(1, 0, 0));

		drawSquare(*ms);
	}
	ms->Pop();
}

bool Billboard::CompareDistance(Billboard* a, Billboard* b)
{
	return a->GetDistanceFromCamera() > b->GetDistanceFromCamera();
}

bool Billboard::operator<(const Billboard& rhs)
{
	return _distanceFromCamera > rhs._distanceFromCamera;
}
#include "Fence.h"
#include "Utility.h"
#include "drawScene.h"

Fence::Fence(vec3 position, float rotationAngle, vec3* cameraPosition, vec3* cameraDirection)
{
	_transform.rotation = vec3(0.0f, 1.0f, 0.0f);
	_transform.scale = vec3(512.0f, 32.0f, 1.0f);

	_transform.position = position;
	//_transform.position = vec3();
	_transform.position.y = _transform.scale.y * 0.5f;

	_rotationAngle = rotationAngle;

	_cameraPosition = cameraPosition;
	_cameraDirection = cameraDirection;

}

void Fence::Draw(ModelviewStack* ms)
{
	if (!Utility::isVisible(_transform.position, *_cameraPosition, *_cameraDirection))
		return;

	useTexture(16);
	setColour(1.0f, 1.0f, 1.0f);
	ms->Push();
	{
		ms->Translate(_transform.position);
		ms->Rotate(_rotationAngle, _transform.rotation);
		ms->Scale(_transform.scale);
		drawSquare(*ms);
	}
	ms->Pop();
}
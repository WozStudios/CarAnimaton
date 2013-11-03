#include "FenceBoard.h"
#include "drawScene.h"
#include "Utility.h"

FenceBoard::FenceBoard(vec3 position, float rotationAngle, vec3* cameraPosition, vec3* cameraDirection)
{
	_transform.rotation = vec3(0.0f, 1.0f, 0.0f);
	_transform.scale = vec3(1.0f, 8.0f, 0.2f);

	_transform.position = position;
	//_transform.position = vec3();
	_transform.position.y = _transform.scale.y;
	
	_rotationAngle = rotationAngle;

	_cameraPosition = cameraPosition;
	_cameraDirection = cameraDirection;

}

void FenceBoard::Draw(ModelviewStack* ms)
{
	if (!Utility::isVisible(_transform.position, *_cameraPosition, *_cameraDirection))
		return;

	useTexture(11);
	setColour(0.8f, 0.7f, 0.7f);
	ms->Push();
	{
		ms->Translate(_transform.position);
		ms->Rotate(_rotationAngle, _transform.rotation);
		ms->Scale(_transform.scale);
		drawCube(*ms);
	}
	ms->Pop();
}
#include "Fence.h"
#include "Utility.h"
#include "drawScene.h"
#include "Textures.h"

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
	useTexture(FENCE_TEXTURE);
	setColour(1.0f, 1.0f, 1.0f);
	//vec3 c = vec3(1.0f, 1.0f, 1.0f);
	//setMaterial(0.4f * c, c, c, 60.0f);
	useLighting(0);
	ms->Push();
	{
		ms->Translate(_transform.position);
		ms->Rotate(_rotationAngle, _transform.rotation);
		ms->Scale(_transform.scale);
		drawSquare(*ms);
	}
	ms->Pop();
	useLighting(1);
}
#include "Decal.h"
#include "drawScene.h"
#include "Utility.h"
#include "opengl.h"

Decal::Decal(Transform transform, int textureID, float rotationAngle, vec3* cameraPosition, vec3* cameraDirection)
{
	_textureID = textureID;
	_transform = transform;
	_rotationAngle = rotationAngle;

	_cameraPosition = cameraPosition;
	_cameraDirection = cameraDirection;
}

void Decal::Draw(ModelviewStack* ms)
{
	if (!Utility::isVisible(_transform.position, *_cameraPosition, *_cameraDirection))
		return;

	glEnable(GL_BLEND); //Enable alpha blending
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA); //Set the blend function

	useLighting(0);
	useTexture(_textureID);
	setColour(1.0f, 1.0f, 1.0f);
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
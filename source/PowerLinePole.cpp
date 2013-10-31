#include "PowerLinePole.h"
#include "MathUtils.h"
#include "drawScene.h"
#include "Utility.h"

PowerLinePole::PowerLinePole(vec3 position, vec3* cameraPosition, vec3* cameraDirection)
{
	_transform = Transform();
	_transform.position = position;
	_transform.rotation = vec3(1.0f, 0.0f, 0.0f);
	_transform.scale = vec3(8.0f, 100.0f, 8.0f);

	_cameraPosition = cameraPosition;
	_cameraDirection = cameraDirection;
}

void PowerLinePole::Draw(ModelviewStack* ms)
{
	if (!Utility::isVisible(_transform.position, *_cameraPosition, *_cameraDirection))
		return;

	ms->Push();
	{
		useTexture(11);
		vec3 colour = vec3(1.0f, 1.0f, 1.0f);
		setMaterial(colour, colour, colour, 60.0f);

		ms->Translate(_transform.position);
		ms->Scale(vec3(0.5f * _transform.scale));
		ms->Translate(vec3(0.0f, 0.5f, 0.0f));
		ms->Rotate(90.0f, _transform.rotation);
		drawCylinder(*ms);
	}
	ms->Pop();
}
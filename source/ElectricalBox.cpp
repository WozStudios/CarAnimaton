#include "ElectricalBox.h"
#include "MathUtils.h"
#include "drawScene.h"
#include "Utility.h"

ElectricalBox::ElectricalBox(vec3* cameraPosition, vec3* cameraDirection)
{
	_transform = Transform();
	_transform.position = vec3(0.0f, 0.0f, 0.0f);
	_transform.rotation = vec3(1.0f, 0.0f, 0.0f);
	_transform.scale = vec3(1.0f, 1.0f, 1.0f);

	_cameraPosition = cameraPosition;
	_cameraDirection = cameraDirection;
}

void ElectricalBox::Draw(ModelviewStack* ms)
{
	if (!Utility::isVisible(_transform.position, *_cameraPosition, *_cameraDirection))
		return;

	ms->Push();
	{
		ms->Translate(_transform.position);

		DrawPole(ms);
	}
	ms->Pop();
}

void ElectricalBox::DrawPole(ModelviewStack* ms)
{
	useTexture(11);
	vec3 colour = vec3(1.0f, 1.0f, 1.0f);
	setMaterial(colour, colour, colour, 60.0f);
	ms->Push();
	{
		ms->Translate(vec3(0.0f, 6.0f, 0.0f));

		ms->Rotate(90.0f, _transform.rotation);
		ms->Scale(vec3(3.0f, 3.0f, 10.0f));
		drawCylinder(*ms);
	}
	ms->Pop();
}
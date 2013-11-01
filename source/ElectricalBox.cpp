#include "ElectricalBox.h"
#include "MathUtils.h"
#include "drawScene.h"
#include "Utility.h"

ElectricalBox::ElectricalBox(vec3* cameraPosition, vec3* cameraDirection)
{
	_transform = Transform();
	_transform.position = vec3(0.0f, 6.0f, 23.55f);
	_transform.rotation = vec3(1.0f, 0.0f, 0.0f);
	_transform.scale = vec3(6.0f, 7.0f, 2.0f);

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

		useTexture(0);
		vec3 colour = vec3(0.5f, 0.5f, 0.5f);
		setMaterial(colour, colour, colour, 60.0f);
		// Draw box
		ms->Push();
		{
			ms->Translate(vec3(_transform.position));
			ms->Scale(vec3(0.5f * _transform.scale));
			drawCube(*ms);
		}
		ms->Pop();

		//Draw door
		ms->Push();
		{
			ms->Translate(vec3(_transform.position.x - 0.1f,
				_transform.position.y,
				_transform.position.z - 1.0f));
			ms->Scale(vec3(0.5f * _transform.scale.x + 0.1f,
				0.5f * _transform.scale.y + 0.2f, 
				0.03f * _transform.scale.z));
			drawCube(*ms);
		}
		ms->Pop();

		// Draw warning texture
		useTexture(14);
		//wsetColour(1.0f, 1.0f, 1.0f);
		ms->Push();
		{
			ms->Translate(vec3(_transform.position.x - 0.1f,
				_transform.position.y,
				_transform.position.z - 1.07f));
			ms->Rotate(180.0f, vec3(0.0f, 1.0f, 0.0f));
			ms->Scale(vec3(0.5f * _transform.scale));
			drawSquare(*ms);
		}
		ms->Pop();
	}
	ms->Pop();
}
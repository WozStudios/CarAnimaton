#include "Dumpster.h"
#include "drawScene.h"
#include "Utility.h"

Dumpster::Dumpster(vec3* cameraPosition, vec3* cameraDirection)
{
	_wheelDiameter = 1.0f;

	_transform.scale = vec3(22.0f, 13.0f, 13.0f);
	_transform.position = vec3(116.0f, 0.0f, -195.0f);
	_transform.rotation = vec3(0.0f, 1.0f, 0.0f);

	_cameraPosition = cameraPosition;
	_cameraDirection = cameraDirection;
}

void Dumpster::Draw(ModelviewStack* ms)
{
	if (!Utility::isVisible(_transform.position, *_cameraPosition, *_cameraDirection))
		return;

	useTexture(0);
	setColour(0.05f, 0.1f, 0.01f);

	float height = 0.5f * _transform.scale.y + _wheelDiameter;

	ms->Push();
	{
		ms->Translate(_transform.position);

		// Draw body
		ms->Push();
		{
			ms->Translate(vec3(0.0f, height, 0.0f));
			ms->Scale(vec3(0.52f * _transform.scale.x, 0.5f * _transform.scale.y, 0.52f * _transform.scale.z));

			drawCube(*ms);
		}
		ms->Pop();

		// Draw trimming
		ms->Push();
		{
			ms->Translate(vec3(-0.5f * _transform.scale.x, height, 0.48f * _transform.scale.z));
			ms->Scale(vec3(1.0f, 0.5f * _transform.scale.y, 1.0f));

			drawCube(*ms);
		}
		ms->Pop();
		ms->Push();
		{
			ms->Translate(vec3(-0.5f * _transform.scale.x, height, 0.0f));
			ms->Scale(vec3(1.0f, 0.5f * _transform.scale.y, 1.0f));

			drawCube(*ms);
		}
		ms->Pop();
		ms->Push();
		{
			ms->Translate(vec3(-0.5f * _transform.scale.x, height, -0.48f * _transform.scale.z));
			ms->Scale(vec3(1.0f, 0.5f * _transform.scale.y, 1.0f));

			drawCube(*ms);
		}
		ms->Pop();
		ms->Push();
		{
			ms->Translate(vec3(-0.25f * _transform.scale.x, height, -0.48f * _transform.scale.z));
			ms->Scale(vec3(1.0f, 0.5f * _transform.scale.y, 1.0f));

			drawCube(*ms);
		}
		ms->Pop();
		ms->Push();
		{
			ms->Translate(vec3(0.0f * _transform.scale.x, height, -0.48f * _transform.scale.z));
			ms->Scale(vec3(1.0f, 0.5f * _transform.scale.y, 1.0f));

			drawCube(*ms);
		}
		ms->Pop();
		ms->Push();
		{
			ms->Translate(vec3(0.25f * _transform.scale.x, height, -0.48f * _transform.scale.z));
			ms->Scale(vec3(1.0f, 0.5f * _transform.scale.y, 1.0f));

			drawCube(*ms);
		}
		ms->Pop();
		ms->Push();
		{
			ms->Translate(vec3(0.5f * _transform.scale.x, height, -0.48f * _transform.scale.z));
			ms->Scale(vec3(1.0f, 0.5f * _transform.scale.y, 1.0f));

			drawCube(*ms);
		}
		ms->Pop();

		// Draw Base
		ms->Push();
		{
			ms->Translate(vec3(0.0f,  0.06f * _transform.scale.y + _wheelDiameter, 0.0f));
			ms->Scale(vec3(0.551f * _transform.scale.x, 0.06f * _transform.scale.y, 0.58f * _transform.scale.z));

			drawCube(*ms);
		}
		ms->Pop();

		// Draw lid
		ms->Push();
		{
			ms->Translate(vec3(0.0f, height + 0.5f * _transform.scale.y, 0.0f));
			ms->Scale(vec3(1.1f * _transform.scale.x, 0.2f * _transform.scale.y, 1.1f *  _transform.scale.z));
			ms->Rotate(90.0f, _transform.rotation);

			drawCylinder(*ms);
		}
		ms->Pop();
		ms->Push();
		{
			ms->Translate(vec3(-0.55f * _transform.scale.x, height + 0.5f * _transform.scale.y, 0.0f));
			ms->Scale(vec3(0.1f, 0.1f * _transform.scale.y, 0.55f *  _transform.scale.z));

			drawSphere(*ms);
		}
		ms->Pop();

		// Draw wheels
		setColour(0.1f, 0.1f, 0.1f);
		ms->Push();
		{
			ms->Translate(vec3(-0.5f * _transform.scale.x, 0.5f * _wheelDiameter, 4.0f));
			ms->Scale(vec3(0.3f * _wheelDiameter, 0.5f * _wheelDiameter, 0.5f * _wheelDiameter));

			drawSphere(*ms);
		}
		ms->Pop();
		ms->Push();
		{
			ms->Translate(vec3(-0.5f * _transform.scale.x, 0.5f * _wheelDiameter, -4.0f));
			ms->Scale(vec3(0.3f * _wheelDiameter, 0.5f * _wheelDiameter, 0.5f * _wheelDiameter));

			drawSphere(*ms);
		}
		ms->Pop();
	}
	ms->Pop();
}
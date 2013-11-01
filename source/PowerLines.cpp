#include "PowerLines.h"
#include "MathUtils.h"
#include "drawScene.h"
#include "Utility.h"

PowerLines::PowerLines(vec3* cameraPosition, vec3* cameraDirection)
{
	_transform = Transform();
	_transform.position = vec3(200.0f, 0.0f, 50.0f);
	_transform.rotation = vec3(1.0f, 0.0f, 0.0f);
	_transform.scale = vec3(8.0f, 100.0f, 8.0f);

	_cameraPosition = cameraPosition;
	_cameraDirection = cameraDirection;
	
	SetupPoles();
}

PowerLines::~PowerLines()
{
	for (vector<PowerLinePole*>::iterator i = _poles.begin(); i != _poles.end(); i++)
	{
		delete *i;
	}
}

void PowerLines::SetupPoles()
{
	vec3 position = _transform.position;

	for (int i = 0; position.x > -220; i++)
	{
		_poles.push_back(new PowerLinePole(position, _cameraPosition, _cameraDirection));

		position.x -= 100.0f;
	}
}

void PowerLines::Draw(ModelviewStack* ms)
{
	if (!Utility::isVisible(_transform.position, *_cameraPosition, *_cameraDirection))
		return;

	ms->Push();
	{
		unsigned int index = 0;
		for (vector<PowerLinePole*>::iterator i = _poles.begin(); i != _poles.end(); i++, index++)
		{
			(*i)->Draw(ms);

			// Draw lines
			if (index != _poles.size() - 1)
			{
				setColour(0.0f, 0.0f, 0.0f);
				vec3 position = vec3((*i)->GetPosition().x, 45.0f, (*i)->GetPosition().z);
				DrawLine(ms, position);
				position.y -= 10.0f;
				DrawLine(ms, position);

			}
		}
	}
	ms->Pop();
}
void PowerLines::DrawLine(ModelviewStack* ms, vec3 position)
{
	// Draw left section
	ms->Push();
	{
		ms->Translate(position);
		ms->Rotate(10.0f, vec3(0.0f, 0.0f, 1.0f));
		ms->Scale(vec3(35.0f, 0.4f, 0.4f));
		ms->Translate(vec3(-0.5f, 0.0f, 0.0f));
		ms->Rotate(90.0f, vec3(0.0f, 1.0f, 0.0f));
		drawCylinder(*ms);
	}
	ms->Pop();

	double y = sin(10.0 * DEGREES_TO_RADIANS) * 35.0f;
	// Draw left joint
	ms->Push();
	{
		ms->Translate(vec3(position.x - 34.5f, position.y - y, position.z));
		ms->Scale(vec3(0.2f, 0.2f, 0.2f));
		drawSphere(*ms);
	}
	ms->Pop();

	// Draw middle section
	ms->Push();
	{
		ms->Translate(vec3(position.x - 49.5f, position.y - y, position.z));
		ms->Scale(vec3(30.0f, 0.4f, 0.4f));
		ms->Rotate(90.0f, vec3(0.0f, 1.0f, 0.0f));
		drawCylinder(*ms);
	}
	ms->Pop();

	// Draw right joint
	ms->Push();
	{
		ms->Translate(vec3(position.x - 64.5f, position.y - y, position.z));
		ms->Scale(vec3(0.2f, 0.2f, 0.2f));
		drawSphere(*ms);
	}
	ms->Pop();

	// Draw right section
	ms->Push();
	{
		ms->Translate(vec3(position.x - 64.5f, position.y - y, position.z));
		ms->Rotate(-10.0f, vec3(0.0f, 0.0f, 1.0f));
		ms->Scale(vec3(35.0f, 0.4f, 0.4f));
		ms->Translate(vec3(-0.5f, 0.0f, 0.0f));
		ms->Rotate(90.0f, vec3(0.0f, 1.0f, 0.0f));
		drawCylinder(*ms);
	}
	ms->Pop();
}
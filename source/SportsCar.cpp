#include "SportsCar.h"
#include "drawScene.h"
#include "Utility.h"

void SportsCar::Draw(ModelviewStack* ms)
{
	//_path->DrawDebugSpheres(ms);

	if (!Utility::isVisible(_transform.position, *_cameraPosition, *_cameraDirection))
		return;

	useTexture(0);
	setColour(_colour.x, _colour.y, _colour.z);

	ms->Push();
	{
		ms->Translate(_transform.position);
		ms->Mult(mat4_cast(_heading));

		// Draw body
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 0.6f * _transform.scale.y, 0.0f));
			ms->Scale(vec3(_transform.scale.x,
				0.6f * _transform.scale.y,
				0.8f * _transform.scale.z));
			drawSphere(*ms);
		}
		ms->Pop();

		// Draw roof
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 1.0f * _transform.scale.y, -0.3f * _transform.scale.z));
			ms->Rotate(-15.0f, vec3(1.0f, 0.0f, 0.0f));
			ms->Scale(vec3(0.7f * _transform.scale.x,
				0.6f * _transform.scale.y,
				0.4f * _transform.scale.z));
			drawSphere(*ms);
		}
		ms->Pop();

		// Draw back wheels cover
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 0.65f * _transform.scale.y, -0.5f * _transform.scale.z));
			ms->Rotate(90.0f, vec3(.0f, 1.0f, 0.0f));
			ms->Scale(vec3(0.53f * _transform.scale.x,
				0.55f * _transform.scale.y,
				1.7f * _transform.scale.x));
			drawCylinder(*ms);
		}
		ms->Pop();

		// Draw front right wheel cover
		ms->Push();
		{
			ms->Translate(vec3(-_transform.scale.x * 0.75f, 0.8f * _transform.scale.y, 0.3f * _transform.scale.z));
			ms->Rotate(-5.0f, vec3(0.0f, 1.0f, 0.0f));
			ms->Rotate(-5.0f, vec3(1.0f, 0.0f, 0.0f));
			
			ms->Push();
			{
				ms->Translate(vec3(0.0f, 0.0f, 0.25f * _transform.scale.z));
				ms->Scale(vec3(0.15f * _transform.scale.x,
					0.25f * _transform.scale.y,
					0.1f * _transform.scale.z));
				drawSphere(*ms);
			}
			ms->Pop();
			ms->Push();
			{
				ms->Scale(vec3(0.3f * _transform.scale.x,
					0.5f * _transform.scale.y,
					0.5f * _transform.scale.z));
				drawCylinder(*ms);
			}
			ms->Pop();
		}
		ms->Pop();

		ms->Push();
		{
			ms->Translate(vec3(_transform.scale.x * 0.75f, 0.8f * _transform.scale.y, 0.3f * _transform.scale.z));
			ms->Rotate(5.0f, vec3(0.0f, 1.0f, 0.0f));
			ms->Rotate(-5.0f, vec3(1.0f, 0.0f, 0.0f));

			ms->Push();
			{
				ms->Translate(vec3(0.0f, 0.0f, 0.25f * _transform.scale.z));
				ms->Scale(vec3(0.15f * _transform.scale.x,
					0.25f * _transform.scale.y,
					0.1f * _transform.scale.z));
				drawSphere(*ms);
			}
			ms->Pop();
			ms->Push();
			{
				ms->Scale(vec3(0.3f * _transform.scale.x,
					0.5f * _transform.scale.y,
					0.5f * _transform.scale.z));
				drawCylinder(*ms);
			}
			ms->Pop();
		}
		ms->Pop();

		// Draw windshield
		setColour(0.0f, 0.0f, 0.0f);
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 1.1f * _transform.scale.y, -0.0f * _transform.scale.z));
			ms->Rotate(-0.0f, vec3(1.0f, 0.0f, 0.0f));
			ms->Scale(vec3(0.7f * _transform.scale.x,
				0.4f * _transform.scale.y,
				0.25f * _transform.scale.z));
			drawSphere(*ms);
		}
		ms->Pop();

		// Draw wheels
		DrawWheel(ms, 1, -1);
		DrawWheel(ms, -1, 1);
		DrawWheel(ms, -1, -1);
		DrawWheel(ms, 1, 1);
	}
	ms->Pop();
}

void SportsCar::DrawWheel(ModelviewStack* ms, int frontBack, int rightLeft)
{
	setColour(0.1f, 0.1f, 0.1f);
	ms->Push();
	{
		ms->Translate(vec3(rightLeft * _transform.scale.x * 0.8f,
			_tireRadius,
			frontBack * -_transform.scale.z / 2.0f));

		ms->Rotate(_wheelAngle, vec3(1.0f, 0.0f, 0.0f));

		// Draw tire
		ms->Push();
		{
			ms->Scale(vec3(_tireRadius * 0.5f, _tireRadius * 1.6f, _tireRadius * 1.6f));
			ms->Rotate(90.0, vec3(0.0f, 1.0f, 0.0f));
			drawCylinder(*ms);
		}
		ms->Pop();

		// Draw hub cap
		ms->Push();
		{
			ms->Translate(vec3(rightLeft * _tireRadius / 4.0f, 0.0f, 0.0f));
			ms->Scale(vec3(0.05f, _tireRadius * 0.8f, _tireRadius * 0.8f));
			//ms->Rotate(90.0, vec3(0.0f, 1.0f, 0.0f));
			drawSphere(*ms);

			setColour(0.1f, 0.1f, 0.1f);
			ms->Scale(vec3(1.5f, 0.5f, 0.5f));
			drawSphere(*ms);

		}
		ms->Pop();

		setColour(0.6f, 0.6f, 0.6f);
		// Draw bolts
		for (int i = 0; i < 6; i++)
		{
			ms->Push();
			{
				ms->Translate(vec3(rightLeft * _tireRadius / 4.0f, std::sin(i) * 0.5f, std::cos(i) * 0.5f));
				ms->Scale(vec3(0.1f, 0.1f, 0.1f));
				//ms->Rotate(90.0, vec3(0.0f, 1.0f, 0.0f));
				drawSphere(*ms);

			}
			ms->Pop();
		}
	}
	ms->Pop();
}
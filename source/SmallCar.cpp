#include "SmallCar.h"
#include "Utility.h"
#include "drawScene.h"

void SmallCar::Draw(ModelviewStack* ms)
{
	//_path.DrawDebugSpheres(ms);

	if (!Utility::isVisible(_transform.position, *_cameraPosition, *_cameraDirection))
		return;

	useTexture(0);
	setColour(_colour.x, _colour.y, _colour.z);
	ms->Push();
	{
		ms->Translate(_transform.position);
		ms->Mult(mat4_cast(_heading));

		ms->Rotate(_rollAngle, vec3(0.0f, 0.0f, 1.0f));

		// Draw main body
		ms->Push();
		{
			ms->Translate(vec3(0.0f, _transform.scale.y * 0.3f + _tireRadius, 0.0f));

			ms->Scale(vec3(_transform.scale.x * 0.5f,
				_transform.scale.y * 0.3f,
				_transform.scale.z * 0.5f));
			drawCube(*ms);
		}
		ms->Pop();

		//Draw Top
		ms->Push();
		{
			ms->Translate(vec3(0.0f, _transform.scale.y * 0.77f + _tireRadius, -3.0f));

			ms->Scale(vec3(_transform.scale.x * 0.47f,
				_transform.scale.y * 0.17f,
				_transform.scale.z * 0.2f));
			drawCube(*ms);
		}
		ms->Pop();

		//Draw Roof
		ms->Push();
		{
			ms->Translate(vec3(0.0f, _transform.scale.y * 1.06f + _tireRadius, -2.0f));

			ms->Scale(vec3(_transform.scale.x * 0.47f,
				_transform.scale.y * 0.12f,
				_transform.scale.z * 0.25f));
			drawCube(*ms);
		}
		ms->Pop();

		setColour(0.0f, 0.0f, 0.0f);
		//Draw front windows
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 
				_transform.scale.y * 0.77f + _tireRadius,
				-3.0f + _transform.scale.z * 0.235f));

			ms->Scale(vec3(_transform.scale.x * 0.471f,
				_transform.scale.y * 0.3f,
				_transform.scale.z * 0.07f));

			drawCube(*ms);
		}
		ms->Pop();
		// Draw windshield
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 
				_transform.scale.y * 0.66f + _tireRadius,
				-3.0f + _transform.scale.z * 0.34f));

			ms->Rotate(45.0f, vec3(1.0f, 0.0f, 0.0f));

			ms->Scale(vec3(_transform.scale.x * 0.469f,
				_transform.scale.y * 0.17f,
				_transform.scale.z * 0.1f));
			drawCube(*ms);
		}
		ms->Pop();

		//Draw middle windows
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 
				_transform.scale.y * 0.77f + _tireRadius,
				-3.0f)); // + _transform.scale.z * 0.25f));

			ms->Scale(vec3(_transform.scale.x * 0.471f,
				_transform.scale.y * 0.3f,
				_transform.scale.z * 0.1f));

			drawCube(*ms);
		}
		ms->Pop();

		// Draw back window
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 
				_transform.scale.y * 0.655f + _tireRadius,
				-3.0f - _transform.scale.z * 0.23f));

			ms->Rotate(-45.0f, vec3(1.0f, 0.0f, 0.0f));

			ms->Scale(vec3(_transform.scale.x * 0.469f,
				_transform.scale.y * 0.18f,
				_transform.scale.z * 0.1f));
			drawCube(*ms);
		}
		ms->Pop();

		setColour(1.0f, 1.0f, 1.0f);

		// Draw headlights
		ms->Push();
		{
			ms->Translate(vec3(-_transform.scale.x / 4.0f, 
				_transform.scale.y * 0.3f + _tireRadius,
				_transform.scale.z * 0.5f));

			ms->Scale(vec3(_transform.scale.x * 0.06f, _transform.scale.x * 0.06f, 0.01f));
			drawCube(*ms);
		}
		ms->Pop();
		ms->Push();
		{
			ms->Translate(vec3(_transform.scale.x / 4.0f, 
				_transform.scale.y * 0.3f + _tireRadius,
				_transform.scale.z * 0.5f));

			ms->Scale(vec3(_transform.scale.x * 0.06f, _transform.scale.x * 0.06f, 0.01f));
			drawCube(*ms);
		}
		ms->Pop();

		setColour(0.4f, 0.0f, 0.0f);
		// Draw brake lights
		ms->Push();
		{
			ms->Translate(vec3(-_transform.scale.x / 4.0f, 
				_transform.scale.y * 0.3f + _tireRadius,
				-_transform.scale.z * 0.5f));

			ms->Scale(vec3(_transform.scale.x * 0.06f, _transform.scale.x * 0.06f, 0.01f));
			drawCube(*ms);
		}
		ms->Pop();
		ms->Push();
		{
			ms->Translate(vec3(_transform.scale.x / 4.0f, 
				_transform.scale.y * 0.3f + _tireRadius,
				-_transform.scale.z * 0.5f));

			ms->Scale(vec3(_transform.scale.x * 0.06f, _transform.scale.x * 0.06f, 0.01f));
			drawCube(*ms);
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

void SmallCar::DrawWheel(ModelviewStack* ms, int frontBack, int rightLeft)
{
	setColour(0.1f, 0.1f, 0.1f);
	ms->Push();
	{
		ms->Translate(vec3(rightLeft * _transform.scale.x / 2.0f,
			_tireRadius,
			frontBack * -_transform.scale.z / 4.0f));

		ms->Rotate(_wheelAngle, vec3(1.0f, 0.0f, 0.0f));

		// Draw tire
		ms->Push();
		{
			ms->Scale(vec3(_tireRadius, _tireRadius * 2.0, _tireRadius * 2.0));
			ms->Rotate(90.0, vec3(0.0f, 1.0f, 0.0f));
			drawCylinder(*ms);
		}
		ms->Pop();

		// Draw hub cap
		ms->Push();
		{
			ms->Translate(vec3(rightLeft * _tireRadius / 2.0f, 0.0f, 0.0f));
			ms->Scale(vec3(0.05f, _tireRadius, _tireRadius));
			//ms->Rotate(90.0, vec3(0.0f, 1.0f, 0.0f));
			drawSphere(*ms);

			setColour(0.5f, 0.5f, 0.5f);
			ms->Scale(vec3(1.5f, 0.5f, 0.5f));
			drawSphere(*ms);

		}
		ms->Pop();

		setColour(0.1f, 0.1f, 0.1f);
		// Draw bolts
		for (int i = 0; i < 6; i++)
		{
			ms->Push();
			{
				ms->Translate(vec3(rightLeft * _tireRadius / 2.0f, std::sin(i) * 0.5f, std::cos(i) * 0.5f));
				ms->Scale(vec3(0.1f, 0.1f, 0.1f));
				//ms->Rotate(90.0, vec3(0.0f, 1.0f, 0.0f));
				drawSphere(*ms);

			}
			ms->Pop();
		}
	}
	ms->Pop();
}

void SmallCar::Crash(float deltaTime)
{
	_transform.position.x = _crashPosition.x + _crashVelocity.x * _timeSinceCrash;
	_transform.position.z = _crashPosition.z + _crashVelocity.z * _timeSinceCrash;
	_transform.position.y = _crashPosition.y +
		_crashVelocity.y * _timeSinceCrash +
		0.5 * -10.0f * _timeSinceCrash *_timeSinceCrash;

	_rollAngle += deltaTime * 100.0f;
	if (_rollAngle > 360.0f)
		_rollAngle -= 360.0f;

	//else
	//{
	//	_crashVelocity *= 1.1f * deltaTime;
	//	
	//}

	_timeSinceCrash += deltaTime;
}
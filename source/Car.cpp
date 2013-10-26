#include "Car.h"
#include "drawScene.h"

Car::Car()
{
	_transform.position = vec3(0.0, 0.0, 0.0);
	_transform.scale = vec3(12.0f, 5.0f, 20.0f);

	_tireRadius = 8.0f;
}

void Car::Update(float deltaTime)
{

}

void Car::Draw(ModelviewStack* ms)
{
	setColour(0.25f, 0.4f, 0.3f);
	ms->Push();
	{
		ms->Translate(_transform.position);
		// Draw main body
		ms->Push();
		{
			ms->Translate(vec3(0.0f, _transform.scale.y / 4.0f + _tireRadius / 2.0, 0.0f));
			ms->Scale(vec3(_transform.scale.x / 2.0f,
						   _transform.scale.y / 2.0f,
						   _transform.scale.z / 2.0f));
			drawCube(*ms);
		}
		ms->Pop();
		
		//Draw Top
		ms->Push();
		{
			ms->Translate(vec3(0.0f, _transform.scale.y * 0.75 + _tireRadius / 2.0, -2.0f));
			ms->Scale(vec3(_transform.scale.x / 2.0f,
						   _transform.scale.y / 4.0f,
						   _transform.scale.z / 4.0f));
			ms->Translate(vec3(0.0f, 1.0f, 0.0));
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

void Car::DrawWheel(ModelviewStack* ms, int frontBack, int rightLeft)
{
	setColour(0.1f, 0.1f, 0.1f);
	ms->Push();
	{
		ms->Translate(vec3(rightLeft * _transform.scale.x / 2.0f,
						   _tireRadius / 4.0,
						   frontBack * -_transform.scale.z / 4.0f));
			
		// Draw tire
		ms->Push();
		{
			ms->Scale(vec3(_tireRadius / 4.0f, _tireRadius / 2.0, _tireRadius / 2.0));
			ms->Rotate(90.0, vec3(0.0f, 1.0f, 0.0f));
			drawCylinder(*ms);
		}
		ms->Pop();

		// Draw hub cap
		ms->Push();
		{
			ms->Translate(vec3(rightLeft * _tireRadius / 8.0f, 0.0f, 0.0f));
			ms->Scale(vec3(0.05f, _tireRadius / 4.0, _tireRadius / 4.0));
			//ms->Rotate(90.0, vec3(0.0f, 1.0f, 0.0f));
			drawSphere(*ms);
				
			setColour(0.7f, 0.7f, 0.7f);
			ms->Scale(vec3(1.5f, 0.5f, 0.5f));
			drawSphere(*ms);

		}
		ms->Pop();
	}
	ms->Pop();
}
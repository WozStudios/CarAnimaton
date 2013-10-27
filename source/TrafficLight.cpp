#include "TrafficLight.h"
#include "drawScene.h"

TrafficLight::TrafficLight(int light)
{
	float radius = 2.0f;
	float height = 64.0f;;
	
	_transform.position = vec3(32.0f, 0.0f, -30.0f);
	_lightNumber = light;
	_transform.rotation = vec3(0.0f, 1.0f, 0.0f);
	_transform.scale = vec3(radius, height, radius);
}

void TrafficLight::Draw(ModelviewStack* ms)
{
	useTexture(0);
	float grey = 0.7f;
	setColour(grey, grey, grey);
	ms->Push();
	{
		ms->Rotate(90.0f * _lightNumber, _transform.rotation);
		ms->Translate(_transform.position);
		
		DrawPost(ms);
	}
	ms->Pop();
}

void TrafficLight::DrawPost(ModelviewStack* ms)
{
    vec3 ks = vec3(4.0f) ;
    vec3 c(1.0f, 1.0f, 1.0f) ;
    setMaterial(0.7f * c, 0.7f * c, ks, 40.0f) ;

	// Draw main post
	ms->Push();
	{
		ms->Translate(vec3(0.0, _transform.scale.y / 4.0, 0.0));
		ms->Scale(vec3(_transform.scale.x / 2, _transform.scale.y / 2, _transform.scale.z / 2));
		ms->Rotate(90.0, vec3(1.0, 0.0, 0.0));

		drawCylinder(*ms);
	}
	ms->Pop();

	// Draw top post
	ms->Push();
	{
		ms->Translate(vec3(0.0, _transform.scale.y / 2.0, 0.0));
		DrawJoint(ms);

		ms->Push();
		{
			ms->Translate(vec3(0.0, 0.0, _transform.scale.y / 8.0));
			ms->Scale(vec3(_transform.scale.x / 2.0, _transform.scale.z / 2.0, _transform.scale.y / 4.0));
			//ms->Rotate(90.0, vec3(1.0, 0.0, 0.0));
			drawCylinder(*ms);
		}
		ms->Pop();

		ms->Translate(vec3(0.0, 0.0, _transform.scale.y / 4.0));
		DrawJoint(ms);
		DrawLights(ms);
	}
	ms->Pop();
}

void TrafficLight::DrawJoint(ModelviewStack* ms)
{
	ms->Push();
	{
		ms->Scale(vec3(0.5f, 0.5f, 0.5f));
		drawSphere(*ms);
	}
	ms->Pop();
}

void TrafficLight::DrawLights(ModelviewStack* ms)
{
	setColour(0.9, 0.8, 0.1);
	
	ms->Push();
	{
		ms->Scale(vec3(1.5, 5.0, 2.5));
		drawCube(*ms);
	}
	ms->Pop();

	ms->Push();
	{
		//Draw Red Light
		DrawLight(ms, 3.0f, vec3(0.3, 0.0, 0.0));
		//Draw Yellow Light
		DrawLight(ms, 0.0f, vec3(0.3, 0.3, 0.0));
		//Draw Green Light
		DrawLight(ms, -3.0f, vec3(0.0, 1.0, 0.0));

	}
	ms->Pop();
}

void TrafficLight::DrawLight(ModelviewStack* ms, float height, vec3 colour)
{
	ms->Push();
	{
		ms->Translate(vec3(1.8f, height, 0.0f));
		//ms->Scale(vec3(1.0, 1.2, 1.2));
		setColour(colour.x, colour.y, colour.z);
		drawSphere(*ms);
		
		setColour(0.9, 0.8, 0.1);
		ms->Translate(vec3(0.0f, 0.0, 0.0));
		ms->Rotate(90.0, vec3(0.0f, 1.0, 0.0));
		ms->Scale(vec3(2.4f, 2.4f, 2.4f));

		drawCylinder(*ms);
	}
	ms->Pop();
}


#include "TrafficLight.h"
#include "drawScene.h"
#include "MathUtils.h"
#include "Utility.h"

TrafficLight::TrafficLight(int light, vec3* cameraPosition, vec3* cameraDirection, bool isGreen)
{
	float radius = 2.0f;
	float height = 64.0f;;
	
	_transform.position = vec3(32.0f, 0.0f, -30.0f);
	_lightNumber = light;
	_transform.rotation = vec3(0.0f, 1.0f, 0.0f);
	_transform.scale = vec3(radius, height, radius);

	_cameraPosition = cameraPosition;
	_cameraDirection = cameraDirection;

	_isGreen = isGreen;
	_isRed = !_isGreen;
}

void TrafficLight::Draw(ModelviewStack* ms)
{
	vec3 cameraToPosition = _transform.position - *_cameraPosition;
	float cameraDistance = glm::length(cameraToPosition);

	if (!Utility::isVisible(_transform.position, *_cameraPosition, *_cameraDirection))
		return;

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
		ms->Translate(vec3(0.0f, _transform.scale.y / 4.0f, 0.0f));
		ms->Scale(vec3(0.5f * _transform.scale));
		ms->Rotate(90.0f, vec3(1.0f, 0.0f, 0.0f));

		drawCylinder(*ms);
	}
	ms->Pop();

	// Draw top post
	ms->Push();
	{
		ms->Translate(vec3(0.0f, _transform.scale.y / 2.0f, 0.0f));
		DrawJoint(ms);

		ms->Push();
		{
			ms->Translate(vec3(0.0f, 0.0f, _transform.scale.y / 4.0f));
			ms->Scale(vec3(_transform.scale.x / 2.0f, _transform.scale.z / 2.0f, _transform.scale.y / 2.0f));
			//ms->Rotate(90.0, vec3(1.0, 0.0, 0.0));
			drawCylinder(*ms);
		}
		ms->Pop();

		ms->Translate(vec3(0.0f, 0.0f, _transform.scale.y / 4.0f));
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
	setColour(0.9f, 0.8f, 0.1f);
	
	ms->Push();
	{
		ms->Translate(vec3(0.0f, 0.0f, 16.0f));
		ms->Rotate(180.0f, vec3(0.0f, 1.0f, 0.0f));
		ms->Push();
		{
			ms->Scale(vec3(1.5f, 5.0f, 2.5f));
			drawCube(*ms);
		}
		ms->Pop();

		ms->Push();
		{
			//Draw Red Light
			if (_isRed)
				DrawLight(ms, 3.0f, vec3(1.0f, 0.0f, 0.0f));
			else
				DrawLight(ms, 3.0f, vec3(0.3f, 0.0f, 0.0f));

			//Draw Yellow Light
			DrawLight(ms, 0.0f, vec3(0.3f, 0.3f, 0.0f));

			//Draw Green Light
			if (_isGreen)
				DrawLight(ms, -3.0f, vec3(0.0f, 1.0f, 0.0f));
			else
				DrawLight(ms, -3.0f, vec3(0.0f, 0.3f, 0.0f));
		}
		ms->Pop();
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
		
		setColour(0.9f, 0.8f, 0.1f);
		//ms->Translate(vec3(0.0f, 0.0, 0.0));
		ms->Rotate(90.0, vec3(0.0f, 1.0, 0.0));
		ms->Scale(vec3(2.4f, 2.4f, 2.4f));

		drawCylinder(*ms);
	}
	ms->Pop();
}


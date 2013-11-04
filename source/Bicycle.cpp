#include "Bicycle.h"
#include "drawScene.h"
#include "MathUtils.h"
#include "Utility.h"
#include "Textures.h"

Bicycle::Bicycle(vec3* cameraPosition, vec3* cameraDirection)
{
	_transform = Transform();
	_transform.position = vec3(52.0f, 0.0f, -150.0f);
	_transform.rotation = vec3(0.0f, 1.0f, 0.0f);
	_transform.scale = vec3(1.5f, 1.5f, 1.5f);
	
	_cameraPosition = cameraPosition;
	_cameraDirection = cameraDirection;
}

void Bicycle::Draw(ModelviewStack* ms)
{
	if (!Utility::isVisible(_transform.position, *_cameraPosition, *_cameraDirection))
		return;

	ms->Push();
	{
		ms->Translate(_transform.position);
		ms->Rotate(90.0f, _transform.rotation);
		ms->Rotate(10.0f, vec3(1.0f, 0.0f, 0.0f));
		ms->Scale(_transform.scale);
		DrawWheels(ms);
		DrawBody(ms);
	}
	ms->Pop();
}

void Bicycle::DrawWheels(ModelviewStack* ms)
{
	// Draw inner wheels
	setColour(1.0f, 1.0f, 1.0f);
	useTexture(BRICKS_TEXTURE);
	ms->Push();
	{
		ms->Translate(vec3(4.5f, 3.0f, 0.0f));
		ms->Scale(vec3(2.7f, 2.7f, 0.4f));
		drawSphere(*ms);
	}
	ms->Pop();
	ms->Push();
	{
		ms->Translate(vec3(-4.5f, 3.0f, 0.0f));
		ms->Scale(vec3(2.7f, 2.7f, 0.4f));
		drawSphere(*ms);
	}
	ms->Pop();
	useTexture(0);

	// Draw tires
	setColour(0.1f, 0.1f, 0.1f);
	ms->Push();
	{
		ms->Translate(vec3(4.5f, 3.0f, 0.0f));
		ms->Scale(vec3(3.0f, 3.0f, 0.3f));
		drawSphere(*ms);
	}
	ms->Pop();
	ms->Push();
	{
		ms->Translate(vec3(-4.5f, 3.0f, 0.0f));
		ms->Scale(vec3(3.0f, 3.0f, 0.3f));
		drawSphere(*ms);
	}
	ms->Pop();
}

void Bicycle::DrawBody(ModelviewStack* ms)
{
	setColour(0.3f, 0.0f, 0.0f);
	// Draw front axle;
	ms->Push();
	{
		ms->Translate(vec3(4.5f, 3.0f, 0.0f));
		ms->Scale(vec3(0.4f, 0.4f, 1.6f));
		drawCylinder(*ms);
	}
	ms->Pop();;
	// Draw back axle;
	ms->Push();
	{
		ms->Translate(vec3(-4.5f, 3.0f, 0.0f));
		ms->Scale(vec3(0.4f, 0.4f, 1.6f));
		drawCylinder(*ms);
	}
	ms->Pop();

	ms->Push();
	{
		ms->Translate(vec3(4.5f, 2.8f, 0.0f));
		ms->Rotate(20.0f, vec3(0.0f, 0.0f, 1.0f));

		// Draw front left beam
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 2.0f, 0.7f));
			ms->Scale(vec3(0.4f, 4.0f, 0.4f));
			ms->Rotate(-90.0f, vec3(1.0f, 0.0f, 0.0f));
			drawCylinder(*ms);
		}
		ms->Pop();

		// Draw front right beam
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 2.0f, -0.7f));
			ms->Scale(vec3(0.4f, 4.0f, 0.4f));
			ms->Rotate(-90.0f, vec3(1.0f, 0.0f, 0.0f));
			drawCylinder(*ms);
		}
		ms->Pop();

		//Draw front top crossbar
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 3.9f, 0.0f));
			ms->Scale(vec3(0.4f, 0.4f, 1.6f));
			drawCylinder(*ms);
		}
		ms->Pop();

		//Draw handle bar post
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 5.0f, 0.0f));
			ms->Scale(vec3(0.4f, 2.0f, 0.4f));
			ms->Rotate(-90.0f, vec3(1.0f, 0.0f, 0.0f));
			drawCylinder(*ms);
		}
		ms->Pop();
		//Draw handle bar joint
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 6.0f, 0.0f));
			ms->Scale(vec3(0.2f, 0.2f, 0.2f));
			ms->Rotate(-90.0f, vec3(1.0f, 0.0f, 0.0f));
			drawSphere(*ms);
		}
		ms->Pop();

		setColour(0.1f, 0.1f, 0.1f);
		//Draw left handle bar
		ms->Push();
		{
			ms->Rotate(10.0f, vec3(0.0f, 1.0f, 0.0f));
			ms->Translate(vec3(0.0f, 6.0f, -0.9f));
			ms->Scale(vec3(0.4f, 0.4f, 1.8f));
			drawCylinder(*ms);
		}
		ms->Pop();
		//Draw right handle bar
		ms->Push();
		{
			ms->Rotate(-10.0f, vec3(0.0f, 1.0f, 0.0f));
			ms->Translate(vec3(0.0f, 6.0f, 0.9f));
			ms->Scale(vec3(0.4f, 0.4f, 1.8f));
			drawCylinder(*ms);
		}
		ms->Pop();
	}
	ms->Pop();

	setColour(0.3f, 0.0f, 0.0f);
	ms->Push();
	{
		ms->Translate(vec3(-4.5f, 2.8f, 0.0f));
		ms->Rotate(-30.0f, vec3(0.0f, 0.0f, 1.0f));

		// Draw back top left beam
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 2.0f, 0.7f));
			ms->Scale(vec3(0.4f, 4.0f, 0.4f));
			ms->Rotate(-90.0f, vec3(1.0f, 0.0f, 0.0f));
			drawCylinder(*ms);
		}
		ms->Pop();

		// Draw back top right beam
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 2.0f, -0.7f));
			ms->Scale(vec3(0.4f, 4.0f, 0.4f));
			ms->Rotate(-90.0f, vec3(1.0f, 0.0f, 0.0f));
			drawCylinder(*ms);
		}
		ms->Pop();

		//Draw back top crossbar
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 3.9f, 0.0f));
			ms->Scale(vec3(0.4f, 0.4f, 1.6f));
			drawCylinder(*ms);
		}
		ms->Pop();
	}
	ms->Pop();

	ms->Push();
	{
		ms->Translate(vec3(-4.5f, 2.8f, 0.0f));
		ms->Rotate(-90.0f, vec3(0.0f, 0.0f, 1.0f));

		// Draw back bottom left beam
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 2.0f, 0.7f));
			ms->Scale(vec3(0.4f, 4.0f, 0.4f));
			ms->Rotate(-90.0f, vec3(1.0f, 0.0f, 0.0f));
			drawCylinder(*ms);
		}
		ms->Pop();

		// Draw back bottom right beam
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 2.0f, -0.7f));
			ms->Scale(vec3(0.4f, 4.0f, 0.4f));
			ms->Rotate(-90.0f, vec3(1.0f, 0.0f, 0.0f));
			drawCylinder(*ms);
		}
		ms->Pop();

		//Draw back bottom crossbar
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 3.9f, 0.0f));
			ms->Scale(vec3(0.4f, 0.4f, 2.0f));
			drawCylinder(*ms);
		}
		ms->Pop();

		//Draw left pedal bar
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 5.0f, 1.0f));
			ms->Scale(vec3(0.2f, 2.0f, 0.2f));
			ms->Rotate(-90.0f, vec3(1.0f, 0.0f, 0.0f));
			drawCylinder(*ms);
		}
		ms->Pop();

		//Draw right pedal bar
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 3.0f, -1.0f));
			ms->Scale(vec3(0.2f, 2.0f, 0.2f));
			ms->Rotate(-90.0f, vec3(1.0f, 0.0f, 0.0f));
			drawCylinder(*ms);
		}
		ms->Pop();
	}
	ms->Pop();

	// Draw main beam
	ms->Push();
	{
		ms->Translate(vec3(0.2f, 6.4f, 0.0f));
		ms->Rotate(5.0f, vec3(0.0f, 0.0f, 1.0f));
		ms->Rotate(90.0f, vec3(0.0f, 1.0f, 0.0f));
		ms->Scale(vec3(0.4f, 0.4f, 5.7f));
		drawCylinder(*ms);
	}
	ms->Pop();
	ms->Push();
	{
		ms->Translate(vec3(1.3f, 4.7f, 0.0f));
		ms->Rotate(45.0f, vec3(0.0f, 0.0f, 1.0f));
		ms->Rotate(90.0f, vec3(0.0f, 1.0f, 0.0f));
		ms->Scale(vec3(0.35f, 0.35f, 5.25f));
		drawCylinder(*ms);
	}
	ms->Pop();

	//Draw seat bar
	ms->Push();
	{
		ms->Translate(vec3(-2.0f, 6.2f, 0.0f));
		ms->Rotate(20.0f, vec3(0.0f, 0.0f, 1.0f));
		ms->Translate(vec3(0.0f, 1.0f, 0.0f));
		ms->Scale(vec3(0.35f, 2.0f, 0.35f));
		ms->Rotate(90.0f, vec3(1.0f, 0.0f, 0.0f));
		drawCylinder(*ms);
	}
	ms->Pop();

	setColour(0.1f, 0.1f, 0.1f);
	//Draw left pedal
	ms->Push();
	{
		ms->Translate(vec3(1.6f, 2.7f, 1.5f));
		ms->Rotate(30.0f, vec3(.0f, 0.0f, 1.0f));
		ms->Scale(vec3(0.5f, 0.2f, 0.75f));
		drawCube(*ms);
	}
	ms->Pop();
	//Draw right pedal
	ms->Push();
	{
		ms->Translate(vec3(-2.1f, 2.7f, -1.7f));
		ms->Rotate(-30.0f, vec3(0.0f, 0.0f, 1.0f));
		ms->Scale(vec3(0.5f, 0.2f, 0.75f));
		drawCube(*ms);
	}
	ms->Pop();

	//Draw seat 
	ms->Push();
	{
		ms->Translate(vec3(-2.4f, 8.0f, 0.0f));
		ms->Rotate(-10.0f, vec3(0.0f, 0.0f, 1.0f));
		ms->Scale(vec3(1.2f, 0.2f, 0.9f));
		drawSphere(*ms);
	}
	ms->Pop();

}
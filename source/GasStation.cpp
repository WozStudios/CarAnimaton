#include "GasStation.h"
#include "drawScene.h"
#include "Textures.h"

GasStation::GasStation()
{
	_transform.position = vec3(-200.0f, 0.0f, -120.0f);
	_transform.rotation = vec3(0.0f, 1.0f, 0.0f);
	_transform.scale = vec3(128.0f, 40.0f, 64.0f);
}

void GasStation::Draw(ModelviewStack* ms)
{
	useTexture(BRICKS_TEXTURE);
	setColour(1.0f, 1.0f, 1.0f);
	
	// Draw Building
	ms->Push();
	{
		ms->Translate(_transform.position);
		ms->Rotate(-90.0f, _transform.rotation);
		
		// Draw main building
		ms->Push();
		{
			ms->Scale(vec3(_transform.scale.x / 2.0f,
						   _transform.scale.y / 2.0f,
						   _transform.scale.z / 2.0f));
			ms->Translate(vec3(0.0f, 1.0f, 0.0f));

			drawCube(*ms);
		}
		ms->Pop();

		// Draw Roof
		useTexture(0);
		setColour(1.0f, 1.0f, 1.0f);
		ms->Push();
		{
			ms->Translate(vec3(0.0f, _transform.scale.y, -_transform.scale.z * 0.75f));
			ms->Scale(vec3(_transform.scale.x / 1.9f,
						   _transform.scale.y / 8.0f,
						   _transform.scale.z * 1.5f));
			ms->Translate(vec3(0.0f, 1.0f, 0.0f));

			drawCube(*ms);
		}
		ms->Pop();

		DrawPosts(ms);
		DrawGasPumps(ms);
		DrawTrim(ms);
		DrawDoors(ms);
	}
	ms->Pop();

	// Draw main building shadow
	useLighting(0);
	useTexture(SQUARE_SHADOW_TEXTURE);
	ms->Push();
	{
		ms->Translate(vec3(_transform.position.x, 0.003f, _transform.position.z));
		ms->Rotate(270.0f, vec3(1.0f, 0.0f, 0.0f));
		ms->Scale(vec3(_transform.scale.z * 1.3f, _transform.scale.x * 1.3f, 1.0f));
		drawSquare(*ms);
	}
	ms->Pop();

	//Draw gas pump shadows
	ms->Push();
	{
		ms->Translate(vec3(-71.9f, 0.003f, -94.4f));
		ms->Rotate(270.0f, vec3(1.0f, 0.0f, 0.0f));
		ms->Scale(vec3(10.8f, 10.8f, 1.0f));
		drawSquare(*ms);
	}
	ms->Pop();
	ms->Push();
	{
		ms->Translate(vec3(-71.9f, 0.003f, -145.7f));
		ms->Rotate(270.0f, vec3(1.0f, 0.0f, 0.0f));
		ms->Scale(vec3(10.8f, 10.8f, 1.0f));
		drawSquare(*ms);
	}
	ms->Pop();

	//Draw pole shadows
	useTexture(CIRCLE_SHADOW_TEXTURE);
	ms->Push();
	{
		ms->Translate(vec3(-71.9f, 0.003f, -61.8f));
		ms->Rotate(270.0f, vec3(1.0f, 0.0f, 0.0f));
		ms->Scale(vec3(7.5f, 7.5f, 1.0f));
		drawSquare(*ms);
	}
	ms->Pop();
	ms->Push();
	{
		ms->Translate(vec3(-71.9f, 0.003f, -120.0f));
		ms->Rotate(270.0f, vec3(1.0f, 0.0f, 0.0f));
		ms->Scale(vec3(7.5f, 7.5f, 1.0f));
		drawSquare(*ms);
	}
	ms->Pop();
	ms->Push();
	{
		ms->Translate(vec3(-71.9f, 0.003f, -178.15f));
		ms->Rotate(270.0f, vec3(1.0f, 0.0f, 0.0f));
		ms->Scale(vec3(7.5f, 7.5f, 1.0f));
		drawSquare(*ms);
	}
	ms->Pop();

	useLighting(1);
}

void GasStation::DrawTrim(ModelviewStack* ms)
{
	setColour(0.8f, 0.15f, 0.0f);
	ms->Push();
	{
		ms->Translate(vec3(_transform.scale.x / 1.9f, _transform.scale.y + _transform.scale.y / 8.0f, -_transform.scale.z * 0.75f));
		ms->Scale(vec3(_transform.scale.y / 4.0f, _transform.scale.y / 4.0f, _transform.scale.z * 3.0f));
		drawCylinder(*ms);
	}
	ms->Pop();
	ms->Push();
	{
		ms->Translate(vec3(-_transform.scale.x / 1.9f, _transform.scale.y + _transform.scale.y / 8.0f, -_transform.scale.z * 0.75f));
		ms->Scale(vec3(_transform.scale.y / 4.0f, _transform.scale.y / 4.0f, _transform.scale.z * 3.0f));
		drawCylinder(*ms);
	}
	ms->Pop();
	ms->Push();
	{
		ms->Translate(vec3(0.0f, _transform.scale.y + _transform.scale.y / 8.0f, -_transform.scale.z * 2.25f));
		ms->Rotate(90.0f, _transform.rotation);
		ms->Scale(vec3(_transform.scale.y / 4.0f, _transform.scale.y / 4.0f, _transform.scale.z * 2.1f));
		drawCylinder(*ms);
	}
	ms->Pop();
	ms->Push();
	{
		ms->Translate(vec3(_transform.scale.x / 1.9f, _transform.scale.y + _transform.scale.y / 8.0f, -_transform.scale.z * 2.25f));
		ms->Scale(vec3(_transform.scale.y / 8.0f, _transform.scale.y / 8.0f, _transform.scale.y / 8.0f));
		drawSphere(*ms);
	}
	ms->Pop();
	ms->Push();
	{
		ms->Translate(vec3(-_transform.scale.x / 1.9f, _transform.scale.y + _transform.scale.y / 8.0f, -_transform.scale.z * 2.25f));
		ms->Scale(vec3(_transform.scale.y / 8.0f, _transform.scale.y / 8.0f, _transform.scale.y / 8.0f));
		drawSphere(*ms);
	}
	ms->Pop();
}

void GasStation::DrawPosts(ModelviewStack* ms)
{
	ms->Push();
	{
		ms->Translate(vec3(_transform.scale.x / 2.2f, _transform.scale.y / 2.0f, -_transform.scale.z * 2.0f));
		ms->Scale(vec3(4.0f, _transform.scale.y, 4.0f));
		ms->Rotate(90.0f, vec3(1.0f, 0.0f, 0.0f));

		drawCylinder(*ms);
	}
	ms->Pop();
	ms->Push();
	{
		ms->Translate(vec3(0.0f, _transform.scale.y / 2.0f, -_transform.scale.z * 2.0f));
		ms->Scale(vec3(4.0f, _transform.scale.y, 4.0f));
		ms->Rotate(90.0f, vec3(1.0f, 0.0f, 0.0f));

		drawCylinder(*ms);
	}
	ms->Pop();
	ms->Push();
	{
		ms->Translate(vec3(-_transform.scale.x / 2.2f, _transform.scale.y / 2.0f, -_transform.scale.z * 2.0f));
		ms->Scale(vec3(4.0f, _transform.scale.y, 4.0f));
		ms->Rotate(90.0f, vec3(1.0f, 0.0f, 0.0f));

		drawCylinder(*ms);
	}
	ms->Pop();
}

void GasStation::DrawGasPumps(ModelviewStack* ms)
{
	DrawGasPump(ms, 0.2f);
	DrawGasPump(ms, -0.2f);
}

void GasStation::DrawGasPump(ModelviewStack* ms, float position)
{
	setColour(1.0f, 1.0f, 1.0f);
	// Draw Main Body
	ms->Push();
	{
		ms->Translate(vec3(_transform.scale.x * position, _transform.scale.y / 6.0f, -_transform.scale.z * 2.0f));
		ms->Scale(vec3(4.0f, _transform.scale.y / 3.0f, 4.0f));
		ms->Rotate(90.0f, vec3(1.0f, 0.0f, 0.0f));

		drawCube(*ms);
	}
	ms->Pop();

	//Draw left post
	setColour(0.8f, 0.15f, 0.0f);
	ms->Push();
	{
		ms->Translate(vec3(_transform.scale.x * position + 4.0f, _transform.scale.y / 8.0f, -_transform.scale.z * 2.0f));
		ms->Scale(vec3(2.0f, _transform.scale.y / 4.0f, 2.0f));
		ms->Rotate(90.0f, vec3(1.0f, 0.0f, 0.0f));

		drawCylinder(*ms);
	}
	ms->Pop();
	ms->Push();
	{
		ms->Translate(vec3(_transform.scale.x * position - 4.0f, _transform.scale.y / 8.0f, -_transform.scale.z * 2.0f));
		ms->Scale(vec3(2.0f, _transform.scale.y / 4.0f, 2.0f));
		ms->Rotate(90.0f, vec3(1.0f, 0.0f, 0.0f));

		drawCylinder(*ms);
	}
	ms->Pop();

	//Draw right post
	ms->Push();
	{
		ms->Translate(vec3(_transform.scale.x * position + 4.0f, _transform.scale.y / 4.0f, -_transform.scale.z * 2.0f));
		ms->Scale(vec3(1.0f, 1.0f, 1.0f));
		ms->Rotate(90.0f, vec3(1.0f, 0.0f, 0.0f));

		drawSphere(*ms);
	}
	ms->Pop();
	ms->Push();
	{
		ms->Translate(vec3(_transform.scale.x * position - 4.0f, _transform.scale.y / 4.0f, -_transform.scale.z * 2.0f));
		ms->Scale(vec3(1.0f, 1.0f, 1.0f));
		ms->Rotate(90.0f, vec3(1.0f, 0.0f, 0.0f));

		drawSphere(*ms);
	}
	ms->Pop();
	//Draw Meter
	ms->Push();
	{
		ms->Translate(vec3(_transform.scale.x * position, _transform.scale.y / 2.0f, -_transform.scale.z * 2.0f));
		ms->Scale(vec3(4.0f, 4.0f, 1.0f));
		ms->Rotate(90.0f, vec3(1.0f, 0.0f, 0.0f));

		drawSphere(*ms);
	}
	ms->Pop();
	setColour(1.0f, 1.0f, 1.0f);
	ms->Push();
	{
		ms->Translate(vec3(_transform.scale.x * position, _transform.scale.y / 2.0f, -_transform.scale.z * 1.995f));
		ms->Scale(vec3(3.7f, 3.7f, 1.0f));
		ms->Rotate(90.0f, vec3(1.0f, 0.0f, 0.0f));

		drawSphere(*ms);
	}
	ms->Pop();

	// Draw Handle
	setColour(0.15f, 0.15f, 0.15f);
	ms->Push();
	{
		ms->Translate(vec3(_transform.scale.x * position, _transform.scale.y / 3.0f, -_transform.scale.z * 1.92f));
		ms->Rotate(60.0f, vec3(1.0f, 0.0f, 0.0f));
		ms->Push();
		{
			ms->Scale(vec3(0.2f, 2.0f, 0.4f));

			drawCube(*ms);
		}
		ms->Pop();
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 2.2f, 0.8f));
			ms->Rotate(90.0f, vec3(1.0f, 0.0f, 0.0f));
			ms->Scale(vec3(0.2f, 1.2f, 0.2f));

			drawCube(*ms);
		}
		ms->Pop();
		ms->Push();
		{
			ms->Translate(vec3(0.0f, 1.0f, 1.8f));
			ms->Scale(vec3(0.2f, 1.0f, 0.2f));
			drawCube(*ms);
		}
		ms->Pop();
		ms->Push();
		{
			ms->Translate(vec3(0.0f, -0.2f, 1.2f));
			ms->Rotate(90.0f, vec3(1.0f, 0.0f, 0.0f));
			ms->Scale(vec3(0.2f, 0.8f, 0.2f));

			drawCube(*ms);
		}
		ms->Pop();
	}
	ms->Pop();
}

void GasStation::DrawDoors(ModelviewStack* ms)
{
	// Draw Door
	useTexture(0);
	setColour(0.3f, 0.3f, 0.3f);
	ms->Push();
	{
		ms->Translate(vec3(0.0f, 0.0f, -_transform.scale.z * 0.515f));
		ms->Scale(vec3(12.0f, 12.0f, 1.0f));
		ms->Translate(vec3(0.0f, 1.0f, 0.0f));

		drawCube(*ms);
	}
	ms->Pop();

	//Draw left framepost
	setColour(0.8f, 0.15f, 0.0f);
	ms->Push();
	{
		ms->Translate(vec3(12.0f, 0.0f, -_transform.scale.z * 0.515f));
		ms->Scale(vec3(1.0f, 12.0f, 1.5f));
		ms->Translate(vec3(0.0f, 1.0f, 0.0f));

		drawCube(*ms);
	}
	ms->Pop();
	//Draw middle framepost
	ms->Push();
	{
		ms->Translate(vec3(0.0f, 0.0f, -_transform.scale.z * 0.515f));
		ms->Scale(vec3(1.0f, 12.0f, 1.5f));
		ms->Translate(vec3(0.0f, 1.0f, 0.0f));

		drawCube(*ms);
	}
	ms->Pop();
		
	//Draw right framepost
	ms->Push();
	{
		ms->Translate(vec3(-12.0f, 0.0f, -_transform.scale.z * 0.515f));
		ms->Scale(vec3(1.0f, 12.0f, 1.5f));
		ms->Translate(vec3(0.0f, 1.0f, 0.0f));

		drawCube(*ms);
	}
	ms->Pop();
		
	//Draw top framepost
	ms->Push();
	{
		ms->Translate(vec3(0.0f, 24.0f, -_transform.scale.z * 0.515f));
		ms->Scale(vec3(13.0f, 1.0f, 1.5f));
		ms->Translate(vec3(0.0f, 1.0f, 0.0f));

		drawCube(*ms);
	}
	ms->Pop();

	//Draw middle-horizontal framepost
	ms->Push();
	{
		ms->Translate(vec3(0.0f, 10.0f, -_transform.scale.z * 0.515f));
		ms->Scale(vec3(11.0f, 0.5f, 1.2f));
		ms->Translate(vec3(0.0f, 1.0f, 0.0f));

		drawCube(*ms);
	}
	ms->Pop();
		
	//Draw left handle
	ms->Push();
	{
		ms->Translate(vec3(3.0f, 13.0f, -_transform.scale.z * 0.525f));
		ms->Scale(vec3(0.25f, 1.0f, 01.15f));
		ms->Translate(vec3(0.0f, 1.0f, 0.0f));
		drawCube(*ms);
	}
	ms->Pop();
	ms->Push();
	{
		ms->Translate(vec3(3.5f, 12.5f, -_transform.scale.z * 0.54f));
		ms->Scale(vec3(0.8f, 1.7f, 0.2f));
		ms->Translate(vec3(0.0f, 1.0f, 0.0f));
		drawCube(*ms);
	}
	ms->Pop();

	//Draw right handle
	ms->Push();
	{
		ms->Translate(vec3(-3.0f, 13.0f, -_transform.scale.z * 0.525f));
		ms->Scale(vec3(0.25f, 1.0f, 01.15f));
		ms->Translate(vec3(0.0f, 1.0f, 0.0f));
		
		drawCube(*ms);
	}
	ms->Pop();
	ms->Push();
	{
		ms->Translate(vec3(-3.5f, 12.5f, -_transform.scale.z * 0.54f));
		ms->Scale(vec3(0.8f, 1.7f, 0.2f));
		ms->Translate(vec3(0.0f, 1.0f, 0.0f));
		drawCube(*ms);
	}
	ms->Pop();
}

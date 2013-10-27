#include "Store.h"
#include "drawScene.h"

Store::Store(Transform transform)
{
	_transform = transform;
	_transform.position = vec3(120.0f, 0.0f, -120.0f);
	_transform.rotation = vec3(0.0f, 1.0f, 0.0f);
	_transform.scale = vec3(128.0f, 40.0f, 128.0f);
}

void Store::Draw(ModelviewStack* ms)
{
	useTexture(9);
	setColour(0.92f, 0.53f, 0.22f);
	
	// Draw Building
	ms->Push();
	{
		ms->Translate(_transform.position);
		ms->Rotate(90.0f, _transform.rotation);
		
		ms->Push();
		{
			ms->Scale(vec3(_transform.scale.x / 2.0f,
						   _transform.scale.y / 2.0f,
						   _transform.scale.z / 2.0f));
			ms->Translate(vec3(0.0f, 1.0f, 0.0f));

			drawCube(*ms);
		}
		ms->Pop();
		
		// Draw Trim
		useTexture(0);
		ms->Push();
		{
			ms->Translate(vec3(0.0f, _transform.scale.y, 0.0f));
			ms->Scale(vec3(_transform.scale.x / 1.9f,
						   _transform.scale.y / 8.0f,
						   _transform.scale.z / 1.9f));
			ms->Translate(vec3(0.0f, 1.0f, 0.0f));

			drawCube(*ms);
		}
		ms->Pop();
		
		// Draw Sign
		useTexture(10);
		ms->Push();
		{
			ms->Translate(vec3(0.0f, _transform.scale.y * 0.8f, -_transform.scale.z * 0.515f));
			ms->Rotate(180.0f, _transform.rotation);
			ms->Scale(vec3(24.0f, 12.0f, 1.0f));
			//ms->Translate(vec3(0.0f, 1.0f, 0.0f));

			drawSquare(*ms);
		}
		ms->Pop();

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
		setColour(0.1f, 0.1f, 0.1f);
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
			ms->Translate(vec3(3.0f, 13.0f, -_transform.scale.z * 0.52f));
			ms->Scale(vec3(0.25f, 1.0f, 01.15f));
			ms->Translate(vec3(0.0f, 1.0f, 0.0f));
			drawCube(*ms);
		}
		ms->Pop();
		ms->Push();
		{
			ms->Translate(vec3(3.5f, 12.5f, -_transform.scale.z * 0.53f));
			ms->Scale(vec3(0.8f, 1.7f, 0.2f));
			ms->Translate(vec3(0.0f, 1.0f, 0.0f));
			drawCube(*ms);
		}
		ms->Pop();

		//Draw right handle
		ms->Push();
		{
			ms->Translate(vec3(-3.0f, 13.0f, -_transform.scale.z * 0.52f));
			ms->Scale(vec3(0.25f, 1.0f, 01.15f));
			ms->Translate(vec3(0.0f, 1.0f, 0.0f));

			drawCube(*ms);
		}
		ms->Pop();
		ms->Push();
		{
			ms->Translate(vec3(-3.5f, 12.5f, -_transform.scale.z * 0.53f));
			ms->Scale(vec3(0.8f, 1.7f, 0.2f));
			ms->Translate(vec3(0.0f, 1.0f, 0.0f));
			drawCube(*ms);
		}
		ms->Pop();
	}
	ms->Pop();
}
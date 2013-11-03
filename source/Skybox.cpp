#include "Skybox.h"
#include "drawScene.h"
#include "..\cse3431Template\Textures.h"

Skybox::Skybox(double size, vec3* cameraPos)
{
	_size = size;

	_transform.position = vec3(0.0, 0.0, 0.0);
	_transform.rotation = vec3(0.0, 0.0, 0.0);
	_transform.scale = vec3(_size / 2, _size / 2, _size / 2);

	_cameraPosition = cameraPos;
	
	_rotationAngle = 0.0f;
	_rotationSpeed = 5.0f;
}

void Skybox::Draw(ModelviewStack* ms)
{
	useLighting(0);

	setColour(1.0, 1.0, 1.0);
	ms->Push();
	{
		DrawWalls(ms);
	}
	ms->Pop();
}

void Skybox::DrawWalls(ModelviewStack* ms)
{
	useLighting(0);

	ms->Push();
	{
		ms->Translate(_transform.position);
		ms->Rotate(_rotationAngle, vec3(0.0, 1.0, 0.0));
	
		//Draw Left Wall
		useTexture(SKY_LEFT_TEXTURE);
		DrawWall(ms, vec3(_size / 2.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), 270.0);
	
		//Draw Front Wall
		useTexture(SKY_FRONT_TEXTURE);
		DrawWall(ms, vec3(0.0, 0.0, _size / 2.0), vec3(0.0, 1.0, 0.0), 180.0);
	
		//Draw Right Wall
		useTexture(SKY_RIGHT_TEXTURE);
		DrawWall(ms, vec3(-_size / 2.0, 0.0, 0.0), vec3(0.0, 1.0, 0.0), 90.0);
	
		//Draw Back Wall
		useTexture(SKY_BACK_TEXTURE);
		DrawWall(ms, vec3(0.0, 0.0, -_size / 2.0), vec3(0.0, 1.0, 0.0), 0.);
	
		//Draw Ceiling
		useTexture(SKY_TOP_TEXTURE);
		DrawWall(ms, vec3(0.0, _size / 2.0, 0.0), vec3(1.0, 0.0, 0.0), 90.0);
	}
	ms->Pop();

	useLighting(1);
}

void Skybox::DrawWall(ModelviewStack* ms, vec3 translation, vec3 rotationAxis, double rotation)
{
	ms->Push();
	{
		double epsilon = 1.005;
		ms->Translate(vec3(translation));
		ms->Rotate(rotation, rotationAxis);
		ms->Scale(vec3(_size * epsilon, _size * epsilon, 1.0));
		drawSquare(*ms);
	}
	ms->Pop();
}

void Skybox::Update(float deltaTime)
{
	_transform.position = *_cameraPosition;
	_rotationAngle += deltaTime * _rotationSpeed;

	if (_rotationAngle >= 360.0f)
	{
		_rotationAngle -= 360.0f;
	}
}
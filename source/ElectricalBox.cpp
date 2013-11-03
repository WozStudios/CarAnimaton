#include "ElectricalBox.h"
#include "MathUtils.h"
#include "drawScene.h"
#include "Utility.h"
#include "..\cse3431Template\Textures.h"

ElectricalBox::ElectricalBox(vec3* cameraPosition, vec3* cameraDirection)
{
	_transform = Transform();
	_transform.position = vec3(0.0f, 15.0f, 47.0f);
	_transform.rotation = vec3(1.0f, 0.0f, 0.0f);
	_transform.scale = vec3(6.0f, 7.0f, 2.0f);

	_cameraPosition = cameraPosition;
	_cameraDirection = cameraDirection;

	_colour = vec3(0.5f, 0.5f, 0.5f);
	_exploded = false;
	
	GenerateSparks();
}

void ElectricalBox::GenerateSparks()
{
	_sparks.push_back(new Spark(_transform.position, vec3(-20.0f, 30.0f, 5.0f)));
	_sparks.push_back(new Spark(_transform.position, vec3( 20.0f, 25.0f, 2.0f)));
	_sparks.push_back(new Spark(_transform.position, vec3(-15.0f, 35.0f, -3.0f)));
	_sparks.push_back(new Spark(_transform.position, vec3( 15.0f, 30.0f, -5.0f)));
	_sparks.push_back(new Spark(_transform.position, vec3(-10.0f, 30.0f, 0.0f)));
	_sparks.push_back(new Spark(_transform.position, vec3( 0.0f, 25.0f, 20.0f)));
	_sparks.push_back(new Spark(_transform.position, vec3(-5.0f, 35.0f, -20.0f)));
	_sparks.push_back(new Spark(_transform.position, vec3( 5.0f, 25.0f, -15.0f)));
	_sparks.push_back(new Spark(_transform.position, vec3(-8.0f, 3.0f, 3.0f)));
	_sparks.push_back(new Spark(_transform.position, vec3( 0.0f, -2.0f, -6.0f)));
	_sparks.push_back(new Spark(_transform.position, vec3( 5.0f, 3.0f, -4.0f)));
	_sparks.push_back(new Spark(_transform.position, vec3(-6.0f, 10.0f, 5.0f)));
	_sparks.push_back(new Spark(_transform.position, vec3(-20.0f, -2.0f, -6.0f)));
	_sparks.push_back(new Spark(_transform.position, vec3(30.0f, -2.0f, 4.0f)));
	_sparks.push_back(new Spark(_transform.position, vec3(-32.0f, -3.0f, 5.0f)));
	_sparks.push_back(new Spark(_transform.position, vec3(6.0f, 15.0f, -5.0f)));
}

void ElectricalBox::Update(float deltaTime)
{
	if (_exploded && _sparks.size() > 0)
	{
		for (list<Spark*>::iterator i = _sparks.begin(); i != _sparks.end(); )
		{
			(*i)->Update(deltaTime);

			if (!(*i)->IsAlive())
			{
				delete *i;
				i = _sparks.erase(i);
			}
			else
			{
				i++;
			}
		}
	}
}

void ElectricalBox::Draw(ModelviewStack* ms)
{
	if (!Utility::isVisible(_transform.position, *_cameraPosition, *_cameraDirection))
		return;

	ms->Push();
	{
		//ms->Translate(_transform.position);

		useTexture(0);
		vec3 colour = vec3(_colour.x, _colour.y, _colour.z);
		setMaterial(colour, colour, colour, 60.0f);
		// Draw box
		ms->Push();
		{
			ms->Translate(vec3(_transform.position));
			ms->Scale(vec3(0.5f * _transform.scale));
			drawCube(*ms);
		}
		ms->Pop();

		//Draw door
		ms->Push();
		{
			ms->Translate(vec3(_transform.position.x - 0.1f,
				_transform.position.y,
				_transform.position.z - 1.0f));

			if (_exploded)
			{
				ms->Translate(vec3(1.0f, -0.9f, 0.0f));
				ms->Rotate(15.0f, vec3(0.0f, 0.0f, 1.0f));
			}
			
			ms->Push();
			{
				ms->Scale(vec3(0.5f * _transform.scale.x + 0.1f,
					0.5f * _transform.scale.y + 0.2f, 
					0.03f * _transform.scale.z));
				drawCube(*ms);
			}
			ms->Pop();
		}
		ms->Pop();

		// Draw warning texture
		useTexture(WARNING_SIGN_TEXTURE);
		//wsetColour(1.0f, 1.0f, 1.0f);
		ms->Push();
		{
			ms->Translate(vec3(_transform.position.x - 0.1f,
				_transform.position.y,
				_transform.position.z - 1.07f));

			if (_exploded)
			{
				ms->Translate(vec3(1.0f, -0.9f, 0.0f));
				ms->Rotate(15.0f, vec3(0.0f, 0.0f, 1.0f));
			}

			ms->Rotate(180.0f, vec3(0.0f, 1.0f, 0.0f));
			ms->Scale(vec3(0.5f * _transform.scale));
			drawSquare(*ms);
		}
		ms->Pop();
	}
	ms->Pop();


	if (_exploded && _sparks.size() > 0)
		DrawSparks(ms);
}

void ElectricalBox::DrawSparks(ModelviewStack* ms)
{
	for (list<Spark*>::iterator i = _sparks.begin(); i != _sparks.end(); i++)
	{
		(*i)->Draw(ms);
	}
}

void ElectricalBox::Explode()
{
	_exploded = true;
	_colour = vec3(0.05f, 0.05f, 0.05f);
}
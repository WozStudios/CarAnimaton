#include "Metronome.h"
#include "drawScene.h"

Metronome::Metronome()
{
	_transform = Transform();
	_transform.rotation = vec3(0.0f, 0.0f, 1.0f);
	_transform.scale = vec3(1.0f, 10.0f, 1.0f);
	_counter = 0.0f;
	_rotationAngle = 0.0f;
}

void Metronome::Update(float deltaTime)
{
	_counter += deltaTime;

	_rotationAngle = cos(_counter * 1.2f) * 45.0f;
}

void Metronome::Draw(ModelviewStack* ms)
{
	ms->Push();
	{
		ms->Rotate(_rotationAngle, _transform.rotation);
		ms->Translate(vec3(_transform.position.x,
						   _transform.position.y,
						   _transform.position.z));
		ms->Scale(_transform.scale);
		ms->Translate(vec3(0.0f, 1.0f, 0.0f));
		drawCube(*ms);
	}
	ms->Pop();
}
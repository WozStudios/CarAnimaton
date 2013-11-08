#include "Spark.h"
#include "drawScene.h"
#include "Random.h"

Spark::Spark(vec3 position, vec3 velocity)
{
	_transform.position = position;
	_transform.scale = vec3(0.1f, 0.1f, 0.1f);

	_initialPosition = _transform.position;
	_velocity = velocity;
	_timeSinceCreated = 0.0f;
	_isAlive = true;

	_colour = vec3(1.0f, 0.9f, (float)Random(0.0, 0.8));
}

void Spark::Update(float deltaTime)
{
	
	_transform.position.x = _initialPosition.x + _velocity.x * _timeSinceCreated;
	_transform.position.z = _initialPosition.z + _velocity.z * _timeSinceCreated;
	_transform.position.y = _initialPosition.y +
		_velocity.y * _timeSinceCreated +
		0.5 * -10.0f * _timeSinceCreated *_timeSinceCreated;

	if (_transform.position.y < -1.0f)
	{
		_isAlive = false;
		return;
	}

	_timeSinceCreated += deltaTime;
}

void Spark::Draw(ModelviewStack* ms)
{
	setColour(_colour.x, _colour.y, _colour.z);
	ms->Push();
	{
		ms->Translate(_transform.position);
		ms->Scale(_transform.scale);
		drawSphere(*ms);
	}
	ms->Pop();
}
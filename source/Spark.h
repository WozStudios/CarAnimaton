#ifndef SPARK_H
#define SPARK_H

#include "IGameObject.h"

class Spark
{
private:
	Transform _transform;
	vec3 _initialPosition;
	vec3 _velocity;
	float _timeSinceCreated;
	bool _isAlive;
	vec3 _colour;

public:
	Spark(vec3 position, vec3 velocity);

	vec3 GetPosition() { return _transform.position; }

	void Update(float deltaTime);
	void Draw(ModelviewStack* ms);

	bool IsAlive() { return _isAlive; }

};

#endif
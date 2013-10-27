#ifndef BIRD_GENERATOR_H
#define BIRD_GENERATOR_H

#include "Bird.h"
#include <vector>

using std::vector;

class BirdGenerator
{
private:
	vec3 _position;
	vector<Bird*> _birds;
	vec3* _cameraPosition;
	vec3* _cameraDirection;

public:
	BirdGenerator(vec3 position, vec3* cameraPosition, vec3* cameraDirection);

	vector<Bird*> GetBirds() { return _birds; }

private:
	void Generate();
	Transform GenerateTransform();
};

#endif
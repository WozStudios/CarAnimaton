#ifndef FOREST_GENERATOR_H
#define FOREST_GENERATOR_H

#include <vector>
#include "Billboard.h"

using std::vector;

class ForestGenerator
{
private:
	vector<Billboard*> _trees;
	vec3 _position;
	int _numTrees;
	vec3* _cameraPosition;
	vec3* _cameraDirection;

public:
	ForestGenerator(vec3 position, vec3* cameraPosition, vec3* cameraDirection);

	vector<Billboard*> GetTrees() { return _trees; }

private:
	void Generate();
};

#endif
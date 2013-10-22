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

public:
	ForestGenerator(vec3 position = vec3(), vec3* cameraPosition = NULL, int numTrees = 0);

	vector<Billboard*> GetTrees() { return _trees; }

private:
	void Generate();
};

#endif
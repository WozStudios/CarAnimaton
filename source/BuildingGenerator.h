#ifndef BUILDING_GENERATOR_H
#define BUILDING_GENERATOR_H

#include <vector>
#include "Building.h"

using std::vector;

class BuildingGenerator
{
private:
	vec3 _position;
	int _numBuildings;

	vector<Building*> _buildings;

public:
	BuildingGenerator(vec3 position, int numBuildings);

	vector<Building*> GetBuildings() { return _buildings; }

private:
	void Generate();
};

#endif
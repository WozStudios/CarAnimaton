#ifndef DECAL_GENERATOR_H
#define DECAL_GENERATOR_H

#include "Decal.h"
#include <vector>

using std::vector;

class DecalGenerator
{
private:
	vector<Decal*> _decals;
	vec3* _cameraPosition;
	vec3* _cameraDirection;

public:
	DecalGenerator();

public:
	DecalGenerator(vec3* cameraPosition, vec3* cameraDirection);

	vector<Decal*> GetDecals() { return _decals; }

private:
	void Generate();
	Transform GenerateTransform();
};

#endif
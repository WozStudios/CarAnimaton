#include "ForestGenerator.h"
#include "Billboard.h"
#include "Random.h"

ForestGenerator::ForestGenerator(vec3 position, vec3* cameraPosition, int numTrees)
{
	_position = position;
	_numTrees = numTrees;
	_cameraPosition = cameraPosition;

	Generate();
}

void ForestGenerator::Generate()
{
	int numTrees = sqrt(_numTrees);
	
	for (int j = 0; j < numTrees; j++)
	{
		for (int i = 0; i < numTrees; i++)
		{
			Transform transform;
		
			transform.scale.y = 64 + Random(-16.0, 16.0);
			transform.scale.x = transform.scale.y / 2.0;

			transform.position = _position + vec3(i * transform.scale.x, 1.0, -j);

			_trees.push_back(new Billboard(transform, _cameraPosition, 7));
		}
	}
}
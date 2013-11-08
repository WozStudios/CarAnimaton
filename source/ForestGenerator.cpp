#include "ForestGenerator.h"
#include "Billboard.h"
#include "Random.h"

#include "Debug.h"

void ForestGenerator::Init(vec3 position, vec3* cameraPosition, vec3* cameraDirection)
{
	_position = position;
	_cameraPosition = cameraPosition;
	_cameraDirection = cameraDirection;

	Generate();
}

void ForestGenerator::Generate()
{
	int numTrees = sqrt(4);
	
	for (int j = 2; j >= 0; j--)
	{
		for (int i = 0; i < 16; i++)
		{
			Transform transform;
		
			transform.scale.y = 64 + Random(-16.0, 16.0);
			transform.scale.x = transform.scale.y / 2.0;

			transform.position = _position + vec3(i * (32 + Random( -4, 4)), 1.0, -j * transform.scale.x);

			_trees.push_back(Billboard(transform, _cameraPosition, _cameraDirection, 8));
		}
	}
}

void ForestGenerator::Destroy()
{
}
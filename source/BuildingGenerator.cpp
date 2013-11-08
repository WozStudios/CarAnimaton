#include "BuildingGenerator.h"
#include "Random.h"

#include "Debug.h"

BuildingGenerator::BuildingGenerator(vec3 position, int numBuildings)
{
	_position = position;
	_numBuildings = numBuildings;

	Generate();
}

void BuildingGenerator::Generate()
{
	for (int i = 0; i < 2; i++)
	{
		for (int j = 0; j < _numBuildings / 2; j++)
		{
			Transform transform;
			
			transform.rotation = vec3();
			
			double width = 32 + Random(-5.0, 25.0);
			double depth = 32 + Random(-5.0, 25.0);
			double height = 256.0 + Random(-20.0, 40.0);
	
			int numStories = 5 + Random(-2, 2);
	
			transform.scale = vec3(width, height, depth);
			transform.position = _position + vec3(32 * (i + 1) * 2, 0.0, 32 * (j + 1) * 2);
	
			_buildings.push_back(new Building(transform, numStories));
		}
	}

	//Transform transform;
	//
	//transform.rotation = vec3();
	//
	//double width = 32 + Random(-5.0, 25.0);
	//double depth = 32 + Random(-5.0, 25.0);
	//double height = 256.0 + Random(-20.0, 40.0);
	//
	//int numStories = 7 + Random(-2, 2);
	//
	//transform.scale = vec3(width, height, depth);
	//transform.position = vec3();
	//
	//_buildings.push_back(new Building(transform, numStories));
}
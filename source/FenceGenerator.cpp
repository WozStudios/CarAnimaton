#include "FenceGenerator.h"

FenceGenerator::FenceGenerator(vec3* cameraPosition, vec3* cameraDirection)
{
	GenerateFenceBoards(cameraPosition, cameraDirection);
}

void FenceGenerator::GenerateFenceBoards(vec3* cameraPosition, vec3* cameraDirection)
{
	for (int i = 0; i < 150; i++)
	{
		vec3 position = vec3(255.0f - i * 3.0f, 0.0f, -255.0f);
		_fenceBoards.push_back(new FenceBoard(position, 0.0f, cameraPosition, cameraDirection));
	}
}
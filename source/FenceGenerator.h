#ifndef FENCE_GENERATOR_H
#define FENCE_GENERATOR_H

#include <vector>
#include "FenceBoard.h"
#include "IGameObject.h"
#include "IDrawable.h"
#include "Transform.h"

using std::vector;

class FenceGenerator
{
private:

	vector<FenceBoard*> _fenceBoards;

public:
	FenceGenerator(vec3* cameraPosition, vec3* cameraDirection);

	vector<FenceBoard*> GetFenceBoards() { return _fenceBoards; }

private:
	void GenerateFenceBoards(vec3* cameraPosition, vec3* cameraDirection);
};

#endif
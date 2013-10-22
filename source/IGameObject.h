#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include "Transform.h"
#include "MatStack.h"

class IGameObject
{
public:
	virtual vec3 GetPosition() = 0;
	virtual vec3 GetRotation() = 0;
	virtual vec3 GetScale() = 0;

	virtual void SetPosition(vec3 position) = 0;
	virtual void SetRotation(vec3 rotation) = 0;
	virtual void SetScale(vec3 scale) = 0;
};

#endif
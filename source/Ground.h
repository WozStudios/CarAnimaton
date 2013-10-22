#ifndef GROUND_H
#define GROUND_H

#include "glm/glm.hpp"
#include "IGameObject.h"
#include "drawScene.h"
#include "matStack.h"
#include "IDrawable.h"
#include "Transform.h"

using glm::vec3;

class Ground : public IGameObject, public IDrawable
{
private:
	Transform _transform;
	int _size;
public:
	Ground(double size);

	vec3 GetPosition() { return _transform.position; }
	vec3 GetRotation() { return _transform.rotation; }
	vec3 GetScale() { return _transform.scale; }
	
	void SetPosition(vec3 position) { _transform.position = position; }
	void SetRotation(vec3 rotation) { _transform.rotation = rotation; }
	void SetScale(vec3 scale) { _transform.scale = scale; }

	void Draw(ModelviewStack* ms);
};

#endif
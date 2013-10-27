#ifndef STORE_H
#define STORE_H

#include "IGameObject.h"
#include "IDrawable.h"
#include "Transform.h"

class Store : public IGameObject, public IDrawable
{
private:
	Transform _transform;

public:
	Store(Transform transform);

	vec3 GetPosition() { return _transform.position; }
	vec3 GetRotation() { return _transform.rotation; }
	vec3 GetScale() { return _transform.scale; }
	
	void SetPosition(vec3 position) { _transform.position = position; }
	void SetRotation(vec3 rotation) { _transform.rotation = rotation; }
	void SetScale(vec3 scale) { _transform.scale = scale; }
	
	void Draw(ModelviewStack* ms);
};

#endif
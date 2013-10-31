#ifndef NODE_H
#define NODE_H

#include "IGameObject.h"

class Node : public IGameObject
{
private:
	Transform _transform;

public:
	Node(vec3 position) { _transform.position = position; }

	vec3 GetPosition() { return _transform.position; }
	vec3 GetRotation() { return _transform.rotation; }
	vec3 GetScale() { return _transform.scale; }

	void SetPosition(vec3 position) { _transform.position = position; }
	void SetRotation(vec3 rotation) { _transform.rotation = rotation; }
	void SetScale(vec3 scale) { _transform.scale = scale; }

};

#endif
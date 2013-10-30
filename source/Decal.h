#ifndef DECAL_H
#define DECAL_H

#include "IGameObject.h"
#include "IDrawable.h"

class Decal : public IGameObject, public IDrawable
{
private:
	Transform _transform;
	int _textureID;
	float _rotationAngle;

	vec3* _cameraPosition;
	vec3* _cameraDirection;

public:
	Decal(Transform transform, int textureID, float rotationAngle, vec3* cameraPosition, vec3* cameraDirection);

	vec3 GetPosition() { return _transform.position; }
	vec3 GetRotation() { return _transform.rotation; }
	vec3 GetScale() { return _transform.scale; }

	void SetPosition(vec3 position) { _transform.position = position; }
	void SetRotation(vec3 rotation) { _transform.rotation = rotation; }
	void SetScale(vec3 scale) { _transform.scale = scale; }

	void Draw(ModelviewStack* ms);
};

#endif
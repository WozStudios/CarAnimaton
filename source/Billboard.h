#ifndef BILLBOARD_H
#define BILLBOARD_H

#include "IGameObject.h"
#include "IDrawable.h"
#include "IUpdateable.h"

class Billboard : public IGameObject, public IDrawable, public IUpdateable
{
private:
	Transform _transform;
	vec3 _normal;
	vec3* _cameraPosition;
	vec3* _cameraDirection;

	float _distanceFromCamera;

	float _rotationAngle;

	int _textureID;

public:
	Billboard(Transform transform, vec3* cameraPosition, vec3* cameraDirection, int textureID);
	
	vec3 GetPosition() { return _transform.position; }
	vec3 GetRotation() { return _transform.rotation; }
	vec3 GetScale() { return _transform.scale; }
	
	void SetPosition(vec3 position) { _transform.position = position; }
	void SetRotation(vec3 rotation) { _transform.rotation = rotation; }
	void SetScale(vec3 scale) { _transform.scale = scale; }
	
	void Update(float deltaTime);

	void Draw(ModelviewStack* ms);

	float GetDistanceFromCamera() { return _distanceFromCamera; }

	bool operator<(const Billboard& rhs);
	static bool CompareDistance(Billboard* a, Billboard* b);
};

#endif
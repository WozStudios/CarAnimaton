#ifndef RAT_H
#define RAT_H

#include "IGameObject.h"
#include "IDrawable.h"
#include "IUpdateable.h"

class Rat : public IGameObject, public IDrawable, public IUpdateable
{
	Transform _transform;

	vec3* _cameraPosition;
	vec3* _cameraDirection;

	float _tailCounter;
	float _tailAngle;

	float _movementSpeed;
	float _pathCounter;
	float _pathWidth;
	float _rotationAngle;
	vec3 _front;
	vec3 _lastPosition;
	bool _isVisible;
	bool _isAnimating;

public:
	Rat(vec3* cameraPosition, vec3* cameraDirection);

	vec3 GetPosition() { return _transform.position; }
	vec3 GetRotation() { return _transform.rotation; }
	vec3 GetScale() { return _transform.scale; }
	
	void SetPosition(vec3 position) { _transform.position = position; }
	void SetRotation(vec3 rotation) { _transform.rotation = rotation; }
	void SetScale(vec3 scale) { _transform.scale = scale; }

	void SetAnimating(bool isAnimating) { _isAnimating = isAnimating; }
	
	void Update(float deltaTime);
	
	void Draw(ModelviewStack* ms);
};

#endif
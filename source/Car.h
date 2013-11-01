#ifndef CAR_H
#define CAR_H

#include "IGameObject.h"
#include "IDrawable.h"
#include "IUpdateable.h"
#include "Transform.h"
#include "Path.h"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>

using namespace glm;

class Car : public IGameObject, public IUpdateable, public IDrawable
{
protected:
	Transform _transform;
	vec3 _lastPosition;

	vec3 _colour;

	float _carSpeed;

	vec3 _carDirection;
	float _carAngle;
	quat _heading;
	float _rotationCounter;

	Path* _path;
	vector<vec3> _points;
	unsigned int _currentNode;
	double _currentC;

	float _tireRadius;
	float _wheelAngle;

	vec3* _cameraPosition;
	vec3* _cameraDirection;

	bool _isAnimating;

public:
	Car(Transform transform, vec3 direction, vec3 colour, vec3* cameraPosition, vec3* cameraDirection, Path* path);
	
	vec3 GetPosition() { return _transform.position; }
	vec3 GetRotation() { return _transform.rotation; }
	vec3 GetScale() { return _transform.scale; }

	vec3* GetPositionPointer() { return &_transform.position; }
	
	void SetPosition(vec3 position) { _transform.position = position; }
	void SetRotation(vec3 rotation) { _transform.rotation = rotation; }
	void SetScale(vec3 scale) { _transform.scale = scale; }

	void SetCarSpeed(float carSpeed) {_carSpeed = carSpeed; }

	bool IsAnimating() { return _isAnimating; }
	void SetAnimating(bool isAnimating) { _isAnimating = isAnimating; }
	
	void Update(float deltaTime);
	virtual void Draw(ModelviewStack* ms) = 0;
};

#endif
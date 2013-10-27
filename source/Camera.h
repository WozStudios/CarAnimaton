#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "DummyCameraTarget.h"
#include "InputManager.h"
#include "IGameObject.h""
#include "IDrawable.h"
#include "IUpdateable.h"
#include "QuaternionTest.h"

using namespace glm;

class Camera : public IGameObject
{
private:
	Transform _transform;
	//vec3* _target;
	vec3 _previousTargetPosition;
	vec3 _upVector;
	vec3 _origin;

	vec3 _direction;

	DummyCameraTarget _dummy;

	double _distance;
	double _heightSpeed;
	double _zoomSpeed;
	double _rotationSpeed;

	double _angle;

	float _counterY;
	float _counterX;
	
	bool _isRotating;

	InputManager* _inputManager;

	mat4 _orientationMat;

	quat _orientation;

public:
	Camera(double distance = 1.0);
	
	vec3 GetPosition() { return _transform.position; }
	vec3 GetRotation() { return _transform.rotation; }
	vec3 GetScale() { return _transform.scale; }
	
	void SetPosition(vec3 position) { _transform.position = position; }
	void SetRotation(vec3 rotation) { _transform.rotation = rotation; }
	void SetScale(vec3 scale) { _transform.scale = scale; }

	void Update(float deltaTime);
	void Animate(float deltaTime);
	
	vec3* GetTarget() { return _dummy.GetPositionPointer(); }
	vec3 GetUpVector() { return _upVector; }
	
	vec3* GetPositionPointer() { return &_transform.position; }
	vec3* GetDirectionPointer() { return &_direction; }
	
	//void SetPosition(vec3 position) { _position = position; }
	void SetTarget(vec3* target) { _dummy.SetPosition(target); }
	void SetUpVector(vec3 upVector) { _upVector = upVector; }

	//void SetDummyTarget(DummyCameraTarget* dummy);
};

#endif
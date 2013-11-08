#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "DummyCameraTarget.h"
#include "InputManager.h"
#include "IGameObject.h"
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
	double _idealDistance;
	double _heightSpeed;
	double _zoomSpeed;
	float _rotationSpeedX;
	float _rotationSpeedY;

	double _angle;

	float _counterY;
	float _counterX;
	float _idealCounterY;
	float _idealCounterX;
	int _leftRight;
	
	bool _isRotating;
	bool _isAnimating;

	InputManager* _inputManager;

	mat4 _orientationMat;

	bool _isFollowing;

public:
	void Init(double distance);
	void Destroy();
	
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

	vec3 GetTargetPosition() { return _dummy.GetPosition(); }
	
	//void SetPosition(vec3 position) { _position = position; }
	void SetTarget(vec3* target) { _dummy.SetPosition(target); }
	void SetUpVector(vec3 upVector) { _upVector = upVector; }

	void SetAnimating(bool isAnimating) { _isAnimating = isAnimating; _dummy.SetAnimating(isAnimating); }
	void SetAcceleration(float acceleration, float targetSpeed) {_dummy.SetAcceleration(acceleration, targetSpeed); }
	void SetDistance(float distance) { _idealDistance = distance; }

	void SetIdealCounterY(float idealCounterY, int leftRight) { _idealCounterY = idealCounterY; _leftRight = leftRight; }
	void SetIdealCounterX(float idealCounterX) { _idealCounterX = idealCounterX; }

	void SetRotationSpeedY(float rotationSpeedY) { _rotationSpeedY = rotationSpeedY; }
	void SetRotationSpeedX(float rotationSpeedX) { _rotationSpeedX = rotationSpeedX; }

	void SetFollowing(bool isFollowing) { _isFollowing = isFollowing; }

	//void SetDummyTarget(DummyCameraTarget* dummy);

	void Draw(ModelviewStack* ms);

	void ResetCounters();

private:
	void RotateToIdeals(float deltaTime);
};

#endif
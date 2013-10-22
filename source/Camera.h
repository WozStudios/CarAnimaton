#ifndef CAMERA_H
#define CAMERA_H

#include "glm/glm.hpp"
#include "IUpdateable.h"

using glm::vec3;

class Camera : public IUpdateable
{
private:
	vec3 _position;
	vec3 _target;
	vec3 _upVector;

	double _distance;
	double _heightSpeed;
	double _zoomSpeed;
	double _rotationSpeed;

	double _angle;

	bool _isRotating;

public:
	Camera(double distance = 1.0);

	void Update(float deltaTime);
	
	vec3 GetPosition() { return _position; }
	vec3 GetTarget() { return _target; }
	vec3 GetUpVector() { return _upVector; }

	vec3* GetPositionPointer() { return &_position; }
	
	vec3 SetPosition(vec3 position) { _position = position; }
	vec3 SetTarget(vec3 target) { _target = target; }
	vec3 SetUpVector(vec3 upVector) { _upVector = upVector; }
};

#endif
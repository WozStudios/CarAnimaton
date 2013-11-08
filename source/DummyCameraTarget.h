#ifndef DUMMY_CAMERA_TARGET_H
#define DUMMY_CAMERA_TARGET_H

#include "InputManager.h"
#include "IGameObject.h"
#include "IUpdateable.h"
#include "IDrawable.h"
#include "Path.h"

class DummyCameraTarget : public IGameObject, public IUpdateable, public IDrawable
{
private:
	Transform _transform;
	vec3 _cameraPosition;
	vec3* _targetPosition;

	InputManager* _inputManager;

	vec3 _movementVector;
	float _movementSpeed;
	float _acceleration;
	float _targetSpeed;

	Path _path;
	int _currentNode;
	float _currentC;

	bool _isAnimating;

public:
	void Init(vec3 position);
	void Destroy();

	vec3 GetPosition() { return _transform.position; }
	vec3 GetRotation() { return _transform.rotation; }
	vec3 GetScale() { return _transform.scale; }

	vec3 GetMovementVector() { return _movementVector; }
	vec3* GetPositionPointer() { return &_transform.position; }

	void SetPosition(vec3 position) { _transform.position = position; }
	void SetPosition(vec3* position) { _targetPosition = position; }
	void SetRotation(vec3 rotation) { _transform.rotation = rotation; }
	void SetScale(vec3 scale) { _transform.scale = scale; }

	void SetAnimating(bool isAnimating) { _isAnimating = isAnimating; }
	void SetAcceleration(float acceleration, float targetSpeed) { _acceleration = acceleration; _targetSpeed = targetSpeed; }

	void Update(float deltaTime);
	void Draw(ModelviewStack* ms);

	void SetCameraPosition(vec3 cameraPosition) { _cameraPosition = cameraPosition; }
	
private:
	void SetupPath();
};

#endif
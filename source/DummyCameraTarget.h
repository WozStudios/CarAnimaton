#ifndef DUMMY_CAMERA_TARGET_H
#define DUMMY_CAMERA_TARGET_H

#include "InputManager.h"
#include "IGameObject.h"
#include "IUpdateable.h"
#include "IDrawable.h"

class DummyCameraTarget : public IGameObject, public IUpdateable, public IDrawable
{
private:
	Transform _transform;
	vec3 _cameraPosition;
	InputManager* _inputManager;
	vec3 _movementVector;
	float _movementSpeed;

public:
	DummyCameraTarget(vec3 position = vec3());

	void Update(float deltaTime);

	void Draw(ModelviewStack* ms);
	
	vec3 GetPosition() { return _transform.position; }
	vec3 GetRotation() { return _transform.rotation; }
	vec3 GetScale() { return _transform.scale; }
	vec3 GetMovementVector() { return _movementVector; }
	vec3* GetPositionPointer() { return &_transform.position; }

	void SetPosition(vec3 position) { _transform.position = position; }
	void SetPosition(vec3* position) { _transform.position = *position; }
	void SetRotation(vec3 rotation) { _transform.rotation = rotation; }
	void SetScale(vec3 scale) { _transform.scale = scale; }

	void SetCameraPosition(vec3 cameraPosition) { _cameraPosition = cameraPosition; }
	
};

#endif
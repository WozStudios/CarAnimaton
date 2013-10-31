#include "Camera.h"
#include "drawScene.h"
#include "MathUtils.h"

Camera::Camera(double distance)
{
	_distance = distance;
	_transform.position = vec3(0.0f, 0.0f, distance);
	_origin = vec3(0.0f, 0.0f, 0.0f);
	_dummy = DummyCameraTarget(vec3(0.0f, 0.0f, 0.0f));
	//_target = _dummy.GetPositionPointer();
	_previousTargetPosition = _dummy.GetPosition();
	_upVector = vec3(0, 1, 0);
	
	_heightSpeed = 10.0;
	_zoomSpeed = 10.0;
	_rotationSpeedX = 0.5;
	_rotationSpeedY = 0.5;

	_angle = 0.0;

	_isRotating = false;

	_inputManager = InputManager::GetInstance();
	
	_counterY = 0.0f;
	_counterX = M_PI / 8.0f;
}

void Update2(float deltaTime)
{
	//if (_inputManager->IsRightClicked())
	//	_distance += deltaTime * _inputManager->GetMouseDY() * _zoomSpeed;

	double heightFactor = 1.0;
	//if (_inputManager->IsLeftClicked())
	//	_transform.position.y += deltaTime * _inputManager->GetMouseDY() * _heightSpeed;
	
	/*
	if (_inputManager->WasSpacePressed())
	{
		_inputManager->SetSpacePressed(false);
		_isRotating = !_isRotating;
	}
	
	if (_isRotating)
	{
		_angle += deltaTime;

		if (_angle > 360.0)
			_angle -=360.0;
	}
	
	_position = vec3(_distance * cos(_angle) * _rotationSpeed,
					 _position.y,
					 _distance  * sin(_angle) * _rotationSpeed);
	*/

	//vec3 movementVector = *_target - _previousTargetPosition;

	//_dummy.SetCameraPosition(_transform.position);
	//_dummy.Update(deltaTime);

	//_transform.position += _dummy.GetMovementVector();
	//_previousTargetPosition = *_target;
	//quat y1 = quat(vec3(0.0, 0.0, 0.0));
	//quat y2 = quat(vec3(0.0, M_PI / 2, 0.0));
	//
	//quat x1 = quat(vec3(-M_PI, 0.0, 0.0));
	//quat x2 = quat(vec3(M_PI, 0.0, 0.0));
	//
	//InputManager* inputManager = InputManager::GetInstance();
	//
	//if (inputManager->IsLeftClicked())
	//{		
	//	_counterY += inputManager->GetMouseDX() * deltaTime * 0.01;
	//	if (_counterY > 2.0)
	//		_counterY -= 2.0;
	//	if (_counterY < 0.0)
	//		_counterY += 2.0;
	//
	//	//std::cout << "_counterY: " << _counterY << "\n";
	//	
	//	_counterX += inputManager->GetMouseDY() * deltaTime * 0.001;
	//	if (_counterX > 0.5)
	//		_counterX = 0.5;
	//	if (_counterX < -0.5)
	//		_counterX = -0.5;
	//	
	//	std::cout << "_counterX: " << _counterX << "\n";
	//
	//	//quat orientation = mix(y1, y2, _counterY); // * mix(x1, x2, _counterX);
	//	quat orientation = mix(x1, x2, _counterX);
	//
	//	/*
	//	_orientationMat = mat4_cast(orientation);
	//
	//	vec4 position = (_orientationMat * vec4(_transform.position.x,
	//											_transform.position.y,
	//											_transform.position.z, 1.0));
	//	_transform.position.x = position.x;
	//	_transform.position.y = position.y;
	//	_transform.position.z = position.z;
	//	*/
	//
	//	ModelviewStack ms(10);
	//	
	//	ms.LoadIdentity();
	//
	//	ms.Push();
	//		ms.Mult(mat4_cast(orientation));
	//		ms.Translate(_distance);
	//		
	//		vec4 position = (ms.Top() * vec4(0.0, 0.0, 0.0, 1.0));
	//		/*
	//		_transform.position.x = position.x;
	//		_transform.position.y = position.y;
	//		_transform.position.z = position.z;*/
	//
	//		_transform.position = vec3(position.x,
	//								   position.y,
	//								   position.z);
	//
	//	ms.Pop();
	//}
}						   

void Camera::Animate(float deltaTime)
{
	_counterY += deltaTime * 1.0f;
		if (_counterY > 2.0 * M_PI)
			_counterY -= 2.0 * M_PI;
		if (_counterY < 0.0)
			_counterY += 2.0 * M_PI;
}

void Camera::Update(float deltaTime)
{
	_dummy.SetCameraPosition(_transform.position);
	_dummy.Update(deltaTime);

	vec3 target = _dummy.GetPosition();
	vec3 movementVector = target - _previousTargetPosition;

	//_transform.position += _dummy.GetMovementVector();
	_previousTargetPosition = target;

	_transform.position = _dummy.GetPosition();
	
	//Animate(deltaTime);

	if (_inputManager->IsLeftClicked())
	{
		_counterY += _inputManager->GetMouseDX() * deltaTime * 2.0;
		if (_counterY > 2.0 * M_PI)
			_counterY -= 2.0 * M_PI;
		if (_counterY < 0.0)
			_counterY += 2.0 * M_PI;
		
		//std::cout << "_counterY: " << _counterY << "\n";
		
		_counterX -= _inputManager->GetMouseDY() * deltaTime * 2.0;
		if (_counterX > M_PI / 2)
			_counterX = M_PI / 2;
		if (_counterX < -M_PI / 2)
			_counterX = -M_PI / 2;
	}

	double scroll = _inputManager->GetMouseScroll();

	if (scroll > 0.0)
		_distance = _inputManager->GetMouseScroll() + 5.0f;

	_transform.position.x += cos(_counterY) * cos(_counterX) * _distance * _rotationSpeedX;
	_transform.position.y += sin(_counterX) * _distance * _rotationSpeedY;
	_transform.position.z += sin(_counterY) * cos(_counterX) * _distance * _rotationSpeedX;

	// Keep camera from colliding with ground
	if (_transform.position.y < 0)
		_transform.position.y = 0;

	if (_inputManager->IsRightClicked())
	{
		std::cout << "Camera Position: (" << _transform.position.x << ", "
										  << _transform.position.y << ", "
										  << _transform.position.z << ")\n";
	}
	
	_direction = glm::normalize(_dummy.GetPosition() - _transform.position);
}
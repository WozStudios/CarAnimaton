#include "QuaternionTest.h"
#include "drawScene.h"
#include "MathUtils.h"
#include "InputManager.h"

QuaternionTest::QuaternionTest()
{
	_transform = Transform();
	_transform.position = vec3(0.0, 0.0, -2.0);
	
	_counterY = 0.0f;
	_counterX = 0.0f;
}


void QuaternionTest::Update(float deltaTime)
{
	quat y1 = quat(vec3(0.0, 0.0, 0.0));
	quat y2 = quat(vec3(0.0, M_PI, 0.0));

	quat x1 = quat(vec3(-M_PI, 0.0, 0.0));
	quat x2 = quat(vec3(0.0, 0.0, 0.0));

	InputManager* inputManager = InputManager::GetInstance();
	
	if (inputManager->IsLeftClicked())
	{		
		_counterY += inputManager->GetMouseDX() * deltaTime;
		if (_counterY > 2.0)
			_counterY -= 2.0;
		if (_counterY < 0.0)
			_counterY += 2.0;

		//std::cout << "_counterY: " << _counterY << "\n";
		
		_counterX += inputManager->GetMouseDY() * deltaTime * 0.1;
		if (_counterX > 0.5)
			_counterX = 0.5;
		if (_counterX < -0.5)
			_counterX = -0.5;

		//_orientation = mix(y1, y2, _counterY) * mix(x1, x2, _counterX);
	}
}

void QuaternionTest::Draw(ModelviewStack* ms)
{
	useTexture(0);
	setColour(1.0, 1.0, 1.0);

	ms->Push();
	{
		ms->Mult(mat4_cast(_orientation));
		ms->Translate(_transform.position);

		vec4 pos4 = mat4_cast(_orientation) * vec4(1.0, 1.0, 1.0, 1.0);
		
		drawCube(*ms);
	}
	ms->Pop();

	setColour(0.0, 0.0, 0.0);
	ms->Push();
	{
		ms->Scale(vec3(0.25f, 0.25f, 0.25f));
		drawSphere(*ms);
	}
	ms->Pop();
}
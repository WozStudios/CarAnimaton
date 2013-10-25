#ifndef QUATERNION_TEST
#define QUATERNION_TEST

#include <glm/gtc/quaternion.hpp>
#include <glm/gtx/quaternion.hpp>
#include "IGameObject.h"
#include "IDrawable.h"
#include "IUpdateable.h"

using namespace glm;

class QuaternionTest : public IGameObject, public IDrawable, public IUpdateable
{
private:
	Transform _transform;
	quat _orientation;
	
	float _counterY;
	float _counterX;

public:
	QuaternionTest();

	vec3 GetPosition() { return _transform.position; }
	vec3 GetRotation() { return _transform.rotation; }
	vec3 GetScale() { return _transform.scale; }
	
	void SetPosition(vec3 position) { _transform.position = position; }
	void SetRotation(vec3 rotation) { _transform.rotation = rotation; }
	void SetScale(vec3 scale) { _transform.scale = scale; }
	
	void Update(float deltaTime);

	void Draw(ModelviewStack* ms);

};

#endif
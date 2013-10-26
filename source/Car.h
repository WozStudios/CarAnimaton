#ifndef CAR_H
#define CAR_H

#include "IGameObject.h"
#include "IDrawable.h"
#include "IUpdateable.h"
#include "Transform.h"

class Car : public IGameObject, public IUpdateable, public IDrawable
{
private:
	Transform _transform;

	float _tireRadius;

public:
	Car();
	
	vec3 GetPosition() { return _transform.position; }
	vec3 GetRotation() { return _transform.rotation; }
	vec3 GetScale() { return _transform.scale; }
	
	void SetPosition(vec3 position) { _transform.position = position; }
	void SetRotation(vec3 rotation) { _transform.rotation = rotation; }
	void SetScale(vec3 scale) { _transform.scale = scale; }
	
	void Update(float deltaTime);
	void Draw(ModelviewStack* ms);

private:
	void DrawWheel(ModelviewStack* ms, int frontBack, int rightLeft);
};

#endif
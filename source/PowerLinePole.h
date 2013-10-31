#ifndef POWER_LINE_POLE_H
#define POWER_LINE_POLE_H

#include "IGameObject.h"
#include "IDrawable.h"

class PowerLinePole : public IGameObject, public IDrawable
{
private:
	Transform _transform;

	vec3* _cameraPosition;
	vec3* _cameraDirection;

public:
	PowerLinePole(vec3 position, vec3* cameraPosition, vec3* cameraDirection);

	vec3 GetPosition() { return _transform.position; }
	vec3 GetRotation() { return _transform.rotation; }
	vec3 GetScale() { return _transform.scale; }

	void SetPosition(vec3 position) { _transform.position = position; }
	void SetRotation(vec3 rotation) { _transform.rotation = rotation; }
	void SetScale(vec3 scale) { _transform.scale = scale; }

	void Draw(ModelviewStack* ms);
};

#endif
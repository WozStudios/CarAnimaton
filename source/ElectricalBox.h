#ifndef ELECTRICAL_BOX_H
#define ELECTRICAL_BOX_H

#include "IGameObject.h"
#include "IDrawable.h"

class ElectricalBox : public IGameObject, public IDrawable
{
private:
	Transform _transform;

	vec3* _cameraPosition;
	vec3* _cameraDirection;

public:
	ElectricalBox(vec3* cameraPosition, vec3* cameraDirection);

	vec3 GetPosition() { return _transform.position; }
	vec3 GetRotation() { return _transform.rotation; }
	vec3 GetScale() { return _transform.scale; }

	void SetPosition(vec3 position) { _transform.position = position; }
	void SetRotation(vec3 rotation) { _transform.rotation = rotation; }
	void SetScale(vec3 scale) { _transform.scale = scale; }

	void Update(float deltaTime);

	void Draw(ModelviewStack* ms);

private:
	void DrawPole(ModelviewStack* ms);
};

#endif
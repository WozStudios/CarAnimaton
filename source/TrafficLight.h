#ifndef TRAFFIC_LIGHT_H
#define TRAFFIC_LIGHT_H

#include "IGameObject.h"
#include "IDrawable.h"
#include "Transform.h"

class TrafficLight : public IGameObject, public IDrawable
{
private:
	Transform _transform;
	int _lightNumber;

public:
	TrafficLight(int lightNumber);
	
	vec3 GetPosition() { return _transform.position; }
	vec3 GetRotation() { return _transform.rotation; }
	vec3 GetScale() { return _transform.scale; }
	
	void SetPosition(vec3 position) { _transform.position = position; }
	void SetRotation(vec3 rotation) { _transform.rotation = rotation; }
	void SetScale(vec3 scale) { _transform.scale = scale; }
	
	void Draw(ModelviewStack* ms);

private:
	void DrawPost(ModelviewStack* ms);
	void DrawJoint(ModelviewStack* ms);
	void DrawLights(ModelviewStack* ms);
	void DrawLight(ModelviewStack* ms, float height, vec3 colour);
};

#endif
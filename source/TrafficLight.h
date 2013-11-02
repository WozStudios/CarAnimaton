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
	
	vec3* _cameraPosition;
	vec3* _cameraDirection;

	bool _isGreen;
	bool _isRed;

public:
	TrafficLight(int lightNumber, vec3* cameraPosition, vec3* cameraDirection, bool isGreen);
	
	vec3 GetPosition() { return _transform.position; }
	vec3 GetRotation() { return _transform.rotation; }
	vec3 GetScale() { return _transform.scale; }
	
	void SetPosition(vec3 position) { _transform.position = position; }
	void SetRotation(vec3 rotation) { _transform.rotation = rotation; }
	void SetScale(vec3 scale) { _transform.scale = scale; }
	
	void Draw(ModelviewStack* ms);

	void SetRed(bool isRed) { _isRed = isRed; }
	void SetGreen(bool isGreen) { _isGreen = isGreen; }

private:
	void DrawPost(ModelviewStack* ms);
	void DrawJoint(ModelviewStack* ms);
	void DrawLights(ModelviewStack* ms);
	void DrawLight(ModelviewStack* ms, float height, vec3 colour);
};

#endif
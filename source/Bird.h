#ifndef BIRD_H
#define BIRD_H

#include "IGameObject.h"
#include "IUpdateable.h"
#include "IDrawable.h"

class Bird : public IGameObject, public IUpdateable, public IDrawable
{
private:
	Transform _transform;

	float _wingAngle;
	float _wingCounter;
	float _wingFlapSpeed;
	float _flightSpeed;
	float _pathCounter;
	float _rotationAngle;
	vec3 _front;
	vec3 _lastPosition;

public:
	Bird(Transform transform, float flightSpeed, int pathFunction);
	
	vec3 GetPosition() { return _transform.position; }
	vec3 GetRotation() { return _transform.rotation; }
	vec3 GetScale() { return _transform.scale; }
	
	void SetPosition(vec3 position) { _transform.position = position; }
	void SetRotation(vec3 rotation) { _transform.rotation = rotation; }
	void SetScale(vec3 scale) { _transform.scale = scale; }
	
	void Update(float deltaTime);
	void Draw(ModelviewStack* ms);

private:
	void DrawWing(ModelviewStack* ms, int rightLeft);

	void SetPathFunction(int pathFunction);
	void (*PathFunction)(float &x, float &y, float t, float width, float height);
};

#endif
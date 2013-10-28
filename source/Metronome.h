#ifndef METRONOME_H
#define METRONOME_H

#include "IGameObject.h"
#include "IDrawable.h"
#include "IUpdateable.h"

class Metronome : public IGameObject, public IDrawable, public IUpdateable
{
private:
	Transform _transform;
	float _counter;
	float _rotationAngle;

public:
	Metronome();
	
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
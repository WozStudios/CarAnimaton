#ifndef SKYBOX_H
#define SKYBOX_H

#include "IGameObject.h"
#include "IDrawable.h"
#include "IUpdateable.h"
#include "matStack.h"

class Skybox : public IGameObject, public IDrawable, public IUpdateable
{
private:
	Transform _transform;
	double _size;
	vec3* _cameraPosition;
	float _rotationAngle;
	float _rotationSpeed;

public:
	Skybox(double size = 64.0, vec3* cameraPos = NULL);

	vec3 GetPosition() { return _transform.position; }
	vec3 GetRotation() { return _transform.rotation; }
	vec3 GetScale() { return _transform.scale; }
	
	void SetPosition(vec3 position) { _transform.position = position; }
	void SetRotation(vec3 rotation) { _transform.rotation = rotation; }
	void SetScale(vec3 scale) { _transform.scale = scale; }
	
	void Draw(ModelviewStack* ms);

	void Update(float deltaTime);

private:
	void DrawWalls(ModelviewStack* ms);
	void Skybox::DrawWall(ModelviewStack* ms, vec3 translation, vec3 rotationAxis, double rotation);
};

#endif
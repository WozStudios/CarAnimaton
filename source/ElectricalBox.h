#ifndef ELECTRICAL_BOX_H
#define ELECTRICAL_BOX_H

#include <list>
#include "IGameObject.h"
#include "IDrawable.h"
#include "IUpdateable.h"
#include "Spark.h"

using std::list;

class ElectricalBox : public IGameObject, public IDrawable, public IUpdateable
{
private:
	Transform _transform;

	vec3* _cameraPosition;
	vec3* _cameraDirection;

	vec3 _colour;

	list<Spark*> _sparks;

	bool _exploded;

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

	void Explode();

private:
	void GenerateSparks();
	void DrawSparks(ModelviewStack* ms);

};

#endif
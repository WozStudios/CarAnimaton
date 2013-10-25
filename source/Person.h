#ifndef PERSON_H
#define PERSON_H

#include "IGameObject.h"
#include "IDrawable.h"
#include "IUpdateable.h"

class Person : public IGameObject, public IDrawable, public IUpdateable
{
private:
	Transform _transform;
	
	double _bodyHeight;
	double _bodyWidth;
	double _bodyDepth;
	double _thighHeight;
	double _thighWidth;
	double _calfHeight;
	double _calfWidth;
	double _footHeight;
	double _footWidth;
	double _neckHeight;
	double _neckWidth;
	double _headHeight;
	double _headWidth;
	double _upperArmHeight;
	double _upperArmWidth;
	double _foreArmHeight;
	double _foreArmWidth;

	double _totalBodyHeight;
	double  _totalLegHeight;

	double  _size;

public:
	Person();

	vec3 GetPosition() { return _transform.position; }
	vec3 GetRotation() { return _transform.rotation; }
	vec3 GetScale() { return _transform.scale; }
	
	void SetPosition(vec3 position) { _transform.position = position; }
	void SetRotation(vec3 rotation) { _transform.rotation = rotation; }
	void SetScale(vec3 scale) { _transform.scale = scale; }
	
	void Update(float deltaTime);

	void Draw(ModelviewStack* ms);

private:
	void DrawBody(ModelviewStack* ms);
	void DrawNeck(ModelviewStack* ms);
	void DrawHead(ModelviewStack* ms);
	void DrawArms(ModelviewStack* ms);
	void DrawLegs(ModelviewStack* ms);
};

#endif
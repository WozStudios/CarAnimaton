#include "Person.h"
#include "drawScene.h"

Person::Person()
{
	_transform.position = vec3(0.0, 4.0, 0.0);
	_transform.rotation = vec3(0.0, 0.0, 0.0);
	_transform.scale = vec3(0.0, 0.0, 0.0);
	
	_size = 1.0;

	_totalBodyHeight = 8.0 * _size;
	_bodyHeight = _totalBodyHeight * 0.77;
	_bodyWidth = _bodyHeight * 0.4;
	_bodyDepth = _bodyWidth * 0.3;
	_thighHeight = 0;
	_thighWidth;
	_calfHeight = 0;
	_calfWidth;
	_footHeight = 0;
	_footWidth;
	_neckHeight;
	_neckWidth;
	_headHeight;
	_headWidth;

	_totalLegHeight = _footHeight + _calfHeight + _thighHeight;
}

void Person::Update(float deltaTime)
{

}

void Person::Draw(ModelviewStack* ms)
{
	useLighting(1);

	setColour(1.0, 0.0, 0.0);
	ms->Push();
	{
		ms->Translate(_transform.position);
		
		DrawBody(ms);
		//DrawNeck(ms);
		DrawHead(ms);
		DrawArms(ms);
		DrawLegs(ms);
	}
	ms->Pop();
}

void Person::DrawBody(ModelviewStack* ms)
{
	ms->Push();
	{
		double posX = _bodyHeight / 2 + _totalLegHeight;
		ms->Translate(vec3(0.0, _totalLegHeight, 0.0));

		double scaleX = (_transform.position.y / _bodyHeight + 1.5) * _bodyWidth;
		ms->Scale(vec3(_bodyWidth, _bodyHeight / 2.0, _bodyDepth));
		ms->Translate(vec3(0.0, 1.0, 0.0));
		
		drawCube(*ms);
	}
	ms->Pop();
}

void Person::DrawNeck(ModelviewStack* ms)
{
	ms->Push();
	{
		ms->Translate(vec3(0.0, 10, 0.0));
		ms->Scale(vec3(0.8, 0.5, 0.8));
		drawCube(*ms);
	}
	ms->Pop();
}

void Person::DrawHead(ModelviewStack* ms)
{

}

void Person::DrawArms(ModelviewStack* ms)
{

}

void Person::DrawLegs(ModelviewStack* ms)	
{

}

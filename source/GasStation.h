#ifndef GAS_STATION_H
#define GAS_STATION_H

#include "IGameObject.h"
#include "IDrawable.h"
#include "Transform.h"

class GasStation : public IGameObject, public IDrawable
{
private:
	Transform _transform;

public:
	GasStation();

	vec3 GetPosition() { return _transform.position; }
	vec3 GetRotation() { return _transform.rotation; }
	vec3 GetScale() { return _transform.scale; }
	
	void SetPosition(vec3 position) { _transform.position = position; }
	void SetRotation(vec3 rotation) { _transform.rotation = rotation; }
	void SetScale(vec3 scale) { _transform.scale = scale; }
	
	void Draw(ModelviewStack* ms);

private:
	void GasStation::DrawTrim(ModelviewStack* ms);
	void GasStation::DrawPosts(ModelviewStack* ms);
	void GasStation::DrawGasPumps(ModelviewStack* ms);
	void GasStation::DrawGasPump(ModelviewStack* ms, float position);
	void GasStation::DrawDoors(ModelviewStack* ms);
};

#endif
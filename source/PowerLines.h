#ifndef POWER_LINES_H
#define POWER_LINES_H

#include "PowerLinePole.h"
#include <vector>
#include "IGameObject.h"
#include "IDrawable.h"

using std::vector;

class PowerLines : public IGameObject, public IDrawable
{
private:
	Transform _transform;

	vec3* _cameraPosition;
	vec3* _cameraDirection;

	vector<PowerLinePole*> _poles;

public:
	PowerLines(vec3* cameraPosition, vec3* cameraDirection);
	~PowerLines();

	vec3 GetPosition() { return _transform.position; }
	vec3 GetRotation() { return _transform.rotation; }
	vec3 GetScale() { return _transform.scale; }

	void SetPosition(vec3 position) { _transform.position = position; }
	void SetRotation(vec3 rotation) { _transform.rotation = rotation; }
	void SetScale(vec3 scale) { _transform.scale = scale; }

	void Draw(ModelviewStack* ms);
	void Destroy();

private:
	void SetupPoles();
	void DrawLine(ModelviewStack* ms, vec3 position);
};

#endif
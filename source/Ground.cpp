#include "Ground.h"

Ground::Ground(double size)
{
	_size = size;

	_transform.position = vec3(0.0, -1.0, 0.0);
	_transform.rotation = vec3(0.0, 0.0, 0.0);
	_transform.scale = vec3(_size / 2, 1.0, _size / 2);
}

void Ground::Draw(ModelviewStack* ms)
{
	useTexture(7);
	useLighting(1);
	setColour(1.0, 1.0, 1.0);

	ms->Push();
	{
		ms->Translate(_transform.position);
		ms->Scale(_transform.scale);
		drawCube(*ms);
	}
	ms->Pop();
}
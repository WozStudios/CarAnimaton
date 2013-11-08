#include "DecalGenerator.h"
#include "Textures.h"
#include "Debug.h"

DecalGenerator::DecalGenerator(vec3* cameraPosition, vec3* cameraDirection)
{
	_cameraPosition =  cameraPosition;
	_cameraDirection =  cameraDirection;

	Generate();
}

void DecalGenerator::Generate()
{
	Transform transform;

	// Hours sign
	transform.position = vec3(55.5f, 20.0f, -90.0f);
	transform.rotation = vec3(0.0f, 1.0f, 0.0f);
	transform.scale = vec3(8.0f, 16.0f, 1.0f);
	_decals.push_back(new Decal(transform, HOURS_SIGN_TEXTURE, -90.0f, _cameraPosition, _cameraDirection));
}
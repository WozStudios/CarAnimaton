#include "BirdGenerator.h"
#include "MathUtils.h"
#include "Random.h"

#include "Debug.h"

void BirdGenerator::Init(vec3 position, vec3* cameraPosition, vec3* cameraDirection)
{
	_position = position;
	_cameraPosition = cameraPosition;
	_cameraDirection = cameraDirection;

	Generate();
}

void BirdGenerator::Generate()
{
	_birds.push_back(Bird(GenerateTransform(), 0.5f, 1, 128.0f, _cameraPosition, _cameraDirection));
	_birds.push_back(Bird(GenerateTransform(), -0.5f, 1, 128.0f, _cameraPosition, _cameraDirection));
	_birds.push_back(Bird(GenerateTransform(), -0.05f, 2, 128.0f, _cameraPosition, _cameraDirection));
	_birds.push_back(Bird(GenerateTransform(), 0.08f, 2, 128.0f, _cameraPosition, _cameraDirection));
	_birds.push_back(Bird(GenerateTransform(), 0.18f, 3, 128.0f, _cameraPosition, _cameraDirection));
	_birds.push_back(Bird(GenerateTransform(), -0.23f, 3, 128.0f, _cameraPosition, _cameraDirection));

	_birds.push_back(Bird(GenerateTransform(), 0.25f, 1, 256.0f, _cameraPosition, _cameraDirection));
	_birds.push_back(Bird(GenerateTransform(), -0.25f, 1, 256.0f, _cameraPosition, _cameraDirection));
	_birds.push_back(Bird(GenerateTransform(), 0.04f, 2, 256.0f, _cameraPosition, _cameraDirection));
	_birds.push_back(Bird(GenerateTransform(), 0.03f, 2, 256.0f, _cameraPosition, _cameraDirection));
	_birds.push_back(Bird(GenerateTransform(), 0.09f, 3, 256.0f, _cameraPosition, _cameraDirection));
	_birds.push_back(Bird(GenerateTransform(), -0.05f, 3, 256.0f, _cameraPosition, _cameraDirection));
}

Transform BirdGenerator::GenerateTransform()
{
	Transform transform;
	transform.position = _position;
	transform.position.y += Random(-32.0f, 32.0f);
	transform.scale = vec3(Random(0.9f, 1.1f), Random(0.9f, 1.1f), Random(3.6f, 4.4f));
	
	return transform;
}

void BirdGenerator::Destroy()
{
	//for (vector<Bird*>::iterator i = _birds.begin(); i != _birds.end(); i++)
	//{
	//	delete *i;
	//}
}
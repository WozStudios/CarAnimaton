#include "Scene.h"
#include "Camera.h"
#include "DummyCameraTarget.h"
#include "Ground.h"
#include "Skybox.h"
#include "Person.h"
#include "Billboard.h"
#include "ForestGenerator.h"
#include "BuildingGenerator.h"
#include "Building.h"
#include "QuaternionTest.h"
#include "IDrawable.h"
#include "IUpdateable.h"

Scene::Scene()
{
	_camera = Camera(8);
}
Scene::~Scene()
{
	for (vector<IGameObject*>::iterator i = _gameObjects.begin(); i != _gameObjects.end(); i++)
	{
		delete *i;
	}
}

void Scene::Init()
{
	vec3* cameraPosition = _camera.GetPositionPointer();

	_gameObjects.push_back(new Skybox(2048.0, cameraPosition));
	_gameObjects.push_back(new Ground(1024.0));
	//_gameObjects.push_back(new Person());
	_gameObjects.push_back(new QuaternionTest());

	ForestGenerator forestGenerator = ForestGenerator(vec3(0.0, 0.0, -256.0), cameraPosition, 64);
	vector<Billboard*> trees = forestGenerator.GetTrees();
	for (vector<Billboard*>::iterator i = trees.begin(); i != trees.end(); i++)
	{
		_gameObjects.push_back(*i);
	}


	//BuildingGenerator buildingGenerator = BuildingGenerator(vec3(256, 0, -400), 32);
	//vector<Building*> buildings = buildingGenerator.GetBuildings();
	//for (vector<Building*>::iterator i = buildings.begin(); i != buildings.end(); i++)
	//{
	//	_gameObjects.push_back(*i);
	//}
}

void Scene::Update(float deltaTime)
{
	_camera.Update(deltaTime);

	for (vector<IGameObject*>::iterator i = _gameObjects.begin(); i != _gameObjects.end(); i++)
	{
		if (IUpdateable* updateable = dynamic_cast<IUpdateable*>(*i))
			updateable->Update(deltaTime);
	}
}
void drawTestBox(ModelviewStack* ms, double x, double scale)
{
	setColour(1.0, 0.0, 0.0);

	ms->Push();
	{
		ms->Translate(vec3(x, 1.0 * scale, 0.0));
		ms->Scale(vec3(scale, scale, scale));
		drawCube(*ms);
	}
	ms->Pop();
}

void Scene::Draw(ModelviewStack* ms)
{
    ms->SetViewMatrix(_camera.GetPosition(), *_camera.GetTarget(), _camera.GetUpVector());

	for (vector<IGameObject*>::iterator i = _gameObjects.begin(); i != _gameObjects.end(); i++)
	{
		if (IDrawable* drawable = dynamic_cast<IDrawable*>(*i))
			drawable->Draw(ms);
	}
	
	//drawTestBox(ms, 0.0, 1.0);
	//drawTestBox(ms, 3.0, 0.5);
}
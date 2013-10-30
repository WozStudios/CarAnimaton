#include "Scene.h"
#include "IDrawable.h"
#include "IUpdateable.h"
#include "Camera.h"
#include "DummyCameraTarget.h"
#include "Ground.h"
#include "Skybox.h"
#include "Person.h"
#include "Billboard.h"
#include "TrafficLight.h"
#include "Car.h"
#include "Bird.h"
#include "BirdGenerator.h"
#include "Store.h"
#include "GasStation.h"
#include "Metronome.h"
#include "Bicycle.h"
#include "ForestGenerator.h"
#include "BuildingGenerator.h"
#include "Building.h"
#include "QuaternionTest.h"
#include "ElectricalBox.h"
#include "Decal.h"
#include "DecalGenerator.h"

Scene::Scene()
{
	_camera = Camera(16);
	//_soundtrack = new sf::Music();
	//_soundtrack->openFromFile("../media/audio/Soundtrack.ogg");
}
Scene::~Scene()
{
	for (vector<IGameObject*>::iterator i = _gameObjects.begin(); i != _gameObjects.end(); i++)
	{
		delete *i;
	}

	//delete _soundtrack;
}

void Scene::Init()
{
	vec3* cameraPosition = _camera.GetPositionPointer();
	vec3* cameraDirection = _camera.GetDirectionPointer();

	_gameObjects.push_back(new Skybox(2048.0, cameraPosition));
	_gameObjects.push_back(new Ground(512.0));
	//_gameObjects.push_back(new Person());
	//_gameObjects.push_back(new QuaternionTest());
	_gameObjects.push_back(new TrafficLight(0, cameraPosition, cameraDirection));
	//_gameObjects.push_back(new TrafficLight(1, cameraPosition, cameraDirection));
	_gameObjects.push_back(new TrafficLight(2, cameraPosition, cameraDirection));
	_gameObjects.push_back(new TrafficLight(3, cameraPosition, cameraDirection));
	Car* car = new Car(cameraPosition, cameraDirection);
	//_camera.SetTarget(car->GetPositionPointer());
	_gameObjects.push_back(car);
	_gameObjects.push_back(new Store());
	_gameObjects.push_back(new GasStation());
	//_gameObjects.push_back(new Metronome());
	_gameObjects.push_back(new Bicycle(cameraPosition, cameraDirection));
	//_gameObjects.push_back(new ElectricalBox(cameraPosition, cameraDirection));

	DecalGenerator decalGenerator = DecalGenerator(cameraPosition, cameraDirection);
	vector<Decal*> decals = decalGenerator.GetDecals();
	for (vector<Decal*>::iterator i = decals.begin(); i != decals.end(); i++)
	{
		_gameObjects.push_back(*i);
	}

	BirdGenerator birdGenerator = BirdGenerator(vec3(0.0f, 128.0f, 0.0f), cameraPosition, cameraDirection);
	vector<Bird*> birds = birdGenerator.GetBirds();
	for (vector<Bird*>::iterator i = birds.begin(); i != birds.end(); i++)
	{
		_gameObjects.push_back(*i);
	}

	//ForestGenerator forestGenerator = ForestGenerator(vec3(0.0, 0.0, -256.0), cameraPosition, 64);
	//vector<Billboard*> trees = forestGenerator.GetTrees();
	//for (vector<Billboard*>::iterator i = trees.begin(); i != trees.end(); i++)
	//{
	//	_gameObjects.push_back(*i);
	//}


	//BuildingGenerator buildingGenerator = BuildingGenerator(vec3(256, 0, -400), 32);
	//vector<Building*> buildings = buildingGenerator.GetBuildings();
	//for (vector<Building*>::iterator i = buildings.begin(); i != buildings.end(); i++)
	//{
	//	_gameObjects.push_back(*i);
	//}

	//_soundtrack->play();
}

void Scene::Update(float deltaTime)
{
	for (vector<IGameObject*>::iterator i = _gameObjects.begin(); i != _gameObjects.end(); i++)
	{
		if (IUpdateable* updateable = dynamic_cast<IUpdateable*>(*i))
			updateable->Update(deltaTime);
	}

	_camera.Update(deltaTime);
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
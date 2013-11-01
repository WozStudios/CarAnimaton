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
#include "PowerLines.h"
#include "ElectricalBox.h"
#include "Decal.h"
#include "DecalGenerator.h"
#include "Path.h"
#include "Node.h"

Scene::Scene()
{
	_camera = Camera(32);
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
	//_frameBuffer.Init(gWidth, gHeight);

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

	SetupCarPaths();

	Transform transform;
	transform.position = vec3(-109.0f, 0.0f, -95.0f);
	transform.rotation = vec3(0.0f, 1.0f, 0.0f);
	transform.scale = vec3(8.0f, 4.0f, 20.0f);
	SmallCar* smallCar = new SmallCar(transform, vec3(0.0f, 0.0f, -1.0f), vec3(0.25f, 0.4f, 0.3f), cameraPosition, cameraDirection, &_firstCarPath);
	//_camera.SetTarget(car->GetPositionPointer());

	transform.position = vec3(220.0f, 0.0f, -14.0f);
	transform.rotation = vec3(0.0f, 1.0f, 0.0f);
	transform.scale = vec3(5.0f, 4.0f, 12.0f);
	SportsCar* sportsCar = new SportsCar(transform, vec3(-1.0f, 0.0f, 0.0f), vec3(0.6f, 0.15f, 0.1f), cameraPosition, cameraDirection, &_secondCarPath);

	_gameObjects.push_back(smallCar);
	_gameObjects.push_back(sportsCar);
	_gameObjects.push_back(new Store());
	_gameObjects.push_back(new GasStation());
	//_gameObjects.push_back(new Metronome());
	_gameObjects.push_back(new Bicycle(cameraPosition, cameraDirection));
	_gameObjects.push_back(new PowerLines(cameraPosition, cameraDirection));
	_gameObjects.push_back(new ElectricalBox(cameraPosition, cameraDirection));

	_animationManager.Init(&_camera, smallCar, sportsCar);

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

void Scene::SetupCarPaths()
{
	_firstCarPath.AddNode(new Node(vec3(-109.0f, 0.0f, -60.0f)));
	_firstCarPath.AddNode(new Node(vec3(-109.0f, 0.0f, -95.0f)));
	_firstCarPath.AddNode(new Node(vec3(-115.0f, 0.0f, -160.0f)));
	_firstCarPath.AddNode(new Node(vec3(-82.0f, 0.0f, -210.0f)));
	_firstCarPath.AddNode(new Node(vec3(-22.0f, 0.0f, -168.0f)));
	_firstCarPath.AddNode(new Node(vec3(-8.0f, 0.0f, -10.0f)));
	_firstCarPath.AddNode(new Node(vec3(90.0f, 0.0f, 16.0f)));
	_firstCarPath.AddNode(new Node(vec3(150.0f, 0.0f, 16.0f)));
	_firstCarPath.CalculatePath();

	_secondCarPath.AddNode(new Node(vec3(210.0f, 0.0f, -14.0f)));
	_secondCarPath.AddNode(new Node(vec3(220.0f, 0.0f, -14.0f)));
	_secondCarPath.AddNode(new Node(vec3(100.0f, 0.0f, -14.0f)));
	_secondCarPath.AddNode(new Node(vec3(-14.0f, 0.0f, -14.0f)));
	_secondCarPath.AddNode(new Node(vec3(-20.0f, 0.0f, -30.0f)));
	_secondCarPath.AddNode(new Node(vec3(-25.0f, 0.0f, -40.0f)));
	_secondCarPath.CalculatePath();
}

void Scene::Update(float deltaTime)
{
	_animationManager.Update(deltaTime);

	for (vector<IGameObject*>::iterator i = _gameObjects.begin(); i != _gameObjects.end(); i++)
	{
		if (IUpdateable* updateable = dynamic_cast<IUpdateable*>(*i))
			updateable->Update(deltaTime);
	}

	_camera.Update(deltaTime);
}

void Scene::Draw(ModelviewStack* ms)
{
	//FrameBuffer::UseFrameBuffer(_frameBuffer.GetId());
	//gShaders.use(0);
	//
	//glEnable(GL_DEPTH_TEST);

    ms->SetViewMatrix(_camera.GetPosition(), *_camera.GetTarget(), _camera.GetUpVector());

	for (vector<IGameObject*>::iterator i = _gameObjects.begin(); i != _gameObjects.end(); i++)
	{
		if (IDrawable* drawable = dynamic_cast<IDrawable*>(*i))
			drawable->Draw(ms);
	}

	//FrameBuffer::UseFrameBuffer(0);
	//gShaders.use(1);
	//_frameBuffer.Draw();

}
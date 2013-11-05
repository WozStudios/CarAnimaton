#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include "Camera.h"
#include "Path.h"
#include "IGameObject.h"
#include "FrameBuffer.h"
#include "Billboard.h"
#include "AnimationManager.h"
#include "MatStack.h"
#include "SFML/Audio.hpp"

using std::vector;

class Scene
{
private:
	Camera _camera;
	Path _firstCarPath;
	Path _secondCarPath;
	vector<IGameObject*> _gameObjects;
	vector<Billboard*> _trees;
	sf::Music* _soundtrack;
	FrameBuffer _frameBuffer;
	AnimationManager _animationManager;

public:
	//Scene() {}
	~Scene();
	
	void Init(sf::Music* soundtrack);

	void Update(float deltaTime);
	void Draw(ModelviewStack* ms);

private:
	void SetupCarPaths();

};

#endif
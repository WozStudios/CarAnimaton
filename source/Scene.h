#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include <memory>
#include "Camera.h"
#include "IGameObject.h"
#include "MatStack.h"
#include "SFML/Audio.hpp"

using std::vector;

class Scene
{
private:
	Camera _camera;
	vector<IGameObject*> _gameObjects;
	sf::Music* _soundtrack;

public:
	Scene();
	~Scene();
	
	void Init();
	void Update(float deltaTime);
	void Draw(ModelviewStack* ms);
};

#endif
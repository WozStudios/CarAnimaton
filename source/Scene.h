#ifndef SCENE_H
#define SCENE_H

#include <vector>
#include "Camera.h"
#include "IGameObject.h"
#include "MatStack.h"

using std::vector;

class Scene
{
private:
	Camera _camera;
	vector<IGameObject*> _gameObjects;

public:
	Scene();
	~Scene();
	
	void Init();
	void Update(float deltaTime);
	void Draw(ModelviewStack* ms);
};

#endif
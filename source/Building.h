#ifndef BUILDING_H
#define BUILDING_H

#include "IGameObject.h"
#include "IDrawable.h"
#include "Transform.h"

#define MAX_STORIES 10

class Building : public IGameObject, public IDrawable
{
private:
	Transform _transform;

	double _width;
	double _height;
	double _depth;
	int _numStories;
	int _numWindows;
	double _windowWidth;

	double _storyHeights[MAX_STORIES];

public:
	Building(Transform transform, int numStories);

	vec3 GetPosition() { return _transform.position; }
	vec3 GetRotation() { return _transform.rotation; }
	vec3 GetScale() { return _transform.scale; }
	
	void SetPosition(vec3 position) { _transform.position = position; }
	void SetRotation(vec3 rotation) { _transform.rotation = rotation; }
	void SetScale(vec3 scale) { _transform.scale = scale; }
	
	void Draw(ModelviewStack* ms);

private:
	void GenerateStoryHeights();

	void DrawStory(int story, ModelviewStack* ms);
	void DrawWindow(int story, ModelviewStack* ms);
};

#endif
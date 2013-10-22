#include "Building.h"
#include "drawScene.h"
#include "Random.h"

Building::Building(Transform transform, int numStories)
{
	_transform = transform;

	_width = transform.scale.x;
	_height = transform.scale.y;
	_depth = transform.scale.z;
	_numStories = numStories < MAX_STORIES ? numStories : MAX_STORIES;
	
	_windowWidth = _width * 0.2;

	GenerateStoryHeights();
}

void Building::GenerateStoryHeights()
{
	double currentStoryHeight = 0.5 * _height;
	for (int i = 0; i < _numStories; i++)
	{
		if (i != 0)
			currentStoryHeight = currentStoryHeight * Random(0.3, 0.7);

		_storyHeights[i] = currentStoryHeight;
	}
}

void Building::Draw(ModelviewStack* ms)
{
	useTexture(0);
	useLighting(1);

	ms->Push();
	{
		ms->Translate(_transform.position);
		//ms->Scale(_transform.scale);

		for (int i = 0; i < _numStories; i++)
		{
			DrawStory(i, ms);
		}
	}
	ms->Pop();
}

void Building::DrawStory(int story, ModelviewStack* ms)
{
	double colour = 0.1 * story + 0.5;
	setColour(colour, colour, colour);

	double baseHeight = 0;
	for (int i = 1; i <= story; i++)
		baseHeight += _storyHeights[i - 1];
;
	
	double scaleFactorXZ = 0.2 * (_numStories - story + 1);

	double storyWidth = scaleFactorXZ * _transform.scale.x;
	double storyDepth = scaleFactorXZ * _transform.scale.z;

	ms->Push();
	{
		ms->Translate(vec3(0.0, baseHeight, 0.0));
		ms->Scale(vec3(storyWidth / 2, _storyHeights[story] / 2, storyDepth / 2));
		ms->Translate(vec3(0.0, 1.0, 0.0));

		drawCube(*ms);
	}
	ms->Pop();
	
	//setColour(0.0, 0.0, 0.0);
	//
	//double windowGap = _windowWidth * 0.5;
	//int numWindows = storyDepth / (_windowWidth + windowGap);
	//
	//vec3 initialWindowPos = vec3(storyWidth / 2, _windowWidth / 2 + windowGap, storyDepth / 2 - (_windowWidth / 2 + windowGap));
	//vec3 currentWindowPos = initialWindowPos;
	//
	//// Draw Right Windows
	//
	//for (int j = 0; currentWindowPos.y + _windowWidth < _storyHeights[story]; j++)
	//{
	//	for (int i = 0; i < numWindows; i++)
	//	{
	//		ms->Push();
	//		{
	//			if (i != 0)
	//				currentWindowPos.z -= _windowWidth + windowGap;
	//			
	//			ms->Translate(vec3(0.0, baseHeight, 0.0));
	//			ms->Translate(currentWindowPos);
	//			ms->Rotate(90.0, vec3(.0, 1.0, 0.0));
	//			ms->Rotate(90.0, vec3(1.0, 0.0, 0.0));
	//			ms->Scale(vec3(_windowWidth / 2, 1.0, _windowWidth / 2));
	//			drawCube(*ms);
	//		}
	//		ms->Pop();
	//	}
	//	
	//	currentWindowPos.x = initialWindowPos.x;
	//	currentWindowPos.y += _windowWidth + windowGap;
	//	currentWindowPos.z = initialWindowPos.z;
	//}
	// Draw Left Windows
	// Draw Front Windows
	// Draw Back Windows

}


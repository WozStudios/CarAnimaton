#ifndef FPS_COUNTER_H
#define FPS_COUNTER_H

#include <iostream>

class FPSCounter
{
private:
	int _numFrames;
	float _timeCounter;

public:
	FPSCounter() { _numFrames = 0; _timeCounter = 0; }

	void update(float deltaTime)
	{
		_numFrames++;
		_timeCounter += deltaTime;

		if (_timeCounter > 1.0)
		{
			std::cout << "FPS: " << _numFrames / _timeCounter << "\n";

			_numFrames = 0;
			_timeCounter = 0;
		}
	}
};

#endif
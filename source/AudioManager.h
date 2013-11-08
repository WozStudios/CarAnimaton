#ifndef AUDIO_MANAGER_H
#define AUDIO_MANAGER_H

#include <SFML/Audio.hpp>

#include "Debug.h"

class AudioManager
{
private:
	sf::Music* _soundtrack;
public:
	AudioManager() { _soundtrack = new sf::Music(); }
	~AudioManager() { delete _soundtrack; }
	void Init() { _soundtrack->openFromFile("../media/audio/Soundtrack.ogg"); }

	void StartSoundtrack() { _soundtrack->play(); }
};

#endif
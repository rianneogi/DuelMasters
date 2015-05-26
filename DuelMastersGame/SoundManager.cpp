#include "SoundManager.h"

SoundManager::SoundManager()
{
	for (int i = 0; i < SoundBuffers.size(); i++)
	{
		sounds.push_back(sf::Sound(SoundBuffers.at(i)));
	}
}

SoundManager::~SoundManager()
{
}

void SoundManager::playSound(int soundid)
{
	sounds.at(soundid).play();
}

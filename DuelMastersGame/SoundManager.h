#pragma once

#include "MessageManager.h"

class SoundManager
{
public:
	vector<sf::Sound> sounds;

	SoundManager();
	~SoundManager();

	void playSound(int soundid);
};

extern SoundManager* SoundMngr;


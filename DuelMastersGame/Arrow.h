#pragma once

#include "SoundManager.h"

class Arrow
{
public:
	int fromx;
	int fromy;
	int tox;
	int toy;
	sf::RectangleShape body;
	sf::ConvexShape head;

	Arrow();
	~Arrow();

	void setFrom(int x, int y);
	void setTo(int x, int y);
	void setColor(sf::Color c);
	void render(sf::RenderWindow& window);
};


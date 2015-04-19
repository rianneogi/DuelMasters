#pragma once

#include "Zone.h"

class ZoneList
{
public:
	Zone* zone;
	int scrollpos;

	ZoneList();
	ZoneList(Zone* z);
	~ZoneList();
	
	void render(sf::RenderWindow& window);
	void handleEvent(sf::Event e);
	int getCardAtPos(int x, int y);
	void setZone(Zone* z);
};


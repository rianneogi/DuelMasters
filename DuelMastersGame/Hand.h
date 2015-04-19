#pragma once

#include "ZoneList.h"

class Hand : public Zone
{
public:
	Hand();
	~Hand();

	void renderCards(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	void addCard(Card* c);
	void removeCard(Card* c);
};


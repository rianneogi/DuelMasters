#pragma once

#include "ManaZone.h"

class ShieldZone : public Zone
{
public:
	ShieldZone();
	~ShieldZone();

	int slotsUsed;

	void renderCards(sf::RenderWindow& window, int myPlayer);
	void handleEvent(sf::Event event);
	void addCard(Card* c);
	void removeCard(Card* c);
};


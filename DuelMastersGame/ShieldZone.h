#pragma once

#include "ManaZone.h"

class ShieldZone : public Zone
{
public:
	ShieldZone();
	~ShieldZone();

	int totalcards;

	void renderCards(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	void addCard(Card* c);
};


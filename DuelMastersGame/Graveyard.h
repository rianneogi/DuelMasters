#pragma once

#include "Deck.h"

class Graveyard : public Zone
{
public:
	Graveyard();
	~Graveyard();

	void renderCards(sf::RenderWindow& window, int myPlayer);
	void handleEvent(sf::Event event);
	void addCard(Card* c);
};


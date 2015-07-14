#pragma once

#include "ZoneList.h"

class Hand : public Zone
{
public:
	int myPlayer;

	Hand();
	Hand(int p);
	~Hand();

	void renderCards(sf::RenderWindow& window, int myPlayer);
	void handleEvent(sf::Event event);
	void addCard(Card* c);
	void removeCard(Card* c);
	void flipAllCards();
};


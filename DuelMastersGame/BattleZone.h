#pragma once

#include "ShieldZone.h"

class BattleZone : public Zone
{
public:
	BattleZone();
	~BattleZone();

	void renderCards(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	void addCard(Card* c);
	void evolveCard(Card* c, int evobait); //removes the evobait and adds the evolution at its location
	void removeCard(Card* c);
	//void removeBait(Card* c);
	void seperateEvolution(Card* c); //seperates a card stack
};


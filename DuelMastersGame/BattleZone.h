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
	void addEvoCard(Card* c, int evobait);
	void removeCard(Card* c);
};


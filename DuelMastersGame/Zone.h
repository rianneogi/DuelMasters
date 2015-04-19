#pragma once

#include "Card.h"

class Zone
{
public:
	int x;
	int y;
	int owner;
	vector<Card*> cards;
	sf::RectangleShape rect;

	Zone();
	Zone(int _x, int _y);
	~Zone();

	void render(sf::RenderWindow& window);
	virtual void renderCards(sf::RenderWindow& window) = 0;
	virtual void addCard(Card* c) = 0;
	virtual void handleEvent(sf::Event event) = 0;
	sf::FloatRect getBounds();
	virtual void removeCard(Card* id);
};


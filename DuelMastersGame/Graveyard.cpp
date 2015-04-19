#include "Graveyard.h"

Graveyard::Graveyard()
{
}

Graveyard::~Graveyard()
{
}

void Graveyard::renderCards(sf::RenderWindow& window)
{
	if (cards.size() != 0)
	{
		cards.at(cards.size() - 1)->render(window);
	}
}

void Graveyard::handleEvent(sf::Event event)
{
	for (int i = 0; i < cards.size(); i++)
	{
		cards.at(i)->handleEvent(event);
	}
}
void Graveyard::addCard(Card* c)
{
	c->move(x + CARDZONEOFFSET + CARDORIGINOFFSET, y + CARDZONEOFFSET + CARDORIGINOFFSET);
	c->unflip();
	c->untap();
	cards.push_back(c);
}
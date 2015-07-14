#include "ShieldZone.h"


ShieldZone::ShieldZone() : totalcards(0)
{
}

ShieldZone::~ShieldZone()
{
}

void ShieldZone::renderCards(sf::RenderWindow& window, int myPlayer)
{
	for (int i = 0; i < cards.size(); i++)
	{
		cards.at(i)->render(window, myPlayer);
	}
}

void ShieldZone::handleEvent(sf::Event event)
{
	for (int i = 0; i < cards.size(); i++)
	{
		cards.at(i)->handleEvent(event);
	}
}

void ShieldZone::addCard(Card* c)
{
	c->move(x + CARDZONEOFFSET + CARDORIGINOFFSET + totalcards * CARDSEPERATION, y + CARDZONEOFFSET + CARDORIGINOFFSET);
	c->flip();
	c->untap();
	cards.push_back(c);
	totalcards++;
}


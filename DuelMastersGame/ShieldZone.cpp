#include "ShieldZone.h"


ShieldZone::ShieldZone() : slotsUsed(0)
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
	int cn = 0;
	int i = 1;
	for (i = 1;; i *= 2)
	{
		if (!(slotsUsed&i))
			break;
		cn++;
		if (cn > 32)
		{
			cout << "ERROR: Shield zone add card ERROR" << endl;
			return;
		}
	}
	c->move(x + CARDZONEOFFSET + CARDORIGINOFFSET + cn * CARDSEPERATION, y + CARDZONEOFFSET + CARDORIGINOFFSET);
	c->flip();
	c->untap();
	cards.push_back(c);
	slotsUsed |= i;
}

void ShieldZone::removeCard(Card* c)
{
	for (vector<Card*>::iterator i = cards.begin(); i != cards.end(); i++)
	{
		if (*i == c)
		{
			cards.erase(i);
			break;
		}
	}
}


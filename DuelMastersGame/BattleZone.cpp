#include "BattleZone.h"

BattleZone::BattleZone()
{
}

BattleZone::~BattleZone()
{
}

void BattleZone::renderCards(sf::RenderWindow& window)
{
	for (int i = 0; i < cards.size(); i++)
	{
		cards.at(i)->render(window);
	}
}

void BattleZone::handleEvent(sf::Event event)
{
	for (int i = 0; i < cards.size(); i++)
	{
		cards.at(i)->handleEvent(event);
	}
}

void BattleZone::addCard(Card* c)
{
	c->move(x + CARDZONEOFFSET + CARDORIGINOFFSET + cards.size() * CARDSEPERATION, y + CARDZONEOFFSET + CARDORIGINOFFSET);
	c->unflip();
	c->untap();
	c->summoningSickness = 1;
	cards.push_back(c);
}

void BattleZone::removeCard(Card* c)
{
	int x = 0;
	for (vector<Card*>::iterator i = cards.begin(); i != cards.end(); i++)
	{
		if (*i == c)
		{
			cards.erase(i);
			break;
		}
		x++;
	}
	for (int i = x; i < cards.size(); i++)
	{
		cards.at(i)->setPosition(cards.at(i)->x - CARDSEPERATION, cards.at(i)->y);
	}
}


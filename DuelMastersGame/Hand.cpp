#include "Hand.h"

Hand::Hand() : myPlayer(0)
{
}

Hand::Hand(int p) : myPlayer(p)
{
}


Hand::~Hand()
{
}

void Hand::renderCards(sf::RenderWindow& window, int myPlayer)
{
	for (int i = 0; i < cards.size(); i++)
	{
		cards.at(i)->render(window, myPlayer);
	}
}

void Hand::handleEvent(sf::Event event)
{
	for (int i = 0; i < cards.size(); i++)
	{
		cards.at(i)->handleEvent(event);
	}
}

void Hand::addCard(Card* c)
{
	c->move(x + CARDZONEOFFSET + CARDORIGINOFFSET + cards.size() * CARDSEPERATION, y + CARDZONEOFFSET + CARDORIGINOFFSET);
	c->unflipForPlayer(c->Owner);
	c->flipForPlayer(getOpponent(c->Owner));
	//if (c->Owner == myPlayer)
	//{
	//	c->unflip();
	//}
	//else
	//{
	//	c->flip();
	//}
	c->untap();
	cards.push_back(c);
}

void Hand::removeCard(Card* c)
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

void Hand::flipAllCards()
{
	for (int j = 0; j < 2; j++)
	{
		for (vector<Card*>::iterator i = cards.begin(); i != cards.end(); i++)
		{
			if ((*i)->isFlipped[j] == true)
			{
				(*i)->unflip();
			}
			else
			{
				(*i)->flip();
			}
		}
	}
}

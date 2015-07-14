#include "BattleZone.h"

BattleZone::BattleZone()
{
}

BattleZone::~BattleZone()
{
}

void BattleZone::renderCards(sf::RenderWindow& window, int myPlayer)
{
	for (int i = 0; i < cards.size(); i++)
	{
		cards.at(i)->render(window, myPlayer);
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

//void BattleZone::addCard(Card* c, int speedattacker)
//{
//	c->move(x + CARDZONEOFFSET + CARDORIGINOFFSET + cards.size() * CARDSEPERATION, y + CARDZONEOFFSET + CARDORIGINOFFSET);
//	c->unflip();
//	c->untap();
//	c->summoningSickness = (speedattacker+1)%2;
//	cards.push_back(c);
//}

void BattleZone::evolveCard(Card* c, int evobait)
{
	Card* eb = NULL;
	int ebloc = 0;
	for (vector<Card*>::iterator i = cards.begin(); i != cards.end(); i++)
	{
		if ((*i)->UniqueId == evobait)
		{
			eb = *i;
			break;
		}
		ebloc++;
	}
	if (eb == NULL)
	{
		cout << "ERROR: attempting to evolve on card not in battlezone, cid: " << evobait << endl;
		return;
	}
	sf::FloatRect r = eb->sprite.getGlobalBounds();
	c->move(r.left + r.width/2, r.top + r.height/2);
	c->unflip();
	c->untap();
	c->summoningSickness = 0;
	eb->Zone = ZONE_EVOLVED;
	c->evostack.push_back(eb);
	cards.at(ebloc) = c;
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

void BattleZone::seperateEvolution(Card* c)
{
	//vector<Card*>::iterator eb = cards.begin();
	int flag = 0;
	int eb = -1;

	for (eb = 0; eb < cards.size(); eb++)
	{
		if (cards.at(eb) == c)
		{
			flag = 1;
			eb;
			break;
		}
	}

	if (flag==0)
	{
		cout << "ERROR: attempting to seperate evolution stack not in battlezone, evo name: " << c->Name << endl;
		return;
	}

	for (vector<Card*>::iterator i = c->evostack.begin(); i != c->evostack.end(); i++)
	{
		(*i)->Zone = ZONE_BATTLE;
		cards.insert(cards.begin()+eb, *i);
	}
	c->evostack.clear();
}

//void BattleZone::removeBait(Card* c)
//{
//	int x = 0;
//	for (vector<Card*>::iterator i = cards.begin(); i != cards.end(); i++)
//	{
//		if (*i == c)
//		{
//			cards.erase(i);
//			break;
//		}
//		x++;
//	}
//}


#include "Zone.h"

Zone::Zone() : x(0), y(0)
{
}

Zone::Zone(int _x, int _y) : x(_x), y(_y)
{
}

Zone::~Zone()
{
	/*for (int i = 0; i < cards.size(); i++)
	{
		delete cards.at(i);
	}*/
}

void Zone::removeCard(Card* c)
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

void Zone::render(sf::RenderWindow& window)
{
	window.draw(rect);
}

sf::FloatRect Zone::getBounds()
{
	return rect.getGlobalBounds();
}

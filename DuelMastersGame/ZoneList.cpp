#include "ZoneList.h"

ZoneList::ZoneList() : zone(NULL), scrollpos(0)
{
}

ZoneList::ZoneList(Zone* z) : zone(z), scrollpos(0)
{
}

ZoneList::~ZoneList()
{
}

void ZoneList::render(sf::RenderWindow& window)
{
	if (zone == NULL) return;
	int count = 0;
	for (vector<Card*>::reverse_iterator i = zone->cards.rbegin() + scrollpos; i != zone->cards.rend(); i++)
	{
		sf::RectangleShape r(sf::Vector2f(CARDSEARCHLENGTH, 20));
		r.setPosition(CARDSEARCHX, CARDSEARCHY + CARDSEARCHSEPERATION*count);
		r.setFillColor(sf::Color::White);
		window.draw(r);
		sf::Text t((*i)->Name, DefaultFont, 14);
		t.setFillColor(sf::Color::Black);
		t.setPosition(CARDSEARCHX + CARDZONEOFFSET, CARDSEARCHY + CARDSEARCHSEPERATION*count + CARDZONEOFFSET);
		window.draw(t);
		count++;
		if (count >= CARDSEARCHITEMCOUNT)
		{
			break;
		}
	}
}

void ZoneList::handleEvent(sf::Event e)
{
	if (e.type == sf::Event::MouseWheelMoved)
	{
		scrollpos -= e.mouseWheel.delta;
		if (scrollpos < 0)
		{
			scrollpos = 0;
		}
		if (scrollpos >= zone->cards.size())
		{
			scrollpos = zone->cards.size() - 1;
		}
	}
}

int ZoneList::getCardAtPos(int x, int y)
{
	if (zone == NULL) return -1;
	int ans = -1;
	if (x >= CARDSEARCHX && x <= CARDSEARCHX + CARDSEARCHLENGTH)
	{
		if (y >= CARDSEARCHY && y <= CARDSEARCHY + CARDSEARCHITEMCOUNT*CARDSEARCHSEPERATION)
		{
			ans = zone->cards.size() - (((y - CARDSEARCHY) / CARDSEARCHSEPERATION) + scrollpos) - 1;
		}
	}
	if (ans >= zone->cards.size() || ans < 0)
	{
		ans = -1;
	}
	return ans;
}

void ZoneList::setZone(Zone* z)
{
	zone = z;
	scrollpos = 0;
}
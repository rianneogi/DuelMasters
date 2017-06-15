#include "List.h"

List::List()
{
}

List::List(int _x, int _y, int w, int h, int c) : x(_x), y(_y), itemWidth(w), itemHeight(h), itemCount(c), scrollpos(0)
{
}

List::~List()
{
}

void List::render(sf::RenderWindow& window)
{
	int count = 0;
	for (vector<string>::iterator i = items.begin() + scrollpos; i != items.end(); i++)
	{
		sf::RectangleShape r(sf::Vector2f(itemWidth, itemHeight));
		r.setPosition(x, y + itemHeight*count);
		r.setFillColor(sf::Color::White);
		window.draw(r);
		sf::Text t((*i), DefaultFont, 14);
		t.setFillColor(sf::Color::Black);
		t.setPosition(x + CARDZONEOFFSET, y + itemHeight*count + CARDZONEOFFSET);
		window.draw(t);
		count++;
		if (count >= itemCount)
		{
			break;
		}
	}
}

void List::handleEvent(sf::Event event)
{
	if (event.type == sf::Event::MouseWheelMoved)
	{
		scrollpos -= event.mouseWheel.delta;
		if (scrollpos < 0)
		{
			scrollpos = 0;
		}
		if (scrollpos >= items.size())
		{
			scrollpos = items.size() - 1;
		}
	}
}

int List::getItemAtPos(int MouseX, int MouseY)
{
	int ans = -1;
	if (MouseX >= x && MouseX <= x + itemWidth)
	{
		if (MouseY >= y && MouseY <= y + itemCount*itemHeight)
		{
			ans = ((MouseY - y) / itemHeight) + scrollpos;
		}
	}
	if (ans >= items.size() || ans < 0)
	{
		ans = -1;
	}
	return ans;
}

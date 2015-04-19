#include "Arrow.h"

Arrow::Arrow()
{
	body = sf::RectangleShape(sf::Vector2f(0, 0));
	body.setFillColor(sf::Color(255, 0, 0, 128));
	head = sf::ConvexShape(3);
	head.setFillColor(sf::Color(255, 0, 0, 128));
	head.setPoint(0, sf::Vector2f(0, -10));
	head.setPoint(1, sf::Vector2f(0, 10));
	head.setPoint(2, sf::Vector2f(14, 0));
}

Arrow::~Arrow()
{
}

void Arrow::setFrom(int x, int y)
{
	fromx = x;
	fromy = y;
}

void Arrow::setTo(int x, int y)
{
	tox = x;
	toy = y;
}

void Arrow::setColor(sf::Color c)
{
	body.setFillColor(c);
	head.setFillColor(c);
}

void Arrow::render(sf::RenderWindow& window)
{
	float dx = tox - fromx;
	float dy = toy - fromy;
	float size = sqrt(dx*dx + dy*dy);
	float angle = atan2(dy, dx);
	float rotation = (angle * 180 / 3.1415);
	body.setSize(sf::Vector2f(size, 10));
	body.setPosition(sf::Vector2f(fromx - 5 * sin(-angle), fromy - 5 * cos(-angle)));
	body.setRotation(rotation);
	head.setRotation(rotation);
	head.setPosition(sf::Vector2f(fromx + cos(angle)*size, fromy + sin(angle)*size));
	window.draw(body);
	window.draw(head);
}

#include "Button.h"

Button::Button()
{
}

Button::Button(const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Color& rectcolor, int bordersize, const sf::Color& bordercolor,
	const sf::Color& textcolor, const string& textstr, int textsize)
{
	rect = sf::RectangleShape(size);
	rect.setPosition(pos);
	rect.setFillColor(rectcolor);
	rect.setOutlineThickness(bordersize);
	rect.setOutlineColor(bordercolor);
	text = sf::Text(textstr, DefaultFont, textsize);
	text.setColor(textcolor);
	text.setPosition(pos.x + CARDZONEOFFSET, pos.y + CARDZONEOFFSET);
}

Button::~Button()
{
}

bool Button::collision(int MouseX, int MouseY)
{
	return (checkCollision(rect.getGlobalBounds(), MouseX, MouseY));
}

void Button::render(sf::RenderWindow& window)
{
	window.draw(rect);
	window.draw(text);
}

bool checkCollision(sf::FloatRect& b, int x, int y)
{
	if (x >= b.left && x <= b.left + b.width && y >= b.top && y <= b.top + b.height)
	{
		return true;
	}
	return false;
}


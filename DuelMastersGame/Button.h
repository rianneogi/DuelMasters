#pragma once

#include "List.h"

class Button
{
public:
	sf::Text text;
	sf::RectangleShape rect;

	Button();
	Button(const sf::Vector2f& pos, const sf::Vector2f& size, const sf::Color& rectcolor, int bordersize, const sf::Color& bordercolor,
		const sf::Color& textcolor, const string& text, int textsize);
	~Button();

	void render(sf::RenderWindow& window);
	bool collision(int MouseX, int MouseY);
	
	void setString(string s);
	void setPosition(int x, int y);
};

bool checkCollision(sf::FloatRect& b, int x, int y);


#pragma once

#include "Arrow.h"

class List
{
public:
	vector<string> items;
	int x, y;
	int itemWidth;
	int itemHeight;
	int itemCount;
	int scrollpos;
	int MouseX, MouseY;

	List();
	List(int _x, int _y, int w, int h, int c);
	~List();

	void render(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	int getItemAtPos(int MouseX, int MouseY);
};


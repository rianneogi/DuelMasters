#pragma once
#include "MainMenu.h"
class DeckBuilder : public GameWindow
{
public:
	DeckBuilder();
	~DeckBuilder();

	void render(sf::RenderWindow& window);
	void update(unsigned int deltatime);
	int handleEvent(sf::Event event, int callback);
};


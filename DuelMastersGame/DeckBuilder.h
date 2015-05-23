#pragma once
#include "MainMenu.h"
class DeckBuilder : public GameWindow
{
public:
	std::map<int, int> decklist;
	int decklistpos;

	int cardlistpos;

	int cardcountx;
	int cardcounty;

	int MouseX, MouseY;

	vector<sf::Sprite> cardsprites;

	Button exitbutton;

	DeckBuilder();
	~DeckBuilder();

	void render(sf::RenderWindow& window);
	void update(unsigned int deltatime);
	int handleEvent(sf::Event event, int callback);
};


#pragma once

#include "GameWindow.h"

class DeckBuilder;
class DuelInterface;

class MainMenu : public GameWindow
{
public:
	sf::Text title;
	Button play;
	Button deckbuilder;
	Button exit;

	int MouseX, MouseY;

	MainMenu();
	~MainMenu();

	int handleEvent(sf::Event event, int callback);
	void render(sf::RenderWindow& window);
	void update(unsigned int deltatime);
};

extern DeckBuilder* deckBuilder;
extern DuelInterface* ActiveDuel;
extern MainMenu* mainMenu;
extern GameWindow* currentWindow;


#pragma once

#include "Button.h"

//enum WindowType { WINDOW_MENU, WINDOW_DUEL, WINDOW_DECK };
enum ReturnValue { RETURN_BUTTON1 = -1, RETURN_BUTTON2 = -2, RETURN_NOVALID = -3, RETURN_NOTHING = -4, RETURN_QUIT = -5 };

class GameWindow
{
public:
	GameWindow();
	~GameWindow();

	virtual void render(sf::RenderWindow& window) = 0;
	virtual int handleEvent(sf::Event event, int callback) = 0;
	virtual void update(unsigned int deltatime) = 0;
};


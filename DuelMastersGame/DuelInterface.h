#pragma once

#include "Duel.h"

enum DuelState { DUELSTATE_DUEL, DUELSTATE_MENU, DUELSTATE_SINGLE, DUELSTATE_MULTI };

class DuelInterface : public GameWindow
{
public:
	Duel duel;

	int duelstate;

	int MouseX;
	int MouseY;
	int selectedcard;
	int selectedcardzone;

	Button endturnbutton;
	vector<sf::Sound> sounds;

	Button cancelbutton;
	Button quitbutton;
	sf::Text infotext;

	Button cardCountBox;

	vector<Arrow> arrows;
	int mousearrow;

	sf::Sprite hovercard;

	ZoneList cardsearch;

	List decklist;
	int deckschosen;

	DuelInterface();
	~DuelInterface();

	int handleMessage(Message& msg);
	void dispatchMessage(Message& msg);
	void update(unsigned int deltatime);
	void render(sf::RenderWindow& window);
	int handleEvent(sf::Event event, int callback);

	void setDecklist();

	void undoSelection();
};

int mainLoop(sf::RenderWindow& window, int callback);


#pragma once

#include "Duel.h"

class DuelInterface
{
public:
	Duel duel;

	int MouseX;
	int MouseY;
	int selectedcard;
	int selectedcardzone;

	/*MessageManager MsgMngr;
	Message currentMessage;*/

	sf::RectangleShape endturnbutton;
	sf::Text endturntext;
	sf::Sound endturnsound;

	sf::RectangleShape cancelbutton;
	sf::Text canceltext;
	sf::Text infotext;

	vector<Arrow> arrows;
	int mousearrow;

	sf::Sprite hovercard;

	ZoneList cardsearch;

	DuelInterface();
	~DuelInterface();

	int handleMessage(Message& msg);
	void dispatchMessage(Message& msg);
	void update(int deltatime);
	void render(sf::RenderWindow& window);
	void handleEvent(sf::Event event);

	void undoSelection();
};


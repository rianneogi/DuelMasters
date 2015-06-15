#pragma once

#include "Duel.h"

enum DuelState { DUELSTATE_DUEL, DUELSTATE_MENU, DUELSTATE_SINGLE, DUELSTATE_MULTI };
enum DuelType { DUELTYPE_SINGLE, DUELTYPE_MULTI, DUELTYPE_AI };

extern sf::TcpSocket Socket;

class DuelInterface : public GameWindow
{
public:
	Duel duel;

	int dueltype;
	int duelstate;

	int myPlayer;

	int MouseX;
	int MouseY;
	int selectedcard;
	int selectedcardzone;
	int iscardevo;

	Button endturnbutton;

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
	int receivePacket(sf::Packet& packet, int callback);

	void setDecklist();

	void undoSelection();
	void setMyPlayer(int p);

	void flipCardForPlayer(int cid, int p);
	void unflipCardForPlayer(int cid, int p);
};

int mainLoop(sf::RenderWindow& window, int callback);


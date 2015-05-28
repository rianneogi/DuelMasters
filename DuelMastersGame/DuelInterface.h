#pragma once

#include "Duel.h"

enum DuelState { DUELSTATE_DUEL, DUELSTATE_MENU, DUELSTATE_SINGLE, DUELSTATE_MULTI };
enum DuelType { DUELTYPE_SINGLE, DUELTYPE_MULTI, DUELTYPE_AI };
enum PacketType { PACKET_MSG, PACKET_SETDECK };

extern sf::TcpSocket Socket;

class DuelInterface : public GameWindow
{
public:
	Duel duel;

	int dueltype;
	int duelstate;

	int MouseX;
	int MouseY;
	int selectedcard;
	int selectedcardzone;

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
	void receivePacket(sf::Packet& packet);

	void setDecklist();

	void undoSelection();
};

int mainLoop(sf::RenderWindow& window, int callback);


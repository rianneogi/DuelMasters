#pragma once
#include "Card.h"

struct DeckItem
{
	int card;
	int count;
};

class DeckBuilder : public GameWindow
{
public:
	sf::Sprite hovercard;

	int decklistpos;
	//std::map<int, int> decklist;
	vector<DeckItem> decklist;

	int cardlistpos;
	vector<sf::Sprite> cardsprites;

	int cardcountx;
	int cardcounty;

	int MouseX, MouseY;

	Button savebutton;
	Button loadbutton;
	Button newbutton;
	Button exitbutton;

	string currentdeck;
	int isloadingdeck;

	fstream deckfile;
	vector<string> decks;

	DeckBuilder();
	~DeckBuilder();

	void render(sf::RenderWindow& window);
	void update(unsigned int deltatime);
	int handleEvent(sf::Event event, int callback);
	int getCardAtPos(int x, int y);
	int getDeckAtPos(int x, int y);

	void addCard(int cid);
	void removeCard(int cid);
	int getCardCount(int cid);
	void setCardCount(int cid, int count);

	void loaddeck();
	void savedeck();
};


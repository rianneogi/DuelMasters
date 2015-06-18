#pragma once
#include "Card.h"

enum SortBy { SORTBY_NAME, SORTBY_COST, SORTBY_CIV, SORTBY_RACE, SORTBY_TYPE };

const sf::Color CivColors[5] = { sf::Color::Yellow, sf::Color::Green, sf::Color::Blue, sf::Color::Red, sf::Color::Magenta };
const sf::Color InactiveButtonColor = sf::Color(170, 170, 170);
const sf::Color ActiveButtonColor = sf::Color(255, 255, 70);

const int DECKLISTX = CARDSEARCHX;
const int DECKLISTY = CARDSEARCHY + 200;
const int DECKLISTLENGTH = CARDSEARCHLENGTH;
const int DECKLISTSEPERATION = CARDSEARCHSEPERATION;
const int DECKLISTCOUNT = 18;

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
	vector<DeckItem> decklist;

	vector<CardData> cardlist;
	int cardlistpos;
	vector<sf::Sprite> cardsprites;

	int cardcountx;
	int cardcounty;

	int MouseX, MouseY;

	Button savebutton;
	Button loadbutton;
	Button newbutton;
	Button exitbutton;

	Button civbutton[5];
	int civfilter[5];
	int sortby;
	Button sortbutton[5];

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

	void generateCardList();
	void resetCardSprites();

	void loaddeck();
	void savedeck();
};


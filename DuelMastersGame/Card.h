#pragma once

#include "Modifier.h"

enum ZoneType { ZONE_HAND, ZONE_DECK, ZONE_BATTLE, ZONE_MANA, ZONE_SHIELD, ZONE_GRAVEYARD };
enum Civilization { CIV_LIGHT, CIV_NATURE, CIV_WATER, CIV_FIRE, CIV_DARKNESS };
enum CardType { TYPE_CREATURE, TYPE_SPELL };
enum DefenderType { DEFENDER_CREATURE, DEFENDER_PLAYER };

class Card
{
public:
	int UniqueId;
	int CardId;
	int x;
	int y;

	vector<Modifier> modifiers;

	string Name;
	string Race;
	int Civilization;
	int Type;
	int ManaCost;
	int Power;
	int Breaker;
	int Owner;
	int Zone;
	int isBlocker;
	int isShieldTrigger;
	bool isTapped;
	int summoningSickness;

	sf::Sprite sprite;
	sf::Text powertext;
	bool isFlipped;
	//int displayPower;
	
	Card();
	Card(int uid, int cid, int owner);
	~Card();

	void render(sf::RenderWindow& window);
	void handleEvent(sf::Event event);
	int handleMessage(Message& msg);
	void callOnCast();
	void move(int _x, int _y);
	void setPosition(int _x, int _y);
	void updatePower(int pow);
	void flip();
	void unflip();
	void tap();
	void untap();
	sf::FloatRect getBounds();
};

int getCardIdFromName(string s);
int initCards();
void cleanupCards();




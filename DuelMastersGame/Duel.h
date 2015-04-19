#pragma once

#include "Choice.h"

enum AttackPhase { PHASE_NONE, PHASE_BLOCK, PHASE_TARGET, PHASE_TRIGGER };

class Duel
{
public:
	Deck decks[2];
	Hand hands[2];
	ManaZone manazones[2];
	Graveyard graveyards[2];
	ShieldZone shields[2];
	BattleZone battlezones[2];

	vector<Card*> CardList;

	int attacker;
	int defender;
	int defendertype;
	int breakcount;
	vector<int> shieldtargets;
	int attackphase;

	Choice choice;
	int choiceCard;
	bool isChoiceActive;

	int winner;

	int nextUniqueId;

	MessageManager MsgMngr;
	Message currentMessage;
	

	/*int MouseX;
	int MouseY;
	int selectedcard;
	int selectedcardzone;

	sf::RectangleShape endturnbutton;
	sf::Text endturntext;
	sf::Sound endturnsound;

	sf::RectangleShape cancelbutton;
	sf::Text canceltext;
	sf::Text infotext;

	vector<Arrow> arrows;
	int mousearrow;

	sf::Sprite hovercard;

	ZoneList cardsearch;*/

	int turn;
	int manaUsed;

	Duel();
	~Duel();

	void setDecks(string p1, string p2);
	void loadDeck(string s, int p);
	void startDuel();
	void nextTurn();

	int handleMessage(Message& msg);
	int handleInterfaceInput(Message& msg);
	void dispatchMessage(Message& msg);
	void update(int deltatime);
	//void render(sf::RenderWindow& window);
	void handleEvent(sf::Event event);

	void addChoice(string info, int skip, int card);
	void checkChoiceValid();
	int choiceCanBeSelected(int sid);

	//void undoSelection();
	void resetAttack();

	Zone* getZone(int player, int zone);
	void destroyCard(Card* c);
	void battle(int att, int def);
	Card* getCard(int player, int zone, int id);

	int getCreaturePower(int uid);
	int getCreatureBreaker(int uid);
	int getCreatureCanAttack(int uid);
	int getCreatureCanBlock(int uid);
	int getCreatureCanBeAttacked(int uid);
	int getCreatureCanBeBlocked(int uid);
	int getCreatureCanAttackPlayers(int uid);
	int getCreatureCanAttackCreatures(int uid);
	int getCreatureCanAttackUntappedCreatures(int uid);
	int getCardCost(int uid);
	int getIsShieldTrigger(int uid);
};

int getOpponent(int turn);
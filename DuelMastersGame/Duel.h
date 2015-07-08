#pragma once

#include "Choice.h"

enum AttackPhase { PHASE_NONE, PHASE_BLOCK, PHASE_TARGET, PHASE_TRIGGER };
enum CanAttack { CANATTACK_TAPPED, CANATTACK_UNTAPPED, CANATTACK_NO, CANATTACK_ALWAYS };

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

	int castingcard;
	int castingciv;
	int castingcost;
	int castingevobait;
	bool castingcivtapped;

	Choice choice;
	int choiceCard;
	int choicePlayer;
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
	void undoMessage(Message& msg);
	int handleInterfaceInput(Message& msg);
	bool dispatchAllMessages();
	void dispatchMessage(Message& msg);
	void update(unsigned int deltatime);
	//void render(sf::RenderWindow& window);
	void handleEvent(sf::Event event);

	void addChoice(string info, int skip, int card, int player, int validref);
	void checkChoiceValid();
	int choiceCanBeSelected(int sid);

	//void undoSelection();
	void resetAttack();
	void resetCasting();
	void resetChoice();
	void clearCards();

	void setMyPlayer(int p);

	bool isThereUntappedManaOfCiv(int player, int civ);

	Zone* getZone(int player, int zone);
	void destroyCard(Card* c);
	void battle(int att, int def);
	Card* getCard(int player, int zone, int id);

	void drawCards(int player, int count);

	int getCreaturePower(int uid);
	int getCreatureBreaker(int uid);
	int getCreatureIsBlocker(int uid);
	int getCreatureCanBlock(int attckr, int blckr);
	//int getCreatureCanAttack(int uid);
	int getCreatureCanAttackPlayers(int uid);
	//int getCreatureCanAttackCreatures(int uid);
	//int getCreatureCanAttackTarget(int attckr, int dfndr);
	int getCreatureCanAttackCreature(int attckr, int dfndr);
	//int getCreatureCanBeAttacked(int attckr, int dfndr);
	//int getCreatureCanBeBlocked(int uid);
	//int getCreatureCanAttackUntappedCreatures(int uid);
	int getCardCost(int uid);
	int getCardCivilization(int uid);
	int getIsShieldTrigger(int uid);
	int canUseShieldTrigger(int uid);
	int getIsEvolution(int uid);
	int getIsSpeedAttacker(int uid);
	int getCardCanCast(int uid);
	int isCreatureOfRace(int uid, string race); //finds if the word race exists in the creature's race
	string getCreatureRace(int uid); //returns the full race string of the creature
	int getCreatureCanEvolve(int evo, int bait);
};

int getOpponent(int turn);
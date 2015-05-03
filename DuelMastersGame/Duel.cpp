#include "Duel.h"

Duel::Duel()
{
	turn = 0;
	manaUsed = 0;
	nextUniqueId = 0;

	int Factor[2] = { 1, -1 };
	int Factor2[2] = { 1, 0 };
	for (int i = 0; i < 2; i++)
	{
		decks[i].owner = i;
		battlezones[i].owner = i;
		graveyards[i].owner = i;
		hands[i].owner = i;
		manazones[i].owner = i;
		shields[i].owner = i;

		decks[i].x = ZONE2X;
		graveyards[i].x = ZONE2X;
		hands[i].x = ZONE1X;
		manazones[i].x = ZONE1X;
		shields[i].x = ZONE1X;
		battlezones[i].x = ZONE1X;

		hands[i].y = CENTER + ZONEYOFFSET*Factor[i] * 4 - ZONEYOFFSET*Factor2[i];
		decks[i].y = CENTER + ZONEYOFFSET*Factor[i] * 3 - ZONEYOFFSET*Factor2[i];
		manazones[i].y = CENTER + ZONEYOFFSET*Factor[i] * 3 - ZONEYOFFSET*Factor2[i];
		shields[i].y = CENTER + ZONEYOFFSET*Factor[i] * 2 - ZONEYOFFSET*Factor2[i];
		graveyards[i].y = CENTER + ZONEYOFFSET*Factor[i] * 2 - ZONEYOFFSET*Factor2[i];
		battlezones[i].y = CENTER + ZONEYOFFSET*Factor[i] - ZONEYOFFSET*Factor2[i];

		decks[i].rect = sf::RectangleShape(sf::Vector2f(CARDSEPERATION + CARDZONEOFFSET, CARDSEPERATION + CARDZONEOFFSET));
		graveyards[i].rect = sf::RectangleShape(sf::Vector2f(CARDSEPERATION + CARDZONEOFFSET, CARDSEPERATION + CARDZONEOFFSET));
		hands[i].rect = sf::RectangleShape(sf::Vector2f(ZONE2X - ZONE1X - 10, CARDSEPERATION + CARDZONEOFFSET));
		manazones[i].rect = sf::RectangleShape(sf::Vector2f(ZONE2X - ZONE1X - 10, CARDSEPERATION + CARDZONEOFFSET));
		shields[i].rect = sf::RectangleShape(sf::Vector2f(ZONE2X - ZONE1X - 10, CARDSEPERATION + CARDZONEOFFSET));
		battlezones[i].rect = sf::RectangleShape(sf::Vector2f(ZONE2X - ZONE1X - 10, CARDSEPERATION + CARDZONEOFFSET));

		decks[i].rect.setPosition(decks[i].x, decks[i].y);
		hands[i].rect.setPosition(hands[i].x, hands[i].y);
		manazones[i].rect.setPosition(manazones[i].x, manazones[i].y);
		graveyards[i].rect.setPosition(graveyards[i].x, graveyards[i].y);
		battlezones[i].rect.setPosition(battlezones[i].x, battlezones[i].y);
		shields[i].rect.setPosition(shields[i].x, shields[i].y);

		decks[i].rect.setFillColor(sf::Color(255, 255, 255));
		hands[i].rect.setFillColor(sf::Color(255, 255, 255));
		manazones[i].rect.setFillColor(sf::Color(255, 255, 255));
		graveyards[i].rect.setFillColor(sf::Color(255, 255, 255));
		battlezones[i].rect.setFillColor(sf::Color(255, 255, 255));
		shields[i].rect.setFillColor(sf::Color(255, 255, 255));

		decks[i].rect.setOutlineColor(sf::Color(255, 50, 255));
		hands[i].rect.setOutlineColor(sf::Color(50, 50, 255));
		manazones[i].rect.setOutlineColor(sf::Color(50, 255, 50));
		graveyards[i].rect.setOutlineColor(sf::Color(100, 100, 120));
		battlezones[i].rect.setOutlineColor(sf::Color(255, 50, 50));
		shields[i].rect.setOutlineColor(sf::Color(255, 255, 50));

		decks[i].rect.setOutlineThickness(ZONEBORDERSIZE);
		hands[i].rect.setOutlineThickness(ZONEBORDERSIZE);
		manazones[i].rect.setOutlineThickness(ZONEBORDERSIZE);
		graveyards[i].rect.setOutlineThickness(ZONEBORDERSIZE);
		battlezones[i].rect.setOutlineThickness(ZONEBORDERSIZE);
		shields[i].rect.setOutlineThickness(ZONEBORDERSIZE);
	}

	attackphase = PHASE_NONE;
	attacker = -1;
	defender = -1;
	breakcount = -1;

	isChoiceActive = false;
	choiceCard = -1;

	winner = -1;
}

Duel::~Duel()
{
	for (int i = 0; i < CardList.size(); i++)
	{
		delete CardList.at(i);
	}
}

int Duel::handleMessage(Message& msg)
{
	if (msg.getType() == "cardmove")
	{
		Card* c = CardList.at(msg.getInt("card"));
		int owner = c->Owner;
		getZone(owner, c->Zone)->removeCard(c);
		getZone(owner, msg.getInt("to"))->addCard(c);
		c->Zone = msg.getInt("to");
		if (c->Zone == ZONE_BATTLE && c->Type == TYPE_SPELL)
		{
			c->callOnCast(); //cast the spell
		}
		if (decks[owner].cards.size() == 0)
		{
			//player loses game
			winner = getOpponent(turn);
		}
	}
	else if (msg.getType() == "carddestroy")
	{
		Message m("cardmove");
		m.addValue("card", msg.getInt("card"));
		m.addValue("to", msg.getInt("zoneto"));
		MsgMngr.sendMessage(m);
	}
	else if (msg.getType() == "carddiscard")
	{
		Message m("cardmove");
		m.addValue("card", msg.getInt("card"));
		m.addValue("to", ZONE_GRAVEYARD);
		MsgMngr.sendMessage(m);
	}
	/*else if (msg.getType() == "carddraw") //carddraw is replaced by cardmove with to=ZONE_HAND
	{
		int plyr = msg.getInt("player");
		Message m("cardmove");
		m.addValue("card", decks[plyr].getTopCard());
		m.addValue("to", ZONE_HAND);
		MsgMngr.sendMessage(m);
	}*/
	else if (msg.getType() == "cardplay")
	{
		Message m("cardmove");
		m.addValue("card", msg.getInt("card"));
		m.addValue("to", ZONE_BATTLE);
		MsgMngr.sendMessage(m);
	}
	else if (msg.getType() == "cardmana")
	{
		manaUsed = 1;
		Message m("cardmove");
		m.addValue("card", msg.getInt("card"));
		m.addValue("to", ZONE_MANA);
		MsgMngr.sendMessage(m);
	}
	else if (msg.getType() == "creatureattack")
	{
		/*int type = msg.getInt("defendertype");
		if (type == DEFENDER_CREATURE)
		{
			Message m("creaturebattle");
			m.addValue("attacker", msg.getInt("attacker"));
			m.addValue("defender", msg.getInt("defender"));
			MsgMngr.sendMessage(m);
		}
		else if (type == DEFENDER_PLAYER)
		{
			Message m("creaturebreakshield");
			m.addValue("attacker", msg.getInt("attacker"));
			m.addValue("defender", msg.getInt("defender"));
			MsgMngr.sendMessage(m);
		}*/
		attacker = msg.getInt("attacker");
		defender = msg.getInt("defender");
		defendertype = msg.getInt("defendertype");
		//attackphase = PHASE_BLOCK;
		Message m("changeattackphase");
		m.addValue("phase", PHASE_BLOCK);
		MsgMngr.sendMessage(m);
	}
	else if (msg.getType() == "creatureblock")
	{
		Message m("creaturebattle");
		m.addValue("attacker", msg.getInt("attacker"));
		m.addValue("defender", msg.getInt("blocker"));
		MsgMngr.sendMessage(m);
	}
	else if (msg.getType() == "creaturebreakshield")
	{
		Message m("breakshield");
		m.addValue("player", msg.getInt("defender"));
		m.addValue("shield", msg.getInt("shield"));
		m.addValue("cantrigger", 1);
		MsgMngr.sendMessage(m);
	}
	else if (msg.getType() == "breakshield")
	{
		Message m("cardmove");
		m.addValue("card", msg.getInt("shield"));
		m.addValue("to", ZONE_HAND);
		MsgMngr.sendMessage(m);
		/*if (msg.getInt("cantrigger") == 1)
		{
			attackphase = PHASE_TRIGGER;
			shieldtargets.push_back(shields[plyr].cards.at(shields[plyr].cards.size() - 1)->UniqueId);
		}*/
	}
	else if (msg.getType() == "creaturebattle")
	{
		battle(msg.getInt("attacker"), msg.getInt("defender"));
	}
	else if (msg.getType() == "cardtap")
	{
		CardList.at(msg.getInt("card"))->tap();
	}
	else if (msg.getType() == "carduntap")
	{
		CardList.at(msg.getInt("card"))->untap();
	}
	else if (msg.getType() == "endturn")
	{
		turn = (turn + 1) % 2;
		manaUsed = 0;
		Message m("startturn");
		m.addValue("player", turn);
		MsgMngr.sendMessage(m);
	}
	else if (msg.getType() == "startturn")
	{
		int plyr = msg.getInt("player");
		vector<Card*>::iterator i;
		for (i = battlezones[plyr].cards.begin(); i != battlezones[plyr].cards.end(); i++) //untap creature
		{
			Message m("carduntap");
			m.addValue("card", (*i)->UniqueId);
			MsgMngr.sendMessage(m);
			(*i)->summoningSickness = 0;
		}
		for (i = manazones[plyr].cards.begin(); i != manazones[plyr].cards.end(); i++) //untap mana
		{
			Message m("carduntap");
			m.addValue("card", (*i)->UniqueId);
			MsgMngr.sendMessage(m);
		}
		//Message m("carddraw"); //draw card
		//m.addValue("player", plyr);
		//MsgMngr.sendMessage(m);
		drawCards(plyr, 1);
	}
	else if (msg.getType() == "modifierdestroy")
	{
		int uid = msg.getInt("card");
		CardList.at(uid)->modifiers.erase(CardList.at(uid)->modifiers.begin() + msg.getInt("modifier"));
	}
	else if (msg.getType() == "changeattackphase")
	{
		attackphase = msg.getInt("phase");
	}
	else if (msg.getType() == "resetattack")
	{
		resetAttack();
	}
	else if (msg.getType() == "deckshuffle")
	{
		decks[msg.getInt("player")].shuffle();
	}
	else if (msg.getType() == "carddiscard")
	{
		Message m("cardmove");
		m.addValue("card", hands[msg.getInt("player")].cards.at(rand() % hands[msg.getInt("player")].cards.size())->UniqueId);
		m.addValue("from", ZONE_HAND);
		m.addValue("to", ZONE_GRAVEYARD);
		MsgMngr.sendMessage(m);
	}
	return 0;
}

int Duel::handleInterfaceInput(Message& msg)
{
	string type = msg.getType();
	if (type == "cardplay")
	{
		int whichCard = msg.getInt("card");
		int manacost = getCardCost(whichCard);
		if (manazones[turn].getUntappedMana() >= manacost)
		{
			manazones[turn].tapMana(manacost);
			MsgMngr.sendMessage(msg);
		}
	}
	else if (type == "cardmana")
	{
		if (manaUsed == 0)
		{
			MsgMngr.sendMessage(msg);
		}
	}
	else if (type == "endturn")
	{
		if (attackphase == PHASE_NONE && isChoiceActive == 0)
		{
			nextTurn();
		}
	}
	else if (type == "creatureattack")
	{
		int attck = msg.getInt("attacker");
		int defen = msg.getInt("defender");
		if (msg.getInt("defendertype") == DEFENDER_PLAYER)
		{
			if (getCreatureCanAttackPlayer(attck,defen) == 1
				&& CardList.at(attck)->isTapped == false)
			{
				MsgMngr.sendMessage(msg);
				Message msg2("cardtap");
				msg2.addValue("card", msg.getInt("attacker"));
				MsgMngr.sendMessage(msg2);
			}
		}
		else if (msg.getInt("defendertype") == DEFENDER_CREATURE)
		{
			if ((CardList.at(defen)->isTapped == true || getCreatureCanAttackCreature(attck,defen) == CANATTACK_UNTAPPED)
				&& getCreatureCanAttackCreature(attck, defen) >= CANATTACK_TAPPED
				&& CardList.at(attck)->isTapped == false)
			{
				MsgMngr.sendMessage(msg);
				Message msg2("cardtap");
				msg2.addValue("card", msg.getInt("attacker"));
				MsgMngr.sendMessage(msg2);
			}
		}
	}
	else if (type == "creatureblock")
	{
		if (attackphase == PHASE_BLOCK)
		{
			int blocker = msg.getInt("blocker");
			if (getCreatureCanBlock(attacker, blocker) && CardList.at(blocker)->isTapped == false
				&& blocker != defender)
			{
				Message msg2("cardtap");
				msg2.addValue("card", blocker);
				MsgMngr.sendMessage(msg2);
				Message msg("creaturebattle");
				msg.addValue("attacker", attacker);
				msg.addValue("defender", blocker);
				MsgMngr.sendMessage(msg);
				//resetAttack();
				Message msg3("resetattack");
				MsgMngr.sendMessage(msg3);
			}
		}
	}
	else if (type == "blockskip")
	{
		if (attackphase == PHASE_BLOCK)
		{
			if (defendertype == DEFENDER_CREATURE)
			{
				Message m("creaturebattle");
				m.addValue("attacker", attacker);
				m.addValue("defender", defender);
				MsgMngr.sendMessage(m);
				//resetAttack();
				Message msg3("resetattack");
				MsgMngr.sendMessage(msg3);
			}
			else if (defendertype == DEFENDER_PLAYER)
			{
				//int def = msg.getInt("defender");
				if (shields[defender].cards.size() == 0)
				{
					winner = getOpponent(defender);
				}
				else
				{
					//attackphase = PHASE_TARGET;
					Message m("changeattackphase");
					m.addValue("phase", PHASE_TARGET);
					MsgMngr.sendMessage(m);
					breakcount = getCreatureBreaker(attacker);
				}
			}
		}
	}
	else if (type == "targetshield")
	{
		if (attackphase == PHASE_TARGET)
		{
			int shield = msg.getInt("shield");
			shieldtargets.push_back(shield);

			if (shieldtargets.size() >= breakcount || shields[CardList.at(shield)->Owner].cards.size() <= 1)
			{
				Message m("changeattackphase");
				m.addValue("phase", PHASE_TRIGGER);
				MsgMngr.sendMessage(m);
			}

			Message m("creaturebreakshield");
			m.addValue("attacker", attacker);
			m.addValue("defender", defender);
			m.addValue("shield", shield);
			MsgMngr.sendMessage(m);
		}
	}
	else if (type == "triggeruse")
	{
		if (attackphase == PHASE_TRIGGER)
		{
			for (vector<int>::iterator j = shieldtargets.begin(); j != shieldtargets.end(); j++)
			{
				int trigger = msg.getInt("trigger");
				if (*j == trigger)
				{
					if (getIsShieldTrigger(trigger))
					{
						Message m("cardplay");
						m.addValue("card", trigger);
						MsgMngr.sendMessage(m);
					}
				}
			}
		}
	}
	else if (type == "triggerskip")
	{
		if (attackphase == PHASE_TRIGGER)
		{
			//resetAttack();
			Message msg3("resetattack");
			MsgMngr.sendMessage(msg3);
		}
	}
	else if (type == "choiceselect")
	{
		int sid = msg.getInt("selection");
		if (choiceCanBeSelected(sid) == 1)
		{
			int chcard = choiceCard;
			resetChoice();
			choice.callselect(chcard, sid);
		}
	}
	else if (type == "choicebutton1")
	{
		if (choice.buttoncount >= 1 && isChoiceActive)
		{
			int chcard = choiceCard;
			resetChoice();
			choice.callbutton1(chcard);
		}
	}
	else if (type == "choicebutton2")
	{
		if (choice.buttoncount >= 2 && isChoiceActive)
		{
			int chcard = choiceCard;
			resetChoice();
			choice.callbutton2(chcard);
		}
	}
	return 0;
}

void Duel::update(int deltatime)
{
	if (!isChoiceActive)
	{
		bool worldchanged = false;
		while (MsgMngr.hasMoreMessages())
		{
			Message msg = MsgMngr.peekMessage();
			MsgMngr.dispatch();
			std::cout << "dispatching message: ";
			for (std::map<std::string, std::string>::iterator i = msg.map.begin(); i != msg.map.end(); i++)
			{
				std::cout << i->first << " " << i->second << " ";
			}
			std::cout << "\n";
			dispatchMessage(msg);
			worldchanged = true;
		}
		if (worldchanged)
		{
			for (vector<Card*>::iterator i = CardList.begin(); i != CardList.end(); i++)
			{
				if ((*i)->Zone == ZONE_BATTLE)
				{
					(*i)->updatePower(getCreaturePower((*i)->UniqueId));
				}
			}
		}
	}
}

void Duel::dispatchMessage(Message& msg)
{
	string type = msg.getString("msgtype");
	vector<Card*>::iterator i;

	currentMessage = msg;

	currentMessage.addValue("msgtype", "mod " + type);
	for (i = battlezones[turn].cards.begin(); i != battlezones[turn].cards.end(); i++)
	{
		(*i)->handleMessage(msg);
	}
	for (i = battlezones[getOpponent(turn)].cards.begin(); i != battlezones[getOpponent(turn)].cards.end(); i++)
	{
		(*i)->handleMessage(msg);
	}

	//std::cout << "  mod\n";
	if (currentMessage.getInt("msgContinue") == 0) //do we continue?
		return;

	currentMessage.addValue("msgtype", "pre " + type);
	for (i = battlezones[turn].cards.begin(); i != battlezones[turn].cards.end(); i++)
	{
		(*i)->handleMessage(msg);
	}
	for (i = battlezones[getOpponent(turn)].cards.begin(); i != battlezones[getOpponent(turn)].cards.end(); i++)
	{
		(*i)->handleMessage(msg);
	}

	//std::cout << "  pre\n";
	if (currentMessage.getInt("msgContinue") == 0)
		return;

	currentMessage.addValue("msgtype", type);
	handleMessage(currentMessage);
	//std::cout << "  in\n";

	currentMessage.addValue("msgtype", "post " + type);
	for (i = battlezones[turn].cards.begin(); i != battlezones[turn].cards.end(); i++)
	{
		(*i)->handleMessage(msg);
	}
	for (i = battlezones[getOpponent(turn)].cards.begin(); i != battlezones[getOpponent(turn)].cards.end(); i++)
	{
		(*i)->handleMessage(msg);
	}

	//std::cout << "  post\n";
}

void Duel::addChoice(string info, int skip, int card)
{
	choice = Choice(info, skip);
	choiceCard = card;
	isChoiceActive = true;
}

int Duel::choiceCanBeSelected(int sid)
{
	return choice.callvalid(choiceCard, sid);
}

void Duel::checkChoiceValid()
{
	int count = 0;
	for (vector<Card*>::iterator i = CardList.begin(); i != CardList.end(); i++)
	{
		if (choiceCanBeSelected((*i)->UniqueId) == 1)
		{
			count++;
		}
	}
	if (count == 0) //no valid targets
	{
		resetChoice();
	}
}

void Duel::battle(int att, int def)
{
	Card* a = CardList.at(att);
	Card* d = CardList.at(def);
	int p1 = getCreaturePower(a->UniqueId);
	int p2 = getCreaturePower(d->UniqueId);
	if (p1 >= p2)
	{
		Message msg("carddestroy");
		msg.addValue("card", def);
		msg.addValue("zoneto", ZONE_GRAVEYARD);
		MsgMngr.sendMessage(msg);
	}
	if (p2 >= p1)
	{
		Message msg("carddestroy");
		msg.addValue("card", att);
		msg.addValue("zoneto", ZONE_GRAVEYARD);
		MsgMngr.sendMessage(msg);
	}
}

int Duel::getCreaturePower(int uid)
{
	Message oldmsg = currentMessage;
	currentMessage = Message("get creaturepower");
	currentMessage.addValue("power", CardList.at(uid)->Power);
	currentMessage.addValue("creature", uid);

	vector<Card*>::iterator i;
	for (i = CardList.begin(); i != CardList.end(); i++)
	{
		(*i)->handleMessage(currentMessage);
	}
	int c = currentMessage.getInt("power");
	currentMessage = oldmsg;
	return c;
}

int Duel::getCreatureBreaker(int uid)
{
	Message oldmsg = currentMessage;
	currentMessage = Message("get creaturebreaker");
	currentMessage.addValue("breaker", CardList.at(uid)->Breaker);
	currentMessage.addValue("creature", uid);

	vector<Card*>::iterator i;
	for (i = CardList.begin(); i != CardList.end(); i++)
	{
		(*i)->handleMessage(currentMessage);
	}
	int c = currentMessage.getInt("breaker");
	currentMessage = oldmsg;
	return c;
}

//int Duel::getCreatureCanAttack(int uid)
//{
//	Message oldmsg = currentMessage;
//	currentMessage = Message("get creaturecanattack");
//	currentMessage.addValue("canattack", 1);
//	currentMessage.addValue("creature", uid);
//
//	vector<Card*>::iterator i;
//	for (i = CardList.begin(); i != CardList.end(); i++)
//	{
//		(*i)->handleMessage(currentMessage);
//	}
//	int c = currentMessage.getInt("canattack");
//	currentMessage = oldmsg;
//	return c;
//}

//int Duel::getCreatureCanBeAttacked(int uid)
//{
//	Message oldmsg = currentMessage;
//	currentMessage = Message("get creaturecanbeattacked");
//	currentMessage.addValue("canbeattacked", 1);
//	currentMessage.addValue("creature", uid);
//
//	vector<Card*>::iterator i;
//	for (i = CardList.begin(); i != CardList.end(); i++)
//	{
//		(*i)->handleMessage(currentMessage);
//	}
//	int c = currentMessage.getInt("canbeattacked");
//	currentMessage = oldmsg;
//	return c;
//}

int Duel::getCreatureIsBlocker(int uid)
{
	Message oldmsg = currentMessage;
	currentMessage = Message("get creatureisblocker");
	currentMessage.addValue("isblocker", CardList.at(uid)->isBlocker);
	currentMessage.addValue("creature", uid);

	vector<Card*>::iterator i;
	for (i = CardList.begin(); i != CardList.end(); i++)
	{
		(*i)->handleMessage(currentMessage);
	}
	int c = currentMessage.getInt("isblocker");
	currentMessage = oldmsg;
	return c;
}

int Duel::getCreatureCanBlock(int attckr,int blckr)
{
	Message oldmsg = currentMessage;
	currentMessage = Message("get creaturecanblock");
	currentMessage.addValue("canblock", CardList.at(blckr)->isBlocker);
	currentMessage.addValue("blocker", blckr);
	currentMessage.addValue("attacker", attckr);

	vector<Card*>::iterator i;
	for (i = CardList.begin(); i != CardList.end(); i++)
	{
		(*i)->handleMessage(currentMessage);
	}
	int c = currentMessage.getInt("canblock");
	currentMessage = oldmsg;
	return c;
}

//int Duel::getCreatureCanBeBlocked(int uid)
//{
//	Message oldmsg = currentMessage;
//	currentMessage = Message("get creaturecanbeblocked");
//	currentMessage.addValue("canbeblocked", 1);
//	currentMessage.addValue("creature", uid);
//
//	vector<Card*>::iterator i;
//	for (i = CardList.begin(); i != CardList.end(); i++)
//	{
//		(*i)->handleMessage(currentMessage);
//	}
//	int c = currentMessage.getInt("canbeblocked");
//	currentMessage = oldmsg;
//	return c;
//}

int Duel::getCreatureCanAttackPlayer(int attckr,int plyr)
{
	Message oldmsg = currentMessage;
	currentMessage = Message("get creaturecanattackplayer");
	currentMessage.addValue("canattackplayer", 1);
	currentMessage.addValue("attacker", attckr);
	currentMessage.addValue("player", plyr);

	vector<Card*>::iterator i;
	for (i = CardList.begin(); i != CardList.end(); i++)
	{
		(*i)->handleMessage(currentMessage);
	}
	int c = currentMessage.getInt("canattackplayer");
	currentMessage = oldmsg;
	return c;
}

int Duel::getCreatureCanAttackCreature(int attckr,int dfndr)
{
	Message oldmsg = currentMessage;
	currentMessage = Message("get creaturecanattackcreatures");
	currentMessage.addValue("canattackcreature", 1);
	currentMessage.addValue("attacker", attckr);
	currentMessage.addValue("defender", attckr);

	vector<Card*>::iterator i;
	for (i = CardList.begin(); i != CardList.end(); i++)
	{
		(*i)->handleMessage(currentMessage);
	}
	int c = currentMessage.getInt("canattackcreature");
	currentMessage = oldmsg;
	return c;
}

//int Duel::getCreatureCanAttackUntappedCreatures(int uid)
//{
//	Message oldmsg = currentMessage;
//	currentMessage = Message("get creaturecanattackuntappedcreatures");
//	currentMessage.addValue("canattackuntappedcreatures", 0);
//	currentMessage.addValue("creature", uid);
//
//	vector<Card*>::iterator i;
//	for (i = CardList.begin(); i != CardList.end(); i++)
//	{
//		(*i)->handleMessage(currentMessage);
//	}
//	int c = currentMessage.getInt("canattackuntappedcreatures");
//	currentMessage = oldmsg;
//	return c;
//}

int Duel::getCardCost(int uid)
{
	Message oldmsg = currentMessage;
	currentMessage = Message("get cardcost");
	currentMessage.addValue("cost", CardList.at(uid)->ManaCost);
	currentMessage.addValue("card", uid);

	vector<Card*>::iterator i;
	for (i = CardList.begin(); i != CardList.end(); i++)
	{
		(*i)->handleMessage(currentMessage);
	}
	int c = currentMessage.getInt("cost");
	currentMessage = oldmsg;
	return c;
}

int Duel::getIsShieldTrigger(int uid)
{
	Message oldmsg = currentMessage;
	currentMessage = Message("get cardshieldtrigger");
	currentMessage.addValue("shieldtrigger", CardList.at(uid)->isShieldTrigger);
	currentMessage.addValue("card", uid);

	vector<Card*>::iterator i;
	for (i = CardList.begin(); i != CardList.end(); i++)
	{
		(*i)->handleMessage(currentMessage);
	}
	int c = currentMessage.getInt("shieldtrigger");
	currentMessage = oldmsg;
	return c;
}

void Duel::drawCards(int player, int count)
{
	for (int i = 0; i < count; i++)
	{
		Message msg("cardmove");
		msg.addValue("card", decks[player].cards.at(decks[player].cards.size() - i - 1)->UniqueId);
		msg.addValue("to", ZONE_HAND);
		MsgMngr.sendMessage(msg);
	}
}

void Duel::setDecks(string p1, string p2)
{
	loadDeck(p1, 0);
	loadDeck(p2, 1);

	decks[0].x = ZONE2X;
	decks[1].x = ZONE2X;
	decks[0].y = CENTER - ZONEYOFFSET * 4;
	decks[1].y = CENTER + ZONEYOFFSET * 3;
}

void Duel::loadDeck(string s, int p)
{
	decks[p].cards.empty();
	fstream file;
	file.open(s, ios::in | ios::out);
	string str;

	while (!file.eof())
	{
		getline(file, str);
		if (str == "")
			continue;
		cout << "loading card " << str << endl;
		Card* c = new Card(nextUniqueId, getCardIdFromName(str), p);
		CardList.push_back(c);
		decks[p].addCard(c);
		nextUniqueId++;
	}

	file.close();
}

void Duel::startDuel()
{
	turn = 0;
	manaUsed = 0;
	for (int i = 0; i < 2; i++)
	{
		decks[i].shuffle();
		for (int j = 0; j < 5; j++)
		{
			/*Card* c = decks[i].draw();
			shields[i].addCard(c);*/
			Message msg("cardmove");
			msg.addValue("card", decks[i].cards.at(decks[i].cards.size() - 1 - j)->UniqueId);
			msg.addValue("to", ZONE_SHIELD);
			MsgMngr.sendMessage(msg);
		}
		for (int j = 0; j < 5; j++)
		{
			/*Card* c = decks[i].draw();
			hands[i].addCard(c);*/
			Message msg("cardmove");
			msg.addValue("card", decks[i].cards.at(decks[i].cards.size() - 6 - j)->UniqueId);
			msg.addValue("to", ZONE_HAND);
			MsgMngr.sendMessage(msg);
		}
	}
}

void Duel::nextTurn()
{
	Message msg("endturn");
	msg.addValue("player", turn);
	MsgMngr.sendMessage(msg);
}

void Duel::resetAttack()
{
	cout << "attackreset" << endl;
	attackphase = PHASE_NONE;
	attacker = -1;
	defender = -1;
	breakcount = -1;
	shieldtargets.clear();
}

void Duel::resetChoice()
{
	choiceCard = -1;
	isChoiceActive = false;
}

Zone* Duel::getZone(int player, int zone)
{
	if (zone == ZONE_BATTLE)
	{
		return &battlezones[player];
	}
	else if (zone == ZONE_MANA)
	{
		return &manazones[player];
	}
	else if (zone == ZONE_HAND)
	{
		return &hands[player];
	}
	else if (zone == ZONE_DECK)
	{
		return &decks[player];
	}
	else if (zone == ZONE_SHIELD)
	{
		return &shields[player];
	}
	else if (zone == ZONE_GRAVEYARD)
	{
		return &graveyards[player];
	}
	return NULL;
}

void Duel::destroyCard(Card* c)
{
	//moveCard(c, ZONE_GRAVEYARD);
}

int getOpponent(int turn)
{
	return (turn + 1) % 2;
}
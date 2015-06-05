#include "LuaFunctions.h"

static int printstr(lua_State* L)
{
	std::cout << lua_tostring(L, 1);
	return 0;
}

static int printint(lua_State* L)
{
	std::cout << lua_tointeger(L, 1);
	return 0;
}

static int setMessageString(lua_State* L)
{
	ActiveDuel->duel.currentMessage.addValue(lua_tostring(L, 1), lua_tostring(L, 2));
	return 0;
}

static int setMessageInt(lua_State* L)
{
	ActiveDuel->duel.currentMessage.addValue(lua_tostring(L, 1), std::to_string(lua_tointeger(L, 2)));
	return 0;
}

static int getMessageString(lua_State* L)
{
	lua_pushstring(L, ActiveDuel->duel.currentMessage.getString(lua_tostring(L, 1)).c_str());
	return 1;
}

static int getMessageInt(lua_State* L)
{
	lua_pushinteger(L, ActiveDuel->duel.currentMessage.getInt(lua_tostring(L, 1)));
	return 1;
}

static int getMessageType(lua_State* L)
{
	lua_pushstring(L, ActiveDuel->duel.currentMessage.getType().c_str());
	return 1;
}

static int createChoice(lua_State* L)
{
	ActiveDuel->duel.dispatchAllMessages(); //first resolve all pending messages
	//lua_pushvalue(L, -1);
	lua_pushvalue(L, 5);
	int ref = luaL_ref(L, LUA_REGISTRYINDEX);
	cout << "ref: " << ref << endl;
	ActiveDuel->duel.addChoice(lua_tostring(L, 1), lua_tointeger(L, 2), lua_tointeger(L, 3), lua_tointeger(L, 4), ref);
	ActiveDuel->duel.checkChoiceValid();
	if (ActiveDuel->duel.isChoiceActive) //if choice is still active
	{
		int r = mainLoop(*Window, 1); //wait for selection made by user
		lua_pushinteger(L, r);
		return 1;
	}
	else
	{
		lua_pushinteger(L, RETURN_NOVALID);
	}
	luaL_unref(L, LUA_REGISTRYINDEX, ref);
	return 1;
}

static int createChoiceNoCheck(lua_State* L)
{
	ActiveDuel->duel.dispatchAllMessages(); //first resolve all pending messages
	//lua_pushvalue(L, -1);
	lua_pushvalue(L, 4);
	int ref = luaL_ref(L, LUA_REGISTRYINDEX);
	cout << "ref: " << ref << endl;
	ActiveDuel->duel.addChoice(lua_tostring(L, 1), lua_tointeger(L, 2), lua_tointeger(L, 3), lua_tointeger(L, 4), ref);
	//ActiveDuel->duel.checkChoiceValid();
	if (ActiveDuel->duel.isChoiceActive) //if choice is still active
	{
		int r = mainLoop(*Window, 1); //wait for selection made by user
		lua_pushinteger(L, r);
		return 1;
	}
	else
	{
		lua_pushinteger(L, RETURN_NOVALID);
	}
	luaL_unref(L, LUA_REGISTRYINDEX, ref);
	return 1;
}

static int setChoiceActive(lua_State* L)
{
	ActiveDuel->duel.isChoiceActive = lua_tointeger(L, 1);
	if (ActiveDuel->duel.isChoiceActive == false)
	{
		ActiveDuel->duel.choiceCard = -1;
	}
	return 0;
}

static int isChoiceActive(lua_State* L)
{
	lua_pushinteger(L, ActiveDuel->duel.isChoiceActive);
	return 1;
}

static int getChoice(lua_State* L)
{
	int r = mainLoop(*Window, 1);
	lua_pushinteger(L, r);
	return 1;
}

//static int destroyCard(lua_State* L)
//{
//	Message msg("carddestroy");
//	msg.addValue("card", lua_tointeger(L, 1));
//	msg.addValue("zoneto", ZONE_GRAVEYARD);
//	ActiveDuel->duel.MsgMngr.sendMessage(msg);
//	return 0;
//}

static int destroyCreature(lua_State* L)
{
	int cid = lua_tointeger(L, 1);
	Message msg("creaturedestroy");
	msg.addValue("creature", cid);
	msg.addValue("zoneto", ZONE_GRAVEYARD);
	ActiveDuel->duel.MsgMngr.sendMessage(msg);
	if (ActiveDuel->duel.CardList.at(cid)->Zone != ZONE_BATTLE)
	{
		cout << "WARNING: destroyCreature called on creature that is not in battle zone" << endl;
	}
	if (ActiveDuel->duel.CardList.at(cid)->Type != TYPE_CREATURE)
	{
		cout << "WARNING: destroyCreature called on card that is not a creature" << endl;
	}

	return 0;
}

static int discardCard(lua_State* L)
{
	int cid = lua_tointeger(L, 1);
	Message msg("carddiscard");
	msg.addValue("card", cid);
	msg.addValue("zoneto", ZONE_GRAVEYARD);
	ActiveDuel->duel.MsgMngr.sendMessage(msg);
	if (ActiveDuel->duel.CardList.at(cid)->Zone != ZONE_HAND)
	{
		cout << "WARNING: discardCard called on card that is not in hand" << endl;
	}
	return 0;
}

static int destroyMana(lua_State* L)
{
	int cid = lua_tointeger(L, 1);
	Message msg("manadestroy");
	msg.addValue("card", cid);
	msg.addValue("zoneto", ZONE_GRAVEYARD);
	ActiveDuel->duel.MsgMngr.sendMessage(msg);
	if (ActiveDuel->duel.CardList.at(cid)->Zone != ZONE_MANA)
	{
		cout << "WARNING: destroyMana called on card that is not in mana zone" << endl;
	}
	return 0;
}

static int discardCardAtRandom(lua_State* L)
{
	Message msg("carddiscardatrandom");
	msg.addValue("player", lua_tointeger(L, 1));
	ActiveDuel->duel.MsgMngr.sendMessage(msg);
	return 0;
}


static int moveCard(lua_State* L)
{
	Message msg("cardmove");
	msg.addValue("card", lua_tointeger(L, 1));
	msg.addValue("to", lua_tointeger(L, 2));
	ActiveDuel->duel.MsgMngr.sendMessage(msg);
	return 0;
}

static int tapCard(lua_State* L)
{
	Message msg("cardtap");
	msg.addValue("card", lua_tointeger(L, 1));
	ActiveDuel->duel.MsgMngr.sendMessage(msg);
	return 0;
}

static int untapCard(lua_State* L)
{
	Message msg("carduntap");
	msg.addValue("card", lua_tointeger(L, 1));
	ActiveDuel->duel.MsgMngr.sendMessage(msg);
	return 0;
}

static int drawCards(lua_State* L)
{
	int player = lua_tointeger(L, 1);
	int count = lua_tointeger(L, 2);
	ActiveDuel->duel.drawCards(player, count);
	return 0;
}

static int createModifier(lua_State* L)
{
	int uid = lua_tointeger(L, 1);
	lua_pushvalue(L, 2);
	int ref = luaL_ref(L, LUA_REGISTRYINDEX);
	/*Modifier m(ref);
	ActiveDuel->duel.CardList.at(uid)->modifiers.push_back(m);*/
	Message msg("modifiercreate");
	msg.addValue("card", uid);
	msg.addValue("funcref", ref);
	ActiveDuel->duel.MsgMngr.sendMessage(msg);
	return 0;
}

static int destroyModifier(lua_State* L)
{
	Message msg("modifierdestroy");
	msg.addValue("card", lua_tointeger(L, 1));
	msg.addValue("modifier", lua_tointeger(L, 2));
	ActiveDuel->duel.MsgMngr.sendMessage(msg);
	return 0;
}

static int shuffleDeck(lua_State* L)
{
	Message msg("deckshuffle");
	msg.addValue("player", lua_tointeger(L, 1));
	ActiveDuel->duel.MsgMngr.sendMessage(msg);
	return 0;
}

static int openDeck(lua_State* L)
{
	ActiveDuel->cardsearch.zone = ActiveDuel->duel.getZone(lua_tointeger(L, 1), ZONE_DECK);
	return 0;
}

static int closeDeck(lua_State* L)
{
	ActiveDuel->cardsearch.zone = NULL;
	return 0;
}

static int getCardAt(lua_State* L)
{
	int p = lua_tointeger(L, 1);
	int z = lua_tointeger(L, 2);
	
	lua_pushinteger(L, ActiveDuel->duel.getZone(p, z)->cards.at(lua_tointeger(L, 3))->UniqueId);

	return 1;
}

static int getTotalCardCount(lua_State* L)
{
	lua_pushinteger(L, ActiveDuel->duel.nextUniqueId);
	return 1;
}

static int getZoneSize(lua_State* L)
{
	int p = lua_tointeger(L, 1);
	int z = lua_tointeger(L, 2);
	
	lua_pushinteger(L, ActiveDuel->duel.getZone(p, z)->cards.size());

	return 1;
}

static int getTurn(lua_State* L)
{
	lua_pushinteger(L, ActiveDuel->duel.turn);
	return 1;
}

static int getCardName(lua_State* L)
{
	lua_pushstring(L, ActiveDuel->duel.CardList.at(lua_tointeger(L, 1))->Name.c_str());
	return 1;
}

static int getCardZone(lua_State* L)
{
	lua_pushinteger(L, ActiveDuel->duel.CardList.at(lua_tointeger(L, 1))->Zone);
	return 1;
}

static int getCardCiv(lua_State* L)
{
	lua_pushinteger(L, ActiveDuel->duel.CardList.at(lua_tointeger(L, 1))->Civilization);
	return 1;
}

static int getCardType(lua_State* L)
{
	lua_pushinteger(L, ActiveDuel->duel.CardList.at(lua_tointeger(L, 1))->Type);
	return 1;
}

static int getCardRace(lua_State* L)
{
	lua_pushstring(L, ActiveDuel->duel.CardList.at(lua_tointeger(L, 1))->Race.c_str());
	return 1;
}

static int getCardOwner(lua_State* L)
{
	lua_pushinteger(L, ActiveDuel->duel.CardList.at(lua_tointeger(L, 1))->Owner);
	return 1;
}

static int getCreaturePower(lua_State* L)
{
	lua_pushinteger(L, ActiveDuel->duel.getCreaturePower(lua_tointeger(L, 1)));
	return 1;
}

static int getCreatureCanBlock(lua_State* L)
{
	lua_pushinteger(L, ActiveDuel->duel.getCreatureCanBlock(lua_tointeger(L, 1),lua_tointeger(L,2)));
	return 1;
}

static int getCreatureIsBlocker(lua_State* L)
{
	lua_pushinteger(L, ActiveDuel->duel.getCreatureIsBlocker(lua_tointeger(L, 1)));
	return 1;
}

static int isCardTapped(lua_State* L)
{
	lua_pushinteger(L, ActiveDuel->duel.CardList.at(lua_tointeger(L, 1))->isTapped);
	return 1;
}

static int getAttacker(lua_State* L)
{
	lua_pushinteger(L, ActiveDuel->duel.attacker);
	return 1;
}

static int getDefender(lua_State* L)
{
	lua_pushinteger(L, ActiveDuel->duel.defender);
	return 1;
}

void registerLua(lua_State* L)
{
	lua_register(L, "printstr", printstr);
	lua_register(L, "printint", printint);

	lua_register(L, "setMessageString", setMessageString);
	lua_register(L, "setMessageInt", setMessageInt);
	lua_register(L, "getMessageString", getMessageString);
	lua_register(L, "getMessageInt", getMessageInt);
	lua_register(L, "getMessageType", getMessageType);

	lua_register(L, "createChoice", createChoice);
	lua_register(L, "createChoiceNoCheck", createChoiceNoCheck);
	lua_register(L, "setChoiceActive", setChoiceActive);
	lua_register(L, "isChoiceActive", isChoiceActive);
	lua_register(L, "getChoice", getChoice);

	lua_register(L, "createModifier", createModifier);
	lua_register(L, "destroyModifier", destroyModifier);
	
	lua_register(L, "destroyCreature", destroyCreature);
	lua_register(L, "discardCard", discardCard);
	lua_register(L, "destroyMana", destroyMana);
	lua_register(L, "discardCardAtRandom", discardCardAtRandom);
	lua_register(L, "moveCard", moveCard);
	lua_register(L, "tapCard", tapCard);
	lua_register(L, "untapCard", untapCard);
	lua_register(L, "drawCards", drawCards);
	lua_register(L, "createModifier", createModifier);
	lua_register(L, "destroyModifier", destroyModifier);
	lua_register(L, "shuffleDeck", shuffleDeck);
	lua_register(L, "openDeck", openDeck);
	lua_register(L, "closeDeck", closeDeck);

	lua_register(L, "getCardAt", getCardAt);
	lua_register(L, "getTotalCardCount", getTotalCardCount);
	lua_register(L, "getZoneSize", getZoneSize);
	lua_register(L, "getTurn", getTurn);
	lua_register(L, "getCardName", getCardName);
	lua_register(L, "getCardZone", getCardZone);
	lua_register(L, "getCardCiv", getCardCiv);
	lua_register(L, "getCardType", getCardType);
	lua_register(L, "getCardRace", getCardRace);
	lua_register(L, "getCardOwner", getCardOwner);
	lua_register(L, "getCreaturePower", getCreaturePower);
	lua_register(L, "getCreatureCanBlock", getCreatureCanBlock);
	lua_register(L, "getCreatureIsBlocker", getCreatureIsBlocker);
	lua_register(L, "isCardTapped", isCardTapped);
	lua_register(L, "getAttacker", getAttacker);
	lua_register(L, "getDefender", getDefender);
}
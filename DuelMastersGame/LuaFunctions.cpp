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
	ActiveDuel->duel.addChoice(lua_tostring(L, 1), lua_tointeger(L, 2), lua_tointeger(L, 3));
	return 0;
}

static int choicePushSelect(lua_State* L)
{
	int count = lua_tointeger(L, 1);
	for (int i = 2; i <= count + 1; i++)
	{
		ActiveDuel->duel.choice.pushselect(lua_tostring(L, i));
	}
	return 0;
}

static int choicePushButton1(lua_State* L)
{
	int count = lua_tointeger(L, 1);
	for (int i = 2; i <= count + 1; i++)
	{
		ActiveDuel->duel.choice.pushbutton1(lua_tostring(L, i));
	}
	return 0;
}

static int choicePushButton2(lua_State* L)
{
	int count = lua_tointeger(L, 1);
	for (int i = 2; i <= count + 1; i++)
	{
		ActiveDuel->duel.choice.pushbutton2(lua_tostring(L, i));
	}
	return 0;
}

static int choicePushValid(lua_State* L)
{
	int count = lua_tointeger(L, 1);
	for (int i = 2; i <= count + 1; i++)
	{
		ActiveDuel->duel.choice.pushvalid(lua_tostring(L, i));
	}
	ActiveDuel->duel.checkChoiceValid();
	return 0;
}

static int choicePushValidNoCheck(lua_State* L)
{
	int count = lua_tointeger(L, 1);
	for (int i = 2; i <= count + 1; i++)
	{
		ActiveDuel->duel.choice.pushvalid(lua_tostring(L, i));
	}
	//ActiveDuel->duel.checkChoiceValid();
	return 0;
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

static int destroyCard(lua_State* L)
{
	Message msg("carddestroy");
	msg.addValue("card", lua_tointeger(L, 1));
	msg.addValue("zoneto", ZONE_GRAVEYARD);
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
	int count = lua_tointeger(L, 2);
	Modifier m;
	for (int i = 3; i <= count + 2; i++)
	{
		m.pushfunc(lua_tostring(L, i));
	}
	ActiveDuel->duel.CardList.at(uid)->modifiers.push_back(m);
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

static int getCardAt(lua_State* L)
{
	int p = lua_tointeger(L, 1);
	int z = lua_tointeger(L, 2);
	
	lua_pushinteger(L, ActiveDuel->duel.getZone(p, z)->cards.at(lua_tointeger(L, 3))->UniqueId);

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
	lua_register(L, "choicePushSelect", choicePushSelect);
	lua_register(L, "choicePushButton1", choicePushButton1);
	lua_register(L, "choicePushButton2", choicePushButton2);
	lua_register(L, "choicePushValid", choicePushValid);
	lua_register(L, "choicePushValidNoCheck", choicePushValidNoCheck);
	lua_register(L, "setChoiceActive", setChoiceActive);

	lua_register(L, "createModifier", createModifier);
	lua_register(L, "destroyModifier", destroyModifier);
	
	lua_register(L, "destroyCard", destroyCard);
	lua_register(L, "moveCard", moveCard);
	lua_register(L, "tapCard", tapCard);
	lua_register(L, "untapCard", untapCard);
	lua_register(L, "drawCards", drawCards);
	lua_register(L, "createModifier", createModifier);
	lua_register(L, "destroyModifier", destroyModifier);
	lua_register(L, "shuffleDeck", shuffleDeck);

	lua_register(L, "getCardAt", getCardAt);
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
	lua_register(L, "isCardTapped", isCardTapped);
	lua_register(L, "getAttacker", getAttacker);
	lua_register(L, "getDefender", getDefender);
}
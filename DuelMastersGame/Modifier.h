#pragma once

#include "DeckBuilder.h"

extern lua_State* LuaCards;

class Modifier
{
public:
	vector<string> func;

	Modifier();
	~Modifier();

	void pushfunc(string s);
	int handleMessage(int cid, int mid, Message& msg);
};


#include "Modifier.h"

lua_State* LuaCards;

Modifier::Modifier()
{
}

Modifier::~Modifier()
{
}

void Modifier::pushfunc(string s)
{
	func.push_back(s);
}

int Modifier::handleMessage(int cid, int mid, Message& msg)
{
	int size = func.size();
	if (size > 0)
	{
		lua_getglobal(LuaCards, func.at(0).c_str());
		for (int i = 1; i < size; i++)
		{
			lua_getfield(LuaCards, -1, func.at(i).c_str());
		}
		lua_pushinteger(LuaCards, cid);
		lua_pushinteger(LuaCards, mid);
		lua_pcall(LuaCards, 2, 0, 0);
		for (int i = 1; i < size; i++)
		{
			lua_pop(LuaCards, 1);
		}
	}
	return 0;
}

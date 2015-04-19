#include "Choice.h"

Choice::Choice() : infotext(""), canskip(true)
{
}

Choice::Choice(string info, int skip) : infotext(info), canskip(skip)
{
}

Choice::~Choice()
{
}

void Choice::pushselect(string s)
{
	selectfunc.push_back(s);
}

void Choice::pushskip(string s)
{
	skipfunc.push_back(s);
}

void Choice::pushvalid(string s)
{
	validfunc.push_back(s);
}

void Choice::callselect(int cid, int sid)
{
	int size = selectfunc.size();
	if (size > 0)
	{
		lua_getglobal(LuaCards, selectfunc.at(0).c_str());
		for (int i = 1; i < size; i++)
		{
			lua_getfield(LuaCards, -1, selectfunc.at(i).c_str());
		}
		lua_pushinteger(LuaCards, cid);
		lua_pushinteger(LuaCards, sid);
		lua_pcall(LuaCards, 2, 0, 0);
		for (int i = 1; i < size; i++)
		{
			lua_pop(LuaCards, 1);
		}
	}
}

void Choice::callskip(int cid)
{
	int size = skipfunc.size();
	if (size > 0)
	{
		lua_getglobal(LuaCards, skipfunc.at(0).c_str());
		for (int i = 1; i < size; i++)
		{
			lua_getfield(LuaCards, -1, skipfunc.at(i).c_str());
		}
		lua_pushinteger(LuaCards, cid);
		lua_pcall(LuaCards, 1, 0, 0);
		for (int i = 1; i < size; i++)
		{
			lua_pop(LuaCards, 1);
		}
	}
}

int Choice::callvalid(int cid, int sid)
{
	int size = validfunc.size();
	int r = -1;
	if (size > 0)
	{
		lua_getglobal(LuaCards, validfunc.at(0).c_str());
		for (int i = 1; i < size; i++)
		{
			lua_getfield(LuaCards, -1, validfunc.at(i).c_str());
		}
		lua_pushinteger(LuaCards, cid);
		lua_pushinteger(LuaCards, sid);
		lua_pcall(LuaCards, 2, 1, 0);
		r = lua_tointeger(LuaCards, -1);
		lua_pop(LuaCards, 1);
		for (int i = 1; i < size; i++)
		{
			lua_pop(LuaCards, 1);
		}
	}
	if (r == -1)
	{
		cout << "ERROR callvalid returning -1" << endl;
	}
	return r;
}


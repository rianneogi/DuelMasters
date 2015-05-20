#include "Choice.h"

Choice::Choice() : infotext(""), buttoncount(0)
{
}

Choice::Choice(string info, int bcount, int vr) : infotext(info), buttoncount(bcount), validref(vr)
{
	cout << "refch: " << vr << endl;
}

Choice::~Choice()
{
}

void Choice::pushselect(string s)
{
	selectfunc.push_back(s);
}

void Choice::pushbutton1(string s)
{
	button1.push_back(s);
}

void Choice::pushbutton2(string s)
{
	button2.push_back(s);
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

void Choice::callbutton1(int cid)
{
	int size = button1.size();
	if (size > 0)
	{
		lua_getglobal(LuaCards, button1.at(0).c_str());
		for (int i = 1; i < size; i++)
		{
			lua_getfield(LuaCards, -1, button1.at(i).c_str());
		}
		lua_pushinteger(LuaCards, cid);
		lua_pcall(LuaCards, 1, 0, 0);
		for (int i = 1; i < size; i++)
		{
			lua_pop(LuaCards, 1);
		}
	}
}

void Choice::callbutton2(int cid)
{
	int size = button2.size();
	if (size > 0)
	{
		lua_getglobal(LuaCards, button2.at(0).c_str());
		for (int i = 1; i < size; i++)
		{
			lua_getfield(LuaCards, -1, button2.at(i).c_str());
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
	//int size = validfunc.size();
	//int r = -1;
	/*if (size > 0)
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
	return r;*/

	int r = -1;
	lua_rawgeti(LuaCards, LUA_REGISTRYINDEX, validref);
	cout << "Callid validref " << validref << endl;
	lua_pushinteger(LuaCards, cid);
	lua_pushinteger(LuaCards, sid);
	lua_pcall(LuaCards, 2, 1, 0);
	r = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);
	cout << " r is " << r << endl;
	if (r == -1)
	{
		cout << "ERROR callvalid returning -1" << endl;
	}
	return r;
}


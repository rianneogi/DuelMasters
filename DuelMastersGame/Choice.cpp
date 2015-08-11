#include "Choice.h"

Choice::Choice() : infotext(""), buttoncount(0)
{
}

Choice::Choice(string info, int bcount, int vr, int ar) : infotext(info), buttoncount(bcount), validref(vr), actionref(ar), isCopy(false)
{
}

Choice::~Choice()
{
	if (!isCopy)
	{
		luaL_unref(LuaCards, LUA_REGISTRYINDEX, validref);
		luaL_unref(LuaCards, LUA_REGISTRYINDEX, actionref);
		cout << "unref " << validref << " " << actionref << endl;
	}
}

int Choice::callvalid(int cid, int sid)
{
	int r = -1;
	lua_rawgeti(LuaCards, LUA_REGISTRYINDEX, validref);
	lua_pushinteger(LuaCards, cid);
	lua_pushinteger(LuaCards, sid);
	lua_pcall(LuaCards, 2, 1, 0);
	r = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);
	if (r == -1)
	{
		cout << "ERROR callvalid returning -1" << endl;
	}
	return r;
}

void Choice::callaction(int cid, int sid)
{
	lua_rawgeti(LuaCards, LUA_REGISTRYINDEX, actionref);
	lua_pushinteger(LuaCards, cid);
	lua_pushinteger(LuaCards, sid);
	lua_pcall(LuaCards, 2, 0, 0);
}

void Choice::copyFrom(Choice* c)
{
	infotext = c->infotext;
	buttoncount = c->buttoncount;
	validref = c->validref;
	actionref = c->actionref;
	isCopy = true;
}


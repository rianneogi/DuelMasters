#include "Modifier.h"

lua_State* LuaCards;

Modifier::Modifier()
{
}

Modifier::Modifier(int ref) : funcref(ref)
{
	cout << "ref mod: " << funcref << endl;
}

Modifier::~Modifier()
{
	cout << "unref mod: " << funcref << endl;
	luaL_unref(LuaCards, LUA_REGISTRYINDEX, funcref);
}

void Modifier::setfunc(int ref)
{
	cout << "ref mod: " << funcref << endl;
	funcref = ref;
}

int Modifier::handleMessage(int cid, int mid, Message& msg)
{
	/*int size = func.size();
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
	return 0;*/

	lua_rawgeti(LuaCards, LUA_REGISTRYINDEX, funcref);
	lua_pushinteger(LuaCards, cid);
	lua_pushinteger(LuaCards, mid);
	lua_pcall(LuaCards, 2, 0, 0);
	return 0;
}

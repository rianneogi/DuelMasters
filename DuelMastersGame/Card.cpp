#include "Card.h"

Card::Card() : UniqueId(-1), CardId(0), x(0), y(0), Owner(0)
{
	isFlipped[0] = false;
	isFlipped[1] = false;
	isTapped = false;
	summoningSickness = 1;
}

Card::Card(int uid, int cid, int owner) : UniqueId(uid),CardId(cid), Owner(owner), x(0), y(0)
{
	if (uid == -1)
		cout << "ERROR unit id = -1" << endl;

	lua_getglobal(LuaCards, "Cards");
	lua_getfield(LuaCards, -1, CardNames.at(cid).c_str());

	lua_getfield(LuaCards, -1, "name");
	Name = lua_tostring(LuaCards, -1);
	lua_pop(LuaCards, 1);

	lua_getfield(LuaCards, -1, "type");
	Type = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);

	lua_getfield(LuaCards, -1, "shieldtrigger");
	isShieldTrigger = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);

	if (Type==TYPE_CREATURE)
	{
		lua_getfield(LuaCards, -1, "race");
		Race = lua_tostring(LuaCards, -1);
		lua_pop(LuaCards, 1);

		lua_getfield(LuaCards, -1, "power");
		Power = lua_tointeger(LuaCards, -1);
		//displayPower = Power;
		lua_pop(LuaCards, 1);

		lua_getfield(LuaCards, -1, "breaker");
		Breaker = lua_tointeger(LuaCards, -1);
		lua_pop(LuaCards, 1);

		lua_getfield(LuaCards, -1, "blocker");
		isBlocker = lua_tointeger(LuaCards, -1);
		lua_pop(LuaCards, 1);
	}
	else
	{
		Race = "";
		Power = 0;
		//displayPower = 0;
		Breaker = 0;
		isBlocker = 0;
	}

	lua_getfield(LuaCards, -1, "civilization");
	Civilization = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);

	lua_getfield(LuaCards, -1, "cost");
	ManaCost = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);

	lua_pop(LuaCards, 1);
	lua_pop(LuaCards, 1);

	isFlipped[0] = false;
	isFlipped[1] = false;
	isTapped = false;
	Zone = ZONE_DECK;
	summoningSickness = 1;

	sprite = sf::Sprite(CardTextures.at(CardId));
	sprite.setScale(CARD_SCALE, CARD_SCALE);
	sf::FloatRect v = sprite.getLocalBounds();
	sprite.setOrigin(v.width / 2, v.height / 2);
	powertext = sf::Text(std::to_string(Power), DefaultFont, 12);
	powertext.setStyle(sf::Text::Style::Bold);
	powertext.setFillColor(sf::Color::Black);
}

Card::~Card()
{
}

void Card::render(sf::RenderWindow& window, int myPlayer)
{
	//sprite.setPosition(x, y);
	if (isFlipped[myPlayer]==true)
		sprite.setTexture(Textures.at(TEXTURE_CARDBACK));
	else
		sprite.setTexture(CardTextures.at(CardId));
	window.draw(sprite);
	if (Zone == ZONE_BATTLE && Type == TYPE_CREATURE)
	{
		window.draw(powertext);
	}
}

void Card::copyFrom(Card* c)
{
	UniqueId = c->UniqueId;
	CardId = c->CardId;
	x = c->x;
	y = c->y;

}

void Card::handleEvent(sf::Event event)
{

}

int Card::handleMessage(Message& msg)
{
	lua_getglobal(LuaCards, "Cards");
	lua_getfield(LuaCards, -1, CardNames.at(CardId).c_str());
	lua_getfield(LuaCards, -1, "HandleMessage");
	lua_pushinteger(LuaCards, UniqueId);
	lua_pcall(LuaCards, 1, 0, 0);
	//sendMessageToBuffs(msg);
	lua_pop(LuaCards, 1);
	lua_pop(LuaCards, 1);

	int cnt = 0;
	for (vector<Modifier*>::iterator i = modifiers.begin(); i != modifiers.end(); i++, cnt++)
	{
		(*i)->handleMessage(UniqueId, cnt, msg);
	}

	return 0;
}

void Card::callOnCast()
{
	lua_getglobal(LuaCards, "Cards");
	lua_getfield(LuaCards, -1, CardNames.at(CardId).c_str());
	lua_getfield(LuaCards, -1, "OnCast");
	lua_pushinteger(LuaCards, UniqueId);
	lua_pcall(LuaCards, 1, 0, 0);
	lua_pop(LuaCards, 1);
	lua_pop(LuaCards, 1);
}

void Card::move(int _x, int _y)
{
	x = _x;
	y = _y;
	sprite.setPosition(_x, _y);
	powertext.setPosition(_x - 15, _y + 25);
}

void Card::setPosition(int _x, int _y)
{
	x = _x;
	y = _y;
	sprite.setPosition(_x, _y);
	powertext.setPosition(_x - 15, _y + 25);
}

void Card::updatePower(int pow)
{
	powertext.setString(std::to_string(pow));
}

void Card::flip()
{
	isFlipped[0] = true;
	isFlipped[1] = true;
	//sprite.setTexture(Textures.at(TEXTURE_CARDBACK));
}

void Card::unflip()
{
	isFlipped[0] = false;
	isFlipped[1] = false;
	//sprite.setTexture(CardTextures.at(CardId));
}

void Card::flipForPlayer(int p)
{
	isFlipped[p] = true;
	/*if (p==myPlayer)
		sprite.setTexture(Textures.at(TEXTURE_CARDBACK));*/
}

void Card::unflipForPlayer(int p)
{
	isFlipped[p] = false;
	/*if (p == myPlayer)
		sprite.setTexture(CardTextures.at(CardId));*/
}

void Card::tap()
{
	isTapped = true;
	sprite.setRotation(90);
}

void Card::untap()
{
	isTapped = false;
	sprite.setRotation(0);
}

sf::FloatRect Card::getBounds()
{
	return sprite.getGlobalBounds();
}


int getCardIdFromName(string s)
{
	for (int i = 0; i < CardNames.size(); i++)
	{
		if (CardNames.at(i) == s)
		{
			return i;
		}
	}
	return -1;
}

static int loadcard(lua_State* L)
{
	string name = lua_tostring(L, 1);
	string set = lua_tostring(L, 2);

	std::cout << "Loading Card : " << name << "\n";

	CardNames.push_back(name);

	lua_getglobal(LuaCards, "Cards");
	lua_getfield(LuaCards, -1, name.c_str());

	lua_getfield(LuaCards, -1, "type");
	int type = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);

	string race = "";
	int power = 0;

	if (type == TYPE_CREATURE)
	{
		lua_getfield(LuaCards, -1, "race");
		race = lua_tostring(LuaCards, -1);
		lua_pop(LuaCards, 1);

		lua_getfield(LuaCards, -1, "power");
		power = lua_tointeger(LuaCards, -1);
		lua_pop(LuaCards, 1);
	}

	lua_getfield(LuaCards, -1, "civilization");
	int civ = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);

	lua_getfield(LuaCards, -1, "cost");
	int cost = lua_tointeger(LuaCards, -1);
	lua_pop(LuaCards, 1);

	lua_pop(LuaCards, 1);
	lua_pop(LuaCards, 1);

	CardData cd(CardDatabase.size(), name, set, race, civ, type, cost, power);
	CardDatabase.push_back(cd);

	name = "Graphics\\" + set + "\\" + name + ".png";
	CardTextures.push_back(sf::Texture());
	if (!CardTextures.at(CardTextures.size() - 1).loadFromFile(name))
	{
		cout << "ERROR cant load texture " << CardNames.at(CardNames.size() - 1) << endl;
	}
	CardTextures.at(CardTextures.size() - 1).setSmooth(true);
	return 0;
}

int initCards()
{
	std::cout << "Loading Cards...\n";
	LuaCards = luaL_newstate(); //create new lua state
	luaL_openlibs(LuaCards);

	lua_register(LuaCards, "loadcard", loadcard); //register loadcard
	registerLua(LuaCards); //register functions

	if (luaL_loadfile(LuaCards, "Lua\\Cards.lua") || lua_pcall(LuaCards, 0, 0, 0))
	{
		std::cout << "Error: failed to load Cards.lua" << std::endl;
		std::cout << lua_tostring(LuaCards, -1) << "\n";
		_getch();
		return -1;
	}

	lua_getglobal(LuaCards, "loadCards");
	lua_pcall(LuaCards, 0, 0, 0); //execute once to load units
	lua_pop(LuaCards, 1);

	return 0;
}

void cleanupCards()
{
	lua_close(LuaCards);
}
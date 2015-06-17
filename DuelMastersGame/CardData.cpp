#include "CardData.h"

vector<CardData> CardDatabase;

CardData::CardData()
{
}

CardData::CardData(int id, string n, string s, string r, int civ, int type, int cost, int power) : CardId(id), Name(n), Set(s), Race(r), Civilization(civ), Type(type), ManaCost(cost), Power(power)
{
}

CardData::~CardData()
{
}

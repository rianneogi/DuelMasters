#pragma once

#include "Modifier.h"

class CardData
{
public:
	int CardId;
	string Name;
	string Set;
	string Race;
	int Civilization;
	int Type;
	int ManaCost;
	int Power;

	CardData();
	CardData(int id, string n, string s, string r, int civ, int type, int cost, int power);
	~CardData();
};

extern vector<CardData> CardDatabase;


#pragma once

#include "BattleZone.h"

class Choice
{
public:
	string infotext;
	int buttoncount;
	int validref;
	int actionref;

	bool isCopy;

	Choice();
	Choice(string info, int skip, int vr, int ar);
	~Choice();

	int callvalid(int cid, int sid);
	void callaction(int cid, int sid);
	void copyFrom(Choice* c);
};


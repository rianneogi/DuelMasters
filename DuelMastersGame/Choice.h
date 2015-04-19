#pragma once

#include "BattleZone.h"

class Choice
{
public:
	vector<string> selectfunc;
	vector<string> skipfunc;
	vector<string> validfunc;
	string infotext;
	int canskip;

	Choice();
	Choice(string info, int skip);
	~Choice();
	void pushselect(string s);
	void pushskip(string s);
	void pushvalid(string s);
	void callselect(int cid,int sid);
	void callskip(int cid);
	int callvalid(int cid, int sid);
};


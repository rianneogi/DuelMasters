#pragma once

#include "BattleZone.h"

class Choice
{
public:
	vector<string> selectfunc;
	vector<string> button1;
	vector<string> button2;
	vector<string> validfunc;
	string infotext;
	int buttoncount;

	Choice();
	Choice(string info, int skip);
	~Choice();

	void pushselect(string s);
	void pushbutton1(string s);
	void pushbutton2(string s);
	void pushvalid(string s);

	void callselect(int cid,int sid);
	void callbutton1(int cid);
	void callbutton2(int cid);
	int callvalid(int cid, int sid);
};


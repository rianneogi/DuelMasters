#pragma once

#include "FileFunctions.h"

class Message
{
public:
	Message();
	Message(std::string type);
	~Message();

	std::map<std::string,std::string> map;

	void addValue(std::string key,std::string value);
	void addValue(std::string key,int value);
	std::string getType();
	std::string getString(std::string key);
	int getInt(std::string key);
};


#include "Message.h"


Message::Message()
{
	map = std::map<std::string,std::string>();
}

Message::Message(std::string type)
{
	map["msgtype"] = type;
	map["msgContinue"] = "1";
}

Message::~Message()
{
}

void Message::addValue(std::string key,std::string value)
{
	map[key] = value;
}

void Message::addValue(std::string key,int value)
{
	map[key] = std::to_string(value);
}

std::string Message::getType()
{
	return map["msgtype"];
}

std::string Message::getString(std::string key)
{
	auto search = map.find(key);
	if(search!=map.end())
		return map[key];
	else
		std::cout << "ERROR unable to access value " << key << " in message " << getType() << "\n"; 
	return "";
}

int Message::getInt(std::string key)
{
	auto search = map.find(key);
	if(search!=map.end())
		return atoi(map[key].c_str());
	else
		std::cout << "ERROR unable to access value " << key << " in message " << getType() << "\n";
	return 0;
}
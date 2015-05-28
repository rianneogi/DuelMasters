#pragma once

#include "FileFunctions.h"

enum PacketType { PACKET_MSG, PACKET_SETDECK, PACKET_SETSEED, PACKET_CHOICESELECT };

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
	void clear();
};

sf::Packet& operator <<(sf::Packet& packet, const Message& m);
sf::Packet& operator >>(sf::Packet& packet, Message& m);
sf::Packet createPacketFromMessage(Message& m);


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

void Message::clear()
{
	map.clear();
}

sf::Packet& operator <<(sf::Packet& packet, const Message& m)
{
	sf::Uint32 size = m.map.size();
	packet << size;
	for (map<string, string>::const_iterator i = m.map.begin(); i != m.map.end(); i++)
	{
		packet << i->first << i->second;
	}
	return packet;
}

sf::Packet& operator >>(sf::Packet& packet, Message& m)
{
	m.clear();
	sf::Uint32 size;
	packet >> size;
	for (int i = 0; i < size; i++)
	{
		string a, b;
		packet >> a >> b;
		m.addValue(a, b);
	}
	return packet;
}

sf::Packet createPacketFromMessage(Message& m)
{
	sf::Packet p;
	p << m;
	return p;
}
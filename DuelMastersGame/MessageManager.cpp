#include "MessageManager.h"

MessageManager::MessageManager()
{
	messages = std::deque<Message>(0);
}

MessageManager::~MessageManager()
{
}

void MessageManager::sendMessage(const Message& msg)
{
	messages.push_back(msg);
}

Message MessageManager::peekMessage()
{
	Message msg = messages.at(0);
	return msg;
}

Message MessageManager::dispatch()
{
	Message msg = messages.at(0);
	messages.pop_front();
	return msg;
}

bool MessageManager::hasMoreMessages()
{
	if(messages.size()>0)
		return true;
	return false;
}

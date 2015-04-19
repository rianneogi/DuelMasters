#pragma once

#include <deque>
#include "Message.h"

class MessageManager
{
public:
	MessageManager();
	~MessageManager();

	std::deque<Message> messages;

	void sendMessage(const Message& msg);
	Message dispatch();
	Message peekMessage();
	bool hasMoreMessages();
};


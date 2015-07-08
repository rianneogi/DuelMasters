#pragma once

#include "Duel.h"

class AIInterface
{
public:
	Duel* duel;

	AIInterface();
	AIInterface(Duel* d);
	~AIInterface();

	vector<Message> getValidMoves();
	Message makeMove();
	int getPlayerToMove();
};


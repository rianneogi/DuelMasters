#pragma once

#include "Duel.h"

class AIInterface
{
public:
	Duel* duel;

	AIInterface();
	AIInterface(Duel* d);
	~AIInterface();

	vector<Message> getValidMoves(Duel* d);
	int Search(Duel* positions, int depth, int player);
	int AlphaBeta(Duel* positions, int depth, int player);
	Message makeMove();
	int Evaluate(Duel* pos, int player);
	int getPlayerToMove();
	int getPlayerToMove(Duel* d);
};


#include "AIInterface.h"


AIInterface::AIInterface()
{
}

AIInterface::AIInterface(Duel* d) : duel(d)
{
}

AIInterface::~AIInterface()
{
}

vector<Message> AIInterface::getValidMoves()
{
	return vector<Message>(0);
}

int AIInterface::getPlayerToMove()
{
	if (duel->isChoiceActive)
		return duel->choicePlayer;
	if (duel->attackphase == PHASE_BLOCK || duel->attackphase == PHASE_TRIGGER)
		return getOpponent(duel->turn);
	return duel->turn;
}

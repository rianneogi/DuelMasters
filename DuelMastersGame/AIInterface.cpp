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

Message AIInterface::makeMove()
{
	vector<Message> m = getValidMoves();
	if (m.size() == 0)
	{
		cout << "ERROR: valid moves size is 0" << endl;
		return Message("ERROR");
	}
	return (m.at(rand() % m.size()));
}

vector<Message> AIInterface::getValidMoves()
{
	vector<Message> moves(0);
	int player = getPlayerToMove();
	if (duel->turn == player && duel->attackphase == PHASE_NONE && !(duel->isChoiceActive) && duel->castingcard == -1)
	{
		Message m("endturn");
		m.addValue("player", duel->turn);
		moves.push_back(m);
	}
	else if (duel->isChoiceActive && player == duel->choicePlayer)
	{
		if (duel->choice.buttoncount > 0)
		{
			Message msg("choiceselect");
			msg.addValue("selection", RETURN_BUTTON1);
			moves.push_back(msg);
		}
		if (duel->choice.buttoncount > 1)
		{
			Message msg("choiceselect");
			msg.addValue("selection", RETURN_BUTTON2);
			moves.push_back(msg);
		}
		for (vector<Card*>::iterator i = duel->CardList.begin(); i != duel->CardList.end(); i++)
		{
			if ((*i)->Zone != ZONE_EVOLVED)
			{
				if (duel->choice.callvalid(duel->choiceCard, (*i)->UniqueId) == 1)
				{
					Message msg("choiceselect");
					msg.addValue("selection", (*i)->UniqueId);
					moves.push_back(msg);
				}
			}
		}
	}
	else if (duel->attackphase == PHASE_TRIGGER && player == getOpponent(duel->turn)) //use shield triggers
	{
		for (vector<Card*>::iterator i = duel->hands[getOpponent(duel->turn)].cards.begin(); i != duel->hands[getOpponent(duel->turn)].cards.end(); i++)
		{
			for (vector<int>::iterator j = duel->shieldtargets.begin(); j != duel->shieldtargets.end(); j++)
			{
				if (*j == (*i)->UniqueId)
				{
					Message msg("triggeruse");
					msg.addValue("trigger", (*i)->UniqueId);
					moves.push_back(msg);
				}
			}
		}
		Message m("triggerskip");
		moves.push_back(m);
	}
	else if (duel->attackphase == PHASE_TARGET && player == duel->turn) //target shields
	{
		for (vector<Card*>::iterator i = duel->shields[getOpponent(duel->turn)].cards.begin(); i != duel->shields[getOpponent(duel->turn)].cards.end(); i++)
		{
			Message m("targetshield");
			m.addValue("attacker", duel->attacker);
			m.addValue("shield", (*i)->UniqueId);
			moves.push_back(m);
		}
	}
	else if (duel->attackphase == PHASE_BLOCK && player == getOpponent(duel->turn)) //block
	{
		for (vector<Card*>::iterator i = duel->battlezones[getOpponent(duel->turn)].cards.begin(); i != duel->battlezones[getOpponent(duel->turn)].cards.end(); i++)
		{
			if (duel->getCreatureCanBlock(duel->attacker, (*i)->UniqueId) && (*i)->isTapped == false
				&& ((*i)->UniqueId != duel->defender || duel->defendertype == DEFENDER_PLAYER))
			{
				/*Message msg2("cardtap");
				msg2.addValue("card", (*i)->UniqueId);
				MsgMngr.sendMessage(msg2);*/

				Message msg("creatureblock");
				msg.addValue("attacker", duel->attacker);
				msg.addValue("blocker", (*i)->UniqueId);
				moves.push_back(msg);
			}
		}
		Message m("blockskip");
		moves.push_back(m);
	}
	else if (duel->castingcard != -1 && player == duel->turn) //tap mana
	{
		for (vector<Card*>::iterator i = duel->manazones[duel->turn].cards.begin(); i != duel->manazones[duel->turn].cards.end(); i++)
		{
			Message m("manatap");
			m.addValue("card", (*i)->UniqueId);
			moves.push_back(m);
		}
	}

	if (player == duel->turn && !duel->isChoiceActive)
	{
		for (vector<Card*>::iterator i = duel->hands[duel->turn].cards.begin(); i != duel->hands[duel->turn].cards.end(); i++)
		{
			if (duel->getCardCost((*i)->UniqueId) <= duel->manazones[duel->turn].getUntappedMana())
			{
				if (duel->getIsEvolution((*i)->UniqueId) == 1)
				{
					for (vector<Card*>::iterator j = duel->battlezones[duel->turn].cards.begin(); j != duel->battlezones[duel->turn].cards.end(); j++)
					{
						if (duel->getCreatureCanEvolve((*i)->UniqueId, (*j)->UniqueId) == 1)
						{
							Message msg("cardplay");
							msg.addValue("card", (*i)->UniqueId);
							msg.addValue("evobait", (*j)->UniqueId);
							moves.push_back(msg);
						}
					}
				}
				else
				{
					Message msg("cardplay");
					msg.addValue("card", (*i)->UniqueId);
					msg.addValue("evobait", -1);
					moves.push_back(msg);
				}
			}
			if (duel->manaUsed == 0)
			{
				Message msg("cardmana");
				msg.addValue("card", (*i)->UniqueId);
				moves.push_back(msg);
			}
		}
	}
	
	if (player == duel->turn && !duel->isChoiceActive)
	{
		for (vector<Card*>::iterator i = duel->battlezones[duel->turn].cards.begin(); i != duel->battlezones[duel->turn].cards.end(); i++)
		{
			int canattack = duel->getCreatureCanAttackPlayers((*i)->UniqueId);
			if ((canattack == CANATTACK_ALWAYS ||
				((duel->CardList.at((*i)->UniqueId)->summoningSickness == 0 || duel->getIsSpeedAttacker((*i)->UniqueId) == 1) && (canattack == CANATTACK_TAPPED || canattack == CANATTACK_UNTAPPED)))
				&& duel->CardList.at((*i)->UniqueId)->isTapped == false)
			{

				Message msg("creatureattack");
				msg.addValue("attacker", (*i)->UniqueId);
				msg.addValue("defender", getOpponent(duel->turn));
				msg.addValue("defendertype", DEFENDER_PLAYER);
				moves.push_back(msg);
			}
			for (vector<Card*>::iterator j = duel->battlezones[getOpponent(duel->turn)].cards.begin(); j != duel->battlezones[getOpponent(duel->turn)].cards.end(); j++)
			{
				int canattack = duel->getCreatureCanAttackCreature((*i)->UniqueId, (*j)->UniqueId);
				if (((*j)->isTapped == true || canattack == CANATTACK_UNTAPPED)
					&& canattack <= CANATTACK_UNTAPPED
					&& duel->CardList.at((*i)->UniqueId)->summoningSickness == 0
					&& duel->CardList.at((*i)->UniqueId)->isTapped == false)
				{

					Message msg("creatureattack");
					msg.addValue("attacker", (*i)->UniqueId);
					msg.addValue("defender", (*j)->UniqueId);
					msg.addValue("defendertype", DEFENDER_CREATURE);
					moves.push_back(msg);
				}
			}
		}
	}
	return moves;
}

int AIInterface::getPlayerToMove()
{
	if (duel->isChoiceActive)
		return duel->choicePlayer;
	if (duel->attackphase == PHASE_BLOCK || duel->attackphase == PHASE_TRIGGER)
		return getOpponent(duel->turn);
	return duel->turn;
}

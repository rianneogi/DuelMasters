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

int AIInterface::Search(Duel* pos, int depth)
{
	//Duel* lastpos
	if (depth == 0)
	{
		return (2 * pos->battlezones[pos->turn].cards.size() + pos->hands[pos->turn].cards.size()
			- 2 * pos->battlezones[getOpponent(pos->turn)].cards.size() - pos->hands[getOpponent(pos->turn)].cards.size());
	}
	int value = 0;
	for (int i = 0; i < 2; i++)
	{
		//Duel* d = new Duel(*pos);
		Duel* d = new Duel;
		d->RandomGen.SetRandomSeed(pos->RandomGen.GetRandomSeed());
		d->setDecks(pos->decknames[0], pos->decknames[1]);
		d->startDuel();
		cout << "move size: " << pos->MoveHistory.size() << endl;
		for (vector<Message>::iterator i = pos->MoveHistory.begin(); i != pos->MoveHistory.end(); i++)
		{
			d->handleInterfaceInput(*i);
			d->dispatchAllMessages();
		}
		if (d->hands[0].cards.size() != pos->hands[0].cards.size())
		{
			cout << "ERROR check not valid _______________" << d->hands[0].cards.size() << " " << pos->hands[0].cards.size() << endl;
		}
	
		for (int i = 0; i < depth; i++)
		{
			vector<Message> m = getValidMoves(d);
			if (m.size() == 0)
			{
				break;
			}
			Message mov = m.at(rand() % m.size());
			d->handleInterfaceInput(mov);
			d->dispatchAllMessages();
			cout << "move made: " << mov.getType() << endl;
		}
		value += (4 * d->battlezones[d->turn].cards.size() + 2 * d->manazones[d->turn].cards.size() + d->hands[d->turn].cards.size()
			- 4 * d->battlezones[getOpponent(d->turn)].cards.size() - 2 * d->manazones[getOpponent(d->turn)].cards.size() - d->hands[getOpponent(d->turn)].cards.size());
		
		if (d!=NULL)
			delete d;
	}

	return value;
}

Message AIInterface::makeMove()
{
	vector<Message> m = getValidMoves(duel);
	if (m.size() == 0)
	{
		return Message("AI NO VALID MOVES ERROR");
	}
	int max = -10000;
	Message maxmove("AI DEFAULT MOVE ERROR");
	for (vector<Message>::iterator i = m.begin(); i != m.end(); i++)
	{
		Duel* d = new Duel(*duel);
		d->handleInterfaceInput(*i);
		//positions.push_back(d);
		int x = Search(d, 2);
		//positions.pop_back();
		if (x > max)
		{
			maxmove = *i;
			max = x;
		}
	}
	cout << "AI maxmove value: " << max << endl;
	return maxmove;
}

//Message AIInterface::makeMove()
//{
//	vector<Message> m = getValidMoves();
//	if (m.size() == 0)
//	{
//		cout << "ERROR: valid moves size is 0" << endl;
//		return Message("ERROR");
//	}
//	return (m.at(rand() % m.size()));
//}

vector<Message> AIInterface::getValidMoves(Duel* d)
{
	vector<Message> moves(0);
	int player = getPlayerToMove();
	if (d->turn == player && d->attackphase == PHASE_NONE && !(d->isChoiceActive) && d->castingcard == -1)
	{
		Message m("endturn");
		m.addValue("player", d->turn);
		moves.push_back(m);
	}
	else if (d->isChoiceActive && player == d->choicePlayer)
	{
		if (d->choice.buttoncount > 0)
		{
			Message msg("choiceselect");
			msg.addValue("selection", RETURN_BUTTON1);
			moves.push_back(msg);
		}
		if (d->choice.buttoncount > 1)
		{
			Message msg("choiceselect");
			msg.addValue("selection", RETURN_BUTTON2);
			moves.push_back(msg);
		}
		for (vector<Card*>::iterator i = d->CardList.begin(); i != d->CardList.end(); i++)
		{
			if ((*i)->Zone != ZONE_EVOLVED)
			{
				if (d->choice.callvalid(d->choiceCard, (*i)->UniqueId) == 1)
				{
					Message msg("choiceselect");
					msg.addValue("selection", (*i)->UniqueId);
					moves.push_back(msg);
				}
			}
		}
	}
	else if (d->attackphase == PHASE_TRIGGER && player == getOpponent(d->turn)) //use shield triggers
	{
		for (vector<Card*>::iterator i = d->hands[getOpponent(d->turn)].cards.begin(); i != d->hands[getOpponent(d->turn)].cards.end(); i++)
		{
			for (vector<int>::iterator j = d->shieldtargets.begin(); j != d->shieldtargets.end(); j++)
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
	else if (d->attackphase == PHASE_TARGET && player == d->turn) //target shields
	{
		for (vector<Card*>::iterator i = d->shields[getOpponent(d->turn)].cards.begin(); i != d->shields[getOpponent(d->turn)].cards.end(); i++)
		{
			Message m("targetshield");
			m.addValue("attacker", d->attacker);
			m.addValue("shield", (*i)->UniqueId);
			moves.push_back(m);
		}
	}
	else if (d->attackphase == PHASE_BLOCK && player == getOpponent(d->turn)) //block
	{
		for (vector<Card*>::iterator i = d->battlezones[getOpponent(d->turn)].cards.begin(); i != d->battlezones[getOpponent(d->turn)].cards.end(); i++)
		{
			if (d->getCreatureCanBlock(d->attacker, (*i)->UniqueId) && (*i)->isTapped == false
				&& ((*i)->UniqueId != d->defender || d->defendertype == DEFENDER_PLAYER))
			{
				/*Message msg2("cardtap");
				msg2.addValue("card", (*i)->UniqueId);
				MsgMngr.sendMessage(msg2);*/

				Message msg("creatureblock");
				msg.addValue("attacker", d->attacker);
				msg.addValue("blocker", (*i)->UniqueId);
				moves.push_back(msg);
			}
		}
		Message m("blockskip");
		moves.push_back(m);
	}
	else if (d->castingcard != -1 && player == d->turn) //tap mana
	{
		for (vector<Card*>::iterator i = d->manazones[d->turn].cards.begin(); i != d->manazones[d->turn].cards.end(); i++)
		{
			Message m("manatap");
			m.addValue("card", (*i)->UniqueId);
			moves.push_back(m);
		}
	}

	if (player == d->turn && !d->isChoiceActive)
	{
		for (vector<Card*>::iterator i = d->hands[d->turn].cards.begin(); i != d->hands[d->turn].cards.end(); i++)
		{
			if (d->getCardCost((*i)->UniqueId) <= d->manazones[d->turn].getUntappedMana())
			{
				if (d->getIsEvolution((*i)->UniqueId) == 1)
				{
					for (vector<Card*>::iterator j = d->battlezones[d->turn].cards.begin(); j != d->battlezones[d->turn].cards.end(); j++)
					{
						if (d->getCreatureCanEvolve((*i)->UniqueId, (*j)->UniqueId) == 1)
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
			if (d->manaUsed == 0)
			{
				Message msg("cardmana");
				msg.addValue("card", (*i)->UniqueId);
				moves.push_back(msg);
			}
		}
	}
	
	if (player == d->turn && !d->isChoiceActive)
	{
		for (vector<Card*>::iterator i = d->battlezones[d->turn].cards.begin(); i != d->battlezones[d->turn].cards.end(); i++)
		{
			int canattack = d->getCreatureCanAttackPlayers((*i)->UniqueId);
			if ((canattack == CANATTACK_ALWAYS ||
				((d->CardList.at((*i)->UniqueId)->summoningSickness == 0 || d->getIsSpeedAttacker((*i)->UniqueId) == 1) && (canattack == CANATTACK_TAPPED || canattack == CANATTACK_UNTAPPED)))
				&& d->CardList.at((*i)->UniqueId)->isTapped == false)
			{

				Message msg("creatureattack");
				msg.addValue("attacker", (*i)->UniqueId);
				msg.addValue("defender", getOpponent(d->turn));
				msg.addValue("defendertype", DEFENDER_PLAYER);
				moves.push_back(msg);
			}
			for (vector<Card*>::iterator j = d->battlezones[getOpponent(d->turn)].cards.begin(); j != d->battlezones[getOpponent(d->turn)].cards.end(); j++)
			{
				int canattack = d->getCreatureCanAttackCreature((*i)->UniqueId, (*j)->UniqueId);
				if (((*j)->isTapped == true || canattack == CANATTACK_UNTAPPED)
					&& canattack <= CANATTACK_UNTAPPED
					&& d->CardList.at((*i)->UniqueId)->summoningSickness == 0
					&& d->CardList.at((*i)->UniqueId)->isTapped == false)
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

int AIInterface::getPlayerToMove(Duel* d)
{
	if (d->isChoiceActive)
		return d->choicePlayer;
	if (d->attackphase == PHASE_BLOCK || d->attackphase == PHASE_TRIGGER)
		return getOpponent(d->turn);
	return d->turn;
}

int AIInterface::getPlayerToMove()
{
	if (duel->isChoiceActive)
		return duel->choicePlayer;
	if (duel->attackphase == PHASE_BLOCK || duel->attackphase == PHASE_TRIGGER)
		return getOpponent(duel->turn);
	return duel->turn;
}

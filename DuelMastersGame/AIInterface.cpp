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

int AIInterface::Evaluate(Duel* pos, int player)
{
	return (5 * pos->shields[player].cards.size() + 4 * pos->battlezones[player].cards.size() + 2 * pos->manazones[player].cards.size() + pos->hands[player].cards.size()
		- 5 * pos->shields[getOpponent(player)].cards.size() - 4 * pos->battlezones[getOpponent(player)].cards.size() - 2 * pos->manazones[getOpponent(player)].cards.size()
		- pos->hands[getOpponent(player)].cards.size());
}

int AIInterface::Search(Duel* pos, int depth, int player)
{
	//Duel* lastpos
	if (depth == 0)
	{
		return Evaluate(pos, player);
	}
	int value = 0;
	for (int i = 0; i < 10; i++)
	{
		//Duel* d = new Duel(*pos);
		Duel* d = new Duel;
		ActiveDuel = d;
		d->isSimulation = true;
		d->RandomGen.SetRandomSeed(pos->RandomGen.GetRandomSeed());
		d->setDecks(pos->decknames[0], pos->decknames[1]);
		d->startDuel();
		d->dispatchAllMessages();
		cout << "AI: move size: " << pos->MoveHistory.size() << endl;
		for (vector<Message>::iterator i = pos->MoveHistory.begin(); i != pos->MoveHistory.end(); i++)
		{
			//cout << "AI sim move: " << (*i).getType() << endl;
			d->handleInterfaceInput(*i);
			d->dispatchAllMessages();
		}
		if (d->hands[0].cards.size() != pos->hands[0].cards.size())
		{
			cout << "AI: ERROR check not valid NON-ROOT " << d->hands[0].cards.size() << " " << pos->hands[0].cards.size() << endl;
			cout << d->MoveHistory.size() << " " << pos->MoveHistory.size() << endl;
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
			cout << "AI: move made: " << mov.getType() << endl;
		}
		value += Evaluate(d, player);
		
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
		return Message("AI: NO VALID MOVES ERROR");
	}
	if (m.size() == 1) //only 1 valid move
	{
		cout << "AI: only 1 legal move" << endl;
		return m.at(0);
	}
	if (duel->castingcard != -1) //auto-tap
	{
		return m.at(0);
	}
	Duel* oldDuel = ActiveDuel;
	int max = -10000;
	Message maxmove("AI: DEFAULT MOVE ERROR");
	for (vector<Message>::iterator i = m.begin(); i != m.end(); i++)
	{
		Duel* d = new Duel;
		ActiveDuel = d;
		d->isSimulation = true;
		d->RandomGen.SetRandomSeed(duel->RandomGen.GetRandomSeed());
		d->setDecks(duel->decknames[0], duel->decknames[1]);
		d->startDuel();
		d->dispatchAllMessages();
		cout << "AI: move size: " << duel->MoveHistory.size() << endl;
		for (vector<Message>::iterator j = duel->MoveHistory.begin(); j != duel->MoveHistory.end(); j++)
		{
			//cout << "AI sim move: " << (*j).getType() << endl;
			d->handleInterfaceInput(*j);
			d->dispatchAllMessages();
		}
		if (d->hands[0].cards.size() != duel->hands[0].cards.size())
		{
			cout << "AI: ERROR check not valid ROOT " << d->hands[0].cards.size() << " " << duel->hands[0].cards.size() << endl;
		}
		d->handleInterfaceInput(*i);
		d->dispatchAllMessages();
		//positions.push_back(d);
		int x = Search(d, 2, duel->turn);
		cout << "AI: value " << x << " for move: " << (*i).getType() << endl;
		//positions.pop_back();
		if (x > max)
		{
			maxmove = *i;
			max = x;
		}
		if (d!=NULL)
			delete d;
	}
	cout << "AI: maxmove value: " << max << endl;
	ActiveDuel = oldDuel;
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
		if (d->choice->buttoncount > 0)
		{
			Message msg("choiceselect");
			msg.addValue("selection", RETURN_BUTTON1);
			moves.push_back(msg);
		}
		if (d->choice->buttoncount > 1)
		{
			Message msg("choiceselect");
			msg.addValue("selection", RETURN_BUTTON2);
			moves.push_back(msg);
		}
		for (vector<Card*>::iterator i = d->CardList.begin(); i != d->CardList.end(); i++)
		{
			if ((*i)->Zone != ZONE_EVOLVED)
			{
				if (d->choice->callvalid(d->choiceCard, (*i)->UniqueId) == 1)
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
					if (d->getIsShieldTrigger(*j) && d->canUseShieldTrigger(*j) && d->getCardCanCast(*j))
					{
						Message msg("triggeruse");
						msg.addValue("trigger", *j);
						moves.push_back(msg);
					}
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
			if ((*i)->isTapped == false)
			{
				if (d->castingcost == 1) //last card to be tapped
				{
					if (d->getCardCivilization((*i)->UniqueId) == d->castingciv || d->castingcivtapped)
					{
						Message m("manatap");
						m.addValue("card", (*i)->UniqueId);
						moves.push_back(m);
					}
				}
				else
				{
					Message m("manatap");
					m.addValue("card", (*i)->UniqueId);
					moves.push_back(m);
				}
			}
		}
	}

	if (player == d->turn && !d->isChoiceActive)
	{
		for (vector<Card*>::iterator i = d->hands[d->turn].cards.begin(); i != d->hands[d->turn].cards.end(); i++)
		{
			if (d->getCardCost((*i)->UniqueId) <= d->manazones[d->turn].getUntappedMana()
				&& d->isThereUntappedManaOfCiv(d->turn, d->getCardCivilization((*i)->UniqueId)) && d->getCardCanCast((*i)->UniqueId) == 1)
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

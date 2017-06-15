#include "DuelInterface.h"

DuelInterface::DuelInterface()
{
	duelstate = DUELSTATE_MENU;
	dueltype = DUELTYPE_SINGLE;

	setMyPlayer(0);

	endturnbutton = Button(sf::Vector2f(ENDTURNX, ENDTURNY), sf::Vector2f(BUTTONLENGTH, BUTTONHEIGHT), sf::Color::White, ZONEBORDERSIZE,
		sf::Color(127, 127, 127), sf::Color::Black, "Multiplayer", 16);
	cancelbutton = Button(sf::Vector2f(CANCELBOXX, CANCELBOXY), sf::Vector2f(BUTTONLENGTH, BUTTONHEIGHT), sf::Color::White, ZONEBORDERSIZE,
		sf::Color(127, 127, 127), sf::Color::Black, "Single Player", 16);
	quitbutton = Button(sf::Vector2f(QUITBUTTONX, QUITBUTTONY), sf::Vector2f(QUITBUTTONLENGTH, QUITBUTTONHEIGHT), sf::Color::White,
		3, sf::Color::Green, sf::Color::Black, "Main Menu", 16);

	infotext = sf::Text("Choose Blocker", DefaultFont, 16);
	infotext.setPosition(INFOTEXTX, INFOTEXTY);
	infotext.setFillColor(sf::Color::White);

	hovercard = sf::Sprite();
	hovercard.setPosition(HOVERCARDX, HOVERCARDY);

	selectedcard = -1;
	selectedcardzone = -1;

	mousearrow = -1;

	decklist = List(CARDSEARCHX, CARDSEARCHY, CARDSEARCHLENGTH, CARDSEARCHSEPERATION, CARDSEARCHITEMCOUNT);
	deckschosen = 0;

	cardCountBox = Button(sf::Vector2f(0, 0), sf::Vector2f(25, 25), sf::Color::Black, 0, sf::Color::Black, sf::Color::White, "0", 16);

	ai.duel = &duel;
}

DuelInterface::~DuelInterface()
{
}

void DuelInterface::render(sf::RenderWindow& window)
{
	//render zones
	for (int i = 0; i < 2; i++)
	{
		duel.decks[i].render(window);
		duel.hands[i].render(window);
		duel.manazones[i].render(window);
		duel.graveyards[i].render(window);
		duel.shields[i].render(window);
		duel.battlezones[i].render(window);

		duel.decks[i].renderCards(window, myPlayer);
		duel.hands[i].renderCards(window, myPlayer);
		duel.manazones[i].renderCards(window, myPlayer);
		duel.graveyards[i].renderCards(window, myPlayer);
		duel.shields[i].renderCards(window, myPlayer);
		duel.battlezones[i].renderCards(window, myPlayer);
	}
	
	if (duelstate == DUELSTATE_DUEL)
	{
		//draw endturn
		if (!duel.isChoiceActive)
		{
			endturnbutton.setString("End Turn");
			endturnbutton.render(window);
		}

		//draw cancel button
		if (duel.winner != -1)
		{
			infotext.setString("Player " + std::to_string(duel.winner + 1) + " wins");
			window.draw(infotext);
		}
		else if (duel.isChoiceActive)
		{
			infotext.setString(duel.CardList.at(duel.choiceCard)->Name + ": " + duel.choice->infotext);
			window.draw(infotext);
			if (duel.choice->buttoncount >= 1)
			{
				if (duel.choice->buttoncount >= 2)
				{
					cancelbutton.setString("Yes");
				}
				else
				{
					cancelbutton.setString("Skip");
				}
				cancelbutton.render(window);
			}
			if (duel.choice->buttoncount >= 2)
			{
				endturnbutton.setString("No");
				endturnbutton.render(window);
			}
		}
		else if (duel.attackphase == PHASE_BLOCK)
		{
			infotext.setString("Choose Blocker");
			cancelbutton.setString("Skip");
			cancelbutton.render(window);
			window.draw(infotext);
		}
		else if (duel.attackphase == PHASE_TARGET)
		{
			infotext.setString("Choose shields to break");
			window.draw(infotext);
		}
		else if (duel.attackphase == PHASE_TRIGGER)
		{
			infotext.setString("Choose shield triggers to cast");
			cancelbutton.setString("Skip");
			cancelbutton.render(window);
			window.draw(infotext);
		}
		else if (duel.castingcard != -1)
		{
			infotext.setString("Tap " + std::to_string(duel.castingcost) + " mana");
			window.draw(infotext);
		}

		if (duel.isChoiceActive && (duel.choicePlayer==myPlayer || dueltype==DUELTYPE_SINGLE))
		{
			for (int i = 0; i < 2; i++)
			{
				for (vector<Card*>::iterator j = duel.decks[i].cards.begin(); j != duel.decks[i].cards.end(); j++)
				{
					if (duel.choice->callvalid(duel.choiceCard, (*j)->UniqueId) == 1) //if choice contains a card in a deck, open the deck
					{
						cardsearch.zone = &duel.decks[i];
					}
				}
			}
		}
		else
		{
			for (int i = 0; i < 2; i++)
			{
				if (cardsearch.zone == &duel.decks[i])
				{
					cardsearch.zone = NULL; //close deck if there is no choice
				}
			}
		}
		if (cardsearch.zone != NULL)
		{
			cardsearch.render(window);
		}

		//draw hover card
		for (int i = 0; i < 2; i++)
		{
			vector<Card*>::iterator j;
			for (j = duel.hands[i].cards.begin(); j != duel.hands[i].cards.end(); j++)
			{
				if (checkCollision((*j)->getBounds(), MouseX, MouseY) && (*j)->UniqueId != selectedcard
					&& (dueltype == DUELTYPE_SINGLE || myPlayer == i))
				{
					hovercard.setTexture(CardTextures.at((*j)->CardId), true);
					window.draw(hovercard);
					break;
				}
			}

			for (j = duel.battlezones[i].cards.begin(); j != duel.battlezones[i].cards.end(); j++)
			{
				if (checkCollision((*j)->getBounds(), MouseX, MouseY))
				{
					hovercard.setTexture(CardTextures.at((*j)->CardId), true);
					window.draw(hovercard);
					break;
				}
			}

			for (j = duel.manazones[i].cards.begin(); j != duel.manazones[i].cards.end(); j++)
			{
				if (checkCollision((*j)->getBounds(), MouseX, MouseY))
				{
					hovercard.setTexture(CardTextures.at((*j)->CardId), true);
					window.draw(hovercard);
					break;
				}
			}

			if (duel.graveyards[i].cards.size() != 0)
			{
				j = duel.graveyards[i].cards.end() - 1;
				if (checkCollision((*j)->getBounds(), MouseX, MouseY))
				{
					hovercard.setTexture(CardTextures.at((*j)->CardId), true);
					window.draw(hovercard);
				}
			}

			int cs = cardsearch.getCardAtPos(MouseX, MouseY);
			if (cs != -1)
			{
				if (cs < cardsearch.zone->cards.size())
				{
					hovercard.setTexture(CardTextures.at(cardsearch.zone->cards.at(cs)->CardId), true);
					window.draw(hovercard);
				}
			}
		}

		quitbutton.render(window);

		//draw arrows
		if (arrows.size() > 0)
		{
			if (mousearrow >= 0)
			{
				arrows.at(mousearrow).setTo(MouseX, MouseY);
			}
			for (vector<Arrow>::iterator i = arrows.begin(); i != arrows.end(); i++)
			{
				(*i).render(window);
			}
		}
		
		//draw count
		for (int i = 0; i < 2; i++)
		{
			if (checkCollision((duel.getZone(i, ZONE_DECK))->getBounds(), MouseX, MouseY))
			{
				cardCountBox.setString(std::to_string(duel.getZone(i, ZONE_DECK)->cards.size()));
				cardCountBox.setPosition(MouseX - 25, MouseY - 25);
				cardCountBox.render(window);
			}
			if (checkCollision((duel.getZone(i, ZONE_GRAVEYARD))->getBounds(), MouseX, MouseY))
			{
				cardCountBox.setString(std::to_string(duel.getZone(i, ZONE_GRAVEYARD)->cards.size()));
				cardCountBox.setPosition(MouseX - 25, MouseY - 25);
				cardCountBox.render(window);
			}
			/*for (int j = 0; j < 6; j++)
			{
				if (checkCollision((duel.getZone(i, j))->getBounds(), MouseX, MouseY))
				{
					cardCountBox.setString(std::to_string(duel.getZone(i, j)->cards.size()));
					cardCountBox.setPosition(MouseX - 25, MouseY - 25);
					cardCountBox.render(window);
				}
			}*/
		}
	}
	else if (duelstate == DUELSTATE_SINGLE)
	{
		decklist.render(window);
		if (deckschosen == 0)
		{
			infotext.setString("Choose deck for player 1");
			window.draw(infotext);
		}
		else if (deckschosen == 1)
		{
			infotext.setString("Choose deck for player 2");
			window.draw(infotext);
		}
		quitbutton.render(window);
	}
	else if (duelstate == DUELSTATE_MULTI)
	{
		if (dueltype == DUELTYPE_MULTI)
		{
			decklist.render(window);
			infotext.setString("Choose deck:");
			window.draw(infotext);
		}
		else
		{
			cancelbutton.setString("Join Game");
			cancelbutton.render(window);
			endturnbutton.setString("Host Game");
			endturnbutton.render(window);
		}
		quitbutton.render(window);
	}
	else if (duelstate == DUELSTATE_MENU)
	{
		cancelbutton.setString("Single Player");
		cancelbutton.render(window);
		endturnbutton.setString("Multiplayer");
		endturnbutton.render(window);
		quitbutton.render(window);
	}
}

int DuelInterface::handleEvent(sf::Event event, int callback)
{
	if (duel.winner != -1) return RETURN_NOTHING;
	//if (ai.getPlayerToMove(ai.duel) == 1)
	//{
	//	duel.dispatchAllMessages(); //AI shouldnt make moves when there are pending messages
	//	Message m = ai.makeMove();
	//	cout << "AI make move " << m.getType() << endl;
	//	duel.handleInterfaceInput(m);
	//	duel.dispatchAllMessages();
	//	
	//	/*if (m.getType() == "choiceselect")
	//	{
	//		duel.resetChoice();
	//		if (callback != 0)
	//		{
	//			return m.getInt("selection");
	//		}
	//	}*/
	//	return RETURN_NOTHING;
	//}
	if (event.type == sf::Event::MouseMoved)
	{
		MouseX = event.mouseMove.x;
		MouseY = event.mouseMove.y;
	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (duelstate == DUELSTATE_DUEL)
			{
				if (endturnbutton.collision(MouseX, MouseY) && duel.attackphase == PHASE_NONE && !(duel.isChoiceActive)
					&& duel.castingcard == -1
					&& (duel.turn == myPlayer || dueltype == DUELTYPE_SINGLE)) //end turn
				{
					Message m("endturn");
					m.addValue("player", duel.turn);
					duel.handleInterfaceInput(m);
					undoSelection();

					if (dueltype == DUELTYPE_MULTI)
					{
						Socket.send(createPacketFromMessage(m));
					}
					else if (dueltype == DUELTYPE_SINGLE)
					{
						setMyPlayer(getOpponent(myPlayer));
					}
				}

				if (duel.isChoiceActive)
				{
					if (cancelbutton.collision(MouseX, MouseY) && (duel.choicePlayer == myPlayer || dueltype == DUELTYPE_SINGLE)) //button1 press
					{
						//choice.callskip(duel.choiceCard);
						Message msg("choiceselect");
						msg.addValue("selection", -1);
						duel.handleInterfaceInput(msg);
						if (dueltype == DUELTYPE_MULTI)
						{
							sf::Packet packet;
							sf::Uint32 ptype = PACKET_CHOICESELECT;
							sf::Uint32 selectedchoice = -1;
							packet << ptype << selectedchoice;
							Socket.send(packet);
						}
						/*duel.resetChoice();
						if (callback != 0)
						{
							return RETURN_BUTTON1;
						}*/
					}
					if (endturnbutton.collision(MouseX, MouseY) && (duel.choicePlayer == myPlayer || dueltype == DUELTYPE_SINGLE)) //button2 press
					{
						//choice.callskip(duel.choiceCard);
						Message msg("choiceselect");
						msg.addValue("selection", -2);
						duel.handleInterfaceInput(msg);
						if (dueltype == DUELTYPE_MULTI)
						{
							sf::Packet packet;
							sf::Uint32 ptype = PACKET_CHOICESELECT;
							sf::Uint32 selectedchoice = -2;
							packet << ptype << selectedchoice;
							Socket.send(packet);
						}
						/*duel.resetChoice();
						if (callback != 0)
						{
							return RETURN_BUTTON2;
						}*/
					}
					for (vector<Card*>::iterator i = duel.CardList.begin(); i != duel.CardList.end(); i++)
					{
						if ((*i)->Zone != ZONE_DECK && (*i)->Zone != ZONE_GRAVEYARD && (*i)->Zone != ZONE_EVOLVED)
						{
							if (checkCollision((*i)->getBounds(), MouseX, MouseY) && (duel.choicePlayer == myPlayer || dueltype == DUELTYPE_SINGLE))
							{
								if (duel.choice->callvalid(duel.choiceCard, (*i)->UniqueId) == 1)
								{
									//choice.callselect(duel.choiceCard, (*i)->UniqueId);
									Message msg("choiceselect");
									msg.addValue("selection", (*i)->UniqueId);
									duel.handleInterfaceInput(msg);
									if (dueltype == DUELTYPE_MULTI)
									{
										sf::Packet packet;
										sf::Uint32 ptype = PACKET_CHOICESELECT;
										sf::Uint32 selectedchoice = (*i)->UniqueId;
										packet << ptype << selectedchoice;
										Socket.send(packet);
									}
									/*duel.resetChoice();
									if (callback != 0)
									{
										return (*i)->UniqueId;
									}*/
									break;
								}
							}
						}
					}
					if (cardsearch.zone != NULL)
					{
						int cs = cardsearch.getCardAtPos(MouseX, MouseY);
						cout << "cs returned " << cs << endl;
						if (cs != -1)
						{
							if (duel.choice->callvalid(duel.choiceCard, cardsearch.zone->cards.at(cs)->UniqueId) == 1
								&& (duel.choicePlayer == myPlayer || dueltype == DUELTYPE_SINGLE))
							{
								cout << "true " << endl;
								Message msg("choiceselect");
								msg.addValue("selection", cardsearch.zone->cards.at(cs)->UniqueId);
								duel.handleInterfaceInput(msg);
								if (dueltype == DUELTYPE_MULTI)
								{
									sf::Packet packet;
									sf::Uint32 ptype = PACKET_CHOICESELECT;
									sf::Uint32 selectedchoice = cardsearch.zone->cards.at(cs)->UniqueId;
									packet << ptype << selectedchoice;
									Socket.send(packet);
								}
								/*duel.resetChoice();
								if (callback != 0)
								{
									return cardsearch.zone->cards.at(cs)->UniqueId;
								}*/
							}
						}
					}
				}
				else if (duel.attackphase == PHASE_TRIGGER && (dueltype == DUELTYPE_SINGLE || duel.defender == myPlayer)) //use shield triggers
				{
					for (vector<Card*>::iterator i = duel.hands[getOpponent(duel.turn)].cards.begin(); i != duel.hands[getOpponent(duel.turn)].cards.end(); i++)
					{
						if (checkCollision((*i)->getBounds(), MouseX, MouseY))
						{
							for (vector<int>::iterator j = duel.shieldtargets.begin(); j != duel.shieldtargets.end(); j++)
							{
								if (*j == (*i)->UniqueId)
								{
									Message msg("triggeruse");
									msg.addValue("trigger", (*i)->UniqueId);
									duel.handleInterfaceInput(msg);
									if (dueltype == DUELTYPE_MULTI)
									{
										Socket.send(createPacketFromMessage(msg));
									}
								}
							}
						}
					}
					if (cancelbutton.collision(MouseX, MouseY)) //skip shield triggers
					{
						SoundMngr->playSound(SOUND_BUTTONPRESS);
						Message m("triggerskip");
						duel.handleInterfaceInput(m);
						if (dueltype == DUELTYPE_MULTI)
						{
							Socket.send(createPacketFromMessage(m));
						}
					}
				}
				else if (duel.attackphase == PHASE_TARGET && (duel.CardList.at(duel.attacker)->Owner == myPlayer || dueltype == DUELTYPE_SINGLE)) //target shields
				{
					for (vector<Card*>::iterator i = duel.shields[getOpponent(duel.turn)].cards.begin(); i != duel.shields[getOpponent(duel.turn)].cards.end(); i++)
					{
						if (checkCollision((*i)->getBounds(), MouseX, MouseY))
						{
							Message m("targetshield");
							m.addValue("attacker", duel.attacker);
							m.addValue("shield", (*i)->UniqueId);
							duel.handleInterfaceInput(m);
							if (dueltype == DUELTYPE_MULTI)
							{
								Socket.send(createPacketFromMessage(m));
							}
						}
					}
				}
				else if (duel.attackphase == PHASE_BLOCK && (dueltype == DUELTYPE_SINGLE
					|| (duel.CardList.at(duel.defender)->Owner == myPlayer && duel.defendertype == DEFENDER_CREATURE)
					|| (duel.defender == myPlayer && duel.defendertype == DEFENDER_PLAYER))) //block
				{
					for (vector<Card*>::iterator i = duel.battlezones[getOpponent(duel.turn)].cards.begin(); i != duel.battlezones[getOpponent(duel.turn)].cards.end(); i++)
					{
						if (checkCollision((*i)->getBounds(), MouseX, MouseY)
							&& duel.getCreatureCanBlock(duel.attacker, (*i)->UniqueId) && (*i)->isTapped == false
							&& ((*i)->UniqueId != duel.defender || duel.defendertype == DEFENDER_PLAYER))
						{
							/*Message msg2("cardtap");
							msg2.addValue("card", (*i)->UniqueId);
							MsgMngr.sendMessage(msg2);*/

							Message msg("creatureblock");
							msg.addValue("attacker", duel.attacker);
							msg.addValue("blocker", (*i)->UniqueId);
							duel.handleInterfaceInput(msg);
							if (dueltype == DUELTYPE_MULTI)
							{
								Socket.send(createPacketFromMessage(msg));
							}

							undoSelection();
						}
					}
					if (cancelbutton.collision(MouseX, MouseY)) //skip block
					{
						SoundMngr->playSound(SOUND_BUTTONPRESS);
						Message m("blockskip");
						duel.handleInterfaceInput(m);
						if (dueltype == DUELTYPE_MULTI)
						{
							Socket.send(createPacketFromMessage(m));
						}

						undoSelection();
					}
				}
				else if (duel.castingcard != -1 && (duel.turn == myPlayer || dueltype == DUELTYPE_SINGLE)) //tap mana
				{
					for (vector<Card*>::iterator i = duel.manazones[duel.turn].cards.begin(); i != duel.manazones[duel.turn].cards.end(); i++)
					{
						if (checkCollision((*i)->getBounds(), MouseX, MouseY))
						{
							Message m("manatap");
							m.addValue("card", (*i)->UniqueId);
							duel.handleInterfaceInput(m);
							if (dueltype == DUELTYPE_MULTI)
							{
								Socket.send(createPacketFromMessage(m));
							}
						}
					}
				}
				else if (selectedcard == -1) //select a card
				{
					for (vector<Card*>::iterator j = duel.hands[duel.turn].cards.begin(); j != duel.hands[duel.turn].cards.end(); j++)
					{
						if (checkCollision((*j)->getBounds(), MouseX, MouseY)
							&& (duel.getCardCost((*j)->UniqueId) <= duel.manazones[duel.turn].getUntappedMana() || duel.manaUsed == 0)
							&& (duel.turn == myPlayer || dueltype == DUELTYPE_SINGLE))
						{
							selectedcard = (*j)->UniqueId;
							selectedcardzone = ZONE_HAND;
							iscardevo = duel.getIsEvolution(selectedcard);
							arrows.push_back(Arrow());
							sf::FloatRect bounds = duel.CardList.at(selectedcard)->sprite.getGlobalBounds();
							float cx = (bounds.left + bounds.left + bounds.width) / 2;
							float cy = (bounds.top + bounds.top + bounds.height) / 2;
							arrows.at(arrows.size() - 1).setFrom(cx, cy);
							arrows.at(arrows.size() - 1).setColor(SUMMONARROWCOLOR);
							mousearrow = arrows.size() - 1;

							break;
						}
					}
					for (vector<Card*>::iterator j = duel.battlezones[duel.turn].cards.begin(); j != duel.battlezones[duel.turn].cards.end(); j++)
					{
						if (checkCollision((*j)->getBounds(), MouseX, MouseY) && (*j)->isTapped == false
							&& (duel.turn == myPlayer || dueltype != DUELTYPE_MULTI))
						{
							selectedcard = (*j)->UniqueId;
							selectedcardzone = ZONE_BATTLE;

							arrows.push_back(Arrow());
							/*sf::FloatRect bounds = CardList.at(selectedcard)->sprite.getGlobalBounds();
							float cx = (bounds.left + bounds.left + bounds.width) / 2;
							float cy = (bounds.top + bounds.top + bounds.height) / 2;*/
							arrows.at(arrows.size() - 1).setFrom(duel.CardList.at(selectedcard)->x, duel.CardList.at(selectedcard)->y);
							arrows.at(arrows.size() - 1).setColor(ATTACKARROWCOLOR);
							mousearrow = arrows.size() - 1;

							break;
						}
					}
				}
				else if (selectedcardzone == ZONE_HAND) //play a card
				{
					if (iscardevo == 1)
					{
						if (duel.turn == myPlayer || dueltype == DUELTYPE_SINGLE) //cast evolution card
						{
							for (int i = 0; i < duel.battlezones[duel.turn].cards.size(); i++)
							{
								//if (duel.battlezones[duel.turn].cards.at(i)->Race == duel.CardList.at(selectedcard)->Race)
								if (checkCollision((duel.battlezones[duel.turn].cards.at(i))->sprite.getGlobalBounds(), MouseX, MouseY))
								{
									//if (duel.getCreatureCanEvolve(selectedcard, duel.battlezones[duel.turn].cards.at(i)->UniqueId) == 1)
									{
										Message msg("cardplay");
										msg.addValue("card", selectedcard);
										msg.addValue("evobait", duel.battlezones[duel.turn].cards.at(i)->UniqueId);
										duel.handleInterfaceInput(msg);
										if (dueltype == DUELTYPE_MULTI)
										{
											Socket.send(createPacketFromMessage(msg));
										}

										undoSelection();
										break;
									}
								}
							}
						}
					}
					else
					{
						if (checkCollision(duel.battlezones[duel.turn].getBounds(), MouseX, MouseY)
							&& (duel.turn == myPlayer || dueltype == DUELTYPE_SINGLE)) //cast a non-evo card
						{
							Message msg("cardplay");
							msg.addValue("card", selectedcard);
							msg.addValue("evobait", -1);
							duel.handleInterfaceInput(msg);
							if (dueltype == DUELTYPE_MULTI)
							{
								Socket.send(createPacketFromMessage(msg));
							}

							undoSelection();
						}
					}
					if (checkCollision(duel.manazones[duel.turn].getBounds(), MouseX, MouseY) && duel.manaUsed == 0
						&& (duel.turn == myPlayer || dueltype != DUELTYPE_MULTI)) //put mana
					{
						Message msg("cardmana");
						msg.addValue("card", selectedcard);
						duel.handleInterfaceInput(msg);
						if (dueltype == DUELTYPE_MULTI)
						{
							Socket.send(createPacketFromMessage(msg));
						}

						undoSelection();
						//manaUsed = 1;
					}
					if (checkCollision(duel.hands[duel.turn].getBounds(), MouseX, MouseY))
					{
						undoSelection();
					}
				}
				else if (selectedcardzone == ZONE_BATTLE) //attack
				{
					int canattack = duel.getCreatureCanAttackPlayers(selectedcard);
					if (checkCollision(duel.shields[getOpponent(duel.turn)].getBounds(), MouseX, MouseY) //attack player
						&& ((canattack == CANATTACK_ALWAYS ||
						((duel.CardList.at(selectedcard)->summoningSickness == 0 || duel.getIsSpeedAttacker(selectedcard) == 1) && (canattack == CANATTACK_TAPPED || canattack == CANATTACK_UNTAPPED)))
						&& duel.CardList.at(selectedcard)->isTapped == false)
						&& (duel.turn == myPlayer || dueltype != DUELTYPE_MULTI))
					{
						/*Message msg2("cardtap");
						msg2.addValue("card", selectedcard);
						MsgMngr.sendMessage(msg2);*/

						Message msg("creatureattack");
						msg.addValue("attacker", selectedcard);
						msg.addValue("defender", getOpponent(duel.turn));
						msg.addValue("defendertype", DEFENDER_PLAYER);
						duel.handleInterfaceInput(msg);

						sf::FloatRect bounds = duel.shields[getOpponent(duel.turn)].getBounds();

						arrows.at(mousearrow).setTo((bounds.left * 2 + bounds.width) / 2, (bounds.top * 2 + bounds.height) / 2);

						if (dueltype == DUELTYPE_MULTI)
						{
							Socket.send(createPacketFromMessage(msg));

							sf::Packet p;
							sf::Uint32 ptype = PACKET_ADDARROW;
							sf::Uint32 fx = arrows.at(mousearrow).fromx;
							sf::Uint32 fy = arrows.at(mousearrow).fromy;
							sf::Uint32 tx = arrows.at(mousearrow).tox;
							sf::Uint32 ty = arrows.at(mousearrow).toy;
							p << ptype << fx << fy << tx << ty;
							Socket.send(p);
						}
						mousearrow = -1;
						//undoSelection();
					}
					for (vector<Card*>::iterator i = duel.battlezones[getOpponent(duel.turn)].cards.begin(); i != duel.battlezones[getOpponent(duel.turn)].cards.end(); i++)
					{
						int canattack = duel.getCreatureCanAttackCreature(selectedcard, (*i)->UniqueId);
						if (checkCollision((*i)->getBounds(), MouseX, MouseY) //attack creature
							&& ((*i)->isTapped == true || canattack == CANATTACK_UNTAPPED)
							&& canattack <= CANATTACK_UNTAPPED
							&& duel.CardList.at(selectedcard)->summoningSickness == 0
							&& duel.CardList.at(selectedcard)->isTapped == false
							&& (duel.turn == myPlayer || dueltype == DUELTYPE_SINGLE))
						{
							/*Message msg2("cardtap");
							msg2.addValue("card", selectedcard);
							MsgMngr.sendMessage(msg2);*/

							Message msg("creatureattack");
							msg.addValue("attacker", selectedcard);
							msg.addValue("defender", (*i)->UniqueId);
							msg.addValue("defendertype", DEFENDER_CREATURE);
							duel.handleInterfaceInput(msg);

							arrows.at(mousearrow).setTo((*i)->x, (*i)->y);

							if (dueltype == DUELTYPE_MULTI)
							{
								Socket.send(createPacketFromMessage(msg));

								sf::Packet p;
								sf::Uint32 ptype = PACKET_ADDARROW;
								sf::Uint32 fx = arrows.at(mousearrow).fromx;
								sf::Uint32 fy = arrows.at(mousearrow).fromy;
								sf::Uint32 tx = arrows.at(mousearrow).tox;
								sf::Uint32 ty = arrows.at(mousearrow).toy;
								p << ptype << fx << fy << tx << ty;
								Socket.send(p);
							}
							mousearrow = -1;

							//undoSelection();
						}
					}
					if (checkCollision(duel.battlezones[duel.turn].getBounds(), MouseX, MouseY))
					{
						undoSelection();
					}
				}

				for (int i = 0; i < 2; i++) //view graveyard
				{
					if (checkCollision(duel.graveyards[i].getBounds(), MouseX, MouseY)
						&& cardsearch.zone != &duel.decks[0] && cardsearch.zone != &duel.decks[1])
					{
						//if (cardsearch.zone != &duel.graveyards[i]
						if (cardsearch.zone != &duel.graveyards[i])
						{
							cardsearch.setZone(&duel.graveyards[i]);
						}
						else
						{
							cardsearch.setZone(NULL);
						}
					}
				}

				/*for (int i = 0; i < 2; i++)
				{
				if (checkCollision(duel.decks[i].getBounds(), MouseX, MouseY))
				{
				if (cardsearch.zone != &duel.decks[i])
				{
				cardsearch.setZone(&duel.decks[i]);
				}
				else
				{
				cardsearch.setZone(NULL);
				}
				}
				}*/
			}
			else if (duelstate == DUELSTATE_SINGLE)
			{
				int deck = decklist.getItemAtPos(MouseX, MouseY);
				if (deck != -1)
				{
					duel.loadDeck("Decks\\My Decks\\" + decklist.items.at(deck) + DECKEXTENSION, deckschosen);
					deckschosen++;
					if (deckschosen >= 2)
					{
						dueltype = DUELTYPE_SINGLE;
						duelstate = DUELSTATE_DUEL;
						myPlayer = 0;
						duel.startDuel();
					}
				}
			}
			else if (duelstate == DUELSTATE_MULTI)
			{
				if (dueltype == DUELTYPE_MULTI)
				{
					int deck = decklist.getItemAtPos(MouseX, MouseY);
					if (deck != -1)
					{
						duel.loadDeck("Decks\\My Decks\\" + decklist.items.at(deck) + DECKEXTENSION, deckschosen);
						setMyPlayer(deckschosen);

						sf::Packet p;
						sf::Uint32 ptype = PACKET_SETDECK;
						sf::Uint32 size = duel.decks[deckschosen].cards.size();
						p << ptype << size;
						for (vector<Card*>::iterator i = duel.decks[deckschosen].cards.begin(); i != duel.decks[deckschosen].cards.end(); i++)
						{
							p << (*i)->CardId;
						}
						Socket.send(p);
						cout << "sent setdeck packet" << endl;

						deckschosen++;

						if (deckschosen >= 2 && dueltype == DUELTYPE_MULTI)
						{
							duelstate = DUELSTATE_DUEL;
							duel.startDuel();
						}
					}
				}
				else
				{
					if (cancelbutton.collision(MouseX, MouseY)) //join game
					{
						SoundMngr->playSound(SOUND_BUTTONPRESS);

						fstream ipfile;
						ipfile.open("ip.txt", ios::in | ios::out);
						string ipadd;
						string port;
						getline(ipfile, ipadd);
						getline(ipfile, port);
						ipfile.close();
						sf::Socket::Status status = Socket.connect(ipadd, atoi(port.c_str()));
						Socket.setBlocking(false);
						dueltype = DUELTYPE_MULTI;
						cout << "game connected" << endl;
						if (deckschosen >= 2)
						{
							duelstate = DUELSTATE_DUEL;
							duel.startDuel();
						}
					}
					if (endturnbutton.collision(MouseX, MouseY))  //host game
					{
						SoundMngr->playSound(SOUND_BUTTONPRESS);

						fstream ipfile;
						ipfile.open("ip.txt", ios::in | ios::out);
						string ipadd;
						string port;
						getline(ipfile, ipadd);
						getline(ipfile, port);
						ipfile.close();
						sf::TcpListener listener;
						listener.listen(atoi(port.c_str()));
						listener.accept(Socket);
						Socket.setBlocking(false);
						dueltype = DUELTYPE_MULTI;
						cout << "game connected" << endl;

						//int seed = time(0);
						//std::srand(seed);
						duel.RandomGen.Randomize();
						sf::Packet packet;
						packet << PACKET_SETSEED << duel.RandomGen.GetRandomSeed();
						Socket.send(packet);

						if (deckschosen >= 2)
						{
							duelstate = DUELSTATE_DUEL;
							duel.startDuel();
						}
					}
				}
			}
			else if (duelstate == DUELSTATE_MENU)
			{
				if (cancelbutton.collision(MouseX, MouseY)) //singleplayer
				{
					SoundMngr->playSound(SOUND_BUTTONPRESS);

					duelstate = DUELSTATE_SINGLE;
					deckschosen = 0;
					setDecklist();
					duel.clearCards();
				}
				if (endturnbutton.collision(MouseX, MouseY))  //multiplayer
				{
					SoundMngr->playSound(SOUND_BUTTONPRESS);

					duelstate = DUELSTATE_MULTI;
					deckschosen = 0;
					setDecklist();
					duel.clearCards();
				}
			}
			if (quitbutton.collision(MouseX, MouseY)) //go back to main menu
			{
				SoundMngr->playSound(SOUND_BUTTONPRESS);
				currentWindow = static_cast<GameWindow*>(mainMenu);
			}

		}
		else if (event.mouseButton.button == sf::Mouse::Right)
		{
			undoSelection();
		}
	}

	if (cardsearch.zone != NULL)
	{
		cardsearch.handleEvent(event);
	}
	if (duelstate == DUELSTATE_SINGLE || (duelstate == DUELSTATE_MULTI && dueltype == DUELTYPE_MULTI))
	{
		decklist.handleEvent(event);
	}

	return RETURN_NOTHING;
}

int DuelInterface::receivePacket(sf::Packet& packet, int callback)
{
	if (dueltype == DUELTYPE_MULTI)
	{
		sf::Uint32 ptype;
		packet >> ptype;
		if (ptype == PACKET_MSG)
		{
			Message msg;
			packet >> msg;
			cout << "received msg packet : " << msg.getType() << endl;
			duel.handleInterfaceInput(msg);
		}
		else if (ptype == PACKET_SETDECK)
		{
			cout << "setdeck packet recieved" << endl;
			sf::Uint32 size;
			packet >> size;
			cout << "size: " << endl;
			duel.decks[deckschosen].cards.empty();
			for (int i = 0; i < size; i++)
			{
				sf::Uint32 cid;
				packet >> cid;
				Card* c = new Card(duel.nextUniqueId, cid, deckschosen);
				duel.CardList.push_back(c);
				duel.decks[deckschosen].addCard(c);
				duel.nextUniqueId++;
				cout << "added card: " << cid << endl;
			}
			deckschosen++;
			if (deckschosen >= 2)
			{
				duelstate = DUELSTATE_DUEL;
				duel.startDuel();
			}
		}
		else if (ptype == PACKET_SETSEED)
		{
			sf::Uint32 x;
			packet >> x;
			//std::srand(x);
			duel.RandomGen.SetRandomSeed(x);
			cout << "set seed packet received : " << x << endl;
		}
		else if (ptype == PACKET_CHOICESELECT)
		{
			sf::Uint32 x;
			packet >> x;
			duel.resetChoice();
			cout << "choice select packet received : " << x << endl;
			return x;
		}
		else if (ptype == PACKET_ADDARROW)
		{
			arrows.push_back(Arrow());
			sf::Uint32 fx, fy, tx, ty;
			packet >> fx >> fy >> tx >> ty;
			arrows.at(arrows.size() - 1).setColor(ATTACKARROWCOLOR);
			arrows.at(arrows.size() - 1).setFrom(fx,fy);
			arrows.at(arrows.size() - 1).setTo(tx, ty);
			cout << "add arrow packet received" << endl;
		}
		else if (ptype == PACKET_CLEARARROWS)
		{
			arrows.clear();
			cout << "clear arrows packet received" << endl;
			mousearrow = -1;
		}
	}
	return RETURN_NOTHING;
}

void DuelInterface::update(unsigned int deltatime)
{
	duel.update(deltatime);
}

void DuelInterface::undoSelection()
{
	selectedcard = -1;
	selectedcardzone = -1;
	iscardevo = -1;
	arrows.clear();
	mousearrow = -1;
	if (dueltype == DUELTYPE_MULTI)
	{
		sf::Packet p;
		sf::Uint32 ptype = PACKET_CLEARARROWS;
		p << ptype;
		Socket.send(p);
		cout << "clear arrows packet sent" << endl;
	}
}

//void DuelInterface::flipCardForPlayer(int cid, int p)
//{
//	if (myPlayer == p || dueltype == DUELTYPE_SINGLE)
//		duel.CardList.at(cid)->flip();
//}
//
//void DuelInterface::unflipCardForPlayer(int cid, int p)
//{
//	if (myPlayer == p || dueltype == DUELTYPE_SINGLE)
//		duel.CardList.at(cid)->unflip();
//}

void DuelInterface::setDecklist()
{
	decklist.items.clear();
	fstream deckfile;
	deckfile.open("Decks\\My Decks\\decklist.txt", ios::out | ios::in);
	if (!deckfile.is_open())
	{
		cout << "ERROR cant open deckfile, please restart" << endl;
	}
	string s;
	while (!deckfile.eof())
	{
		getline(deckfile, s);
		decklist.items.push_back(s);
	}
	deckfile.close();
}

void DuelInterface::setMyPlayer(int p)
{
	myPlayer = p;
	duel.hands[0].myPlayer = p;
	duel.hands[1].myPlayer = p;
	//duel.hands[0].flipAllCards();
	//duel.hands[1].flipAllCards();
}


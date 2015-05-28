#include "DuelInterface.h"

int mainLoop(sf::RenderWindow& window, int callback)
{
	sf::Packet packet;
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				currentWindow->handleEvent(event, callback);
				window.close();
			}

			int r = currentWindow->handleEvent(event, callback);
			currentWindow->update(0);

			if (callback != 0 && r != RETURN_NOTHING) //if we need to callback(return) and a choice has been made
			{
				return r;
			}
			if (r == RETURN_QUIT)
			{
				window.close();
			}
		}

		Socket.receive(packet);

		window.clear();

		currentWindow->render(window);

		window.display();
	}
}

DuelInterface::DuelInterface()
{
	duelstate = DUELSTATE_MENU;
	dueltype = DUELTYPE_SINGLE;

	endturnbutton = Button(sf::Vector2f(ENDTURNX, ENDTURNY), sf::Vector2f(ENDTURNLENGTH, ENDTURNHEIGHT), sf::Color::White, ZONEBORDERSIZE,
		sf::Color(127, 127, 127), sf::Color::Black, "Multiplayer", 16);
	cancelbutton = Button(sf::Vector2f(CANCELBOXX, CANCELBOXY), sf::Vector2f(ENDTURNLENGTH, ENDTURNHEIGHT), sf::Color::White, ZONEBORDERSIZE,
		sf::Color(127, 127, 127), sf::Color::Black, "Single Player", 16);
	quitbutton = Button(sf::Vector2f(QUITBUTTONX, QUITBUTTONY), sf::Vector2f(QUITBUTTONLENGTH, QUITBUTTONHEIGHT), sf::Color::White,
		3, sf::Color::Green, sf::Color::Black, "Main Menu", 16);

	infotext = sf::Text("Choose Blocker", DefaultFont, 16);
	infotext.setPosition(INFOTEXTX, INFOTEXTY);
	infotext.setColor(sf::Color::White);

	hovercard = sf::Sprite();
	hovercard.setPosition(HOVERCARDX, HOVERCARDY);

	selectedcard = -1;
	selectedcardzone = -1;

	mousearrow = -1;

	decklist = List(CARDSEARCHX, CARDSEARCHY, CARDSEARCHLENGTH, CARDSEARCHSEPERATION, CARDSEARCHITEMCOUNT);
	deckschosen = 0;

	cardCountBox = Button(sf::Vector2f(0, 0), sf::Vector2f(25, 25), sf::Color::Black, 0, sf::Color::Black, sf::Color::White, "0", 16);
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

		duel.decks[i].renderCards(window);
		duel.hands[i].renderCards(window);
		duel.manazones[i].renderCards(window);
		duel.graveyards[i].renderCards(window);
		duel.shields[i].renderCards(window);
		duel.battlezones[i].renderCards(window);
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
			infotext.setString(duel.choice.infotext);
			window.draw(infotext);
			if (duel.choice.buttoncount >= 1)
			{
				if (duel.choice.buttoncount >= 2)
				{
					cancelbutton.setString("Yes");
				}
				else
				{
					cancelbutton.setString("Skip");
				}
				cancelbutton.render(window);
			}
			if (duel.choice.buttoncount >= 2)
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
				if (checkCollision((*j)->getBounds(), MouseX, MouseY) && (*j)->UniqueId != selectedcard)
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
				hovercard.setTexture(CardTextures.at(cardsearch.zone->cards.at(cs)->CardId), true);
				window.draw(hovercard);
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
	}
	else if (duelstate == DUELSTATE_MULTI)
	{
		decklist.render(window);
		infotext.setString("Choose deck:");
		window.draw(infotext);

		cancelbutton.setString("Join Game");
		cancelbutton.render(window);
		endturnbutton.setString("Host Game");
		endturnbutton.render(window);
	}
	else if (duelstate == DUELSTATE_MENU)
	{
		cancelbutton.setString("Single Player");
		cancelbutton.render(window);
		endturnbutton.setString("Multiplayer");
		endturnbutton.render(window);
	}
}

int DuelInterface::handleEvent(sf::Event event, int callback)
{
	if (duel.winner != -1) return RETURN_NOTHING;
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
					&& duel.castingcard == -1) //end turn
				{
					Message m("endturn");
					m.addValue("player", duel.turn);
					duel.handleInterfaceInput(m);
					undoSelection();

					if (dueltype == DUELTYPE_MULTI)
					{
						Socket.send(createPacketFromMessage(m));
					}
				}

				if (duel.isChoiceActive)
				{
					if (cancelbutton.collision(MouseX, MouseY)) //button1 press
					{
						//choice.callskip(duel.choiceCard);
						/*Message msg("choicebutton1");
						duel.handleInterfaceInput(msg);*/
						duel.resetChoice();
						if (callback != 0)
						{
							return RETURN_BUTTON1;
						}
					}
					if (endturnbutton.collision(MouseX, MouseY)) //button2 press
					{
						//choice.callskip(duel.choiceCard);
						/*Message msg("choicebutton2");
						duel.handleInterfaceInput(msg);*/
						duel.resetChoice();
						if (callback != 0)
						{
							return RETURN_BUTTON2;
						}
					}
					for (vector<Card*>::iterator i = duel.CardList.begin(); i != duel.CardList.end(); i++)
					{
						if ((*i)->Zone != ZONE_DECK && (*i)->Zone != ZONE_GRAVEYARD)
						{
							if (checkCollision((*i)->getBounds(), MouseX, MouseY))
							{
								if (duel.choice.callvalid(duel.choiceCard, (*i)->UniqueId) == 1)
								{
									//choice.callselect(duel.choiceCard, (*i)->UniqueId);
									/*Message msg("choiceselect");
									msg.addValue("selection", (*i)->UniqueId);
									duel.handleInterfaceInput(msg);*/
									duel.resetChoice();
									if (callback != 0)
									{
										return (*i)->UniqueId;
									}
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
							if (duel.choice.callvalid(duel.choiceCard, cardsearch.zone->cards.at(cs)->UniqueId) == 1)
							{
								cout << "true " << endl;
								/*Message msg("choiceselect");
								msg.addValue("selection", cardsearch.zone->cards.at(cs)->UniqueId);
								duel.handleInterfaceInput(msg);*/
								duel.resetChoice();
								if (callback != 0)
								{
									return cardsearch.zone->cards.at(cs)->UniqueId;
								}
							}
						}
					}
				}
				else if (duel.attackphase == PHASE_TRIGGER) //use shield triggers
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
						Message m("triggerskip");
						duel.handleInterfaceInput(m);
						if (dueltype == DUELTYPE_MULTI)
						{
							Socket.send(createPacketFromMessage(m));
						}
					}
				}
				else if (duel.attackphase == PHASE_TARGET)
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
				else if (duel.attackphase == PHASE_BLOCK) //block
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
						Message m("blockskip");
						duel.handleInterfaceInput(m);
						if (dueltype == DUELTYPE_MULTI)
						{
							Socket.send(createPacketFromMessage(m));
						}

						undoSelection();
					}
				}
				else if (duel.castingcard != -1)
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
							&& (duel.getCardCost((*j)->UniqueId) <= duel.manazones[duel.turn].getUntappedMana() || duel.manaUsed == 0))
						{
							selectedcard = (*j)->UniqueId;
							selectedcardzone = ZONE_HAND;
							arrows.push_back(Arrow());
							sf::FloatRect bounds = duel.CardList.at(selectedcard)->sprite.getGlobalBounds();
							float cx = (bounds.left + bounds.left + bounds.width) / 2;
							float cy = (bounds.top + bounds.top + bounds.height) / 2;
							arrows.at(arrows.size() - 1).setFrom(cx, cy);
							arrows.at(arrows.size() - 1).setColor(sf::Color(0, 255, 0, 128));
							mousearrow = arrows.size() - 1;

							break;
						}
					}
					for (vector<Card*>::iterator j = duel.battlezones[duel.turn].cards.begin(); j != duel.battlezones[duel.turn].cards.end(); j++)
					{
						if (checkCollision((*j)->getBounds(), MouseX, MouseY) && (*j)->isTapped == false && (*j)->summoningSickness == 0)
						{
							selectedcard = (*j)->UniqueId;
							selectedcardzone = ZONE_BATTLE;

							arrows.push_back(Arrow());
							/*sf::FloatRect bounds = CardList.at(selectedcard)->sprite.getGlobalBounds();
							float cx = (bounds.left + bounds.left + bounds.width) / 2;
							float cy = (bounds.top + bounds.top + bounds.height) / 2;*/
							arrows.at(arrows.size() - 1).setFrom(duel.CardList.at(selectedcard)->x, duel.CardList.at(selectedcard)->y);
							arrows.at(arrows.size() - 1).setColor(sf::Color(255, 0, 0, 128));
							mousearrow = arrows.size() - 1;

							break;
						}
					}
				}
				else if (selectedcardzone == ZONE_HAND) //play a card
				{
					if (checkCollision(duel.battlezones[duel.turn].getBounds(), MouseX, MouseY)) //cast a card
					{
						Message msg("cardplay");
						msg.addValue("card", selectedcard);
						duel.handleInterfaceInput(msg);
						if (dueltype == DUELTYPE_MULTI)
						{
							Socket.send(createPacketFromMessage(msg));
						}

						undoSelection();
					}
					if (checkCollision(duel.manazones[duel.turn].getBounds(), MouseX, MouseY) && duel.manaUsed == 0) //put mana
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
					if (checkCollision(duel.shields[getOpponent(duel.turn)].getBounds(), MouseX, MouseY) //attack player
						&& duel.getCreatureCanAttackPlayers(selectedcard) == 1
						&& duel.CardList.at(selectedcard)->isTapped == false)
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
						mousearrow = -1;

						if (dueltype == DUELTYPE_MULTI)
						{
							Socket.send(createPacketFromMessage(msg));
						}

						//undoSelection();
					}
					for (vector<Card*>::iterator i = duel.battlezones[getOpponent(duel.turn)].cards.begin(); i != duel.battlezones[getOpponent(duel.turn)].cards.end(); i++)
					{
						if (checkCollision((*i)->getBounds(), MouseX, MouseY) //attack creature
							&& ((*i)->isTapped == true || duel.getCreatureCanAttackCreature(selectedcard, (*i)->UniqueId) == CANATTACK_UNTAPPED)
							&& duel.getCreatureCanAttackCreature(selectedcard, (*i)->UniqueId) <= CANATTACK_UNTAPPED
							&& duel.CardList.at(selectedcard)->isTapped == false)
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
							mousearrow = -1;

							if (dueltype == DUELTYPE_MULTI)
							{
								Socket.send(createPacketFromMessage(msg));
							}

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
					if (checkCollision(duel.graveyards[i].getBounds(), MouseX, MouseY))
					{
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
						duelstate = DUELSTATE_DUEL;
						duel.startDuel();
					}
				}
			}
			else if (duelstate == DUELSTATE_MULTI)
			{
				if (cancelbutton.collision(MouseX, MouseY)) //join game
				{
					sf::Socket::Status status = Socket.connect("", 53000);
					Socket.setBlocking(false);
					dueltype = DUELTYPE_MULTI;
					if (deckschosen >= 1)
					{
						duelstate = DUELSTATE_DUEL;
						duel.startDuel();
					}
				}
				if (quitbutton.collision(MouseX, MouseY))  //host game
				{
					sf::TcpListener listener;
					listener.listen(53000);
					listener.accept(Socket);
					Socket.setBlocking(false);
					dueltype = DUELTYPE_MULTI;
					if (deckschosen >= 1)
					{
						duelstate = DUELSTATE_DUEL;
						duel.startDuel();
					}
				}
				int deck = decklist.getItemAtPos(MouseX, MouseY);
				if (deck != -1)
				{
					duel.loadDeck("Decks\\My Decks\\" + decklist.items.at(deck) + DECKEXTENSION, deckschosen);
					deckschosen++;
					if (deckschosen >= 1 && dueltype == DUELTYPE_MULTI)
					{
						duelstate = DUELSTATE_DUEL;
						duel.startDuel();
					}
				}
			}
			else if (duelstate == DUELSTATE_MENU)
			{
				if (cancelbutton.collision(MouseX, MouseY)) //singleplayer
				{
					duelstate = DUELSTATE_SINGLE;
					deckschosen = 0;
					setDecklist();
					duel.clearCards();
				}
				if (quitbutton.collision(MouseX, MouseY))  //multiplayer
				{
					duelstate = DUELSTATE_MULTI;
					deckschosen = 0;
					setDecklist();
					duel.clearCards();
				}
			}
			if (quitbutton.collision(MouseX, MouseY)) //go back to main menu
			{
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

	return RETURN_NOTHING;
}

void DuelInterface::recievePacket(sf::Packet& packet)
{
	if (dueltype == DUELTYPE_MULTI)
	{
		Message msg;
		packet >> msg;
		duel.handleInterfaceInput(msg);
	}
}

void DuelInterface::update(unsigned int deltatime)
{
	duel.update(deltatime);
}

void DuelInterface::undoSelection()
{
	selectedcard = -1;
	selectedcardzone = -1;
	arrows.clear();
}

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

#include "DuelInterface.h"


DuelInterface::DuelInterface()
{
	endturnbutton = sf::RectangleShape(sf::Vector2f(ENDTURNLENGTH, ENDTURNHEIGHT));
	endturnbutton.setPosition(ENDTURNX, ENDTURNY);
	endturnbutton.setFillColor(sf::Color::White);
	endturnbutton.setOutlineColor(sf::Color(50, 50, 50));
	endturnbutton.setOutlineThickness(ZONEBORDERSIZE);

	endturntext = sf::Text("End Turn", DefaultFont, 16);
	endturntext.setPosition(ENDTURNX + CARDZONEOFFSET, ENDTURNY + CARDZONEOFFSET);
	endturntext.setColor(sf::Color::Black);

	endturnsound = sf::Sound(Sounds.at(SOUND_ENDTURN));

	cancelbutton = sf::RectangleShape(sf::Vector2f(ENDTURNLENGTH, ENDTURNHEIGHT));
	cancelbutton.setPosition(CANCELBOXX, CANCELBOXY);
	cancelbutton.setFillColor(sf::Color::White);
	cancelbutton.setOutlineColor(sf::Color(50, 50, 50));
	cancelbutton.setOutlineThickness(ZONEBORDERSIZE);

	canceltext = sf::Text("Skip", DefaultFont, 16);
	canceltext.setPosition(CANCELBOXX + CARDZONEOFFSET, CANCELBOXY + CARDZONEOFFSET);
	canceltext.setColor(sf::Color::Black);

	infotext = sf::Text("Choose Blocker", DefaultFont, 16);
	infotext.setPosition(INFOTEXTX, INFOTEXTY);
	infotext.setColor(sf::Color::White);

	hovercard = sf::Sprite();
	hovercard.setPosition(HOVERCARDX, HOVERCARDY);

	selectedcard = -1;
	selectedcardzone = -1;

	mousearrow = -1;
}

DuelInterface::~DuelInterface()
{
}

void DuelInterface::render(sf::RenderWindow& window)
{
	/*if (selectedcard != -1 && selectedcardzone == ZONE_HAND)
	{
	CardList.at(selectedcard)->setPosition(MouseX, MouseY);
	}*/
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

	//draw endturn
	if (!duel.isChoiceActive)
	{
		endturntext.setString("End Turn");
		window.draw(endturnbutton);
		window.draw(endturntext);
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
				canceltext.setString("Yes");
			}
			else
			{
				canceltext.setString("Skip");
			}
			window.draw(cancelbutton);
			window.draw(canceltext);
		}
		if (duel.choice.buttoncount >= 2)
		{
			endturntext.setString("No");
			window.draw(endturnbutton);
			window.draw(endturntext);
		}
	}
	else if (duel.attackphase == PHASE_BLOCK)
	{
		infotext.setString("Choose Blocker");
		canceltext.setString("Skip");
		window.draw(cancelbutton);
		window.draw(canceltext);
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
		canceltext.setString("Skip");
		window.draw(cancelbutton);
		window.draw(canceltext);
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

	//draw selected card
	/*if (selectedcard != NULL)
	{
	selectedcard->setPosition(MouseX, MouseY);
	selectedcard->render(window);
	}*/
}

void DuelInterface::handleEvent(sf::Event event)
{
	if (duel.winner != -1) return;
	if (event.type == sf::Event::MouseMoved)
	{
		MouseX = event.mouseMove.x;
		MouseY = event.mouseMove.y;
	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (duel.isChoiceActive)
			{
				if (checkCollision(cancelbutton.getGlobalBounds(), MouseX, MouseY)) //button1 press
				{
					//choice.callskip(duel.choiceCard);
					Message msg("choicebutton1");
					duel.handleInterfaceInput(msg);
				}
				if (checkCollision(endturnbutton.getGlobalBounds(), MouseX, MouseY)) //button2 press
				{
					//choice.callskip(duel.choiceCard);
					Message msg("choicebutton2");
					duel.handleInterfaceInput(msg);
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
								Message msg("choiceselect");
								msg.addValue("selection", (*i)->UniqueId);
								duel.handleInterfaceInput(msg);
								break;
							}
						}
					}
				}
				if (cardsearch.zone != NULL)
				{
					int cs = cardsearch.getCardAtPos(MouseX, MouseY);
					if (cs != -1)
					{
						Message msg("choiceselect");
						msg.addValue("selection", cs);
						duel.handleInterfaceInput(msg);
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
							}
						}
					}
				}
				if (checkCollision(cancelbutton.getGlobalBounds(), MouseX, MouseY)) //skip shield triggers
				{
					Message m("triggerskip");
					duel.handleInterfaceInput(m);
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
					}
				}
			}
			else if (duel.attackphase == PHASE_BLOCK) //block
			{
				for (vector<Card*>::iterator i = duel.battlezones[getOpponent(duel.turn)].cards.begin(); i != duel.battlezones[getOpponent(duel.turn)].cards.end(); i++)
				{
					if (checkCollision((*i)->getBounds(), MouseX, MouseY)
						&& duel.getCreatureCanBlock(duel.attacker, (*i)->UniqueId) && (*i)->isTapped == false
						&& (*i)->UniqueId != duel.defender)
					{
						/*Message msg2("cardtap");
						msg2.addValue("card", (*i)->UniqueId);
						MsgMngr.sendMessage(msg2);*/

						Message msg("creatureblock");
						msg.addValue("attacker", duel.attacker);
						msg.addValue("blocker", (*i)->UniqueId);
						duel.handleInterfaceInput(msg);

						undoSelection();
					}
				}
				if (checkCollision(cancelbutton.getGlobalBounds(), MouseX, MouseY)) //skip block
				{
					Message m("blockskip");
					duel.handleInterfaceInput(m);

					undoSelection();
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

					undoSelection();
				}
				if (checkCollision(duel.manazones[duel.turn].getBounds(), MouseX, MouseY) && duel.manaUsed == 0) //put mana
				{
					Message msg("cardmana");
					msg.addValue("card", selectedcard);
					duel.handleInterfaceInput(msg);

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
					&& duel.getCreatureCanAttackPlayer(selectedcard,getOpponent(duel.turn)) == 1
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

					//undoSelection();
				}
				for (vector<Card*>::iterator i = duel.battlezones[getOpponent(duel.turn)].cards.begin(); i != duel.battlezones[getOpponent(duel.turn)].cards.end(); i++)
				{
					if (checkCollision((*i)->getBounds(), MouseX, MouseY) //attack creature
						&& ((*i)->isTapped == true || duel.getCreatureCanAttackCreature(selectedcard,(*i)->UniqueId) == CANATTACK_UNTAPPED)
						&& duel.getCreatureCanAttackCreature(selectedcard,(*i)->UniqueId) >= CANATTACK_TAPPED
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

						//undoSelection();
					}
				}
				if (checkCollision(duel.battlezones[duel.turn].getBounds(), MouseX, MouseY))
				{
					undoSelection();
				}
			}
			if (checkCollision(endturnbutton.getGlobalBounds(), MouseX, MouseY) && duel.attackphase == PHASE_NONE && duel.isChoiceActive == 0) //end turn
			{
				Message m("endturn");
				m.addValue("player", duel.turn);
				duel.handleInterfaceInput(m);
				endturnsound.play();
				undoSelection();
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
			for (int i = 0; i < 2; i++)
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

	/*for (int i = 0; i < 2; i++)
	{
	decks[i].handleEvent(event);
	hands[i].handleEvent(event);
	manazones[i].handleEvent(event);
	graveyards[i].handleEvent(event);
	shields[i].handleEvent(event);
	battlezones[i].handleEvent(event);
	}*/
}

void DuelInterface::update(int deltatime)
{
	duel.update(deltatime);
}

void DuelInterface::undoSelection()
{
	selectedcard = -1;
	selectedcardzone = -1;
	arrows.clear();
}

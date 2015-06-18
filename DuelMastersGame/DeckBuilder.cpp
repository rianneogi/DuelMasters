#include "DeckBuilder.h"

DeckBuilder::DeckBuilder()
{
	cardcountx = 6;
	cardcounty = 5;
	decklistpos = 0;
	cardlistpos = 0;

	hovercard = sf::Sprite();
	hovercard.setPosition(HOVERCARDX, HOVERCARDY);

	exitbutton = Button(sf::Vector2f(QUITBUTTONX, QUITBUTTONY), sf::Vector2f(QUITBUTTONLENGTH, QUITBUTTONHEIGHT), sf::Color::White,
		3, sf::Color::Green, sf::Color::Black, "Main Menu", 16);
	loadbutton = Button(sf::Vector2f(ENDTURNX, ENDTURNY - BUTTONSEPERATION), sf::Vector2f(BUTTONLENGTH, BUTTONHEIGHT), sf::Color::White,
		3, sf::Color::Blue, sf::Color::Black, "Load Deck", 16);
	savebutton = Button(sf::Vector2f(ENDTURNX, ENDTURNY), sf::Vector2f(BUTTONLENGTH, BUTTONHEIGHT), sf::Color::White,
		3, sf::Color::Blue, sf::Color::Black, "Save Deck", 16);
	newbutton = Button(sf::Vector2f(ENDTURNX, ENDTURNY + BUTTONSEPERATION), sf::Vector2f(BUTTONLENGTH, BUTTONHEIGHT), sf::Color::White,
		3, sf::Color::Blue, sf::Color::Black, "New Deck", 16);

	civbutton[0] = Button(sf::Vector2f(HOVERCARDX + 250, HOVERCARDY), sf::Vector2f(80, BUTTONHEIGHT), sf::Color::White, 3, CivColors[0], sf::Color::Black, "Light", 16);
	civbutton[1] = Button(sf::Vector2f(HOVERCARDX + 250, HOVERCARDY + 35), sf::Vector2f(80, BUTTONHEIGHT), sf::Color::White, 3, CivColors[1], sf::Color::Black, "Nature", 16);
	civbutton[2] = Button(sf::Vector2f(HOVERCARDX + 250, HOVERCARDY + 70), sf::Vector2f(80, BUTTONHEIGHT), sf::Color::White, 3, CivColors[2], sf::Color::Black, "Water", 16);
	civbutton[3] = Button(sf::Vector2f(HOVERCARDX + 250, HOVERCARDY + 105), sf::Vector2f(80, BUTTONHEIGHT), sf::Color::White, 3, CivColors[3], sf::Color::Black, "Fire", 16);
	civbutton[4] = Button(sf::Vector2f(HOVERCARDX + 250, HOVERCARDY + 140), sf::Vector2f(80, BUTTONHEIGHT), sf::Color::White, 3, CivColors[4], sf::Color::Black, "Darkness", 16);

	sortbutton[0] = Button(sf::Vector2f(HOVERCARDX + 350, HOVERCARDY), sf::Vector2f(BUTTONLENGTH, BUTTONHEIGHT), sf::Color::White, 3, ActiveButtonColor, sf::Color::Black, "Sort: Name", 16);
	sortbutton[1] = Button(sf::Vector2f(HOVERCARDX + 350, HOVERCARDY + 35), sf::Vector2f(BUTTONLENGTH, BUTTONHEIGHT), sf::Color::White, 3, InactiveButtonColor, sf::Color::Black, "Sort: Cost", 16);
	sortbutton[2] = Button(sf::Vector2f(HOVERCARDX + 350, HOVERCARDY + 70), sf::Vector2f(BUTTONLENGTH, BUTTONHEIGHT), sf::Color::White, 3, InactiveButtonColor, sf::Color::Black, "Sort: Civ", 16);
	sortbutton[3] = Button(sf::Vector2f(HOVERCARDX + 350, HOVERCARDY + 105), sf::Vector2f(BUTTONLENGTH, BUTTONHEIGHT), sf::Color::White, 3, InactiveButtonColor, sf::Color::Black, "Sort: Race", 16);
	sortbutton[4] = Button(sf::Vector2f(HOVERCARDX + 350, HOVERCARDY + 140), sf::Vector2f(BUTTONLENGTH, BUTTONHEIGHT), sf::Color::White, 3, InactiveButtonColor, sf::Color::Black, "Sort: Type", 16);

	for (int i = 0; i < 5; i++)
	{
		civfilter[i] = 1;
	}
	sortby = SORTBY_NAME;

	MouseX = MouseY = 0;

	int count = 0;
	for (int i = 0; i < cardcounty; i++)
	{
		for (int j = 0; j < cardcountx; j++)
		{
			cardsprites.push_back(sf::Sprite());
			cardsprites[count] = sf::Sprite(CardTextures.at(count));
			cardsprites[count].setPosition(j * 125, i * 155);
			cardsprites[count].setScale(2*CARD_SCALE, 2*CARD_SCALE);
			count++;
		}
	}

	string currentdeck = "";
	isloadingdeck = 0;

	deckfile.open("Decks\\My Decks\\decklist.txt", ios::out | ios::in);
	if (!deckfile.is_open())
	{
		cout << "ERROR cant open deckfile, please restart" << endl;
	}
	while (!deckfile.eof())
	{
		string s;
		getline(deckfile, s);
		decks.push_back(s);
	}
	deckfile.close();

	generateCardList();
}

DeckBuilder::~DeckBuilder()
{
	deckfile.close();
}

void DeckBuilder::render(sf::RenderWindow& window)
{
	exitbutton.render(window);
	savebutton.render(window);
	loadbutton.render(window);
	newbutton.render(window);

	for (int i = 0; i < 5; i++)
	{
		civbutton[i].render(window);
		sortbutton[i].render(window);
	}

	if (isloadingdeck == 1)
	{
		sf::Text t("Choose Deck: ", DefaultFont, 16);
		t.setPosition(HOVERCARDX, HOVERCARDY - 100);
		window.draw(t);

		int count = 0;
		for (vector<string>::iterator i = decks.begin(); i != decks.end(); i++)
		{
			if (count >= decklistpos)
			{
				string s = *i;
				sf::RectangleShape r(sf::Vector2f(150, 20));
				r.setPosition(DECKLISTX, DECKLISTY + DECKLISTSEPERATION*(count - decklistpos));
				r.setFillColor(sf::Color::White);
				window.draw(r);
				sf::Text t(s, DefaultFont, 14);
				t.setColor(sf::Color::Black);
				t.setPosition(DECKLISTX + CARDZONEOFFSET, DECKLISTY + DECKLISTSEPERATION*(count - decklistpos) + CARDZONEOFFSET);
				window.draw(t);
			}
			count++;
			if (count >= decklistpos + DECKLISTCOUNT)
			{
				break;
			}
		}
	}
	if (isloadingdeck == 0)
	{
		sf::Text t("Deck Name: " + currentdeck, DefaultFont, 16);
		t.setPosition(HOVERCARDX, HOVERCARDY - BUTTONSEPERATION);
		window.draw(t);

		int count = 0;
		for (vector<DeckItem>::iterator i = decklist.begin(); i != decklist.end(); i++)
		{
			if (count >= decklistpos)
			{
				string s = std::to_string((*i).count) + " " + CardNames.at((*i).card);
				sf::RectangleShape r(sf::Vector2f(DECKLISTLENGTH, 20));
				r.setPosition(DECKLISTX, DECKLISTY + DECKLISTSEPERATION*(count - decklistpos));
				r.setFillColor(sf::Color::White);
				window.draw(r);
				sf::Text t(s, DefaultFont, 14);
				t.setColor(sf::Color::Black);
				t.setPosition(DECKLISTX + CARDZONEOFFSET, DECKLISTY + DECKLISTSEPERATION*(count - decklistpos) + CARDZONEOFFSET);
				window.draw(t);
			}
			count++;
			if (count >= decklistpos + DECKLISTCOUNT)
			{
				break;
			}
		}
	}

	for (vector<sf::Sprite>::iterator i = cardsprites.begin(); i != cardsprites.end(); i++)
	{
		window.draw(*i);
	}

	//draw hovercard
	int count = 0;
	for (vector<sf::Sprite>::iterator i = cardsprites.begin(); i != cardsprites.end(); i++)
	{
		if (checkCollision((*i).getGlobalBounds(), MouseX, MouseY))
		{
			if (cardlistpos*cardcountx + count < cardlist.size())
			{
				hovercard.setTexture(CardTextures.at(cardlist.at(cardlistpos*cardcountx + count).CardId));
				window.draw(hovercard);
			}
		}
		count++;
	}

	if (isloadingdeck == 0)
	{
		int card = getCardAtPos(MouseX, MouseY);
		if (card != -1)
		{
			hovercard.setTexture(CardTextures.at(decklist.at(card).card));
			window.draw(hovercard);
		}
	}
}

int DeckBuilder::handleEvent(sf::Event e, int callback)
{
	if (e.type == sf::Event::MouseMoved)
	{
		MouseX = e.mouseMove.x;
		MouseY = e.mouseMove.y;
	}
	else if (e.type == sf::Event::TextEntered)
	{
		if (isloadingdeck == 0)
		{
			if (e.text.unicode == 8) //backspace
			{
				if (currentdeck.size() > 0)
				{
					currentdeck = currentdeck.substr(0, currentdeck.size() - 1);
				}
			}
			else if ((e.text.unicode >= 'a' && e.text.unicode <= 'z') || (e.text.unicode >= 'A' && e.text.unicode <= 'Z')
				|| (e.text.unicode >= '0' && e.text.unicode <= '9') || e.text.unicode == '_' || e.text.unicode == ' ')
			{
				currentdeck += e.text.unicode;
			}
		}
	}
	else  if (e.type == sf::Event::MouseWheelMoved)
	{
		if (MouseX < 125 * cardcountx + 50)
		{
			cardlistpos -= e.mouseWheel.delta;
			if (cardlistpos < 0)
			{
				cardlistpos = 0;
			}
			if (cardlistpos > cardlist.size() / cardcountx)
			{
				cardlistpos = cardlist.size() / cardcountx;
			}

			int hori = 0;
			int vert = 0;
			for (vector<sf::Sprite>::iterator i = cardsprites.begin(); i != cardsprites.end(); i++)
			{
				int index = (cardlistpos + vert)*cardcountx + hori;
				if (index < cardlist.size())
				{
					(*i).setTexture(CardTextures.at(cardlist.at(index).CardId), true);
				}
				else
				{
					(*i).setTexture(sf::Texture(), true);
				}
				hori++;
				if (hori >= cardcountx)
				{
					hori = 0;
					vert++;
				}
			}
		}
		else
		{
			decklistpos -= e.mouseWheel.delta;
			if (decklistpos < 0)
			{
				decklistpos = 0;
			}
			if (decklistpos >= decklist.size())
			{
				decklistpos = decklist.size() - 1;
			}
		}
	}
	else if (e.type == sf::Event::MouseButtonPressed)
	{
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			if (isloadingdeck == 0)
			{
				int count = 0;
				for (vector<sf::Sprite>::iterator i = cardsprites.begin(); i != cardsprites.end(); i++)
				{
					if (checkCollision((*i).getGlobalBounds(), MouseX, MouseY))
					{
						int index = cardlistpos*cardcountx + count;
						if (getCardCount(cardlist.at(index).CardId) < 4)
						{
							addCard(cardlist.at(index).CardId);
						}
					}
					count++;
				}

				int card = getCardAtPos(MouseX, MouseY);
				if (card != -1)
				{
					if (getCardCount(decklist.at(card).card) < 4)
					{
						addCard(decklist.at(card).card);
					}
				}
			}

			for (int i = 0; i < 5; i++)
			{
				if (sortbutton[i].collision(MouseX, MouseY))
				{
					sortby = i;
					for (int j = 0; j < 5; j++)
					{
						if (i != j)
						{
							sortbutton[j].setBorderColor(InactiveButtonColor);
						}
						else
						{
							sortbutton[j].setBorderColor(ActiveButtonColor);
						}
					}
					generateCardList();
				}
				if (civbutton[i].collision(MouseX, MouseY))
				{
					civfilter[i] = (civfilter[i] + 1) % 2;
					if (civfilter[i] == 0)
					{
						civbutton[i].setBorderColor(InactiveButtonColor);
					}
					else
					{
						civbutton[i].setBorderColor(CivColors[i]);
					}
					generateCardList();
				}
			}

			if (exitbutton.collision(MouseX, MouseY)) //go to main menu
			{
				currentWindow = static_cast<GameWindow*>(mainMenu);
			}
			if (loadbutton.collision(MouseX, MouseY))
			{
				isloadingdeck = 1;
				decklistpos = 0;
				currentdeck = "";
			}
			if (savebutton.collision(MouseX, MouseY))
			{
				if (currentdeck != "")
				{
					savedeck();
				}
			}
			if (newbutton.collision(MouseX, MouseY))
			{
				decklist.clear();
				currentdeck = "New Deck";
				isloadingdeck = 0;
				decklistpos = 0;
			}

			if (isloadingdeck == 1)
			{
				int d = getDeckAtPos(MouseX, MouseY);
				if (d != -1)
				{
					currentdeck = decks.at(d);
					loaddeck();
					isloadingdeck = 0;
					decklistpos = 0;
				}
			}
		}
		else if (e.mouseButton.button == sf::Mouse::Right)
		{
			if (isloadingdeck == 0)
			{
				int count = 0;
				for (vector<sf::Sprite>::iterator i = cardsprites.begin(); i != cardsprites.end(); i++)
				{
					if (checkCollision((*i).getGlobalBounds(), MouseX, MouseY))
					{
						int index = cardlistpos*cardcountx + count;
						if (getCardCount(cardlist.at(index).CardId) > 0)
						{
							removeCard(cardlist.at(index).CardId);
						}
					}
					count++;
				}

				int card = getCardAtPos(MouseX, MouseY);
				if (card != -1)
				{
					if (getCardCount(decklist.at(card).card) > 0)
					{
						removeCard(decklist.at(card).card);
					}
				}
			}
		}
	}
	return RETURN_NOTHING;
}

void DeckBuilder::generateCardList()
{
	cardlist.clear();
	cardlistpos = 0;

	for (vector<CardData>::iterator i = CardDatabase.begin(); i != CardDatabase.end(); i++)
	{
		int civ = (*i).Civilization;
		if (civfilter[civ] == 1)
		{
			cardlist.push_back(*i);
		}
	}
	
	if (sortby == SORTBY_NAME)
	{
		for (int i = 0; i < cardlist.size(); i++)
		{
			for (int j = 0; j < cardlist.size() - 1 - i; j++)
			{
				if (cardlist.at(j).Name.compare(cardlist.at(j + 1).Name) > 0)
				{
					CardData d = cardlist.at(j);
					cardlist.at(j) = cardlist.at(j + 1);
					cardlist.at(j + 1) = d;
				}
			}
		}
	}
	else if (sortby == SORTBY_RACE)
	{
		for (int i = 0; i < cardlist.size(); i++)
		{
			for (int j = 0; j < cardlist.size() - 1 - i; j++)
			{
				if (cardlist.at(j).Race.compare(cardlist.at(j + 1).Race) > 0)
				{
					CardData d = cardlist.at(j);
					cardlist.at(j) = cardlist.at(j + 1);
					cardlist.at(j + 1) = d;
				}
			}
		}
	}
	else if (sortby == SORTBY_COST)
	{
		for (int i = 0; i < cardlist.size(); i++)
		{
			for (int j = 0; j < cardlist.size() - 1 - i; j++)
			{
				if (cardlist.at(j).ManaCost > cardlist.at(j + 1).ManaCost)
				{
					CardData d = cardlist.at(j);
					cardlist.at(j) = cardlist.at(j + 1);
					cardlist.at(j + 1) = d;
				}
			}
		}
	}
	else if (sortby == SORTBY_CIV)
	{
		for (int i = 0; i < cardlist.size(); i++)
		{
			for (int j = 0; j < cardlist.size() - 1 - i; j++)
			{
				if (cardlist.at(j).Civilization > cardlist.at(j + 1).Civilization)
				{
					CardData d = cardlist.at(j);
					cardlist.at(j) = cardlist.at(j + 1);
					cardlist.at(j + 1) = d;
				}
			}
		}
	}
	else if (sortby == SORTBY_TYPE)
	{
		for (int i = 0; i < cardlist.size(); i++)
		{
			for (int j = 0; j < cardlist.size() - 1 - i; j++)
			{
				if (cardlist.at(j).Type > cardlist.at(j + 1).Type)
				{
					CardData d = cardlist.at(j);
					cardlist.at(j) = cardlist.at(j + 1);
					cardlist.at(j + 1) = d;
				}
			}
		}
	}
	resetCardSprites();
}

void DeckBuilder::resetCardSprites()
{
	cardlistpos = 0;
	int count = 0;
	for (int i = 0; i < cardcounty; i++)
	{
		for (int j = 0; j < cardcountx; j++)
		{
			if (count >= cardlist.size())
			{
				break;
			}
			cardsprites[count].setTexture(CardTextures.at(cardlist.at(count).CardId), true);
			count++;
		}
	}
}

int DeckBuilder::getCardAtPos(int x, int y)
{
	int ans = -1;
	if (x >= DECKLISTX && x <= DECKLISTX + DECKLISTLENGTH)
	{
		if (y >= DECKLISTY && y <= DECKLISTY + DECKLISTCOUNT*DECKLISTSEPERATION)
		{
			ans = ((y - DECKLISTY) / DECKLISTSEPERATION) + decklistpos;
		}
	}
	if (ans >= decklist.size() || ans < 0)
	{
		ans = -1;
	}
	return ans;
}

int DeckBuilder::getDeckAtPos(int x, int y)
{
	int ans = -1;
	if (x >= DECKLISTX && x <= DECKLISTX + DECKLISTLENGTH)
	{
		if (y >= DECKLISTY && y <= DECKLISTY + DECKLISTCOUNT*DECKLISTSEPERATION)
		{
			ans = ((y - DECKLISTY) / DECKLISTSEPERATION) + decklistpos;
		}
	}
	if (ans >= decks.size() || ans < 0)
	{
		ans = -1;
	}
	return ans;
}

void DeckBuilder::loaddeck()
{
	decklist.clear();
	fstream file;
	file.open("Decks\\My Decks\\" + currentdeck + DECKEXTENSION, ios::in);
	string str;

	if (!file.is_open())
	{
		cout << "ERROR opening deck: " << currentdeck << endl;
	}

	while (!file.eof())
	{
		getline(file, str);
		if (str == "")
			continue;
		cout << "loading card " << str << endl;
		for (int i = 0; i < str.size(); i++)
		{
			if (str.at(i) == ' ')
			{
				int count = atoi(str.substr(0, i).c_str());
				string name = str.substr(i + 1);
				for (int j = 0; j < count; j++)
				{
					//decklist[getCardIdFromName(name)] = count;
					setCardCount(getCardIdFromName(name), count);
				}
				break;
			}
		}
	}

	file.close();
}

void DeckBuilder::savedeck()
{
	if (currentdeck == "" || isloadingdeck == 1) return;

	fstream file;
	file.open("Decks\\My Decks\\" + currentdeck + DECKEXTENSION, ios::out | ios::trunc);

	if (!file.is_open())
	{
		cout << "ERROR opening deck: " << currentdeck << endl;
	}

	for (vector<DeckItem>::iterator i = decklist.begin(); i != decklist.end(); i++)
	{
		string s = std::to_string((*i).count) + " " + CardNames.at((*i).card);
		file << s << endl;
	}

	file.close();
}

void DeckBuilder::addCard(int cid)
{
	bool found = false;
	for (vector<DeckItem>::iterator i = decklist.begin(); i != decklist.end(); i++)
	{
		if ((*i).card == cid)
		{
			(*i).count++;
			found = true;
			break;
		}
	}
	if (!found)
	{
		DeckItem d;
		d.count = 1;
		d.card = cid;
		decklist.push_back(d);
	}
}

void DeckBuilder::removeCard(int cid)
{
	for (vector<DeckItem>::iterator i = decklist.begin(); i != decklist.end(); i++)
	{
		if ((*i).card == cid)
		{
			(*i).count--;
			if ((*i).count == 0)
			{
				decklist.erase(i);
			}
			break;
		}
	}
}

int DeckBuilder::getCardCount(int cid)
{
	for (vector<DeckItem>::iterator i = decklist.begin(); i != decklist.end(); i++)
	{
		if ((*i).card == cid)
		{
			return (*i).count;
		}
	}
	return 0;
}

void DeckBuilder::setCardCount(int cid, int count)
{
	bool found = false;
	for (vector<DeckItem>::iterator i = decklist.begin(); i != decklist.end(); i++)
	{
		if ((*i).card == cid)
		{
			(*i).count = count;
			found = true;
			break;
		}
	}
	if (!found)
	{
		DeckItem d;
		d.count = count;
		d.card = cid;
		decklist.push_back(d);
	}
}

void DeckBuilder::update(unsigned int deltatime)
{
}

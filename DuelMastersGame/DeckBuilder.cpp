#include "DeckBuilder.h"

DeckBuilder::DeckBuilder()
{
	cardcountx = 3;
	cardcounty = 2;
	decklistpos = 0;
	cardlistpos = 0;

	exitbutton = Button(sf::Vector2f(QUITBUTTONX, QUITBUTTONY), sf::Vector2f(QUITBUTTONLENGTH, QUITBUTTONHEIGHT), sf::Color::White,
		3, sf::Color::Green, sf::Color::Black, "Main Menu", 16);

	MouseX = MouseY = 0;

	int count = 0;
	for (int i = 0; i < cardcounty; i++)
	{
		for (int j = 0; j < cardcountx; j++)
		{
			cardsprites.push_back(sf::Sprite());
			cardsprites[count] = sf::Sprite(CardTextures.at(count));
			cardsprites[count].setPosition(j * 250, i * 350);
			count++;
		}
	}
}

DeckBuilder::~DeckBuilder()
{
}

void DeckBuilder::render(sf::RenderWindow& window)
{
	exitbutton.render(window);
	for (vector<sf::Sprite>::iterator i = cardsprites.begin(); i != cardsprites.end(); i++)
	{
		window.draw(*i);
	}
	int count = 0;
	for (map<int, int>::iterator i = decklist.begin(); i != decklist.end(); i++)
	{
		if (count < decklistpos)
			continue;
		string s = std::to_string(i->second) + " " + CardNames.at(i->first);
		sf::RectangleShape r(sf::Vector2f(150, 20));
		r.setPosition(CARDSEARCHX, CARDSEARCHY + CARDSEARCHSEPERATION*count);
		r.setFillColor(sf::Color::White);
		window.draw(r);
		sf::Text t(s, DefaultFont, 14);
		t.setColor(sf::Color::Black);
		t.setPosition(CARDSEARCHX + CARDZONEOFFSET, CARDSEARCHY + CARDSEARCHSEPERATION*count + CARDZONEOFFSET);
		window.draw(t);
		count++;
		if (count >= decklistpos + CARDSEARCHITEMCOUNT)
		{
			break;
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
	else  if (e.type == sf::Event::MouseWheelMoved)
	{
		if (MouseX < 250 * cardcountx + 50)
		{
			cardlistpos -= e.mouseWheel.delta;
			if (cardlistpos < 0)
			{
				cardlistpos = 0;
			}
			if (cardlistpos > CardNames.size() / cardcountx)
			{
				cardlistpos = CardNames.size() / cardcountx;
			}

			int hori = 0;
			int vert = 0;
			for (vector<sf::Sprite>::iterator i = cardsprites.begin(); i != cardsprites.end(); i++)
			{
				int index = (cardlistpos + vert)*cardcountx + hori;
				if (index < CardTextures.size())
				{
					(*i).setTexture(CardTextures.at(index), true);
					hori++;
					if (hori >= cardcountx)
					{
						hori = 0;
						vert++;
					}
				}
				else
				{
					break;
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
				decklistpos = decklist.size()-1;
			}
		}
	}
	else if (e.type == sf::Event::MouseButtonPressed)
	{
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			int count = 0;
			for (vector<sf::Sprite>::iterator i = cardsprites.begin(); i != cardsprites.end(); i++)
			{
				if (checkCollision((*i).getGlobalBounds(), MouseX, MouseY))
				{
					if (decklist[count] < 4)
					{
						decklist[count]++;
					}
				}
				count++;
			}

			if (exitbutton.collision(MouseX, MouseY)) //go to main menu
			{
				currentWindow = static_cast<GameWindow*>(mainMenu);
			}
		}
		else if (e.mouseButton.button == sf::Mouse::Right)
		{
			int count = 0;
			for (vector<sf::Sprite>::iterator i = cardsprites.begin(); i != cardsprites.end(); i++)
			{
				if (checkCollision((*i).getGlobalBounds(), MouseX, MouseY))
				{
					if (decklist[count] > 0)
					{
						decklist[count]--;
					}
					if (decklist[count] == 0)
					{
						decklist.erase(count);
					}
				}
				count++;
			}
		}
	}
	return RETURN_NOTHING;
}

void DeckBuilder::update(unsigned int deltatime)
{
}

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
	else if (e.type == sf::Event::MouseButtonPressed)
	{
		if (e.mouseButton.button == sf::Mouse::Left)
		{
			if (exitbutton.collision(MouseX, MouseY))
			{
				currentWindow = static_cast<GameWindow*>(mainMenu);
			}
		}
	}
	return RETURN_NOTHING;
}

void DeckBuilder::update(unsigned int deltatime)
{
}

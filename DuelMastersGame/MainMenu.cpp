#include "MainMenu.h"

MainMenu::MainMenu()
{
	MouseX = 0;
	MouseY = 0;
	title = sf::Text("Duel Masters", DefaultFont, 22);
	title.setPosition(300,200);
	play = Button(sf::Vector2f(300, 250), sf::Vector2f(150, 25), sf::Color::White, 3, sf::Color::Blue, sf::Color::Black, "Play", 16);
	deckbuilder = Button(sf::Vector2f(300, 300), sf::Vector2f(150, 25), sf::Color::White, 3, sf::Color::Blue, sf::Color::Black, "Deck Builder", 16);
	exit = Button(sf::Vector2f(300, 350), sf::Vector2f(150, 25), sf::Color::White, 3, sf::Color::Blue, sf::Color::Black, "Exit", 16);
}

MainMenu::~MainMenu()
{
}

void MainMenu::render(sf::RenderWindow& window)
{
	window.draw(title);
	play.render(window);
	deckbuilder.render(window);
	exit.render(window);
}

int MainMenu::handleEvent(sf::Event event, int callback)
{
	if (event.type == sf::Event::MouseMoved)
	{
		MouseX = event.mouseMove.x;
		MouseY = event.mouseMove.y;
	}
	else if (event.type == sf::Event::MouseButtonPressed)
	{
		if (event.mouseButton.button == sf::Mouse::Left)
		{
			if (play.collision(MouseX, MouseY))
			{
				SoundMngr->playSound(SOUND_BUTTONPRESS);
				currentWindow = (GameWindow*)(duelInterface);
			}
			else if (deckbuilder.collision(MouseX, MouseY))
			{
				SoundMngr->playSound(SOUND_BUTTONPRESS);
				currentWindow = (GameWindow*)(deckBuilder);
			}
			else if (exit.collision(MouseX, MouseY))
			{
				return RETURN_QUIT;
			}
		}
	}
	return RETURN_NOTHING;
}

void MainMenu::update(unsigned int deltatime)
{
}
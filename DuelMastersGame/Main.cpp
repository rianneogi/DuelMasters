#include "LuaFunctions.h"

DuelInterface* ActiveDuel;
sf::RenderWindow* Window;

int main()
{
	srand(time(0));
	if (loadfiles() != 0)
	{
		cout << "ERROR couldnt load files" << endl;
	}

	if (initCards() != 0)
	{
		cout << "ERROR couldnt init cards" << endl;
	}

	//createCardSprites();

	Window = new sf::RenderWindow(sf::VideoMode(1400,800), "Duel Masters");
	Window->setPosition(sf::Vector2i(0, 0));
	ActiveDuel = new DuelInterface();
	ActiveDuel->duel.setDecks("Decks\\test.txt", "Decks\\test.txt");
	ActiveDuel->duel.startDuel();

	while (Window->isOpen())
	{
		sf::Event event;
		while (Window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				ActiveDuel->handleEvent(event, 0);
				Window->close();
			}
			ActiveDuel->handleEvent(event, 0);
			ActiveDuel->update(0);
		}

		Window->clear();

		ActiveDuel->render(*Window);

		Window->display();
	}

	delete ActiveDuel;
	delete Window;
	cleanupCards();
	
	return 0;
}
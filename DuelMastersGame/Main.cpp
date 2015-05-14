#include "LuaFunctions.h"

DuelInterface* ActiveDuel;

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

	sf::RenderWindow window(sf::VideoMode(1400,800), "Duel Masters");
	window.setPosition(sf::Vector2i(0, 0));
	ActiveDuel = new DuelInterface();
	ActiveDuel->duel.setDecks("Decks\\DeathbladeBeetle.txt", "Decks\\Zagaan.txt");
	ActiveDuel->duel.startDuel();

	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				ActiveDuel->handleEvent(event);
				window.close();
			}
			ActiveDuel->handleEvent(event);
			ActiveDuel->update(0);
		}

		window.clear();

		ActiveDuel->render(window);

		window.display();
	}

	delete ActiveDuel;
	cleanupCards();
	
	return 0;
}
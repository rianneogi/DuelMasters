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

	Window = new sf::RenderWindow(sf::VideoMode(1400,800), "Duel Masters");
	Window->setPosition(sf::Vector2i(0, 0));
	ActiveDuel = new DuelInterface();
	ActiveDuel->duel.setDecks("Decks\\yash.txt", "Decks\\Rian Deck.txt");
	ActiveDuel->duel.startDuel();

	mainLoop(*Window, 0);

	delete ActiveDuel;
	delete Window;
	cleanupCards();
	
	return 0;
}
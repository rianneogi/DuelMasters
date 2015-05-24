#include "LuaFunctions.h"

DuelInterface* ActiveDuel;
MainMenu* mainMenu;
DeckBuilder* deckBuilder;

GameWindow* currentWindow;

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

	Window = new sf::RenderWindow(sf::VideoMode(1300,800), "Duel Masters");
	Window->setPosition(sf::Vector2i(0, 0));
	ActiveDuel = new DuelInterface();
	ActiveDuel->duel.setDecks("Decks\\My decks\\DF Unholy Fire.txt", "Decks\\My decks\\F Bolshack.txt");
	ActiveDuel->duel.startDuel();

	mainMenu = new MainMenu();
	deckBuilder = new DeckBuilder();

	currentWindow = static_cast<GameWindow*>(mainMenu);

	mainLoop(*Window, 0);

	delete ActiveDuel;
	delete deckBuilder;
	delete mainMenu;
	delete Window;

	cleanupCards();
	
	return 0;
}
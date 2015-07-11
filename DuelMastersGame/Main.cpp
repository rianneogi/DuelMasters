#include "LuaFunctions.h"

DuelInterface* ActiveDuel;
MainMenu* mainMenu;
DeckBuilder* deckBuilder;

GameWindow* currentWindow;
SoundManager* SoundMngr;

sf::RenderWindow* Window;

sf::TcpSocket Socket;

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

			if (callback != 0 && r != RETURN_NOTHING) //if we need to callback(return) and a choice has been made
			{
				return r;
			}
			if (r == RETURN_QUIT)
			{
				window.close();
			}
		}
		
		if (Socket.receive(packet) != sf::Socket::Status::NotReady)
		{
			int r = ActiveDuel->receivePacket(packet, callback);
			if (callback != 0 && r != RETURN_NOTHING)
			{
				return r;
			}
		}

		currentWindow->update(0);

		window.clear();

		currentWindow->render(window);

		window.display();
	}
	return RETURN_NOTHING;
}

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

	sf::VideoMode vm = sf::VideoMode::getFullscreenModes().at(0);
	cout << "Video Mode width: " << vm.width << ", height: " << vm.height << ", bpp: " << vm.bitsPerPixel << endl;
	Window = new sf::RenderWindow(vm, "Duel Masters", sf::Style::Fullscreen);
	Window->setPosition(sf::Vector2i(0, 0));

	SoundMngr = new SoundManager();
	ActiveDuel = new DuelInterface();
	mainMenu = new MainMenu();
	deckBuilder = new DeckBuilder();

	currentWindow = static_cast<GameWindow*>(mainMenu);

	mainLoop(*Window, 0);

	delete ActiveDuel;
	delete deckBuilder;
	delete mainMenu;
	delete SoundMngr;
	delete Window;

	cleanupCards();
	
	return 0;
}
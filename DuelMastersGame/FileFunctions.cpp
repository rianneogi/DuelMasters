#include "FileFunctions.h"

vector<sf::Texture> Textures;
vector<sf::SoundBuffer> Sounds;
vector<sf::Sprite> Sprites;
vector<sf::Texture> CardTextures;
vector<sf::Sprite> CardSprites;
vector<string> CardNames;

sf::Font DefaultFont;

int loadfiles()
{
	Textures.push_back(sf::Texture());
	if (!Textures.at(0).loadFromFile("Graphics\\cardback.png"))
	{
		cout << "ERROR couldnt load texture cardback" << endl;
		return -1;
	}

	Sounds.push_back(sf::SoundBuffer());
	if (!Sounds.at(0).loadFromFile("Graphics\\endturn.wav"))
	{
		cout << "ERROR couldnt load endturn sound" << endl;
		return -1;
	}

	if (!DefaultFont.loadFromFile("Graphics\\OxygenMono.ttf"))
	{
		cout << "ERROR couldnt load font" << endl;
		return -2;
	}

	/*for (int i = 0; i < Textures.size(); i++)
	{
		Sprites.push_back(sf::Sprite(Textures.at(i)));
	}
	Sprites.at(0).setScale(CARD_SCALE, CARD_SCALE);*/
	
	return 0;
}

int createCardSprites()
{
	for (int i = 0; i < CardTextures.size(); i++)
	{
		CardSprites.push_back(sf::Sprite());
		CardSprites[i] = sf::Sprite(CardTextures.at(i));
		CardSprites[i].setScale(CARD_SCALE, CARD_SCALE);
	}
	return 0;
}
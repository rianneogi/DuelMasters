#include "FileFunctions.h"

deque<sf::Texture> Textures;
deque<sf::SoundBuffer> SoundBuffers;
deque<sf::Sprite> Sprites;
deque<sf::Texture> CardTextures;
deque<sf::Sprite> CardSprites;
deque<string> CardNames;

sf::Font DefaultFont;

int loadfiles()
{
	Textures.push_back(sf::Texture());
	if (!Textures.at(0).loadFromFile("Graphics\\cardback.png"))
	{
		cout << "ERROR couldnt load texture cardback" << endl;
		return -1;
	}

	for (int i = 0; i < SoundCount; i++)
	{
		SoundBuffers.push_back(sf::SoundBuffer());
		if (!SoundBuffers.at(i).loadFromFile(SoundPaths[i]))
		{
			cout << "ERROR couldnt load sound no. " << i << endl;
			return -2;
		}
	}

	if (!DefaultFont.loadFromFile("Graphics\\OxygenMono.ttf"))
	{
		cout << "ERROR couldnt load font" << endl;
		return -3;
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
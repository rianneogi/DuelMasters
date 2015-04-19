#pragma once

#include "Constants.h"

#include <iostream>
#include "conio.h"
#include <fstream>

#include "SFML\Graphics.hpp"
#include "SFML\Audio.hpp"
#include "SFML\Network.hpp"
#include "SFML\Window.hpp"

extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

using namespace std;

enum SpriteId { TEXTURE_CARDBACK };
enum SoundId { SOUND_ENDTURN };

extern vector<sf::Texture> Textures;
extern vector<sf::SoundBuffer> Sounds;
extern vector<sf::Sprite> Sprites;

extern vector<sf::Texture> CardTextures;
extern vector<sf::Sprite> CardSprites;
extern vector<string> CardNames;

extern sf::Font DefaultFont;

int loadfiles();
int createCardSprites();

void registerLua(lua_State* L);

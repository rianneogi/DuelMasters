#pragma once

#include "Constants.h"

#include <iostream>
#include "conio.h"
#include <fstream>

extern "C"
{
	#include "lua.h"
	#include "lualib.h"
	#include "lauxlib.h"
}

using namespace std;

const string DECKEXTENSION = ".txt";

enum SpriteId { TEXTURE_CARDBACK };

enum SoundId { SOUND_ENDTURN, SOUND_DRAW, SOUND_TAP, SOUND_UNTAP, SOUND_PLAY, SOUND_SHUFFLE, SOUND_BUTTONPRESS, SOUND_BUTTONUNPRESS };
const string SoundPaths[] = { "Graphics\\Sounds\\endturn.wav", "Graphics\\Sounds\\draw.wav", "Graphics\\Sounds\\tap.wav",
"Graphics\\Sounds\\untap.wav", "Graphics\\Sounds\\playcard.wav", "Graphics\\Sounds\\shuffle.wav", "Graphics\\Sounds\\Button1.wav", "Graphics\\Sounds\\Button2.wav" };
const int SoundCount = 8;

extern vector<sf::Texture> Textures;
extern vector<sf::SoundBuffer> SoundBuffers;
extern vector<sf::Sprite> Sprites;

extern vector<sf::Texture> CardTextures;
extern vector<sf::Sprite> CardSprites;
extern vector<string> CardNames;

extern sf::Font DefaultFont;

int loadfiles();
int createCardSprites();

void registerLua(lua_State* L);

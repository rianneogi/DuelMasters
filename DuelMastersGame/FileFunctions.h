#pragma once

#include "Constants.h"

#include <iostream>
#include "conio.h"
#include <fstream>
#include <deque>

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

extern deque<sf::Texture> Textures;
extern deque<sf::SoundBuffer> SoundBuffers;
extern deque<sf::Sprite> Sprites;

extern deque<sf::Texture> CardTextures;
extern deque<sf::Sprite> CardSprites;
extern deque<string> CardNames;

extern sf::Font DefaultFont;

int loadfiles();
int createCardSprites();

void registerLua(lua_State* L);

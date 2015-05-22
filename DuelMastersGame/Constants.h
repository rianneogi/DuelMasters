#pragma once

const float CARD_SCALE = 0.20;

const int CARDSEPERATION = 65;
const int CARDZONEOFFSET = 5;
const int CARDORIGINOFFSET = (307/2) * CARD_SCALE;

const int ZONEBORDERSIZE = 3;

const int CENTER = 360;
const int ZONEYOFFSET = CARDSEPERATION + 3 * CARDZONEOFFSET;
const int ZONE1X = 100;
const int ZONE2X = 700;

const int INFOBOXX = 800;
const int INFOBOXY = CENTER - ZONEYOFFSET * 3;

const int HOVERCARDX = INFOBOXX + CARDZONEOFFSET;
const int HOVERCARDY = INFOBOXY + CARDZONEOFFSET;

const int INFOTEXTX = INFOBOXX;
const int INFOTEXTY = CENTER + ZONEYOFFSET;

const int CANCELBOXX = INFOTEXTX;
const int CANCELBOXY = INFOTEXTY + 30;

const int ENDTURNX = INFOBOXX;
const int ENDTURNY = INFOTEXTY + 90;
const int ENDTURNLENGTH = 150;
const int ENDTURNHEIGHT = 40;

const int QUITBUTTONX = INFOBOXX;
const int QUITBUTTONY = ENDTURNY + 90;
const int QUITBUTTONLENGTH = ENDTURNLENGTH;
const int QUITBUTTONHEIGHT = ENDTURNHEIGHT;

const int CARDSEARCHX = HOVERCARDX + 250;
const int CARDSEARCHY = INFOBOXY;
const int CARDSEARCHSEPERATION = 20;
const int CARDSEARCHITEMCOUNT = 25;

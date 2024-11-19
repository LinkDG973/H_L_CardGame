#pragma once

#include <iostream>

#include <assert.h>

typedef unsigned __int8 ui8; // Type Declaration for unsinged 8-bit integers

typedef ui8 ERROR_CODE; // Error Code Type
static ERROR_CODE ret_code;  // Error Check Return Variable
#define GAME_OK 0	// Clean Error Code

constexpr ui8 MAX_DECK_SIZE = 54;
constexpr ui8 DEFAULT_DECK_SIZE = 52;

constexpr char SUITS[4] = { 'H','S','D','C' };




#pragma once

#include <iostream>

#include <assert.h>

using namespace std;

typedef unsigned __int8 ui8; // Type Declaration for unsinged 8-bit integers

typedef ui8 ERROR_CODE; // Error Code Type
static ERROR_CODE ret_code;  // Error Check Return Variable
#define GAME_OK 0	// Clean Error Code

constexpr ui8 MAX_DECK_SIZE = 54;
constexpr ui8 DEFAULT_DECK_SIZE = 52;
constexpr ui8 CARD_GRAPHIC_SIZE = 7;

constexpr wchar_t SUITS[4] = { L'♠', L'♦', L'♥', L'♣' };
static const std::wstring CARD_INDENT = L"           ";
static const std::wstring BOARDER = L"////////////////////////////";

static const std::wstring _FaceDownCard[CARD_GRAPHIC_SIZE] = {
	L"┌─────────┐",
	L"│┌───────┐│",
	L"│││││││││││",
	L"│││││││││││",
	L"│││││││││││",
	L"│└───────┘│",
	L"└─────────┘"
};




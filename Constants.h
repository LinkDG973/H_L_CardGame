#pragma once

#include <iostream>

#include <assert.h>

using namespace std;

typedef unsigned __int8 ui8; // Type Declaration for unsinged 8-bit integers

typedef ui8 ERROR_CODE; // Error Code Type
static ERROR_CODE ret_code;  // Error Check Return Variable
#define GAME_OK 0	// Clean Error Code

#define STATE_COUNT 4
#define START_STATE 0
#define SETUP_STATE 1
#define PLAY_STATE 2
#define END_STATE 3

constexpr ui8 MAX_DECK_SIZE = 54;
constexpr ui8 PLAY_DECK_SIZE = 10;
constexpr ui8 CARD_GRAPHIC_SIZE = 7;

constexpr ui8 ASCII_NUM_SHIFT = 48;

constexpr wchar_t SUITS[5] = { L'♠', L'♦', L'♥', L'♣', L'J' };
static const std::wstring CARD_INDENT = L"           ";
static const std::wstring SMALL_INDENT = L"   ";
static const std::wstring BOARDER = L"───────────────────────────────────────────────────────────────────────────────────";
static const int SCREEN_WIDTH = 83;

static const int STARTING_COIN_COUNT = 2000;

static const std::wstring _FaceDownCard[CARD_GRAPHIC_SIZE] = {
	L"┌─────────┐",
	L"│┌───────┐│",
	L"││ │ │ │ ││",
	L"││ │ │ │ ││",
	L"││ │ │ │ ││",
	L"│└───────┘│",
	L"└─────────┘"
};
static const std::wstring _Selector = L"     \u2571\u2572     ";
static const std::wstring _EmptySelector = L"           ";
static const std::wstring DEFAULT_ERROR_MSG = L"                          Invalid input, please try again.";

struct GameConfig {
	GameConfig() {};
	GameConfig(bool _J, bool _D, bool _C, bool _N, int _R)
		: _PWJokers(_J), _PWDuplicateCards(_D), _PWCoins(_C), _PWDlbNothing(_N), _NumPlaySets(_R) {};
	bool _PWJokers = true;
	bool _PWDuplicateCards = false;
	bool _PWCoins = true;
	bool _PWDlbNothing = true;
	int _NumPlaySets = 1;
};


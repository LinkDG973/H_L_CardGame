﻿#pragma once

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
constexpr ui8 FOCUS_DECK_SIZE = 51;
constexpr ui8 PLAY_DECK_SIZE = 10;
constexpr ui8 CARD_GRAPHIC_SIZE = 7;

constexpr ui8 ASCII_NUM_SHIFT = 48;

constexpr wchar_t SUITS[5] = { L'♠', L'♦', L'♥', L'♣', L'J' };
constexpr wchar_t INITALS[14] = { L'0', L'A', L'2', L'3', L'4', L'5', L'6', L'7', L'8', L'9', L'10', L'J', L'Q', L'K'};
static const std::wstring CARD_INDENT = L"           ";
static const int SCREEN_WIDTH = 83;
static const std::wstring BOARDER(SCREEN_WIDTH, L'─');

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
static const std::wstring _Selector = L"     \u2571\u2572    ";
static const std::wstring DEFAULT_ERROR_MSG = L"Invalid input, please try again.";

struct GameConfig {
	GameConfig() {};
	GameConfig(bool _J, bool _D, bool _C, bool _N, int _R, int _S)
		: _PWJokers(_J), _PWDuplicateCards(_D), _PWCoins(_C), _PWDlbNothing(_N), _NumPlaySets(_R), _Score(_S) {};
	bool _PWJokers = true;
	bool _PWDuplicateCards = false;
	bool _PWCoins = true;
	bool _PWDlbNothing = true;
	int _NumPlaySets = 1;
	int _Score = 0;
};

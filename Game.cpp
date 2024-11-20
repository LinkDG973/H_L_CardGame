
#include "Game.h"

#include <string>
#include <io.h>
#include <fcntl.h>
#include <sstream>  // Used to access stringstream library
#include <algorithm>

using namespace std;

ERROR_CODE Game::Init() {
	_setmode(_fileno(stdout), _O_U16TEXT);

	// Initalise the Deck
	ui8 num = 1;
	ui8 suit_index = 0;
	for (Card& _C : _Deck) {
		Card temp_Card(SUITS[suit_index], num++);
		GenerateGraphics(temp_Card);
		_C = temp_Card;
		if (num > 13) {
			num = 1;
			suit_index++;
		}
	}

	Draw_Cards(5, 13);

	return GAME_OK;
}

ERROR_CODE Game::GenerateGraphics(Card& _C) {
	wstringstream ss;

	wstringstream mSuit; // │    ♦    │
	mSuit << L"│    " << _C.GetSuit() << L"    │";

	wstringstream dSuit; // │  ♦   ♦  │
	dSuit << L"│  " << _C.GetSuit() << L"   " << _C.GetSuit() << L"  │";

	if (_C.GetVal() > 1 && _C.GetVal() <= 3) {
		ss << L"│" << _C.GetVal() << L"   " << _C.GetSuit() << L"    │"; // │{}{}     │
	}
	else if (_C.GetVal() > 3 && _C.GetVal() < 10) {
		ss << L"│"<< _C.GetVal() << L" " << _C.GetSuit() << L"   " << _C.GetSuit() << L"  │";
	}

	switch (_C.GetVal())
	{
	case 1: 
		ss << L"│A        │";
	case 3:
	case 5:
		_C.GetCardGraphic(3) = mSuit.str();
		break;
	case 8:
		_C.GetCardGraphic(2) = mSuit.str();
	case 7: 
		_C.GetCardGraphic(4) = mSuit.str();
	case 6:
		_C.GetCardGraphic(3) = dSuit.str();
		break;
	case 9: 
		_C.GetCardGraphic(2) = dSuit.str();
		_C.GetCardGraphic(3) = mSuit.str();
		_C.GetCardGraphic(4) = dSuit.str();
		break;
	case 10: 
		ss << L"│" << _C.GetVal() << _C.GetSuit() << L"   " << _C.GetSuit() << L"  │";
		_C.GetCardGraphic(2) = dSuit.str();
		_C.GetCardGraphic(3) = dSuit.str();
		_C.GetCardGraphic(4) = dSuit.str();
		break;
	case 11: 
		ss << L"│J " << _C.GetSuit() << L"   " << _C.GetSuit() << L"  │";
		break;
	case 12: 
		ss << L"│Q " << _C.GetSuit() << L"   " << _C.GetSuit() << L"  │";
		break;
	case 13: 
		ss << L"│K " << _C.GetSuit() << L"   " << _C.GetSuit() << L"  │";
		break;
	default:
		break;
	}

	_C.GetCardGraphic(1) = ss.str();
	_C.GetCardGraphic(5) = _C.GetCardGraphic(1);
	if (_C.GetVal() != 10)std::reverse(_C.GetCardGraphic(5).begin(), _C.GetCardGraphic(5).end());

	return GAME_OK;
}

ERROR_CODE Game::Draw_Card(Card& _C) {
	for (int i = 0; i < CARD_GRAPHIC_SIZE; ++i) {
		wcout << _C.GetCardGraphic(i) << endl;
	}

	return GAME_OK;
}

ERROR_CODE Game::Draw_Cards(int _C_Count, int _Columns) {
	for (int i = 0; i < DEFAULT_DECK_SIZE; i + 0) { // for the number of cards
		for (int x = 0; x < CARD_GRAPHIC_SIZE; ++x) { // for the number of graphics
			wstring _line = L"";
			int num = 0;
			for (int j = 0; j < _Columns; ++j) { // for the number of columns
				_line += _Deck[i + num].GetCardGraphic(x);
				++num;
			}
			wcout << _line << endl;
		}
		i += _Columns;
	}

	return GAME_OK;
}

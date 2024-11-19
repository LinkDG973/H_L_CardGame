
#include "Game.h"

#include <string>
#include <io.h>
#include <fcntl.h>

ERROR_CODE Game::Init() {
	_setmode(_fileno(stdout), _O_U16TEXT);

	// Initalise the Deck

	// H = Hearts, S = Spades, D = Diamonds, C = Clubs

	ui8 num = 1;
	ui8 suit_index = 0;
	for (Card& _C : _Deck) {
		Card temp_Card(SUITS[suit_index], num++);
		_C = temp_Card;
		if (num > 13) {
			num = 1;
			suit_index++;
		}
		Draw_Card(_C);
	}

	return GAME_OK;
}

ERROR_CODE Game::Draw_Card(Card& _C) {

		//"┌─────────┐"
		//"│{}{}     │"
		//"│         │"
		//"│         │"
		//"│    {}   │"
		//"│         │"
		//"│         │"
		//"│     {}{}│"
		//"└─────────┘"

	std::wcout << L"┌─────────┐\n";						 // ┌─────────┐
	std::wcout << L"│" << _C.GetVal() << L"        │\n"; // │         │
	std::wcout << L"│         │\n";						 // │         │
	std::wcout << L"│    " << _C.GetSuit() << L"    │\n";// │    ♠    │
	std::wcout << L"│         │\n";						 // │         │
	std::wcout << L"│        " << _C.GetVal() << L"│\n"; // │         │
	std::wcout << L"└─────────┘\n";						 // └─────────┘

	return GAME_OK;
}

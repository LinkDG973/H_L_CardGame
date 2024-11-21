#include "Game.h"
#include "States.h"

#include <cctype>

bool SetupState::CheckInput(char _Input) {
	switch (_Input) {
		case 'S':
			// setup game with set settings
			Game::getInstance().UpdateGameConfig(_PWJokers, _PWDuplicateCards, _PWCoins, _PWDlbNothing, _NumRows);
			Game::getInstance().SwitchState(PLAY_STATE);
			break;
		case 'J': _PWJokers = !_PWJokers; break;
		case 'D': _PWDuplicateCards = !_PWDuplicateCards; break;
		case 'C': _PWCoins = !_PWCoins; break;
		case 'N': _PWDlbNothing = !_PWDlbNothing; break;
		case '1': case '2': case '3': 
			_NumRows = int(_Input) - ASCII_NUM_SHIFT; break;
		default: return false; break;
	}

	return true;
}

wchar_t toggleChar(bool _toggle) {
	if (_toggle) {
		return L'╳';
	}
	return L' ';
}

void SetupState::Render() {
	wcout << BOARDER << endl << BOARDER << endl;
	for (int y = 0; y < 5; ++y) wcout << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"┌───────────────────────────────────────────────┒" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"│                  GAME SETUP                   ┃" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"├───────────────────────────────────────────┬───┨" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"│ Play with Jokers                      (J) │ " << toggleChar(_PWJokers) << L" ┃" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"├───────────────────────────────────────────┼───┨" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"│ Play with Duplicate Cards             (D) │ " << toggleChar(_PWDuplicateCards) << L" ┃" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"├───────────────────────────────────────────┼───┨" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"│ Play with Coins                       (C) │ " << toggleChar(_PWCoins) << L" ┃" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"├───────────────────────────────────────────┼───┨" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"│ Play with Double or Nothing Mode      (N) │ " << toggleChar(_PWDlbNothing) << L" ┃" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"├───────────────────────────────────────────┼───┨" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"│ Number of Card Rows           (1 / 2 / 3) │ " << _NumRows << L" ┃" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┷━━━┛" << endl;
	for (int y = 0; y < 5; ++y) wcout << endl;
	wcout << BOARDER << endl << BOARDER << endl;
	if (!_ValidInput) wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << L"Invalid input, please try again." << endl;
	wcout << CARD_INDENT << L"Select Option to toggle ON or OFF, type (S) to start game :" << endl 
		<< CARD_INDENT << CARD_INDENT << CARD_INDENT << L"\u2192 ";
}
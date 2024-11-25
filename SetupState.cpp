#include "Game.h"
#include "States.h"

#include <cctype>

bool SetupState::CheckInput(char _Input) {
	switch (_Input) {
		case 'B':
			Game::getInstance().UpdateGameConfig(_tempConfig); // setup game with set settings
			Game::getInstance().SwitchState(START_STATE);
			break;
		case 'J': _tempConfig._PWJokers = !_tempConfig._PWJokers; break;
		case 'D': _tempConfig._PWDuplicateCards = !_tempConfig._PWDuplicateCards; break;
		case 'C': _tempConfig._PWCoins = !_tempConfig._PWCoins; break;
		case 'N': _tempConfig._PWDlbNothing = !_tempConfig._PWDlbNothing; break;
		case '1': case '2': case '3':
			_tempConfig._NumPlaySets = int(_Input) - ASCII_NUM_SHIFT; break;
		default: return false; break;
	}
	return true;
}

wchar_t toggleChar(bool _toggle) {
	if (_toggle) { return L'╳'; }
	return L' ';
}

void SetupState::SpecificRender() {
	MakeSpace(5);
	wcout << CARD_INDENT << CARD_INDENT << L"┌───────────────────────────────────────────────┒" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"│                  GAME SETUP                   ┃" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"├───────────────────────────────────────────┬───┨" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"│ Play with Jokers                      (J) │ " << toggleChar(_tempConfig._PWJokers) << L" ┃" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"├───────────────────────────────────────────┼───┨" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"│ Play with Duplicate Cards             (D) │ " << toggleChar(_tempConfig._PWDuplicateCards) << L" ┃" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"├───────────────────────────────────────────┼───┨" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"│ Play with Coins                       (C) │ " << toggleChar(_tempConfig._PWCoins) << L" ┃" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"├───────────────────────────────────────────┼───┨" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"│ Play with Double or Nothing Mode      (N) │ " << toggleChar(_tempConfig._PWDlbNothing) << L" ┃" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"├───────────────────────────────────────────┼───┨" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"│ Number of card sets           (1 / 2 / 3) │ " << _tempConfig._NumPlaySets << L" ┃" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┷━━━┛" << endl;
	MakeSpace(6);
	SetCmdPromt(L"Select Option to toggle, type 'B' to Return to the Title Screen (B)");
}
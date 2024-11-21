#include "Game.h"
#include "States.h"

void SetupState::Update() {
	wstring _Input = L"";
	wcin >> _Input;

	if (_Input == L"start" || _Input == L"S" || _Input == L"s") {
		// setup game with set settings
		Game::getInstance().SwitchState(PLAY_STATE);
	}
	else if (_Input == L"J" || _Input == L"j") {
		_PWJokers = !_PWJokers;
	}
	else if (_Input == L"D" || _Input == L"d") {
		_PWDuplicateCards = !_PWDuplicateCards;
	}
	else if (_Input == L"C" || _Input == L"c") {
		_PWCoins = !_PWCoins;
	}
	else if (_Input == L"N" || _Input == L"n") {
		_PWDlbNothing = !_PWDlbNothing;
	}
	else {
		_ValidInput = false;
	}

}

wstring toggleChar(bool _toggle) {
	if (_toggle) {
		return L"╳";
	}
	else {
		return L" ";
	}
}

void SetupState::Render() {
	wcout << BOARDER << endl << BOARDER << endl;
	for (int y = 0; y < 5; ++y) wcout << endl;
	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << L"GAME SETUP" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"┌───────────────────────────────────────────┬───┒" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"│ Play with Jokers                      (J) │ " << toggleChar(_PWJokers) << L" ┃" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"├───────────────────────────────────────────┼───┨" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"│ Play with Duplicate Cards             (D) │ " << toggleChar(_PWDuplicateCards) << L" ┃" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"├───────────────────────────────────────────┼───┨" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"│ Play with Coins                       (C) │ " << toggleChar(_PWCoins) << L" ┃" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"├───────────────────────────────────────────┼───┨" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"│ Play with Double or Nothing Mode      (N) │ " << toggleChar(_PWDlbNothing) << L" ┃" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"├───────────────────────────────────────────┼───┨" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"│ Number of Card Rows           (1 / 2 / 3) │ " << toggleChar(false) << L" ┃" << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┷━━━┛" << endl;
	for (int y = 0; y < 5; ++y) wcout << endl;
	wcout << BOARDER << endl << BOARDER << endl;
	if (!_ValidInput) wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << L"Invalid input, please try again." << endl;
	wcout << CARD_INDENT << L"Select Option to toggle ON or OFF, type 'start' to start game :" << endl 
		<< CARD_INDENT << CARD_INDENT << CARD_INDENT << L"\u2192 ";


}
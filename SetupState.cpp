//====================================================================================
// NAME: SetupState.cpp
// DESC: Presents a settings table so the player can adjust game settings.
// AUTH: Oliver Callaghan
//====================================================================================
#include "Game.h"
#include "States.h"
//====================================================================================

// SUMMARY: Takes the player's input.
// PARAMETERS: CHAR - Player's Input Character Command.
// RETURNS: BOOL - Validation Result of Input
bool SetupState::CheckInput(char _Input) {
	switch (_Input) {
		case 'B':
			Game::getInstance().UpdateGameConfig(_tempConfig); // setup game with set settings
			Game::getInstance().SwitchState(START_STATE);
			break;
		case 'J': _tempConfig._PWJokers = !_tempConfig._PWJokers; break;
		case 'D': _tempConfig._PWDuplicateCards = !_tempConfig._PWDuplicateCards; break;
		case 'C': 
			_tempConfig._PWCoins = !_tempConfig._PWCoins; 
			if (_tempConfig._PWCoins == true) _tempConfig._Score = STARTING_COIN_COUNT;
			else _tempConfig._Score = 0;
			break;
		case 'N': _tempConfig._PWDlbNothing = !_tempConfig._PWDlbNothing; break;
		case '1': case '2': _tempConfig._NumPlaySets = int(_Input) - ASCII_NUM_SHIFT; break;
		default: return false; break;
	}
	return true;
}

// SUMMARY: Toggle Character function
// PARAMETERS: BOOL - State of selection to toggle.
// RETURNS: WCHAR_T - Character respective of toggle state (X - ON / ' ' - OFF)
wchar_t toggleChar(bool _toggle) {
	if (_toggle) { return L'╳'; }
	return L' ';
}

// SUMMARY: Draws settings Screen.
// RETURNS: VOID
void SetupState::SpecificRender() {
	MakeSpace(7); // Draw Settings Menu Table
	wcout << centreString(L"┌────────────────────────────────────────────────┒") << endl;
	wcout << centreString(L"│                   GAME SETUP                   ┃") << endl;
	wcout << centreString(L"├────────────────────────────────────────────┬───┨") << endl;
	wcout << L"                │ Play with Jokers                       (J) │ " << toggleChar(_tempConfig._PWJokers) << L" ┃" << endl;
	wcout << centreString(L"├────────────────────────────────────────────┼───┨") << endl;
	wcout << L"                │ Play with Duplicate Cards              (D) │ " << toggleChar(_tempConfig._PWDuplicateCards) << L" ┃" << endl;
	wcout << centreString(L"├────────────────────────────────────────────┼───┨") << endl;
	wcout << L"                │ Play with Coins                        (C) │ " << toggleChar(_tempConfig._PWCoins) << L" ┃" << endl;
	wcout << centreString(L"├────────────────────────────────────────────┼───┨") << endl;
	wcout << L"                │ Play with Double or Nothing Mode       (N) │ " << toggleChar(_tempConfig._PWDlbNothing) << L" ┃" << endl;
	wcout << centreString(L"├────────────────────────────────────────────┼───┨") << endl;
	wcout << L"                │ Number of Rounds                  ( 1 / 2) │ " << _tempConfig._NumPlaySets << L" ┃" << endl;
	wcout << centreString(L"┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┷━━━┛") << endl;
	MakeSpace(6);
	SetCmdPromt(L"Select Option to toggle or type 'B' to Return to the Title Screen (B)"); // Set Command Promt Message
}
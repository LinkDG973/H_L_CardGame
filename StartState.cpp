#include "Game.h"
#include "States.h"

void StartState::DrawTitleScreen() {
	wcout << BOARDER << endl << BOARDER << endl;
	wcout << CARD_INDENT << CARD_INDENT << L"┌─┒ ┌─┒┌─────┒┌─────┒┌─┒ ┌─┒┌─────┒┌────┒" << endl
		  << CARD_INDENT << CARD_INDENT << L"│ ┃ │ ┃┕━┑ ┏━┛│┏━━┑ ┃│ ┃ │ ┃│ ┏━━━┛│ ┏━┑┃ " << endl
		  << CARD_INDENT << CARD_INDENT << L"│ ┖─┘ ┃  │ ┃  │┃  ┕━┛│ ┖─┘ ┃│ ┖───┒│ ┖─┘┖┒" << endl
		  << CARD_INDENT << CARD_INDENT << L"│ ┏━┑ ┃  │ ┃  │┃ ┌──┒│ ┏━┑ ┃│ ┏━━━┛│ ┏━┑ ┃" << endl
		  << CARD_INDENT << CARD_INDENT << L"│ ┃ │ ┃┌─┘ ┖─┒│┖─┴─ ┃│ ┃ │ ┃│ ┖───┒│ ┃ │ ┃" << endl
		  << CARD_INDENT << CARD_INDENT << L"┕━┛ ┕━┛┕━━━━━┛┕━━━━━┛┕━┛ ┕━┛┕━━━━━┛┕━┛ ┕━┛" << endl
		  << CARD_INDENT << CARD_INDENT << L"    ┌─┒    ┌─────┒┌┒   ┌┒┌─────┒┌────┒" << endl
		  << CARD_INDENT << CARD_INDENT << L"    │ ┃    │ ┏━┑ ┃│┃┌─┒│┃│ ┏━━━┛│ ┏━┑┃" << endl
		  << CARD_INDENT << CARD_INDENT << L"    │ ┃    │ ┃ │ ┃│┃│ ┃│┃│ ┖───┒│ ┖─┘┖┒" << endl
		  << CARD_INDENT << CARD_INDENT << L"    │ ┃    │ ┃ │ ┃│┃│ ┃│┃│ ┏━━━┛│ ┏━┑ ┃" << endl
		  << CARD_INDENT << CARD_INDENT << L"    │ ┖───┒│ ┖─┘ ┃│┖┘ ┖┘┃│ ┖───┒│ ┃ │ ┃" << endl
		  << CARD_INDENT << CARD_INDENT << L"    ┕━━━━━┛┕━━━━━┛┕━━━━━┛┕━━━━━┛┕━┛ ┕━┛" << endl;
	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << L"By : Oliver Callaghan" << endl;

	wcout << BOARDER << endl;
	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << "     Main Menu" << endl;
	wcout << BOARDER << endl;
	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << L"   Play Game (P)" << endl;
	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << "   Settings (S)" << endl;
	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << "     Rules (R)" << endl;
	wcout << BOARDER << endl;
	if (!_ValidInput) wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << L"Invalid input, please try again." << endl;
	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << L"Select Option (P / S / R) \u2192 ";
}

void StartState::DrawRulesScreen() {
	wcout << BOARDER << endl << BOARDER << endl;
	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << "     RULES" << endl;
	wcout << BOARDER << endl;
	wcout << SMALL_INDENT << L"HOW TO PLAY" << endl;
	wcout << BOARDER << endl;
	wcout << SMALL_INDENT << L" ⌂ The player is presented with one card face-up and several face-down cards." << endl;
	wcout << SMALL_INDENT << L"   They must make an educated guess whether they or not their card is higher" << endl;
	wcout << SMALL_INDENT << L"   or lower than the card shown above." << endl;
	wcout << SMALL_INDENT << L" ⌂ If they guess correctly, they are awarded with 150 points." << endl;
	wcout << SMALL_INDENT << L" ⌂ If they guess incorrectly, they are deducted 100 points." << endl;
	wcout << BOARDER << endl;
	wcout << SMALL_INDENT << L"CONTROLS" << endl;
	wcout << BOARDER << endl;
	wcout << SMALL_INDENT << L" ⌂ Each operation in the game can be selected by inputing a single character." << endl;
	wcout << SMALL_INDENT << L"   Character codes are shown next to their respective operation." << endl;
	wcout << SMALL_INDENT << L" ⌂ For Example : 'Back (B)' allows the player to go back by inputing 'B'." << endl;
	wcout << SMALL_INDENT << L" ⌂ Inputs work regardless of capitalisation. Inputing 'b' works the same as 'B'." << endl;
	wcout << BOARDER << endl;
	wcout << SMALL_INDENT << L"DOUBLE OR NOTHING MODE" << endl;
	wcout << BOARDER << endl;
	wcout << SMALL_INDENT << L" ⌂ This is a rule" << endl;
	wcout << SMALL_INDENT << L" ⌂ This is a rule" << endl;
	wcout << BOARDER << endl;
	wcout << SMALL_INDENT << L"DUPLICATE CARDS" << endl;
	wcout << BOARDER << endl;
	wcout << SMALL_INDENT << L" ⌂ This is a rule" << endl;
	wcout << SMALL_INDENT << L" ⌂ This is a rule" << endl;
	wcout << BOARDER << endl;
	wcout << SMALL_INDENT << L"COINS MODE" << endl;
	wcout << BOARDER << endl;
	wcout << SMALL_INDENT << L" ⌂ This is a rule" << endl;
	wcout << SMALL_INDENT << L" ⌂ This is a rule" << endl;
	wcout << BOARDER << endl;
	if (!_ValidInput) wcout << CARD_INDENT << L"Invalid input, please try again." << endl;
	wcout << CARD_INDENT << L"Input (B) to Return to the Title Screen \u2192 ";
}

bool StartState::CheckInput(char _Input) {
	if (!_showingRules) {
		switch (_Input) {
		case 'P':
			Game::getInstance().SwitchState(SETUP_STATE);
			break;
		case 'S':  break;
		case 'R':  _showingRules = true; break;
		default: return false; break;
		}
	}
	else {
		switch (_Input) {
		case 'B': _showingRules = false; break;
		default: return false; break;
		}
	}

	return true;
}

void StartState::Render() {
	if (!_showingRules) {
		DrawTitleScreen();
	}
	else {
		DrawRulesScreen();
	}
}
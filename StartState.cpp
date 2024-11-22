#include "Game.h"
#include "States.h"

void StartState::DrawTitleScreen() {
	wcout << BOARDER << endl << BOARDER << endl << endl;
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
	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << L"BY - OLIVER CALLAGHAN" << endl << endl;

	wcout << BOARDER << endl;
	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << "     MAIN MENU" << endl;
	wcout << BOARDER << endl << endl << endl;
	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << L"   PLAY GAME (P)" << endl;
	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << "   SETTINGS (S)" << endl;
	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << "     RULES (R)" << endl << endl << endl << endl;
	wcout << BOARDER << endl;
	if (!_ValidInput) wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << L"Invalid input, please try again." << endl;
	else wcout << endl;
	wcout << BOARDER << endl;
	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << L"Select Option (P / S / R) \u2192 ";
}

void StartState::DrawRulesScreen() {
	wcout << BOARDER << endl << BOARDER << endl;
	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << "     RULES" << endl;
	wcout << BOARDER << endl;

	switch (_currentPage)
	{
	case 2: break;
	case 3: break;
	default:
		wcout << L"     ┌───────────────────────────────────────────────────────────────────────┒" << endl;
		wcout << L"     │ HOW TO PLAY                                                           ┃" << endl;
		wcout << L"     ├───────────────────────────────────────────────────────────────────────┨" << endl;
		wcout << L"     │ ⌂ The player is presented with one card face-up and several face-down ┃" << endl;
		wcout << L"     │   cards. They must make an educated guess whether they or not their   ┃" << endl;
		wcout << L"     │   card is higher or lower than the card shown above.                  ┃" << endl;
		wcout << L"     │ ⌂ If they guess correctly, they are awarded with 150 points.          ┃" << endl;
		wcout << L"     │ ⌂ If they guess incorrectly, they are deducted 100 points.            ┃" << endl;
		wcout << L"     ├───────────────────────────────────────────────────────────────────────┨" << endl;
		wcout << L"     │ CONTROLS                                                              ┃" << endl;
		wcout << L"     ├───────────────────────────────────────────────────────────────────────┨" << endl;
		wcout << L"     │ ⌂ Each operation in the game can be selected by inputing a single     ┃" << endl;
		wcout << L"     │   character. Character codes are shown next to their respective       ┃" << endl;
		wcout << L"     │   operation.                                                          ┃" << endl;
		wcout << L"     │ ⌂ For Example : 'Back (B)' allows the player to go back by inputing   ┃" << endl;
		wcout << L"     │   'B'. Inputs work regardless of capitalisation. Inputing 'b' works   ┃" << endl;
		wcout << L"     │   the same as 'B'.                                                    ┃" << endl;
		wcout << L"     ├───────────────────────────────────────────────────────────────────────┨" << endl;
		wcout << L"     │ NUMBER OF CARD ROWS                                                   ┃" << endl;
		wcout << L"     ├───────────────────────────────────────────────────────────────────────┨" << endl;
		wcout << L"     │ ⌂ There are 10 face-down cards in the game be defualt. This number    ┃" << endl;
		wcout << L"     │   can be increased to 15 or decreased to 5 in the Game Setup Menu.    ┃" << endl;
		wcout << L"     ┕━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┛" << endl;
		break;
	}

	wcout << L"     Select Page (1 / 2 / 3)                                        PAGE " << _currentPage << L" - 3" << endl;
	wcout << BOARDER << endl;
	if (!_ValidInput) wcout << L"     Invalid input, please try again." << endl;
	else wcout << endl;
	wcout << BOARDER << endl;
	wcout << L"     " << L"Input (B) to Return to the Title Screen \u2192 ";
}

bool StartState::CheckInput(char _Input) {
	if (!_showingRules) {
		switch (_Input) {
		case 'P': Game::getInstance().SwitchState(PLAY_STATE); break;
		case 'S': Game::getInstance().SwitchState(SETUP_STATE); break;
		case 'R':  _showingRules = true; break;
		default: return false; break;
		}
	}
	else {
		switch (_Input) {
		case 'B': 
			_showingRules = false;
			_currentPage = 1;
			break;
		case '1': _currentPage = 1; break;
		case '2': _currentPage = 2; break;
		case '3': _currentPage = 3; break;
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
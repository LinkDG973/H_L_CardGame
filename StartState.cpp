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

void StartState::Update() {
	wstring _Input = L"";
	wcin >> _Input;

	if (_Input == L"P" || _Input == L"p") {
		Game::getInstance().setUserName(_Input);
		Game::getInstance().SwitchState(SETUP_STATE);
	}
	else if (_Input == L"S" || _Input == L"s") {

	}
	else if (_Input == L"R" || _Input == L"r") {

	}
	else {
		_ValidInput = false;
	}

}

void StartState::Render() {
	DrawTitleScreen();
}
#include "Game.h"
#include "States.h"

void StartState::Update() {
	wstring name = L"";
	wcout << BOARDER << endl;
	for (int y = 0; y < 10; ++y) wcout << endl;
	wcout << BOARDER << endl;
	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << "Input Name" << endl;
	wcout << BOARDER << endl;
	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << L"\u2192 ";
	wcin >> name;


	Game::getInstance().setUserName(name);
	Game::getInstance().SwitchState(PLAY_STATE);
}

void StartState::Render() {
	system("cls");

}
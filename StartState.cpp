#include "Game.h"
#include "States.h"

void StartState::Update() {
	wstring name = L"";

	for (int y = 0; y < 10; ++y) wcout << endl;

	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << CARD_INDENT << "Input Name : ";
	wcin >> name;

	Game::getInstance().setUserName(name);
	Game::getInstance().SwitchState(PLAY_STATE);
}

void StartState::Render() {

}
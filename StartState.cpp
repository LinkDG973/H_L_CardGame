#include "Game.h"
#include "States.h"

void StartState::Update() {
	wstring name = L"";

	wcout << "Input Name : ";
	wcin >> name;

	Game::getInstance().setUserName(name);
	Game::getInstance().SwitchState(PLAY_STATE);
}

void StartState::Render() {

}
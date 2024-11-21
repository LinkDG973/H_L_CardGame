#include "Game.h"
#include "States.h"

void SetupState::Update() {
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

void SetupState::Render() {
	wcout << BOARDER << endl << BOARDER << endl;


}
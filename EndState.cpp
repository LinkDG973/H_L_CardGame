#include "Game.h"
#include "States.h"

void EndState::Update() {
	wstring name = L"";
	wcout << BOARDER << endl;
	for (int y = 0; y < 10; ++y) wcout << endl;
	wcout << BOARDER << endl;

	int tempScore = Game::getInstance().GetScore();

	if (tempScore > Game::getInstance().GetHighScore()) {
		Game::getInstance().SetHighScore(tempScore);
		wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << "! NEW HIGH SCORE !" << endl;
	}

	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << "HIGH SCORE : " << Game::getInstance().GetHighScore() << endl;
	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT 
		  << Game::getInstance().GetUserName() << " SCORE : " << tempScore << endl;
	wcout << BOARDER << endl;
	for (int y = 0; y < 10; ++y) wcout << endl;
	wcout << BOARDER << endl;
	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << "Play Again ? Y / N" << endl;
	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << L"\u2192 ";
	wcin >> name;

	Game::getInstance().SwitchState(START_STATE);
}

void EndState::Render() {
	system("cls");

}
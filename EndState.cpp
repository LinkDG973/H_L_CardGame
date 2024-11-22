#include "Game.h"
#include "States.h"

bool EndState::CheckInput(char _Input) {
	switch (_Input) {
	case 'Y':
		Game::getInstance().SwitchState(START_STATE);
	default: 
		system("cls");
		for (int y = 0; y < 10; ++y) wcout << endl;
		wcout << BOARDER << endl;
		wcout << CARD_INDENT << CARD_INDENT << L"THE GAME HAS ENDED. PRESS ANY KEY TO EXIT." << endl;
		wcout << BOARDER << endl;
		for (int y = 0; y < 10; ++y) wcout << endl;

		Game::getInstance().setGameRunning(false);
		return false; 
		break;
	}

	return true;
}

void EndState::Render() {
	wcout << BOARDER << endl << BOARDER << endl;
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
	wcout << BOARDER << endl << BOARDER << endl;
	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << "Play Again ? Y / N" << endl;
	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << L"\u2192 ";
}


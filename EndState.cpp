#include "Game.h"
#include "States.h"

bool EndState::CheckInput(char _Input) {
	switch (_Input) {
	case 'Y':
		Game::getInstance().SwitchState(START_STATE);
	case 'N':
		system("cls");
		wcout << BOARDER << endl << BOARDER << endl;
		for (int y = 0; y < 12; ++y) wcout << endl;
		wcout << BOARDER << endl;
		wcout << CARD_INDENT << CARD_INDENT << L"THE GAME HAS ENDED. THANK YOU FOR PLAYING." << endl;
		wcout << BOARDER << endl;
		for (int y = 0; y < 11; ++y) wcout << endl;
		wcout << BOARDER << endl << endl << BOARDER << endl;
		wcout << CARD_INDENT << CARD_INDENT << L"                            PRESS ANY KEY TO EXIT..." << endl;
		Game::getInstance().setGameRunning(false);
		break;
	default: 
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
		wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << "HIGH SCORE : " << Game::getInstance().GetHighScore() << endl;
	}
	else {
		wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << "HIGH SCORE : " << Game::getInstance().GetHighScore() << endl << endl;
	}

	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT
		<< Game::getInstance().GetUserName() << " SCORE : " << tempScore << endl;
	wcout << BOARDER << endl;
	for (int y = 0; y < 11; ++y) wcout << endl;
	wcout << BOARDER << endl;
	if (!_ValidInput) wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << L"Invalid input, please try again." << endl;
	else wcout << endl;
	wcout << BOARDER << endl;
	wcout << CARD_INDENT << CARD_INDENT << CARD_INDENT << "Play Again ? (Y / N) \u2192 ";
}


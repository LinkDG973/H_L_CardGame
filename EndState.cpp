#include "Game.h"
#include "States.h"

bool EndState::CheckInput(char _Input) {
	switch (_Input) {
		case 'Y': Game::getInstance().SwitchState(START_STATE); break;
		case 'N':
			system("cls");
			wcout << BOARDER << endl << BOARDER << endl;
			MakeSpace(12);
			wcout << BOARDER << endl;
			wcout << centreString(L"THE GAME HAS ENDED. THANK YOU FOR PLAYING.") << endl;
			wcout << BOARDER << endl;
			MakeSpace(11);
			wcout << BOARDER << endl << endl << BOARDER << endl;
			wcout << centreString(L"PRESS ANY KEY TO EXIT...") << endl;
			Game::getInstance().setGameRunning(false);
			break;
		default: return false; break;
	}

	return true;
}

void EndState::SpecificRender() {
	MakeSpace(10);
	wcout << BOARDER << endl;

	int tempVal = 0;
	wstring mode = L"COINS : £";
	wstringstream _MSG;
	if (Game::getInstance().GetGameConfig()._PWCoins) {
		tempVal = Game::getInstance().GetCoins();
	}
	else {
		tempVal = Game::getInstance().GetScore();
		mode = L"SCORE : ";
	}

	if (tempVal > Game::getInstance().GetHighScore()) {
		wstringstream _MSG2;
		Game::getInstance().SetHighScore(tempVal);
		wcout << centreString(L"! NEW HIGH SCORE !") << endl;
		_MSG2 << L"HIGH SCORE : " << Game::getInstance().GetHighScore() << endl;
		wcout << centreString(_MSG2.str()) << endl;
	}
	else {
		wstringstream _MSG2;
		_MSG2 << "HIGH SCORE : " << Game::getInstance().GetHighScore();
		wcout << centreString(_MSG2.str()) << endl << endl;
	}

	_MSG << mode << tempVal;

	wcout << centreString(_MSG.str()) << endl;
	wcout << BOARDER << endl;

	MakeSpace(11);
	SetCmdPromt(L"Play Again ? (Y / N)");
}

#include "Game.h"
#include "States.h"

bool EndState::CheckInput(char _Input) {
	if (_DblN_Played == false) {
		switch (_Input)
		{
		case 'Y':
			_DblN_Played = true;
			break;
		case 'N':
			_DblN_Played = true;
			break;
		default:
			break;
		}
	}
	else {
		switch (_Input) {
		case 'Y':
			_DblN_Played = false;
			Game::getInstance().SwitchState(START_STATE); break;
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
	}

	return true;
}

void EndState::DrawEndScreen() {
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

void EndState::DrawDblN() {
	Card card1 = Game::getInstance().GetCard(randomNum(0, MAX_DECK_SIZE));
	MakeSpace(4);
	Draw_Card(card1);
	MakeSpace(4);
	for (int i = 0; i < CARD_GRAPHIC_SIZE; ++i) {
		wcout << centreString(_FaceDownCard[i]) << endl;
	}
	MakeSpace(4);
	SetCmdPromt(L"Go for double or nothing? (Y / N)");
}

void EndState::SpecificRender() {
	if (Game::getInstance().GetGameConfig()._PWDlbNothing && !_DblN_Played) {
		DrawDblN();
	}
	else {
		DrawEndScreen();
	}
}
